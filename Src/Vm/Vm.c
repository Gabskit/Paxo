#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "vars.c" // Arena y variables
#include "cast.c"
#include "Ffi.c"

// 1. Sincronización estricta con el objeto OP de abytec.js
typedef enum : uint8_t {
    OP_WRITE = 0, OP_READ = 1, OP_EXPAND = 2, OP_COLLAPSE = 3,
    OP_ADD = 4, OP_SUB = 5, OP_MUL = 6, OP_DIV = 7, OP_CAST = 8,
    OP_LOAD_VAR = 9, OP_STORE_VAR = 10, OP_PRINT = 11,
    OP_JUMP = 12, OP_JUMP_IF_FALSE = 13, OP_JUMP_IF_TRUE = 14, OP_HALT = 15,
    OP_CALL = 16, OP_CALL_NATIVE = 17,
    OP_EQ = 18, OP_NEQ = 19, OP_LT = 20, OP_GT = 21, OP_LTE = 22, OP_GTE = 23,
    OP_AND = 24, OP_OR = 25, OP_NOT = 26,
    OP_BIT_AND = 27, OP_BIT_OR = 28, OP_BIT_NOT = 29, OP_BIT_XOR = 30, OP_BIT_SHL = 31, OP_BIT_SHR = 32,
    OP_INC = 33, OP_DEC = 34,
    OP_RETURN = 35, OP_CALL_VAR = 36,
    OP_ARRAY_NEW = 37, OP_ARRAY_GET = 38, OP_ARRAY_SET = 39,
    OP_PKG_NEW = 40, OP_PKG_GET = 41, OP_PKG_SET = 42,
    OP_TRY_SETUP = 43, OP_TRY_END = 44, OP_THROW = 45,
    OP_STORE_LOCAL = 46, OP_LOAD_LOCAL = 47, OP_CALL_METHOD = 48,
    OP_THIS_GET = 49, OP_THIS_SET = 50
} LEPOpCode;

// Macro para leer punteros como u16 generados por writeUInt16LE en el compilador
#define READ_U16(ip) ((uint16_t)((uint16_t)(ip)[0] | ((uint16_t)(ip)[1] << 8)))

// Estructura de pila para saltos de funciones sin usar la recursividad de C
typedef struct {
    size_t saved_pivot;          // Para restaurar la Arena al hacer Return
    size_t saved_var_count;      // Para destruir IDs generados
    uint32_t* saved_regs_ptr;    // Ventana de registros anterior
    uint8_t* return_ip;          // A donde regresar en el bytecode
} LEPCallFrame;

typedef struct {
    LEPEnv env;
    uint8_t* ip;
    bool is_running;
    
    // Mapeo: Registro de abytec.js (0-65535) -> ID real en LEPEnv
    // Cada función recibe su propia "ventana" en este arreglo
    uint32_t registers[65536 * 16]; 
    uint32_t* current_regs; 
    
    LEPCallFrame call_stack[256];
    size_t call_depth;
    
    // El "Return Slot" físico persistente asignado en el inicio
    uint32_t universal_return_id;
    LEPNativeRegistry ffi;
} LEPVM;

LEPVM init_vm() {
    LEPVM vm = {0};

    // Capacidad inicial del buffer de datos (ej. 20 MB)
    vm.env.arena_capacity = 20 * 1024 * 1024;
    vm.env.start_ptr = malloc(vm.env.arena_capacity);

    // Capacidad inicial de la tabla de etiquetas (ej. 65,536 variables)
    vm.env.tag_capacity = 65536;
    vm.env.tags = malloc(sizeof(LEPVartag) * vm.env.tag_capacity);

    // Creamos el registro virtual 65535 como Return Slot permanente
    static const uint8_t EMPTY_SLOT[16] = {0};
    vm.universal_return_id = lep_push_var(&vm.env, INT, L, (void*)EMPTY_SLOT, 16);

    vm.current_regs = vm.registers;
    LEP_ffi_init(&vm.ffi);
    vm.is_running = true;

    return vm;
}


void vm_execute(LEPVM* vm, uint8_t* bytecode) {
    vm->ip = bytecode;
    
    while (vm->is_running) {
        uint8_t instruction = *vm->ip;

        switch (instruction) {
            
            case OP_HALT: {
                vm->is_running = false;
                break;
            }

            case OP_ADD: {
    uint16_t reg_left  = READ_U16(vm->ip + 1);
    uint16_t reg_right = READ_U16(vm->ip + 3);
    uint16_t reg_dest  = READ_U16(vm->ip + 5);

    uint32_t id_a = vm->current_regs[reg_left];
    uint32_t id_b = vm->current_regs[reg_right];

    LEPType type_a = vm->env.tags[id_a].type;
    LEPType type_b = vm->env.tags[id_b].type;

    // Caso 1: Enteros puros
    if (type_a == INT && type_b == INT) {
        int64_t res = LEP_AS(&(vm->env), id_a, int64_t) + LEP_AS(&(vm->env), id_b, int64_t);
        vm->current_regs[reg_dest] = LEP_PUSH(&(vm->env), res);
    }
    // Caso 2: Punto Fijo (FRAC / ACCUM C23)
    else if (type_a == FRAC && type_b == FRAC) {
        _Fract res = LEP_AS(&(vm->env), id_a, _Fract) + LEP_AS(&(vm->env), id_b, _Fract);
        vm->current_regs[reg_dest] = LEP_PUSH(&(vm->env), res);
    }
    else if (type_a == ACCUM && type_b == ACCUM) {
        _Accum res = LEP_AS(&(vm->env), id_a, _Accum) + LEP_AS(&(vm->env), id_b, _Accum);
        vm->current_regs[reg_dest] = LEP_PUSH(&(vm->env), res);
    }
    // Caso 3: Flotantes
    else if (type_a == FP || type_b == FP) {
		double res = LEP_AS(&(vm->env), id_a, double) + LEP_AS(&(vm->env), id_b, double);
		vm->current_regs[reg_dest] = LEP_PUSH(&(vm->env), res);
    }
    else if (type_a == SFP || type_b == SFP) {
    	_Float16 res = LEP_AS(&(vm->env), id_a, _Float16) + LEP_AS(&(vm->env), id_b, double);
    	vm->current_regs[reg_dest] = LEP_PUSH(&(vm->env), res);
	}
    
    vm->ip += 7;
    break;
}


            case OP_CALL_NATIVE: {
                // opcode(1) + nativeId(2) + argc(1) + base(2) + dest(2) = 8 bytes
                uint16_t native_id = READ_U16(vm->ip + 1);
                uint8_t argc = *(vm->ip + 3);
                uint16_t base_reg = READ_U16(vm->ip + 4);
                uint16_t dest_reg = READ_U16(vm->ip + 6);
                bool ok = false;
                uint32_t result = 0;
                uint32_t *args = vm->current_regs + base_reg;

                // 100 = ffiCall(name, ...args)
                if (native_id == 100) {
                    if (argc >= 1) {
                        uint32_t name_id = args[0];
                        if (name_id < vm->env.var_count && vm->env.tags[name_id].type == STRING) {
                            const char *name = (const char *)lep_get_var_data(&(vm->env), name_id);
                            result = LEP_ffi_call_name(&vm->ffi, &(vm->env), name, args + 1, (uint8_t)(argc - 1), &ok);
                        }
                    }
                } else if (native_id == 101) {
                    if (argc == 1) {
                        uint32_t path_id = args[0];
                        if (path_id < vm->env.var_count && vm->env.tags[path_id].type == STRING) {
                            const char *path = (const char *)lep_get_var_data(&(vm->env), path_id);
                            ok = LEP_ffi_load(&vm->ffi, path);
                            int64_t b = ok ? 1 : 0;
                            result = lep_push_var(&(vm->env), INT, M, &b, sizeof(b));
                        }
                    }
                } else {
                    result = LEP_ffi_call_id(&vm->ffi, &(vm->env), native_id, args, argc, &ok);
                }
                if (!ok) {
                    int64_t zero = 0;
                    result = lep_push_var(&(vm->env), INT, M, &zero, sizeof(zero));
                }
                vm->current_regs[dest_reg] = result;
                vm->ip += 8;
                break;
            }

            case OP_CALL: {
                // Leer: opcode(1) + funcReg(2) + args_len(1) + base(2) = 6 bytes
                uint16_t func_reg = READ_U16(vm->ip + 1);
                uint8_t args_len = *(vm->ip + 3);
                uint16_t base_reg = READ_U16(vm->ip + 4);
                
                // Extraer el puntero de instrucción de la función almacenada
                uint32_t func_id = vm->current_regs[func_reg];
                LEPFunction func_data = LEP_AS(&(vm->env), func_id, LEPFunction);
                
                // Configurar Frame de retorno
                LEPCallFrame* frame = &vm->call_stack[vm->call_depth++];
                frame->saved_pivot = vm->env.pivot;
                frame->saved_var_count = vm->env.var_count;
                frame->saved_regs_ptr = vm->current_regs;
                frame->return_ip = vm->ip + 6;
                
                // Desplazar la ventana de registros para la nueva función
                vm->current_regs += 65536;
                
                // Copiar los argumentos pasados a la nueva ventana local
                for(uint8_t i = 0; i < args_len; i++) {
                    vm->current_regs[i] = frame->saved_regs_ptr[base_reg + i];
                }
                
                // Saltar a la función en el bytecode
                vm->ip = bytecode + func_data.ip;
                break;
            }

            case OP_RETURN: {
                // Leer: opcode(1) + valueReg(2) + destReg(2) = 5 bytes
                uint16_t val_reg = READ_U16(vm->ip + 1);
                
                // Extraer la variable resultado a devolver
                uint32_t local_result_id = vm->current_regs[val_reg];
                LEPVartag ret_tag = vm->env.tags[local_result_id];
                void* ret_data = lep_get_var_data(&(vm->env), local_result_id);
                
                // Transmutar el universal_return_slot con la Técnica In-Place
                lep_transmute_var(&(vm->env), vm->universal_return_id, ret_tag.type, ret_tag.bytesize, ret_data, ret_tag.bytesize);
                
                // Destruir entorno local
                vm->call_depth--;
                LEPCallFrame* frame = &vm->call_stack[vm->call_depth];
                
                vm->env.pivot = frame->saved_pivot;
                vm->env.var_count = frame->saved_var_count;
                vm->current_regs = frame->saved_regs_ptr;
                
                // En abytec.js, el resultado siempre se lee del registro 65535 tras un CALL
                vm->current_regs[65535] = vm->universal_return_id;
                
                vm->ip = frame->return_ip;
                break;
            }

            case OP_READ: {
                // OP_READ se emite después de OP_CALL para capturar el 65535
                uint16_t src_reg = READ_U16(vm->ip + 1);
                uint16_t dest_reg = READ_U16(vm->ip + 3);
                
                vm->current_regs[dest_reg] = vm->current_regs[src_reg];
                
                vm->ip += 5;
                break;
            }
                        // ==========================================
            // CARGA DE CONSTANTES Y LITERALES
            // ==========================================
            case OP_WRITE: {
                // Leer: opcode(1) + type_js(1) + destReg(2) = 4 bytes base
                uint8_t type_js = *(vm->ip + 1);
                uint16_t reg_dest = READ_U16(vm->ip + 2);
                
                uint8_t* payload_ptr = vm->ip + 4;
                uint32_t bytes_avanzados = 4;
                
                // Estos tipos corresponden a "TYPE" en abytec.js
                if (type_js == 0) { // TYPE.NUM (payload = 8 bytes)
                    uint64_t raw_num = *(uint64_t*)payload_ptr;
                    
                    // TODO: Aquí decodificas tu formato personalizado de Mobile Point.
                    // Por ahora, empujamos el valor crudo en un registro temporal UINT
                    vm->current_regs[reg_dest] = lep_push_var(&(vm->env), UINT, M, &raw_num, 8);
                    bytes_avanzados += 8;
                }
                else if (type_js == 6) { // TYPE.STRING
                    uint16_t str_len = READ_U16(payload_ptr);
                    
                    // Asignamos memoria C-string estática en la Arena 
                    // (Asumiendo que lep_push_var copia los bytes_avanzados)
                    vm->current_regs[reg_dest] = lep_push_var(&(vm->env), STRING, M, payload_ptr + 2, str_len);
                    bytes_avanzados += 2 + str_len;
                }
                else if (type_js == 3) { // TYPE.BOOL (payload = 1 byte)
                    bool val = (*payload_ptr) != 0;
                    vm->current_regs[reg_dest] = LEP_PUSH(&(vm->env), val);
                    bytes_avanzados += 1;
                }
                // (Agregar los demás TYPE de abytec.js como CHAR, COLOR, etc.)
                
                vm->ip += bytes_avanzados;
                break;
            }

            // ==========================================
            // CASTING EXPLICITO
            // ==========================================
            case OP_CAST: {
                // OP_CAST srcReg(2) + destType(1) + destReg(2) = 6 bytes
                uint16_t reg_src = READ_U16(vm->ip + 1);
                uint8_t target_type = *(vm->ip + 3);
                uint16_t reg_dest = READ_U16(vm->ip + 4);
                
                uint32_t src_id = vm->current_regs[reg_src];
                
                // Usamos cast.c
                vm->current_regs[reg_dest] = lep_cast_var(&(vm->env), src_id, (LEPType)target_type);
                
                vm->ip += 6;
                break;
            }

            // ==========================================
            // CONTROL DE FLUJO (JUMPS)
            // ==========================================
            case OP_JUMP: {
                // OP_JUMP offset(2) = 3 bytes
                int16_t offset = *(int16_t*)(vm->ip + 1);
                
                // En abytec.js el offset se calcula desde ip_despues_de_la_instruccion (ip + 3)
                vm->ip += 3 + offset;
                break;
            }

            case OP_JUMP_IF_FALSE: {
                // OP_JUMP_IF_FALSE condReg(2) + offset(2) = 5 bytes
                uint16_t reg_cond = READ_U16(vm->ip + 1);
                int16_t offset = *(int16_t*)(vm->ip + 3);
                
                uint32_t cond_id = vm->current_regs[reg_cond];
                LEPVartag cond_tag = vm->env.tags[cond_id];
                void* cond_data = lep_get_var_data(&(vm->env), cond_id);
                
                bool is_true = false;
                
                // Evaluación "Truthness" rápida
                // Extensión para Truthness completa en Vm.c:
switch (cond_tag.type) {
    case BOOL:  is_true = *(bool*)cond_data; break;
    case TRIT:  is_true = (*(uint8_t*)cond_data == 1); break;
    case INT:   is_true = (*(int64_t*)cond_data != 0); break;
    case UINT:  is_true = (*(uint64_t*)cond_data != 0); break;
    case FP:    is_true = (*(double*)cond_data != 0.0); break;
    case FRAC:  is_true = (*(_Fract*)cond_data != 0.0r); break;
    case ACCUM: is_true = (*(_Accum*)cond_data != 0.0k); break;
    default: break;
}

                
                if (!is_true) {
                    vm->ip += 5 + offset; // Saltar
                } else {
                    vm->ip += 5; // Continuar normal
                }
                break;
            }

        }
    }
}

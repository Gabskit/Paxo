/* Light Environment Processing VM */
#pragma once
#include "Calc.c"
#include "Deque.c"
#include "Typecast_and_read.c"
#include <stdint.h>
#include <string.h>

typedef struct {
  const uint8_t *bytecode;
  size_t ip; // Instruction Pointer (puntero de instrucción)
} VM;

typedef enum {
  OP_PUSH,
  OP_POP,
  OP_ADD,
  OP_SUB,
  OP_MUL,
  OP_DIV,
  OP_CAST,
  OP_LOAD_VAR,  // [uint16_t index] -> Push var
  OP_STORE_VAR, // [uint16_t index] -> Pop var
  OP_PRINT,
  OP_JUMP,          // [int16_t offset]
  OP_JUMP_IF_FALSE, // [int16_t offset]
  OP_HALT           // Detener la VM
} PaxoOpcode;

void vm_init(VM *vm, const uint8_t *bytecode) {
  vm->bytecode = bytecode;
  vm->ip = 0;
}

void vm_run(VM *vm, Deque *stack, PaxoVar *globals) {
  bool running = true;

  while (running) {
    uint8_t op = vm->bytecode[vm->ip++];

    switch (op) {
    case OP_PUSH: {
      uint8_t var_type = vm->bytecode[vm->ip++];
      PaxoVar val = {0};
      val.type = var_type;
      switch (var_type) {
      case NUM4: {
        val.as.number4 = *(Num4 *)(vm->bytecode + vm->ip);
        vm->ip += sizeof(Num4);
        break;
      }
      case NUM6: {
        val.as.number6 = *(Num6 *)(vm->bytecode + vm->ip);
        vm->ip += sizeof(Num6);
        break;
      }
      case NUM8: {
        val.as.number8 = *(Num8 *)(vm->bytecode + vm->ip);
        vm->ip += sizeof(Num8);
        break;
      }
      case NUM16: {
        val.as.number16 = *(Num16 *)(vm->bytecode + vm->ip);
        vm->ip += sizeof(Num16);
        break;
      }
      case NUM32: {
        val.as.number32 = *(Num32 *)(vm->bytecode + vm->ip);
        vm->ip += sizeof(Num32);
        break;
      }
      case NUM64: {
        val.as.number64 = *(Num64 *)(vm->bytecode + vm->ip);
        vm->ip += sizeof(Num64);
        break;
      }
      case BOOL: {
        val.as.truebool = vm->bytecode[vm->ip++];
        break;
      }
      case TRIT: {
        val.as.bit = vm->bytecode[vm->ip++];
        break;
      }
      case CHAR: {
        val.as.chara = vm->bytecode[vm->ip++];
        break;
      }
      case POINT: {
        memcpy(&val.as.puntero, vm->bytecode + vm->ip, sizeof(void *));
        vm->ip += sizeof(void *);
        break;
      }
      default:
        // Tipo desconocido o no soportado en OP_PUSH directo
        break;
      }

      // 3. Empujar la estructura completa ya armada a la pila
      deque_push_back(stack, val);
      break;
    }

    case OP_POP: {
      deque_pop_back(stack);
      break;
    }

    case OP_ADD: {
      PaxoVar b = deque_pop_back(stack);
      PaxoVar a = deque_pop_back(stack);
      PaxoVar res = {0};

      if (a.type == NUM32 && b.type == NUM32) {
        res.type = NUM32;
        res.as.number32 = add_num32(a.as.number32, b.as.number32);
      } else if (a.type == NUM8 && b.type == NUM8) {
        res.type = NUM8;
        res.as.number8 = add_num8(a.as.number8, b.as.number8);
      } else if (a.type == NUM16 && b.type == NUM16) {
        res.type = NUM16;
        res.as.number16 = add_num16(a.as.number16, b.as.number16);
      } else if (a.type == NUM64 && b.type == NUM64) {
        res.type = NUM64;
        res.as.number64 = add_num64(a.as.number64, b.as.number64);
      } else {
      }

      deque_push_back(stack, res);
      break;
    }

    case OP_SUB: {
      PaxoVar b = deque_pop_back(stack);
      PaxoVar a = deque_pop_back(stack);
      PaxoVar res = {0};

      if (a.type == NUM32 && b.type == NUM32) {
        res.type = NUM32;
        res.as.number32 = sub_num32(a.as.number32, b.as.number32);
      } else if (a.type == NUM8 && b.type == NUM8) {
        res.type = NUM8;
        res.as.number8 = sub_num8(a.as.number8, b.as.number8);
      }
      // ... (repetir para Num16 y Num64)

      deque_push_back(stack, res);
      break;
    }

    case OP_LOAD_VAR: {
      uint16_t index = *(uint16_t *)(vm->bytecode + vm->ip);
      vm->ip += sizeof(uint16_t);
      deque_push_back(stack, globals[index]);
      break;
    }

    case OP_STORE_VAR: {
      uint16_t index = *(uint16_t *)(vm->bytecode + vm->ip);
      vm->ip += sizeof(uint16_t);
      globals[index] = deque_pop_back(stack);
      break;
    }

    case OP_PRINT: {
      PaxoVar val = deque_pop_back(stack);
      if (val.type == NUM32) {
        const char8_t *str = readnum32(val.as.number32, 1);
        printf("%s\n", (const char *)str);
      } else if (val.type == NUM8) {
        const char8_t *str = readnum8(val.as.number8, 1);
        printf("%s\n", (const char *)str);
      } else if (val.type == BOOL) {
        const char8_t *str = readbool(val.as.truebool);
        printf("%s\n", (const char *)str);
      }
      break;
    }

    case OP_JUMP: {
      int16_t offset = *(int16_t *)(vm->bytecode + vm->ip);
      vm->ip += sizeof(int16_t);
      vm->ip += offset;
      break;
    }

    case OP_JUMP_IF_FALSE: {
      int16_t offset = *(int16_t *)(vm->bytecode + vm->ip);
      vm->ip += sizeof(int16_t);
      PaxoVar condition = deque_pop_back(stack);

      bool is_false = false;
      if (condition.type == BOOL) {
        is_false = !condition.as.truebool;
      } else if (condition.type == TRIT) {
        is_false = (condition.as.bit == 0);
      }

      if (is_false) {
        vm->ip += offset;
      }
      break;
    }

    case OP_HALT:
    default:
      running = false;
      exit(0);
      break;
    }
  }
}

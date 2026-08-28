/* Light Environment Processing VM (LEP-VM) */
#pragma once
#include "Calc.c"
#include "Deque.c"
#include "Functions.c"
#include "Typecast_and_read.c"
#include "termcolor-c.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#define MAX_FRAMES 128
#define MAX_TRY_FRAMES 64

typedef struct {
  size_t return_ip;
  PaxoVar locals[256];
} CallFrame;

typedef struct {
  size_t catch_ip;
  size_t stack_size;
  size_t frame_count;
} TryFrame;

typedef struct {
  const uint8_t *bytecode;
  size_t bytecode_size;
  size_t ip;
  CallFrame frames[MAX_FRAMES];
  size_t frame_count;
  TryFrame try_frames[MAX_TRY_FRAMES];
  size_t try_frame_count;
} VM;

typedef enum {
  OP_PUSH,
  OP_POP,
  OP_ADD,
  OP_SUB,
  OP_MUL,
  OP_DIV,
  OP_CAST,
  OP_LOAD_VAR,  // [uint16_t index]
  OP_STORE_VAR, // [uint16_t index]
  OP_PRINT,
  OP_JUMP,          // [int16_t offset]
  OP_JUMP_IF_FALSE, // [int16_t offset]
  OP_JUMP_IF_TRUE,  // [int16_t offset]
  OP_HALT,
  OP_CALL,
  OP_CALL_NATIVE,
  // --- Comparación (push BOOL) ---
  OP_EQ,
  OP_NEQ,
  OP_LT,
  OP_GT,
  OP_LTE,
  OP_GTE,
  // --- Lógicos ---
  OP_AND,
  OP_OR,
  OP_NOT,
  // --- Bitwise ---
  OP_BIT_AND,
  OP_BIT_OR,
  OP_BIT_NOT,
  OP_BIT_XOR,
  OP_BIT_SHL,  // •«
  OP_BIT_SHR,  // »•
  // --- Incremento/Decremento ---
  OP_INC,
  OP_DEC,
  OP_RETURN,
  OP_CALL_VAR,
  // --- Arrays ---
  OP_ARRAY_NEW,  // [uint16_t count] — pops count elements, pushes ARRAY
  OP_ARRAY_GET,  // pops index (NUM64) + array, pushes element
  OP_ARRAY_SET,  // pops value + index (NUM64) + array, sets element
  // --- Packages ---
  OP_PKG_NEW,    // [uint16_t field_count] — pops field_count name/value pairs, pushes PACKAGE
  OP_PKG_GET,    // [uint16_t name_len] [chars...] — pops package, pushes field value
  OP_PKG_SET,    // [uint16_t name_len] [chars...] — pops value + package, sets field
  // --- Try/Catch ---
  OP_TRY_SETUP,  // [int16_t catch_offset] — pushes try frame, catch target = ip + catch_offset
  OP_TRY_END,    // pops try frame, jumps past catch block
  OP_THROW,      // pops error value, unwinds to nearest catch handler
  OP_STORE_LOCAL, // [uint16_t index] — stores to frame-local variable
  OP_LOAD_LOCAL,  // [uint16_t index] — loads from frame-local variable
} PaxoOpcode;

void vm_init(VM *vm, const uint8_t *bytecode, size_t bytecode_size) {
  vm->bytecode = bytecode;
  vm->bytecode_size = bytecode_size;
  vm->ip = 0;
}

// Helpers seguros para lectura sin problemas de alineación
static inline uint16_t read_u16(VM *vm) {
  uint16_t val;
  memcpy(&val, vm->bytecode + vm->ip, sizeof(uint16_t));
  vm->ip += sizeof(uint16_t);
  return val;
}

static inline int16_t read_i16(VM *vm) {
  int16_t val;
  memcpy(&val, vm->bytecode + vm->ip, sizeof(int16_t));
  vm->ip += sizeof(int16_t);
  return val;
}

void vm_error(VM *vm, const char *msg);

static inline bool var_is_num_type(enum type t) {
  return t == NUM16 || t == NUM64;
}

static inline Num64 var_num_as64(PaxoVar v) {
  return (var_type(v) == NUM16) ? num16tonum64(var_num16_get(v))
                                : var_num64_get(v);
}

static inline bool var_truthy(PaxoVar v) {
  switch (var_type(v)) {
  case BOOL:
    return var_bool_get(v);
  case TRIT:
    return var_trit_get(v) == 1;
  default:
    return false;
  }
}

static inline size_t var_to_index(PaxoVar v) {
  switch (var_type(v)) {
  case NUM16:
    return (size_t)var_num16_get(v).bc;
  case NUM64:
    return (size_t)var_num64_get(v).bc;
  default:
    return 0;
  }
}

void vm_run(VM *vm, Deque *stack, PaxoVar *globals) {
  bool running = true;

  while (running) {
    if (vm->ip >= vm->bytecode_size) {
      vm_error(vm, "IP fuera de los limites del bytecode");
      break;
    }
    uint8_t op = vm->bytecode[vm->ip++];

    switch (op) {
    case OP_PUSH: {
      uint8_t var_type_tag = vm->bytecode[vm->ip++];
      PaxoVar val = 0;

      switch (var_type_tag) {
      case NUM16: {
        uint16_t raw;
        memcpy(&raw, vm->bytecode + vm->ip, sizeof(raw));
        vm->ip += sizeof(raw);
        val = var_num16(num16_unpack(raw));
        break;
      }
      case NUM64: {
        uint64_t raw;
        memcpy(&raw, vm->bytecode + vm->ip, sizeof(raw));
        vm->ip += sizeof(raw);
        val = var_num64((Num64){.signo = raw & 1,
                                .exp = (raw >> 1) & 0xFF,
                                .bc = (raw >> 9) & bc_max64(),
                                .p = (raw >> 59)});
        break;
      }
      case BOOL:
        val = var_bool(vm->bytecode[vm->ip++] != 0);
        break;
      case TRIT:
        val = var_trit(vm->bytecode[vm->ip++] & 0x3);
        break;
      case CHAR:
        val = var_char((char32_t)vm->bytecode[vm->ip++]);
        break;
      case COLOR: {
        uint8_t r = vm->bytecode[vm->ip++];
        uint8_t g = vm->bytecode[vm->ip++];
        uint8_t b = vm->bytecode[vm->ip++];
        uint8_t a = vm->bytecode[vm->ip++];
        val = var_color(((uint32_t)r << 24) | ((uint32_t)g << 16) |
                        ((uint32_t)b << 8) | a);
        break;
      }
      case INT_FP:
      case PKDEC: {
        uint8_t scale = vm->bytecode[vm->ip++];
        int16_t raw;
        memcpy(&raw, vm->bytecode + vm->ip, sizeof(raw));
        vm->ip += sizeof(raw);
        val = (var_type_tag == INT_FP) ? var_int_fp(raw, scale)
                                        : var_pkdec(raw, scale);
        break;
      }
      case POINT: {
        uint64_t raw;
        memcpy(&raw, vm->bytecode + vm->ip, sizeof(raw));
        vm->ip += sizeof(raw);
        val = var_pin((uint32_t)raw);
        break;
      }
      case STRING: {
        uint16_t len = read_u16(vm);
        val = var_string((const char *)(vm->bytecode + vm->ip));
        vm->ip += len + 1;
        break;
      }
      case FUNC: {
        uint16_t offset = read_u16(vm);
        uint8_t param_count = vm->bytecode[vm->ip++];
        val = var_func(offset, param_count);
        break;
      }
      default:
        vm_error(vm, "tipo de valor desconocido en bytecode");
        running = false;
        break;
      }

      deque_push_back(stack, val);
      break;
    }

    case OP_POP: {
      deque_pop_back(stack);
      break;
    }

#define ARITH_OP(name, op16, op64)                                            \
  case name: {                                                                \
    PaxoVar b = deque_pop_back(stack);                                        \
    PaxoVar a = deque_pop_back(stack);                                        \
    enum type ta = var_type(a), tb = var_type(b);                             \
    PaxoVar res = PAXO_ZERO;                                                  \
    if (var_is_num_type(ta) && var_is_num_type(tb)) {                         \
      if (ta == NUM64 || tb == NUM64) {                                       \
        Num64 r = op64(var_num_as64(a), var_num_as64(b));                     \
        res = var_num64(r);                                                   \
      } else {                                                                \
        Num16 r = op16(var_num16_get(a), var_num16_get(b));                   \
        res = var_num16(r);                                                   \
      }                                                                       \
    } else {                                                                  \
      vm_error(vm, "tipos incompatibles en operación aritmética");            \
    }                                                                         \
    deque_push_back(stack, res);                                              \
    break;                                                                    \
  }

    ARITH_OP(OP_ADD, add_num16, add_num64)
    ARITH_OP(OP_SUB, sub_num16, sub_num64)
    ARITH_OP(OP_MUL, mul_num16, mul_num64)
    ARITH_OP(OP_DIV, div_num16, div_num64)

#undef ARITH_OP

    case OP_LOAD_VAR: {
      uint16_t index = read_u16(vm);
      deque_push_back(stack, globals[index]);
      break;
    }

    case OP_STORE_VAR: {
      uint16_t index = read_u16(vm);
      globals[index] = deque_pop_back(stack);
      break;
    }

    case OP_PRINT: {
      PaxoVar val = deque_pop_back(stack);
      const char8_t *str = NULL;

      switch (var_type(val)) {
      case NUM16:
        str = readnum16(var_num16_get(val), 1);
        break;
      case NUM64:
        str = readnum64(var_num64_get(val), 1);
        break;
      case BOOL:
        str = readbool(var_bool_get(val));
        break;
      case CHAR:
        str = readchar32(var_char_get(val));
        break;
      default:
        break;
      }

      if (str) {
        printf("%s\n", (const char *)str);
      }
      break;
    }

    case OP_JUMP: {
      int16_t offset = read_i16(vm);
      vm->ip += offset;
      break;
    }

    case OP_JUMP_IF_FALSE: {
      int16_t offset = read_i16(vm);
      PaxoVar condition = deque_pop_back(stack);

      bool is_false = false;
      if (var_type(condition) == BOOL)
        is_false = !var_bool_get(condition);
      else if (var_type(condition) == TRIT)
        is_false = (var_trit_get(condition) == 0);

      if (is_false) {
        vm->ip += offset;
      }
      break;
    }
    case OP_CAST: {
      uint8_t target_type = vm->bytecode[vm->ip++];
      PaxoVar val = deque_pop_back(stack);
      enum type src = var_type(val);

      if (src == target_type) {
        deque_push_back(stack, val);
        break;
      }

      PaxoVar res = 0;
      if (target_type == POINT)
        res = var_pin(0);

      switch (src) {
      case NUM16: {
        Num16 n = var_num16_get(val);
        switch (target_type) {
        case NUM64:
          res = var_num64(num16tonum64(n));
          break;
        case BOOL:
          res = var_bool(num16tobool(n));
          break;
        case TRIT:
          res = var_trit(num16totrit(n));
          break;
        case CHAR:
          res = var_char((char32_t)(n.bc > bc_max16() ? bc_max16() : n.bc));
          break;
        case INT_FP:
          res = var_int_fp((int16_t)n.bc, 0);
          break;
        case PKDEC:
          res = var_pkdec((int16_t)n.bc, 0);
          break;
        case COLOR: {
          uint32_t rgba = ((uint32_t)n.bc & 0xFFFFFFu);
          res = var_color((rgba << 8) | 0xFFu);
          break;
        }
        default:
          break;
        }
        break;
      }
      case NUM64: {
        Num64 n = var_num64_get(val);
        switch (target_type) {
        case NUM16:
          res = var_num16(num64tonum16(n));
          break;
        case BOOL:
          res = var_bool(num64tobool(n));
          break;
        case TRIT:
          res = var_trit(num64totrit(n));
          break;
        case CHAR:
          res = var_char((char32_t)(n.bc & 0xFF));
          break;
        case INT_FP:
          res = var_int_fp((int16_t)n.bc, 0);
          break;
        case PKDEC:
          res = var_pkdec((int16_t)n.bc, 0);
          break;
        case COLOR: {
          uint32_t rgba = (uint32_t)(n.bc & 0xFFFFFFFFULL);
          res = var_color((rgba << 8) | 0xFFu);
          break;
        }
        default:
          break;
        }
        break;
      }
      case BOOL: {
        bool b = var_bool_get(val);
        switch (target_type) {
        case NUM16:
          res = var_num16(booltonum16(b));
          break;
        case NUM64:
          res = var_num64(booltonum64(b));
          break;
        case TRIT:
          res = var_trit(booltotrit(b));
          break;
        default:
          break;
        }
        break;
      }
      case TRIT: {
        uint8_t t = var_trit_get(val);
        switch (target_type) {
        case NUM16:
          res = var_num16(trittonum16(t));
          break;
        case NUM64:
          res = var_num64(trittonum64(t));
          break;
        case BOOL:
          res = var_bool(trittobool(t));
          break;
        default:
          break;
        }
        break;
      }
      case CHAR: {
        char32_t c = var_char_get(val);
        switch (target_type) {
        case NUM16: {
          Num16 conv = {0};
          conv.bc = (c > bc_max16()) ? bc_max16() : (uint16_t)c;
          conv.exp = BIAS16;
          conv.p = 0;
          res = var_num16(conv);
          break;
        }
        case NUM64: {
          Num64 conv = {0};
          conv.bc = (uint64_t)c;
          conv.exp = BIAS64;
          conv.p = 0;
          res = var_num64(conv);
          break;
        }
        case BOOL:
          res = var_bool(c != 0);
          break;
        case TRIT:
          res = var_trit(c < 3 ? (uint8_t)c : 0);
          break;
        default:
          break;
        }
        break;
      }
      case STRING: {
        if (target_type == CHAR) {
          const char *s = var_string_get(val);
          res = var_char((s && s[0]) ? (char32_t)(uint8_t)s[0] : 0);
        }
        break;
      }
      case INT_FP:
      case PKDEC: {
        PaxoFxp f = var_fxp_get(val);
        switch (target_type) {
        case NUM64: {
          Num64 conv = {0};
          conv.bc = (uint64_t)f.value;
          conv.exp = BIAS64;
          conv.p = 0;
          res = var_num64(conv);
          break;
        }
        case NUM16: {
          Num16 conv = {0};
          conv.bc = (uint16_t)f.value;
          conv.exp = BIAS16;
          conv.p = 0;
          res = var_num16(conv);
          break;
        }
        default:
          break;
        }
        break;
      }
      case COLOR: {
        uint32_t rgba = var_color_get(val);
        switch (target_type) {
        case NUM64: {
          Num64 conv = {0};
          conv.bc = (uint64_t)rgba;
          conv.exp = BIAS64;
          conv.p = 0;
          res = var_num64(conv);
          break;
        }
        default:
          break;
        }
        break;
      }
      default:
        break;
      }

      deque_push_back(stack, res);
      break;
    }

    case OP_CALL: {
      uint16_t target_ip = read_u16(vm);
      if (vm->frame_count >= MAX_FRAMES) {
        vm_error(vm, "desbordamiento de pila de llamadas");
        running = false;
        break;
      }
      vm->frames[vm->frame_count++] = (CallFrame){.return_ip = vm->ip};
      vm->ip = target_ip;
      break;
    }

    case OP_CALL_NATIVE: {
      uint16_t native_id = read_u16(vm);
      uint8_t argc = vm->bytecode[vm->ip++];
      PaxoVar args[16];
      for (int i = argc - 1; i >= 0; i--)
        args[i] = deque_pop_back(stack);

      PaxoVar result = native_call(native_id, args, argc);
      if (result != PAXO_NO_VALUE)
        deque_push_back(stack, result);
      break;
    }

    case OP_RETURN: {
      if (vm->frame_count == 0) {
        running = false;
        break;
      }
      vm->ip = vm->frames[--vm->frame_count].return_ip;
      break;
    }

    case OP_CALL_VAR: {
      uint8_t argc = vm->bytecode[vm->ip++];
      PaxoVar func_val = deque_pop_back(stack);
      if (var_type(func_val) != FUNC) {
        vm_error(vm, "se esperaba una función");
        running = false;
        break;
      }

      PaxoVar args[256];
      for (int i = argc - 1; i >= 0; i--)
        args[i] = deque_pop_back(stack);

      CallFrame *frame = &vm->frames[vm->frame_count++];
      frame->return_ip = vm->ip;
      for (int i = 0; i < argc; i++)
        frame->locals[i] = args[i];

      vm->ip = var_func_id(func_val);
      break;
    }

    // ==========================================
    // FRAME LOCAL VARIABLES
    // ==========================================
    case OP_STORE_LOCAL: {
      uint16_t index = read_u16(vm);
      vm->frames[vm->frame_count - 1].locals[index] = deque_pop_back(stack);
      break;
    }

    case OP_LOAD_LOCAL: {
      uint16_t index = read_u16(vm);
      deque_push_back(stack, vm->frames[vm->frame_count - 1].locals[index]);
      break;
    }

    // ==========================================
    // ARRAYS
    // ==========================================
    case OP_ARRAY_NEW: {
      uint16_t count = read_u16(vm);
      PaxoArray *arr = malloc(sizeof(PaxoArray));
      arr->len = count;
      arr->capacity = count > 0 ? count : 4;
      arr->items = malloc(sizeof(PaxoVar) * arr->capacity);
      for (int i = count - 1; i >= 0; i--)
        arr->items[i] = deque_pop_back(stack);
      deque_push_back(stack, var_array(arr));
      break;
    }

    case OP_ARRAY_GET: {
      PaxoVar idx_val = deque_pop_back(stack);
      PaxoVar arr_val = deque_pop_back(stack);
      if (var_type(arr_val) != ARRAY) {
        vm_error(vm, "se esperaba un array");
        running = false;
        break;
      }
      size_t idx = var_to_index(idx_val);
      if (idx >= var_array_get(arr_val)->len) {
        vm_error(vm, "índice fuera de rango");
        running = false;
        break;
      }
      deque_push_back(stack, var_array_get(arr_val)->items[idx]);
      break;
    }

    case OP_ARRAY_SET: {
      PaxoVar value = deque_pop_back(stack);
      PaxoVar idx_val = deque_pop_back(stack);
      PaxoVar arr_val = deque_pop_back(stack);
      if (var_type(arr_val) != ARRAY) {
        vm_error(vm, "se esperaba un array");
        running = false;
        break;
      }
      size_t idx = var_to_index(idx_val);
      if (idx >= var_array_get(arr_val)->len) {
        vm_error(vm, "índice fuera de rango");
        running = false;
        break;
      }
      var_array_get(arr_val)->items[idx] = value;
      break;
    }

    // ==========================================
    // PACKAGES
    // ==========================================
    case OP_PKG_NEW: {
      uint16_t field_count = read_u16(vm);
      PaxoPackageField *head = NULL;
      for (uint16_t i = 0; i < field_count; i++) {
        PaxoVar val = deque_pop_back(stack);
        uint16_t name_len = read_u16(vm);
        char *name = malloc(name_len + 1);
        memcpy(name, vm->bytecode + vm->ip, name_len);
        name[name_len] = '\0';
        vm->ip += name_len;
        PaxoPackageField *field = malloc(sizeof(PaxoPackageField));
        field->key = name;
        field->value = val;
        field->hidden = vm->bytecode[vm->ip++] != 0; // flag de visibilidad
        field->next = head;
        head = field;
      }
      deque_push_back(stack, var_pkg(head));
      break;
    }

    case OP_PKG_GET: {
      uint16_t name_len = read_u16(vm);
      char name[256];
      memcpy(name, vm->bytecode + vm->ip, name_len);
      name[name_len] = '\0';
      vm->ip += name_len;
      PaxoVar pkg_val = deque_pop_back(stack);
      if (var_type(pkg_val) != PACKAGE) {
        vm_error(vm, "se esperaba un package");
        running = false;
        break;
      }
      PaxoPackageField *f = var_pkg_get(pkg_val);
      bool found = false;
      while (f) {
        if (strcmp(f->key, name) == 0) {
          found = true;
          break;
        }
        f = f->next;
      }
      if (found) {
        if (f->hidden) {
          vm_error(vm, "campo privado");
          running = false;
          break;
        }
        deque_push_back(stack, f->value);
      }
      if (!found) {
        vm_error(vm, "campo no encontrado");
        running = false;
        break;
      }
      break;
    }

    case OP_PKG_SET: {
      uint16_t name_len = read_u16(vm);
      char name[256];
      memcpy(name, vm->bytecode + vm->ip, name_len);
      name[name_len] = '\0';
      vm->ip += name_len;
      PaxoVar value = deque_pop_back(stack);
      PaxoVar pkg_val = deque_pop_back(stack);
      if (var_type(pkg_val) != PACKAGE) {
        vm_error(vm, "se esperaba un package");
        running = false;
        break;
      }
      PaxoPackageField *f = var_pkg_get(pkg_val);
      while (f) {
        if (strcmp(f->key, name) == 0) {
          if (f->hidden) {
            vm_error(vm, "campo privado");
            running = false;
            break;
          }
          f->value = value;
          break;
        }
        f = f->next;
      }
      break;
    }

    // ==========================================
    // TRY / CATCH / THROW
    // ==========================================
    case OP_TRY_SETUP: {
      int16_t catch_offset = read_i16(vm);
      if (vm->try_frame_count >= MAX_TRY_FRAMES) {
        vm_error(vm, "demasiados try/catch anidados");
        running = false;
        break;
      }
      TryFrame *tf = &vm->try_frames[vm->try_frame_count++];
      tf->catch_ip = vm->ip + catch_offset;
      tf->stack_size = deque_size(stack);
      tf->frame_count = vm->frame_count;
      break;
    }

    case OP_TRY_END: {
      int16_t end_offset = read_i16(vm);
      if (vm->try_frame_count > 0)
        vm->try_frame_count--;
      vm->ip += end_offset;
      break;
    }

    case OP_THROW: {
      PaxoVar error_val = deque_pop_back(stack);
      if (vm->try_frame_count == 0) {
        vm_error(vm, "throw sin try/catch");
        running = false;
        break;
      }
      TryFrame *tf = &vm->try_frames[--vm->try_frame_count];
      while (deque_size(stack) > tf->stack_size)
        deque_pop_back(stack);
      vm->frame_count = tf->frame_count;
      deque_push_back(stack, error_val);
      vm->ip = tf->catch_ip;
      break;
    }

    case OP_JUMP_IF_TRUE: {
      int16_t offset = read_i16(vm);
      PaxoVar condition = deque_pop_back(stack);

      if (var_truthy(condition)) {
        vm->ip += offset;
      }
      break;
    }

    // ==========================================
    // COMPARACIONES (result -> BOOL)
    // ==========================================
#define c_eq(c)  ((c) == 0)
#define c_neq(c) ((c) != 0)
#define c_lt(c)  ((c) < 0)
#define c_gt(c)  ((c) > 0)
#define c_lte(c) ((c) <= 0)
#define c_gte(c) ((c) >= 0)

#define CMP_NUMBERS(chose)                                                    \
  do {                                                                        \
    int c;                                                                    \
    if (ta == NUM64 || tb == NUM64)                                           \
      c = cmp_num64(var_num_as64(a), var_num_as64(b));                        \
    else                                                                      \
      c = cmp_num16(var_num16_get(a), var_num16_get(b));                      \
    result_bool = chose(c);                                                   \
  } while (0)

#define CMP_BOTH(same_kind, expr)                                             \
  do {                                                                        \
    if (ta == tb && ta == same_kind)                                          \
      result_bool = (expr);                                                   \
  } while (0)

    case OP_EQ: {
      PaxoVar b = deque_pop_back(stack);
      PaxoVar a = deque_pop_back(stack);
      enum type ta = var_type(a), tb = var_type(b);
      bool result_bool = false;
      if (var_is_num_type(ta) && var_is_num_type(tb)) {
        CMP_NUMBERS(c_eq);
      } else {
        CMP_BOTH(BOOL, var_bool_get(a) == var_bool_get(b));
        CMP_BOTH(TRIT, var_trit_get(a) == var_trit_get(b));
        CMP_BOTH(CHAR, var_char_get(a) == var_char_get(b));
        CMP_BOTH(POINT, var_pin_get(a) == var_pin_get(b));
        CMP_BOTH(STRING,
                 strcmp(var_string_get(a), var_string_get(b)) == 0);
      }
      deque_push_back(stack, var_bool(result_bool));
      break;
    }

    case OP_NEQ: {
      PaxoVar b = deque_pop_back(stack);
      PaxoVar a = deque_pop_back(stack);
      enum type ta = var_type(a), tb = var_type(b);
      bool result_bool = true;
      if (var_is_num_type(ta) && var_is_num_type(tb)) {
        CMP_NUMBERS(c_neq);
      } else if (ta == tb) {
        result_bool = false;
        CMP_BOTH(BOOL, var_bool_get(a) != var_bool_get(b));
        CMP_BOTH(TRIT, var_trit_get(a) != var_trit_get(b));
        CMP_BOTH(CHAR, var_char_get(a) != var_char_get(b));
        CMP_BOTH(POINT, var_pin_get(a) != var_pin_get(b));
        CMP_BOTH(STRING,
                 strcmp(var_string_get(a), var_string_get(b)) != 0);
      }
      deque_push_back(stack, var_bool(result_bool));
      break;
    }

    case OP_LT: {
      PaxoVar b = deque_pop_back(stack);
      PaxoVar a = deque_pop_back(stack);
      enum type ta = var_type(a), tb = var_type(b);
      bool result_bool = false;
      if (var_is_num_type(ta) && var_is_num_type(tb)) {
        CMP_NUMBERS(c_lt);
      } else {
        CMP_BOTH(CHAR, var_char_get(a) < var_char_get(b));
      }
      deque_push_back(stack, var_bool(result_bool));
      break;
    }

    case OP_GT: {
      PaxoVar b = deque_pop_back(stack);
      PaxoVar a = deque_pop_back(stack);
      enum type ta = var_type(a), tb = var_type(b);
      bool result_bool = false;
      if (var_is_num_type(ta) && var_is_num_type(tb)) {
        CMP_NUMBERS(c_gt);
      } else {
        CMP_BOTH(CHAR, var_char_get(a) > var_char_get(b));
      }
      deque_push_back(stack, var_bool(result_bool));
      break;
    }

    case OP_LTE: {
      PaxoVar b = deque_pop_back(stack);
      PaxoVar a = deque_pop_back(stack);
      enum type ta = var_type(a), tb = var_type(b);
      bool result_bool = false;
      if (var_is_num_type(ta) && var_is_num_type(tb)) {
        CMP_NUMBERS(c_lte);
      } else {
        CMP_BOTH(CHAR, var_char_get(a) <= var_char_get(b));
      }
      deque_push_back(stack, var_bool(result_bool));
      break;
    }

    case OP_GTE: {
      PaxoVar b = deque_pop_back(stack);
      PaxoVar a = deque_pop_back(stack);
      enum type ta = var_type(a), tb = var_type(b);
      bool result_bool = false;
      if (var_is_num_type(ta) && var_is_num_type(tb)) {
        CMP_NUMBERS(c_gte);
      } else {
        CMP_BOTH(CHAR, var_char_get(a) >= var_char_get(b));
      }
      deque_push_back(stack, var_bool(result_bool));
      break;
    }

#undef CMP_BOTH
#undef CMP_NUMBERS
#undef c_eq
#undef c_neq
#undef c_lt
#undef c_gt
#undef c_lte
#undef c_gte

    // ==========================================
    // LÓGICOS (BOOL / TRIT)
    // ==========================================
    case OP_AND: {
      PaxoVar b = deque_pop_back(stack);
      PaxoVar a = deque_pop_back(stack);
      deque_push_back(stack, var_bool(var_truthy(a) && var_truthy(b)));
      break;
    }

    case OP_OR: {
      PaxoVar b = deque_pop_back(stack);
      PaxoVar a = deque_pop_back(stack);
      deque_push_back(stack, var_bool(var_truthy(a) || var_truthy(b)));
      break;
    }

    case OP_NOT: {
      PaxoVar a = deque_pop_back(stack);
      enum type ta = var_type(a);
      bool result_bool = true;
      if (ta == BOOL)
        result_bool = !var_bool_get(a);
      else if (ta == TRIT)
        result_bool = (var_trit_get(a) == 0);
      deque_push_back(stack, var_bool(result_bool));
      break;
    }

    // ==========================================
    // BITWISE (BOOL / TRIT / CHAR)
    // ==========================================
    case OP_BIT_AND: {
      PaxoVar b = deque_pop_back(stack);
      PaxoVar a = deque_pop_back(stack);
      PaxoVar res = 0;
      if (var_type(a) == BOOL && var_type(b) == BOOL) {
        res = var_bool((int)var_bool_get(a) & (int)var_bool_get(b));
      } else if (var_type(a) == TRIT && var_type(b) == TRIT) {
        res = var_trit(var_trit_get(a) & var_trit_get(b));
      }
      deque_push_back(stack, res);
      break;
    }

    case OP_BIT_OR: {
      PaxoVar b = deque_pop_back(stack);
      PaxoVar a = deque_pop_back(stack);
      PaxoVar res = 0;
      if (var_type(a) == BOOL && var_type(b) == BOOL) {
        res = var_bool((int)var_bool_get(a) | (int)var_bool_get(b));
      } else if (var_type(a) == TRIT && var_type(b) == TRIT) {
        res = var_trit(var_trit_get(a) | var_trit_get(b));
      }
      deque_push_back(stack, res);
      break;
    }

    case OP_BIT_NOT: {
      PaxoVar a = deque_pop_back(stack);
      PaxoVar res = 0;
      switch (var_type(a)) {
      case BOOL:
        res = var_bool(!var_bool_get(a));
        break;
      case TRIT:
        res = var_trit(~var_trit_get(a) & 0x3u);
        break;
      case CHAR:
        res = var_char(~var_char_get(a) & 0xFFFFFFFFu);
        break;
      default:
        break;
      }
      deque_push_back(stack, res);
      break;
    }

    case OP_BIT_XOR: {
      PaxoVar b = deque_pop_back(stack);
      PaxoVar a = deque_pop_back(stack);
      PaxoVar res = 0;
      if (var_type(a) == BOOL && var_type(b) == BOOL) {
        res = var_bool(var_bool_get(a) ^ var_bool_get(b));
      } else if (var_type(a) == TRIT && var_type(b) == TRIT) {
        res = var_trit(var_trit_get(a) ^ var_trit_get(b));
      }
      deque_push_back(stack, res);
      break;
    }

    case OP_BIT_SHL: {
      PaxoVar b = deque_pop_back(stack);
      PaxoVar a = deque_pop_back(stack);
      PaxoVar res = 0;
      if (var_type(a) == CHAR && var_type(b) == CHAR) {
        res = var_char(var_char_get(a) << var_char_get(b));
      } else if (var_type(a) == NUM64 && var_type(b) == NUM64) {
        Num64 r = var_num64_get(a);
        r.bc = var_num64_get(a).bc << var_num64_get(b).bc;
        res = var_num64(r);
      } else if (var_type(a) == NUM16 && var_type(b) == NUM16) {
        Num16 r = var_num16_get(a);
        r.bc = var_num16_get(a).bc << var_num16_get(b).bc;
        res = var_num16(r);
      }
      deque_push_back(stack, res);
      break;
    }

    case OP_BIT_SHR: {
      PaxoVar b = deque_pop_back(stack);
      PaxoVar a = deque_pop_back(stack);
      PaxoVar res = 0;
      if (var_type(a) == CHAR && var_type(b) == CHAR) {
        res = var_char(var_char_get(a) >> var_char_get(b));
      } else if (var_type(a) == NUM64 && var_type(b) == NUM64) {
        Num64 r = var_num64_get(a);
        r.bc = var_num64_get(a).bc >> var_num64_get(b).bc;
        res = var_num64(r);
      } else if (var_type(a) == NUM16 && var_type(b) == NUM16) {
        Num16 r = var_num16_get(a);
        r.bc = var_num16_get(a).bc >> var_num16_get(b).bc;
        res = var_num16(r);
      }
      deque_push_back(stack, res);
      break;
    }

    // ==========================================
    // INC / DEC
    // ==========================================
    case OP_INC: {
      PaxoVar a = deque_pop_back(stack);
      switch (var_type(a)) {
      case NUM16: {
        Num16 one = {0};
        one.bc = 1;
        one.exp = BIAS16;
        a = var_num16(add_num16(var_num16_get(a), one));
        break;
      }
      case NUM64: {
        Num64 one = {0};
        one.bc = 1;
        one.exp = BIAS64;
        a = var_num64(add_num64(var_num64_get(a), one));
        break;
      }
      default:
        break;
      }
      deque_push_back(stack, a);
      break;
    }

    case OP_DEC: {
      PaxoVar a = deque_pop_back(stack);
      switch (var_type(a)) {
      case NUM16: {
        Num16 one = {0};
        one.bc = 1;
        one.exp = BIAS16;
        a = var_num16(sub_num16(var_num16_get(a), one));
        break;
      }
      case NUM64: {
        Num64 one = {0};
        one.bc = 1;
        one.exp = BIAS64;
        a = var_num64(sub_num64(var_num64_get(a), one));
        break;
      }
      default:
        break;
      }
      deque_push_back(stack, a);
      break;
    }

    case OP_HALT:
    default:
      running = false;
      break;
    }
  }
}

void vm_error(VM *vm, const char *msg) {
  text_red(stderr);
  fprintf(stderr, "[lepvm error]");
  reset_colors(stderr);
  fprintf(stderr, " en IP 0x%04zX: %s\n", vm->ip, msg);
}

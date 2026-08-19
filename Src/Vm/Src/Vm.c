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

typedef struct {
  size_t return_ip;
  PaxoVar locals[16]; // Variables locales del marco activo
} CallFrame;

typedef struct {
  const uint8_t *bytecode;
  size_t bytecode_size;
  size_t ip;
  CallFrame frames[MAX_FRAMES];
  size_t frame_count;
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
      uint8_t var_type = vm->bytecode[vm->ip++];
      PaxoVar val = {0};
      val.type = var_type;

      switch (var_type) {
      case NUM8:
        memcpy(&val.as.number8, vm->bytecode + vm->ip, sizeof(Num8));
        vm->ip += sizeof(Num8);
        break;
      case NUM16:
        memcpy(&val.as.number16, vm->bytecode + vm->ip, sizeof(Num16));
        vm->ip += sizeof(Num16);
        break;
      case NUM32:
        memcpy(&val.as.number32, vm->bytecode + vm->ip, sizeof(Num32));
        vm->ip += sizeof(Num32);
        break;
      case NUM64:
        memcpy(&val.as.number64, vm->bytecode + vm->ip, sizeof(Num64));
        vm->ip += sizeof(Num64);
        break;
      case BOOL:
        val.as.truebool = vm->bytecode[vm->ip++];
        break;
      case TRIT:
        val.as.bit = vm->bytecode[vm->ip++];
        break;
      case CHAR:
        val.as.chara = vm->bytecode[vm->ip++];
        break;
      case POINT:
        memcpy(&val.as.puntero, vm->bytecode + vm->ip, sizeof(void *));
        vm->ip += sizeof(void *);
        break;
      default:
        break;
      }

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

      if (a.type == b.type) {
        res.type = a.type;
        switch (a.type) {
        case NUM8:
          res.as.number8 = add_num8(a.as.number8, b.as.number8);
          break;
        case NUM16:
          res.as.number16 = add_num16(a.as.number16, b.as.number16);
          break;
        case NUM32:
          res.as.number32 = add_num32(a.as.number32, b.as.number32);
          break;
        case NUM64:
          res.as.number64 = add_num64(a.as.number64, b.as.number64);
          break;
        }
      }
      deque_push_back(stack, res);
      break;
    }

    case OP_SUB: {
      PaxoVar b = deque_pop_back(stack);
      PaxoVar a = deque_pop_back(stack);
      PaxoVar res = {0};

      if (a.type == b.type) {
        res.type = a.type;
        switch (a.type) {
        case NUM8:
          res.as.number8 = sub_num8(a.as.number8, b.as.number8);
          break;
        case NUM16:
          res.as.number16 = sub_num16(a.as.number16, b.as.number16);
          break;
        case NUM32:
          res.as.number32 = sub_num32(a.as.number32, b.as.number32);
          break;
        case NUM64:
          res.as.number64 = sub_num64(a.as.number64, b.as.number64);
          break;
        }
      }
      deque_push_back(stack, res);
      break;
    }

    case OP_MUL: {
      PaxoVar b = deque_pop_back(stack);
      PaxoVar a = deque_pop_back(stack);
      PaxoVar res = {0};

      if (a.type == b.type) {
        res.type = a.type;
        switch (a.type) {
        case NUM8:
          res.as.number8 = mul_num8(a.as.number8, b.as.number8);
          break;
        case NUM16:
          res.as.number16 = mul_num16(a.as.number16, b.as.number16);
          break;
        case NUM32:
          res.as.number32 = mul_num32(a.as.number32, b.as.number32);
          break;
        case NUM64:
          res.as.number64 = mul_num64(a.as.number64, b.as.number64);
          break;
        }
      }
      deque_push_back(stack, res);
      break;
    }

    case OP_DIV: {
      PaxoVar b = deque_pop_back(stack);
      PaxoVar a = deque_pop_back(stack);
      PaxoVar res = {0};

      if (a.type == b.type) {
        res.type = a.type;
        switch (a.type) {
        case NUM8:
          res.as.number8 = div_num8(a.as.number8, b.as.number8);
          break;
        case NUM16:
          res.as.number16 = div_num16(a.as.number16, b.as.number16);
          break;
        case NUM32:
          res.as.number32 = div_num32(a.as.number32, b.as.number32);
          break;
        case NUM64:
          res.as.number64 = div_num64(a.as.number64, b.as.number64);
          break;
        }
      }
      deque_push_back(stack, res);
      break;
    }

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

      switch (val.type) {
      case NUM8:
        str = readnum8(val.as.number8, 1);
        break;
      case NUM16:
        str = readnum16(val.as.number16, 1);
        break;
      case NUM32:
        str = readnum32(val.as.number32, 1);
        break;
      case NUM64:
        str = readnum64(val.as.number64, 1);
        break;
      case BOOL:
        str = readbool(val.as.truebool);
        break;
      case CHAR:
        printf("%c\n", val.as.chara);
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
    case OP_CAST: {
      uint8_t target_type = vm->bytecode[vm->ip++];
      PaxoVar val = deque_pop_back(stack);
      PaxoVar res = {0};
      res.type = target_type;

      if (val.type == target_type) {
        deque_push_back(stack, val);
        break;
      }

      // NUM8 -> ?
      if (val.type == NUM8) {
        switch (target_type) {
        case NUM16:
          res.as.number16 = num8tonum16(val.as.number8);
          break;
        case NUM32:
          res.as.number32 = num8tonum32(val.as.number8);
          break;
        case NUM64:
          res.as.number64 = num8tonum64(val.as.number8);
          break;
        case BOOL:
          res.as.truebool = num8tobool(val.as.number8);
          break;
        case TRIT:
          res.as.bit = num8totrit(val.as.number8);
          break;
        }
      }
      // NUM16 -> ?
      else if (val.type == NUM16) {
        switch (target_type) {
        case NUM8:
          res.as.number8 = num16tonum8(val.as.number16);
          break;
        case NUM32:
          res.as.number32 = num16tonum32(val.as.number16);
          break;
        case NUM64:
          res.as.number64 = num16tonum64(val.as.number16);
          break;
        case BOOL:
          res.as.truebool = num16tobool(val.as.number16);
          break;
        case TRIT:
          res.as.bit = num16totrit(val.as.number16);
          break;
        }
      }
      // NUM32 -> ?
      else if (val.type == NUM32) {
        switch (target_type) {
        case NUM8:
          res.as.number8 = num32tonum8(val.as.number32);
          break;
        case NUM16:
          res.as.number16 = num32tonum16(val.as.number32);
          break;
        case NUM64:
          res.as.number64 = num32tonum64(val.as.number32);
          break;
        case BOOL:
          res.as.truebool = num32tobool(val.as.number32);
          break;
        case TRIT:
          res.as.bit = num32totrit(val.as.number32);
          break;
        }
      }
      // NUM64 -> ?
      else if (val.type == NUM64) {
        switch (target_type) {
        case NUM8:
          res.as.number8 = num64tonum8(val.as.number64);
          break;
        case NUM16:
          res.as.number16 = num64tonum16(val.as.number64);
          break;
        case NUM32:
          res.as.number32 = num64tonum32(val.as.number64);
          break;
        case BOOL:
          res.as.truebool = num64tobool(val.as.number64);
          break;
        case TRIT:
          res.as.bit = num64totrit(val.as.number64);
          break;
        }
      }
      // BOOL -> ?
      else if (val.type == BOOL) {
        switch (target_type) {
        case NUM8:
          res.as.number8 = booltonum8(val.as.truebool);
          break;
        case NUM16:
          res.as.number16 = booltonum16(val.as.truebool);
          break;
        case NUM32:
          res.as.number32 = booltonum32(val.as.truebool);
          break;
        case NUM64:
          res.as.number64 = booltonum64(val.as.truebool);
          break;
        case TRIT:
          res.as.bit = booltotrit(val.as.truebool);
          break;
        }
      }
      // TRIT -> ?
      else if (val.type == TRIT) {
        switch (target_type) {
        case NUM8:
          res.as.number8 = trittonum8(val.as.bit);
          break;
        case NUM16:
          res.as.number16 = trittonum16(val.as.bit);
          break;
        case NUM32:
          res.as.number32 = trittonum32(val.as.bit);
          break;
        case NUM64:
          res.as.number64 = trittonum64(val.as.bit);
          break;
        case BOOL:
          res.as.truebool = trittobool(val.as.bit);
          break;
        }
      }
      else if (val.type == CHAR && target_type == NUM8) {
        Num8 conv = {0};
        conv.bc = val.as.chara;
        res.as.number8 = conv;
      }

      deque_push_back(stack, res);
      break;
    }

    case OP_CALL: {
      uint16_t target_ip = read_u16(vm);
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
      if (result.type != 0xFF)
        deque_push_back(stack, result);
      break;
    }

    case OP_JUMP_IF_TRUE: {
      int16_t offset = read_i16(vm);
      PaxoVar condition = deque_pop_back(stack);

      bool is_true = false;
      if (condition.type == BOOL)
        is_true = condition.as.truebool;
      else if (condition.type == TRIT)
        is_true = (condition.as.bit == 1);

      if (is_true) {
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

#define CMP_OP_CASES(chose)                                                   \
  case NUM8: {                                                                \
    int c = cmp_num8(a.as.number8, b.as.number8);                            \
    res.as.truebool = chose(c);                                              \
    break;                                                                    \
  }                                                                           \
  case NUM16: {                                                               \
    int c = cmp_num16(a.as.number16, b.as.number16);                          \
    res.as.truebool = chose(c);                                              \
    break;                                                                    \
  }                                                                           \
  case NUM32: {                                                               \
    int c = cmp_num32(a.as.number32, b.as.number32);                          \
    res.as.truebool = chose(c);                                              \
    break;                                                                    \
  }                                                                           \
  case NUM64: {                                                               \
    int c = cmp_num64(a.as.number64, b.as.number64);                          \
    res.as.truebool = chose(c);                                              \
    break;                                                                    \
  }

    case OP_EQ: {
      PaxoVar b = deque_pop_back(stack);
      PaxoVar a = deque_pop_back(stack);
      PaxoVar res = {0};
      res.type = BOOL;
      if (a.type != b.type) {
        res.as.truebool = false;
      } else {
        switch (a.type) {
          CMP_OP_CASES(c_eq)
        case BOOL:
          res.as.truebool = (a.as.truebool == b.as.truebool);
          break;
        case TRIT:
          res.as.truebool = (a.as.bit == b.as.bit);
          break;
        case CHAR:
          res.as.truebool = (a.as.chara == b.as.chara);
          break;
        case POINT:
          res.as.truebool = (a.as.puntero == b.as.puntero);
          break;
        default:
          res.as.truebool = false;
          break;
        }
      }
      deque_push_back(stack, res);
      break;
    }

    case OP_NEQ: {
      PaxoVar b = deque_pop_back(stack);
      PaxoVar a = deque_pop_back(stack);
      PaxoVar res = {0};
      res.type = BOOL;
      if (a.type != b.type) {
        res.as.truebool = true;
      } else {
        switch (a.type) {
          CMP_OP_CASES(c_neq)
        case BOOL:
          res.as.truebool = (a.as.truebool != b.as.truebool);
          break;
        case TRIT:
          res.as.truebool = (a.as.bit != b.as.bit);
          break;
        case CHAR:
          res.as.truebool = (a.as.chara != b.as.chara);
          break;
        case POINT:
          res.as.truebool = (a.as.puntero != b.as.puntero);
          break;
        default:
          res.as.truebool = true;
          break;
        }
      }
      deque_push_back(stack, res);
      break;
    }

    case OP_LT: {
      PaxoVar b = deque_pop_back(stack);
      PaxoVar a = deque_pop_back(stack);
      PaxoVar res = {0};
      res.type = BOOL;
      if (a.type != b.type) {
        res.as.truebool = false;
      } else {
        switch (a.type) {
          CMP_OP_CASES(c_lt)
        case CHAR:
          res.as.truebool = (a.as.chara < b.as.chara);
          break;
        default:
          res.as.truebool = false;
          break;
        }
      }
      deque_push_back(stack, res);
      break;
    }

    case OP_GT: {
      PaxoVar b = deque_pop_back(stack);
      PaxoVar a = deque_pop_back(stack);
      PaxoVar res = {0};
      res.type = BOOL;
      if (a.type != b.type) {
        res.as.truebool = false;
      } else {
        switch (a.type) {
          CMP_OP_CASES(c_gt)
        case CHAR:
          res.as.truebool = (a.as.chara > b.as.chara);
          break;
        default:
          res.as.truebool = false;
          break;
        }
      }
      deque_push_back(stack, res);
      break;
    }

    case OP_LTE: {
      PaxoVar b = deque_pop_back(stack);
      PaxoVar a = deque_pop_back(stack);
      PaxoVar res = {0};
      res.type = BOOL;
      if (a.type != b.type) {
        res.as.truebool = false;
      } else {
        switch (a.type) {
          CMP_OP_CASES(c_lte)
        case CHAR:
          res.as.truebool = (a.as.chara <= b.as.chara);
          break;
        default:
          res.as.truebool = false;
          break;
        }
      }
      deque_push_back(stack, res);
      break;
    }

    case OP_GTE: {
      PaxoVar b = deque_pop_back(stack);
      PaxoVar a = deque_pop_back(stack);
      PaxoVar res = {0};
      res.type = BOOL;
      if (a.type != b.type) {
        res.as.truebool = false;
      } else {
        switch (a.type) {
          CMP_OP_CASES(c_gte)
        case CHAR:
          res.as.truebool = (a.as.chara >= b.as.chara);
          break;
        default:
          res.as.truebool = false;
          break;
        }
      }
      deque_push_back(stack, res);
      break;
    }

#undef CMP_OP_CASES
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
      PaxoVar res = {0};
      res.type = BOOL;
      bool va = false, vb = false;
      if (a.type == BOOL) va = a.as.truebool;
      else if (a.type == TRIT) va = (a.as.bit == 1);
      if (b.type == BOOL) vb = b.as.truebool;
      else if (b.type == TRIT) vb = (b.as.bit == 1);
      res.as.truebool = va && vb;
      deque_push_back(stack, res);
      break;
    }

    case OP_OR: {
      PaxoVar b = deque_pop_back(stack);
      PaxoVar a = deque_pop_back(stack);
      PaxoVar res = {0};
      res.type = BOOL;
      bool va = false, vb = false;
      if (a.type == BOOL) va = a.as.truebool;
      else if (a.type == TRIT) va = (a.as.bit == 1);
      if (b.type == BOOL) vb = b.as.truebool;
      else if (b.type == TRIT) vb = (b.as.bit == 1);
      res.as.truebool = va || vb;
      deque_push_back(stack, res);
      break;
    }

    case OP_NOT: {
      PaxoVar a = deque_pop_back(stack);
      PaxoVar res = {0};
      res.type = BOOL;
      if (a.type == BOOL)
        res.as.truebool = !a.as.truebool;
      else if (a.type == TRIT)
        res.as.truebool = (a.as.bit == 0);
      else
        res.as.truebool = true;
      deque_push_back(stack, res);
      break;
    }

    // ==========================================
    // BITWISE (BOOL / TRIT / CHAR)
    // ==========================================
    case OP_BIT_AND: {
      PaxoVar b = deque_pop_back(stack);
      PaxoVar a = deque_pop_back(stack);
      PaxoVar res = {0};
      res.type = BOOL;
      if (a.type == BOOL && b.type == BOOL)
        res.as.truebool = a.as.truebool & b.as.truebool;
      else if (a.type == TRIT && b.type == TRIT)
        res.as.bit = a.as.bit & b.as.bit;
      deque_push_back(stack, res);
      break;
    }

    case OP_BIT_OR: {
      PaxoVar b = deque_pop_back(stack);
      PaxoVar a = deque_pop_back(stack);
      PaxoVar res = {0};
      res.type = BOOL;
      if (a.type == BOOL && b.type == BOOL)
        res.as.truebool = a.as.truebool | b.as.truebool;
      else if (a.type == TRIT && b.type == TRIT)
        res.as.bit = a.as.bit | b.as.bit;
      deque_push_back(stack, res);
      break;
    }

    case OP_BIT_NOT: {
      PaxoVar a = deque_pop_back(stack);
      PaxoVar res = {0};
      if (a.type == BOOL) {
        res.type = BOOL;
        res.as.truebool = !a.as.truebool;
      } else if (a.type == TRIT) {
        res.type = TRIT;
        res.as.bit = ~a.as.bit;
      } else if (a.type == CHAR) {
        res.type = CHAR;
        res.as.chara = ~a.as.chara;
      }
      deque_push_back(stack, res);
      break;
    }

    case OP_BIT_XOR: {
      PaxoVar b = deque_pop_back(stack);
      PaxoVar a = deque_pop_back(stack);
      PaxoVar res = {0};
      res.type = BOOL;
      if (a.type == BOOL && b.type == BOOL)
        res.as.truebool = a.as.truebool ^ b.as.truebool;
      else if (a.type == TRIT && b.type == TRIT)
        res.as.bit = a.as.bit ^ b.as.bit;
      deque_push_back(stack, res);
      break;
    }

    case OP_BIT_SHL: {
      PaxoVar b = deque_pop_back(stack);
      PaxoVar a = deque_pop_back(stack);
      PaxoVar res = {0};
      if (a.type == CHAR && b.type == CHAR) {
        res.type = CHAR;
        res.as.chara = a.as.chara << b.as.chara;
      } else if (a.type == NUM8 && b.type == NUM8) {
        res.type = NUM8;
        res.as.number8.bc = a.as.number8.bc << b.as.number8.bc;
      } else if (a.type == NUM16 && b.type == NUM16) {
        res.type = NUM16;
        res.as.number16.bc = a.as.number16.bc << b.as.number16.bc;
      }
      deque_push_back(stack, res);
      break;
    }

    case OP_BIT_SHR: {
      PaxoVar b = deque_pop_back(stack);
      PaxoVar a = deque_pop_back(stack);
      PaxoVar res = {0};
      if (a.type == CHAR && b.type == CHAR) {
        res.type = CHAR;
        res.as.chara = a.as.chara >> b.as.chara;
      } else if (a.type == NUM8 && b.type == NUM8) {
        res.type = NUM8;
        res.as.number8.bc = a.as.number8.bc >> b.as.number8.bc;
      } else if (a.type == NUM16 && b.type == NUM16) {
        res.type = NUM16;
        res.as.number16.bc = a.as.number16.bc >> b.as.number16.bc;
      }
      deque_push_back(stack, res);
      break;
    }

    // ==========================================
    // INC / DEC
    // ==========================================
    case OP_INC: {
      PaxoVar a = deque_pop_back(stack);
      PaxoVar one = {0};
      one.type = a.type;
      switch (a.type) {
      case NUM8:
        one.as.number8.bc = 1;
        a.as.number8 = add_num8(a.as.number8, one.as.number8);
        break;
      case NUM16:
        one.as.number16.bc = 1;
        a.as.number16 = add_num16(a.as.number16, one.as.number16);
        break;
      case NUM32:
        one.as.number32.bc = 1;
        a.as.number32 = add_num32(a.as.number32, one.as.number32);
        break;
      case NUM64:
        one.as.number64.bc = 1;
        a.as.number64 = add_num64(a.as.number64, one.as.number64);
        break;
      }
      deque_push_back(stack, a);
      break;
    }

    case OP_DEC: {
      PaxoVar a = deque_pop_back(stack);
      PaxoVar one = {0};
      one.type = a.type;
      switch (a.type) {
      case NUM8:
        one.as.number8.bc = 1;
        a.as.number8 = sub_num8(a.as.number8, one.as.number8);
        break;
      case NUM16:
        one.as.number16.bc = 1;
        a.as.number16 = sub_num16(a.as.number16, one.as.number16);
        break;
      case NUM32:
        one.as.number32.bc = 1;
        a.as.number32 = sub_num32(a.as.number32, one.as.number32);
        break;
      case NUM64:
        one.as.number64.bc = 1;
        a.as.number64 = sub_num64(a.as.number64, one.as.number64);
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
  fprintf(stderr, "[PAXO EXEC ERROR]");
  reset_colors(stderr);
  fprintf(stderr, " en IP 0x%04zX: %s\n", vm->ip, msg);
}
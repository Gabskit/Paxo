/* Light Environment Processing VM (LEP-VM) */
#pragma once
#include "Calc.c"
#include "Deque.c"
#include "Typecast_and_read.c"
#include "termcolor-c.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

typedef struct {
  const uint8_t *bytecode;
  size_t ip;
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
  OP_HALT,
  OP_CALL,
  OP_CALL_NATIVE
} PaxoOpcode;

void vm_init(VM *vm, const uint8_t *bytecode) {
  vm->bytecode = bytecode;
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

    case OP_HALT:
    default:
      running = false;
      break;
    }
  }
}

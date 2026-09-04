#define LEP_IMPLEMENTATION
#include "lep.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

static size_t pos = 0;
static uint8_t bc[8192];
static int tests_pass = 0;
static int tests_fail = 0;

static void emit8(uint8_t v) { bc[pos++] = v; }
static void emit16(uint16_t v) { memcpy(bc + pos, &v, 2); pos += 2; }
static void emit_i16(int16_t v) { memcpy(bc + pos, &v, 2); pos += 2; }
static void emit_op(uint8_t op) { emit8(op); }

static void emit_push_num8(uint8_t val) {
  emit_op(OP_PUSH);
  emit8(NUM8);
  Num8 n = {0};
  n.bc = val;
  memcpy(bc + pos, &n, sizeof(Num8));
  pos += sizeof(Num8);
}

static void emit_push_num16(uint16_t val) {
  emit_op(OP_PUSH);
  emit8(NUM16);
  Num16 n = {0};
  n.bc = val;
  memcpy(bc + pos, &n, sizeof(Num16));
  pos += sizeof(Num16);
}

static void emit_push_num32(uint32_t val) {
  emit_op(OP_PUSH);
  emit8(NUM32);
  Num32 n = {0};
  n.bc = val;
  memcpy(bc + pos, &n, sizeof(Num32));
  pos += sizeof(Num32);
}

static void emit_push_num64(uint64_t val) {
  emit_op(OP_PUSH);
  emit8(NUM64);
  Num64 n = {0};
  n.bc = val;
  memcpy(bc + pos, &n, sizeof(Num64));
  pos += sizeof(Num64);
}

static void emit_push_bool(bool val) {
  emit_op(OP_PUSH);
  emit8(BOOL);
  emit8(val ? 1 : 0);
}

static void emit_push_char(char c) {
  emit_op(OP_PUSH);
  emit8(CHAR);
  emit8((uint8_t)c);
}

static void emit_push_trit(uint8_t val) {
  emit_op(OP_PUSH);
  emit8(TRIT);
  emit8(val);
}

static void reset(void) { pos = 0; memset(bc, 0, sizeof(bc)); }

static PaxoVar heap_pop_top_for_test(Smart_heap *stack) {
  if (stack->amount == 0)
    return LEP_ZERO;
  stack->amount--;
  PaxoVar *slot = heap_read(stack, stack->amount);
  return slot ? *slot : LEP_ZERO;
}

#define RUN_AND_POP(top) do { \
  VM vm = {0}; vm_init(&vm, bc); \
  Smart_heap stack = create_heap(64); \
  PaxoVar globals[256] = {0}; \
  vm_run(&vm, &stack, globals); \
  top = heap_pop_top_for_test(&stack); \
  free_heap(&stack); \
} while(0)

#define RUN_STACK_SIZE(sz) do { \
  VM vm = {0}; vm_init(&vm, bc); \
  Smart_heap stack = create_heap(64); \
  PaxoVar globals[256] = {0}; \
  vm_run(&vm, &stack, globals); \
  sz = stack.amount; \
  free_heap(&stack); \
} while(0)

#define ASSERT_MSG(cond, msg) do { \
  if (cond) { tests_pass++; printf("  PASS %s\n", msg); } \
  else { tests_fail++; printf("  FAIL %s\n", msg); } \
} while(0)

#define ASSERT_TYPE(top, expected_type, msg) \
  ASSERT_MSG((top).type == (expected_type), msg)

#define ASSERT_NUM8_BC(top, expected_bc, msg) \
  ASSERT_MSG((top).type == NUM8 && (top).as.number8.bc == (expected_bc), msg)

#define ASSERT_BOOL(top, expected_val, msg) \
  ASSERT_MSG((top).type == BOOL && (top).as.truebool == (expected_val), msg)

// ==========================================
// Aritmetica NUM8
// ==========================================
static void test_add_num8(void) {
  printf("\n--- ADD NUM8 ---\n");
  reset();
  emit_push_num8(3); emit_push_num8(5); emit_op(OP_ADD); emit_op(OP_HALT);
  PaxoVar top; RUN_AND_POP(top);
  ASSERT_NUM8_BC(top, 8, "3 + 5 = 8");

  reset();
  emit_push_num8(0); emit_push_num8(7); emit_op(OP_ADD); emit_op(OP_HALT);
  RUN_AND_POP(top);
  ASSERT_NUM8_BC(top, 7, "0 + 7 = 7");

  reset();
  emit_push_num8(12); emit_push_num8(3); emit_op(OP_ADD); emit_op(OP_HALT);
  RUN_AND_POP(top);
  ASSERT_MSG(top.type == NUM8, "12 + 3 type is NUM8");
}

static void test_sub_num8(void) {
  printf("\n--- SUB NUM8 ---\n");
  reset();
  emit_push_num8(10); emit_push_num8(3); emit_op(OP_SUB); emit_op(OP_HALT);
  PaxoVar top; RUN_AND_POP(top);
  ASSERT_NUM8_BC(top, 7, "10 - 3 = 7");

  reset();
  emit_push_num8(5); emit_push_num8(5); emit_op(OP_SUB); emit_op(OP_HALT);
  RUN_AND_POP(top);
  ASSERT_MSG(top.type == NUM8 && top.as.number8.bc == 0, "5 - 5 = 0");
}

static void test_mul_num8(void) {
  printf("\n--- MUL NUM8 ---\n");
  reset();
  emit_push_num8(4); emit_push_num8(5); emit_op(OP_MUL); emit_op(OP_HALT);
  PaxoVar top; RUN_AND_POP(top);
  ASSERT_MSG(top.type == NUM8, "4 * 5 type is NUM8");

  reset();
  emit_push_num8(3); emit_push_num8(0); emit_op(OP_MUL); emit_op(OP_HALT);
  RUN_AND_POP(top);
  ASSERT_NUM8_BC(top, 0, "3 * 0 = 0");
}

static void test_div_num8(void) {
  printf("\n--- DIV NUM8 ---\n");
  reset();
  emit_push_num8(10); emit_push_num8(2); emit_op(OP_DIV); emit_op(OP_HALT);
  PaxoVar top; RUN_AND_POP(top);
  ASSERT_MSG(top.type == NUM8, "10 / 2 type is NUM8");

  reset();
  emit_push_num8(0); emit_push_num8(5); emit_op(OP_DIV); emit_op(OP_HALT);
  RUN_AND_POP(top);
  ASSERT_NUM8_BC(top, 0, "0 / 5 = 0");
}

// ==========================================
// Aritmetica NUM16
// ==========================================
static void test_add_num16(void) {
  printf("\n--- ADD NUM16 ---\n");
  reset();
  emit_push_num16(100); emit_push_num16(200); emit_op(OP_ADD); emit_op(OP_HALT);
  PaxoVar top; RUN_AND_POP(top);
  ASSERT_TYPE(top, NUM16, "100 + 200 type is NUM16");
}

static void test_sub_num16(void) {
  printf("\n--- SUB NUM16 ---\n");
  reset();
  emit_push_num16(500); emit_push_num16(200); emit_op(OP_SUB); emit_op(OP_HALT);
  PaxoVar top; RUN_AND_POP(top);
  ASSERT_TYPE(top, NUM16, "500 - 200 type is NUM16");
}

static void test_mul_num16(void) {
  printf("\n--- MUL NUM16 ---\n");
  reset();
  emit_push_num16(50); emit_push_num16(10); emit_op(OP_MUL); emit_op(OP_HALT);
  PaxoVar top; RUN_AND_POP(top);
  ASSERT_TYPE(top, NUM16, "50 * 10 type is NUM16");
}

static void test_div_num16(void) {
  printf("\n--- DIV NUM16 ---\n");
  reset();
  emit_push_num16(1000); emit_push_num16(10); emit_op(OP_DIV); emit_op(OP_HALT);
  PaxoVar top; RUN_AND_POP(top);
  ASSERT_TYPE(top, NUM16, "1000 / 10 type is NUM16");
}

// ==========================================
// Aritmetica NUM32
// ==========================================
static void test_add_num32(void) {
  printf("\n--- ADD NUM32 ---\n");
  reset();
  emit_push_num32(100000); emit_push_num32(200000); emit_op(OP_ADD); emit_op(OP_HALT);
  PaxoVar top; RUN_AND_POP(top);
  ASSERT_TYPE(top, NUM32, "100000 + 200000 type is NUM32");
}

// ==========================================
// Comparaciones
// ==========================================
static void test_eq(void) {
  printf("\n--- EQ ---\n");
  reset();
  emit_push_num8(7); emit_push_num8(7); emit_op(OP_EQ); emit_op(OP_HALT);
  PaxoVar top; RUN_AND_POP(top);
  ASSERT_BOOL(top, true, "7 == 7 -> true");

  reset();
  emit_push_num8(7); emit_push_num8(3); emit_op(OP_EQ); emit_op(OP_HALT);
  RUN_AND_POP(top);
  ASSERT_BOOL(top, false, "7 == 3 -> false");
}

static void test_neq(void) {
  printf("\n--- NEQ ---\n");
  reset();
  emit_push_num8(5); emit_push_num8(3); emit_op(OP_NEQ); emit_op(OP_HALT);
  PaxoVar top; RUN_AND_POP(top);
  ASSERT_BOOL(top, true, "5 != 3 -> true");

  reset();
  emit_push_num8(5); emit_push_num8(5); emit_op(OP_NEQ); emit_op(OP_HALT);
  RUN_AND_POP(top);
  ASSERT_BOOL(top, false, "5 != 5 -> false");
}

static void test_lt(void) {
  printf("\n--- LT ---\n");
  reset();
  emit_push_num8(3); emit_push_num8(5); emit_op(OP_LT); emit_op(OP_HALT);
  PaxoVar top; RUN_AND_POP(top);
  ASSERT_BOOL(top, true, "3 < 5 -> true");

  reset();
  emit_push_num8(5); emit_push_num8(3); emit_op(OP_LT); emit_op(OP_HALT);
  RUN_AND_POP(top);
  ASSERT_BOOL(top, false, "5 < 3 -> false");

  reset();
  emit_push_num8(5); emit_push_num8(5); emit_op(OP_LT); emit_op(OP_HALT);
  RUN_AND_POP(top);
  ASSERT_BOOL(top, false, "5 < 5 -> false");
}

static void test_gt(void) {
  printf("\n--- GT ---\n");
  reset();
  emit_push_num8(5); emit_push_num8(3); emit_op(OP_GT); emit_op(OP_HALT);
  PaxoVar top; RUN_AND_POP(top);
  ASSERT_BOOL(top, true, "5 > 3 -> true");

  reset();
  emit_push_num8(3); emit_push_num8(5); emit_op(OP_GT); emit_op(OP_HALT);
  RUN_AND_POP(top);
  ASSERT_BOOL(top, false, "3 > 5 -> false");
}

static void test_lte(void) {
  printf("\n--- LTE ---\n");
  reset();
  emit_push_num8(5); emit_push_num8(5); emit_op(OP_LTE); emit_op(OP_HALT);
  PaxoVar top; RUN_AND_POP(top);
  ASSERT_BOOL(top, true, "5 <= 5 -> true");

  reset();
  emit_push_num8(5); emit_push_num8(3); emit_op(OP_LTE); emit_op(OP_HALT);
  RUN_AND_POP(top);
  ASSERT_BOOL(top, false, "5 <= 3 -> false");
}

static void test_gte(void) {
  printf("\n--- GTE ---\n");
  reset();
  emit_push_num8(5); emit_push_num8(5); emit_op(OP_GTE); emit_op(OP_HALT);
  PaxoVar top; RUN_AND_POP(top);
  ASSERT_BOOL(top, true, "5 >= 5 -> true");

  reset();
  emit_push_num8(3); emit_push_num8(5); emit_op(OP_GTE); emit_op(OP_HALT);
  RUN_AND_POP(top);
  ASSERT_BOOL(top, false, "3 >= 5 -> false");
}

static void test_cmp_neq_different_types(void) {
  printf("\n--- CMP DIFFERENT TYPES ---\n");
  reset();
  emit_push_num8(5); emit_push_num16(5); emit_op(OP_EQ); emit_op(OP_HALT);
  PaxoVar top; RUN_AND_POP(top);
  ASSERT_BOOL(top, false, "NUM8(5) == NUM16(5) -> false (type mismatch)");
}

// ==========================================
// Logicos
// ==========================================
static void test_and(void) {
  printf("\n--- AND ---\n");
  reset();
  emit_push_bool(true); emit_push_bool(true); emit_op(OP_AND); emit_op(OP_HALT);
  PaxoVar top; RUN_AND_POP(top);
  ASSERT_BOOL(top, true, "true & true -> true");

  reset();
  emit_push_bool(true); emit_push_bool(false); emit_op(OP_AND); emit_op(OP_HALT);
  RUN_AND_POP(top);
  ASSERT_BOOL(top, false, "true & false -> false");

  reset();
  emit_push_bool(false); emit_push_bool(false); emit_op(OP_AND); emit_op(OP_HALT);
  RUN_AND_POP(top);
  ASSERT_BOOL(top, false, "false & false -> false");
}

static void test_or(void) {
  printf("\n--- OR ---\n");
  reset();
  emit_push_bool(false); emit_push_bool(true); emit_op(OP_OR); emit_op(OP_HALT);
  PaxoVar top; RUN_AND_POP(top);
  ASSERT_BOOL(top, true, "false | true -> true");

  reset();
  emit_push_bool(false); emit_push_bool(false); emit_op(OP_OR); emit_op(OP_HALT);
  RUN_AND_POP(top);
  ASSERT_BOOL(top, false, "false | false -> false");
}

static void test_not(void) {
  printf("\n--- NOT ---\n");
  reset();
  emit_push_bool(true); emit_op(OP_NOT); emit_op(OP_HALT);
  PaxoVar top; RUN_AND_POP(top);
  ASSERT_BOOL(top, false, "!true -> false");

  reset();
  emit_push_bool(false); emit_op(OP_NOT); emit_op(OP_HALT);
  RUN_AND_POP(top);
  ASSERT_BOOL(top, true, "!false -> true");
}

static void test_nested_logic(void) {
  printf("\n--- NESTED LOGIC ---\n");
  reset();
  emit_push_bool(true); emit_push_bool(false); emit_op(OP_AND);
  emit_push_bool(true); emit_op(OP_OR); emit_op(OP_HALT);
  PaxoVar top; RUN_AND_POP(top);
  ASSERT_BOOL(top, true, "(true & false) | true -> true");
}

// ==========================================
// Bitwise
// ==========================================
static void test_bit_and(void) {
  printf("\n--- BIT_AND ---\n");
  reset();
  emit_push_bool(true); emit_push_bool(false); emit_op(OP_BIT_AND); emit_op(OP_HALT);
  PaxoVar top; RUN_AND_POP(top);
  ASSERT_BOOL(top, false, "true & false -> false (bit)");

  reset();
  emit_push_bool(true); emit_push_bool(true); emit_op(OP_BIT_AND); emit_op(OP_HALT);
  RUN_AND_POP(top);
  ASSERT_BOOL(top, true, "true & true -> true (bit)");
}

static void test_bit_or(void) {
  printf("\n--- BIT_OR ---\n");
  reset();
  emit_push_bool(false); emit_push_bool(true); emit_op(OP_BIT_OR); emit_op(OP_HALT);
  PaxoVar top; RUN_AND_POP(top);
  ASSERT_BOOL(top, true, "false | true -> true (bit)");
}

static void test_bit_xor(void) {
  printf("\n--- BIT_XOR ---\n");
  reset();
  emit_push_bool(true); emit_push_bool(false); emit_op(OP_BIT_XOR); emit_op(OP_HALT);
  PaxoVar top; RUN_AND_POP(top);
  ASSERT_BOOL(top, true, "true ^ false -> true (bit)");

  reset();
  emit_push_bool(true); emit_push_bool(true); emit_op(OP_BIT_XOR); emit_op(OP_HALT);
  RUN_AND_POP(top);
  ASSERT_BOOL(top, false, "true ^ true -> false (bit)");
}

static void test_bit_not(void) {
  printf("\n--- BIT_NOT ---\n");
  reset();
  emit_push_bool(true); emit_op(OP_BIT_NOT); emit_op(OP_HALT);
  PaxoVar top; RUN_AND_POP(top);
  ASSERT_BOOL(top, false, "~true -> false (bit)");

  reset();
  emit_push_bool(false); emit_op(OP_BIT_NOT); emit_op(OP_HALT);
  RUN_AND_POP(top);
  ASSERT_BOOL(top, true, "~false -> true (bit)");
}

static void test_bit_shl(void) {
  printf("\n--- BIT_SHL ---\n");
  reset();
  emit_push_num8(1); emit_push_num8(1); emit_op(OP_BIT_SHL); emit_op(OP_HALT);
  PaxoVar top; RUN_AND_POP(top);
  ASSERT_NUM8_BC(top, 2, "1 << 1 -> 2");

  reset();
  emit_push_num8(3); emit_push_num8(2); emit_op(OP_BIT_SHL); emit_op(OP_HALT);
  RUN_AND_POP(top);
  ASSERT_NUM8_BC(top, 12, "3 << 2 -> 12");
}

static void test_bit_shr(void) {
  printf("\n--- BIT_SHR ---\n");
  reset();
  emit_push_num8(4); emit_push_num8(1); emit_op(OP_BIT_SHR); emit_op(OP_HALT);
  PaxoVar top; RUN_AND_POP(top);
  ASSERT_NUM8_BC(top, 2, "4 >> 1 -> 2");

  reset();
  emit_push_num8(12); emit_push_num8(2); emit_op(OP_BIT_SHR); emit_op(OP_HALT);
  RUN_AND_POP(top);
  ASSERT_NUM8_BC(top, 3, "12 >> 2 -> 3");
}

// ==========================================
// INC / DEC
// ==========================================
static void test_inc(void) {
  printf("\n--- INC ---\n");
  reset();
  emit_push_num8(5); emit_op(OP_INC); emit_op(OP_HALT);
  PaxoVar top; RUN_AND_POP(top);
  ASSERT_NUM8_BC(top, 6, "inc 5 -> 6");

  reset();
  emit_push_num8(0); emit_op(OP_INC); emit_op(OP_HALT);
  RUN_AND_POP(top);
  ASSERT_NUM8_BC(top, 1, "inc 0 -> 1");
}

static void test_dec(void) {
  printf("\n--- DEC ---\n");
  reset();
  emit_push_num8(5); emit_op(OP_DEC); emit_op(OP_HALT);
  PaxoVar top; RUN_AND_POP(top);
  ASSERT_NUM8_BC(top, 4, "dec 5 -> 4");

  reset();
  emit_push_num8(1); emit_op(OP_DEC); emit_op(OP_HALT);
  RUN_AND_POP(top);
  ASSERT_NUM8_BC(top, 0, "dec 1 -> 0");
}

static void test_inc_dec_chain(void) {
  printf("\n--- INC/DEC CHAIN ---\n");
  reset();
  emit_push_num8(0);
  emit_op(OP_INC); emit_op(OP_INC); emit_op(OP_INC);
  emit_op(OP_INC); emit_op(OP_INC);
  emit_op(OP_HALT);
  PaxoVar top; RUN_AND_POP(top);
  ASSERT_NUM8_BC(top, 5, "inc x5: 0 -> 5");

  reset();
  emit_push_num8(10);
  emit_op(OP_DEC); emit_op(OP_DEC); emit_op(OP_DEC);
  emit_op(OP_HALT);
  RUN_AND_POP(top);
  ASSERT_NUM8_BC(top, 7, "dec x3: 10 -> 7");
}

static void test_inc_num16(void) {
  printf("\n--- INC NUM16 ---\n");
  reset();
  emit_push_num16(255); emit_op(OP_INC); emit_op(OP_HALT);
  PaxoVar top; RUN_AND_POP(top);
  ASSERT_TYPE(top, NUM16, "inc NUM16 type");
}

// ==========================================
// Variables (LOAD / STORE)
// ==========================================
static void test_load_store_var(void) {
  printf("\n--- LOAD/STORE VAR ---\n");
  reset();
  emit_push_num8(7); emit_op(OP_STORE_VAR); emit16(0);
  emit_op(OP_LOAD_VAR); emit16(0);
  emit_op(OP_HALT);
  PaxoVar top; RUN_AND_POP(top);
  ASSERT_NUM8_BC(top, 7, "store 7, load -> 7");

  reset();
  emit_push_num8(3); emit_op(OP_STORE_VAR); emit16(5);
  emit_push_num8(5); emit_op(OP_STORE_VAR); emit16(6);
  emit_op(OP_LOAD_VAR); emit16(5);
  emit_op(OP_LOAD_VAR); emit16(6);
  emit_op(OP_ADD); emit_op(OP_HALT);
  RUN_AND_POP(top);
  ASSERT_MSG(top.type == NUM8, "a=3, b=5, a+b type is NUM8");
}

static void test_var_overwrite(void) {
  printf("\n--- VAR OVERWRITE ---\n");
  reset();
  emit_push_num8(3); emit_op(OP_STORE_VAR); emit16(0);
  emit_push_num8(7); emit_op(OP_STORE_VAR); emit16(0);
  emit_op(OP_LOAD_VAR); emit16(0);
  emit_op(OP_HALT);
  PaxoVar top; RUN_AND_POP(top);
  ASSERT_NUM8_BC(top, 7, "overwrite 3 -> 7");
}

// ==========================================
// POP
// ==========================================
static void test_pop(void) {
  printf("\n--- POP ---\n");
  reset();
  emit_push_num8(7); emit_push_num8(3); emit_op(OP_POP); emit_op(OP_HALT);
  PaxoVar top; RUN_AND_POP(top);
  ASSERT_NUM8_BC(top, 7, "push 7, push 3, pop -> top is 7");
}

// ==========================================
// JUMPS
// ==========================================
static void test_jump(void) {
  printf("\n--- JUMP ---\n");
  reset();
  emit_push_num8(7); emit_op(OP_JUMP); emit_i16(1);
  emit_op(OP_POP); emit_op(OP_HALT);
  PaxoVar top; RUN_AND_POP(top);
  ASSERT_NUM8_BC(top, 7, "JUMP skips POP -> 7 preserved");
}

static void test_jump_if_false(void) {
  printf("\n--- JUMP_IF_FALSE ---\n");
  reset();
  emit_push_bool(false); emit_op(OP_JUMP_IF_FALSE); emit_i16(3);
  emit_push_num8(7); emit_op(OP_HALT);
  size_t sz; RUN_STACK_SIZE(sz);
  ASSERT_MSG(sz == 0, "JIF(false): skip PUSH 7 -> empty stack");

  reset();
  emit_push_bool(true); emit_op(OP_JUMP_IF_FALSE); emit_i16(3);
  emit_push_num8(7); emit_op(OP_HALT);
  PaxoVar top; RUN_AND_POP(top);
  ASSERT_NUM8_BC(top, 7, "JIF(true): no skip -> 7 on stack");
}

static void test_jump_if_true(void) {
  printf("\n--- JUMP_IF_TRUE ---\n");
  reset();
  emit_push_bool(true); emit_op(OP_JUMP_IF_TRUE); emit_i16(3);
  emit_push_num8(7); emit_op(OP_HALT);
  size_t sz; RUN_STACK_SIZE(sz);
  ASSERT_MSG(sz == 0, "JIT(true): skip PUSH 7 -> empty stack");

  reset();
  emit_push_bool(false); emit_op(OP_JUMP_IF_TRUE); emit_i16(3);
  emit_push_num8(7); emit_op(OP_HALT);
  PaxoVar top; RUN_AND_POP(top);
  ASSERT_NUM8_BC(top, 7, "JIT(false): no skip -> 7 on stack");
}

// ==========================================
// CHAR
// ==========================================
static void test_char_cmp(void) {
  printf("\n--- CHAR CMP ---\n");
  reset();
  emit_push_char('a'); emit_push_char('z'); emit_op(OP_LT); emit_op(OP_HALT);
  PaxoVar top; RUN_AND_POP(top);
  ASSERT_BOOL(top, true, "'a' < 'z' -> true");

  reset();
  emit_push_char('z'); emit_push_char('a'); emit_op(OP_GT); emit_op(OP_HALT);
  RUN_AND_POP(top);
  ASSERT_BOOL(top, true, "'z' > 'a' -> true");

  reset();
  emit_push_char('x'); emit_push_char('x'); emit_op(OP_EQ); emit_op(OP_HALT);
  RUN_AND_POP(top);
  ASSERT_BOOL(top, true, "'x' == 'x' -> true");
}

// ==========================================
// TRIT
// ==========================================
static void test_trit(void) {
  printf("\n--- TRIT ---\n");
  reset();
  emit_push_trit(0); emit_push_trit(1); emit_op(OP_EQ); emit_op(OP_HALT);
  PaxoVar top; RUN_AND_POP(top);
  ASSERT_BOOL(top, false, "trit(0) == trit(1) -> false");

  reset();
  emit_push_trit(1); emit_push_trit(1); emit_op(OP_EQ); emit_op(OP_HALT);
  RUN_AND_POP(top);
  ASSERT_BOOL(top, true, "trit(1) == trit(1) -> true");
}

static void test_trit_bitwise(void) {
  printf("\n--- TRIT BITWISE ---\n");
  reset();
  emit_push_trit(1); emit_push_trit(0); emit_op(OP_BIT_AND); emit_op(OP_HALT);
  PaxoVar top; RUN_AND_POP(top);
  ASSERT_MSG(top.type == TRIT && top.as.bit == 0, "trit(1) & trit(0) -> 0");

  reset();
  emit_push_trit(1); emit_push_trit(0); emit_op(OP_BIT_OR); emit_op(OP_HALT);
  RUN_AND_POP(top);
  ASSERT_MSG(top.type == TRIT && top.as.bit == 1, "trit(1) | trit(0) -> 1");
}

// ==========================================
// CHAINED OPS
// ==========================================
static void test_chained_add(void) {
  printf("\n--- CHAINED ADD ---\n");
  reset();
  emit_push_num8(1); emit_push_num8(2); emit_op(OP_ADD);
  emit_push_num8(3); emit_op(OP_ADD);
  emit_op(OP_HALT);
  PaxoVar top; RUN_AND_POP(top);
  ASSERT_NUM8_BC(top, 6, "(1 + 2) + 3 = 6");
}

static void test_add_mul_precedence(void) {
  printf("\n--- ADD+MUL ---\n");
  reset();
  emit_push_num8(2); emit_push_num8(3); emit_op(OP_MUL);
  emit_push_num8(4); emit_op(OP_ADD);
  emit_op(OP_HALT);
  PaxoVar top; RUN_AND_POP(top);
  ASSERT_NUM8_BC(top, 10, "2 * 3 + 4 = 10");
}

// ==========================================
// Edge cases
// ==========================================
static void test_zero_ops(void) {
  printf("\n--- ZERO OPS ---\n");
  reset();
  emit_push_num8(0); emit_push_num8(0); emit_op(OP_ADD); emit_op(OP_HALT);
  PaxoVar top; RUN_AND_POP(top);
  ASSERT_NUM8_BC(top, 0, "0 + 0 = 0");

  reset();
  emit_push_num8(0); emit_push_num8(0); emit_op(OP_MUL); emit_op(OP_HALT);
  RUN_AND_POP(top);
  ASSERT_NUM8_BC(top, 0, "0 * 0 = 0");
}

// ==========================================
// Native calls
// ==========================================
static void test_native_typeof(void) {
  printf("\n--- NATIVE TYPEOF ---\n");
  reset();
  emit_push_num8(5); emit_op(OP_CALL_NATIVE); emit16(2); emit8(1);
  emit_op(OP_HALT);
  PaxoVar top; RUN_AND_POP(top);
  ASSERT_MSG(top.type == CHAR && top.as.chara == 'n', "typeof(num8) -> 'n'");
}

// ==========================================
// VM error handler
// ==========================================
static void test_vm_error(void) {
  printf("\n--- VM ERROR HANDLER ---\n");
  VM vm = {0};
  uint8_t dummy[1] = {0};
  vm_init(&vm, dummy);
  vm_error(&vm, "test error");
  ASSERT_MSG(1, "vm_error does not crash");
}

// ==========================================
// main
// ==========================================
int main(void) {
  printf("=== LEP-VM: Full Test Suite ===\n");

  test_add_num8();
  test_sub_num8();
  test_mul_num8();
  test_div_num8();
  test_add_num16();
  test_sub_num16();
  test_mul_num16();
  test_div_num16();
  test_add_num32();
  test_eq();
  test_neq();
  test_lt();
  test_gt();
  test_lte();
  test_gte();
  test_cmp_neq_different_types();
  test_and();
  test_or();
  test_not();
  test_nested_logic();
  test_bit_and();
  test_bit_or();
  test_bit_xor();
  test_bit_not();
  test_bit_shl();
  test_bit_shr();
  test_inc();
  test_dec();
  test_inc_dec_chain();
  test_inc_num16();
  test_load_store_var();
  test_var_overwrite();
  test_pop();
  test_jump();
  test_jump_if_false();
  test_jump_if_true();
  test_char_cmp();
  test_trit();
  test_trit_bitwise();
  test_chained_add();
  test_add_mul_precedence();
  test_zero_ops();
  test_native_typeof();
  test_vm_error();

  printf("\n=== Resultados: %d passed, %d failed ===\n", tests_pass, tests_fail);
  return tests_fail > 0 ? 1 : 0;
}

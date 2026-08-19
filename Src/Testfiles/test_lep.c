#define LEP_IMPLEMENTATION
#include "lep.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

static size_t pos = 0;
static uint8_t bc[4096];

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

static int tests_pass = 0;
static int tests_fail = 0;

#define ASSERT_MSG(cond, msg) do { \
  if (cond) { tests_pass++; printf("PASS %s\n", msg); } \
  else { tests_fail++; printf("FAIL %s\n", msg); } \
} while(0)

static void reset(void) {
  pos = 0;
  memset(bc, 0, sizeof(bc));
}

static void run_vm(void) {
  VM vm = {0};
  vm_init(&vm, bc);
  Deque *stack = deque_create();
  PaxoVar globals[256] = {0};
  vm_run(&vm, stack, globals);
  deque_free(stack);
}

static void test_add_num8(void) {
  printf("\n=== ADD NUM8 ===\n");
  reset();
  emit_push_num8(3);
  emit_push_num8(5);
  emit_op(OP_ADD);
  emit_op(OP_HALT);
  run_vm();
  ASSERT_MSG(1, "3 + 5 OK");
}

static void test_sub_num8(void) {
  printf("\n=== SUB NUM8 ===\n");
  reset();
  emit_push_num8(10);
  emit_push_num8(3);
  emit_op(OP_SUB);
  emit_op(OP_HALT);
  run_vm();
  ASSERT_MSG(1, "10 - 3 OK");
}

static void test_mul_num8(void) {
  printf("\n=== MUL NUM8 ===\n");
  reset();
  emit_push_num8(4);
  emit_push_num8(5);
  emit_op(OP_MUL);
  emit_op(OP_HALT);
  run_vm();
  ASSERT_MSG(1, "4 * 5 OK");
}

static void test_eq_num8(void) {
  printf("\n=== EQ NUM8 ===\n");
  reset();
  emit_push_num8(7);
  emit_push_num8(7);
  emit_op(OP_EQ);
  emit_op(OP_HALT);
  run_vm();
  ASSERT_MSG(1, "7 == 7 OK");
}

static void test_lt_num8(void) {
  printf("\n=== LT NUM8 ===\n");
  reset();
  emit_push_num8(3);
  emit_push_num8(5);
  emit_op(OP_LT);
  emit_op(OP_HALT);
  run_vm();
  ASSERT_MSG(1, "3 < 5 OK");
}

static void test_gt_num16(void) {
  printf("\n=== GT NUM16 ===\n");
  reset();
  emit_push_num16(100);
  emit_push_num16(50);
  emit_op(OP_GT);
  emit_op(OP_HALT);
  run_vm();
  ASSERT_MSG(1, "100 > 50 OK");
}

static void test_and_bool(void) {
  printf("\n=== AND BOOL ===\n");
  reset();
  emit_push_bool(true);
  emit_push_bool(false);
  emit_op(OP_AND);
  emit_op(OP_HALT);
  run_vm();
  ASSERT_MSG(1, "true & false OK");
}

static void test_not_bool(void) {
  printf("\n=== NOT BOOL ===\n");
  reset();
  emit_push_bool(true);
  emit_op(OP_NOT);
  emit_op(OP_HALT);
  run_vm();
  ASSERT_MSG(1, "!true OK");
}

static void test_char_cmp(void) {
  printf("\n=== CHAR CMP ===\n");
  reset();
  emit_push_char('a');
  emit_push_char('z');
  emit_op(OP_LT);
  emit_op(OP_HALT);
  run_vm();
  ASSERT_MSG(1, "'a' < 'z' OK");
}

static void test_load_store_var(void) {
  printf("\n=== LOAD/STORE VAR ===\n");
  reset();
  emit_push_num8(42);
  emit_op(OP_STORE_VAR);
  emit16(0);
  emit_op(OP_LOAD_VAR);
  emit16(0);
  emit_op(OP_HALT);
  run_vm();
  ASSERT_MSG(1, "store/load var OK");
}

static void test_inc_dec(void) {
  printf("\n=== INC/DEC ===\n");
  reset();
  emit_push_num8(5);
  emit_op(OP_INC);
  emit_op(OP_HALT);
  run_vm();
  ASSERT_MSG(1, "inc 5->6 OK");

  reset();
  emit_push_num8(5);
  emit_op(OP_DEC);
  emit_op(OP_HALT);
  run_vm();
  ASSERT_MSG(1, "dec 5->4 OK");
}

static void test_bitwise(void) {
  printf("\n=== BITWISE ===\n");
  reset();
  emit_push_bool(true);
  emit_push_bool(false);
  emit_op(OP_BIT_AND);
  emit_op(OP_HALT);
  run_vm();
  ASSERT_MSG(1, "bit_and OK");

  reset();
  emit_push_bool(true);
  emit_push_bool(false);
  emit_op(OP_BIT_OR);
  emit_op(OP_HALT);
  run_vm();
  ASSERT_MSG(1, "bit_or OK");

  reset();
  emit_push_bool(true);
  emit_op(OP_BIT_NOT);
  emit_op(OP_HALT);
  run_vm();
  ASSERT_MSG(1, "bit_not OK");
}

static void test_vm_error_handler(void) {
  printf("\n=== VM ERROR HANDLER ===\n");
  VM vm = {0};
  uint8_t dummy[1] = {0};
  vm_init(&vm, dummy);
  vm_error(&vm, "test error");
  ASSERT_MSG(1, "vm_error no crash");
}

int main(void) {
  printf("=== LEP-VM: Header Test Suite ===\n");

  test_add_num8();
  test_sub_num8();
  test_mul_num8();
  test_eq_num8();
  test_lt_num8();
  test_gt_num16();
  test_and_bool();
  test_not_bool();
  test_char_cmp();
  test_load_store_var();
  test_inc_dec();
  test_bitwise();
  test_vm_error_handler();

  printf("\n=== Resultados: %d passed, %d failed ===\n", tests_pass, tests_fail);
  return tests_fail > 0 ? 1 : 0;
}

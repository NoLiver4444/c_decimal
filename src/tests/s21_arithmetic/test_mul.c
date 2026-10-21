#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "./../../s21_decimal.h"
#include "./../s21_test_decimal.h"

START_TEST(test_fail_manual_1) {
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};

  int code = s21_mul(decimal1, decimal2, NULL);

  ck_assert_int_ne(code, S21_ARITHMETIC_OK);
}

START_TEST(test_fail_manual_2) {
  s21_decimal decimal1 = {{0, 0, 0, 1000000000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};

  s21_decimal result;

  int code = s21_mul(decimal1, decimal2, &result);

  ck_assert_int_ne(code, S21_ARITHMETIC_OK);
}

START_TEST(test_fail_manual_3) {
  s21_decimal decimal1 = {{-1, 0, 0, 0x1D0000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};

  s21_decimal result;

  int code = s21_mul(decimal1, decimal2, &result);

  ck_assert_int_ne(code, S21_ARITHMETIC_OK);
}

START_TEST(test_fail_manual_4) {
  s21_decimal decimal1 = {{0, 0, 0, 0x1D0000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};

  s21_decimal result;

  int code = s21_mul(decimal1, decimal2, &result);

  ck_assert_int_ne(code, S21_ARITHMETIC_OK);
}

START_TEST(test_fail_manual_5) {
  s21_decimal decimal1 = {{-1, 0, 0, 0x1C0001}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};

  s21_decimal result;

  int code = s21_mul(decimal1, decimal2, &result);

  ck_assert_int_ne(code, S21_ARITHMETIC_OK);
}

START_TEST(test_fail_manual_6) {
  s21_decimal decimal1 = {{-1, 0, 0, 0x1C8000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};

  s21_decimal result;

  int code = s21_mul(decimal1, decimal2, &result);

  ck_assert_int_ne(code, S21_ARITHMETIC_OK);
}

START_TEST(test_fail_manual_7) {
  s21_decimal decimal1 = {{-1, 0, 0, 0x11C0000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};

  s21_decimal result;

  int code = s21_mul(decimal1, decimal2, &result);

  ck_assert_int_ne(code, S21_ARITHMETIC_OK);
}

START_TEST(test_fail_manual_8) {
  s21_decimal decimal1 = {{-1, 0, 0, 0x401C0000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};

  s21_decimal result;

  int code = s21_mul(decimal1, decimal2, &result);

  ck_assert_int_ne(code, S21_ARITHMETIC_OK);
}

START_TEST(test_fail_manual_9) {
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};

  s21_decimal result;

  int code = s21_mul(decimal1, decimal2, &result);

  ck_assert_int_ne(code, S21_ARITHMETIC_OK);
}

START_TEST(test_fail_manual_10) {
  // 792281625.14264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  int code = s21_mul(decimal1, decimal2, NULL);

  ck_assert_int_ne(code, S21_ARITHMETIC_OK);
}

START_TEST(test_fail_manual_11) {
  // -0.0000000000000025
  s21_decimal decimal1 = {{0x19, 0x0, 0x0, 0x80100000}};
  // -0.0000000000000005
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x80100000}};
  // too small
  // 0.0000000000000000000000000000
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x1C0000}};
  int code_check = S21_ARITHMETIC_SMALL;

  test_mul_fail2(decimal1, decimal2, decimal_check, code_check);
}

START_TEST(test_mul_1) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -1
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x80000000}};
  // -79228162514264337593543950335
  s21_decimal decimal_check = {
      {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul_2) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x0}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul_3) {
  // 0.5000000000000000000000000001
  s21_decimal decimal1 = {{0x88000001, 0x1F128130, 0x1027E72F, 0x1C0000}};
  // 1.9999999999999999999999999000
  s21_decimal decimal2 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x1C0000}};
  // 0.9999999999999999999999999502
  s21_decimal decimal_check = {{0xFFFFE0E, 0x3E250261, 0x204FCE5E, 0x1C0000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul_4) {
  // 0.5000000000000000000000000001
  s21_decimal decimal1 = {{0x88000001, 0x1F128130, 0x1027E72F, 0x1C0000}};
  // -1.9999999999999999999999999000
  s21_decimal decimal2 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  // -0.9999999999999999999999999502
  s21_decimal decimal_check = {{0xFFFFE0E, 0x3E250261, 0x204FCE5E, 0x801C0000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul_5) {
  // 0.5000000000000000000000000001
  s21_decimal decimal1 = {{0x88000001, 0x1F128130, 0x1027E72F, 0x1C0000}};
  // -1
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x80000000}};
  // -0.5000000000000000000000000001
  s21_decimal decimal_check = {
      {0x88000001, 0x1F128130, 0x1027E72F, 0x801C0000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul_6) {
  // -0.5000000000000000000000000001
  s21_decimal decimal1 = {{0x88000001, 0x1F128130, 0x1027E72F, 0x801C0000}};
  // 0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x10000}};
  // -0.2500000000000000000000000000
  s21_decimal decimal_check = {{0x44000000, 0x8F894098, 0x813F397, 0x801C0000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul_7) {
  // -0.5000000000000000000000000001
  s21_decimal decimal1 = {{0x88000001, 0x1F128130, 0x1027E72F, 0x801C0000}};
  // -8
  s21_decimal decimal2 = {{0x8, 0x0, 0x0, 0x80000000}};
  // 4.0000000000000000000000000008
  s21_decimal decimal_check = {{0x40000008, 0xF8940984, 0x813F3978, 0x1C0000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul_8) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x80000000}};
  // -0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul_9) {
  // 1.0000000000000000000000000001
  s21_decimal decimal1 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x1C0000}};
  // 6148914689804861440
  s21_decimal decimal2 = {{0x0, 0x55555555, 0x0, 0x0}};
  // 6148914689804861440.0000000006
  s21_decimal decimal_check = {{0x6, 0x8EA6B400, 0xC6AEA154, 0xA0000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul_10) {
  // 1.0000000000000000000000000001
  s21_decimal decimal1 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x1C0000}};
  // -79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // overflow
  int code_check = S21_ARITHMETIC_SMALL;

  test_mul_fail1(decimal1, decimal2, code_check);
}

Suite *mul_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("mul");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_fail_manual_1);
  tcase_add_test(tc_core, test_fail_manual_2);
  tcase_add_test(tc_core, test_fail_manual_3);
  tcase_add_test(tc_core, test_fail_manual_4);
  tcase_add_test(tc_core, test_fail_manual_5);
  tcase_add_test(tc_core, test_fail_manual_6);
  tcase_add_test(tc_core, test_fail_manual_7);
  tcase_add_test(tc_core, test_fail_manual_8);
  tcase_add_test(tc_core, test_fail_manual_9);
  tcase_add_test(tc_core, test_fail_manual_10);
  tcase_add_test(tc_core, test_fail_manual_11);

  tcase_add_test(tc_core, test_mul_1);
  tcase_add_test(tc_core, test_mul_2);
  tcase_add_test(tc_core, test_mul_3);
  tcase_add_test(tc_core, test_mul_4);
  tcase_add_test(tc_core, test_mul_5);
  tcase_add_test(tc_core, test_mul_6);
  tcase_add_test(tc_core, test_mul_7);
  tcase_add_test(tc_core, test_mul_8);
  tcase_add_test(tc_core, test_mul_9);
  tcase_add_test(tc_core, test_mul_10);

  suite_add_tcase(s, tc_core);
  return s;
}

void test_mul(s21_decimal decimal1, s21_decimal decimal2, s21_decimal check) {
  s21_decimal result;
  int code = s21_mul(decimal1, decimal2, &result);

#if defined(__DEBUG)
  printf("---------------------------------\n");
  printf("\n\nTests:\n");
  s21_print_decimal_bits(decimal1);
  s21_print_decimal_string(decimal1);
  s21_print_decimal_bits(decimal2);
  s21_print_decimal_string(decimal2);
  printf("\ncheck:\n");
  s21_print_decimal_bits(check);
  s21_print_decimal_string(check);
  printf("\nres:\n");
  s21_print_decimal_bits(result);
  s21_print_decimal_string(result);
  printf("---------------------------------\n");
#endif

  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(code, S21_ARITHMETIC_OK);
}

void test_mul_fail1(s21_decimal decimal1, s21_decimal decimal2,
                    int code_check) {
  s21_decimal result;
  int code = s21_mul(decimal1, decimal2, &result);

#if defined(__DEBUG)
  printf("---------------------------------\n");
  printf("\n\nTests:\n");
  s21_print_decimal_bits(decimal1);
  s21_print_decimal_string(decimal1);
  s21_print_decimal_bits(decimal2);
  s21_print_decimal_string(decimal2);
  printf("\nres:\n");
  s21_print_decimal_bits(result);
  s21_print_decimal_string(result);
  printf("---------------------------------\n");
#endif

  ck_assert_int_eq(code, code_check);
}

void test_mul_fail2(s21_decimal decimal1, s21_decimal decimal2,
                    s21_decimal decimal_check, int code_check) {
  s21_decimal result;
  int code = s21_mul(decimal1, decimal2, &result);

#if defined(__DEBUG)
  printf("---------------------------------\n");
  printf("\n\nTests:\n");
  s21_print_decimal_bits(decimal1);
  s21_print_decimal_string(decimal1);
  s21_print_decimal_bits(decimal2);
  s21_print_decimal_string(decimal2);
  printf("\nres:\n");
  s21_print_decimal_bits(result);
  s21_print_decimal_string(result);
  printf("---------------------------------\n");
#endif

  ck_assert_int_eq(code, code_check);
  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

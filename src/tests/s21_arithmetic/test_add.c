#include <stdio.h>
#include <stdlib.h>

#include "./../../s21_decimal.h"
#include "./../s21_test_decimal.h"

START_TEST(test_fail_manual_1) {
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};

  int code = s21_add(decimal1, decimal2, NULL);

  ck_assert_int_ne(code, S21_ARITHMETIC_OK);
}

START_TEST(test_fail_manual_2) {
  s21_decimal decimal1 = {{0, 0, 0, 1000000000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};

  s21_decimal result;

  int code = s21_add(decimal1, decimal2, &result);

  ck_assert_int_ne(code, S21_ARITHMETIC_OK);
}

START_TEST(test_fail_manual_3) {
  s21_decimal decimal1 = {{-1, 0, 0, 0x1D0000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};

  s21_decimal result;

  int code = s21_add(decimal1, decimal2, &result);

  ck_assert_int_ne(code, S21_ARITHMETIC_OK);
}

START_TEST(test_fail_manual_4) {
  s21_decimal decimal1 = {{0, 0, 0, 0x1D0000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};

  s21_decimal result;

  int code = s21_add(decimal1, decimal2, &result);

  ck_assert_int_ne(code, S21_ARITHMETIC_OK);
}

START_TEST(test_fail_manual_5) {
  s21_decimal decimal1 = {{-1, 0, 0, 0x1C0001}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};

  s21_decimal result;

  int code = s21_add(decimal1, decimal2, &result);

  ck_assert_int_ne(code, S21_ARITHMETIC_OK);
}

START_TEST(test_fail_manual_6) {
  s21_decimal decimal1 = {{-1, 0, 0, 0x1C8000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};

  s21_decimal result;

  int code = s21_add(decimal1, decimal2, &result);

  ck_assert_int_ne(code, S21_ARITHMETIC_OK);
}

START_TEST(test_fail_manual_7) {
  s21_decimal decimal1 = {{-1, 0, 0, 0x11C0000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};

  s21_decimal result;

  int code = s21_add(decimal1, decimal2, &result);

  ck_assert_int_ne(code, S21_ARITHMETIC_OK);
}

START_TEST(test_fail_manual_8) {
  s21_decimal decimal1 = {{-1, 0, 0, 0x401C0000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};

  s21_decimal result;

  int code = s21_add(decimal1, decimal2, &result);

  ck_assert_int_ne(code, S21_ARITHMETIC_OK);
}

START_TEST(test_fail_manual_9) {
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};

  s21_decimal result;

  int code = s21_add(decimal1, decimal2, &result);

  ck_assert_int_ne(code, S21_ARITHMETIC_OK);
}

START_TEST(test_fail_manual_10) {
  s21_decimal decimal2 = {{0, 0, 0, 1000000000}};
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};

  s21_decimal result;

  int code = s21_add(decimal1, decimal2, &result);

  ck_assert_int_ne(code, S21_ARITHMETIC_OK);
}

START_TEST(test_add_1) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // overflow
  int check = S21_ARITHMETIC_BIG;

  test_add_fail(decimal1, decimal2, check);
}

START_TEST(test_add_2) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 0
  s21_decimal check = {{0x0, 0x0, 0x0, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add_3) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 79228162514264337593543950334
  s21_decimal decimal2 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // overflow
  int check = S21_ARITHMETIC_BIG;

  test_add_fail(decimal1, decimal2, check);
}

START_TEST(test_add_4) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -79228162514264337593543950334
  s21_decimal decimal2 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 1
  s21_decimal check = {{0x1, 0x0, 0x0, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add_5) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // -0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x80010000}};
  // 0.5
  s21_decimal check = {{0x5, 0x0, 0x0, 0x10000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add_6) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0.0000000000000000000000000000
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x1C0000}};
  // 79228162514264337593543950335
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add_7) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 7.9228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  // -79228162514264337593543950327
  s21_decimal check = {{0xFFFFFFF7, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add_9) {
  // -0.5
  s21_decimal decimal1 = {{0x5, 0x0, 0x0, 0x80010000}};
  // 1
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x0}};
  // 0.5
  s21_decimal check = {{0x5, 0x0, 0x0, 0x10000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add_10) {
  // 0.5
  s21_decimal decimal1 = {{0x5, 0x0, 0x0, 0x10000}};
  // -0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x80010000}};
  // 0
  s21_decimal check = {{0x0, 0x0, 0x0, 0x10000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add_11) {
  // -1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x80000000}};
  // -26409387.498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x80150000}};
  // -26409388.498605864508043122005
  s21_decimal check = {{0x33F55555, 0x35C9ADC6, 0x5555558B, 0x80150000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add_12) {
  // -1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x80000000}};
  // -8
  s21_decimal decimal2 = {{0x8, 0x0, 0x0, 0x80000000}};
  // -9
  s21_decimal check = {{0x9, 0x0, 0x0, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add_13) {
  // 0.5
  s21_decimal decimal1 = {{0x5, 0x0, 0x0, 0x10000}};
  // -0.4999999999999999999999999999
  s21_decimal decimal2 = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x801C0000}};
  // 0.0000000000000000000000000001
  s21_decimal check = {{0x1, 0x0, 0x0, 0x1C0000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add_14) {
  // 0.5
  s21_decimal decimal1 = {{0x5, 0x0, 0x0, 0x10000}};
  // 0.5000000000000000000000000001
  s21_decimal decimal2 = {{0x88000001, 0x1F128130, 0x1027E72F, 0x1C0000}};
  // 1.0000000000000000000000000001
  s21_decimal check = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x1C0000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add_15) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // overflow
  int check = S21_ARITHMETIC_SMALL;

  test_add_fail(decimal1, decimal2, check);
}

Suite *add_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("add");
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

  tcase_add_test(tc_core, test_add_1);
  tcase_add_test(tc_core, test_add_2);
  tcase_add_test(tc_core, test_add_3);
  tcase_add_test(tc_core, test_add_4);
  tcase_add_test(tc_core, test_add_5);
  tcase_add_test(tc_core, test_add_6);
  tcase_add_test(tc_core, test_add_7);
  tcase_add_test(tc_core, test_add_9);
  tcase_add_test(tc_core, test_add_10);
  tcase_add_test(tc_core, test_add_11);
  tcase_add_test(tc_core, test_add_12);
  tcase_add_test(tc_core, test_add_13);
  tcase_add_test(tc_core, test_add_14);
  tcase_add_test(tc_core, test_add_15);

  suite_add_tcase(s, tc_core);
  return s;
}

void test_add(s21_decimal decimal1, s21_decimal decimal2, s21_decimal check) {
  s21_decimal result;
  int code = s21_add(decimal1, decimal2, &result);

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
  printf("---------------------------------\n\n\n\n");
#endif

  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(code, S21_ARITHMETIC_OK);
}

void test_add_fail(s21_decimal decimal1, s21_decimal decimal2, int check) {
  s21_decimal result;
  int code = s21_add(decimal1, decimal2, &result);

#if defined(__DEBUG)
  printf("---------------------------------\n");
  printf("\n\nTests:\n");
  s21_print_decimal_bits(decimal1);
  s21_print_decimal_string(decimal1);
  s21_print_decimal_bits(decimal2);
  s21_print_decimal_string(decimal2);
  printf("Check: %d\n", check);
  printf("Result: %d\n", code);
  printf("---------------------------------\n\n\n\n");
#endif

  ck_assert_int_eq(code, check);
}

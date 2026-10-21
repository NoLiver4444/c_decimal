#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "./../../s21_decimal.h"
#include "./../s21_test_decimal.h"

START_TEST(test_fail_manual_1) {
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};

  int code = s21_sub(decimal1, decimal2, NULL);

  ck_assert_int_ne(code, S21_ARITHMETIC_OK);
}
END_TEST

START_TEST(test_fail_manual_2) {
  s21_decimal decimal1 = {{0, 0, 0, 1000000000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};

  s21_decimal result;

  int code = s21_sub(decimal1, decimal2, &result);

  ck_assert_int_ne(code, S21_ARITHMETIC_OK);
}
END_TEST

START_TEST(test_fail_manual_3) {
  s21_decimal decimal1 = {{-1, 0, 0, 0x1D0000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};

  s21_decimal result;

  int code = s21_sub(decimal1, decimal2, &result);

  ck_assert_int_ne(code, S21_ARITHMETIC_OK);
}
END_TEST

START_TEST(test_fail_manual_4) {
  s21_decimal decimal1 = {{0, 0, 0, 0x1D0000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};

  s21_decimal result;

  int code = s21_sub(decimal1, decimal2, &result);

  ck_assert_int_ne(code, S21_ARITHMETIC_OK);
}
END_TEST

START_TEST(test_fail_manual_5) {
  s21_decimal decimal1 = {{-1, 0, 0, 0x1C0001}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};

  s21_decimal result;

  int code = s21_sub(decimal1, decimal2, &result);

  ck_assert_int_ne(code, S21_ARITHMETIC_OK);
}
END_TEST

START_TEST(test_fail_manual_6) {
  s21_decimal decimal1 = {{-1, 0, 0, 0x1C8000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};

  s21_decimal result;

  int code = s21_sub(decimal1, decimal2, &result);

  ck_assert_int_ne(code, S21_ARITHMETIC_OK);
}
END_TEST

START_TEST(test_fail_manual_7) {
  s21_decimal decimal1 = {{-1, 0, 0, 0x11C0000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};

  s21_decimal result;

  int code = s21_sub(decimal1, decimal2, &result);

  ck_assert_int_ne(code, S21_ARITHMETIC_OK);
}
END_TEST

START_TEST(test_fail_manual_8) {
  s21_decimal decimal1 = {{-1, 0, 0, 0x401C0000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};

  s21_decimal result;

  int code = s21_sub(decimal1, decimal2, &result);

  ck_assert_int_ne(code, S21_ARITHMETIC_OK);
}
END_TEST

START_TEST(test_fail_manual_9) {
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};

  s21_decimal result;

  int code = s21_sub(decimal1, decimal2, &result);

  ck_assert_int_ne(code, S21_ARITHMETIC_OK);
}
END_TEST

START_TEST(test_fail_manual_10) {
  // 792281625.14264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  int code = s21_sub(decimal1, decimal2, NULL);

  ck_assert_int_ne(code, S21_ARITHMETIC_OK);
}
END_TEST

START_TEST(test_sub_1) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0
  s21_decimal check = {{0x0, 0x0, 0x0, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub_2) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 79228162514264337593543950334
  s21_decimal decimal2 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 1
  s21_decimal check = {{0x1, 0x0, 0x0, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub_3) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x10000}};
  // 79228162514264337593543950334
  s21_decimal check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub_4) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x0}};
  // 79228162514264337593543950335
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub_5) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x801C0000}};
  // 79228162514264337593543950335
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub_6) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // overflow
  int check = S21_ARITHMETIC_SMALL;

  test_sub_fail(decimal1, decimal2, check);
}

START_TEST(test_sub_7) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 1
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x0}};
  // overflow
  int check = S21_ARITHMETIC_SMALL;

  test_sub_fail(decimal1, decimal2, check);
}

START_TEST(test_sub_10) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0.4999999999999999999999999999
  s21_decimal decimal2 = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x801C0000}};
  // 79228162514264337593543950334
  s21_decimal check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub_11) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -7922816251426433759354395033
  s21_decimal decimal2 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // -71305346262837903834189555302
  s21_decimal check = {{0x66666666, 0x66666666, 0xE6666666, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub_12) {
  // -26409387.498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x80150000}};
  // -0.5000000000000000000000000001
  s21_decimal decimal2 = {{0x88000001, 0x1F128130, 0x1027E72F, 0x801C0000}};
  // -26409386.998605864508043122005
  s21_decimal check = {{0x66055555, 0xE51B291D, 0x55555539, 0x80150000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub_13) {
  // -0.5
  s21_decimal decimal1 = {{0x5, 0x0, 0x0, 0x80010000}};
  // -646.33673839575124685661598885
  s21_decimal decimal2 = {{0xB2C6F4A5, 0xA11CA39F, 0xD0D7B8CF, 0x801A0000}};
  // 645.83673839575124685661598885
  s21_decimal check = {{0x40C6F4A5, 0x32B89D36, 0xD0AE5CE6, 0x1A0000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub_14) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // overflow
  int check = S21_ARITHMETIC_BIG;

  test_sub_fail(decimal1, decimal2, check);
}

START_TEST(test_sub_15) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -1.9999999999999999999999999000
  s21_decimal decimal2 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  // overflow
  int check = S21_ARITHMETIC_BIG;

  test_sub_fail(decimal1, decimal2, check);
}
Suite *sub_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("sub");
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

  tcase_add_test(tc_core, test_sub_1);
  tcase_add_test(tc_core, test_sub_2);
  tcase_add_test(tc_core, test_sub_3);
  tcase_add_test(tc_core, test_sub_4);
  tcase_add_test(tc_core, test_sub_5);
  tcase_add_test(tc_core, test_sub_6);
  tcase_add_test(tc_core, test_sub_7);
  tcase_add_test(tc_core, test_sub_10);
  tcase_add_test(tc_core, test_sub_11);
  tcase_add_test(tc_core, test_sub_12);
  tcase_add_test(tc_core, test_sub_13);
  tcase_add_test(tc_core, test_sub_14);
  tcase_add_test(tc_core, test_sub_15);

  suite_add_tcase(s, tc_core);
  return s;
}

void test_sub(s21_decimal decimal1, s21_decimal decimal2, s21_decimal check) {
  s21_decimal result;
  int code = s21_sub(decimal1, decimal2, &result);
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

void test_sub_fail(s21_decimal decimal1, s21_decimal decimal2, int check) {
  s21_decimal result;
  int code = s21_sub(decimal1, decimal2, &result);

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

  ck_assert_int_eq(code, check);
}

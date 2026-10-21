#include <check.h>
#include <limits.h>

#include "../../s21_decimal.h"

START_TEST(test_from_int_to_decimal_positive) {
  int src = 12345;
  s21_decimal result;
  ck_assert_int_eq(s21_from_int_to_decimal(src, &result), 0);
  ck_assert_int_eq(result.bits[0], 12345);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_from_int_to_decimal_negative) {
  int src = -12345;
  s21_decimal result;
  ck_assert_int_eq(s21_from_int_to_decimal(src, &result), 0);
  ck_assert_int_eq(result.bits[0], 12345);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], (-2147483648));
}
END_TEST

START_TEST(test_from_int_to_decimal_zero) {
  int src = 0;
  s21_decimal result;
  ck_assert_int_eq(s21_from_int_to_decimal(src, &result), 0);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_from_int_to_decimal_null_decimal) {
  int src = 12345;
  ck_assert_int_eq(s21_from_int_to_decimal(src, NULL), 1);
}
END_TEST

START_TEST(test_from_int_to_decimal_int_min) {
  int src = INT_MIN;
  s21_decimal result;
  ck_assert_int_eq(s21_from_int_to_decimal(src, &result), 0);
  ck_assert_int_eq(result.bits[0], (-2147483648));
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], (-2147483648));
}
END_TEST

START_TEST(test_from_int_to_decimal_int_max) {
  int src = INT_MAX;
  s21_decimal result;
  ck_assert_int_eq(s21_from_int_to_decimal(src, &result), 0);
  ck_assert_int_eq(result.bits[0], INT_MAX);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

Suite *suite_s21_from_int_to_decimal(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_from_int_to_decimal");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_from_int_to_decimal_positive);
  tcase_add_test(tc_core, test_from_int_to_decimal_negative);
  tcase_add_test(tc_core, test_from_int_to_decimal_zero);
  tcase_add_test(tc_core, test_from_int_to_decimal_null_decimal);
  tcase_add_test(tc_core, test_from_int_to_decimal_int_min);
  tcase_add_test(tc_core, test_from_int_to_decimal_int_max);
  suite_add_tcase(s, tc_core);

  return s;
}

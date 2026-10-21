#include <check.h>

#include "../../s21_decimal.h"

START_TEST(test_from_decimal_to_int_positive) {
  s21_decimal value = {{12345, 0, 0, 0}};
  int result;
  ck_assert_int_eq(s21_from_decimal_to_int(value, &result), 0);
  ck_assert_int_eq(result, 12345);
}
END_TEST

START_TEST(test_from_decimal_to_int_zero) {
  s21_decimal value = {{0, 0, 0, 0}};
  int result;
  ck_assert_int_eq(s21_from_decimal_to_int(value, &result), 0);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_from_decimal_to_int_null_pointer) {
  s21_decimal value = {{12345, 0, 0, 0}};
  ck_assert_int_eq(s21_from_decimal_to_int(value, NULL), 1);
}
END_TEST

START_TEST(test_from_decimal_to_int_incorrect_decimal) {
  s21_decimal value = {{12345, 0, 0, 0xFFFFFFFF}};  // Некорректный decimal
  int result;
  ck_assert_int_eq(s21_from_decimal_to_int(value, &result), 1);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_from_decimal_to_int_max_int) {
  s21_decimal value = {{INT32_MAX, 0, 0, 0}};
  int result;
  ck_assert_int_eq(s21_from_decimal_to_int(value, &result), 0);
  ck_assert_int_eq(result, INT32_MAX);
}
END_TEST

START_TEST(test_from_decimal_to_int_min_int) {
  s21_decimal value = {{(unsigned int)INT32_MAX + 1, 0, 0, 0x80000000}};
  int result;
  ck_assert_int_eq(s21_from_decimal_to_int(value, &result), 0);
  ck_assert_int_eq(result, INT32_MIN);
}
END_TEST

START_TEST(test_from_decimal_to_int_too_large) {
  s21_decimal value = {{0, 1, 0, 0}};  // Число больше INT32_MAX
  int result;
  ck_assert_int_eq(s21_from_decimal_to_int(value, &result), 1);
}
END_TEST

START_TEST(test_from_decimal_to_int_too_small) {
  s21_decimal value = {{0, 1, 0, 0x80000000}};  // Число меньше INT32_MIN
  int result;
  ck_assert_int_eq(s21_from_decimal_to_int(value, &result), 1);
}
END_TEST

START_TEST(test_from_decimal_to_int_with_scale) {
  s21_decimal value = {{12345, 0, 0, 0x10000}};  // Число с масштабом 1
  int result;
  ck_assert_int_eq(s21_from_decimal_to_int(value, &result), 0);
  ck_assert_int_eq(result, 1234);  // 12345/10 = 1234 после truncate
}
END_TEST

Suite *suite_s21_from_decimal_to_int(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_from_decimal_to_int");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_from_decimal_to_int_positive);
  tcase_add_test(tc_core, test_from_decimal_to_int_zero);
  tcase_add_test(tc_core, test_from_decimal_to_int_null_pointer);
  tcase_add_test(tc_core, test_from_decimal_to_int_incorrect_decimal);
  tcase_add_test(tc_core, test_from_decimal_to_int_max_int);
  tcase_add_test(tc_core, test_from_decimal_to_int_min_int);
  tcase_add_test(tc_core, test_from_decimal_to_int_too_large);
  tcase_add_test(tc_core, test_from_decimal_to_int_too_small);
  tcase_add_test(tc_core, test_from_decimal_to_int_with_scale);
  suite_add_tcase(s, tc_core);

  return s;
}

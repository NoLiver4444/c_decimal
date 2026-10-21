#include <check.h>

#include "../../s21_decimal.h"

START_TEST(test_floor_positive) {
  s21_decimal value = {{12345, 0, 0, 0}};
  s21_decimal expected = {{12345, 0, 0, 0}};
  s21_decimal result;
  ck_assert_int_eq(s21_floor(value, &result), 0);
  ck_assert(s21_is_equal(result, expected));
}
END_TEST

START_TEST(test_floor_negative) {
  s21_decimal value = {{12345, 0, 0, 0x80000000}};
  s21_decimal expected = {{12346, 0, 0, 0x80000000}};
  s21_decimal result;
  ck_assert_int_eq(s21_floor(value, &result), 0);
  ck_assert(s21_is_equal(result, expected));
}
END_TEST

START_TEST(test_floor_zero) {
  s21_decimal value = {{0, 0, 0, 0}};
  s21_decimal expected = {{0, 0, 0, 0}};
  s21_decimal result;
  ck_assert_int_eq(s21_floor(value, &result), 0);
  ck_assert(s21_is_equal(result, expected));
}
END_TEST

START_TEST(test_floor_null_result) {
  s21_decimal value = {{12345, 0, 0, 0}};
  ck_assert_int_eq(s21_floor(value, NULL), 1);
}
END_TEST

START_TEST(test_floor_positive_with_fraction) {
  s21_decimal value = {{12345, 0, 0, 0}};
  s21_decimal expected = {{12345, 0, 0, 0}};
  s21_decimal result;
  ck_assert_int_eq(s21_floor(value, &result), 0);
  ck_assert(s21_is_equal(result, expected));
}
END_TEST

START_TEST(test_floor_positive_no_fraction) {
  s21_decimal value = {{12345, 0, 0, 0}};
  s21_decimal expected = {{12345, 0, 0, 0}};
  s21_decimal result;
  ck_assert_int_eq(s21_floor(value, &result), 0);
  ck_assert(s21_is_equal(result, expected));
}
END_TEST

Suite *suite_s21_floor(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_floor");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_floor_positive);
  tcase_add_test(tc_core, test_floor_negative);
  tcase_add_test(tc_core, test_floor_zero);
  tcase_add_test(tc_core, test_floor_null_result);
  tcase_add_test(tc_core, test_floor_positive_with_fraction);
  tcase_add_test(tc_core, test_floor_positive_no_fraction);
  suite_add_tcase(s, tc_core);

  return s;
}

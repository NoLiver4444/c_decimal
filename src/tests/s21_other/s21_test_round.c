#include <check.h>

#include "../../s21_decimal.h"

START_TEST(test_round_positive) {
  s21_decimal value = {{15, 0, 0, 0x10000}};  // 1.5
  s21_decimal expected = {{2, 0, 0, 0}};      // 2
  s21_decimal result;
  ck_assert_int_eq(s21_round(value, &result), 0);
  ck_assert(s21_is_equal(result, expected));
}
END_TEST

START_TEST(test_round_negative) {
  s21_decimal value = {{15, 0, 0, 0x80010000}};    // -1.5
  s21_decimal expected = {{2, 0, 0, 0x80000000}};  // -2
  s21_decimal result;
  ck_assert_int_eq(s21_round(value, &result), 0);
  ck_assert(s21_is_equal(result, expected));
}
END_TEST

START_TEST(test_round_banking_even) {
  s21_decimal value = {{25, 0, 0, 0x10000}};  // 2.5
  s21_decimal expected = {{2, 0, 0, 0}};  // 2 (округление к ближайшему чётному)
  s21_decimal result;
  ck_assert_int_eq(s21_round(value, &result), 0);
  ck_assert(s21_is_equal(result, expected));
}
END_TEST

START_TEST(test_round_banking_odd) {
  s21_decimal value = {{35, 0, 0, 0x10000}};  // 3.5
  s21_decimal expected = {{4, 0, 0, 0}};  // 4 (округление к ближайшему чётному)
  s21_decimal result;
  ck_assert_int_eq(s21_round(value, &result), 0);
  ck_assert(s21_is_equal(result, expected));
}
END_TEST

START_TEST(test_round_zero) {
  s21_decimal value = {{0, 0, 0, 0}};
  s21_decimal expected = {{0, 0, 0, 0}};
  s21_decimal result;
  ck_assert_int_eq(s21_round(value, &result), 0);
  ck_assert(s21_is_equal(result, expected));
}
END_TEST

START_TEST(test_round_null_pointer) {
  s21_decimal value = {{15, 0, 0, 0x10000}};
  ck_assert_int_eq(s21_round(value, NULL), 1);
}
END_TEST

START_TEST(test_round_incorrect_decimal) {
  s21_decimal value = {{0, 0, 0, 0x001F0000}};  // Некорректная степень > 28
  s21_decimal result;
  ck_assert_int_eq(s21_round(value, &result), 1);
}
END_TEST

START_TEST(test_round_large_number) {
  s21_decimal value = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
                        0x10000}};  // Максимальное значение с дробной частью
  s21_decimal result;
  ck_assert_int_eq(s21_round(value, &result), 0);
}
END_TEST

Suite *suite_s21_round(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_round");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_round_positive);
  tcase_add_test(tc_core, test_round_negative);
  tcase_add_test(tc_core, test_round_banking_even);
  tcase_add_test(tc_core, test_round_banking_odd);
  tcase_add_test(tc_core, test_round_zero);
  tcase_add_test(tc_core, test_round_null_pointer);
  tcase_add_test(tc_core, test_round_incorrect_decimal);
  tcase_add_test(tc_core, test_round_large_number);

  suite_add_tcase(s, tc_core);

  return s;
}

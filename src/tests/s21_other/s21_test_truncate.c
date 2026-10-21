#include "../s21_test_decimal.h"

START_TEST(test_truncate_positive) {
  s21_decimal value = {{15, 0, 0, 0x10000}};  // 1.5
  s21_decimal result;
  s21_decimal check = {{1, 0, 0, 0}};  // 1

  int code = s21_truncate(value, &result);

  ck_assert_int_eq(code, S21_OTHER_OK);
  ck_assert_int_eq(s21_is_equal_dickcart(result, check), S21_COMPARISON_TRUE);
}
END_TEST

START_TEST(test_truncate_negative) {
  s21_decimal value = {{15, 0, 0, 0x80010000}};  // -1.5
  s21_decimal result;
  s21_decimal check = {{1, 0, 0, 0x80000000}};  // -1

  int code = s21_truncate(value, &result);

  ck_assert_int_eq(code, S21_OTHER_OK);
  ck_assert_int_eq(s21_is_equal_dickcart(result, check), S21_COMPARISON_TRUE);
}
END_TEST

START_TEST(test_truncate_zero) {
  s21_decimal value = {{0, 0, 0, 0}};  // 0
  s21_decimal result;
  s21_decimal check = {{0, 0, 0, 0}};  // 0

  int code = s21_truncate(value, &result);

  ck_assert_int_eq(code, S21_OTHER_OK);
  ck_assert_int_eq(s21_is_equal_dickcart(result, check), S21_COMPARISON_TRUE);
}
END_TEST

START_TEST(test_truncate_large_power) {
  s21_decimal value = {
      {123456789, 0, 0, 0x1C0000}};  // 0.123456789 (power = 28)
  s21_decimal result;
  s21_decimal check = {{0, 0, 0, 0}};  // 0

  int code = s21_truncate(value, &result);

  ck_assert_int_eq(code, S21_OTHER_OK);
  ck_assert_int_eq(s21_is_equal_dickcart(result, check), S21_COMPARISON_TRUE);
}
END_TEST

START_TEST(test_truncate_null_pointer) {
  s21_decimal value = {{15, 0, 0, 0x10000}};  // 1.5

  int code = s21_truncate(value, NULL);

  ck_assert_int_eq(code, S21_OTHER_ERROR);
}
END_TEST

START_TEST(test_truncate_incorrect_decimal) {
  s21_decimal value = {{15, 0, 0, 0x1F0000}};  // Некорректная степень (31)
  s21_decimal result;
  s21_decimal check = s21_decimal_get_inf();

  int code = s21_truncate(value, &result);

  ck_assert_int_eq(code, S21_OTHER_ERROR);
  ck_assert_int_eq(s21_is_equal_dickcart(result, check), S21_COMPARISON_TRUE);
}
END_TEST

Suite *suite_s21_truncate(void) {
  Suite *s = suite_create("suite_s21_truncate");
  TCase *tc = tcase_create("s21_truncate_tc");

  tcase_add_test(tc, test_truncate_positive);
  tcase_add_test(tc, test_truncate_negative);
  tcase_add_test(tc, test_truncate_zero);
  tcase_add_test(tc, test_truncate_large_power);
  tcase_add_test(tc, test_truncate_null_pointer);
  tcase_add_test(tc, test_truncate_incorrect_decimal);

  suite_add_tcase(s, tc);
  return s;
}

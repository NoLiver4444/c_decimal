#include "../s21_test_decimal.h"

START_TEST(test_get_bit_basic) {
  s21_decimal dec = {{0x1, 0x0, 0x0, 0x0}};  // 1 в младшем бите
  ck_assert_int_eq(s21_get_bit(&dec, 0), 1);
  ck_assert_int_eq(s21_get_bit(&dec, 1), 0);
}
END_TEST

START_TEST(test_get_bit_middle) {
  s21_decimal dec = {{0x0, 0x1, 0x0, 0x0}};  // 1 в 32-м бите
  ck_assert_int_eq(s21_get_bit(&dec, 32), 1);
  ck_assert_int_eq(s21_get_bit(&dec, 31), 0);
}
END_TEST

START_TEST(test_get_bit_high) {
  s21_decimal dec = {{0x0, 0x0, 0x1, 0x0}};  // 1 в 64-м бите
  ck_assert_int_eq(s21_get_bit(&dec, 64), 1);
  ck_assert_int_eq(s21_get_bit(&dec, 63), 0);
}
END_TEST

START_TEST(test_get_power_zero) {
  s21_decimal dec = {{0x0, 0x0, 0x0, 0x0}};  // степень 0
  ck_assert_int_eq(s21_get_power(&dec), 0);
}
END_TEST

START_TEST(test_get_power_max) {
  s21_decimal dec = {{0x0, 0x0, 0x0, 0x1C0000}};  // степень 28
  ck_assert_int_eq(s21_get_power(&dec), 28);
}
END_TEST

START_TEST(test_get_sign_positive) {
  s21_decimal dec = {{0x1, 0x0, 0x0, 0x0}};  // положительное число
  ck_assert_int_eq(s21_get_sign(&dec), 0);
}
END_TEST

START_TEST(test_get_sign_negative) {
  s21_decimal dec = {{0x1, 0x0, 0x0, 0x80000000}};  // отрицательное число
  ck_assert_int_eq(s21_get_sign(&dec), 1);
}
END_TEST

Suite *suite_s21_get_bit_dickcart(void) {
  Suite *s = suite_create("s21_get_bit");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, test_get_bit_basic);
  tcase_add_test(tc, test_get_bit_middle);
  tcase_add_test(tc, test_get_bit_high);

  suite_add_tcase(s, tc);
  return s;
}

Suite *suite_s21_get_power_dickcart(void) {
  Suite *s = suite_create("s21_get_power");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, test_get_power_zero);
  tcase_add_test(tc, test_get_power_max);

  suite_add_tcase(s, tc);
  return s;
}

Suite *suite_s21_get_sign_dickcart(void) {
  Suite *s = suite_create("s21_get_sign");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, test_get_sign_positive);
  tcase_add_test(tc, test_get_sign_negative);

  suite_add_tcase(s, tc);
  return s;
}

#include <check.h>

#include "../../s21_decimal.h"

START_TEST(test_from_decimal_to_float_null_dst) {
  s21_decimal src = {{123, 0, 0, 0}};
  ck_assert_int_eq(s21_from_decimal_to_float(src, NULL), 1);
}
END_TEST

START_TEST(test_from_decimal_to_float_incorrect_decimal) {
  s21_decimal src = {{123, 0, 0, 0xFFFFFFFF}};  // Некорректная степень
  float dst;
  ck_assert_int_eq(s21_from_decimal_to_float(src, &dst), 1);
  ck_assert_float_eq(dst, 0.0);
}
END_TEST

START_TEST(test_from_decimal_to_float_zero) {
  s21_decimal src = {{0, 0, 0, 0}};
  float dst;
  ck_assert_int_eq(s21_from_decimal_to_float(src, &dst), 0);
  ck_assert_float_eq(dst, 0.0);
}
END_TEST

START_TEST(test_from_decimal_to_float_negative_zero) {
  s21_decimal src = {{0, 0, 0, 0x80000000}};  // -0
  float dst;
  ck_assert_int_eq(s21_from_decimal_to_float(src, &dst), 0);
  ck_assert_float_eq(dst, -0.0);
}
END_TEST

START_TEST(test_from_decimal_to_float_positive) {
  s21_decimal src = {{123, 0, 0, 0}};
  float dst;
  ck_assert_int_eq(s21_from_decimal_to_float(src, &dst), 0);
  ck_assert_float_eq(dst, 123.0);
}
END_TEST

START_TEST(test_from_decimal_to_float_negative) {
  s21_decimal src = {{123, 0, 0, 0x80000000}};  // -123
  float dst;
  ck_assert_int_eq(s21_from_decimal_to_float(src, &dst), 0);
  ck_assert_float_eq(dst, -123.0);
}
END_TEST

START_TEST(test_from_decimal_to_float_with_power) {
  s21_decimal src = {{123, 0, 0, 0x00010000}};  // 12.3 (power = 1)
  float dst;
  ck_assert_int_eq(s21_from_decimal_to_float(src, &dst), 0);
  ck_assert_float_eq(dst, 12.3f);
}
END_TEST

START_TEST(test_from_decimal_to_float_max_value) {
  s21_decimal src = {
      {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};  // Максимальное значение
  float dst;
  ck_assert_int_eq(s21_from_decimal_to_float(src, &dst), 0);
  ck_assert_float_eq(dst, 79228162514264337593543950336.0f);
}
END_TEST

START_TEST(test_from_decimal_to_float_different_bits) {
  s21_decimal src = {{0xAAAAAAAA, 0x55555555, 0xCCCCCCCC, 0}};  // Разные биты
  float dst;
  ck_assert_int_eq(s21_from_decimal_to_float(src, &dst), 0);
  // Конкретное значение можно проверить с помощью калькулятора
  ck_assert_float_ne(dst, 0.0);
}
END_TEST

Suite *suite_s21_from_decimal_to_float(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_from_decimal_to_float");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_from_decimal_to_float_null_dst);
  tcase_add_test(tc_core, test_from_decimal_to_float_incorrect_decimal);
  tcase_add_test(tc_core, test_from_decimal_to_float_zero);
  tcase_add_test(tc_core, test_from_decimal_to_float_negative_zero);
  tcase_add_test(tc_core, test_from_decimal_to_float_positive);
  tcase_add_test(tc_core, test_from_decimal_to_float_negative);
  tcase_add_test(tc_core, test_from_decimal_to_float_with_power);
  tcase_add_test(tc_core, test_from_decimal_to_float_max_value);
  tcase_add_test(tc_core, test_from_decimal_to_float_different_bits);

  suite_add_tcase(s, tc_core);

  return s;
}

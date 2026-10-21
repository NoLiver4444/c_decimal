#include <check.h>
#include <math.h>

#include "../../s21_decimal.h"

START_TEST(test_float_to_decimal_null) {
  float src = 123.456f;
  ck_assert_int_eq(s21_from_float_to_decimal(src, NULL), 1);
}
END_TEST

START_TEST(test_float_to_decimal_zero) {
  float src = 0.0f;
  s21_decimal result;
  s21_decimal expected = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_from_float_to_decimal(src, &result), 0);
  ck_assert(s21_is_equal(result, expected));
}
END_TEST

START_TEST(test_float_to_decimal_negative_zero) {
  float src = -0.0f;
  s21_decimal result;
  s21_decimal expected = {{0, 0, 0, 0x80000000}};
  ck_assert_int_eq(s21_from_float_to_decimal(src, &result), 0);
  ck_assert(s21_is_equal(result, expected));
}
END_TEST

START_TEST(test_float_to_decimal_inf) {
  float src = INFINITY;
  s21_decimal result;
  ck_assert_int_eq(s21_from_float_to_decimal(src, &result), 1);
}
END_TEST

START_TEST(test_float_to_decimal_negative_inf) {
  float src = -INFINITY;
  s21_decimal result;
  ck_assert_int_eq(s21_from_float_to_decimal(src, &result), 1);
}
END_TEST

START_TEST(test_float_to_decimal_nan) {
  float src = NAN;
  s21_decimal result;
  ck_assert_int_eq(s21_from_float_to_decimal(src, &result), 1);
}
END_TEST

START_TEST(test_float_to_decimal_too_large) {
  float src = 1e29f;
  s21_decimal result;
  ck_assert_int_eq(s21_from_float_to_decimal(src, &result), 1);
}
END_TEST

START_TEST(test_float_to_decimal_too_small) {
  float src = 1e-29f;
  s21_decimal result;
  ck_assert_int_eq(s21_from_float_to_decimal(src, &result), 1);
}
END_TEST

START_TEST(test_float_to_decimal_normal) {
  float src = 123.456f;
  s21_decimal result;
  ck_assert_int_eq(s21_from_float_to_decimal(src, &result), 0);
  // Проверка значения можно добавить, если есть функция конвертации обратно в
  // float
}
END_TEST

START_TEST(test_float_to_decimal_small_precision) {
  float src = 1.23456e-20f;
  s21_decimal result;
  ck_assert_int_eq(s21_from_float_to_decimal(src, &result), 0);
}
END_TEST

// Тест на обработку денормализованных чисел
START_TEST(test_float_to_decimal_denormalized) {
  float src = 1.4e-45f;  // Денормализованное число
  s21_decimal result;
  ck_assert_int_eq(s21_from_float_to_decimal(src, &result), 1);
  // Результат должен быть нулем
  ck_assert(s21_is_equal(result, s21_decimal_get_zero()));
}
END_TEST

Suite *suite_s21_from_float_to_decimal(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_from_float_to_decimal");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_float_to_decimal_null);
  tcase_add_test(tc_core, test_float_to_decimal_zero);
  tcase_add_test(tc_core, test_float_to_decimal_negative_zero);
  tcase_add_test(tc_core, test_float_to_decimal_inf);
  tcase_add_test(tc_core, test_float_to_decimal_negative_inf);
  tcase_add_test(tc_core, test_float_to_decimal_nan);
  tcase_add_test(tc_core, test_float_to_decimal_too_large);
  tcase_add_test(tc_core, test_float_to_decimal_too_small);
  tcase_add_test(tc_core, test_float_to_decimal_normal);
  tcase_add_test(tc_core, test_float_to_decimal_small_precision);
  tcase_add_test(tc_core, test_float_to_decimal_denormalized);

  suite_add_tcase(s, tc_core);

  return s;
}

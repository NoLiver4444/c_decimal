#include <check.h>

#include "../../s21_decimal.h"

// Тесты для s21_decimal_get_from_char
START_TEST(test_decimal_get_from_char_0) {
  s21_decimal result = s21_decimal_get_from_char('0');
  s21_decimal expected = s21_decimal_get_zero();
  ck_assert(s21_is_equal(result, expected));
}
END_TEST

START_TEST(test_decimal_get_from_char_1) {
  s21_decimal result = s21_decimal_get_from_char('1');
  s21_decimal expected = s21_decimal_get_one();
  ck_assert(s21_is_equal(result, expected));
}
END_TEST

START_TEST(test_decimal_get_from_char_2_to_9) {
  char digits[] = "23456789";
  for (int i = 0; i < 8; i++) {
    s21_decimal result = s21_decimal_get_from_char(digits[i]);
    s21_decimal expected;
    s21_from_int_to_decimal(digits[i] - '0', &expected);
    ck_assert(s21_is_equal(result, expected));
  }
}
END_TEST

// Тесты для s21_get_float_exp_from_string
START_TEST(test_get_float_exp_from_string_positive) {
  char *str = "1.23456E+5";
  int exp = s21_get_float_exp_from_string(str);
  ck_assert_int_eq(exp, 5);
}
END_TEST

START_TEST(test_get_float_exp_from_string_negative) {
  char *str = "1.23456E-7";
  int exp = s21_get_float_exp_from_string(str);
  ck_assert_int_eq(exp, -7);
}
END_TEST

START_TEST(test_get_float_exp_from_string_zero) {
  char *str = "1.23456E0";
  int exp = s21_get_float_exp_from_string(str);
  ck_assert_int_eq(exp, 0);
}
END_TEST

START_TEST(test_get_float_exp_from_string_no_exp) {
  char *str = "1.23456";
  int exp = s21_get_float_exp_from_string(str);
  ck_assert_int_eq(exp, 0);
}
END_TEST

// Тесты для s21_float_string_to_decimal
START_TEST(test_float_string_to_decimal_positive) {
  char *str = "1.23456E0";
  s21_decimal result = s21_float_string_to_decimal(str);

  s21_decimal expected;
  s21_from_float_to_decimal(1.23456f, &expected);

  ck_assert(s21_is_equal(result, expected));
}
END_TEST

START_TEST(test_float_string_to_decimal_positive_exp) {
  char *str = "1.23456E2";
  s21_decimal result = s21_float_string_to_decimal(str);

  s21_decimal expected;
  s21_from_float_to_decimal(123.456f, &expected);

  ck_assert(s21_is_equal(result, expected));
}
END_TEST

START_TEST(test_float_string_to_decimal_negative_exp) {
  char *str = "1.23456E-2";
  s21_decimal result = s21_float_string_to_decimal(str);

  s21_decimal expected;
  s21_from_float_to_decimal(0.0123456f, &expected);

  ck_assert(s21_is_equal(result, expected));
}
END_TEST

START_TEST(test_float_string_to_decimal_small_negative_exp) {
  char *str = "1.23456E-29";
  s21_decimal result = s21_float_string_to_decimal(str);

  // Проверяем, что работает ветка для очень маленьких степеней (< -28)
  s21_decimal expected = s21_decimal_get_zero();

  ck_assert(s21_is_equal(result, expected));
}
END_TEST

// Тесты для s21_decimal_get_power
START_TEST(test_decimal_get_power) {
  s21_decimal dec = {{123, 0, 0, 0}};
  decimal_bit3 bits3;
  bits3.i = 0;
  bits3.parts.power = 5;
  dec.bits[3] = bits3.i;

  int power = s21_decimal_get_power(dec);
  ck_assert_int_eq(power, 5);
}
END_TEST

START_TEST(test_decimal_get_power_zero) {
  s21_decimal dec = {{123, 0, 0, 0}};

  int power = s21_decimal_get_power(dec);
  ck_assert_int_eq(power, 0);
}
END_TEST

// Тесты для s21_decimal_set_sign
START_TEST(test_decimal_set_sign_positive) {
  s21_decimal dec = {{123, 0, 0, 0}};
  s21_decimal_set_sign(&dec, S21_POSITIVE);

  decimal_bit3 bits3;
  bits3.i = dec.bits[3];

  ck_assert_int_eq(bits3.parts.sign, S21_POSITIVE);
}
END_TEST

START_TEST(test_decimal_set_sign_negative) {
  s21_decimal dec = {{123, 0, 0, 0}};
  s21_decimal_set_sign(&dec, S21_NEGATIVE);

  decimal_bit3 bits3;
  bits3.i = dec.bits[3];

  ck_assert_int_eq(bits3.parts.sign, S21_NEGATIVE);
}
END_TEST

// Тесты для s21_decimal_get_int_max
START_TEST(test_decimal_get_int_max) {
  s21_decimal max = s21_decimal_get_int_max();

  ck_assert_uint_eq(max.bits[0], 0x7FFFFFFF);
  ck_assert_uint_eq(max.bits[1], 0x0);
  ck_assert_uint_eq(max.bits[2], 0x0);
  ck_assert_uint_eq(max.bits[3], 0x0);

  int value;
  s21_from_decimal_to_int(max, &value);
  ck_assert_int_eq(value, 2147483647);
}
END_TEST

// Тесты для s21_decimal_get_int_min
START_TEST(test_decimal_get_int_min) {
  s21_decimal min = s21_decimal_get_int_min();

  ck_assert_uint_eq(min.bits[1], 0x0);
  ck_assert_uint_eq(min.bits[2], 0x0);

  int value;
  s21_from_decimal_to_int(min, &value);
  ck_assert_int_eq(value, -2147483648);
}
END_TEST

// Тест для проверки нулевого указателя в строке для float_string_to_decimal
START_TEST(test_float_string_to_decimal_null_pointer) {
  s21_decimal result = s21_float_string_to_decimal(NULL);
  s21_decimal expected = s21_decimal_get_zero();
  ck_assert(s21_is_equal(result, expected));
}
END_TEST

// Тест для проверки пустой строки
START_TEST(test_float_string_to_decimal_empty_string) {
  s21_decimal result = s21_float_string_to_decimal("");
  s21_decimal expected = s21_decimal_get_zero();
  ck_assert(s21_is_equal(result, expected));
}
END_TEST

// Тест для проверки строки с некорректным форматом
START_TEST(test_float_string_to_decimal_invalid_format) {
  s21_decimal result = s21_float_string_to_decimal("abc");
  s21_decimal expected = s21_decimal_get_zero();
  ck_assert(s21_is_equal(result, expected));
}
END_TEST

// Создание тестового набора
Suite *suite_transformation_helpers(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("transformation_helpers");
  tc_core = tcase_create("Core");

  // Тесты для s21_decimal_get_from_char
  tcase_add_test(tc_core, test_decimal_get_from_char_0);
  tcase_add_test(tc_core, test_decimal_get_from_char_1);
  tcase_add_test(tc_core, test_decimal_get_from_char_2_to_9);

  // Тесты для s21_get_float_exp_from_string
  tcase_add_test(tc_core, test_get_float_exp_from_string_positive);
  tcase_add_test(tc_core, test_get_float_exp_from_string_negative);
  tcase_add_test(tc_core, test_get_float_exp_from_string_zero);
  tcase_add_test(tc_core, test_get_float_exp_from_string_no_exp);

  // Тесты для s21_float_string_to_decimal
  tcase_add_test(tc_core, test_float_string_to_decimal_positive);
  tcase_add_test(tc_core, test_float_string_to_decimal_positive_exp);
  tcase_add_test(tc_core, test_float_string_to_decimal_negative_exp);
  tcase_add_test(tc_core, test_float_string_to_decimal_small_negative_exp);

  // Тесты для s21_decimal_get_power
  tcase_add_test(tc_core, test_decimal_get_power);
  tcase_add_test(tc_core, test_decimal_get_power_zero);

  // Тесты для s21_decimal_set_sign
  tcase_add_test(tc_core, test_decimal_set_sign_positive);
  tcase_add_test(tc_core, test_decimal_set_sign_negative);

  // Тесты для s21_decimal_get_int_max и s21_decimal_get_int_min
  tcase_add_test(tc_core, test_decimal_get_int_max);
  tcase_add_test(tc_core, test_decimal_get_int_min);

  // Тесты для s21_float_string_to_decimal
  tcase_add_test(tc_core, test_float_string_to_decimal_null_pointer);
  tcase_add_test(tc_core, test_float_string_to_decimal_empty_string);
  tcase_add_test(tc_core, test_float_string_to_decimal_invalid_format);

  suite_add_tcase(s, tc_core);

  return s;
}

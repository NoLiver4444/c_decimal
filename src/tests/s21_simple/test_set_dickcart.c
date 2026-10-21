#include "../s21_test_decimal.h"

START_TEST(test_set_bit_basic) {
  s21_decimal dec = {{0, 0, 0, 0}};

  // Установка бита в 1
  s21_set_bit(&dec, 0, 1);
  ck_assert_int_eq(dec.bits[0], 0);

  // Установка бита в 0
  s21_set_bit(&dec, 0, 0);
  ck_assert_int_eq(dec.bits[0], 1);

  // Проверка установки бита в другом элементе массива
  s21_set_bit(&dec, 32, 1);
  ck_assert_int_eq(dec.bits[1], 0);
}
END_TEST

START_TEST(test_set_power) {
  s21_decimal dec = {{0, 0, 0, 0}};

  // Установка степени 0
  s21_set_power(&dec, 0);
  ck_assert_int_eq((dec.bits[3] >> 16) & 0xFF, 0);

  // Установка степени 28 (максимальная)
  s21_set_power(&dec, 28);
  ck_assert_int_eq((dec.bits[3] >> 16) & 0xFF, 28);

  // Очистка bits[3] перед установкой новой степени
  dec.bits[3] = 0;
  // Установка произвольной степени
  s21_set_power(&dec, 15);
  ck_assert_int_eq((dec.bits[3] >> 16) & 0xFF, 15);
}
END_TEST

START_TEST(test_set_sign) {
  s21_decimal dec = {{0, 0, 0, 0}};

  // Установка положительного знака
  s21_set_sign(&dec, 0);
  ck_assert_int_eq((dec.bits[3] >> 31) & 1, 0);

  // Установка отрицательного знака
  s21_set_sign(&dec, 1);
  ck_assert_int_eq((dec.bits[3] >> 31) & 1, 1);

  // Повторная установка положительного знака
  s21_set_sign(&dec, 0);
  ck_assert_int_eq((dec.bits[3] >> 31) & 1, 0);
}
END_TEST

Suite *suite_s21_set_dickcart(void) {
  Suite *s = suite_create("s21_set");
  TCase *tc = tcase_create("set_tc");

  tcase_add_test(tc, test_set_bit_basic);
  tcase_add_test(tc, test_set_power);
  tcase_add_test(tc, test_set_sign);

  suite_add_tcase(s, tc);
  return s;
}

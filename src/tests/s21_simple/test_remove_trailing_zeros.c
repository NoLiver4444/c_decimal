#include "../s21_test_decimal.h"

// Тест на удаление нулей из числа с масштабом
START_TEST(test_remove_trailing_zeros_basic) {
  s21_decimal dec = {{1000, 0, 0, 0x30000}};  // 1000 с масштабом 3 (1.000)
  s21_remove_trailing_zeros_arnoldea(&dec);

  // Проверяем, что значение осталось 1, а масштаб стал 0
  ck_assert_int_eq(dec.bits[0], 1);
  ck_assert_int_eq(dec.bits[1], 0);
  ck_assert_int_eq(dec.bits[2], 0);
  ck_assert_int_eq((dec.bits[3] >> 16) & 0xFF, 0);  // Проверка масштаба
}

Suite *remove_trailing_zeros_suite(void) {
  Suite *s = suite_create("Remove Trailing Zeros");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_remove_trailing_zeros_basic);

  suite_add_tcase(s, tc_core);
  return s;
}

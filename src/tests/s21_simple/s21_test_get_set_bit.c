#include "../s21_test_decimal.h"

START_TEST(get_set_bit_one_position_1) {
  s21_decimal value = {{0, 0, 0, 0}};
  s21_set_bit_arnoldea(&value, 0, 1);
  ck_assert_int_eq(s21_get_bit_arnoldea(&value, 0), 1);
}
END_TEST

START_TEST(get_set_bit_one_position_2) {
  s21_decimal value = {{1, 0, 0, 0}};
  s21_set_bit_arnoldea(&value, 0, 0);
  ck_assert_int_eq(s21_get_bit_arnoldea(&value, 0), 0);
}
END_TEST

START_TEST(get_set_bit_last_position) {
  s21_decimal value = {{0, 0, 0, 0}};
  s21_set_bit_arnoldea(&value, 127, 1);
  ck_assert_int_eq(s21_get_bit_arnoldea(&value, 127), 1);
}
END_TEST

Suite *suite_s21_get_set_bit(void) {
  Suite *suite = suite_create("s21_get_set_bit_suite");
  TCase *tcase_core = tcase_create("s21_get_set_bit_tc");

  tcase_add_test(tcase_core, get_set_bit_one_position_1);
  tcase_add_test(tcase_core, get_set_bit_one_position_2);
  tcase_add_test(tcase_core, get_set_bit_last_position);

  suite_add_tcase(suite, tcase_core);
  return suite;
}

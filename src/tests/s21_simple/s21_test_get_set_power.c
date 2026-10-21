#include "../s21_test_decimal.h"

START_TEST(get_set_power_1) {
  s21_decimal value = {{0, 0, 0, 0}};
  s21_set_power_arnoldea(&value, 1);
  ck_assert_int_eq(s21_get_power_arnoldea(&value), 1);
}
END_TEST

START_TEST(get_set_power_2) {
  s21_decimal value = {{0, 0, 0, 0}};
  s21_set_power_arnoldea(&value, 28);
  ck_assert_int_eq(s21_get_power_arnoldea(&value), 28);
}
END_TEST

START_TEST(get_set_power_with_sign) {
  s21_decimal value = {{0, 0, 0, 0}};
  s21_set_sign_arnoldea(&value, 1);
  s21_set_power_arnoldea(&value, 28);
  ck_assert_int_eq(s21_get_power_arnoldea(&value), 28);
  ck_assert_int_eq(s21_get_sign_arnoldea(&value), 1);
}
END_TEST

Suite *suite_s21_get_set_power(void) {
  Suite *suite = suite_create("s21_get_set_power_suite");
  TCase *tcase_core = tcase_create("s21_get_set_power_tc");

  tcase_add_test(tcase_core, get_set_power_1);
  tcase_add_test(tcase_core, get_set_power_2);
  tcase_add_test(tcase_core, get_set_power_with_sign);
  suite_add_tcase(suite, tcase_core);
  return suite;
}

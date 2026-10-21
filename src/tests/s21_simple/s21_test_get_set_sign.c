#include "../s21_test_decimal.h"

START_TEST(get_set_sign_positive) {
  s21_decimal value = {{0, 0, 0, 0}};
  s21_set_sign_arnoldea(&value, 0);
  ck_assert_int_eq(s21_get_sign_arnoldea(&value), 0);
}
END_TEST

START_TEST(get_set_sign_negative) {
  s21_decimal value = {{0, 0, 0, 0}};
  s21_set_sign_arnoldea(&value, 1);
  ck_assert_int_eq(s21_get_sign_arnoldea(&value), 1);
}
END_TEST

Suite *suite_s21_get_set_sign(void) {
  Suite *suite = suite_create("s21_get_set_sign_suite");
  TCase *tcase_core = tcase_create("s21_get_set_sign_tc");

  tcase_add_test(tcase_core, get_set_sign_positive);
  tcase_add_test(tcase_core, get_set_sign_negative);

  suite_add_tcase(suite, tcase_core);
  return suite;
}

#include "../s21_test_decimal.h"

START_TEST(test_negate_positive) {
  s21_decimal value = {{123, 0, 0, 0}};  // Положительное число
  s21_decimal result;

  int code = s21_negate(value, &result);

  ck_assert_int_eq(code, S21_OTHER_OK);
  ck_assert_int_eq(s21_get_sign(&result),
                   1);  // Проверяем что знак стал отрицательным
  ck_assert_int_eq(result.bits[0],
                   123);  // Проверяем что значение не изменилось
}
END_TEST

START_TEST(test_negate_negative) {
  s21_decimal value = {{123, 0, 0, 0x80000000}};  // Отрицательное число
  s21_decimal result;

  int code = s21_negate(value, &result);

  ck_assert_int_eq(code, S21_OTHER_OK);
  ck_assert_int_eq(s21_get_sign(&result),
                   0);  // Проверяем что знак стал положительным
  ck_assert_int_eq(result.bits[0],
                   123);  // Проверяем что значение не изменилось
}
END_TEST

START_TEST(test_negate_zero) {
  s21_decimal value = {{0, 0, 0, 0}};  // Ноль
  s21_decimal result;

  int code = s21_negate(value, &result);

  ck_assert_int_eq(code, S21_OTHER_OK);
  ck_assert_int_eq(s21_get_sign(&result), 1);  // Проверяем что знак изменился
  ck_assert_int_eq(result.bits[0], 0);  // Проверяем что значение осталось нулем
}
END_TEST

START_TEST(test_negate_null_pointer) {
  s21_decimal value = {{123, 0, 0, 0}};

  int code = s21_negate(value, NULL);

  ck_assert_int_eq(code, S21_OTHER_ERROR);
}
END_TEST

START_TEST(test_negate_incorrect_decimal) {
  s21_decimal value = {{123, 0, 0, 0x001C0000}};  // Некорректная степень
  s21_decimal result;

  int code = s21_negate(value, &result);

  ck_assert_int_eq(code, S21_OTHER_OK);
  // Проверяем что знак все равно изменился
  ck_assert_int_eq(s21_get_sign(&result), 1);
}
END_TEST
Suite *suite_s21_negate(void) {
  Suite *s = suite_create("s21_negate");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, test_negate_positive);
  tcase_add_test(tc, test_negate_negative);
  tcase_add_test(tc, test_negate_zero);
  tcase_add_test(tc, test_negate_null_pointer);
  tcase_add_test(tc, test_negate_incorrect_decimal);

  suite_add_tcase(s, tc);
  return s;
}

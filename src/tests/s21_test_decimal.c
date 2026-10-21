#include "s21_test_decimal.h"

int run_test(Suite *test_case);

int main(void) {
  run_test(add_suite());
  run_test(sub_suite());
  run_test(mul_suite());
  run_test(div_suite());
  // s21_arithmetic
  // s21_comparison
  // s21_other
  // s21_simple
  // s21_transformation

  // s21_arithmetic

  // s21_comparison
  run_test(suite_s21_is_equal());
  run_test(suite_s21_is_greater_or_equal());
  run_test(suite_s21_is_greater());
  run_test(suite_s21_is_less_or_equal());
  run_test(suite_s21_is_less());
  run_test(suite_s21_is_not_equal());

  // s21_other
  run_test(suite_s21_floor());
  run_test(suite_s21_negate());
  run_test(suite_s21_round());
  run_test(suite_s21_truncate());

  // s21_simple
  run_test(suite_s21_get_set_bit());
  run_test(suite_s21_get_set_power());
  run_test(suite_s21_get_set_sign());
  run_test(suite_s21_get_bit_dickcart());
  run_test(suite_s21_get_power_dickcart());
  run_test(suite_s21_get_sign_dickcart());
  run_test(suite_s21_set_dickcart());
  run_test(suite_transformation_helpers());
  run_test(remove_trailing_zeros_suite());

  // s21_transformation
  run_test(suite_s21_from_decimal_to_float());
  run_test(suite_s21_from_decimal_to_int());
  run_test(suite_s21_from_int_to_decimal());
  run_test(suite_s21_from_float_to_decimal());

  return 0;
}

/**
 * The run_test function executes the tests defined in the provided test suite.
 *
 * @param test_case A pointer to the test suite that will be executed.
 * @return Returns EXIT_SUCCESS if all tests passed successfully,
 *         otherwise returns EXIT_FAILURE.
 */
int run_test(Suite *test_case) {
  int failed_count;
  SRunner *suite_runner = srunner_create(test_case);

  srunner_run_all(suite_runner, CK_NORMAL);
  failed_count = srunner_ntests_failed(suite_runner);
  srunner_free(suite_runner);
  putchar('\n');

  return (failed_count == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

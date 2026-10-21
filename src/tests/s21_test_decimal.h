#ifndef SRC_TESTS_S21_TEST_DECIMAL_H
#define SRC_TESTS_S21_TEST_DECIMAL_H

#include <check.h>
#include <stdlib.h>

// Project libraries
#include "../s21_decimal.h"
#include "../s21_decimal/s21_simple/simple_arnoldea/s21_simple_arnoldea.h"

// s21_arithmetic
Suite *add_suite(void);
Suite *sub_suite(void);
Suite *mul_suite(void);
Suite *div_suite(void);

void test_add(s21_decimal decimal1, s21_decimal decimal2, s21_decimal check);
void test_add_fail(s21_decimal decimal1, s21_decimal decimal2, int check);
void test_sub(s21_decimal decimal1, s21_decimal decimal2, s21_decimal check);
void test_sub_fail(s21_decimal decimal1, s21_decimal decimal2, int check);
void test_mul(s21_decimal decimal1, s21_decimal decimal2, s21_decimal check);
void test_mul_fail1(s21_decimal decimal1, s21_decimal decimal2, int code_check);
void test_mul_fail2(s21_decimal decimal1, s21_decimal decimal2,
                    s21_decimal decimal_check, int code_check);
void test_div(s21_decimal decimal1, s21_decimal decimal2, s21_decimal check);
void test_div_fail1(s21_decimal decimal1, s21_decimal decimal2, int code_check);
void test_div_fail2(s21_decimal decimal1, s21_decimal decimal2,
                    s21_decimal decimal_check, int code_check);

// s21_comparison
Suite *suite_s21_is_equal(void);
Suite *suite_s21_is_greater_or_equal(void);
Suite *suite_s21_is_greater(void);
Suite *suite_s21_is_less_or_equal(void);
Suite *suite_s21_is_less(void);
Suite *suite_s21_is_not_equal(void);

// s21_other
Suite *suite_s21_floor(void);
Suite *suite_s21_negate(void);
Suite *suite_s21_round(void);
Suite *suite_s21_truncate(void);

// s21_simple
Suite *suite_s21_get_set_bit(void);
Suite *suite_s21_get_set_power(void);
Suite *suite_s21_get_set_sign(void);
Suite *suite_s21_get_bit_dickcart(void);
Suite *suite_s21_get_power_dickcart(void);
Suite *suite_s21_get_sign_dickcart(void);
Suite *suite_s21_set_dickcart(void);
Suite *suite_transformation_helpers(void);
Suite *remove_trailing_zeros_suite(void);

// s21_transformation
Suite *suite_s21_from_decimal_to_float(void);
Suite *suite_s21_from_decimal_to_int(void);
Suite *suite_s21_from_int_to_decimal(void);
Suite *suite_s21_from_float_to_decimal(void);
#endif  // SRC_TESTS_S21_TEST_DECIMAL_H

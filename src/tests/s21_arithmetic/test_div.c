#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "./../../s21_decimal.h"
#include "./../s21_test_decimal.h"

START_TEST(test_fail_manual_1) {
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};

  int code = s21_div(decimal1, decimal2, NULL);

  ck_assert_int_ne(code, S21_ARITHMETIC_OK);
}

START_TEST(test_fail_manual_2) {
  s21_decimal decimal1 = {{0, 0, 0, 1000000000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};

  s21_decimal result;

  int code = s21_div(decimal1, decimal2, &result);

  ck_assert_int_ne(code, S21_ARITHMETIC_OK);
}

START_TEST(test_fail_manual_3) {
  s21_decimal decimal1 = {{-1, 0, 0, 0x1D0000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};

  s21_decimal result;

  int code = s21_div(decimal1, decimal2, &result);

  ck_assert_int_ne(code, S21_ARITHMETIC_OK);
}

START_TEST(test_fail_manual_4) {
  s21_decimal decimal1 = {{0, 0, 0, 0x1D0000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};

  s21_decimal result;

  int code = s21_div(decimal1, decimal2, &result);

  ck_assert_int_ne(code, S21_ARITHMETIC_OK);
}

START_TEST(test_fail_manual_5) {
  s21_decimal decimal1 = {{-1, 0, 0, 0x1C0001}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};

  s21_decimal result;

  int code = s21_div(decimal1, decimal2, &result);

  ck_assert_int_ne(code, S21_ARITHMETIC_OK);
}

START_TEST(test_fail_manual_6) {
  s21_decimal decimal1 = {{-1, 0, 0, 0x1C8000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};

  s21_decimal result;

  int code = s21_div(decimal1, decimal2, &result);

  ck_assert_int_ne(code, S21_ARITHMETIC_OK);
}

START_TEST(test_fail_manual_7) {
  s21_decimal decimal1 = {{-1, 0, 0, 0x11C0000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};

  s21_decimal result;

  int code = s21_div(decimal1, decimal2, &result);

  ck_assert_int_ne(code, S21_ARITHMETIC_OK);
}

START_TEST(test_fail_manual_8) {
  s21_decimal decimal1 = {{-1, 0, 0, 0x401C0000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};

  s21_decimal result;

  int code = s21_div(decimal1, decimal2, &result);

  ck_assert_int_ne(code, S21_ARITHMETIC_OK);
}

START_TEST(test_fail_manual_9) {
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};

  s21_decimal result;

  int code = s21_div(decimal1, decimal2, &result);

  ck_assert_int_ne(code, S21_ARITHMETIC_OK);
}

START_TEST(test_fail_manual_10) {
  // 792281625.14264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  int code = s21_div(decimal1, decimal2, NULL);

  ck_assert_int_ne(code, S21_ARITHMETIC_OK);
}

START_TEST(test_fail_manual_11) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x80000000}};
  // division by zero
  int code_check = S21_ARITHMETIC_ZERO_DIV;

  test_div_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_fail_manual_12) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // overflow
  int code_check = S21_ARITHMETIC_BIG;

  test_div_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_fail_manual_13) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x801C0000}};
  // overflow
  int code_check = S21_ARITHMETIC_SMALL;

  test_div_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_fail_manual_14) {
  // 0.0000000000000000000000000001
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // -79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};
  int code_check = S21_ARITHMETIC_SMALL;

  test_div_fail2(decimal1, decimal2, decimal_check, code_check);
}

START_TEST(test_fail_manual_15) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // 39614081257132168796771975168
  s21_decimal decimal2 = {{0x0, 0x0, 0x80000000, 0x0}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};
  int code_check = S21_ARITHMETIC_SMALL;

  test_div_fail2(decimal1, decimal2, decimal_check, code_check);
}

START_TEST(test_fail_manual_16) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x801C0000}};
  // overflow
  int code_check = S21_ARITHMETIC_SMALL;

  test_div_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_div_1) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -1.0
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x80010000}};
  // 79228162514264337593543950335
  s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div_2) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 10
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x0}};
  // -7922816251426433759354395033.5
  s21_decimal decimal_check = {
      {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div_3) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x0}};
  // division by zero
  int code_check = S21_ARITHMETIC_ZERO_DIV;

  test_div_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_div_4) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -0.0000000000000000000000000000
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x801C0000}};
  // division by zero
  int code_check = S21_ARITHMETIC_ZERO_DIV;

  test_div_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_div_5) {
  // -79228162495817593524129366015
  s21_decimal decimal1 = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x80000000}};
  // -3656273013.5441854660747245473
  s21_decimal decimal2 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x80130000}};
  // 21669104632593688025.07401738
  s21_decimal decimal_check = {{0x8BE1AA0A, 0x97A57D66, 0x7006D23, 0x80000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div_7) {
  // 8460.288
  s21_decimal decimal1 = {{0x811800, 0x0, 0x0, 0x30000}};
  // -2
  s21_decimal decimal2 = {{0x2, 0x0, 0x0, 0x80000000}};
  // -4230.144
  s21_decimal decimal_check = {{0x408C00, 0x0, 0x0, 0x80030000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div_8) {
  // 8460.288
  s21_decimal decimal1 = {{0x811800, 0x0, 0x0, 0x30000}};
  // -1.001
  s21_decimal decimal2 = {{0x3E9, 0x0, 0x0, 0x80030000}};
  // -8451.836163836163836163836164
  s21_decimal decimal_check = {
      {0xA6BEC904, 0x84217DAC, 0x1B4F31EC, 0x80180000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div_9) {
  // -0.0000000000000000000000000010
  s21_decimal decimal1 = {{0xA, 0x0, 0x0, 0x801C0000}};
  // -42.94967296
  s21_decimal decimal2 = {{0x0, 0x1, 0x0, 0x80080000}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};
  int code_check = S21_ARITHMETIC_SMALL;

  test_div_fail2(decimal1, decimal2, decimal_check, code_check);
}

START_TEST(test_div_10) {
  // 0.9999999999999999999999999999
  s21_decimal decimal1 = {{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x1C0000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};
  int code_check = S21_ARITHMETIC_SMALL;

  test_div_fail2(decimal1, decimal2, decimal_check, code_check);
}

START_TEST(test_div_11) {
  // 39614081257132168798919458816
  s21_decimal decimal1 = {{0x80000000, 0x0, 0x80000000, 0x0}};
  // -79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -0.5000000000000000000271050543
  s21_decimal decimal_check = {
      {0x9827E72F, 0x1F128130, 0x1027E72F, 0x801C0000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div_12) {
  // 39614081257132168796771975168
  s21_decimal decimal1 = {{0x0, 0x0, 0x80000000, 0x0}};
  // -79228162514264337593543950334
  s21_decimal decimal2 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -0.5
  s21_decimal decimal_check = {{0x5, 0x0, 0x0, 0x80010000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div_13) {
  // 39614081257132168796771975168
  s21_decimal decimal1 = {{0x0, 0x0, 0x80000000, 0x0}};
  // 79228162514264337593543950334
  s21_decimal decimal2 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0.5
  s21_decimal decimal_check = {{0x5, 0x0, 0x0, 0x10000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div_14) {
  // 0.0000000000000000000000000001
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // -79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};
  int code_check = S21_ARITHMETIC_SMALL;

  test_div_fail2(decimal1, decimal2, decimal_check, code_check);
}

START_TEST(test_div_by_one) {
  s21_decimal decimal1 = {{0xA, 0x0, 0x0, 0x0}};  // 10
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x0}};  // 1
  s21_decimal result;

  int code = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(code, S21_ARITHMETIC_OK);
  ck_assert_int_eq(s21_is_equal_dickcart(result, decimal1), 1);
}

START_TEST(test_div_by_negative_one) {
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};  // 10
  s21_decimal decimal2 = {
      {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};  // -1
  s21_decimal result;

  int code = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(code, S21_ARITHMETIC_OK);
  s21_decimal expected = {{0x1, 0x0, 0x0, 0x80000000}};  // -10
  ck_assert_int_eq(s21_is_equal_dickcart(result, expected), 1);
}

START_TEST(test_div_positive_numbers) {
  s21_decimal decimal1 = {{0xA, 0x0, 0x0, 0x0}};  // 10
  s21_decimal decimal2 = {{0x2, 0x0, 0x0, 0x0}};  // 2
  s21_decimal result;

  int code = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(code, S21_ARITHMETIC_OK);
  s21_decimal expected = {{0x5, 0x0, 0x0, 0x0}};  // 5
  ck_assert_int_eq(s21_is_equal_dickcart(result, expected), 1);
}

START_TEST(test_div_positive_negative) {
  s21_decimal decimal1 = {{0xA, 0x0, 0x0, 0x0}};  // 10
  s21_decimal decimal2 = {
      {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};  // -1
  s21_decimal result;

  int code = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(code, S21_ARITHMETIC_OK);
  s21_decimal expected = {{0x1, 0x0, 0x0, 0x801C0000}};  // -10
  ck_assert_int_eq(s21_is_equal_dickcart(result, expected), 1);
}

START_TEST(test_div_negative_positive) {
  s21_decimal decimal1 = {
      {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};               // -10
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};  // 2
  s21_decimal result;

  int code = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(code, S21_ARITHMETIC_OK);
  s21_decimal expected = {{0x3, 0x0, 0x0, 0x80000000}};  // -5
  ck_assert_int_eq(s21_is_equal_dickcart(result, expected), 1);
}

START_TEST(test_div_large_number_by_small) {
  s21_decimal decimal1 = {{0xA, 0x0, 0x0, 0x0}};  // 10
  s21_decimal decimal2 = {
      {0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x801C0000}};  // 1000000000
  s21_decimal result;

  int code = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(code, S21_ARITHMETIC_OK);
  s21_decimal expected = {
      {0x10000001, 0x3E250261, 0x204FCE5E, 0x801B0000}};  // 0
  ck_assert_int_eq(s21_is_equal_dickcart(result, expected), 1);
}

START_TEST(test_div_with_remainder) {
  // 79228162495817593524129366015
  s21_decimal decimal1 = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x0}};
  // 10
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x0}};
  s21_decimal result;

  int code = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(code, S21_ARITHMETIC_OK);
  s21_decimal expected = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x10000}};  // 3
  ck_assert_int_eq(s21_is_equal_dickcart(result, expected), 1);
}

START_TEST(test_div_15) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x801C0000}};

  s21_decimal result;
  int code = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(code, TEST_ARITHMETIC_SMALL);
}

START_TEST(test_div_16) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x801C0000}};
  // overflow
  s21_decimal result;
  int code = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(code, TEST_ARITHMETIC_SMALL);
}

START_TEST(test_div_17) {
  // 1.0000000000000000000000000001
  s21_decimal decimal1 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x1C0000}};
  // 1.9999999999999999999999999999
  s21_decimal decimal2 = {{0x1FFFFFFF, 0x7C4A04C2, 0x409F9CBC, 0x1C0000}};

  s21_decimal result;
  int code = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(code, S21_ARITHMETIC_OK);
  // 0.5000000000000000000000000001
  s21_decimal expected = {{0x88000001, 0x1F128130, 0x1027E72F, 0x1C0000}};  // 3
  ck_assert_int_eq(s21_is_equal_dickcart(result, expected), 1);
}

START_TEST(test_div_18) {
  // -5
  s21_decimal decimal1 = {{0x5, 0x0, 0x0, 0x80000000}};
  // -1.9999999999999999999999999999
  s21_decimal decimal2 = {{0x1FFFFFFF, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};

  s21_decimal result;
  int code = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(code, S21_ARITHMETIC_OK);
  // 2.5000000000000000000000000001
  s21_decimal expected = {{0xA8000001, 0x9B5C85F2, 0x50C783EB, 0x1C0000}};  // 3
  ck_assert_int_eq(s21_is_equal_dickcart(result, expected), 1);
}

START_TEST(test_div_19) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -1.0
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x80010000}};
  // 79228162514264337593543950335
  s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div_20) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 10
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x0}};
  // -7922816251426433759354395033.5
  s21_decimal decimal_check = {
      {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div_21) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x0}};
  // division by zero
  int code_check = S21_ARITHMETIC_ZERO_DIV;

  test_div_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_div_22) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -0.0000000000000000000000000000
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x801C0000}};
  // division by zero
  int code_check = S21_ARITHMETIC_ZERO_DIV;

  test_div_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_div_23) {
  // -79228162495817593524129366015
  s21_decimal decimal1 = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x80000000}};
  // -3656273013.5441854660747245473
  s21_decimal decimal2 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x80130000}};
  // 21669104632593688025.07401738
  s21_decimal decimal_check = {{0x8BE1AA0A, 0x97A57D66, 0x7006D23, 0x80000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div_24) {
  // 8460.288
  s21_decimal decimal1 = {{0x811800, 0x0, 0x0, 0x30000}};
  // -2
  s21_decimal decimal2 = {{0x2, 0x0, 0x0, 0x80000000}};
  // -4230.144
  s21_decimal decimal_check = {{0x408C00, 0x0, 0x0, 0x80030000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div_25) {
  // 8460.288
  s21_decimal decimal1 = {{0x811800, 0x0, 0x0, 0x30000}};
  // -1.001
  s21_decimal decimal2 = {{0x3E9, 0x0, 0x0, 0x80030000}};
  // -8451.836163836163836163836164
  s21_decimal decimal_check = {
      {0xA6BEC904, 0x84217DAC, 0x1B4F31EC, 0x80180000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div_26) {
  // -0.0000000000000000000000000010
  s21_decimal decimal1 = {{0xA, 0x0, 0x0, 0x801C0000}};
  // -42.94967296
  s21_decimal decimal2 = {{0x0, 0x1, 0x0, 0x80080000}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};
  int code_check = S21_ARITHMETIC_SMALL;

  test_div_fail2(decimal1, decimal2, decimal_check, code_check);
}

START_TEST(test_div_27) {
  // 0.9999999999999999999999999999
  s21_decimal decimal1 = {{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x1C0000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};
  int code_check = S21_ARITHMETIC_SMALL;

  test_div_fail2(decimal1, decimal2, decimal_check, code_check);
}

START_TEST(test_div_28) {
  // 39614081257132168798919458816
  s21_decimal decimal1 = {{0x80000000, 0x0, 0x80000000, 0x0}};
  // -79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -0.5000000000000000000271050543
  s21_decimal decimal_check = {
      {0x9827E72F, 0x1F128130, 0x1027E72F, 0x801C0000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div_29) {
  // 39614081257132168796771975168
  s21_decimal decimal1 = {{0x0, 0x0, 0x80000000, 0x0}};
  // -79228162514264337593543950334
  s21_decimal decimal2 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -0.5
  s21_decimal decimal_check = {{0x5, 0x0, 0x0, 0x80010000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div_30) {
  // 39614081257132168796771975168
  s21_decimal decimal1 = {{0x0, 0x0, 0x80000000, 0x0}};
  // 79228162514264337593543950334
  s21_decimal decimal2 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0.5
  s21_decimal decimal_check = {{0x5, 0x0, 0x0, 0x10000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div_31) {
  // 0.0000000000000000000000000001
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // -79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x80000000}};
  int code_check = S21_ARITHMETIC_SMALL;

  test_div_fail2(decimal1, decimal2, decimal_check, code_check);
}

START_TEST(test_div_32) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // overflow
  int code_check = TEST_ARITHMETIC_BIG;

  test_div_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_div_33) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0.9999999999999999999999999999
  s21_decimal decimal2 = {{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x1C0000}};
  // overflow
  int code_check = TEST_ARITHMETIC_BIG;

  test_div_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_div_34) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0.9999999999999999999999999999
  s21_decimal decimal2 = {{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  // overflow
  int code_check = TEST_ARITHMETIC_SMALL;

  test_div_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_div_manual_1) {
  // 79228162514264337593543950320
  s21_decimal decimal1 = {{0xFFFFFFF0, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0.9999999999999999999999999998
  s21_decimal decimal2 = {{0xFFFFFFE, 0x3E250261, 0x204FCE5E, 0x1C0000}};
  // overflow
  int code_check = TEST_ARITHMETIC_BIG;

  test_div_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_div_35) {
  // 4294967297
  s21_decimal decimal1 = {{0x1, 0x1, 0x0, 0x0}};
  // -1.9999999999999999999999999999
  s21_decimal decimal2 = {{0x1FFFFFFF, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  // -2147483648.5000000000000000001
  s21_decimal decimal_check = {
      {0x44F40001, 0x8A579182, 0x45639182, 0x80130000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div_36) {
  // -4294967297
  s21_decimal decimal1 = {{0x1, 0x1, 0x0, 0x80000000}};
  // 8589934591
  s21_decimal decimal2 = {{0xFFFFFFFF, 0x1, 0x0, 0x0}};
  // -0.5000000001746229827607310124
  s21_decimal decimal_check = {
      {0x42B9AF2C, 0x374E5BF7, 0x1027E72F, 0x801C0000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div_37) {
  // -4294967297
  s21_decimal decimal1 = {{0x1, 0x1, 0x0, 0x80000000}};
  // -2
  s21_decimal decimal2 = {{0x2, 0x0, 0x0, 0x80000000}};
  // 2147483648.5
  s21_decimal decimal_check = {{0x5, 0x5, 0x0, 0x10000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div_38) {
  // 8589934591
  s21_decimal decimal1 = {{0xFFFFFFFF, 0x1, 0x0, 0x0}};
  // 1.9999999999999999999999999999
  s21_decimal decimal2 = {{0x1FFFFFFF, 0x7C4A04C2, 0x409F9CBC, 0x1C0000}};
  // 4294967295.5000000000000000002
  s21_decimal decimal_check = {{0xBB0C0002, 0x44846E7D, 0x8AC72304, 0x130000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div_39) {
  // 5
  s21_decimal decimal1 = {{0x5, 0x0, 0x0, 0x0}};
  // -1.9999999999999999999999999999
  s21_decimal decimal2 = {{0x1FFFFFFF, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  // -2.5000000000000000000000000001
  s21_decimal decimal_check = {
      {0xA8000001, 0x9B5C85F2, 0x50C783EB, 0x801C0000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div_manual_2) {
  // -79228162514264337593543950320
  s21_decimal decimal1 = {{0xFFFFFFF0, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 0.9999999999999999999999999998
  s21_decimal decimal2 = {{0xFFFFFFE, 0x3E250261, 0x204FCE5E, 0x1C0000}};
  // overflow
  int code_check = TEST_ARITHMETIC_SMALL;

  test_div_fail1(decimal1, decimal2, code_check);
}

Suite *div_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("div");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_fail_manual_1);
  tcase_add_test(tc_core, test_fail_manual_2);
  tcase_add_test(tc_core, test_fail_manual_3);
  tcase_add_test(tc_core, test_fail_manual_4);
  tcase_add_test(tc_core, test_fail_manual_5);
  tcase_add_test(tc_core, test_fail_manual_6);
  tcase_add_test(tc_core, test_fail_manual_7);
  tcase_add_test(tc_core, test_fail_manual_8);
  tcase_add_test(tc_core, test_fail_manual_9);
  tcase_add_test(tc_core, test_fail_manual_10);
  tcase_add_test(tc_core, test_fail_manual_11);
  tcase_add_test(tc_core, test_fail_manual_12);
  tcase_add_test(tc_core, test_fail_manual_13);
  tcase_add_test(tc_core, test_fail_manual_14);
  tcase_add_test(tc_core, test_fail_manual_15);
  tcase_add_test(tc_core, test_fail_manual_16);
  tcase_add_test(tc_core, test_div_manual_1);
  tcase_add_test(tc_core, test_div_manual_2);

  tcase_add_test(tc_core, test_div_1);
  tcase_add_test(tc_core, test_div_2);
  tcase_add_test(tc_core, test_div_3);
  tcase_add_test(tc_core, test_div_4);
  tcase_add_test(tc_core, test_div_5);
  tcase_add_test(tc_core, test_div_7);
  tcase_add_test(tc_core, test_div_8);
  tcase_add_test(tc_core, test_div_9);
  tcase_add_test(tc_core, test_div_10);
  tcase_add_test(tc_core, test_div_11);
  tcase_add_test(tc_core, test_div_12);
  tcase_add_test(tc_core, test_div_13);
  tcase_add_test(tc_core, test_div_14);
  tcase_add_test(tc_core, test_div_15);
  tcase_add_test(tc_core, test_div_16);
  tcase_add_test(tc_core, test_div_17);
  tcase_add_test(tc_core, test_div_18);
  tcase_add_test(tc_core, test_div_19);
  tcase_add_test(tc_core, test_div_20);
  tcase_add_test(tc_core, test_div_21);
  tcase_add_test(tc_core, test_div_22);
  tcase_add_test(tc_core, test_div_23);
  tcase_add_test(tc_core, test_div_24);
  tcase_add_test(tc_core, test_div_25);
  tcase_add_test(tc_core, test_div_26);
  tcase_add_test(tc_core, test_div_27);
  tcase_add_test(tc_core, test_div_28);
  tcase_add_test(tc_core, test_div_29);
  tcase_add_test(tc_core, test_div_30);
  tcase_add_test(tc_core, test_div_31);
  tcase_add_test(tc_core, test_div_32);
  tcase_add_test(tc_core, test_div_33);
  tcase_add_test(tc_core, test_div_34);
  tcase_add_test(tc_core, test_div_35);
  tcase_add_test(tc_core, test_div_36);
  tcase_add_test(tc_core, test_div_37);
  tcase_add_test(tc_core, test_div_38);
  tcase_add_test(tc_core, test_div_39);
  tcase_add_test(tc_core, test_div_by_one);
  tcase_add_test(tc_core, test_div_by_negative_one);
  tcase_add_test(tc_core, test_div_positive_numbers);
  tcase_add_test(tc_core, test_div_negative_positive);
  tcase_add_test(tc_core, test_div_positive_negative);
  tcase_add_test(tc_core, test_div_large_number_by_small);
  tcase_add_test(tc_core, test_div_with_remainder);

  suite_add_tcase(s, tc_core);
  return s;
}

void test_div(s21_decimal decimal1, s21_decimal decimal2, s21_decimal check) {
  s21_decimal result;
  int code = s21_div(decimal1, decimal2, &result);
#if defined(__DEBUG)
  printf("---------------------------------\n");
  printf("\n\nTests:\n");
  s21_print_decimal_bits(decimal1);
  s21_print_decimal_string(decimal1);
  s21_print_decimal_bits(decimal2);
  s21_print_decimal_string(decimal2);
  printf("\ncheck:\n");
  s21_print_decimal_bits(check);
  s21_print_decimal_string(check);
  printf("\nres:\n");
  s21_print_decimal_bits(result);
  s21_print_decimal_string(result);
  printf("---------------------------------\n");
#endif
  ck_assert_int_eq(s21_is_equal_dickcart(result, check), 1);
  ck_assert_int_eq(code, S21_ARITHMETIC_OK);
}

void test_div_fail1(s21_decimal decimal1, s21_decimal decimal2,
                    int code_check) {
  s21_decimal result;
  int code = s21_div(decimal1, decimal2, &result);

#if defined(__DEBUG)
  printf("---------------------------------\n");
  printf("\n\nTests:\n");
  s21_print_decimal_bits(decimal1);
  s21_print_decimal_string(decimal1);
  s21_print_decimal_bits(decimal2);
  s21_print_decimal_string(decimal2);
  printf("\ncheck:\n");
  s21_print_decimal_bits(result);
  s21_print_decimal_string(result);
  printf("\nres:\n");
  s21_print_decimal_bits(result);
  s21_print_decimal_string(result);
  printf("Check: %d\n", code_check);
  printf("Result: %d\n", code);
  printf("---------------------------------\n");
#endif

  ck_assert_int_eq(code, code_check);
}

void test_div_fail2(s21_decimal decimal1, s21_decimal decimal2,
                    s21_decimal decimal_check, int code_check) {
  s21_decimal result;
  int code = s21_div(decimal1, decimal2, &result);

#if defined(__DEBUG)
  printf("---------------------------------\n");
  printf("\n\nTests:\n");
  s21_print_decimal_bits(decimal1);
  s21_print_decimal_string(decimal1);
  s21_print_decimal_bits(decimal2);
  s21_print_decimal_string(decimal2);
  printf("\ncheck:\n");
  s21_print_decimal_bits(result);
  s21_print_decimal_string(result);
  printf("\nres:\n");
  s21_print_decimal_bits(result);
  s21_print_decimal_string(result);
  printf("Check: %d\n", code_check);
  printf("Result: %d\n", code);
  printf("---------------------------------\n");
#endif

  ck_assert_int_eq(code, code_check);
  ck_assert_int_eq(s21_is_equal_dickcart(result, decimal_check), 1);
}

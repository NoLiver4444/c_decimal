#include "../s21_test_decimal.h"

START_TEST(test_is_equal_ok1) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  ck_assert_int_eq(s21_is_equal(decimal1, decimal2), 1);
}
END_TEST

START_TEST(test_is_equal_ok2) {
  // -0
  s21_decimal decimal1 = {{0x0, 0x0, 0x0, 0x80000000}};
  // 0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x0}};

  ck_assert_int_eq(s21_is_equal(decimal1, decimal2), 1);
}
END_TEST

START_TEST(test_is_equal_ok3) {
  // 0
  s21_decimal decimal1 = {{0x0, 0x0, 0x0, 0x0}};
  // 0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x0}};

  ck_assert_int_eq(s21_is_equal(decimal1, decimal2), 1);
}
END_TEST

START_TEST(test_is_equal_ok4) {
  // 1
  s21_decimal decimal1 = {{0xA, 0x0, 0x0, 0x0}};
  // 0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x0}};

  ck_assert_int_eq(s21_is_equal(decimal1, decimal2), 0);
}
END_TEST

START_TEST(test_is_equal_ok5) {
  // 1.0
  s21_decimal decimal1 = {{0xA, 0x0, 0x0, 0x10000}};
  // 1.0
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x10000}};

  ck_assert_int_eq(s21_is_equal(decimal1, decimal2), 1);
}
END_TEST

START_TEST(test_is_equal_ok7) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  ck_assert_int_eq(s21_is_equal(decimal1, decimal2), 1);
}
END_TEST

START_TEST(test_is_equal_ok8) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  ck_assert_int_eq(s21_is_equal(decimal1, decimal2), 1);
}
END_TEST

START_TEST(test_is_equal_ok9) {
  s21_decimal decimal1 = {{0x1, 0x2, 0x3, 0x4}};
  s21_decimal decimal2 = {{0x1, 0x2, 0x3, 0x0}};
  ck_assert_int_eq(s21_is_equal(decimal1, decimal2), 0);
}
END_TEST

START_TEST(test_is_equal_ok10) {
  s21_decimal decimal1 = {{0x1, 0x2, 0x3, 0x4}};
  s21_decimal decimal2 = {{0x1, 0x2, 0x0, 0x4}};
  ck_assert_int_eq(s21_is_equal(decimal1, decimal2), 0);
}
END_TEST

START_TEST(test_is_equal_ok12) {
  s21_decimal decimal1 = {{0x1, 0x2, 0x3, 0x4}};
  s21_decimal decimal2 = {{0x1, 0x0, 0x3, 0x4}};
  ck_assert_int_eq(s21_is_equal(decimal1, decimal2), 0);
}
END_TEST

START_TEST(test_is_equal_ok13) {
  s21_decimal decimal1 = {{0x1, 0x2, 0x3, 0x4}};
  s21_decimal decimal2 = {{0x0, 0x2, 0x3, 0x4}};
  ck_assert_int_eq(s21_is_equal(decimal1, decimal2), 0);
}
END_TEST

START_TEST(test_is_equal_ok14) {
  s21_decimal decimal1 = {{0x1, 0x2, 0x3, 0x4}};
  s21_decimal decimal2 = {{0x1, 0x2, 0x3, 0x4}};
  ck_assert_int_eq(s21_is_equal(decimal1, decimal2), 1);
}
END_TEST

START_TEST(test_is_equal_ok15) {
  // -1.23
  s21_decimal decimal1 = {{1000, 0x0, 0x0, 0x0}};
  // -1.230
  s21_decimal decimal2 = {{1, 0x0, 0x0, 0x00030000}};

  ck_assert_int_eq(s21_is_equal(decimal1, decimal2), 0);
}
END_TEST

START_TEST(test_is_equal_ok16) {
  // -1.23
  s21_decimal decimal1 = {{1000, 0x0, 0x0, 0x00030000}};
  // -1.230
  s21_decimal decimal2 = {{1, 0x0, 0x0, 0x0}};

  ck_assert_int_eq(s21_is_equal(decimal1, decimal2), 1);
}
END_TEST

START_TEST(test_is_equal_ok17) {
  s21_decimal decimal1 = {{0x0, 0x0, 0x0, 0x0}};
  s21_decimal decimal2 = {{1, 0x0, 0x0, 0x0}};

  ck_assert_int_eq(s21_is_equal(decimal1, decimal2), 0);
}
END_TEST

START_TEST(test_is_equal_ok18) {
  s21_decimal decimal1 = {{0x0, 0x0, 0x0, 0x0}};
  s21_decimal decimal2 = {{0x0, 1, 0x0, 0x0}};

  ck_assert_int_eq(s21_is_equal(decimal1, decimal2), 0);
}
END_TEST

START_TEST(test_is_equal_ok19) {
  s21_decimal decimal1 = {{0x0, 0x0, 0x0, 0x0}};
  s21_decimal decimal2 = {{0x0, 0x0, 1, 0x0}};

  ck_assert_int_eq(s21_is_equal(decimal1, decimal2), 0);
}
END_TEST

Suite *suite_s21_is_equal(void) {
  Suite *suite = suite_create("s21_is_equal_suite");
  TCase *tcase_core = tcase_create("s21_is_equal_tc");

  tcase_add_test(tcase_core, test_is_equal_ok1);
  tcase_add_test(tcase_core, test_is_equal_ok2);
  tcase_add_test(tcase_core, test_is_equal_ok3);
  tcase_add_test(tcase_core, test_is_equal_ok4);
  tcase_add_test(tcase_core, test_is_equal_ok5);
  tcase_add_test(tcase_core, test_is_equal_ok7);
  tcase_add_test(tcase_core, test_is_equal_ok8);
  tcase_add_test(tcase_core, test_is_equal_ok9);
  tcase_add_test(tcase_core, test_is_equal_ok10);
  tcase_add_test(tcase_core, test_is_equal_ok12);
  tcase_add_test(tcase_core, test_is_equal_ok13);
  tcase_add_test(tcase_core, test_is_equal_ok14);
  tcase_add_test(tcase_core, test_is_equal_ok15);
  tcase_add_test(tcase_core, test_is_equal_ok16);
  tcase_add_test(tcase_core, test_is_equal_ok17);
  tcase_add_test(tcase_core, test_is_equal_ok18);
  tcase_add_test(tcase_core, test_is_equal_ok19);

  suite_add_tcase(suite, tcase_core);
  return suite;
}

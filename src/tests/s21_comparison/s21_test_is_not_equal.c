#include "../s21_test_decimal.h"

START_TEST(test_is_not_equal_ok1) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  ck_assert_int_eq(s21_is_not_equal(decimal1, decimal2), 0);
}

START_TEST(test_is_not_equal_ok2) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  ck_assert_int_eq(s21_is_not_equal(decimal1, decimal2), 0);
}

START_TEST(test_is_not_equal_ok3) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  ck_assert_int_eq(s21_is_not_equal(decimal1, decimal2), 1);
}

START_TEST(test_is_not_equal_ok4) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  ck_assert_int_eq(s21_is_not_equal(decimal1, decimal2), 1);
}

START_TEST(test_is_not_equal_ok5) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 52818775009509558395695966890
  s21_decimal decimal2 = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x0}};

  ck_assert_int_eq(s21_is_not_equal(decimal1, decimal2), 1);
}

START_TEST(test_is_not_equal_ok6) {
  // 52818775009509558395695966890
  s21_decimal decimal1 = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x0}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  ck_assert_int_eq(s21_is_not_equal(decimal1, decimal2), 1);
}

START_TEST(test_is_not_equal_ok7) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -52818775009509558395695966890
  s21_decimal decimal2 = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x80000000}};

  ck_assert_int_eq(s21_is_not_equal(decimal1, decimal2), 1);
}

START_TEST(test_is_not_equal_ok8) {
  // -52818775009509558395695966890
  s21_decimal decimal1 = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x80000000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  ck_assert_int_eq(s21_is_not_equal(decimal1, decimal2), 1);
}

START_TEST(test_is_not_equal_ok9) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 52818775009509558395695966891
  s21_decimal decimal2 = {{0xAAAAAAAB, 0xAAAAAAAA, 0xAAAAAAAA, 0x0}};

  ck_assert_int_eq(s21_is_not_equal(decimal1, decimal2), 1);
}

START_TEST(test_is_not_equal_ok10) {
  // 52818775009509558395695966891
  s21_decimal decimal1 = {{0xAAAAAAAB, 0xAAAAAAAA, 0xAAAAAAAA, 0x0}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  ck_assert_int_eq(s21_is_not_equal(decimal1, decimal2), 1);
}

START_TEST(test_is_not_equal_ok11) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -52818775009509558395695966891
  s21_decimal decimal2 = {{0xAAAAAAAB, 0xAAAAAAAA, 0xAAAAAAAA, 0x80000000}};

  ck_assert_int_eq(s21_is_not_equal(decimal1, decimal2), 1);
}

START_TEST(test_is_not_equal_ok12) {
  // -52818775009509558395695966891
  s21_decimal decimal1 = {{0xAAAAAAAB, 0xAAAAAAAA, 0xAAAAAAAA, 0x80000000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  ck_assert_int_eq(s21_is_not_equal(decimal1, decimal2), 1);
}

START_TEST(test_is_not_equal_ok13) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 5.281877500950955839569596690
  s21_decimal decimal2 = {{0x11111112, 0x11111111, 0x11111111, 0x1B0000}};

  ck_assert_int_eq(s21_is_not_equal(decimal1, decimal2), 1);
}

START_TEST(test_is_not_equal_ok14) {
  // 5.281877500950955839569596690
  s21_decimal decimal1 = {{0x11111112, 0x11111111, 0x11111111, 0x1B0000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  ck_assert_int_eq(s21_is_not_equal(decimal1, decimal2), 1);
}

START_TEST(test_is_not_equal_ok15) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -5.281877500950955839569596690
  s21_decimal decimal2 = {{0x11111112, 0x11111111, 0x11111111, 0x801B0000}};

  ck_assert_int_eq(s21_is_not_equal(decimal1, decimal2), 1);
}

START_TEST(test_is_not_equal_ok16) {
  // -5.281877500950955839569596690
  s21_decimal decimal1 = {{0x11111112, 0x11111111, 0x11111111, 0x801B0000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  ck_assert_int_eq(s21_is_not_equal(decimal1, decimal2), 1);
}

START_TEST(test_is_not_equal_ok17) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 5281877500950955839569596689
  s21_decimal decimal2 = {{0x11111111, 0x11111111, 0x11111111, 0x0}};

  ck_assert_int_eq(s21_is_not_equal(decimal1, decimal2), 1);
}

START_TEST(test_is_not_equal_ok18) {
  // 5281877500950955839569596689
  s21_decimal decimal1 = {{0x11111111, 0x11111111, 0x11111111, 0x0}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  ck_assert_int_eq(s21_is_not_equal(decimal1, decimal2), 1);
}

START_TEST(test_is_not_equal_ok19) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -5281877500950955839569596689
  s21_decimal decimal2 = {{0x11111111, 0x11111111, 0x11111111, 0x80000000}};

  ck_assert_int_eq(s21_is_not_equal(decimal1, decimal2), 1);
}

START_TEST(test_is_not_equal_ok20) {
  // -5281877500950955839569596689
  s21_decimal decimal1 = {{0x11111111, 0x11111111, 0x11111111, 0x80000000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  ck_assert_int_eq(s21_is_not_equal(decimal1, decimal2), 1);
}

START_TEST(test_is_not_equal_ok21) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 5281877500950955839569596689.0
  s21_decimal decimal2 = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x10000}};

  ck_assert_int_eq(s21_is_not_equal(decimal1, decimal2), 1);
}

START_TEST(test_is_not_equal_ok22) {
  // 5281877500950955839569596689.0
  s21_decimal decimal1 = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x10000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  ck_assert_int_eq(s21_is_not_equal(decimal1, decimal2), 1);
}

START_TEST(test_is_not_equal_ok23) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -5281877500950955839569596689.0
  s21_decimal decimal2 = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x80010000}};

  ck_assert_int_eq(s21_is_not_equal(decimal1, decimal2), 1);
}

START_TEST(test_is_not_equal_ok24) {
  // -5281877500950955839569596689.0
  s21_decimal decimal1 = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x80010000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  ck_assert_int_eq(s21_is_not_equal(decimal1, decimal2), 1);
}

START_TEST(test_is_not_equal_ok25) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 7922816251426433759354395033
  s21_decimal decimal2 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};

  ck_assert_int_eq(s21_is_not_equal(decimal1, decimal2), 1);
}

START_TEST(test_is_not_equal_ok26) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  ck_assert_int_eq(s21_is_not_equal(decimal1, decimal2), 1);
}

START_TEST(test_is_not_equal_ok27) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -7922816251426433759354395033
  s21_decimal decimal2 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};

  ck_assert_int_eq(s21_is_not_equal(decimal1, decimal2), 1);
}

START_TEST(test_is_not_equal_ok28) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  ck_assert_int_eq(s21_is_not_equal(decimal1, decimal2), 1);
}

START_TEST(test_is_not_equal_ok29) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 7922816251426433759354395034
  s21_decimal decimal2 = {{0x9999999A, 0x99999999, 0x19999999, 0x0}};

  ck_assert_int_eq(s21_is_not_equal(decimal1, decimal2), 1);
}

START_TEST(test_is_not_equal_ok30) {
  // 7922816251426433759354395034
  s21_decimal decimal1 = {{0x9999999A, 0x99999999, 0x19999999, 0x0}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  ck_assert_int_eq(s21_is_not_equal(decimal1, decimal2), 1);
}

START_TEST(test_is_not_equal_ok31) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -7922816251426433759354395034
  s21_decimal decimal2 = {{0x9999999A, 0x99999999, 0x19999999, 0x80000000}};

  ck_assert_int_eq(s21_is_not_equal(decimal1, decimal2), 1);
}

START_TEST(test_is_not_equal_ok32) {
  // -7922816251426433759354395034
  s21_decimal decimal1 = {{0x9999999A, 0x99999999, 0x19999999, 0x80000000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  ck_assert_int_eq(s21_is_not_equal(decimal1, decimal2), 1);
}

START_TEST(test_is_not_equal_ok33) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 1.2297829382473034409
  s21_decimal decimal2 = {{0xAAAAAAA9, 0xAAAAAAAA, 0x0, 0x130000}};

  ck_assert_int_eq(s21_is_not_equal(decimal1, decimal2), 1);
}

START_TEST(test_is_not_equal_ok34) {
  // 1.2297829382473034409
  s21_decimal decimal1 = {{0xAAAAAAA9, 0xAAAAAAAA, 0x0, 0x130000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  ck_assert_int_eq(s21_is_not_equal(decimal1, decimal2), 1);
}

START_TEST(test_is_not_equal_ok35) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -1.2297829382473034409
  s21_decimal decimal2 = {{0xAAAAAAA9, 0xAAAAAAAA, 0x0, 0x80130000}};

  ck_assert_int_eq(s21_is_not_equal(decimal1, decimal2), 1);
}

START_TEST(test_is_not_equal_ok36) {
  // -1.2297829382473034409
  s21_decimal decimal1 = {{0xAAAAAAA9, 0xAAAAAAAA, 0x0, 0x80130000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  ck_assert_int_eq(s21_is_not_equal(decimal1, decimal2), 1);
}

START_TEST(test_is_not_equal_ok37) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 1.2297829382473034410
  s21_decimal decimal2 = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x130000}};

  ck_assert_int_eq(s21_is_not_equal(decimal1, decimal2), 1);
}

START_TEST(test_is_not_equal_ok38) {
  // 1.2297829382473034410
  s21_decimal decimal1 = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x130000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  ck_assert_int_eq(s21_is_not_equal(decimal1, decimal2), 1);
}

START_TEST(test_is_not_equal_ok39) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -1.2297829382473034410
  s21_decimal decimal2 = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x80130000}};

  ck_assert_int_eq(s21_is_not_equal(decimal1, decimal2), 1);
}

START_TEST(test_is_not_equal_ok40) {
  // -1.2297829382473034410
  s21_decimal decimal1 = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x80130000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  ck_assert_int_eq(s21_is_not_equal(decimal1, decimal2), 1);
}

START_TEST(test_is_not_equal_ok41) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 1.2297829382473034411
  s21_decimal decimal2 = {{0xAAAAAAAB, 0xAAAAAAAA, 0x0, 0x130000}};

  ck_assert_int_eq(s21_is_not_equal(decimal1, decimal2), 1);
}

START_TEST(test_is_not_equal_ok42) {
  // 1.2297829382473034411
  s21_decimal decimal1 = {{0xAAAAAAAB, 0xAAAAAAAA, 0x0, 0x130000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  ck_assert_int_eq(s21_is_not_equal(decimal1, decimal2), 1);
}

START_TEST(test_is_not_equal_ok43) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -1.2297829382473034411
  s21_decimal decimal2 = {{0xAAAAAAAB, 0xAAAAAAAA, 0x0, 0x80130000}};

  ck_assert_int_eq(s21_is_not_equal(decimal1, decimal2), 1);
}

START_TEST(test_is_not_equal_ok44) {
  // -1.2297829382473034411
  s21_decimal decimal1 = {{0xAAAAAAAB, 0xAAAAAAAA, 0x0, 0x80130000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  ck_assert_int_eq(s21_is_not_equal(decimal1, decimal2), 1);
}

START_TEST(test_is_not_equal_ok45) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 1
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x0}};

  ck_assert_int_eq(s21_is_not_equal(decimal1, decimal2), 1);
}

START_TEST(test_is_not_equal_ok46) {
  // 1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x0}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  ck_assert_int_eq(s21_is_not_equal(decimal1, decimal2), 1);
}

START_TEST(test_is_not_equal_ok47) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -1
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x80000000}};

  ck_assert_int_eq(s21_is_not_equal(decimal1, decimal2), 1);
}

START_TEST(test_is_not_equal_ok48) {
  // -1
  s21_decimal decimal1 = {{0x1, 0x0, 0x0, 0x80000000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  ck_assert_int_eq(s21_is_not_equal(decimal1, decimal2), 1);
}

START_TEST(test_is_not_equal_ok49) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 1.0
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x10000}};

  ck_assert_int_eq(s21_is_not_equal(decimal1, decimal2), 1);
}

START_TEST(test_is_not_equal_ok50) {
  // 1.0
  s21_decimal decimal1 = {{0xA, 0x0, 0x0, 0x10000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  ck_assert_int_eq(s21_is_not_equal(decimal1, decimal2), 1);
}

START_TEST(test_is_not_equal_ok51) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -1.0
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x80010000}};

  ck_assert_int_eq(s21_is_not_equal(decimal1, decimal2), 1);
}

START_TEST(test_is_not_equal_ok52) {
  // -1.0
  s21_decimal decimal1 = {{0xA, 0x0, 0x0, 0x80010000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  ck_assert_int_eq(s21_is_not_equal(decimal1, decimal2), 1);
}

START_TEST(test_is_not_equal_ok53) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 1.22
  s21_decimal decimal2 = {{0x7A, 0x0, 0x0, 0x20000}};

  ck_assert_int_eq(s21_is_not_equal(decimal1, decimal2), 1);
}

START_TEST(test_is_not_equal_ok54) {
  // 1.22
  s21_decimal decimal1 = {{0x7A, 0x0, 0x0, 0x20000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  ck_assert_int_eq(s21_is_not_equal(decimal1, decimal2), 1);
}

START_TEST(test_is_not_equal_ok55) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -1.22
  s21_decimal decimal2 = {{0x7A, 0x0, 0x0, 0x80020000}};

  ck_assert_int_eq(s21_is_not_equal(decimal1, decimal2), 1);
}

START_TEST(test_is_not_equal_ok56) {
  // -1.22
  s21_decimal decimal1 = {{0x7A, 0x0, 0x0, 0x80020000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  ck_assert_int_eq(s21_is_not_equal(decimal1, decimal2), 1);
}

START_TEST(test_is_not_equal_ok57) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 1.230001
  s21_decimal decimal2 = {{0x12C4B1, 0x0, 0x0, 0x60000}};

  ck_assert_int_eq(s21_is_not_equal(decimal1, decimal2), 1);
}

START_TEST(test_is_not_equal_ok58) {
  // 1.230001
  s21_decimal decimal1 = {{0x12C4B1, 0x0, 0x0, 0x60000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  ck_assert_int_eq(s21_is_not_equal(decimal1, decimal2), 1);
}

START_TEST(test_is_not_equal_ok59) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -1.230001
  s21_decimal decimal2 = {{0x12C4B1, 0x0, 0x0, 0x80060000}};

  ck_assert_int_eq(s21_is_not_equal(decimal1, decimal2), 1);
}

START_TEST(test_is_not_equal_ok60) {
  // 0
  s21_decimal decimal1 = {{0x0, 0x0, 0x0, 0x0}};
  // -0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x0}};

  ck_assert_int_eq(s21_is_not_equal(decimal1, decimal2), 0);
}

Suite *suite_s21_is_not_equal(void) {
  Suite *suite = suite_create("s21_is_not_equal_suite");
  TCase *tcase_core = tcase_create("s21_is_not_equal_tc");

  tcase_add_test(tcase_core, test_is_not_equal_ok1);
  tcase_add_test(tcase_core, test_is_not_equal_ok2);
  tcase_add_test(tcase_core, test_is_not_equal_ok3);
  tcase_add_test(tcase_core, test_is_not_equal_ok4);
  tcase_add_test(tcase_core, test_is_not_equal_ok5);
  tcase_add_test(tcase_core, test_is_not_equal_ok6);
  tcase_add_test(tcase_core, test_is_not_equal_ok7);
  tcase_add_test(tcase_core, test_is_not_equal_ok8);
  tcase_add_test(tcase_core, test_is_not_equal_ok9);
  tcase_add_test(tcase_core, test_is_not_equal_ok10);
  tcase_add_test(tcase_core, test_is_not_equal_ok11);
  tcase_add_test(tcase_core, test_is_not_equal_ok12);
  tcase_add_test(tcase_core, test_is_not_equal_ok13);
  tcase_add_test(tcase_core, test_is_not_equal_ok14);
  tcase_add_test(tcase_core, test_is_not_equal_ok15);
  tcase_add_test(tcase_core, test_is_not_equal_ok16);
  tcase_add_test(tcase_core, test_is_not_equal_ok17);
  tcase_add_test(tcase_core, test_is_not_equal_ok18);
  tcase_add_test(tcase_core, test_is_not_equal_ok19);
  tcase_add_test(tcase_core, test_is_not_equal_ok20);
  tcase_add_test(tcase_core, test_is_not_equal_ok21);
  tcase_add_test(tcase_core, test_is_not_equal_ok22);
  tcase_add_test(tcase_core, test_is_not_equal_ok23);
  tcase_add_test(tcase_core, test_is_not_equal_ok24);
  tcase_add_test(tcase_core, test_is_not_equal_ok25);
  tcase_add_test(tcase_core, test_is_not_equal_ok26);
  tcase_add_test(tcase_core, test_is_not_equal_ok27);
  tcase_add_test(tcase_core, test_is_not_equal_ok28);
  tcase_add_test(tcase_core, test_is_not_equal_ok29);
  tcase_add_test(tcase_core, test_is_not_equal_ok30);
  tcase_add_test(tcase_core, test_is_not_equal_ok31);
  tcase_add_test(tcase_core, test_is_not_equal_ok32);
  tcase_add_test(tcase_core, test_is_not_equal_ok33);
  tcase_add_test(tcase_core, test_is_not_equal_ok34);
  tcase_add_test(tcase_core, test_is_not_equal_ok35);
  tcase_add_test(tcase_core, test_is_not_equal_ok36);
  tcase_add_test(tcase_core, test_is_not_equal_ok37);
  tcase_add_test(tcase_core, test_is_not_equal_ok38);
  tcase_add_test(tcase_core, test_is_not_equal_ok39);
  tcase_add_test(tcase_core, test_is_not_equal_ok40);
  tcase_add_test(tcase_core, test_is_not_equal_ok41);
  tcase_add_test(tcase_core, test_is_not_equal_ok42);
  tcase_add_test(tcase_core, test_is_not_equal_ok43);
  tcase_add_test(tcase_core, test_is_not_equal_ok44);
  tcase_add_test(tcase_core, test_is_not_equal_ok45);
  tcase_add_test(tcase_core, test_is_not_equal_ok46);
  tcase_add_test(tcase_core, test_is_not_equal_ok47);
  tcase_add_test(tcase_core, test_is_not_equal_ok48);
  tcase_add_test(tcase_core, test_is_not_equal_ok49);
  tcase_add_test(tcase_core, test_is_not_equal_ok50);
  tcase_add_test(tcase_core, test_is_not_equal_ok51);
  tcase_add_test(tcase_core, test_is_not_equal_ok52);
  tcase_add_test(tcase_core, test_is_not_equal_ok53);
  tcase_add_test(tcase_core, test_is_not_equal_ok54);
  tcase_add_test(tcase_core, test_is_not_equal_ok55);
  tcase_add_test(tcase_core, test_is_not_equal_ok56);
  tcase_add_test(tcase_core, test_is_not_equal_ok57);
  tcase_add_test(tcase_core, test_is_not_equal_ok58);
  tcase_add_test(tcase_core, test_is_not_equal_ok59);
  tcase_add_test(tcase_core, test_is_not_equal_ok60);

  suite_add_tcase(suite, tcase_core);
  return suite;
}

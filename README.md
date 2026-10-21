# s21_decimal — Decimal arithmetic library in C

An educational C library for decimal arithmetic using an explicit 128-bit representation. The project explores integer-based decimal calculations, binary representation, scale management, numeric conversions, rounding, and error handling.

**Language:** C11  
**Build:** GNU Make / GCC  
**Tests:** Check

## Representation

The public decimal type is defined as:

```c
typedef struct {
    int bits[4];
} s21_decimal;
```

The implementation uses four 32-bit words: 96 bits for the numeric coefficient and a control word containing sign and scale metadata. Internal helpers also use a 256-bit intermediate representation (`s21_int_256`) for calculations that require more space.

This is a custom decimal representation, **not** the built-in C floating-point type and not an implementation of the IEEE 754 decimal format.

## Supported operations

| Category | Functions |
| --- | --- |
| Arithmetic | Addition, subtraction, multiplication, division |
| Comparison | Less, less-or-equal, greater, greater-or-equal, equal, not-equal |
| Conversion | Decimal ↔ integer; decimal ↔ float |
| Other operations | Floor, round, truncate, negate |

The library implements bit-level helpers for manipulating sign, scale, and coefficient, along with internal routines used in arithmetic and conversion.

## Repository layout

```text
src/
├── s21_decimal.h          # Public umbrella header
├── s21_decimal/           # Types, arithmetic, comparison, conversion, helpers
├── tests/                 # Check-based test suites
└── Makefile               # Library build, tests, coverage, analyzers
```

## Build and test

Prerequisites: GCC with C11 support, GNU Make, and the Check unit-testing library. On Linux, the linker setup may also require `subunit` development libraries. Optional analysis/reporting tools include `gcovr`, `lcov`, `genhtml`, `cppcheck`, `clang-format`, and Valgrind.

From the repository root:

```bash
cd src
make all
```

The default `all` target builds/runs the test executable **and** the coverage executable/report. To build the static library without invoking the full default target:

```bash
make s21_decimal.a
```

Other useful commands:

```bash
make clean             # Remove build outputs
make rebuild           # Rebuild everything
make lcov_report       # Generate an HTML coverage report
make cppcheck          # Run static analysis
make clang             # Check clang-format style
make valgrind          # Run Valgrind checks
```

The Makefile supports different modes, including a sanitizers mode:

```bash
make clean
make all MODE=2
```

Note that sanitizer and reporting targets depend on installed tool versions and platform support; running them successfully is not implied by their presence in the Makefile.

## Using the library

Include the public header and link the generated static archive:

```c
#include "s21_decimal.h"

int main(void) {
    s21_decimal value = {{0}};
    if (s21_from_int_to_decimal(125, &value) != 0) {
        return 1;
    }
    return 0;
}
```

Build the archive first, then compile your application with `-Isrc` and link `src/s21_decimal.a` (adjust paths to your setup).

## Tests and quality tools

The repository contains unit tests built on the Check framework, as well as Makefile targets for coverage, formatting, static analysis, and memory diagnostics. Coverage percentages and the current test-pass status are intentionally not claimed here without a verified clean build.

## Background

Developed as a School 21 educational project. The repository contains a team-project codebase; contributions should be attributed according to the project's actual history.

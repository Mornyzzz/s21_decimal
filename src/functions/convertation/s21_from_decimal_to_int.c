#include <stdint.h>
#include <stdio.h>

#include "../../s21_decimal.h"

/**
 * Convert s21_decimal into int
 *
 * @return  0 - OK
 *          1 - convertation error
 */
int s21_from_decimal_to_int(s21_decimal src, int* dst) {
  int result = 0;
  if (!dst) return 1;
  int sign = s21_get_sign(src);
  if (s21_get_decimal_exp(src) <= 28) {
    while (s21_get_decimal_exp(src)) {
      s21_drop_last_digit(&src);
      s21_set_decimal_exp(&src, s21_get_decimal_exp(src) - 1);
    }
    if (src.bits[1] || src.bits[2] || (s21_get_bit(src.bits[0], 31) && !sign) ||
        s21_check_max_limit(src.bits[0])) {
      result = 1;
    } else {
      *dst = src.bits[0];
      if (sign) *dst *= -1;
    }
  } else {
    result = 1;
  }
  return result;
}

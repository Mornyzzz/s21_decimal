#include <stdio.h>

#include "../../s21_decimal.h"

/**
 * Convert int into s21_decimal
 *
 * @return  0 - OK
 *          1 - convertation error
 */
int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int result = 0;
  if (!dst) return 1;
  if (src < 0) {
    s21_set_sign(dst, -1);
    src *= -1;
  } else {
    s21_set_sign(dst, 1);
  }
  for (int bit = 0; bit < 4; bit++) {
    for (int i = 0; i < BITS; i++) {
      if (bit == 0) {
        s21_set_bit_conv(&(dst->bits[0]), i, s21_get_bit(src, i));
      } else if (bit != 3 || i != 31) {
        s21_set_bit_conv(&dst->bits[bit], i, 0);
      }
    }
  }

  return result;
}

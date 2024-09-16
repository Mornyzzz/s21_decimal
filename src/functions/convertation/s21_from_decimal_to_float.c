#include <math.h>

#include "../../s21_decimal.h"

/**
 * Convert s21_decimal into float
 *
 * @return  0 - OK
 *          1 - convertation error
 */

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int result = 0;
  if (!dst) {
    result = 1;
  } else {
    double reserve = 0;
    for (int i = 0; i < 96; i++)
      if (src.bits[i / 32] & (1u << (i % 32))) reserve += pow(2, i);
    int sign = s21_get_sign(src);
    int ten_pow = (src.bits[3] << 1) >> 17;
    if (ten_pow >= 0) {
      if (ten_pow > 28) {
        *dst = 0;
        result = 1;
      } else {
        for (int i = ten_pow; i > 0; i--) {
          reserve /= 10;
        }
        *dst = (float)reserve;
        if (sign) *dst *= -1;
      }
    }
  }
  return result;
}

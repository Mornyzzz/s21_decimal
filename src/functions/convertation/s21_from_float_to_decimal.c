#include "../../s21_decimal.h"

#define MAX_FLOAT_TO_CONVERT 79228157791897854723898736640.0f

/**
 * Convert float into s21_decimal
 *
 * @return  0 - OK
 *          1 - convertation error
 */
int s21_from_float_to_decimal(float src, s21_decimal* dst) {
  int result = 0;

  if (!dst)
    result = 1;
  else if (fabsf(src) < 1e-28f && src != 0) {
    result = 1;
  } else if (isnan(src) || isinf(src)) {
    result = 1;
  } else if (fabsf(src) > MAX_FLOAT_TO_CONVERT)
    result = 1;
  else {
    s21_set_decimal_to_zero(dst);
    if (src == 0) {
      if (signbit(src) != 0) s21_set_sign(dst, -1);
    } else {
      char float_tmp[64] = {'\0'};
      sprintf(float_tmp, "%.6E", fabsf(src));
      s21_float_convert temp = {0};
      sscanf(float_tmp, "%d.%dE%d", &temp.number, &temp.drobniy, &temp.exp);
      //   printf("float_tmp = %s\nnumber = %d\ndrob =  %d\nexp = %d\n",
      //   float_tmp,
      //          temp.number, temp.drobniy, temp.exp);

      s21_decimal_set_mantissa(dst, temp.number, temp.drobniy, &temp.exp);
      // s21_decimal_set_exp(dst, temp.exp);
      if (signbit(src) != 0) s21_set_sign(dst, -1);
      //   printf("decimal exp = %d\n", s21_get_decimal_exp(dst->bits[3]));
      //   printf("float_tmp = %s\nnumber = %d\ndrob =  %d\nexp = %d\n",
      //   float_tmp,
      //          temp.number, temp.drobniy, temp.exp);
    }
  }
  return result;
}

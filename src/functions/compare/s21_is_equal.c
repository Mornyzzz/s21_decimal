#include "../../s21_decimal.h"

int s21_is_equal(s21_decimal dec1, s21_decimal dec2) {
  s21_big_decimal big_dec1 = {{0}, 0, 0};
  s21_big_decimal big_dec2 = {{0}, 0, 0};
  s21_normalization(dec1, &big_dec1);
  s21_normalization(dec2, &big_dec2);

  //-0 и +0
  if (strchr(big_dec1.number, '1') == NULL &&
      strchr(big_dec2.number, '1') == NULL) {
    return 1;
  }
  //должны быть равны знаки и равны сами числа
  if (big_dec1.sign == big_dec2.sign &&
      !strcmp(big_dec1.number, big_dec2.number))
    return 1;

  return 0;
}
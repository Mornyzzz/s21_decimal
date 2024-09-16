#include "../../s21_decimal.h"

int s21_is_greater(s21_decimal dec1, s21_decimal dec2) {
  int dec1_index = 0;
  int dec2_index = 0;
  s21_big_decimal big_dec1 = {{0}, 0, 0};
  s21_big_decimal big_dec2 = {{0}, 0, 0};
  s21_normalization(dec1, &big_dec1);
  s21_normalization(dec2, &big_dec2);

  //если числа равны или разных знаков
  if (s21_is_equal(dec1, dec2) || big_dec1.sign > big_dec2.sign) {
    return 0;
  }
  if (big_dec1.sign < big_dec2.sign) {
    return 1;
  }

  int sign = big_dec1.sign;

  //алгоритм - ищем индексы единичек и по ним сравниваем числа
  while (strchr(big_dec1.number + dec1_index, '1') != NULL &&
         strchr(big_dec2.number + dec2_index, '1') != NULL) {
    dec1_index =
        strchr(big_dec1.number + dec1_index + 1, '1') - big_dec1.number;
    dec2_index =
        strchr(big_dec2.number + dec2_index + 1, '1') - big_dec2.number;
    if (dec1_index < dec2_index)
      return !sign;
    else if (dec1_index > dec2_index)
      return sign;
  }
  //если единички закончились в первом числе - оно меньше
  if (strchr(big_dec1.number + dec1_index + 1, '1') == NULL) return 0;
  return 1;
}
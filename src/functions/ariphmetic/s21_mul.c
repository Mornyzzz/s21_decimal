#include "../../s21_decimal.h"

int s21_mul(s21_decimal dec1, s21_decimal dec2, s21_decimal *res) {
  s21_big_decimal big_dec1 = {{0}, 0, 0};
  s21_big_decimal big_dec2 = {{0}, 0, 0};
  s21_big_decimal big_res = {{0}, 0, 0};
  s21_decimal_to_big(dec1, &big_dec1);
  s21_decimal_to_big(dec2, &big_dec2);
  char temp[BIG_LEN + 1];
  int shift_index;
  memset(big_res.number, '0', BIG_LEN);

  //разворачиваем число для удобства алгоритма ниже
  s21_str_reverse(big_dec2.number);

  //алгоритм - смотрим, какие индексы второго числа имеют знаки '1', на эти
  //индексы сдвигаем число и все это складываем
  if (strchr(big_dec2.number, '1') != NULL) {
    shift_index = strchr(big_dec2.number, '1') - big_dec2.number;
    while (strchr(big_dec2.number + shift_index + 1, '1') != NULL) {
      strcpy(temp, big_dec1.number);
      s21_shift(temp, shift_index, temp);
      s21_common_add(temp, big_res.number, big_res.number);
      shift_index =
          strchr(big_dec2.number + shift_index + 1, '1') - big_dec2.number;
    }
  }
  if (strchr(big_dec2.number, '1') != NULL) {
    strcpy(temp, big_dec1.number);
    s21_shift(temp, shift_index, temp);
    s21_common_add(temp, big_res.number, big_res.number);
  }
  big_res.power = big_dec1.power + big_dec2.power;

  //знаки
  if (big_dec1.sign != big_dec2.sign)
    big_res.sign = 1;
  else
    big_res.sign = 0;

  //округление
  s21_rounding(&big_res);

  //если число слишком большое
  if (big_res.power < 0 && big_res.sign == 0) return 1;
  //если число слишком маленькое
  if (big_res.power < 0 && big_res.sign == 1) return 2;
  s21_big_to_decimal(big_res, res);
  return 0;
}

#include "../s21_decimal.h"

int s21_stepen(s21_decimal num) {
  int check = 24;
  for (int i = 24; i < 32; i++) {
    s21_set_bit_0(&num.bits[3], check);
    check++;
  }
  num.bits[3] = num.bits[3] >> 16;
  if (num.bits[3] < 29) {
    return num.bits[3];
  } else {
    return -1;
  }
}

void s21_set_bit(unsigned int *number, int bit_number) {
  *number |= (1 << bit_number);
}

int s21_check_bit(unsigned int number, int bit_number) {
  return number & (1 << bit_number);
}

// int s21_get_sign(s21_decimal num) {
//   int sign = -1;
//   if ((s21_check_bit(num.bits[3], 31)) == 0) {
//     sign = 0;
//   } else {
//     sign = 1;
//   }
//   return sign;
// }

void s21_set_bit_0(unsigned int *num, int bit_num) { *num &= ~(1 << bit_num); }

void s21_truncate_buff(s21_decimal *buf, int exp) {
  unsigned long long u_num;
  int tmp_int = 0;
  for (int i = 0; i < exp; i++) {
    u_num = buf->bits[2];
    for (int j = 2; j >= 0; j--) {
      if (j == 0) {
        buf->bits[j] = u_num / 10;
      } else {
        tmp_int = u_num % 10;
        buf->bits[j] = u_num / 10;
        u_num = tmp_int * (OVERFLW) + buf->bits[j - 1];
      }
    }
  }
  buf->bits[3] &= (2147483648);  // 10000000000000000000000000000000 mask to
                                 // sett all bits exept 31 to 0
}

int s21_last_dig(s21_decimal buf, int exp) {
  unsigned long long u_num;
  int tmp_int = 0, more_or_5 = 0;
  for (int i = 0; i < exp; i++) {
    u_num = buf.bits[2];

    for (int j = 2; j >= 0; j--) {
      if (j == 0) {
        buf.bits[j] = u_num / 10;
        more_or_5 = u_num % 10;
      } else {
        tmp_int = u_num % 10;
        buf.bits[j] = u_num / 10;
        u_num = tmp_int * (OVERFLW) + buf.bits[j - 1];
      }
    }
  }
  return more_or_5;
}
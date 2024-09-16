#ifndef C5_S21_DECIMAL_2_S21_DECIMAL_H
#define C5_S21_DECIMAL_2_S21_DECIMAL_H

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "s21_decimal.h"

#define BIG_LEN 192
#define BIT_LEN 32
#define BITS 32
//#define MAX_BITS 128
#define OVERFLW 4294967296
//#define MAX_BLOCK_BITS 32
//#define MAX_BLOCK_NUMBER 96
//#define MAX_BITS 128
//#define MAX_BLOCK_BITS 32
//#define MAX_BLOCK_NUMBER 96

// typedef enum s21_decimal_sign {
//     S21_POSITIVE = 0,
//     S21_NEGATIVE = 1
// } s21_decimal_sign;
// typedef struct {
//     unsigned int bits[8];
//     int scale;
// } big_decimal;

typedef struct {
  int sign;
  int number;
  int drobniy;
  int exp;
} s21_float_convert;

typedef struct {
  unsigned int bits[4];
} s21_decimal;

typedef struct {
  char number[192 + 1];
  int sign;
  int power;
} s21_big_decimal;

/* convertation */

int s21_from_int_to_decimal(int src, s21_decimal* dst);
int s21_from_float_to_decimal(float src, s21_decimal* dst);
int s21_from_decimal_to_int(s21_decimal src, int* dst);
int s21_from_decimal_to_float(s21_decimal src, float* dst);

int s21_get_bit(unsigned int src, int index);
void s21_set_bit_conv(unsigned int* src, int index, int bit);
void s21_set_sign(s21_decimal* decimal, int sign);
void s21_set_decimal_exp(s21_decimal* decimal, int exp);
int s21_get_decimal_exp(s21_decimal decimal);
unsigned int s21_as_uint(int x);
int s21_as_int(unsigned int x);
int s21_drop_last_digit(s21_decimal* src);
int s21_check_max_limit(int src);
void s21_decimal_set_exp(s21_decimal* decimal, int exp);
s21_decimal s21_int128_get_ten_pow(int pow);
void s21_decimal_set_mantissa(s21_decimal* decimal, int number, int drobniy,
                              int* exp);
void s21_set_decimal_to_zero(s21_decimal* decimal);

/* another functions */

int s21_floor(s21_decimal value, s21_decimal* result);
int s21_round(s21_decimal value, s21_decimal* result);
int s21_check_bit(unsigned int number, int bit_number);
int s21_get_sign(s21_decimal num);
int s21_stepen(s21_decimal num);
void s21_set_bit_0(unsigned int* number, int bit_number);
void s21_truncate_buff(s21_decimal* buf, int exp);
int s21_last_dig(s21_decimal buf, int exp);
int s21_truncate(s21_decimal value, s21_decimal* result);
void s21_set_bit(unsigned int* number, int bit_number);
int s21_negate(s21_decimal value, s21_decimal* result);

/* compare */

void s21_normalization(s21_decimal dec1, s21_big_decimal* res);
int s21_is_equal(s21_decimal dec1, s21_decimal dec2);
int s21_is_not_equal(s21_decimal dec1, s21_decimal dec2);
int s21_is_greater(s21_decimal dec1, s21_decimal dec2);
int s21_is_greater_or_equal(s21_decimal dec1, s21_decimal dec2);
int s21_is_less(s21_decimal dec1, s21_decimal dec2);
int s21_is_less_or_equal(s21_decimal dec1, s21_decimal dec2);
int s21_is_greater_value(s21_decimal dec1, s21_decimal dec2);

/* ariphmetic */

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal* result);
int s21_sub(s21_decimal dec1, s21_decimal dec2, s21_decimal* res);
int s21_mul(s21_decimal dec1, s21_decimal dec2, s21_decimal* res);
int s21_div(s21_decimal dec1, s21_decimal dec2, s21_decimal* res);

unsigned int s21_s21_binary_to_int(char* bits);
char* s21_int_to_binary(unsigned int num);
void s21_str_reverse(char* str);
char* s21_delete_zero(char* temp);
void s21_big_to_decimal(s21_big_decimal x, s21_decimal* dec);
void s21_decimal_to_big(s21_decimal dec, s21_big_decimal* x);
void s21_big_print(s21_big_decimal x);
void s21_shift(char* number, int count, char* temp);
void s21_common_add(char* first, char* second, char* result);
void s21_common_sub(char* first, char* second, char* result);
void s21_div_bin_10(char* number, char* result);
void s21_mul_bin_10(char* num, char* result, int count);
void s21_inverse(char* num);
int s21_rem_zero(s21_big_decimal big_dec);
void s21_decimal_copy(s21_decimal* dest, s21_decimal source);
void s21_dec_div_10(s21_decimal* dec);
void s21_rounding(s21_big_decimal* big_dec);

#endif

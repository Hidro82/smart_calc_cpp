#include "mafs.h"

/* This is a series of math functions, that can work with
    numbers in a stack */

namespace s21 {

void MathicModel::summer() {
  double num_1 = 0;
  double num_2 = 0;
  double result = 0;

  pull_number(&num_2);
  pull_number(&num_1);
  result = num_1 + num_2;
  push_number(&(result));
}

void MathicModel::suber() {
  double num_1 = 0;
  double num_2 = 0;
  double result = 0;

  pull_number(&num_2);
  pull_number(&num_1);
  result = num_1 - num_2;
  push_number(&(result));
}

void MathicModel::multiplier() {
  double num_1 = 0;
  double num_2 = 0;
  double result = 0;

  pull_number(&num_2);
  pull_number(&num_1);
  result = num_1 * num_2;
  push_number(&(result));
}

int MathicModel::divisor() {
  double num_1 = 0;
  double num_2 = 0;
  double result = 0;
  int errCode = 0;

  pull_number(&num_2);
  pull_number(&num_1);
  if (num_2 == 0)
    errCode = 1;
  else {
    result = num_1 / num_2;
    push_number(&(result));
  }
  return errCode;
}

int MathicModel::modder() {
  double num_1 = 0;
  double num_2 = 0;
  double result = 0;
  int errCode = 0;

  pull_number(&num_2);
  pull_number(&num_1);
  if (num_2 == 0)
    errCode = 1;
  else {
    result = fmod(num_1, num_2);
    push_number(&(result));
  }
  return errCode;
}

int MathicModel::power() {
  double num_1 = 0;
  double num_2 = 0;
  double result = 0;
  int errCode = 0;

  pull_number(&num_2);
  pull_number(&num_1);
  if ((num_1 == 0) && (num_2 < 0))
    errCode = 1;
  else if (num_1 < 0 && !floor(num_2))
    errCode = 2;
  else {
    result = pow(num_1, num_2);
    push_number(&(result));
  }
  return errCode;
}

void MathicModel::negativate() {
  double num = 0;

  pull_number(&num);
  num = -num;
  push_number(&(num));
}

void MathicModel::sinus() {
  double num = 0;
  double result = 0;

  pull_number(&num);
  result = sin(num);
  push_number(&(result));
}

void MathicModel::cosinus() {
  double num = 0;
  double result = 0;

  pull_number(&num);
  result = cos(num);
  push_number(&(result));
}

void MathicModel::tangens() {
  double num = 0;
  double result = 0;

  pull_number(&num);
  result = tan(num);
  push_number(&(result));
}

int MathicModel::arcsinus() {
  double num = 0;
  double result = 0;
  int errCode = 0;

  pull_number(&num);
  if ((num > -1.0) && (num < 1.0))
    result = asin(num);
  else
    errCode = 6;
  push_number(&(result));
  return errCode;
}

int MathicModel::arccosinus() {
  double num = 0;
  double result = 0;
  int errCode = 0;

  pull_number(&num);
  if ((num > -1.0) && (num < 1.0))
    result = acos(num);
  else
    errCode = 6;
  push_number(&(result));
  return errCode;
}

void MathicModel::arctangens() {
  double num = 0;
  double result = 0;

  pull_number(&num);
  result = atan(num);
  push_number(&(result));
}

int MathicModel::square() {
  double num = 0;
  double result = 0;
  int errCode = 0;

  pull_number(&num);
  if (num < 0)
    errCode = 2;
  else
    result = sqrt(num);
  push_number(&(result));
  return errCode;
}

int MathicModel::log_nat() {
  double num = 0;
  double result = 0;
  int errCode = 0;

  pull_number(&num);
  if (num > 0)
    result = log(num);
  else
    errCode = 6;
  push_number(&(result));
  return errCode;
}

int MathicModel::log_ten() {
  double num = 0;
  double result = 0;
  int errCode = 0;

  pull_number(&num);
  if (num > 0)
    result = log10(num);
  else
    errCode = 6;
  push_number(&(result));
  return errCode;
}

}  // namespace s21
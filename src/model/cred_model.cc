#include "mafs.h"

namespace s21 {

void CreditModel::differential() {
  int pay_count = 0;
  double payday = 0;

  if (this->month == 1)
    pay_count = this->time;
  else
    pay_count = this->time * 12;
  payday = this->cash / pay_count;

  double rue[pay_count]{0};

  for (int i = 0; i < pay_count; i++) {
    rue[i] = payday + (this->cash * this->percent / 1200);
    this->cash -= payday;
    this->whole += rue[i];
  }
  this->over = this->whole - payday * pay_count;
  this->monthly[0] = rue[0];
  this->monthly[1] = rue[pay_count - 1];
}

void CreditModel::annuite() {
  int pay_count = 0;

  if (this->month == 1)
    pay_count = this->time;
  else
    pay_count = this->time * 12;
  this->monthly[0] = this->cash * this->percent / 1200 *
                     pow((1 + (this->percent) / 1200), pay_count) /
                     (pow((1 + (this->percent) / 1200), pay_count) - 1);
  this->whole = this->monthly[0] * pay_count;
  this->over = this->whole - this->cash;
}

}  // namespace s21
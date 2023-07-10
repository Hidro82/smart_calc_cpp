#ifndef SRC_CONTROLLER_CALC_H_
#define SRC_CONTROLLER_CALC_H_

#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <string>

#include "../model/mafs.h"

namespace s21 {

class Mathic {
 public:
  int calc_brain();
  int sign_operator(char og, char backup, char dbck);
  int brace_operator(char og, char *oper, int *brace_opened);
  int string_processor(std::string og, double x_var);
  int stacker(std::string og, double x_var, double *result);

 private:
  MathicModel model;
};

class Credit {
 public:
  void input_handler(double cash, int time, int month, double percent,
                     int differ) {
    model.cash = cash;
    model.time = time;
    model.month = month;
    model.percent = percent;
    model.differ = differ;
  }
  double output_month_1() { return model.monthly[0]; }
  double output_month_2() { return model.monthly[1]; }
  double output_whole() { return model.whole; }
  double output_over() { return model.over; }
  int credit_calculus();

 private:
  CreditModel model;
};

class CoorData {
  friend class SMCalcWin;

 public:
  CoorData(){};
  CoorData(double x_1, double x_2, double y_1, double y_2) {
    this->x_start = x_1;
    this->x_end = x_2;
    this->x_scale = 300 / (fabs(x_start) + fabs(x_end));
    this->x_step = (fabs(x_start) + fabs(x_end)) / 600;
    this->x_zero = fabs(x_start) * x_scale;
    this->y_start = y_1;
    this->y_end = y_2;
    this->y_scale = 300 / (fabs(y_start) + fabs(y_end));
    this->y_step = (fabs(y_start) + fabs(y_end)) / 600;
    this->y_zero = fabs(y_end) * y_scale;
  }

 protected:
  double x_start;
  double x_end;
  double x_scale;
  double x_step;
  double x_zero;
  double y_start;
  double y_end;
  double y_scale;
  double y_step;
  double y_zero;
};

}  // namespace s21

#endif  // SRC_CONTROLLER_CALC_H_

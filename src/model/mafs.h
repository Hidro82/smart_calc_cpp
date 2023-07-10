#ifndef SRC_MODEL_MAFS_H_
#define SRC_MODEL_MAFS_H_

#include <math.h>

namespace s21 {

class MathicModel {
  friend class Mathic;

 public:
  int operand_priority(char sign);
  void push_number(double *token);
  void push_sign(char token);
  void pull_number(double *token);
  void pull_sign(char *token);
  void clear_stacks();

  void summer();
  void suber();
  void multiplier();
  int divisor();
  int modder();
  int power();
  void negativate();
  void sinus();
  void cosinus();
  void tangens();
  int arcsinus();
  int arccosinus();
  void arctangens();
  int square();
  int log_nat();
  int log_ten();

 private:
  double num[256];
  int n_count = 0;
  int priority[256];
  char sign[256];
  int s_count = 0;
};

class CreditModel {
  friend class Credit;
  friend class SMCalcCredit;

 public:
  void differential();
  void annuite();

 private:
  double cash = 0;
  int time = 0;
  int month = 0;
  double percent = 0;
  int differ = 0;
  double monthly[2];
  double over = 0;
  double whole = 0;
};

}  // namespace s21

#endif  // SRC_MODEL_MAFS_H_
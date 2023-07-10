#include "calc.h"

/* This functions are doing calculation operations
    with stacks */

namespace s21 {

int Mathic::calc_brain() {
  /* This masterpiece of Indian code calculates the last
      one or two numbers in number stack, depending on the last
      operator in operator stack */
  char oper = '\0';
  int errCode = 0;

  model.pull_sign(&oper);
  if (model.n_count <= 0 ||
      (model.n_count == 1 && (oper == '+' || oper == '-' || oper == '*' ||
                              oper == '/' || oper == 'm' || oper == '^'))) {
    errCode = 3;
  } else {
    if (oper == '+') {
      if (model.s_count == 0 ||
          (model.s_count > 0 && model.sign[model.s_count - 1] != '-'))
        model.summer();
      else
        model.suber();
    } else if (oper == '-') {
      if (model.s_count == 0 ||
          (model.s_count > 0 && model.sign[model.s_count - 1] != '-'))
        model.suber();
      else
        model.summer();
    } else if (oper == '*')
      model.multiplier();
    else if (oper == '/')
      errCode = model.divisor();
    else if (oper == 'm')
      errCode = model.modder();
    else if (oper == '~')
      model.negativate();
    else if (oper == '^')
      errCode = model.power();
    else if (oper == 's')
      model.sinus();
    else if (oper == 'c')
      model.cosinus();
    else if (oper == 't')
      model.tangens();
    else if (oper == 'S')
      errCode = model.arcsinus();
    else if (oper == 'C')
      errCode = model.arccosinus();
    else if (oper == 'T')
      model.arctangens();
    else if (oper == 'q')
      errCode = model.square();
    else if (oper == 'l')
      errCode = model.log_nat();
    else if (oper == 'L')
      errCode = model.log_ten();
  }
  if (model.s_count < 0) model.s_count++;
  return errCode;
}

}  // namespace s21
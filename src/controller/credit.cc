#include "calc.h"

namespace s21 {

int Credit::credit_calculus() {
  int errCode = 0;

  if (model.cash <= 0)
    errCode = 1;
  else if (model.time <= 0)
    errCode = 2;
  else if (model.percent < 0.01 || model.percent > 999)
    errCode = 3;

  if (model.differ == 1)
    model.differential();
  else
    model.annuite();

  return errCode;
}

}  // namespace s21
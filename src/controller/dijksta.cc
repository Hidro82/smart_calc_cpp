#include "calc.h"

/* This Gargantua is the main function of this calculator
    it reads the entry string, parses the numbers and
    operators from it and, finally, calculates */

namespace s21 {

int Mathic::sign_operator(char og, char backup, char dbck) {
  int errCode = 0;

  if (og != '=') {
    if (backup == 'z' || backup == '(') {
      if (og == '-')
        model.push_sign('~');
      else if (og == '+')
        model.push_sign('p');
      else if (og == '(')
        model.push_sign('(');
      else if (og == '^' || og == '*' || og == '/' || og == 'm' || og == ')')
        errCode = 6;
    } else if (backup == 'a') {
      if (og == 's')
        model.push_sign('S');
      else if (og == 'c')
        model.push_sign('C');
      else if (og == 't')
        model.push_sign('T');
    } else if (backup == 'l') {
      if (og == 'n')
        model.push_sign('l');
      else if (og == 'o')
        model.push_sign('L');
    } else if (backup == 's' && og == 'q')
      model.push_sign('q');
    else if (backup == 's' && og == 'i' && dbck != 'a')
      model.push_sign('s');
    else if (backup == 'c' && og == 'o' && dbck != 'a')
      model.push_sign('c');
    else if (backup == 't' && og == 'a' && dbck != 'a')
      model.push_sign('t');
    else if (og == '+' || og == '-' || og == '*' || og == '/' || og == '^' ||
             og == 'm' || og == '(' || og == ')') {
      model.push_sign(og);
    }
  }
  return errCode;
}

int Mathic::brace_operator(char og, char *oper, int *brace_opened) {
  int errCode = 0;

  if (og == '(') {
    *brace_opened = *brace_opened + 1;
  } else if (og == ')') {
    *brace_opened = *brace_opened - 1;
    if (*brace_opened < 0) {
      errCode = 4;
    } else {
      do {
        errCode = calc_brain();
      } while (model.sign[model.s_count - 1] != '(' && !errCode);
      model.pull_sign(oper);
    }
  }
  return errCode;
}

int Mathic::string_processor(std::string og, double x_var) {
  double number = 0;
  int i = 0;
  int j = 0;
  int errCode = 0;
  int brace_opened = 0;
  char oper;
  char dbck = 'z';
  char backup = 'z';
  std::string buffer = "";

  while ((j < static_cast<int>(og.length())) && !errCode) {
    if ((og[j] >= '0' && og[j] <= '9') || og[j] == '.') {
      buffer = buffer + og[j];
      i++;
    } else if (og[j] == 'X') {
      model.push_number(&x_var);
    } else {
      if (i) {
        number = std::stof(buffer);
        model.push_number(&number);
        i = 0;
        buffer = "";
      }
      if (model.s_count >= 1 &&
          (model.priority[model.s_count - 1] > model.operand_priority(og[j])) &&
          (og[j] != '('))
        errCode = calc_brain();
      errCode = sign_operator(og[j], backup, dbck);
      errCode = brace_operator(og[j], &oper, &brace_opened);
    }
    dbck = backup;
    backup = og[j];
    j++;
  }
  if (brace_opened > 0) errCode = 5;
  return errCode;
}

int Mathic::stacker(std::string og, double x_var, double *result) {
  int errCode = 0;

  errCode = string_processor(og, x_var);
  if (model.s_count > 0 && !errCode)
    while (model.s_count > 0 && !errCode) errCode = calc_brain();
  *result = model.num[0];
  model.clear_stacks();
  return errCode;
}

}  // namespace s21
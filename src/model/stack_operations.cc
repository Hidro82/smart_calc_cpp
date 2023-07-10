#include "mafs.h"

/* All this functions are made to emulate stack
    behavior in current program. 'Push' functions
    are adding another element in stack and 'pull'
    functions are taking the last one in the line */

namespace s21 {

int MathicModel::operand_priority(char sign) {
  /* This function decides the priority of the current
      operator. In the main function if the pointer sees, that
      the current operator is less valuable than the last one - it
      starts counting, until the priority of the last operator in
      stack is equal or less than a current */
  int result = 9000;

  if (sign == '(')
    result = 0;
  else if (sign == '+' || sign == '-')
    result = 1;
  else if (sign == '*' || sign == '/' || sign == 'm')
    result = 2;
  else if (sign == '^')
    result = 3;
  else if (sign == 'p' || sign == '~')
    result = 4;
  else if (sign == 's' || sign == 'c' || sign == 't' || sign == 'S' ||
           sign == 'C' || sign == 'T' || sign == 'q' || sign == 'l' ||
           sign == 'L')
    result = 5;
  else if (sign == ')')
    result = 6;
  return result;
}

void MathicModel::push_number(double *token) {
  this->num[this->n_count] = *token;
  this->n_count += 1;
}

void MathicModel::push_sign(char token) {
  this->sign[this->s_count] = token;
  this->priority[this->s_count] = operand_priority(token);
  this->s_count += 1;
}

void MathicModel::pull_number(double *token) {
  this->n_count -= 1;
  if (this->n_count >= 0) {
    *token = this->num[this->n_count];
    this->num[this->n_count] = 0;
  }
}

void MathicModel::pull_sign(char *token) {
  this->s_count -= 1;
  if (this->s_count >= 0) {
    this->priority[this->s_count] = 0;
    *token = this->sign[this->s_count];
    this->sign[this->s_count] = 0;
  }
}

void MathicModel::clear_stacks() {
  while (this->n_count > 0) {
    this->num[this->n_count] = 0;
    this->n_count--;
  }
  while (this->s_count > 0) {
    this->sign[this->s_count] = '\0';
    this->s_count--;
  }
}

}  // namespace s21
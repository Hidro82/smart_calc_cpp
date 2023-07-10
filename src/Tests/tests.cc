#include <gtest/gtest.h>

#include "../controller/calc.h"

TEST(Test1, base) {
  s21::Mathic SMBrain;
  std::string og =
      "sin(3.14)-(-8)-9+cos(3.14)^2*(2mod(2/"
      "2))+ln(1)+log(1)+asin(0)+acos(1)+atan(0)+tan(0)+sqrt(4)=";
  double result = 0.0;

  SMBrain.stacker(og, 0.0, &result);
  EXPECT_NEAR(result, 1, 1e-2);
}

TEST(Test2, base) {
  s21::Credit CrBrain;
  CrBrain.input_handler(300000, 2, 0, 5, 0);

  CrBrain.credit_calculus();
  EXPECT_NEAR(CrBrain.output_whole(), 315874, 10);
}

TEST(Test3, base) {
  s21::Credit CrBrain;
  CrBrain.input_handler(300000, 2, 0, 5, 1);

  CrBrain.credit_calculus();
  EXPECT_NEAR(CrBrain.output_whole(), 315625, 100);
}

TEST(Test4, base) {
  s21::Credit CrBrain;
  CrBrain.input_handler(300000, 24, 1, 5, 0);

  CrBrain.credit_calculus();

  EXPECT_NEAR(CrBrain.output_whole(), 315874, 100);
}

TEST(Test5, base) {
  s21::Credit CrBrain;
  CrBrain.input_handler(300000, 1, 1, 5, 1);

  CrBrain.credit_calculus();
  EXPECT_NEAR(CrBrain.output_whole(), 301250, 100);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
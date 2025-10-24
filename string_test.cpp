#include "StringCalculator.h"
#include <gtest/gtest.h>

TEST(StringCalculatorTests, TC01_EmptyStringReturnsZero) {
  StringCalculator calc;
  EXPECT_EQ(calc.Add(""), 0);
}

TEST(StringCalculatorTests, TC02_SingleNumberInput) {
  StringCalculator calc;
  EXPECT_EQ(calc.Add("1"), 1);
}

TEST(StringCalculatorTests, TC03_MultipleCommaSeparatedNumbers) {
  StringCalculator calc;
  EXPECT_EQ(calc.Add("1,2,3"), 6);
}

TEST(StringCalculatorTests, TC04_NewlineAsValidDelimiter) {
  StringCalculator calc;
  EXPECT_EQ(calc.Add("1\n2,3"), 6);
}

TEST(StringCalculatorTests, TC05_CustomSingleCharacterDelimiter) {
  StringCalculator calc;
  EXPECT_EQ(calc.Add("//;\n1;2"), 3);
}

TEST(StringCalculatorTests, TC06_CustomMultiCharacterDelimiter) {
  StringCalculator calc;
  EXPECT_EQ(calc.Add("//[***]\n1***2***3"), 6);
}

TEST(StringCalculatorTests, TC07_NegativeNumberThrowsException) {
  StringCalculator calc;
  try {
    calc.Add("1,-2");
    FAIL() << "Expected std::runtime_error";
  } catch (const std::runtime_error& err) {
    EXPECT_STREQ(err.what(), "negatives not allowed: -2");
  } catch (...) {
    FAIL() << "Expected std::runtime_error";
  }
}

TEST(StringCalculatorTests, TC08_NumbersGreaterThan1000AreIgnored) {
  StringCalculator calc;
  EXPECT_EQ(calc.Add("2,1001"), 2);
}

TEST(StringCalculatorTests, TC09_CustomDelimiterWithNewlineMixed) {
  StringCalculator calc;
  EXPECT_EQ(calc.Add("//;\n1;2\n3"), 6);
}

TEST(StringCalculatorTests, TC10_CustomDelimiterWithSpecialCharacters) {
  StringCalculator calc;
  EXPECT_EQ(calc.Add("//[***]\n12***3"), 15);
}

TEST(StringCalculatorTests, TC11_InvalidNewlineFormatThrowsException) {
  StringCalculator calc;
  try {
    calc.Add("1,\n");
    FAIL() << "Expected std::runtime_error";
  } catch (const std::runtime_error& err) {
    EXPECT_STREQ(err.what(), "Invalid input format: empty token");
  } catch (...) {
    FAIL() << "Expected std::runtime_error";
  }
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
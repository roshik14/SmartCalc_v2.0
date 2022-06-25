#include "s21_SmartCalc_v2/Model/model.h"
#include <gtest/gtest.h>

TEST(simple_calc_test_suit, simple_test1) {
    const std::string expr = "123+345/245*0.234";
    const std::string expected = "123.329510";
    s21::Model m;
    const auto actual = m.calculateExpression(expr, "0");
    ASSERT_EQ(expected, actual);
}

TEST(simple_calc_test_suit, simple_test2) {
    const std::string expr = "225*34.324/5*cos(-1.5)";
    const std::string expected = "109.259267";
    s21::Model m;
    const auto actual = m.calculateExpression(expr, "0");
    ASSERT_EQ(expected, actual);
}

TEST(simple_calc_test_suit, simple_test3) {
    const std::string expr = "225*34.324/52*cos(-1.5)/(sin(1)+tan(1)/asin(0.5))";
    const std::string expected = "2.753137";
    s21::Model m;
    const auto actual = m.calculateExpression(expr, "0");
    ASSERT_EQ(expected, actual);
}

TEST(simple_calc_test_suit, simple_test4) {
    const std::string expr = "23452342mod2*(12342/5555)";
    const std::string expected = "0.000000";
    s21::Model m;
    const auto actual = m.calculateExpression(expr, "0");
    ASSERT_EQ(expected, actual);
}

TEST(simple_calc_test_suit, simple_test5) {
    const std::string expr = "23452342mod2*(12342/5555)/cos(2.342)*tan(0.2)+234";
    const std::string expected = "234.000000";
    s21::Model m;
    const auto actual = m.calculateExpression(expr, "0");
    ASSERT_EQ(expected, actual);
}

TEST(simple_calc_test_suit, simple_test6) {
    const std::string expr = "2^3^4";
    const std::string expected = "4096.000000";
    s21::Model m;
    const auto actual = m.calculateExpression(expr, "0");
    ASSERT_EQ(expected, actual);
}

TEST(simple_calc_test_suit, simple_test7) {
    const std::string expr = "-2*-2";
    const std::string expected = "4.000000";
    s21::Model m;
    const auto actual = m.calculateExpression(expr, "0");
    ASSERT_EQ(expected, actual);
}

TEST(simple_calc_test_suit, brackets_test1) {
    const std::string expr = "sin(cos(tan(atan(sin(cos(cos(tan(0.5))))))))";
    const std::string expected = "0.730728";
    s21::Model m;
    const auto actual = m.calculateExpression(expr, "0");
    ASSERT_EQ(expected, actual);
}

TEST(simple_calc_test_suit, brackets_test2) {
    const std::string expr = "934*(11/(34.234mod2+(sin(cos(tan(0.01)))+2.3454+(-1)mod(-1/2.3))))";
    const std::string expected = "3122.408012";
    s21::Model m;
    const auto actual = m.calculateExpression(expr, "0");
    ASSERT_EQ(expected, actual);
}


TEST(simple_calc_test_suit, brackets_test3) {
    const std::string expr = "2*(sin(cos(tan(atan(acos(asin(sqrt(2)))))))*cos(sin(tan(atan(0.2))))+23)";
    const std::string expected = "CANNOT BE CALCULATED";
    s21::Model m;
    const auto actual = m.calculateExpression(expr, "0");
    ASSERT_EQ(expected, actual);
}

TEST(simple_calc_test_suit, brackets_test4) {
    const std::string expr = "sqrt(sqrt(sqrt(sin(sin(cos(cos(2))))))*2+tan(cos(sin(tan(cos(sin(2)))))))";
    const std::string expected = "1.691417";
    s21::Model m;
    const auto actual = m.calculateExpression(expr, "0");
    ASSERT_EQ(expected, actual);
}

TEST(simple_calc_test_suit, nan_test) {
    const std::string expr = "sqrt(sqrt(sqrt(sin(sin(cos(cos(2))))))*2+tan(cos(sin(tan(cos(sin(2)))))))/0";
    const std::string expected = "CANNOT BE CALCULATED";
    s21::Model m;
    const auto actual = m.calculateExpression(expr, "0");
    ASSERT_EQ(expected, actual);
}

TEST(simple_calc_test_suit, inf_test) {
    const std::string expr = "sqrt(sqrt(sqrt(sin(sin(cos(cos(2))))))*2+tan(cos(sin(tan(cos(sin(2)))))))*log(0)";
    const std::string expected = "CANNOT BE CALCULATED";
    s21::Model m;
    const auto actual = m.calculateExpression(expr, "0");
    ASSERT_EQ(expected, actual);
}

TEST(simple_calc_test_suit, error_test1) {
    const std::string expr = "sqrt(sqrt(sqrt(sin(sin(cos(cos(2))))))*2+tan(cos(sin(tan(cos(sin(2)))))))*log(0)**2";
    const std::string expected = "EXPRESSION ERROR";
    s21::Model m;
    const auto actual = m.calculateExpression(expr, "0");
    ASSERT_EQ(expected, actual);
}

TEST(simple_calc_test_suit, error_test2) {
    const std::string expr = "aboba";
    const std::string expected = "EXPRESSION ERROR";
    s21::Model m;
    const auto actual = m.calculateExpression(expr, "0");
    ASSERT_EQ(expected, actual);
}

#include "s21_SmartCalc_v2/Model/model.h"
#include <gtest/gtest.h>
#include <map>

TEST(credit_calc_suit, credit_calc_annuity_test1) {
    std::vector<double> values {
         35e4,
        2,
        7.5
    };
    int termType = 0;
    int creditType = 0;
    auto expectedAmount = 15749.857428068373;
    double expectedPercents = 27996.578273646497;
    double expectedTotal = 377996.57827364648;
    s21::Model m;
    auto data = m.calculateCredit(values, creditType, termType);
    ASSERT_DOUBLE_EQ(data.at("payment").front(), expectedAmount);
    ASSERT_DOUBLE_EQ(data.at("payment").back(), expectedAmount);
    ASSERT_DOUBLE_EQ(data.at("overpay").front(), expectedPercents);
    ASSERT_DOUBLE_EQ(values.at(0) + expectedPercents, expectedTotal);
}

TEST(credit_calc_suit, credit_calc_annuity_test2) {
    std::vector<double> values {
        15e5,
        32,
        12
    };
    int termType = 1;
    int creditType = 0;
    auto expectedAmount = 55006.328624478418;
    double expectedPercents = 260202.51598331053;
    double expectedTotal = 1760202.5159833105;
    s21::Model m;
    auto data = m.calculateCredit(values, creditType, termType);
    ASSERT_DOUBLE_EQ(data.at("payment").front(), expectedAmount);
    ASSERT_DOUBLE_EQ(data.at("payment").back(), expectedAmount);
    ASSERT_DOUBLE_EQ(data.at("overpay").front(), expectedPercents);
    ASSERT_DOUBLE_EQ(values.at(0) + expectedPercents, expectedTotal);
}

TEST(credit_calc_suit, credit_calc_diffrentiated_test1) {
    std::vector<double> values {
         15e5,
         32,
         12
    };
    int termType = 1;
    int creditType = 1;
    auto expectedFirstPay = 61875.00;
    auto expectedLastPay = 47343.75;
    double expectedPercents = 247500.00;
    double expectedTotal = 1747500.00;
    s21::Model m;
    auto data = m.calculateCredit(values, creditType, termType);
    ASSERT_DOUBLE_EQ(data.at("payment").front(), expectedFirstPay);
    ASSERT_DOUBLE_EQ(data.at("payment").back(), expectedLastPay);
    ASSERT_DOUBLE_EQ(data.at("overpay").front(), expectedPercents);
    ASSERT_DOUBLE_EQ(values.at(0) + expectedPercents, expectedTotal);
}

TEST(credit_calc_suit, credit_calc_diffrentiated_test2) {
    std::vector<double> values {
         43e5,
         5,
         13.5
    };
    int termType = 0;
    int creditType = 1;
    auto expectedFirstPay = 120041.66666666669;
    auto expectedLastPay = 72472.916666666701;
    double expectedPercents = 1475437.50;
    double expectedTotal = 5775437.50;
    s21::Model m;
    auto data = m.calculateCredit(values, creditType, termType);
    ASSERT_DOUBLE_EQ(data.at("payment").front(), expectedFirstPay);
    ASSERT_DOUBLE_EQ(data.at("payment").back(), expectedLastPay);
    ASSERT_DOUBLE_EQ(data.at("overpay").front(), expectedPercents);
    ASSERT_DOUBLE_EQ(values.at(0) + expectedPercents, expectedTotal);
}

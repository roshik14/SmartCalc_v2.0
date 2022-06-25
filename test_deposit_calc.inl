#include "s21_SmartCalc_v2/Model/model.h"
#include <gtest/gtest.h>

TEST(deposit_calc_suit, deposit_calc_test1) {
    std::vector<double> values {
        1e5,
        5,
        1,
        0,
        0,
    };
    std::vector<std::vector<std::string>> replList;
    std::vector<std::vector<std::string>> withdrawList;
    bool isCapitalized = false;
    auto expectedInterest = 4999.9999999999691;
    auto expectedTax = 0.00;
    auto expectedAmount = 1e5;
    s21::Model m;
    auto data = m.calculateDeposit(values, replList, withdrawList, isCapitalized);
    ASSERT_DOUBLE_EQ(data.at("totalPercents").front(), expectedInterest);
    ASSERT_DOUBLE_EQ(data.at("totalAmount").back(), expectedAmount);
    ASSERT_DOUBLE_EQ(data.at("taxAmount").front(), expectedTax);
}

TEST(deposit_calc_suit, deposit_calc_test2) {
    std::vector<double> values {
        15e5,
        7.5,
        36,
        1,
        0,
    };
    std::vector<std::vector<std::string>> replList;
    std::vector<std::vector<std::string>> withdrawList;
    bool isCapitalized = false;
    auto expectedInterest = 337499.99999999691;
    auto expectedTax = 29574.9999999996;
    auto expectedAmount = 15e5;
    s21::Model m;
    auto data = m.calculateDeposit(values, replList, withdrawList, isCapitalized);
    ASSERT_DOUBLE_EQ(data.at("totalPercents").front(), expectedInterest);
    ASSERT_DOUBLE_EQ(data.at("totalAmount").back(), expectedAmount);
    ASSERT_DOUBLE_EQ(data.at("taxAmount").back(), expectedTax);
}

TEST(deposit_calc_suit, deposit_calc_test3) {
    std::vector<double> values {
        15e5,
        7.5,
        36,
        1,
        0,
    };
    std::vector<std::vector<std::string>> replList;
    std::vector<std::vector<std::string>> withdrawList;
    bool isCapitalized = true;
    auto expectedInterest = 378440.65687580855;
    auto expectedTax = 34897.285393855112;
    auto expectedAmount = 15e5 + expectedInterest;
    s21::Model m;
    auto data = m.calculateDeposit(values, replList, withdrawList, isCapitalized);
    ASSERT_DOUBLE_EQ(data.at("totalPercents").front(), expectedInterest);
    ASSERT_DOUBLE_EQ(data.at("totalAmount").back(), expectedAmount);
    ASSERT_DOUBLE_EQ(data.at("taxAmount").front(), expectedTax);
}

TEST(deposit_calc_suit, deposit_calc_test4) {
    std::vector<double> values {
        15e5,
        7.5,
        24,
        1,
        1,
    };
    std::vector<std::vector<std::string>> replList {
        std::vector<std::string> {
            "One-time",
            "17.07.2022",
            "150000"
        }
    };
    std::vector<std::vector<std::string>> withdrawList;
    bool isCapitalized = false;
    auto expectedInterest = 246513.69863013699;
    auto expectedTax = 17746.780821917808;
    auto expectedAmount = 165e4;
    s21::Model m;
    auto data = m.calculateDeposit(values, replList, withdrawList, isCapitalized);
    ASSERT_DOUBLE_EQ(data.at("totalPercents").front(), expectedInterest);
    ASSERT_DOUBLE_EQ(data.at("totalAmount").back(), expectedAmount);
    ASSERT_DOUBLE_EQ(data.at("taxAmount").front(), expectedTax);
}

TEST(deposit_calc_suit, deposit_calc_test5) {
    std::vector<double> values {
        25e5,
        9.3,
        66,
        1,
        1,
    };
    std::vector<std::vector<std::string>> replList {
        std::vector<std::string> {
            "One-time",
            "17.07.2022",
            "150000"
        }
    };

    std::vector<std::vector<std::string>> withdrawList {
        std::vector<std::string> {
            "Monthly",
            "23.06.2022",
            "234000"
        }
    };

    bool isCapitalized = false;
    auto expectedInterest = 142893.35342465734;
    auto expectedTax = 4276.1359452054539;
    auto expectedAmount = 76000;
    s21::Model m;
    auto data = m.calculateDeposit(values, replList, withdrawList, isCapitalized);
    ASSERT_DOUBLE_EQ(data.at("totalPercents").front(), expectedInterest);
    ASSERT_DOUBLE_EQ(data.at("totalAmount").back(), expectedAmount);
    ASSERT_DOUBLE_EQ(data.at("taxAmount").front(), expectedTax);
}

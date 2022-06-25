#include "model.h"

s21::Model::Model() {
    setlocale(LC_ALL, "en_US.UTF-8");
}

std::string s21::Model::calculateExpression(const std::string &expression, const std::string &x) {
    SimpleCalcModel calc(expression, x);
    return calc.calculate();
}

std::vector<std::pair<long double, long double>>
s21::Model::graphPoints(const std::string &expression,
                          double xStart,
                          double xEnd) {
    const auto step = fabs(xEnd - xStart) / 10000;
    std::vector<std::pair<long double, long double>> points;
    for (; xStart <= xEnd; xStart += step) {
        SimpleCalcModel calc(expression, std::to_string(xStart));
        auto yStr = calc.calculate();
        if (yStr == "EXPRESSION ERROR") {
            points.push_back(std::pair<long double, long double>(INFINITY, INFINITY));
                break;
        }
        if (yStr == "CANNOT BE CALCULATED") {
            points.push_back
                    (std::pair<long double, long double>
                     (xStart, std::numeric_limits<long double>::quiet_NaN()));
        } else {
            points.push_back(std::pair<long double, long double>(xStart, std::stold(yStr)));
        }
    }
    return points;
}

std::map<std::string, std::vector<double>>
s21::Model::calculateCredit(const std::vector<double> &values, int creditType, int termType) {
    CreditCalcModel calc;
    auto result = calc.calculate(values, creditType, termType);
    monthsData_ = calc.monthsData();
    return result;
}

std::map<std::string, std::vector<double>>
s21::Model::calculateDeposit(const std::vector<double> &data,
                             const std::vector<std::vector<std::string>> &replList,
                             const std::vector<std::vector<std::string>> &withdrawList,
                             bool capitalization) {
    monthsData_.erase(monthsData_.begin(), monthsData_.end());
    DepositCalcModel calc;
    auto result =  calc.calculate(data, replList, withdrawList, capitalization);
    monthsData_ = calc.monthsData();
    return result;
}


std::vector<std::string> s21::Model::getMonthsData() {
    return monthsData_;
}

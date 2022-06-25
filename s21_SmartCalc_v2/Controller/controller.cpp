#include "controller.h"

s21::Controller::Controller(Model *model) : model_(model) {}

std::string s21::Controller::getCalculatedValue(const std::string &expression, const std::string &x) {
    return model_->calculateExpression(expression, x);
}

std::vector<std::pair<long double, long double>>
s21::Controller::getPointsForGraph(const std::string &expression,
                                   double xStart,
                                   double xEnd) {
    return model_->graphPoints(expression, xStart, xEnd);
}

std::map<std::string, std::vector<double>>
s21::Controller::getCreditCalculatedValue(const std::vector<double> &values, int creditType, int termType) {
    return model_->calculateCredit(values, creditType, termType);
}

std::map<std::string, std::vector<double>>
s21::Controller::getDepositCalculatedValue(const std::vector<double> &data,
                                           const std::vector<std::vector<std::string>> &replList,
                                           const std::vector<std::vector<std::string>> &withdrawList,
                                           bool capitalization) {
    return model_->calculateDeposit(data, replList, withdrawList, capitalization);
}

std::vector<std::string> s21::Controller::getMonthsData() {
    return model_->getMonthsData();
}

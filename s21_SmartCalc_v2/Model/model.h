#ifndef SRC_S21_SMARTCALC_V2_MODEL_MODEL_H_
#define SRC_S21_SMARTCALC_V2_MODEL_MODEL_H_

#include <map>
#include <vector>
#include <string>
#include <clocale>

#include "SimpleCalcModel/simplecalcmodel.h"
#include "CreditCalcModel/creditcalcmodel.h"
#include "DepositCalcModel/depositcalcmodel.h"

namespace s21 { class Model; }

class s21::Model {
 public:
    Model();
    std::string calculateExpression(const std::string &expression, const std::string &x);
    std::vector<std::pair<long double, long double>>
        graphPoints(const std::string &expression,
                  double xStart,
                  double xEnd);
    std::map<std::string, std::vector<double>>
        calculateCredit(const std::vector<double> &data, int creditType, int termType);
    std::map<std::string, std::vector<double>>
    calculateDeposit(const std::vector<double> &data,
                     const std::vector<std::vector<std::string>> &replList,
                     const std::vector<std::vector<std::string>> &withdrawList,
                     bool capitalization);
    std::vector<std::string> getMonthsData();
 private:
    std::vector<std::string> monthsData_;
};

#endif  // SRC_S21_SMARTCALC_V2_MODEL_MODEL_H_

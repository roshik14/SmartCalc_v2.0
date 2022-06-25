#ifndef SRC_S21_SMARTCALC_V2_MODEL_SIMPLECALCMODEL_SIMPLECALCMODEL_H_
#define SRC_S21_SMARTCALC_V2_MODEL_SIMPLECALCMODEL_SIMPLECALCMODEL_H_

#include <string>
#include <stack>
#include <cmath>
#include <algorithm>
#include <set>
#include "parsermodel.h"
#include "../additionalmodel.h"

namespace s21 { class SimpleCalcModel; }

class s21::SimpleCalcModel {
 public:
    explicit SimpleCalcModel(const std::string &expression, const std::string &x);
    std::string calculate();
 private:
    std::string input_;
    std::string x_;
    std::string output_;
    std::stack<long double> stack_;
    std::string calculateExpression();
    std::string replaceX();
    std::string getAnswer(const std::string &exression);
    void calculateReplacingExpression();
    void makeBinaryOperation(char operation);
    void makeUnaryFunction(char func_key);
    void readDigitInRpnString(size_t *i, std::string *parsedStr);
    void replaceAll(char c, const std::string &str);
    bool isFunctionOrUnary(char c);
    bool isEquation();
    bool cannotCalculate();
};

#endif  // SRC_S21_SMARTCALC_V2_MODEL_SIMPLECALCMODEL_SIMPLECALCMODEL_H_

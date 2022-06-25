#ifndef SRC_S21_SMARTCALC_V2_MODEL_SIMPLECALCMODEL_PARSERMODEL_H_
#define SRC_S21_SMARTCALC_V2_MODEL_SIMPLECALCMODEL_PARSERMODEL_H_

#include <stack>
#include <map>
#include <string>
#include <algorithm>
#include "../additionalmodel.h"

namespace s21 { class ParserModel; }

class s21::ParserModel {
 public:
    explicit ParserModel(const std::string &inputStr);
    std::string reversePolishNotationString();

 private:
    std::string const ERROR = "EXPRESSION ERROR";

    std::string input_;
    std::string output_;
    std::stack<char> stack_;
    char getFunctionKey(size_t *pos);
    bool isFunction(size_t pos);
    bool isFunctionInStack();
    bool isUnaryOperation(char current, size_t pos);
    bool isOpenBracket(char c);
    bool isCloseBracket(char c);
    bool isDot(char current);
    bool checkPriority(char a, char b);
    bool hasBracketsError();
    bool hasOpenBracketError(size_t i);
    bool hasDigitError(size_t i);
    bool hasFunctionError(size_t i);
    bool hasUnaryOperationError(size_t i);
    bool hasBinaryOperationError(size_t i);
    bool isLastIndex(size_t i);
    bool isMinusOrPlus(char c);
    void readCloseBracket();
    void readBinaryOperation(char current, size_t *pos);
    void readDigit(size_t *pos);
    void readFunction(size_t *pos);
    void readUnaryOperation(size_t pos);
    void readOpenBracket(size_t pos);
};



#endif  // SRC_S21_SMARTCALC_V2_MODEL_SIMPLECALCMODEL_PARSERMODEL_H_

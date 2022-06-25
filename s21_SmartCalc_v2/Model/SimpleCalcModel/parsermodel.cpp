#include "parsermodel.h"

s21::ParserModel::ParserModel(const std::string &inputStr) : input_(inputStr) {
}

std::string s21::ParserModel::reversePolishNotationString() {
    if (hasBracketsError())
        return ERROR;
    for (size_t i = 0; i < input_.length(); ++i) {
        char current = input_[i];
        if (output_ == ERROR)
            break;
        if (isdigit(current)) {
            readDigit(&i);
        } else if (isFunction(i)) {
            readFunction(&i);
        } else if (isUnaryOperation(current, i)) {
            readUnaryOperation(i);
        } else if (isOpenBracket(current)) {
            readOpenBracket(i);
        } else if (isCloseBracket(current)) {
            readCloseBracket();
        } else if (isBinaryOperation(current)) {
            readBinaryOperation(current, &i);
            if (hasBinaryOperationError(i))
                output_ = ERROR;
        } else if (!isDot(input_[i])) {
            output_ = ERROR;
        }
    }
    if (output_ != ERROR) {
        for (; !stack_.empty(); stack_.pop()) {
            output_ += std::string {stack_.top(), ' '};
        }
    }
    return output_;
}

void s21::ParserModel::readFunction(size_t *pos) {
    stack_.push(getFunctionKey(pos));
    if (hasFunctionError(*pos))
        output_ = ERROR;
}

void s21::ParserModel::readUnaryOperation(size_t pos) {
    char unary = input_[pos] == '-' ? 'u' : 'p';
    readBinaryOperation(unary, &pos);
    if (hasUnaryOperationError(pos)) {
        output_ = ERROR;
    }
}

void s21::ParserModel::readOpenBracket(size_t pos) {
    stack_.push(input_[pos]);
    if (hasOpenBracketError(pos))
        output_ = ERROR;
}

char s21::ParserModel::getFunctionKey(size_t *pos) {
    char result = 0;
    static const std::map<char, std::string> functions {
        {'s', "sin"}, {'c', "cos"}, {'t', "tan"},
        {'l', "ln"}, {'L', "log"}, {'C', "acos"},
        {'S', "asin"}, {'T', "atan"}, {'q', "sqrt"},
    };
    for (auto i = functions.begin(); i != functions.end(); ++i) {
        if (!input_.compare(*pos, i->second.length(), i->second)) {
            result = i->first;
            *pos += i->second.length() - 1;
        }
    }
    return result;
}

bool s21::ParserModel::hasOpenBracketError(size_t i) {
    return isLastIndex(i) || isCloseBracket(input_[i+1]);
}

bool s21::ParserModel::hasDigitError(size_t i) {
    return !isLastIndex(i) && !isBinaryOperation(input_[i+1]) && !isCloseBracket(input_[i+1]);
}

bool s21::ParserModel::hasFunctionError(size_t i) {
    return isLastIndex(i) || !isOpenBracket(input_[i+1]);
}

bool s21::ParserModel::hasUnaryOperationError(size_t i) {
    return isLastIndex(i) || isBinaryOperation(input_[i+1]);
}

bool s21::ParserModel::hasBinaryOperationError(size_t i) {
    return (i == 0 || hasUnaryOperationError(i)) && !isMinusOrPlus(input_[i+1]);
}

bool s21::ParserModel::isLastIndex(size_t i) {
    return i == (input_.length() - 1);
}

bool s21::ParserModel::isFunctionInStack() {
    static const std::string functionKeys = "cstlLCSTq";
    return functionKeys.find(stack_.top()) != std::string::npos;
}

bool s21::ParserModel::isUnaryOperation(char current, size_t pos) {
    return isMinusOrPlus(current)
        && (pos == 0 || (!isdigit(input_[pos-1]) && !isCloseBracket(input_[pos-1]) && input_[pos-1] != 'e'));
}

bool s21::ParserModel::isFunction(size_t pos) {
    return getFunctionKey(&pos);
}

bool s21::ParserModel::isOpenBracket(char current) {
    return current == '(';
}

bool s21::ParserModel::isCloseBracket(char current) {
    return current == ')';
}

bool s21::ParserModel::isDot(char current) {
    return current == '.';
}

bool s21::ParserModel::checkPriority(char a, char b) {
    static std::map<char, size_t> operations {
        {'+', 1}, {'-', 1}, {'*', 2},
        {'/', 2}, {'m', 2}, {'^', 3},
        {'p', 4}, {'u', 4}
    };
    return operations.find(b) != operations.end() ? operations.at(a) <= operations.at(b) : false;
}

bool s21::ParserModel::hasBracketsError() {
    return std::count(input_.begin(), input_.end(), '(')
        != std::count(input_.begin(), input_.end(), ')');
}

bool s21::ParserModel::isMinusOrPlus(char c) {
    return c == '+' || c == '-';
}

void s21::ParserModel::readCloseBracket() {
    for (; !isOpenBracket(stack_.top()); stack_.pop()) {
        output_ += std::string {stack_.top(), ' '};
    }
    stack_.pop();
    if (!stack_.empty() && isFunctionInStack()) {
        output_ += std::string {stack_.top(), ' '};
        stack_.pop();
    }
}

void s21::ParserModel::readBinaryOperation(char current, size_t *pos) {
    for (; !stack_.empty() && checkPriority(current, stack_.top()); stack_.pop()) {
        output_ += std::string {stack_.top(), ' '};
    }
    stack_.push(current);
    if (current == 'm') {
        size_t modLen = 2;
        *pos += modLen;
    }
}

void s21::ParserModel::readDigit(size_t *pos) {
    size_t digitLength = 0;
    const long double digit = std::stold(&input_[*pos], &digitLength);
    *pos += digitLength - 1;
    if (hasDigitError(*pos))
        output_ = ERROR;
    else
        output_ += std::to_string(digit) + ' ';
}

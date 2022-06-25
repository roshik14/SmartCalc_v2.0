#include "simplecalcmodel.h"

s21::SimpleCalcModel::SimpleCalcModel(const std::string &expression, const std::string &x) :
    input_(expression),
    x_(x),
    output_("") {
}

std::string s21::SimpleCalcModel::calculate() {
    if (isEquation())
        replaceAll('x', x_);

    output_ = calculateExpression();

    if (cannotCalculate())
        output_ = "CANNOT BE CALCULATED";

    return output_;
}

void s21::SimpleCalcModel::replaceAll(char c, const std::string &str) {
    std::string result;
    for (auto i = 0u; i < input_.length(); ++i) {
        if (input_[i] == c) {
            result += str;
        } else {
            result += input_[i];
        }
    }
    input_ = result;
}

std::string s21::SimpleCalcModel::calculateExpression() {
    ParserModel parser(input_);
    std::string parsedStr = parser.reversePolishNotationString();
    if (parsedStr == "EXPRESSION ERROR")
        return parsedStr;

    for (size_t i = 0; i < parsedStr.length(); ++i) {
        char current = parsedStr[i];
        if (std::isdigit(current))
            readDigitInRpnString(&i, &parsedStr);
        else if (isBinaryOperation(current))
            makeBinaryOperation(current);
        else if (isFunctionOrUnary(current))
            makeUnaryFunction(current);
    }
    output_ = std::to_string(stack_.top());
    return output_;
}

void s21::SimpleCalcModel::makeBinaryOperation(char operation) {
    long double second = stack_.top();
    stack_.pop();
    long double first = stack_.top();
    stack_.pop();
    if (operation == '+')
        stack_.push(first + second);
    else if (operation == '-')
        stack_.push(first - second);
    else if (operation == '*')
        stack_.push(first * second);
    else if (operation == '/')
        stack_.push(first / second);
    else if (operation == '^')
        stack_.push(pow(first, second));
    else if (operation == 'm')
        stack_.push(fmod(first, second));
}

void s21::SimpleCalcModel::makeUnaryFunction(char func_key) {
    double num = stack_.top();
    stack_.pop();
    if (func_key == 's')
        stack_.push(sin(num));
    else if (func_key == 'c')
        stack_.push(cos(num));
    else if (func_key == 't')
        stack_.push(tan(num));
    else if (func_key == 'l')
        stack_.push(log(num));
    else if (func_key == 'L')
        stack_.push(log10(num));
    else if (func_key == 'S')
        stack_.push(asin(num));
    else if (func_key == 'C')
        stack_.push(acos(num));
    else if (func_key == 'T')
        stack_.push(atan(num));
    else if (func_key == 'u')
        stack_.push(num * -1);
    else if (func_key == 'p')
        stack_.push(num * 1);
    else
        stack_.push(sqrt(num));
}

void s21::SimpleCalcModel::readDigitInRpnString(size_t *i, std::string *parsedStr) {
    size_t num_length = 0;
    long double num = std::stold(&parsedStr->at(*i), &num_length);
    stack_.push(num);
    *i += num_length - 1;
}

bool s21::SimpleCalcModel::isFunctionOrUnary(char current) {
    static const std::string functions = "sctlLSCTupq";
    return functions.find(current) != std::string::npos;
}

bool s21::SimpleCalcModel::isEquation() {
    return input_.find('x') != std::string::npos;
}

bool s21::SimpleCalcModel::cannotCalculate() {
    return std::set<std::string> {"inf", "-inf", "nan", "-nan"}.count(output_);
}


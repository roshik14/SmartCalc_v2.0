#include "additionalmodel.h"

bool s21::isBinaryOperation(char current) {
    static const std::string operations = "+/-^*m";
    return operations.find(current) != std::string::npos;
}

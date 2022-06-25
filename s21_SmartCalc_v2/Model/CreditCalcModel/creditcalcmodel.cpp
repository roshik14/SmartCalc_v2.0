#include "creditcalcmodel.h"

s21::CreditCalcModel::CreditCalcModel(): date_(new Date) {
}

s21::CreditCalcModel::~CreditCalcModel() {
    delete date_;
}

std::map<std::string, std::vector<double>>
s21::CreditCalcModel::calculate(const std::vector<double> &values, int creditType, int termType) {
    double percentRate = values.at(RATE) / PERCENT_MAX / Date::MONTHMAX;
    double totalPeriod = period(values.at(TERM), termType);
    CalculatedData data { 0, 0, 0, 0 };
    if (creditType == ANNUITY)
        data.monthPay = values.at(AMOUNT) *
            (percentRate + (percentRate/ (pow(1+percentRate, totalPeriod)-1)));
    else
        data.debtPart = values.at(AMOUNT) / totalPeriod;

    calculateCredit(&data, values, percentRate, creditType, totalPeriod);

    for (int i = 0; i < totalPeriod; ++i) {
        months_.push_back(date_->value());
        date_->increaseDate(Date::MONTH);
    }
    result_["overpay"].push_back(overpayValue());
    return result_;
}

void s21::CreditCalcModel::calculateCredit(
    CalculatedData *data,
    const std::vector<double> &values,
    double percentRate,
    int creditType,
    int period) {
        enum { MONTHPAY = 0, DEBTPART };
        double creditAmount = values.at(AMOUNT);
        while (period-- > 0) {
            double percentPerMonth = creditAmount * percentRate;
            if (creditType == DIFFERENTIATED)
                data->monthPay = data->debtPart+ percentPerMonth;
            else
                data->debtPart = data->monthPay - percentPerMonth;
            creditAmount -= data->debtPart;
            data->percentPerMonth = percentPerMonth;
            data->balance = creditAmount <= 0 ? -0.01 : creditAmount;
            addData(data);
        }
}

void s21::CreditCalcModel::addData(const CalculatedData *data) {
    result_["payment"].push_back(data->monthPay);
    result_["percentage"].push_back(data->percentPerMonth);
    result_["debtPart"].push_back(data->debtPart);
    result_["balance"].push_back(data->balance);
}

double s21::CreditCalcModel::period(double term, int termType) {
    return termType == YEARS_TYPE ? term * Date::MONTHMAX : term;
}

double s21::CreditCalcModel::overpayValue() {
    double result {};
    const std::vector<double> percentageVector = result_.at("percentage");
    for (auto i = percentageVector.begin(); i != percentageVector.end(); ++i)
        result += *i;
    return result;
}

std::vector<std::string> s21::CreditCalcModel::monthsData() {
    return months_;
}

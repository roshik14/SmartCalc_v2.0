#include "depositcalcmodel.h"

s21::DepositCalcModel::DepositCalcModel() : date_(new Date) {
    resultData_["percents"] = {};
    resultData_["depositRepl"] = {};
    resultData_["totalAmount"] = {};
}

s21::DepositCalcModel::~DepositCalcModel() {
    delete date_;
}

std::map<std::string, std::vector<double>>
s21::DepositCalcModel::calculate(const std::vector<double> &data,
                                 const NestedContainer &replList,
                                 const NestedContainer &withdrawList,
                                 bool capitalization) {
    enum { AMOUNT = 0, RATE, PERIOD, PERIOD_TYPE, FREQUENCY };

    double termValue = term(data.at(PERIOD), data.at(PERIOD_TYPE));
    int frequency = data.at(FREQUENCY);

    CalcData calcData {
        data.at(AMOUNT),  // get amount value
        data.at(RATE),  // get rate value
        termValue,
        frequency
    };

    evaluate(&calcData, replList, withdrawList, capitalization);
    return resultData_;
}

void s21::DepositCalcModel::evaluate(CalcData *data,
                                     const NestedContainer &replList,
                                     const NestedContainer &withdrawList,
                                     bool capitalization) {
    double totalPeriod = data->term;
    updateData(data->amount, 0, data->amount, date_->value());

    std::vector<ReplData> replDataContainer = fillReplDataContainer(replList, totalPeriod);
    std::vector<ReplData> withdrawDataContainer = fillReplDataContainer(withdrawList, totalPeriod);

    Date monthDate(date_->value());
    double monthPercents = 0;

    for (int i = 0; i < totalPeriod; ++i) {
        double percents = interestCharges(data);

        monthPercents += percents;

        if (capitalization)
            data->amount += percents;

        if (*date_ == monthDate)
            monthDate.increaseDate(Date::MONTH);

        date_->increaseDate(Date::DAY);

        if (data->freqType == Monthly && *date_ == monthDate) {
                updateData(data->amount, monthPercents, capitalization ? monthPercents : 0, date_->value());
                monthPercents = 0;
        }

        if (data->freqType == Everyday)
            updateData(data->amount, percents, capitalization ? percents : 0, date_->value());

        updatePartialData(data, &replDataContainer, PartialDataType::REPLENISHMENT);
        updatePartialData(data, &withdrawDataContainer, PartialDataType::WITHDRAW);
    }

    resultData_["totalPercents"].push_back(totalPercents());
    resultData_["taxAmount"].push_back(countTax());

    if (data->freqType == Monthly)
        sortResultData();
}

void s21::DepositCalcModel::updatePartialData(CalcData *data,
        std::vector<ReplData> *replList, PartialDataType type) {
    for (auto repl = replList->begin(); repl != replList->end(); ++repl) {
        if (*date_ == repl->date && repl->status == PartialDataStatus::UNCHECKED) {
            bool shouldUpdate = false;
            if (type == PartialDataType::REPLENISHMENT) {
                data->amount += repl->value;
                shouldUpdate = true;
            } else if (repl->value <= data->amount) {
                data->amount -= repl->value;
                repl->value *= -1;
                shouldUpdate = true;
            }
            if (shouldUpdate)
                updateData(data->amount, 0, repl->value, repl->date.value());

            repl->status = PartialDataStatus::CHECKED;
        }
    }
}

std::vector<s21::DepositCalcModel::ReplData>
s21::DepositCalcModel::fillReplDataContainer(const NestedContainer &replList,
                                             int totalPeriod) {
    std::vector<ReplData> replDataContainer = initReplDataContainer(replList);
    std::vector<ReplData> resultContainer;
    Date currentDate(date_->value());
    for (auto i = 0; i < totalPeriod; ++i) {
        for (auto repl = replDataContainer.begin(); repl != replDataContainer.end(); ++repl)  {
            if (currentDate == repl->date && repl->status == PartialDataStatus::UNCHECKED) {
                resultContainer.push_back(*repl);
                if (repl->type != "Monthly")
                    repl->status = PartialDataStatus::CHECKED;
                else
                    repl->date.increaseDate(Date::MONTH);
            }
        }
        currentDate.increaseDate(Date::DAY);
    }
    return resultContainer;
}


std::vector<s21::DepositCalcModel::ReplData>
s21::DepositCalcModel::initReplDataContainer(const NestedContainer &replList) {
    std::vector<ReplData> replDataContainer;
    enum { Type = 0, DateStr, Value };
    for (auto i = replList.begin(); i != replList.end(); ++i) {
            replDataContainer.push_back(
                { Date(i->at(DateStr)),  // date value string
                  i->at(Type),  // type value string
                  std::stod(i->at(Value)),   // replenishment value
                  PartialDataStatus::UNCHECKED,    // status of replenishment data
                });
    }
    return replDataContainer;
}

double s21::DepositCalcModel::countTax() {
    static const int freeTax = 11e4;
    static const double taxPercents = 0.13;
    double tax = resultData_["totalPercents"].front() - freeTax;
    return tax <= 0 ? 0 : tax * taxPercents;
}

double s21::DepositCalcModel::totalPercents() {
    double result = 0;
    auto percents = resultData_.at("percents");
    for (auto i = percents.begin(); i != percents.end(); ++i)
        result += *i;
    return result;
}

void s21::DepositCalcModel::updateData(double amount, double percents, double repl, const std::string &date) {
    resultData_["percents"].push_back(percents);
    resultData_["depositRepl"].push_back(repl);
    resultData_["totalAmount"].push_back(amount);
    months_.push_back(date);
}

double s21::DepositCalcModel::term(double term, int termType) {
    const int daysType = 2;
    if (termType != daysType) {
        return period(term, termType);
    }
    return term;
}

double s21::DepositCalcModel::period(double term, int termType) {
    enum { YEARS = 0, MONTHS };
    double result = 0;
    Date currentDate(date_->value());
    for (auto i = 0 ; i < term; ++i) {
        if (termType == YEARS) {
            result += currentDate.yearDaysCount();
            currentDate.increaseDate(Date::YEAR);
        } else {
            result += currentDate.monthDaysCount();
            currentDate.increaseDate(Date::MONTH);
        }
    }
    return result;
}

double s21::DepositCalcModel::interestCharges(const CalcData *data) {
    static const int percentMax = 100;
    return data->amount * data->rate / date_->yearDaysCount() / percentMax;
}

void s21::DepositCalcModel::sortResultData() {
    for (auto i = 0u; i < months_.size(); ++i) {
        for (auto j = 0u; j < months_.size() - i - 1; ++j) {
            Date current(months_[j]);
            Date next(months_[j+1]);
            if (current.isDayGreater(next)) {
                swapData(j, j+1);
            }
        }
    }
}

void s21::DepositCalcModel::swapData(int currentIndex, int nextIndex) {
    std::swap(resultData_["percents"].at(currentIndex), resultData_["percents"].at(nextIndex));
    std::swap(resultData_["depositRepl"].at(currentIndex), resultData_["depositRepl"].at(nextIndex));
    std::swap(resultData_["totalAmount"].at(currentIndex), resultData_["totalAmount"].at(nextIndex));
    std::swap(months_[currentIndex], months_[nextIndex]);
}

std::vector<std::string> s21::DepositCalcModel::monthsData() {
    return months_;
}


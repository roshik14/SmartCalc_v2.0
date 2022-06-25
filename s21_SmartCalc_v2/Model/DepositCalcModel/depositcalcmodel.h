#ifndef SRC_S21_SMARTCALC_V2_MODEL_DEPOSITCALCMODEL_DEPOSITCALCMODEL_H_
#define SRC_S21_SMARTCALC_V2_MODEL_DEPOSITCALCMODEL_DEPOSITCALCMODEL_H_

#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include "../date.h"

namespace s21 {
class DepositCalcModel;
}

class s21::DepositCalcModel {
    using ResultContainer = std::map<std::string, std::vector<double>>;
    using NestedContainer = std::vector<std::vector<std::string>>;
    using MonthsContainer = std::vector<std::string>;

 public:
    DepositCalcModel();
    DepositCalcModel(const DepositCalcModel &m) = delete;
    ~DepositCalcModel();
    DepositCalcModel& operator=(const DepositCalcModel &m) = delete;
    ResultContainer calculate(const std::vector<double> &data,
                              const NestedContainer &replList,
                              const NestedContainer &withdrawList,
                              bool capitalization);
    MonthsContainer monthsData();

 private:
    enum {
        Everyday = 0,
        Monthly,
    };

    enum PartialDataType {
        REPLENISHMENT = 0,
        WITHDRAW,
    };

    enum PartialDataStatus {
        UNCHECKED = 0,
        CHECKED,
        ADDED,
    };

    struct CalcData {
        double amount;
        double rate;
        double term;
        int freqType;
    };

    struct ReplData {
        Date date;
        std::string type;
        double value;
        PartialDataStatus status;
    };

    ResultContainer resultData_;
    MonthsContainer months_;
    Date *date_;
    void evaluate(CalcData *data,
                  const NestedContainer &replList,
                  const NestedContainer &withdrawList,
                  bool capitalization);
    std::vector<ReplData> initReplDataContainer(const NestedContainer &replList);
    std::vector<ReplData> fillReplDataContainer(const NestedContainer &replList,
                                                int totalPeriod);
    double totalPercents();
    double countTax();
    double interestCharges(const CalcData *data);
    double period(double term, int termType);
    double term(double term, int termType);
    void updateData(double amount,
                    double percents,
                    double repl,
                    const std::string &date);
    void updatePartialData(CalcData *data, std::vector<ReplData> *replList, PartialDataType type);
    void sortResultData();
    void swapData(int currentIndex, int nextIndex);
};

#endif  // SRC_S21_SMARTCALC_V2_MODEL_DEPOSITCALCMODEL_DEPOSITCALCMODEL_H_

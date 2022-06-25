#ifndef SRC_S21_SMARTCALC_V2_MODEL_CREDITCALCMODEL_CREDITCALCMODEL_H_
#define SRC_S21_SMARTCALC_V2_MODEL_CREDITCALCMODEL_CREDITCALCMODEL_H_

#include <string>
#include <map>
#include <vector>
#include <cmath>
#include "../date.h"

namespace s21 { class CreditCalcModel; }

class s21::CreditCalcModel {
 public:
    CreditCalcModel();
    CreditCalcModel(const CreditCalcModel &model) = delete;
    ~CreditCalcModel();
    CreditCalcModel& operator=(const CreditCalcModel &model) = delete;
    std::map<std::string, std::vector<double>>
        calculate(const std::vector<double> &values, int creditType, int termType);
    std::vector<std::string> monthsData();

 private:
    enum {
        ANNUITY = 0,
        DIFFERENTIATED,
    };

    enum {
        AMOUNT = 0,
        TERM,
        RATE
    };

    typedef struct {
        double monthPay;
        double debtPart;
        double percentPerMonth;
        double balance;
    } CalculatedData;

    Date *date_;
    static constexpr int YEARS_TYPE = 0;
    static constexpr int PERCENT_MAX = 100;
    std::map<std::string, std::vector<double>> result_;
    std::vector<std::string> months_;
    void addData(const CalculatedData *data);
    double overpayValue();
    double period(double term, int termType);
    void calculateCredit(CalculatedData *data,
                     const std::vector<double> &values,
                     double percentRate,
                     int creditType,
                     int period);
};

#endif  // SRC_S21_SMARTCALC_V2_MODEL_CREDITCALCMODEL_CREDITCALCMODEL_H_

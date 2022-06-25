#ifndef SRC_S21_SMARTCALC_V2_CONTROLLER_CONTROLLER_H_
#define SRC_S21_SMARTCALC_V2_CONTROLLER_CONTROLLER_H_

#include "../Model/model.h"

namespace s21 { class Controller; }

class s21::Controller {
 public:
    explicit Controller(Model *model);
    std::string getCalculatedValue(const std::string &expression, const std::string &x);
    std::vector<std::pair<long double, long double>>
    getPointsForGraph(const std::string &expression,
                      double xStart,
                      double xEnd);
    std::map<std::string, std::vector<double>>
    getCreditCalculatedValue(const std::vector<double> &data,
                             int creditType,
                             int termType);
    std::map<std::string, std::vector<double>>
    getDepositCalculatedValue(const std::vector<double> &data,
                              const std::vector<std::vector<std::string>> &replList,
                              const std::vector<std::vector<std::string>> &withdrawList,
                              bool capitalization);
    std::vector<std::string> getMonthsData();

 private:
    Model *model_;
};

#endif  // SRC_S21_SMARTCALC_V2_CONTROLLER_CONTROLLER_H_

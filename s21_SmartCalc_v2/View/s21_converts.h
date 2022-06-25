#ifndef SRC_S21_SMARTCALC_V2_VIEW_S21_CONVERTS_H_
#define SRC_S21_SMARTCALC_V2_VIEW_S21_CONVERTS_H_

#include <QMap>
#include <QString>
#include <QVector>
#include <string>
#include <map>
#include <vector>

namespace s21 {
    QMap<QString, QVector<double>> fromStdMap(const std::map<std::string, std::vector<double>> &map);
    QVector<QString> fromStdVector(const std::vector<std::string> &data);
}

#endif  // SRC_S21_SMARTCALC_V2_VIEW_S21_CONVERTS_H_

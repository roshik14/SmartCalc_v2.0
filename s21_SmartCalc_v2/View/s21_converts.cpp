#include "s21_converts.h"

QMap<QString, QVector<double>> s21::fromStdMap(const std::map<std::string, std::vector<double>> &data) {
    QMap<QString, QVector<double>> result;
    for (auto i = data.begin(); i != data.end(); i++) {
        result.insert(QString::fromStdString(i->first),
                     QVector<double>(i->second.begin(), i->second.end()));
    }
    return result;
}

QVector<QString> s21::fromStdVector(const std::vector<std::string> &data) {
    QVector<QString> result;
    for (auto i = data.begin(); i != data.end(); i++) {
        result.append(QString::fromStdString(i->data()));
    }
    return result;
}

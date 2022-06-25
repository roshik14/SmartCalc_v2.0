#include "tableview.h"

s21::TableView::TableWidget::TableWidget(int calcType, QObject *parent)
    : QAbstractTableModel{parent},
    calcType_(calcType) {
}

void s21::TableView::TableWidget::updateData
(const QMap<QString, QVector<double>> &data, const QVector<QString> &monthsData) {
    data_ = data;
    monthsData_ = monthsData;
}

int s21::TableView::TableWidget::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return monthsData_.size();
}

int s21::TableView::TableWidget::columnCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return calcType_ == CreditCalc ? CREDITCOLS : DEPOSITCOLS;
}

QVariant s21::TableView::TableWidget::data(const QModelIndex &index, int role) const {
    if (index.isValid() && role == Qt::DisplayRole) {
        return calcType_ == CreditCalc ? creditData(index) : depositData(index);
    }
    return QVariant();
}

QVariant s21::TableView::TableWidget::headerData
(int section, Qt::Orientation orientation, int role) const {
    QList<QString> creditHeaders {"Date", "Payment", "Main Loan Payment", "Interest", "Balance"};
    QList<QString> depositHeaders {"Date", "Percents", "Deposit replenishment", "Total amount"};
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        return calcType_ == CreditCalc ? creditHeaders[section] : depositHeaders[section];
    }
    return QVariant();
}

QVariant s21::TableView::TableWidget::creditData(const QModelIndex &index) const {
    QVector<double> payment = data_.value("payment");
    QVector<double> debtPart = data_.value("debtPart");
    QVector<double> percentage = data_.value("percentage");
    QVector<double> balance = data_.value("balance");

    QVector<double> dataValues {
        payment.size() > index.row() ? payment[index.row()] : 0,
        debtPart.size() > index.row() ? debtPart[index.row()] : 0,
        percentage.size() > index.row() ? percentage[index.row()] : 0,
        balance.size() > index.row() ? balance[index.row()] : 0
    };
    return currentValue(dataValues, index);
}

QVariant s21::TableView::TableWidget::depositData(const QModelIndex &index) const {
    QVector<double> percents = data_.value("percents");
    QVector<double> depositRepls = data_.value("depositRepl");
    QVector<double> totalAmounts = data_.value("totalAmount");

    QVector<double> dataValues {
        percents.size() > index.row() ? percents[index.row()] : 0,
        depositRepls.size() > index.row() ? depositRepls[index.row()] : 0,
        totalAmounts.size() > index.row() ? totalAmounts[index.row()] : 0,
    };

    return currentValue(dataValues, index);
}

QVariant s21::TableView::TableWidget::currentValue(const QVector<double> &values,
                                                   const QModelIndex &index) const {
    return !(index.column()) ?
        monthsData_.value(index.row()) :
        QString::number(values.value(index.column() - 1), 'd', 2);
}


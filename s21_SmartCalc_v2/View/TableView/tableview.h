#ifndef SRC_S21_SMARTCALC_V2_VIEW_TABLEVIEW_TABLEVIEW_H_
#define SRC_S21_SMARTCALC_V2_VIEW_TABLEVIEW_TABLEVIEW_H_

#include <QWidget>
#include <QBrush>
#include <QAbstractTableModel>

namespace Ui { class TableView; }
namespace s21 { class TableView; }

class s21::TableView : public QWidget {
    Q_OBJECT

 public:
    explicit TableView(int calcType, QWidget *parent = nullptr);
    ~TableView();
    void showData(const QMap<QString,
                  QVector<double>> &data,
                  const QVector<QString> &monthsData);

 private:
    class TableWidget;
    Ui::TableView *ui;
    int calcType_;
    TableWidget *table_;
};

class s21::TableView::TableWidget : public QAbstractTableModel {
    Q_OBJECT

 public:
    explicit TableWidget(int calcType, QObject *parent = nullptr);
    void updateData(const QMap<QString, QVector<double>> &data, const QVector<QString> &monthsData);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

 private:
    enum {
        CreditCalc = 0,
        DepositCalc
    };

    int calcType_;
    const int CREDITCOLS = 5;
    const int DEPOSITCOLS = 4;

    QMap<QString, QVector<double>> data_;
    QVector<QString> monthsData_;
    QVariant creditData(const QModelIndex &index) const;
    QVariant depositData(const QModelIndex &index) const;
    QVariant currentValue(const QVector<double> &values, const QModelIndex &index) const;
};

#endif  // SRC_S21_SMARTCALC_V2_VIEW_TABLEVIEW_TABLEVIEW_H_

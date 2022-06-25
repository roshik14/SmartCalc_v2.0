#ifndef SRC_S21_SMARTCALC_V2_VIEW_CREDITCALCVIEW_CREDITCALCVIEW_H_
#define SRC_S21_SMARTCALC_V2_VIEW_CREDITCALCVIEW_CREDITCALCVIEW_H_

#include <QWidget>
#include <QChart>
#include <QPieSeries>

#include "../../Controller/controller.h"
#include "../TableView/tableview.h"
#include "../s21_converts.h"

namespace Ui { class CreditCalcView; }
namespace s21 { class CreditCalcView; }

class s21::CreditCalcView : public QWidget {
    Q_OBJECT

 public:
    explicit CreditCalcView(Controller *controller, QWidget *parent = nullptr);
    ~CreditCalcView();

 private:
    Ui::CreditCalcView *ui;
    Controller *controller_;
    TableView *tableView_;
    QPieSeries *series_;
    QChart *chart_;
    struct WindowSizeStruct {
        double startWidth = 541;
        double expandWidth = 1207;
        double height = 615;
    } WindowSize;

    typedef struct {
        double firstPay;
        double lastPay;
        double overPay;
        double totalPay;
    } DisplayData;

    QMap<QString, QVector<double>> data_;
    QVector<QString> monthsData_;
    void startEventLoop();
    void connectSignals();
    void customizeChart();
    void updateData(const std::vector<double> &values, DisplayData *displayData, int creditType);
    void updateDisplayData(const DisplayData &data);
    void updateChartData(double amount, double overPay);
    void updateWindow(int creditType);

 private slots:
    void equalBtnClickHandler();
    void clearBtnClickHandler();
    void tableBtnClickHandler();
    void typeValueChangeHandler(int index);
};

#endif  // SRC_S21_SMARTCALC_V2_VIEW_CREDITCALCVIEW_CREDITCALCVIEW_H_

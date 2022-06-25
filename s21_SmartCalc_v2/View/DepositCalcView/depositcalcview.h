#ifndef SRC_S21_SMARTCALC_V2_VIEW_DEPOSITCALCVIEW_DEPOSITCALCVIEW_H_
#define SRC_S21_SMARTCALC_V2_VIEW_DEPOSITCALCVIEW_DEPOSITCALCVIEW_H_

#include <QWidget>
#include <QMap>
#include "../../Controller/controller.h"
#include "../TableView/tableview.h"
#include "../addpaymentview.h"
#include "../s21_converts.h"

namespace Ui { class DepositCalcView; }
namespace s21 { class DepositCalcView; }

class s21::DepositCalcView : public QWidget {
    Q_OBJECT

 public:
    explicit DepositCalcView(Controller *controller, QWidget *parent = nullptr);
    ~DepositCalcView();

 private:
    Ui::DepositCalcView *ui;
    Controller *controller_;
    TableView *tableView_;
    AdditionalPaymentView *replView_;
    AdditionalPaymentView *withdrawView_;
    QMap<QString, QVector<double>> data_;
    QVector<QString> months_;
    struct WindowSizeStruct {
        double startHeight = 480;
        double expandHeight = 680;
        double width = 1065;
    } WindowSize_;

    struct HomeBtnPosStruct {
        double x = 50;
        double startY = 400;
        double moveY = 600;
    } HomeBtnPosition;

    void startEventLoop();
    void connectSignals();
    void updateData(const std::vector<double> &userData,
                    bool isCapitalized);
    void updateDisplayData();


 private slots:
    void equalBtnClickHandler();
    void updateWindowHandler();
    void clearBtnClickHandler();
    void tableBtnClickHandler();
    void replBtnClickHandler();
    void withdrawBtnClickHandler();
    void typeValueChangeHandler(int index);
};


#endif  // SRC_S21_SMARTCALC_V2_VIEW_DEPOSITCALCVIEW_DEPOSITCALCVIEW_H_

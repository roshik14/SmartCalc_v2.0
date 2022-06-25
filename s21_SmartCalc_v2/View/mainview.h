#ifndef SRC_S21_SMARTCALC_V2_VIEW_MAINVIEW_H_
#define SRC_S21_SMARTCALC_V2_VIEW_MAINVIEW_H_

#include <QMainWindow>
#include <QWidget>
#include <QList>
#include <QPushButton>
#include <QScreen>
#include "../Controller/controller.h"
#include "SimpleCalcView/simplecalcview.h"
#include "GraphCalcView/graphcalcview.h"
#include "CreditCalcView/creditcalcview.h"
#include "DepositCalcView/depositcalcview.h"

namespace Ui { class MainView; }
namespace s21 { class MainView; }

class s21::MainView : public QMainWindow {
    Q_OBJECT

 public:
    explicit MainView(Controller *controller, QWidget *parent = nullptr);
    ~MainView();

    void showCalc(const QString &name);
    void startEventLoop();

 private:
    Ui::MainView *ui;
    Controller *controller_;

    void setWidgetToCenter(QWidget *widget);
    void execWidget(QWidget *widget);
    void connectSignals();

 private slots:
  void openCalcHandler();
  void closeCalcHandler();
};

#endif  // SRC_S21_SMARTCALC_V2_VIEW_MAINVIEW_H_

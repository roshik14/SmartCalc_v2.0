#ifndef SRC_S21_SMARTCALC_V2_VIEW_SIMPLECALCVIEW_SIMPLECALCVIEW_H_
#define SRC_S21_SMARTCALC_V2_VIEW_SIMPLECALCVIEW_SIMPLECALCVIEW_H_

#include <QWidget>
#include "../../Controller/controller.h"

namespace Ui { class SimpleCalcView; }
namespace s21 { class SimpleCalcView; }

class s21::SimpleCalcView : public QWidget {
    Q_OBJECT

 public:
    explicit SimpleCalcView(Controller *controller, QWidget* parent = nullptr);
    ~SimpleCalcView();

 private:
    Ui::SimpleCalcView* ui;
    Controller *controller_;
    void connectSignals();

 private slots:
    void clearLineEditHandler();
    void undoLastActionHandler();
    void changeFuncTextHandler();
    void equalBtnClickHandler();
    void textBtnClickHandler();
};


#endif  // SRC_S21_SMARTCALC_V2_VIEW_SIMPLECALCVIEW_SIMPLECALCVIEW_H_

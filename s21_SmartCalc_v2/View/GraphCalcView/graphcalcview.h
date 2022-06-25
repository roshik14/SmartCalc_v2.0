#ifndef SRC_S21_SMARTCALC_V2_VIEW_GRAPHCALCVIEW_GRAPHCALCVIEW_H_
#define SRC_S21_SMARTCALC_V2_VIEW_GRAPHCALCVIEW_GRAPHCALCVIEW_H_

#include <QWidget>
#include <QSpinBox>
#include "../../Controller/controller.h"
#include "QCustomPlot/qcustomplot.h"

namespace Ui { class GraphCalcView; }

namespace s21 { class GraphCalcView; }

class s21::GraphCalcView : public QWidget {
    Q_OBJECT

 public:
    explicit GraphCalcView(Controller *controller, QWidget *parent = nullptr);
    ~GraphCalcView();

 private:
    Ui::GraphCalcView *ui;
    Controller *controller_;

    typedef struct graphData {
        QString expression;
        QString xStart;
        QString xEnd;
        QString yStart;
        QString yEnd;
    } graphData;

    void startEventLoop();
    void connectSignals();
    void setGraphStyle();
    void changeRangeState(QSpinBox *spin, int state, int value);
    bool drawGraph(const graphData &data);
    double getInterval(const QString &str, double defaultNum);

 private slots:
    void equalBtnClickHandler();
    void clearBtnClickHandler();
    void autoBtnClickHandler(int state);
};

#endif  // SRC_S21_SMARTCALC_V2_VIEW_GRAPHCALCVIEW_GRAPHCALCVIEW_H_

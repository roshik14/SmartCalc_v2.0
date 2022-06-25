#include "graphcalcview.h"
#include "ui_graphcalcview.h"

s21::GraphCalcView::GraphCalcView(Controller *controller, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GraphCalcView),
    controller_(controller) {
    ui->setupUi(this);
    startEventLoop();
}

s21::GraphCalcView::~GraphCalcView() {
    delete ui;
}

void s21::GraphCalcView::startEventLoop() {
    ui->plot->hide();
    ui->plot->addGraph();
    setGraphStyle();
    connectSignals();
}

void s21::GraphCalcView::connectSignals() {
    connect(ui->equalBtn, &QPushButton::clicked, this, &GraphCalcView::equalBtnClickHandler);
    connect(ui->autoYBtn, &QCheckBox::stateChanged, this, &GraphCalcView::autoBtnClickHandler);
    connect(ui->autoXBtn, &QCheckBox::stateChanged, this, &GraphCalcView::autoBtnClickHandler);
    connect(ui->clearBtn, &QPushButton::clicked, this, &GraphCalcView::clearBtnClickHandler);
    connect(ui->homeBtn, &QPushButton::clicked, this, &GraphCalcView::close);
}

void s21::GraphCalcView::equalBtnClickHandler() {
    graphData data;
    data.expression = ui->inputEdit->text();
    data.xStart = ui->xStartSpin->text();
    data.xEnd = ui->xEndSpin->text();
    data.yStart = ui->yStartSpin->text();
    data.yEnd = ui->yEndSpin->text();
    if (data.expression.length()) {
        auto const canDraw = drawGraph(data);
        if (!canDraw) {
            ui->inputEdit->setText("EXPRESSION ERROR");
        }
    }
}

bool s21::GraphCalcView::drawGraph(const graphData &data) {
    auto xStart = getInterval(data.xStart, -10);
    auto xEnd = getInterval(data.xEnd, 10);
    auto yStart = getInterval(data.yStart, -1);
    auto yEnd = getInterval(data.yEnd, 1);

    ui->plot->xAxis->setRange(xStart, xEnd);
    ui->plot->yAxis->setRange(yStart, yEnd);

    auto const &points = controller_->getPointsForGraph(data.expression.toStdString(), xStart, xEnd);
    auto const isInvalid = qIsInf(static_cast<double>(points[0].first)) &&
        qIsInf(static_cast<double>(points[0].second));
    if (isInvalid) {
        return false;
    } else {
        QVector<double> pointsX;
        QVector<double> pointsY;
        for (auto i = points.begin(); i != points.end(); ++i) {
            pointsX.append(i->first);
            pointsY.append(i->second);
        }
        ui->plot->graph(0)->setData(pointsX, pointsY);
        ui->plot->replot();
        ui->plot->show();
    }
    return true;
}

void s21::GraphCalcView::setGraphStyle() {
    QColor color;
    color.setRgb(25, 26, 25);

    ui->plot->setBackground(QBrush(color));
    ui->plot->xAxis->setLabel("X axis");
    ui->plot->yAxis->setLabel("Y axis");

    color.setRgb(255, 245, 238);

    ui->plot->xAxis->setTickLabelColor(color);
    ui->plot->xAxis->setLabelColor(color);
    ui->plot->yAxis->setTickLabelColor(color);
    ui->plot->yAxis->setLabelColor(color);
    color.setRgb(128, 128, 128);
    ui->plot->xAxis->setTickPen(QPen(color));
    ui->plot->yAxis->setTickPen(QPen(color));

    color.setRgb(255, 255, 0);

    ui->plot->graph(0)->setPen(QPen(color));
    ui->plot->graph(0)->setAdaptiveSampling(true);
    ui->plot->graph(0)->setLineStyle(QCPGraph::lsNone);
    ui->plot->graph(0)->setScatterStyle(QCPScatterStyle::ssDisc);
}

void s21::GraphCalcView::autoBtnClickHandler(int state) {
    if (sender()->objectName() == "autoXBtn") {
        changeRangeState(ui->xStartSpin, state, -10);
        changeRangeState(ui->xEndSpin, state, 10);
    } else {
        changeRangeState(ui->yStartSpin, state, -1);
        changeRangeState(ui->yEndSpin, state, 1);
    }
}

void s21::GraphCalcView::changeRangeState(QSpinBox *spin, int state, int startValue) {
    if (state == Qt::Unchecked) {
        spin->setEnabled(true);
    } else {
        spin->setValue(startValue);
        spin->setEnabled(false);
    }
}

void s21::GraphCalcView::clearBtnClickHandler() {
    ui->plot->hide();
    ui->inputEdit->clear();
    emit ui->autoXBtn->stateChanged(Qt::Checked);
    emit ui->autoYBtn->stateChanged(Qt::Checked);
    ui->autoXBtn->setCheckState(Qt::Checked);
    ui->autoYBtn->setCheckState(Qt::Checked);
}

double s21::GraphCalcView::getInterval(const QString &str, double defaultNum) {
    return str == "" ? defaultNum : str.toDouble();
}

#include "creditcalcview.h"
#include "ui_creditcalcview.h"

s21::CreditCalcView::CreditCalcView(Controller *controller, QWidget *parent):
    QWidget(parent),
    ui(new Ui::CreditCalcView),
    controller_(controller),
    tableView_(new TableView(0)),
    series_(new QPieSeries(this)),
    chart_(new QChart) {
    ui->setupUi(this);
    startEventLoop();
}

s21::CreditCalcView::~CreditCalcView() {
    series_->clear();
    delete chart_;
    delete tableView_;
    delete ui;
}

void s21::CreditCalcView::startEventLoop() {
    connectSignals();
    customizeChart();
    resize(WindowSize.startWidth, WindowSize.height);
}

void s21::CreditCalcView::connectSignals() {
     connect(ui->equalBtn, &QPushButton::clicked, this, &CreditCalcView::equalBtnClickHandler);
     connect(ui->clearBtn, &QPushButton::clicked, this, &CreditCalcView::clearBtnClickHandler);
     connect(ui->homeBtn, &QPushButton::clicked, this, &CreditCalcView::close);
     connect(ui->termTypeComboBox, &QComboBox::currentIndexChanged,
             this, &s21::CreditCalcView::typeValueChangeHandler);
     connect(ui->tableBtn, &QPushButton::clicked, this, &CreditCalcView::tableBtnClickHandler);
}

void s21::CreditCalcView::customizeChart() {
    series_->append("Credit", 0);
    series_->append("Overpay", 0);
    for (int i {}; i < series_->count(); i++) {
        auto const &slice = series_->slices().at(i);
        slice->setColor(i ? QColor(240, 84, 84) : QColor(3, 80, 111));
        slice->setLabelVisible();
        slice->setLabelPosition(QPieSlice::LabelInsideHorizontal);
    }
    chart_->setTheme(QChart::ChartThemeDark);
    auto const chartWidth = 600.0;
    auto const chartHeight = 300.0;
    chart_->setPlotArea(QRectF((ui->chartView->width() - chartWidth) / 2,
                              (ui->chartView->height() - chartHeight) / 2,
                              chartWidth, chartHeight));
    chart_->legend()->hide();
    chart_->addSeries(series_);
    ui->chartView->setChart(chart_);
    ui->chartView->setRenderHint(QPainter::Antialiasing);
}

void s21::CreditCalcView::equalBtnClickHandler() {
    std::vector<double> values {
        ui->amountValueSpin->value(),
        static_cast<double>(ui->termValueSpin->value()),
        ui->rateValueSpin->value()
    };
    auto const creditType = ui->typeValueWidget->currentIndex();
    DisplayData displayData { 0, 0, 0, 0 };
    updateData(values, &displayData, creditType);
    updateDisplayData(displayData);
    updateChartData(values.at(0), displayData.overPay);
    updateWindow(creditType);
}


void s21::CreditCalcView::updateDisplayData(const DisplayData &data) {
    if (!data_.empty()) {
        ui->monthPayAnswer->setValue(data.firstPay);
        ui->lastPayAnswer->setValue(data.lastPay);
        ui->overPayAnswer->setValue(data.overPay);
        ui->totalPayAnswer->setValue(data.totalPay);
    }
}

void s21::CreditCalcView::updateChartData(double amount, double overPay) {
    series_->slices().at(0)->setValue(amount);
    series_->slices().at(1)->setValue(overPay);
    for (int i {}; i < series_->count(); i++) {
        auto slice = series_->slices().at(i);
        auto percent = static_cast<int>(qRound((slice->percentage() * 100)));
        slice->setLabel(QString::number(percent) + "%");
    }
}

void s21::CreditCalcView::updateWindow(int creditType) {
    if (creditType) {
        ui->monthPayLabel->setText("First payment");
        ui->lastPaymentLabel->show();
        ui->lastPayAnswer->show();
        ui->rubLabel_4->show();
    } else {
        ui->monthPayLabel->setText("Monthly payment");
        ui->lastPaymentLabel->hide();
        ui->lastPayAnswer->hide();
        ui->rubLabel_4->hide();
    }
    setMinimumSize(WindowSize.expandWidth, WindowSize.height);
    setMaximumSize(WindowSize.expandWidth, WindowSize.height);
    resize(WindowSize.expandWidth, WindowSize.height);
}

void s21::CreditCalcView::updateData(const std::vector<double> &values,
                                     DisplayData *displayData,
                                     int creditType) {
    int termType = ui->termTypeComboBox->currentIndex();

    data_ = fromStdMap(controller_->getCreditCalculatedValue(values, creditType, termType));
    monthsData_ = fromStdVector(controller_->getMonthsData());

    if (!data_.empty()) {
        displayData->firstPay = data_.value("payment").constFirst();
        displayData->lastPay = data_.value("payment").constLast();
        displayData->overPay = data_.value("overpay").constFirst();
        displayData->totalPay = values.at(0) + displayData->overPay;
    }
}

void s21::CreditCalcView::tableBtnClickHandler() {
    tableView_->showData(data_, monthsData_);
}

void s21::CreditCalcView::clearBtnClickHandler() {
    ui->amountValueSpin->setValue(100000);
    ui->termValueSpin->setValue(1);
    ui->rateValueSpin->setValue(20);
    ui->termTypeComboBox->setCurrentIndex(0);
    ui->typeValueWidget->setCurrentIndex(0);
    setMinimumSize(WindowSize.startWidth, WindowSize.height);
    setMaximumSize(WindowSize.startWidth, WindowSize.height);
    resize(WindowSize.startWidth, WindowSize.height);
}

void s21::CreditCalcView::typeValueChangeHandler(int index) {
    if (index) {
        const int monthsMax = 600;
        ui->termValueSpin->setMaximum(monthsMax);
    } else {
        const int yearsMax = 50;
        ui->termValueSpin->setMaximum(yearsMax);
    }
}

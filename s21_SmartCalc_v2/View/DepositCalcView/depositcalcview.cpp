#include "depositcalcview.h"
#include "ui_depositcalcview.h"

s21::DepositCalcView::DepositCalcView(Controller *controller, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DepositCalcView),
    controller_(controller),
    tableView_(new TableView(1)),
    replView_(new AdditionalPaymentView),
    withdrawView_(new AdditionalPaymentView) {
    ui->setupUi(this);
    startEventLoop();
}

s21::DepositCalcView::~DepositCalcView() {
    delete withdrawView_;
    delete replView_;
    delete tableView_;
    delete ui;
}

void s21::DepositCalcView::startEventLoop() {
    resize(WindowSize_.width, WindowSize_.startHeight);
    connectSignals();
}

void s21::DepositCalcView::connectSignals() {
    connect(ui->equalBtn, &QPushButton::clicked, this, &DepositCalcView::equalBtnClickHandler);
    connect(ui->equalBtn, &QPushButton::clicked, this, &DepositCalcView::updateWindowHandler);
    connect(ui->clearBtn, &QPushButton::clicked, this, &DepositCalcView::clearBtnClickHandler);
    connect(ui->tableBtn, &QPushButton::clicked, this, &DepositCalcView::tableBtnClickHandler);
    connect(ui->replBtn, &QPushButton::clicked, this, &DepositCalcView::replBtnClickHandler);
    connect(ui->withdrawBtn, &QPushButton::clicked, this, &DepositCalcView::withdrawBtnClickHandler);
    connect(ui->periodTypeWidget, &QComboBox::currentIndexChanged,
            this, &s21::DepositCalcView::typeValueChangeHandler);
}

void s21::DepositCalcView::equalBtnClickHandler() {
    const std::vector<double> userData {
        ui->amountInputWidget->value(),
        ui->rateInputWidget->value(),
        static_cast<double>(ui->periodInputWidget->value()),
        static_cast<double>(ui->periodTypeWidget->currentIndex()),
        static_cast<double>(ui->frequencyTypeWidget->currentIndex()),
    };

    auto const isCapitalized = ui->capitalCheck->isChecked();
    updateData(userData, isCapitalized);
    updateDisplayData();
}

void s21::DepositCalcView::updateData(const std::vector<double> &userData,
                                      bool isCapitalized) {
    auto const &replList = replView_->data();
    auto const &withdrawList = withdrawView_->data();
    data_ = fromStdMap(controller_->
            getDepositCalculatedValue(userData,
                                      replList,
                                      withdrawList,
                                      isCapitalized));
    months_ = fromStdVector(controller_->getMonthsData());
}

void s21::DepositCalcView::updateDisplayData() {
    ui->interestOutputWidget->setValue(data_.value("totalPercents").constFirst());
    ui->depAmountOutputWidget->setValue(data_.value("totalAmount").constLast());
    ui->taxOutputWidget->setValue(data_.value("taxAmount").constFirst());
}

void s21::DepositCalcView::updateWindowHandler() {
    setMinimumSize(WindowSize_.width, WindowSize_.expandHeight);
    setMaximumSize(WindowSize_.width, WindowSize_.expandHeight);
    resize(WindowSize_.width, WindowSize_.expandHeight);
    ui->homeBtn->setGeometry(HomeBtnPosition.x, HomeBtnPosition.moveY,
                             ui->homeBtn->width(), ui->homeBtn->height());
}

void s21::DepositCalcView::clearBtnClickHandler() {
    setMinimumSize(WindowSize_.width, WindowSize_.startHeight);
    setMaximumSize(WindowSize_.width, WindowSize_.startHeight);
    resize(WindowSize_.width, WindowSize_.startHeight);
    ui->homeBtn->setGeometry(HomeBtnPosition.x, HomeBtnPosition.startY,
                             ui->homeBtn->width(), ui->homeBtn->height());
    ui->amountInputWidget->setValue(100000);
    ui->rateInputWidget->setValue(5);
    ui->periodInputWidget->setValue(1);
    ui->periodTypeWidget->setCurrentIndex(0);
    ui->frequencyTypeWidget->setCurrentIndex(0);
    ui->capitalCheck->setChecked(false);
    replView_->clear();
    withdrawView_->clear();
}

void s21::DepositCalcView::typeValueChangeHandler(int index) {
    if (index) {
        const int monthsMax = 600;
        ui->periodInputWidget->setMaximum(monthsMax);
    } else {
        const int yearsMax = 50;
        ui->periodInputWidget->setMaximum(yearsMax);
    }
}

void s21::DepositCalcView::tableBtnClickHandler() {
    tableView_->showData(data_, months_);
}

void s21::DepositCalcView::replBtnClickHandler() {
    replView_->show();
}

void s21::DepositCalcView::withdrawBtnClickHandler() {
    withdrawView_->show();
}

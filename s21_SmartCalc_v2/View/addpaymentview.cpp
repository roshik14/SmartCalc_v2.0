#include "addpaymentview.h"
#include "ui_addpaymentview.h"

s21::AdditionalPaymentView::AdditionalPaymentView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdditionalPaymentView),
    data_(new QStringList) {
    ui->setupUi(this);
    listModel_ = new QStringListModel(ui->listView);
    connectSignals();
}

s21::AdditionalPaymentView::~AdditionalPaymentView() {
    delete ui;
}

void s21::AdditionalPaymentView::connectSignals() {
    connect(ui->addBtn, &QPushButton::clicked, this, &AdditionalPaymentView::addBtnClickHandler);
    connect(ui->homeBtn, &QPushButton::clicked, this, &AdditionalPaymentView::cancelBtnClickHandler);
    connect(ui->delBtn, &QPushButton::clicked, this, &AdditionalPaymentView::deleteBtnClickHandler);
    connect(ui->applyBtn, &QPushButton::clicked, this, &AdditionalPaymentView::close);
}

std::vector<std::vector<std::string>> s21::AdditionalPaymentView::data() {
    std::vector<std::vector<std::string>> resVector;
    for (auto i = data_->begin(); i != data_->end(); ++i) {
        auto tmp = i->split(' ');
        std::vector<std::string> inner;
        for (const auto &j : qAsConst(tmp)) {
            inner.push_back(j.toStdString());
        }
        resVector.push_back(inner);
    }
    return resVector;
}

void s21::AdditionalPaymentView::addBtnClickHandler() {
    *data_ += ui->replTypeWidget->currentText() + ' ' + ui->dateEdit->text() + ' '
                + ui->replInputWidget->text();
    listModel_->setStringList(*data_);
    ui->listView->setModel(listModel_);
}

void s21::AdditionalPaymentView::deleteBtnClickHandler() {
    const auto index = ui->listView->currentIndex().row();
    if (index != -1) {
        listModel_->removeRows(ui->listView->currentIndex().row(), 1);
        data_->removeAt(index);
    }
}

void s21::AdditionalPaymentView::clear() {
    cancelBtnClickHandler();
}

void s21::AdditionalPaymentView::cancelBtnClickHandler() {
    listModel_->removeRows(0, data_->size());
    data_->clear();
    ui->replTypeWidget->setCurrentIndex(0);
    ui->dateEdit->setDate(QDate::currentDate());
    ui->replInputWidget->setValue(1);
    hide();
}

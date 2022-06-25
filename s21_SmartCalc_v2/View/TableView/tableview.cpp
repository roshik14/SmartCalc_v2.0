#include "tableview.h"
#include "ui_tableview.h"

s21::TableView::TableView(int calcType, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TableView),
    calcType_(calcType) {
    ui->setupUi(this);
}

s21::TableView::~TableView() {
    delete ui;
}

void s21::TableView::showData(const QMap<QString,
                              QVector<double>> &data,
                              const QVector<QString> &monthsData) {
    table_ = new TableWidget(calcType_, this);
    table_->updateData(data, monthsData);
    ui->tableView->setModel(table_);
    ui->tableView->setColumnWidth(0, 100);
    for (int i = 1; i < table_->columnCount(); ++i)
        ui->tableView->setColumnWidth(i, 200);
    show();
}

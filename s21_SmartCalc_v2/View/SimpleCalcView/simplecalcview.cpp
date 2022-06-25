#include "simplecalcview.h"
#include "ui_simplecalcview.h"

s21::SimpleCalcView::SimpleCalcView(Controller *controller, QWidget* parent)
    : QWidget(parent),
      ui(new Ui::SimpleCalcView),
      controller_(controller) {
    ui->setupUi(this);
    connectSignals();
}

s21::SimpleCalcView::~SimpleCalcView() {
    delete ui;
}

void s21::SimpleCalcView::connectSignals() {
    for (auto i = 0; i < ui->btns_grid->rowCount(); ++i) {
        for (auto j = 0; j < ui->btns_grid->columnCount(); ++j) {
            auto *btn = qobject_cast<QPushButton*>(ui->btns_grid->itemAtPosition(i, j)->widget());
            if (btn != nullptr) {
                auto const &btnLabel = btn->text();
                if (btnLabel == "C")
                    connect(btn, &QPushButton::clicked, this, &s21::SimpleCalcView::clearLineEditHandler);
                else if (btnLabel == "CE")
                    connect(btn, &QPushButton::clicked, this, &s21::SimpleCalcView::undoLastActionHandler);
                else if (btnLabel == "arc")
                    connect(btn, &QPushButton::clicked, this, &s21::SimpleCalcView::changeFuncTextHandler);
                else if (btnLabel == "=")
                    connect(btn, &QPushButton::clicked, this, &s21::SimpleCalcView::equalBtnClickHandler);
                else
                    connect(btn, &QPushButton::clicked, this, &s21::SimpleCalcView::textBtnClickHandler);
            }
        }
    }
    connect(ui->homeBtn, &QPushButton::clicked, this, &s21::SimpleCalcView::close);
}

void s21::SimpleCalcView::textBtnClickHandler() {
    QPushButton *buttonSender = qobject_cast<QPushButton*>(sender());
    ui->input_edit->insert(buttonSender->text());
}

void s21::SimpleCalcView::equalBtnClickHandler() {
    auto const &expression = ui->input_edit->text();
    if (expression.length()) {
        auto x = ui->replaceSpin->text();
        x.replace(',', '.');
        auto const &result = QString::fromStdString(
                controller_->getCalculatedValue(expression.toStdString(), x.toStdString()));
        if (result.length())
            ui->input_edit->setText(result);
    }
    ui->replaceSpin->setValue(0.0);
}

void s21::SimpleCalcView::clearLineEditHandler() {
    ui->input_edit->clear();
    ui->replaceSpin->setValue(0.0);
}

void s21::SimpleCalcView::undoLastActionHandler() {
    ui->input_edit->backspace();
}

void s21::SimpleCalcView::changeFuncTextHandler() {
    QList<QPushButton*> buttons { ui->sin_btn, ui->cos_btn, ui->tan_btn };
    for (auto *btn : qAsConst(buttons)) {
        if (ui->reverse_func_btn->isChecked())
            btn->setText("a" + btn->text());
        else
            btn->setText(btn->text().remove(0, 1));
    }
}

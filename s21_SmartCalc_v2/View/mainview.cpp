#include "mainview.h"
#include "ui_view.h"

s21::MainView::MainView(Controller *controller, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainView),
    controller_(controller) {
    ui->setupUi(this);
}

s21::MainView::~MainView() {
    delete ui;
}

void s21::MainView::startEventLoop() {
    setWidgetToCenter(this);
    connectSignals();
    show();
}

void s21::MainView::connectSignals() {
    QList<QPushButton*> openCalcButtons {
        ui->simpleCalcBtn, ui->graphCalcBtn,
        ui->creditCalcBtn, ui->depositCalcBtn
    };
    for (QPushButton *btn : qAsConst(openCalcButtons))
        connect(btn, &QPushButton::clicked, this, &MainView::openCalcHandler);
    connect(ui->quitBtn, &QPushButton::clicked, this, &MainView::close);
}

void s21::MainView::execWidget(QWidget *widget) {
    if (widget != nullptr) {
        QList<QPushButton*> btnList = widget->findChildren<QPushButton*>("homeBtn");
        connect(btnList[0], &QPushButton::clicked, this, &MainView::closeCalcHandler);
        setWidgetToCenter(widget);
        widget->show();
    }
}

void s21::MainView::setWidgetToCenter(QWidget *widget) {
    QScreen *screen = QGuiApplication::primaryScreen();
    double centerX = (screen->geometry().width() - widget->width()) / 2;
    double centerY = (screen->geometry().height() - widget->height()) / 2;
    widget->setGeometry(centerX, centerY, widget->width(), widget->height());
}

void s21::MainView::openCalcHandler() {
    QWidget *widget = nullptr;
    auto const &objName = sender()->objectName();
    if (objName == "simpleCalcBtn")
        widget = new SimpleCalcView(controller_);
    else if (objName == "graphCalcBtn")
        widget = new GraphCalcView(controller_);
    else if (objName == "creditCalcBtn")
        widget = new CreditCalcView(controller_);
    else
        widget = new DepositCalcView(controller_);
    hide();
    execWidget(widget);
}

void s21::MainView::closeCalcHandler() {
    QWidget *widget = qobject_cast<QWidget*>(sender()->parent());
    if (widget != nullptr)
        delete widget;
    setWidgetToCenter(this);
    show();
}

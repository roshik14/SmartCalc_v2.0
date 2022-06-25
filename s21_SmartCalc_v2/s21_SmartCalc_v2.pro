QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Controller/controller.cpp \
    Model/date.cpp \
    Model/SimpleCalcModel/parsermodel.cpp \
    Model/SimpleCalcModel/simplecalcmodel.cpp \
    Model/CreditCalcModel/creditcalcmodel.cpp \
    Model/DepositCalcModel/depositcalcmodel.cpp \
    Model/additionalmodel.cpp \
    Model/model.cpp \
    View/addpaymentview.cpp \
    View/TableView/tableview.cpp \
    View/TableView/tablewidget.cpp \
    View/CreditCalcView/creditcalcview.cpp \
    View/DepositCalcView/depositcalcview.cpp \
    View/GraphCalcView/graphcalcview.cpp \
    View/GraphCalcView/QCustomPlot/qcustomplot.cpp \
    View/SimpleCalcView/simplecalcview.cpp \
    View/mainview.cpp \
    View/s21_converts.cpp \
    main.cpp


HEADERS += \
    Controller/controller.h \
    Model/date.h \
    Model/SimpleCalcModel/parsermodel.h \
    Model/SimpleCalcModel/simplecalcmodel.h \
    Model/CreditCalcModel/creditcalcmodel.h \
    Model/DepositCalcModel/depositcalcmodel.h \
    Model/additionalmodel.h \
    Model/model.h \
    View/CreditCalcView/creditcalcview.h \
    View/addpaymentview.h \
    View/TableView/tableview.h \
    View/DepositCalcView/depositcalcview.h \
    View/GraphCalcView/graphcalcview.h \
    View/GraphCalcView/QCustomPlot/qcustomplot.h \
    View/SimpleCalcView/simplecalcview.h \
    View/mainview.h \
    View/s21_converts.h


FORMS += \
    View/Ui/addpaymentview.ui \
    View/Ui/simplecalcview.ui \
    View/Ui/graphcalcview.ui \
    View/Ui/creditcalcview.ui \
    View/Ui/depositcalcview.ui \
    View/Ui/tableview.ui \
    View/Ui/view.ui

ICON = icon.icns

# Default rules for deployment.
qnx: target.path = ~/
else: unix:!android: target.path = ~/Applications/
!isEmpty(target.path): INSTALLS += target

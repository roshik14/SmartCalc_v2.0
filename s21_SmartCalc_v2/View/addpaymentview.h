#ifndef SRC_S21_SMARTCALC_V2_VIEW_ADDPAYMENTVIEW_H_
#define SRC_S21_SMARTCALC_V2_VIEW_ADDPAYMENTVIEW_H_

#include <QWidget>
#include <QListView>
#include <QStringListModel>

namespace Ui { class AdditionalPaymentView; }
namespace s21 { class AdditionalPaymentView; }

class s21::AdditionalPaymentView : public QWidget {
    Q_OBJECT

 public:
    explicit AdditionalPaymentView(QWidget *parent = nullptr);
    ~AdditionalPaymentView();
    std::vector<std::vector<std::string>> data();
    void clear();

 private:
    Ui::AdditionalPaymentView *ui;
    QStringList *data_;
    QStringListModel *listModel_;
    void connectSignals();

 private slots:
    void addBtnClickHandler();
    void cancelBtnClickHandler();
    void deleteBtnClickHandler();
};

#endif  // SRC_S21_SMARTCALC_V2_VIEW_ADDPAYMENTVIEW_H_

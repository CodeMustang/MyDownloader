#ifndef DEPTHDIALOG_H
#define DEPTHDIALOG_H

#include <QDialog>

namespace Ui {
class DepthDialog;
}

class DepthDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DepthDialog(QWidget *parent = 0);
    ~DepthDialog();

private slots:
    void on_pushButton_clicked();
    void closeEvent(QCloseEvent *event);
signals:
    void dialogClosed();
private:
    Ui::DepthDialog *ui;
};

#endif // DEPTHDIALOG_H

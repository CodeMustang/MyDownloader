#ifndef CHOOSEDIR_H
#define CHOOSEDIR_H

#include <QDialog>
#include <QtCore>
#include <QDirModel>
namespace Ui {
class ChooseDir;
}

class ChooseDir : public QDialog
{
    Q_OBJECT

public:
    explicit ChooseDir(QWidget *parent = 0);
    ~ChooseDir();

private slots:
    void on_pushButton_clicked();
    void closeEvent(QCloseEvent *event);
    void on_pushButton_2_clicked();
signals:
    void dialogClosed();
private:
    Ui::ChooseDir *ui;
    QDirModel *saveFilesModel;
};

#endif // CHOOSEDIR_H

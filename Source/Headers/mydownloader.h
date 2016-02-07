#ifndef MYDOWNLOADER_H
#define MYDOWNLOADER_H

#include <QMainWindow>
#include <QTextEdit>
#include <QProcess>
#include <aboutdialog.h>
#include <choosedir.h>
#include <depthdialog.h>
namespace Ui {
class MyDownloader;
}

class MyDownloader : public QMainWindow
{
    Q_OBJECT
public:
    explicit MyDownloader(QWidget *parent = 0);


    QString static fileToSavePath;
    QString static myDepth;
    bool static pressed_x,pressed_x_depth;
    ~MyDownloader();

private slots:
    void on_actionAbout_triggered();

    void on_pushButton_clicked();
    void printOutputText();


    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::MyDownloader *ui;
    AboutDialog *mDialog;
    ChooseDir *dirDialog;

    DepthDialog *depthDialog;
    QString input,outputTextToString;

    QByteArray outputTextLog;
    QProcess *download;
};

#endif // MYDOWNLOADER_H

#include "depthdialog.h"
#include "ui_depthdialog.h"
#include "mydownloader.h"
#include <QCloseEvent>
QString MyDownloader::myDepth;
DepthDialog::DepthDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DepthDialog)
{
    ui->setupUi(this);

}

DepthDialog::~DepthDialog()
{
    delete ui;
}

void DepthDialog::on_pushButton_clicked()
{

            MyDownloader::myDepth = ui->lineEdit->text();

     DepthDialog::done(1);
}
void DepthDialog::closeEvent(QCloseEvent *event){
    MyDownloader::pressed_x_depth = true;
    emit dialogClosed();
    event->accept();
}

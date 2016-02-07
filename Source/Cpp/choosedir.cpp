#include "choosedir.h"
#include "ui_choosedir.h"
#include "QInputDialog"
#include "mydownloader.h"
#include <QCloseEvent>
ChooseDir::ChooseDir(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChooseDir)
{
    ui->setupUi(this);
    saveFilesModel = new QDirModel(this);
    saveFilesModel->setReadOnly(false);
    saveFilesModel->setFilter(QDir::NoDotAndDotDot | QDir::Dirs); // only directories
    saveFilesModel->setSorting(QDir::Name); // sort only by name

    ui->treeView->setModel(saveFilesModel);

    QModelIndex startPath = saveFilesModel->index("/home/");

    ui->treeView->setRootIndex(startPath);
    ui->treeView->expand(startPath);
    ui->treeView->scrollTo(startPath);
    ui->treeView->setCurrentIndex(startPath);
    ui->treeView->resizeColumnToContents(0);
}

ChooseDir::~ChooseDir()
{
    delete ui;
}

void ChooseDir::on_pushButton_clicked()
{
    //create new folder
    QModelIndex myIndex = ui->treeView->currentIndex();

    if(myIndex.isValid()){

        QString newFolder = QInputDialog::getText(this,"Create new folder ","Folder name : ");

        newFolder = newFolder.simplified();
        newFolder.replace(" ","");

        if(!newFolder.isEmpty())
            saveFilesModel->mkdir(myIndex,newFolder);
        else
            return ;
    }
    else
        return ;


}

void ChooseDir::on_pushButton_2_clicked()
{

    //save path
   QString filePath = saveFilesModel->filePath(ui->treeView->currentIndex());

   MyDownloader::fileToSavePath = filePath;

   ChooseDir::done(1);

}
void ChooseDir::closeEvent(QCloseEvent *event){
    MyDownloader::pressed_x = true;
    emit dialogClosed();
    event->accept();
}

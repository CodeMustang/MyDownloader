#include "mydownloader.h"
#include "ui_mydownloader.h"
#include "aboutdialog.h"
#include "QMessageBox"
#include "QListWidgetItem"
#include "QDesktopServices"
#include "unistd.h"
QString MyDownloader::fileToSavePath;
bool MyDownloader::pressed_x,MyDownloader::pressed_x_depth;

QString getFullCommand(QString filePath){

    QString command = "";
    if(!QDir("Website").exists()){
    command.append("mkdir ");
    command.append(filePath);
    command.append("/Website;");
    }
    command.append("wget -P ");
    command.append(filePath);
    command.append("/Website/ -r --level=");
    command.append(MyDownloader::myDepth);
    command.append(" --no-clobber --progress=bar --show-progress -q --adjust-extension --convert-links --page-requisites --random-wait --no-parent --tries=2 -e robots=off  -nd -H -U mozilla ");

    return command;

}

QString getUrls(QString filePath,QString input){
    QString command = "wget --spider -N -m ";
    command.append(input);
    command.append(" 2>&1 |head -n 500| grep '^--' | awk '{ print $3 }' | grep -v '\\.\\(css\\|js\\|png\\|gif\\|jpg\\|JPG\\)$' |sort | uniq > ");
    command.append(filePath + "/links.txt");

    return command;
}



MyDownloader::MyDownloader(QWidget *parent) :

    QMainWindow(parent),
    ui(new Ui::MyDownloader)
{
        ui->setupUi(this);
        pressed_x = true;
        ui->pushButton_4->setVisible(false);
        ui->pushButton_2->setVisible(false);
        ui->pushButton_3->setVisible(false);
        ui->textEdit->setTextColor(Qt::darkMagenta);
}

MyDownloader::~MyDownloader()
{
    delete ui;
}

void MyDownloader::on_actionAbout_triggered()
{
    mDialog = new AboutDialog(this);
    mDialog->show();
}

void MyDownloader::on_pushButton_clicked()
{

    pressed_x = false;
    ui->pushButton_3->setVisible(false);
    input = ui->lineEdit->text();

    if(input.isEmpty() || !QRegularExpression("(?:https?|ftp)://\\S+").match(input).hasMatch())
    QMessageBox::information(this,"Error","Not an url / webpage !");

    else{


        dirDialog= new ChooseDir(this);
        dirDialog->setWindowFlags((windowFlags() | Qt::WindowCloseButtonHint) & ~Qt::WindowMaximizeButtonHint & ~Qt::WindowMinimizeButtonHint);
        dirDialog->exec(); // we want to  pause the application while selecting the directory


   if(!fileToSavePath.isEmpty()&&!pressed_x){
       ui->listWidget->clear();
       outputTextLog.clear();
       outputTextToString.clear();
       QString input = ui->lineEdit->text();



       QMessageBox *msg = new QMessageBox(this);
       msg->setWindowTitle("Generating webpages ...");
       msg->setText("Please wait... (max 20 s)");
       msg->setStandardButtons(0);
       msg->show();



       QProcess *urlProcess = new QProcess(this);
       urlProcess->setProcessChannelMode(QProcess::MergedChannels); //it prints everything , even errors

       QEventLoop waitLoop;
       connect(urlProcess, SIGNAL(finished(int, QProcess::ExitStatus)),&waitLoop, SLOT(quit()));
       urlProcess->start("sh",QStringList() << "-c" <<"cd ;" + getUrls(fileToSavePath,input));
       waitLoop.exec();

       if(msg->isVisible()){
           msg->setText("Done");
           msg->addButton(QMessageBox::Ok);
           msg->exec();
       }


       QFile linksFile(fileToSavePath + "/links.txt");
        if (linksFile.open(QIODevice::ReadOnly))
        {

           QTextStream in(&linksFile);
           bool started = false;
          while(!started){
           while(!in.atEnd())
           {
              started = true;
              QString link = in.readLine();

              if(link.startsWith("http://") || link.startsWith("https://")){
              QListWidgetItem *linkItem = new QListWidgetItem;
              linkItem->setText(link);
              linkItem->setTextColor(Qt::darkBlue);

              ui->listWidget->addItem(linkItem);
              }

           }

        }
       }
        linksFile.flush();
        linksFile.close();


        ui->pushButton_4->setVisible(true);
   }

 }

}




void MyDownloader::printOutputText(){
    QTextCursor scrollBar =  ui->textEdit->textCursor();
    outputTextLog.append(download->readAllStandardOutput());
    outputTextToString.append(outputTextLog);
    ui->textEdit->setText(outputTextToString);
    scrollBar.movePosition(QTextCursor::End);   //move the scroll always at bottom to view current progress
    ui->textEdit->setTextCursor(scrollBar);

}




void MyDownloader::on_pushButton_2_clicked()
{
    download->kill();


    ui->pushButton_3->setVisible(true);
    ui->pushButton_2->setVisible(false);
}

void MyDownloader::on_pushButton_3_clicked()
{
     ui->pushButton_2->setVisible(false);
     ui->pushButton_3->setVisible(true);
     QDesktopServices::openUrl(QUrl::fromLocalFile(fileToSavePath)); // to open file manager / explorer
}

void MyDownloader::on_pushButton_4_clicked()
{
    pressed_x_depth = false;

    depthDialog = new DepthDialog(this);
    depthDialog->setWindowFlags((windowFlags() | Qt::WindowCloseButtonHint) & ~Qt::WindowMaximizeButtonHint & ~Qt::WindowMinimizeButtonHint);
    depthDialog->exec();


    if(!pressed_x_depth){
    download = new QProcess(this);
    download->setProcessChannelMode(QProcess::MergedChannels);
    connect(download,SIGNAL(readyReadStandardOutput()),this ,SLOT(printOutputText()));
    connect(download,SIGNAL(finished(int)),this,SLOT(on_pushButton_3_clicked()));
    download->start("sh",QStringList() << "-c" <<"cd ;" + getFullCommand(fileToSavePath) +  ui->listWidget->currentItem()->text());

    ui->pushButton_2->setVisible(true);
    ui->pushButton_3->setVisible(false);
}

}

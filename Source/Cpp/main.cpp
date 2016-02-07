#include "mydownloader.h"
#include <QApplication>
#include <QLabel>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyDownloader w;
    w.show();
    w.centralWidget()->releaseKeyboard();
    return a.exec();
}

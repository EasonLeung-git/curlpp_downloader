#include "MainWindow.hh"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Curlpp downloader");
    w.show();
    return a.exec();
}

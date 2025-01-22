#include "mainwindow.h"
#include <QApplication>
int main(int argc, char *argv[]){
    QApplication app(argc, argv);

    MainWindow w;
    w.show();
    return app.exec(); // 等待应用程序关闭
}

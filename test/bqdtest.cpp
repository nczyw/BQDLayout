#include "bqdlayout.h"
#include <QMainWindow>
#include <cstddef>
int main(int argc, char *argv[]){
    QApplication app(argc, argv);

    QMainWindow mainWindow;
    mainWindow.show();


    settingsBQDLayout(NULL);
    return app.exec(); // 等待应用程序关闭
}

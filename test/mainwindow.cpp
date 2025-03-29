#include "mainwindow.h"
#include "bqdlayout.h"
#include <QHBoxLayout>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    auto widget = new QWidget(this);
    auto hbox = new QHBoxLayout;
    hbox->addWidget(btnBQDLayout);
    widget->setLayout(hbox);
    setCentralWidget(widget);
    connect(btnBQDLayout,&QPushButton::clicked,this,[this]{
        createBQDLayoutFile();
    //    printfBQDCode("C:/Users/Sublime/Desktop/pdftest/NewBQD.bqd","C:/Users/Sublime/Desktop/pdftest/NewBQD.pdf",1,nullptr);
    //    settingsBQDLayout("C:/Users/Sublime/Desktop/pdftest/NewBQD.bqd",static_cast<void *>(this));
    });
}

MainWindow::~MainWindow() {}

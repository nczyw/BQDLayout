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
    connect(btnBQDLayout,&QPushButton::clicked,this,[]{
        settingsBQDLayout(nullptr);
    });
}

MainWindow::~MainWindow() {}

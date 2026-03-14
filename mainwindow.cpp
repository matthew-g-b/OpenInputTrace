#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , inputState(this)
{
    ui->setupUi(this);

    // InputState setup
    inputState.setControllerIndex(0);
    inputState.startPolling(16);
}

MainWindow::~MainWindow()
{
    delete ui;
}

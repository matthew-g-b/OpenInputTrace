#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QQuickWidget>
#include <QQmlContext>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , inputState(this)
{
    ui->setupUi(this);

    // InputState setup
    inputState.setControllerIndex(0);
    inputState.startPolling(16);

    // Connect axes to widgets in view
    connect(&inputState, &InputState::stateChanged, this, [this](){
        int value = static_cast<int>(inputState.rightTrigger() * 100.0f);
        ui->rightTriggerBar->setValue(value);});

    // Create a QQuickWidget, expose controller state to the QML scene
    QQuickWidget *quickWidget = new QQuickWidget(this);
    quickWidget->rootContext()->setContextProperty("inputState", &inputState);
    quickWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);
    //quickWidget->setSource(QUrl("qrc:/MainView.qml"));
    quickWidget->setSource(QUrl("qrc:/StandardControllerView.qml"));
    if (quickWidget->status() == QQuickWidget::Error) {
        qDebug() << quickWidget->errors();
    }

    QVBoxLayout *layout = new QVBoxLayout(ui->quickViewContainer);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(quickWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

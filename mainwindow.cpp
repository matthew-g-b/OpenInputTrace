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

    // Hide analog input drift labels
    ui->rightTriggerDriftLabel->setVisible(false);
    ui->leftTriggerDriftLabel->setVisible(false);
    ui->rightStickDriftLabel->setVisible(false);
    ui->leftStickDriftLabel->setVisible(false);

    // InputState setup
    inputState.setControllerIndex(0);
    inputState.startPolling(16);

    // Drift timer setup
    m_rightTriggerDriftTimer = new QTimer(this);
    m_rightTriggerDriftTimer->setSingleShot(true);

    m_leftTriggerDriftTimer = new QTimer(this);
    m_leftTriggerDriftTimer->setSingleShot(true);

    m_rightStickDriftTimer = new QTimer(this);
    m_rightStickDriftTimer->setSingleShot(true);


    // Right trigger drift message display
    connect(m_rightTriggerDriftTimer, &QTimer::timeout, this, [this]() {
       // ui->rightTriggerDriftLabel->setText("Possible right trigger drift");
        ui->rightTriggerDriftLabel->show();
    });

    // Left trigger drift message display
    connect(m_leftTriggerDriftTimer, &QTimer::timeout, this, [this]() {
        //ui->leftTriggerDriftLabel->setText("Possible left trigger drift");
        ui->leftTriggerDriftLabel->show();
    });

    // Right stick drift message display
    connect(m_rightStickDriftTimer, &QTimer::timeout, this, [this]() {
        //ui->rightTriggerDriftLabel->setText("Possible right trigger drift");
        ui->rightStickDriftLabel->show();
    });

    // Analog input drift detection
    connect(&inputState, &InputState::stateChanged, this, [this](){
        float rightTriggerValue = inputState.rightTrigger();
        float leftTriggerValue = inputState.leftTrigger();
        float rightStickMagnitude = inputState.rightStickMagnitude();


        // Ui widget for testing input
        int value = static_cast<int>(rightTriggerValue * 100.0f);
        ui->rightTriggerBar->setValue(value);

        // Stick drift detection parameters
        constexpr float driftMin = 0.03f;
        constexpr float driftMax = 0.15f;
        constexpr int driftPersistenceMs = 500; //2000

        bool RTinSuspiciousRange = (rightTriggerValue >= driftMin && rightTriggerValue <= driftMax);
        bool LTinSuspiciousRange = (leftTriggerValue >= driftMin && leftTriggerValue <= driftMax);
        bool RSinSuspiciousRange = (rightStickMagnitude >= driftMin && rightStickMagnitude <= driftMax);

        // Detect right trigger drift
        if (RTinSuspiciousRange) {
            if (!m_rightTriggerInDriftRange) {
                m_rightTriggerInDriftRange = true;
                m_rightTriggerDriftTimer->start(driftPersistenceMs);
            }
        } else {
            m_rightTriggerInDriftRange = false;
            m_rightTriggerDriftTimer->stop();
            ui->rightTriggerDriftLabel->hide();
        }

        // Detect left trigger drift
        if (LTinSuspiciousRange) {
            if (!m_leftTriggerInDriftRange) {
                m_leftTriggerInDriftRange = true;
                m_leftTriggerDriftTimer->start(driftPersistenceMs);
            }
        } else {
            m_leftTriggerInDriftRange = false;
            m_leftTriggerDriftTimer->stop();
            ui->leftTriggerDriftLabel->hide();
        }

        // Detect right stick drift
        if (RSinSuspiciousRange) {
            if (!m_rightStickInDriftRange) {
                m_rightStickInDriftRange = true;
                m_rightStickDriftTimer->start(driftPersistenceMs);
            }
        } else {
            m_rightStickInDriftRange = false;
            m_rightStickDriftTimer->stop();
            ui->rightStickDriftLabel->hide();
        }
    });

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

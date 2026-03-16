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

    //Hide analog input drift labels
    ui->rightTriggerDriftLabel->setVisible(false);
    ui->leftTriggerDriftLabel->setVisible(false);

    // InputState setup
    inputState.setControllerIndex(0);
    inputState.startPolling(16);

    // Connect axes to widgets in view
    m_rightTriggerDriftTimer = new QTimer(this);
    m_rightTriggerDriftTimer->setSingleShot(true);

    ui->rightTriggerDriftLabel->hide();

    connect(m_rightTriggerDriftTimer, &QTimer::timeout, this, [this]() {
        ui->rightTriggerDriftLabel->setText("Possible right trigger drift detected");
        ui->rightTriggerDriftLabel->show();
    });

    connect(&inputState, &InputState::stateChanged, this, [this](){
        float triggerValue = inputState.rightTrigger();
        int value = static_cast<int>(triggerValue * 100.0f);
        ui->rightTriggerBar->setValue(value);

        constexpr float driftMin = 0.03f;
        constexpr float driftMax = 0.15f;
        constexpr int driftPersistenceMs = 2000;

        bool inSuspiciousRange = (triggerValue >= driftMin && triggerValue <= driftMax);

        if (inSuspiciousRange) {
            if (!m_rightTriggerInDriftRange) {
                m_rightTriggerInDriftRange = true;
                m_rightTriggerDriftTimer->start(driftPersistenceMs);
            }
        } else {
            m_rightTriggerInDriftRange = false;
            m_rightTriggerDriftTimer->stop();
            ui->rightTriggerDriftLabel->hide();
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

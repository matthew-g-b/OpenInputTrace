#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "inputstate.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    InputState inputState;

    //Analog input drift timers
    QTimer *m_rightTriggerDriftTimer = nullptr;
    bool m_rightTriggerInDriftRange = false;

    QTimer *m_leftTriggerDriftTimer = nullptr;
    bool m_leftTriggerInDriftRange = false;

    QTimer *m_rightStickDriftTimer = nullptr;
    bool m_rightStickInDriftRange = false;
};
#endif // MAINWINDOW_H

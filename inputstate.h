#ifndef INPUTSTATE_H
#define INPUTSTATE_H

#include <QObject>
#include <QTimer>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <xinput.h>

class InputState : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool connected READ isConnected NOTIFY connectionChanged)

    Q_PROPERTY(float leftStickX READ leftStickX NOTIFY stateChanged)
    Q_PROPERTY(float leftStickY READ leftStickY NOTIFY stateChanged)
    Q_PROPERTY(float rightStickX READ rightStickX NOTIFY stateChanged)
    Q_PROPERTY(float rightStickY READ rightStickY NOTIFY stateChanged)

    Q_PROPERTY(float leftTrigger READ leftTrigger NOTIFY stateChanged)
    Q_PROPERTY(float rightTrigger READ rightTrigger NOTIFY stateChanged)

    Q_PROPERTY(bool dpadUp READ dpadUp NOTIFY stateChanged)
    Q_PROPERTY(bool dpadDown READ dpadDown NOTIFY stateChanged)
    Q_PROPERTY(bool dpadLeft READ dpadLeft NOTIFY stateChanged)
    Q_PROPERTY(bool dpadRight READ dpadRight NOTIFY stateChanged)

    Q_PROPERTY(bool start READ start NOTIFY stateChanged)
    Q_PROPERTY(bool back READ back NOTIFY stateChanged)

    Q_PROPERTY(bool leftThumb READ leftThumb NOTIFY stateChanged)
    Q_PROPERTY(bool rightThumb READ rightThumb NOTIFY stateChanged)

    Q_PROPERTY(bool leftShoulder READ leftShoulder NOTIFY stateChanged)
    Q_PROPERTY(bool rightShoulder READ rightShoulder NOTIFY stateChanged)

    Q_PROPERTY(bool buttonA READ buttonA NOTIFY stateChanged)
    Q_PROPERTY(bool buttonB READ buttonB NOTIFY stateChanged)
    Q_PROPERTY(bool buttonX READ buttonX NOTIFY stateChanged)
    Q_PROPERTY(bool buttonY READ buttonY NOTIFY stateChanged)

    // Mangnitude properties
    Q_PROPERTY(float rightStickMagnitude READ rightStickMagnitude NOTIFY stateChanged)
    Q_PROPERTY(float leftStickMagnitude READ leftStickMagnitude NOTIFY stateChanged)


public:
    explicit InputState(QObject *parent = nullptr);

    // Polling control
    void startPolling(int intervalMs = 16); // ~60 FPS default
    void stopPolling();

    // Choose which XInput controller slot to read [0-3]
    void setControllerIndex(DWORD index);
    DWORD controllerIndex() const;

    // Connection state
    bool isConnected() const;

    // Normalized analog values
    float leftStickX() const;
    float leftStickY() const;
    float rightStickX() const;
    float rightStickY() const;

    float leftTrigger() const;
    float rightTrigger() const;

    // Analog magnitude values
    float rightStickMagnitude() const;
    float leftStickMagnitude() const;

    // Digital buttons
    bool dpadUp() const;
    bool dpadDown() const;
    bool dpadLeft() const;
    bool dpadRight() const;

    bool start() const;
    bool back() const;

    bool leftThumb() const;
    bool rightThumb() const;

    bool leftShoulder() const;
    bool rightShoulder() const;

    bool buttonA() const;
    bool buttonB() const;
    bool buttonX() const;
    bool buttonY() const;

signals:
    void stateChanged();
    void connectionChanged(bool connected);

public slots:
    void pollController();

private:
    QTimer m_pollTimer;

    DWORD m_controllerIndex = 0;
    bool m_connected = false;

    // Cache packet number so we can skip unnecessary updates
    DWORD m_lastPacketNumber = 0;

    // Raw XInput data snapshot
    XINPUT_STATE m_xinputState{};

    // Normalized analog state
    float m_leftStickX = 0.0f;
    float m_leftStickY = 0.0f;
    float m_rightStickX = 0.0f;
    float m_rightStickY = 0.0f;

    float m_leftTrigger = 0.0f;
    float m_rightTrigger = 0.0f;

    // Helper for reading digital input
    bool buttonPressed(WORD mask) const;
};

#endif // INPUTSTATE_H

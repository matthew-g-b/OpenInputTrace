#include "inputstate.h"

#include <iostream>
#include <algorithm>

InputState::InputState(QObject *parent) : QObject(parent) {
    connect(&m_pollTimer, &QTimer::timeout, this, &InputState::pollController);
}

/*
 *  Polling control
 */
void InputState::startPolling(int intervalMs){
    // Clamp interval value to be >= 4ms (i.e. polling is roughly capped to 250 fps)
    if(intervalMs < 4){
        m_pollTimer.setInterval(4);
        m_pollTimer.start();
        return;
    }
    m_pollTimer.setInterval(intervalMs);
    m_pollTimer.start();
}

void InputState::stopPolling(){
    m_pollTimer.stop();
}

/*
 * Controller index
 */
void InputState::setControllerIndex(DWORD index){
    // DWORD is unsigned, so all invalid input is indices > 3
    if(index > 3){
        // Clamp index to default controller port 0
        m_controllerIndex = 0;
        return;
    }
    m_controllerIndex = index;
}


DWORD InputState::controllerIndex() const{
    return m_controllerIndex;
}


/*
 * Connection state
 */
bool InputState::isConnected() const{
    return m_connected;
}

/*
 * Normalized analog values
 */
float InputState::leftStickX() const{
    return m_leftStickX;
}

float InputState::leftStickY() const{
    return m_leftStickY;
}
float InputState::rightStickX() const{
    return m_rightStickX;
}
float InputState::rightStickY() const{
    return m_rightStickY;
}

float InputState::leftTrigger() const{
    return m_leftTrigger;
}
float InputState::rightTrigger() const{
    return m_rightTrigger;
}

/*
 * Analog mangnitude values
 */

float InputState::rightStickMagnitude() const{
    float magnitude = std::sqrt((m_rightStickX * m_rightStickX) + (m_rightStickY * m_rightStickY));
    return std::clamp(magnitude, 0.0f, 1.0f);
}

float InputState::leftStickMagnitude() const{
    float magnitude = std::sqrt((m_leftStickX * m_leftStickX) + (m_leftStickY * m_leftStickY));
    return std::clamp(magnitude, 0.0f, 1.0f);
}

/*
 * Digital input values
 */
bool InputState::buttonPressed(WORD mask) const{
    return (m_xinputState.Gamepad.wButtons & mask) != 0;
}

bool InputState::dpadUp() const{
    return buttonPressed(XINPUT_GAMEPAD_DPAD_UP);
}

bool InputState::dpadDown() const{
    return buttonPressed(XINPUT_GAMEPAD_DPAD_DOWN);
}

bool InputState::dpadLeft() const{
    return buttonPressed(XINPUT_GAMEPAD_DPAD_LEFT);
}

bool InputState::dpadRight() const{
    return buttonPressed(XINPUT_GAMEPAD_DPAD_RIGHT);
}


bool InputState::start() const{
    return buttonPressed(XINPUT_GAMEPAD_START);
}

bool InputState::back() const{
    return buttonPressed(XINPUT_GAMEPAD_BACK);
}

bool InputState::leftThumb() const{
    return buttonPressed(XINPUT_GAMEPAD_LEFT_THUMB);
}

bool InputState::rightThumb() const{
    return buttonPressed(XINPUT_GAMEPAD_RIGHT_THUMB);
}

bool InputState::leftShoulder() const{
    return buttonPressed(XINPUT_GAMEPAD_LEFT_SHOULDER);
}

bool InputState::rightShoulder() const{
    return buttonPressed(XINPUT_GAMEPAD_RIGHT_SHOULDER);
}

bool InputState::buttonA() const{
    return buttonPressed(XINPUT_GAMEPAD_A);
}

bool InputState::buttonB() const{
    return buttonPressed(XINPUT_GAMEPAD_B);
}

bool InputState::buttonX() const{
    return buttonPressed(XINPUT_GAMEPAD_X);
}

bool InputState::buttonY() const{
    return buttonPressed(XINPUT_GAMEPAD_Y);
}

void InputState::pollController(){
    XINPUT_STATE state{};
    DWORD result = XInputGetState(m_controllerIndex, &state);

    if(result == ERROR_SUCCESS){
        m_connected = true;
        m_xinputState = state;

        if(dpadRight()){
            std::cout << "Dpad right pressed!" << std::endl; //For debugging pollController. Remove this!
        }

        // Right trigger
        m_rightTrigger = static_cast<float>(m_xinputState.Gamepad.bRightTrigger) / 255.0f;

        // Left trigger
        m_leftTrigger = static_cast<float>(m_xinputState.Gamepad.bLeftTrigger) / 255.0f;

        // Right stick
        m_rightStickX = static_cast<float>(m_xinputState.Gamepad.sThumbRX) / 32767.0f;
        m_rightStickY = static_cast<float>(m_xinputState.Gamepad.sThumbRY) / 32767.0f;

        // Left stick
        m_leftStickX = static_cast<float>(m_xinputState.Gamepad.sThumbLX) / 32767.0f;
        m_leftStickY = static_cast<float>(m_xinputState.Gamepad.sThumbLY) / 32767.0f;

        emit stateChanged();
    }
    else{
        m_connected = false;
    }
}

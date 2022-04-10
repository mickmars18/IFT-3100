#include "InputController.h"
#include <iostream>

std::vector<bool> InputController::m_keyDown;

void InputController::init() {
    m_keyDown.clear();
    m_keyDown.reserve(128);
    for (size_t i = 0; i < 128; i++) {
        m_keyDown.push_back(false);
    }
}

void InputController::keyPressed(int key) {
    if(key < 128)
        m_keyDown[key] = true;
}

void InputController::keyReleased(int key) {
    if (key < 128)
        m_keyDown[key] = false;
}

bool InputController::isKeyDown(int key) {
    if (key < 128)
        return m_keyDown[key];
    else
        return false;
}

bool InputController::isNumberKey(int key) {
    return key >= KEY::ZERO && key <= KEY::NINE;
}

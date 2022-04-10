#pragma once
#include <vector>

enum KEY {
    SHIFT = 1,
    CTRL = 2,
    ENTER = 13,
    TAB = 9,
    SPACE = 32,
    ZERO = 48,
    ONE = 49,
    TWO = 50,
    THREE = 51,
    FOUR = 52,
    FIVE = 53,
    SIX = 54,
    SEVEN = 55,
    EIGHT = 56,
    NINE = 57,
    A = 97,
    B = 98,
    C = 99,
    D = 100,
    E = 101,
    F = 102,
    G = 103,
    H = 104,
    I = 105,
    J = 106,
    K = 107,
    L = 108,
    M = 109,
    N = 110,
    O = 111,
    P = 112,
    Q = 113,
    R = 114,
    S = 115,
    T = 116,
    U = 117,
    V = 118,
    W = 119,
    X = 120,
    Y = 121,
    Z = 122,
};

class InputController
{
public:
    static void init();
    
    static void keyPressed(int key);
    static void keyReleased(int key);
    static bool isKeyDown(int key);
    static bool isNumberKey(int key);
private:
    static std::vector<bool> m_keyDown;
};


#pragma once
#ifndef KEYBOARD_H
#define KEYBOARD_H
#include <vector>

class Keyboard {
public:
    static int testKeyboardInvalidInput();
    static int testKeyboardValidInput();
    static int test_();
    // Function to handle keyboard input for the drum sequence
    void handleKeyboardInput(std::vector<int>& sequence);
};

#endif  // End of Keyboard.h

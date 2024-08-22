#pragma once
#ifndef KEYBOARD_H
#define KEYBOARD_H
#include <vector>

class Keyboard {
public:
    void testKeyboardInvalidInput();
    void testKeyboardValidInput();
    void runKeyBoardTests();
    // Function to handle keyboard input for the drum sequence
    void handleKeyboardInput(std::vector<int>& sequence);
};

#endif  // End of Keyboard.h

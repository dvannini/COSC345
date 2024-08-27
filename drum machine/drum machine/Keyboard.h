#pragma once
#ifndef KEYBOARD_H
#define KEYBOARD_H
#include <vector>
/**
 * Class to handle simple single key input.
 */
class Keyboard {
public:
    /**
     * Tests invalid keyboard input.
     * 
     * \return int - the status, 1 - fail, 0 - pass
     */
    static int testKeyboardInvalidInput();
    /**
     * Tests valid keyboard input.
     * 
     * \return int - the status, 1 - fail, 0 - pass
     */
    static int testKeyboardValidInput();
    /**
     * Class to return the outcome of the tests.
     * 
     * \return int - the outcome
     */
    static int test_();
    /**
     * modifies sequence based on keys pressed.
     * 
     * \param sequence
     */
    void handleKeyboardInput(std::vector<int>& sequence);
};

#endif  // End of Keyboard.h

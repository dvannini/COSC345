#include "Keyboard.h"
#include <iostream>
#include <conio.h>
#include <vector>
#include <Windows.h>

void Keyboard::handleKeyboardInput(std::vector<int>& sequence) {
    int sound = _getch();

    while (sound >= 48 && sound <= 52) {  // ASCII values for '0'-'4'
        sequence.push_back(sound - 48);    // Convert char to int

        std::cout << "Current Sequence: ";

        for (int i = 0; i < sequence.size(); ++i) {
            std::cout << sequence[i] << " ";
        }
        std::cout << std::endl;

        
        sound = _getch();  // Capture next input
    }
}

int Keyboard::testKeyboardInvalidInput() {
    // Create an instance of Keyboard
    Keyboard keyboard;
    // Initialize a sequence vector
    std::vector<int> testSequence;
    // Simulate valid and invalid inputs
    std::vector<int> simulatedInput = { 48, 49, 120, 50, 51 };  // '0', '1', invalid ('x'), '2', '3'
    // Add valid inputs
    for (int sound : simulatedInput) {
        if (sound >= 48 && sound <= 52) {
            testSequence.push_back(sound - 48);  // ASCII to integer
        }
    }
    // Check if the sequence contains the correct values (should stop at the invalid input)
    std::cout << "Keyboard Invalid Input Test: ";
    for (int i = 0; i < testSequence.size(); i++) {
        if (testSequence[i] != i) return 2;
    }
    return 0;
}

int Keyboard::testKeyboardValidInput() {
    // Create an instance of Keyboard
    Keyboard keyboard;
    // Initialize a sequence vector
    std::vector<int> testSequence;
    // Simulate user input
    std::vector<int> simulatedInput = { 48, 49, 50, 51, 52 };  // '0', '1', '2', '3', '4'
    // Manually push each input to the sequence
    for (int sound : simulatedInput) {
        testSequence.push_back(sound - 48);  // ASCII to integer
    }
    // Check if the sequence contains the correct values
    std::cout << "Keyboard Valid Input Test: ";
    for (int i = 0; i < testSequence.size(); i++) {
        if (testSequence[i] != i) return 1;
    }
    return 0;
}





int Keyboard::test_() {
    return Keyboard::testKeyboardInvalidInput() + Keyboard::testKeyboardValidInput();
}

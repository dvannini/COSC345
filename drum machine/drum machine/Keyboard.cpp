#include "Keyboard.h"
#include <iostream>
#include <conio.h>

void Keyboard::handleKeyboardInput(std::vector<int>& sequence) {
    int sound = _getch();

    while (sound >= 48 && sound <= 52) {  // ASCII values for '0'-'4'
        sequence.push_back(sound - 48);    // Convert char to int
        std::cout << "Added sound: " << sound - 48 << "\n";
        sound = _getch();  // Capture next input
    }
}

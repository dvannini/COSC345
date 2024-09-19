// drum machine.cpp : This is the 'main' function
//

/*! \mainpage CMDrum Docs
 *
 * \section intro_sec Introduction
 *
 * CMDrum is a simple command-line drum sequencer.
 * 
 * To view details about the structure and functionality of the source code, <a href="./annotated.html">view the class list.</a>
 */
#include "utils.h"  // Include the header where clearScreen is declared
#include <vector>   
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include "Sequence.h"
#include "Clock.h"
#include "Interface.h"
#include <map>

#pragma comment(lib, "winmm.lib")

int main() {

    const int N = 8;
    std::map<std::string, std::array<bool, N>> sequence;
    Audio_Engine E = Audio_Engine::Audio_Engine();
    bool playing = false;
    int choice = 0;
    while (choice != 5) {
        Interface::displayMainMenu(sequence);
        char ch = _getch();
        int newBPM = Interface::performAction(ch, sequence, E);
        if (newBPM == -1) {
            choice = 5;
        }
    }   
    return 0;
}

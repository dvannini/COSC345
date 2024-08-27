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
#include "Keyboard.h"
#include "Sequence.h"
#include "Clock.h"
#include "Interface.h"
#include <map>

#pragma comment(lib, "winmm.lib")
int bpm = 178;

//
//void displayMenu() {// maybe menu which will display before user start adding sequence
//
//    std::cout << "\nDrum Machine Menu:\n";
//    std::cout << "1. Edit Sequence\n";
//    std::cout << "2. Edit Sequence 2 (not being used currently)\n";
//    std::cout << "3. Play\n";
//    std::cout << "4. Exit\n";
//    std::cout << "5. Set BPM\n";
//    std::cout << "Enter your choice: ";
//}
//
//void displaySoundOptions() {
//    std::cout << "Sounds:\n";
//    std::cout << "0. Nothing\n";
//    std::cout << "1. Kick\n";
//    std::cout << "2. Snare\n";
//    std::cout << "3. HiHat\n";
//    std::cout << "4. 808\n";
//    std::cout << "Press any other key to save\n";
//    std::cout << "Enter your choice: ";
//}
//
//void printSequence(const std::vector<int>& sequence) {
//    for (int element : sequence) {
//        std::cout << element << " ";
//    }
//    std::cout << std::endl; // End with a newline for better readability
//}
//
//void displaySequence(const std::vector<int>& sequence) {
//    for (int sound : sequence) {
//        std::cout << sound << " ";
//    }
//    std::cout << std::endl;
//}

void setBpm() {
    int newBpm;
    std::cout << "Enter new BPM: ";
    std::cin >> newBpm;

    if (newBpm > 0) {
        bpm = 60000 / newBpm; // Convert BPM to milliseconds per beat
        std::cout << "BPM set to " << newBpm << " (" << bpm << " milliseconds per beat)." << std::endl;
    }
    else {
        std::cout << "Invalid BPM. BPM must be greater than 0." << std::endl;
    }
}


int main() {
    Audio_Engine engine = Audio_Engine::Audio_Engine();
    Clock c = Clock::Clock(bpm);
    Sequence seq = Sequence::Sequence();
    

    engine.Preload("../Assets/Snare 70s MPC 3.wav", 2);
    engine.Preload("../Assets/Kick 70s 1.wav", 1);
    engine.Preload("../Assets/Hihat Closed 80s UK Disco Vinyl.wav", 3);

    Keyboard keyboard;
    const int N = 8;
    std::map<std::string, std::array<bool, N>> sequence;
    std::map<std::string, std::vector<int>> mainSequence;
    std::vector<int> additionalSequence;

    bool exit = false;
    bool playing = false;
    int choice = 0;
    while (choice != 4) {
        // clearScreen(); removed; interface handles all screen clearing
        //displaySequence(mainSequence);
        //replace with interface version:

        //displaySequence(additionalSequence);
        //displayMenu();
        Interface::displayMainMenu(sequence);
        
        std::cin >> choice;
        int newBPM = Interface::performAction(choice, sequence, bpm);
        if (newBPM > 0) {
            bpm = newBPM;
        }
        if (newBPM == -1) {
            choice = 4;
        }
    }   
    return 0;

}

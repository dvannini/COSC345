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
#include <vector>
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include "Keyboard.h"
#include "Sequence.h"
#include "Clock.h"

#pragma comment(lib, "winmm.lib")
int bpm = 178;

void displayMenu() {// maybe menu which will display before user start adding sequence

    std::cout << "\nDrum Machine Menu:\n";
    std::cout << "1. Edit Sequence\n";
    std::cout << "2. Edit Sequence 2 (not being used currently)\n";
    std::cout << "3. Play\n";
    std::cout << "4. Exit\n";
    std::cout << "5. Set BPM\n";
    std::cout << "Enter your choice: ";
}

void displaySoundOptions() {
    std::cout << "Sounds:\n";
    std::cout << "0. Nothing\n";
    std::cout << "1. Kick\n";
    std::cout << "2. Snare\n";
    std::cout << "3. HiHat\n";
    std::cout << "4. 808\n";
    std::cout << "Press any other key to save\n";
    std::cout << "Enter your choice: ";
}

void printSequence(const std::vector<int>& sequence) {
    for (int element : sequence) {
        std::cout << element << " ";
    }
    std::cout << std::endl; // End with a newline for better readability
}

void displaySequence(const std::vector<int>& sequence) {
    for (int sound : sequence) {
        std::cout << sound << " ";
    }
    std::cout << std::endl;
}
void clearScreen() {
    system("cls");
}
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
    std::vector<int> mainSequence;
    std::vector<int> additionalSequence;

    bool exit = false;
    bool playing = false;

    while (!exit) {
        //clearScreen();
        displaySequence(mainSequence);
        displaySequence(additionalSequence);
        displayMenu();

        int choice;
        std::cin >> choice;
        //Sequence seq = Sequence::Sequence();
        switch (choice) {
        case 1: {
            clearScreen();
            displaySoundOptions();
            std::cout << "Current Main Sequence: ";
            displaySequence(mainSequence);
            keyboard.handleKeyboardInput(mainSequence);
            clearScreen();
            break;
        }
        case 2: {
            displaySoundOptions();
            int sound;
            std::cin >> sound;
            additionalSequence.push_back(sound);
            std::cout << "Current Additional Sequence: "; // need to make it so if we add a new sound it creates a new array which can 
            displaySequence(additionalSequence);            // display it as an array.
            break;
        }
        case 3: {
            
            int playhead = 0; //index of playhead in sequence data
            playing = true;
            std::cout << "Playing sequences...\n";
            c.startClock();
            while (playing == true) {

                if (c.interval()) {
                    std::vector<int> data = seq.getColumn(playhead); //get the sounds to play at the playhead position
                    for (int i = 0; i < 3; i++) {
                        if (data[i] != 0) {
                            engine.PlaySound_(data[i]);
                        }
                        
                    }
                    playhead += 1;
                    playhead = playhead % 8;
                }
                
            }
            break;
        }
        case 5: {
            setBpm();
            break;
        }
        case 4: {
            exit = true;
            break;
        }
        default:
            std::cout << "Invalid choice. Please try again.\n";
        }
        }

    return 0;
}
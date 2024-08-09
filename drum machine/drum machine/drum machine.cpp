// drum machine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <vector>
#include <iostream>
#include <Windows.h>
#pragma comment(lib, "winmm.lib")
int bpm = 1000;

void playSound(int sound) { // plays a sound according to the sequencer
    switch (sound) {
    case 0:
        break;
    case 1:
        PlaySound("../Assets/Kick 70s 1.wav", NULL, SND_FILENAME | SND_ASYNC);
        std::cout << "played kick." << std::endl;
        break;
    case 2:
        PlaySound("../Assets/Snare 70s MPC 3.wav", NULL, SND_FILENAME | SND_ASYNC);
        std::cout << "played snare." << std::endl;
        break;
    case 3:
        PlaySound("../Assets/Hihat Closed 80s UK Disco Vinyl.wav", NULL, SND_FILENAME | SND_ASYNC);
        std::cout << "played HiHat." << std::endl;
        break;
    case 4:
        PlaySound("../Assets/very-fat-808.wav", NULL, SND_FILENAME | SND_ASYNC);
        std::cout << "played 808." << std::endl;
        break;
    }
}

void displayMenu() {// maybe menu which will display before user start adding sequence

    std::cout << "\nDrum Machine Menu:\n";
    std::cout << "1. Edit\n";
    std::cout << "2. Play\n";
    std::cout << "3. Change BPM\n";
    std::cout << "4. Exit\n";
    std::cout << "Enter your choice: ";
}

void displaySoundOptions() {
    std::cout << "Sequence: ";
    std::cout << "Sounds:\n";
    std::cout << "0. Nothing\n";
    std::cout << "1. Kick\n";
    std::cout << "2. Snare\n";
    std::cout << "3. HiHat\n";
    std::cout << "4. 808\n";
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

    std::vector<int> mainSequence;
    std::vector<int> additionalSequence;

    bool exit = false;

    while (!exit) {
        //clearScreen();
        displaySequence(mainSequence);
        displaySequence(additionalSequence);
        displayMenu();
        int choice;
        std::cin >> choice;

        switch (choice) {
        case 1: {
            displaySoundOptions();
            int sound;
            std::cin >> sound;
            mainSequence.push_back(sound);
            std::cout << "Current Main Sequence: ";
            displaySequence(mainSequence);
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
            int mainLength = mainSequence.size();
            int additionalLength = additionalSequence.size();
            if (mainLength == 0 || additionalLength == 0) {
                std::cout << "Both sequences must have at least one sound.\n";
                break;
            }

            std::cout << "Playing sequences...\n";
            for (int i = 0; i < 100; i++) {
                playSound(mainSequence[i % mainLength]);
                Sleep(bpm); // half of the total sleep duration
                playSound(additionalSequence[i % additionalLength]);
                Sleep(bpm); // half of the total sleep duration
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
// drum machine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <vector>
#pragma comment(lib, "winmm.lib")
#include <iostream>
#include <Windows.h>
#include <thread>
#pragma comment(lib, "winmm.lib")

void playSound(int sound) { // plays a sound according to the sequencer
    switch (sound) {
    case 0:
        break;
    case 1:
        PlaySound(L"..Assets/Kick 70s 1.wav", NULL, SND_FILENAME | SND_ASYNC);
        std::cout << "played kick." << std::endl;
        break;
    case 2:
        PlaySound(L"../Assets/Snare 70s MPC 3.wav", NULL, SND_FILENAME | SND_ASYNC);
        std::cout << "played snare." << std::endl;
        break;
    case 3:
        PlaySound(L"../Assets/Hihat Closed 80s UK Disco Vinyl.wav", NULL, SND_FILENAME | SND_ASYNC);
        std::cout << "played HiHat." << std::endl;
        break;
    case 4:
        PlaySound(L"../Assets/very-fat-808.wav", NULL, SND_FILENAME | SND_ASYNC);
        std::cout << "played 808." << std::endl;
        break;
    }
}

void displayMenu() {// maybe menu which will display before user start adding sequence

    std::cout << "\nMusic Sequencer Menu:\n";
    std::cout << "1. Add Sound to Main Sequence\n";
    std::cout << "2. Add Sound to Additional Sequence\n";
    std::cout << "3. Play Sequences\n";
    std::cout << "4. Exit\n";
    std::cout << "Enter your choice: ";
}

void displaySoundOptions() {
    std::cout << "Current Sequence: ";
    std::cout << "Sound Options:\n";
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

int main() {

    std::vector<int> mainSequence;
    std::vector<int> additionalSequence(16,0);

    bool exit = false;

    while (!exit) {
        clearScreen();
        displaySequence(mainSequence);
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
            std::cout << "Current Additional Sequence: ";
            displaySequence(additionalSequence);
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
                Sleep(250); // half of the total sleep duration
                playSound(additionalSequence[i % additionalLength]);
                Sleep(250); // half of the total sleep duration
            }
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
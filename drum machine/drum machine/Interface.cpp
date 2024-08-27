#include "Interface.h"
#include "utils.h"  // Include the header where clearScreen is declared
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <map>
#include <array>

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

// Declarations of a few strings which will be used multiple times
std::string mainMenu = "please select (using the adjacent key) an action from the options below:\n-(1)Edit Sequence\n-(2)Play Sequence\n-(3)Set BPM\n-(4)Exit\n";
int BPM = 175;
bool sequenceSet = false;
std::string patternName = "New Pattern";

void Interface::displaySequence(const std::map<std::string, std::array<bool, 8>>& sequence) {
    clearScreen();
    int index = 1;
    std::cout << "BPM: " << BPM << "      Pattern name: " << patternName << "\n";
    for (auto i = sequence.begin(); i != sequence.end(); i++) {
        std::cout << "-(" << index << ")";
        std::cout << i->first << ": ";
        for (int n = 0; n < 10 - i->first.size(); n++) {
            std::cout << " "; //aligns all paterns accounting for different name lengths of sounds
        }
        index++;
        for (bool value : i->second) {
            std::cout << (value ? "0" : "_");
        }
        std::cout << std::endl;
    }
}

void Interface::displayMainMenu(const std::map<std::string, std::array<bool, 8>>& sequence) {
    clearScreen();
    std::cout << "Welcome to CMDrum\n";
    if (sequenceSet) {
        displaySequence(sequence);
    }
    std::cout << mainMenu;
}

void Interface::soundEditDisplay(const std::pair<std::string, std::array<bool, 8>>& keyAndVals) {
    clearScreen();
    // Displays the sequence we are editing:
    std::cout << keyAndVals.first << ": ";
    for (bool i : keyAndVals.second) {
        if (i) {
            std::cout<<"0";
        }
        else {
            std::cout<<"_";
        }
    }
    std::cout << "\nPress Enter to save.\nEnter 1-8 to add or delete a sound in slots 1-8:\n" << std::endl;
}

void Interface::editSound(std::map<std::string, std::array<bool, 8>>& sequence, std::pair<std::string, std::array<bool, 8>>& keyAndVals) {
    soundEditDisplay(keyAndVals);
     // Convert from char to int
    while (true) {
        char ch = _getch();
        int toChange = ch - '0';
        if (ch == 13) {
            break;
        }
        if (toChange >= 1 && toChange <= 8) {
            int index = toChange - 1; // Convert char to int index
            keyAndVals.second[index] = !keyAndVals.second[index];
        }
        soundEditDisplay(keyAndVals);
    }
    // Updates the actual sequence
    auto a = sequence.find(keyAndVals.first);
    if (a != sequence.end()) {
        a->second = keyAndVals.second;
    }
}

std::pair<std::string, std::array<bool, 8>> Interface::getKeyByIndex(int soundIndex, const std::map<std::string, std::array<bool, 8>>& sequence) {
    int index = 1;
    for (auto i = sequence.begin(); i != sequence.end(); i++) {
        if (index == soundIndex) {
            return std::make_pair(i->first, i->second);
        }
        index++;
    }
    return std::make_pair("", std::array<bool, 8>{});
}

void Interface::addSound(int newSound, std::map<std::string, std::array<bool, 8>>& sequence) {
    switch (newSound) {
    case 1:
        sequence.insert(std::make_pair("Kick", std::array<bool, 8>{false, false, false, false, false, false, false, false}));
        break;
    case 2:
        sequence.insert(std::make_pair("Snare", std::array<bool, 8>{false, false, false, false, false, false, false, false}));
        break;
    case 3:
        sequence.insert(std::make_pair("Hat", std::array<bool, 8>{false, false, false, false, false, false, false, false}));
        break;
    }
}

int Interface::editSequence(std::map<std::string, std::array<bool, 8>>& sequence) {
    clearScreen();
    if (!sequenceSet) {
        std::cout << "No Sequence has been set. Please select your first sound to add to a new sequence:\n";
        std::cout << "-(1)Kick\n-(2)Snare\n-(3)Hat";
        int newSound = 0;
        std::cin >> newSound;
        clearScreen();
        addSound(newSound, sequence);
        sequenceSet = true;
    }
    displaySequence(sequence);
    int soundIndex;
    std::cout << "Which sound would you like to edit (enter the corresponding number)?\n(Or enter a to add a new sound, or Enter to save and exit to main menu)";
    char ch = _getch();
    soundIndex = ch - '0';
    if (ch == 97) {
        int newSound;
        clearScreen();
        std::cout << "which sound would you like to add?\n-(1)Kick\n-(2)Snare\n-(3)Hat";
        std::cin >> newSound;
        addSound(newSound, sequence);
        return editSequence(sequence);//returns to editor
    }
    if (ch == 13) {
        return 0;
    }
    std::pair<std::string, std::array<bool, 8>> keyAndVals = getKeyByIndex(soundIndex, sequence);
    if (keyAndVals.first != "") {
        editSound(sequence, keyAndVals);
    }
    // Flip the value in the map of the index entered (minus 1 for zero indexing)
    return editSequence(sequence);
}

int Interface::playSequence(const std::map<std::string, std::array<bool, 8>>& sequence) {
    return 0;
}

int Interface::setBPM(const std::map<std::string, std::array<bool, 8>> sequence, bool edit) {
    clearScreen();
    displayMainMenu(sequence);
    if (edit) {
        std::cout << "Type in your bpm and press Enter to save:\n";
        std::cin >> BPM;
        if (BPM == 0) {
            std::cout << "\nBPM cannot be zero\n";
            setBPM(sequence, false);
        }
        return BPM;
    }
    std::cout << "Press the up and down arrows to scroll bpm, or press E to type bpm.\nPress Enter to save\n";
    char ch = _getch();
    while (ch != 13) {
        if (ch == 101) {
            BPM = 0;
            return setBPM(sequence, true);
        }
        if (ch == 72) {
            BPM = BPM + 1;
            return setBPM(sequence, false);
        }
        if (ch == 80) {
            BPM = BPM - 1;
            return setBPM(sequence, false);
        }
        ch = _getch();
    }
    return BPM;
}

// Note: 1 edit, 2 play, 3 bpm, 4 exit
int Interface::performAction(int choice, std::map<std::string, std::array<bool, 8>>& sequence, int newBPM) {
    bool exit = false;
    switch (choice) {
    case 1: {
        return editSequence(sequence);
        break;
    }
    case 2: {
        return playSequence(sequence);
        break;
    }
    case 3: {
        BPM = newBPM;
        return setBPM(sequence, false);
        break;
    }
    case 4: {
        return -1;
        break;
    }
    default:
        std::cout << "Invalid choice. Please try again.\n";
        return 0;
    }
    return 0;
}

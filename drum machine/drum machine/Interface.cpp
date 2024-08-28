#include "Interface.h"
#include "utils.h"  // Include the header where clearScreen is declared
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <map>
#include <array>
#include "Clock.h"
#include "Interface.h"
#include "Audio_Engine.h"

// Declarations of a few strings which will be used multiple times

std::string mainMenu = "please select (using the adjacent key) an action from the options below, press SPACE to play and then any key pause:\n-(1)Edit Sequence\n-(2)Set BPM\n-(3)Set Pattern Name\n-(4)Exit\n";
int BPM = 175;
bool sequenceSet = false;
std::string patternName = "New Pattern";
bool playing = false;


/*method to display the contents of the current sequence
@param sequence; the currrent sequence, the string is the name of the sound, and the array is the pattern
*/
void Interface::displaySequence(const std::map<std::string, std::array<bool, 8>>& sequence) {
    clearScreen();
    int index = 1;
    std::cout << "BPM: " << BPM << "      Pattern name: " << patternName << "\n";
    for (auto i = sequence.begin(); i != sequence.end(); i++) {
        std::cout << "-(" << index << ")";
        for (int n = 0; n < 40 - i->first.size(); n++) {
            std::cout << " "; //aligns all paterns accounting for different name lengths of sounds
        }
        std::cout << i->first << ": ";
        index++;
        for (bool value : i->second) {
            std::cout << (value ? "0" : "_");
        }
        std::cout << std::endl;
    }
}

/*method to display the main menu when no sequence has been loaded
@param sequence; the currrent sequence, the string is the name of the sound, and the array is the pattern
*/
void Interface::displayMainMenu(const std::map<std::string, std::array<bool, 8>>& sequence) {
    clearScreen();
    std::cout << "Welcome to CMDrum\n";
    if (sequenceSet) {
        displaySequence(sequence);
    }
    std::cout << mainMenu;
}

/*Method to show the display for editing a specific sound
@param keyAndVals; a pair, where the string is the key of the sound, and the array is the pattern
of the sound. 
*/
void Interface::soundEditDisplay(const std::map<std::string, std::array<bool, 8>>& sequence, int editing, std::pair<std::string, std::array<bool, 8>>& keyAndVals) {
    clearScreen();
    int index = 1;
    std::cout << "BPM: " << BPM << "      Pattern name: " << patternName << "\n";
    for (auto i = sequence.begin(); i != sequence.end(); i++) {
        if (index != editing) {
            std::cout << "-(" << index << ")";
            for (int n = 0; n < 40 - i->first.size(); n++) {
                std::cout << " "; //aligns all paterns accounting for different name lengths of sounds
            }
            std::cout << i->first << ": ";
            
            for (bool value : i->second) {
                std::cout << (value ? "0" : "_");
            }
            std::cout << "\n";
        }
        else {
            // Displays the sequence we are editing:
            std::cout << "(->)";
            for (int n = 0; n < 40 - i->first.size(); n++) {
                std::cout << " "; //aligns all paterns accounting for different name lengths of sounds
            }
            std::cout<< keyAndVals.first << ": ";
            for (bool i : keyAndVals.second) {
                if (i) {
                    std::cout << "0";
                }
                else {
                    std::cout << "_";
                }
            }
            std::cout << "\n";
        }
        index++;
        
    }
    std::cout << "Press Enter to save.\nEnter 1 - 8 to add or delete a sound in slots 1 - 8:\n" << std::endl;




    
}

/*
*/
void Interface::editSound(std::map<std::string, std::array<bool, 8>>& sequence, std::pair<std::string, std::array<bool, 8>>& keyAndVals, int soundIndex) {
    soundEditDisplay(sequence, soundIndex, keyAndVals);
     // Convert from char to int
    while (true) {
        char ch = _getch();
        int toChange = ch - '0';
        if (ch == 13) {
            break;
        }
        int index = toChange - 1;
        if (toChange >= 1 && toChange <= 8) {
             // Convert char to int index
            keyAndVals.second[index] = !keyAndVals.second[index];     
        }
        soundEditDisplay(sequence, soundIndex, keyAndVals);
    }
    // Updates the actual sequence
    auto a = sequence.find(keyAndVals.first);
    if (a != sequence.end()) {
        a->second = keyAndVals.second;
    }
}

/*Helper method to find the key corresponding to a certain index in the map
@params soundINdex, the index of the sound whos key we want, \sequence; the currrent sequence, the string is the name of the sound, and the array is the pattern
@returns a pair consisting of the name of the sound at the specified index, and an array 
representing the pattern
*/
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

/*Helper method to add a new sound to the sequence
@param sequence; the currrent sequence, the string is the name of the sound, and the array is 
the pattern
*/
void Interface::addSound(int newSound, std::map<std::string, std::array<bool, 8>>& sequence) {
    switch (newSound) {
    case 1:
        sequence.insert(std::make_pair("Kick 70s 1.wav", std::array<bool, 8>{false, false, false, false, false, false, false, false}));
        break;
    case 2:
        sequence.insert(std::make_pair("Snare 70s MPC 3.wav", std::array<bool, 8>{false, false, false, false, false, false, false, false}));
        break;
    case 3:
        sequence.insert(std::make_pair("Hihat Closed 80s UK Disco Vinyl.wav", std::array<bool, 8>{false, false, false, false, false, false, false, false}));
        break;
    }
}

/*called when the user selects the edit sequence option. It will display the sequence editor, or if no
* sounds have been added, will prompt the user to add a sound. 
@param sequence; the currrent sequence, the string is the name of the sound, and the array is the 
pattern
*/
int Interface::editSequence(std::map<std::string, std::array<bool, 8>>& sequence) {
    clearScreen();
    if (!sequenceSet) {
        std::cout << "No Sequence has been set. Please select your first sound to add to a new sequence:\n";
        std::cout << "-(1)Kick\n-(2)Snare\n-(3)Hat\n";
        int newSound = 0;
        std::cin >> newSound;
        clearScreen();
        addSound(newSound, sequence);
        sequenceSet = true;
        return editSequence(sequence);
    }
    displaySequence(sequence);
    int soundIndex;
    std::cout << "Which sound would you like to edit (enter the corresponding number)?\n(Or enter a to add a new sound, or Enter to save and exit to main menu)";
    char ch = _getch();
    soundIndex = ch - '0';
    if (ch == 13) {
        return 0;
    }
    if (ch == 97) {
        int newSound;
        clearScreen();
        std::cout << "which sound would you like to add?\n-(1)Kick\n-(2)Snare\n-(3)Hat\n";
        std::cin >> newSound;
        addSound(newSound, sequence);
        return editSequence(sequence);//returns to editor
    }
    std::pair<std::string, std::array<bool, 8>> keyAndVals = getKeyByIndex(soundIndex, sequence);
    if (keyAndVals.first != "") {
        editSound(sequence, keyAndVals, soundIndex);
    }
    // Flip the value in the map of the index entered (minus 1 for zero indexing)
    return editSequence(sequence);
}

int Interface::playSequence(const std::map<std::string, std::array<bool, 8>>& sequence) {
    Clock c = Clock::Clock(BPM);
    Audio_Engine E = Audio_Engine::Audio_Engine();
    std::vector<std::string> names;
    std::vector<std::array<bool, 8>> patterns;
    for (auto i = sequence.begin(); i != sequence.end(); i++) {
        E.Preload("../Assets/" + i->first, i->first);
        names.push_back(i->first);
        patterns.push_back(i->second);

    }
    
    int index = 0;
    char ch = 'c';
    c.startClock();
    bool running = true;
    while (running) {
        if (c.interval()) {
            //std::vector<std::string> thisBeat; for multiple sounds
            for (int i = 0; i < patterns.size()/sizeof(bool); i++) {
                if (patterns[i][index]) {
                    std::string name = names[i];
                    //thisBeat.push_back(name); for multiple sounds
                    //add sound into merge
                    E.PlaySound_(name);
                    //break;
                }
            }
            //E.mixDataNice(thisBeat); for multiple sounds
            index++;
        }
        //reset index when it reaches the end
        if (index > 7) {
            index = 0;
        }
        if (_kbhit()) {
            running = false;
        }
    }
    playing = !playing;
    return 0;
}

int Interface::setBPM(const std::map<std::string, std::array<bool, 8>>& sequence, bool edit) {
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

int Interface::setNewName() {
    clearScreen();
    std::cout << "Please enter a name for your pattern:\n";
    std::string name = "";
    while (name == "") {
        std::getline(std::cin, name);
    }
    std::cout << "Confirm name change to: \"" << name << "\" by pressing Enter, or cancel by pressing any other key";
    char ch = _getch();
    if (ch != 13) {
        return 0;
    }
    patternName = name;
    return 0;
}
// Note: 1 edit, 2 play, 3 bpm, 4 exit
int Interface::performAction(char choice, std::map<std::string, std::array<bool, 8>>& sequence) {
    bool exit = false;
    switch (choice) {
    case 49: {
        return editSequence(sequence);
        break;
    }
    case 32: {
        return playSequence(sequence);
        break;
    }
    case 50: {
        return setBPM(sequence, false);
        break;
    }
    case 51: {
        return setNewName();
    }
    case 52: {
        return -1;
        break;
    }
    default:
        std::cout << "Invalid choice. Please try again.\n";
        return 0;
    }
    return 0;
}

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

// Declarations of a few strings which will be used multiple times \x1b[90m- Command Line Drum Machine\x1b[97m 93

std::string mainMenu = "Select an option (numbers 1-4)\n\n\x1b[90m-(1)\x1b[93mEdit Sequence\x1b[97m\n\x1b[90m-(2)\x1b[93mChange BPM\x1b[97m\n\x1b[90m-(3)\x1b[93mSet Pattern Name\x1b[97m\n\x1b[90m-(4)\x1b[93mExit\x1b[97m\n\n\x1b[90mSPACE:\x1b[93mPlay/Pause\x1b[97m";
int BPM = 175;
bool sequenceSet = false;
std::string patternName = "New Pattern";
bool playing = false;

HANDLE Interface::hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
CHAR_INFO* Interface::screen = new CHAR_INFO[SCREEN_SIZE];

Interface::Interface() {
    //fill screen with blank chars
    for (int i = 0; i < WIDTH + 1; i++) {
        for (int j = 0; j < HEIGHT + 1; j++) {
            screen[i * WIDTH + j].Char.UnicodeChar = ' ';
        }
    }
    
}

/**
* @brief Method to display the contents of the current sequence
*
* @param[in] sequence the currrent sequence, the string is the name of the sound, and the array is the pattern
* @return void
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
            std::cout << (value ? "\x1b[94m0\x1b[97m" : "_");
        }
        std::cout << std::endl;
    }
}

void Interface::displayPlayerSequence(const std::map<std::string, std::array<bool, 8>>& sequence, int headIndex) {
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
            if (index - 1 == headIndex) {
                std::cout << "|";
            }
            if (value) {
                std::cout << "\x1b[94m0\x1b[97m";
            }
            else {
                std::cout << "_";
            }
        }
        std::cout << std::endl;
    }
}
/**
* @brief method to display the main menu when no sequence has been loaded
* @param sequence The currrent sequence, the string is the name of the sound, and the array is the pattern
* @return void
*/
void Interface::displayMainMenu(const std::map<std::string, std::array<bool, 8>>& sequence) {
    clearScreen();
    //SetConsoleTextAttribute(hConsole, YELLOW | BACKGROUND_BLUE | FOREGROUND_INTENSITY);
    std::cout << "\x1b[92mWelcome to CMDrum\x1b[97m \x1b[90m- Command Line Drum Machine\x1b[97m\n";
    //SetConsoleTextAttribute(hConsole, WHITE);
    

    if (sequenceSet) {
        displaySequence(sequence);
    }
    std::cout << mainMenu;
}

void Interface::displayPlayerMenu(const std::map<std::string, std::array<bool, 8>>& sequence, int index) {
    clearScreen();
    SetConsoleTextAttribute(hConsole, YELLOW | BACKGROUND_BLUE | FOREGROUND_INTENSITY);
    std::cout << "Welcome to CMDrum - Command Line Drum Machine\n";
    SetConsoleTextAttribute(hConsole, WHITE);
    if (sequenceSet) {
        displayPlayerSequence(sequence, index);
    }
    std::cout << mainMenu;
}
/**
* @brief Method to show the display for editing a specific sound
* @param keyAndVals; a pair, where the string is the key of the sound, and the array is the pattern of the sound.
* @return void
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
                std::cout << (value ? "\x1b[94m0\x1b[97m" : "_");
            }
            std::cout << "\n";
        }
        else {
            // Displays the sequence we are editing:
            std::cout << "\x1b[92m(->)\x1b[97m";
            for (int n = 0; n < 40 - i->first.size(); n++) {
                std::cout << " "; //aligns all paterns accounting for different name lengths of sounds
            }
            std::cout << "\x1b[92m" << keyAndVals.first << "\x1b[97m" << ": ";
            for (bool i : keyAndVals.second) {
                if (i) {
                    std::cout << "\x1b[94m0\x1b[97m";
                }
                else {
                    std::cout << "_";
                }
            }
            std::cout << "\n";
        }
        index++;

    }
    std::cout << "\x1b[90m'Enter'\x1b[93m : Save\nEnter \x1b[93m1 - 8\x1b[97m to add or delete a sound in slots \x1b[93m1 - 8.\x1b[97m\n" << std::endl;





}

/**
* @brief Method to edit the pattern associated with a sound
* @param[in] sequence the map which holds our sounds and their associated patterns.
* @param[in] keyndVals a pair containing the name of the sound whos patttern we will be editing, and its associated pattern
* @return void
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

/**
* @brief Helper method to find the key corresponding to a certain index in the map
* @param[in] soundIndex the index of the sound whos key we want,
* @param[in] sequence the currrent sequence, the string is the name of the sound, and the array is the pattern
* @returns a pair consisting of the name of the sound at the specified index, and an array representing the pattern
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

/**
* @brief Helper method to add a new sound to the sequence
* @param sequence; the currrent sequence, the string is the name of the sound, and the array is the pattern
* @return void
*/
void Interface::addSound(int newSound, std::map<std::string, std::array<bool, 8>>& sequence, Audio_Engine& E) {
    switch (newSound) {
    case 1:
        sequence.insert(std::make_pair("Kick 70s 1.wav", std::array<bool, 8>{false, false, false, false, false, false, false, false}));
        E.Preload("../Assets/Kick 70s 1.wav", "Kick 70s 1.wav");
        break;
    case 2:
        sequence.insert(std::make_pair("Snare 70s MPC 3.wav", std::array<bool, 8>{false, false, false, false, false, false, false, false}));
        E.Preload("../Assets/Snare 70s MPC 3.wav", "Snare 70s MPC 3.wav");
        break;
    case 3:
        sequence.insert(std::make_pair("Hihat Closed 80s UK Disco Vinyl.wav", std::array<bool, 8>{false, false, false, false, false, false, false, false}));
        E.Preload("../Assets/Hihat Closed 80s UK Disco Vinyl.wav", "Hihat Closed 80s UK Disco Vinyl.wav");
        break;
    }
}

/**
* @brief Method called when the user selects the edit sequence option. It will display the sequence editor, or if no sounds have been added, will prompt the user to add a sound.
* @param sequence the currrent sequence, the string is the name of the sound, and the array is the pattern
* @return int, just zero as this function does not return anything useful
*/
void Interface::editSequence(std::map<std::string, std::array<bool, 8>>& sequence, Audio_Engine& E) {
    clearScreen();
    int newSound;
    if (!sequenceSet) {
        std::cout << "Select a sound to add to the sequence:\n";
        std::cout << "\n\x1b[90m-(1)\x1b[93m\x1b[93mKick\x1b[97m\n\x1b[90m-(2)\x1b[93m\x1b[93mSnare\x1b[97m\n\x1b[90m-(3)\x1b[93m\x1b[93mHat\x1b[97m\n";
        sequenceSet = true;
        char ch = _getch();
        while (true) {
            if (ch - '0' == 1) {
                newSound = ch - '0';
                addSound(newSound, sequence, E);
                return editSequence(sequence, E);
                break;
            }
            else if (ch - '0' == 2) {
                newSound = ch - '0';
                addSound(newSound, sequence, E);
                return editSequence(sequence, E);
                break;
            }
            else if (ch - '0' == 3) {
                newSound = ch - '0';
                addSound(newSound, sequence, E);
                return editSequence(sequence, E);
                break;
            }
            ch = _getch();
        }
    }
    displaySequence(sequence);
    int soundIndex;
    std::cout << "Which sound would you like to edit? (enter corresponding number)\n\n\x1b[90m'A'\x1b[93m: \x1b[93mAdd new sound\x1b[97m\n\x1b[90m'Enter'\x1b[93m: \x1b[93mSave and exit\x1b[97m";
    char ch = _getch();
    soundIndex = ch - '0';
    if (ch == 13) {
        return;
    }
    if (ch == 97) {
        clearScreen();
        std::cout << "Select sound to add.\n-(1)\x1b[93mKick\x1b[97m\n-(2)\x1b[93mSnare\x1b[97m\n-(3)\x1b[93mHat\x1b[97m\n";
        char ch = _getch();
        while (true) {
            if (ch - '0' == 1) {
                newSound = ch - '0';
                addSound(newSound, sequence, E);
                return editSequence(sequence, E);
            }
            else if (ch - '0' == 2) {
                newSound = ch - '0';
                addSound(newSound, sequence, E);
                return editSequence(sequence, E);
            }
            else if (ch - '0' == 3) {
                newSound = ch - '0';
                addSound(newSound, sequence, E);
                return editSequence(sequence, E);
            }
            ch = _getch();
        }
        //std::cin >> newSound;
        //returns to editor
    }
    std::pair<std::string, std::array<bool, 8>> keyAndVals = getKeyByIndex(soundIndex, sequence);
    if (keyAndVals.first != "") {
        editSound(sequence, keyAndVals, soundIndex);
    }
    // Flip the value in the map of the index entered (minus 1 for zero indexing)
    return editSequence(sequence, E);
}
/**
 * During playback, this displays a small playhead to show when a step creates sound.
 * 
 * \param sequence - the sequence
 * \param currentBeat - the index of the playhead
 */
void Interface::displaySequenceWithIndicator(const std::map<std::string, std::array<bool, 8>>& sequence, int currentBeat) {
    
    int index = 1;
    /*for (int i = 0; i < sequence.size(); i++) {
        for (int j = 0; j < 8; j++) {
            if (j == currentBeat) {
                screen[i * 8 + j] = (sequence[].second[j] ? "\x1b[94m0\x1b[97m" : "_");
            }
        }
    }*/
    int row = 0;
    for (const auto& i : sequence) {
        //std::cout << "-(" << index << ")";
        //for (int n = 0; n < 40 - i.first.size(); n++) {
        //    std::cout << " "; // aligns all patterns accounting for different name lengths of sounds
        //}
        //std::cout << i.first << ": ";
        //index++;
        
        for (int j = 0; j < 8; j++) {
            if (j == currentBeat) {
                screen[row * 8 + j].Attributes = YELLOW | FOREGROUND_INTENSITY; // White color
                screen[row * 8 + j].Char.UnicodeChar = (WCHAR)(i.second[j] ? '|' :  '|');
            }
            else {
                screen[row * 8 + j].Attributes = (i.second[j] ? FOREGROUND_BLUE | FOREGROUND_INTENSITY : WHITE | FOREGROUND_INTENSITY); // White color
                screen[row * 8 + j].Char.UnicodeChar = (WCHAR)(i.second[j] ? '0' : '_');//L"\x1b[94m0\x1b[97m" : L"_");
            }
            
            
        }
        row =row + 1;
        int hOffset = 46;
        int vOffset = 1;
        SMALL_RECT writeRegion = { 0 + hOffset, 0 + vOffset, 8 - 1 + hOffset, sequence.size() - 1 + vOffset};
        WriteConsoleOutput(hConsole, screen, {8,3}, {0,0}, &writeRegion);
        
    }
    
}
/**
* @brief function to play the sequence out loud
* @param[in] sequence the sequence we will be playing
* @returns int just zero, as this function does not return anyth
*/
void Interface::playSequence(const std::map<std::string, std::array<bool, 8>>& sequence, Audio_Engine& E) {
    //displayPlayerMenu(sequence, 0);
    displayMainMenu(sequence);
    Clock c = Clock::Clock(BPM);
    std::vector<std::string> names;
    std::vector<std::array<bool, 8>> patterns;
    for (auto i = sequence.begin(); i != sequence.end(); i++) {
         /*E.Preload("../Assets/" + i->first, i->first);*/
         names.push_back(i->first);
         patterns.push_back(i->second);

     }

    int index = 0;
    char ch = 'c';
    c.startClock();
    bool running = true;
    //clearScreen();
    //std::cout << "BPM: " << BPM << "      Pattern name: " << patternName << "\n";
    while (running) {
        if (c.interval()) {
            displaySequenceWithIndicator(sequence, index);
            for (int i = 0; i < patterns.size() / sizeof(bool); i++) {
                if (patterns[i][index]) {
                    std::string name = names[i];
                    
                    E.PlaySound_(name);
                    
                }
            }
            E.tick();

            index++;
        }
        
        if (index > 7) {
            index = 0;
        }
            if (_kbhit()) {
                ch = _getch();
                if (ch == 32) {
                    running = false;
                }

            }
        }

    playing = !playing;
    return;
}

/**
* @brief method to set the bpm based on user input
* @param[in] sequence, the current sequence
* @param[in] edit, a boolean used for recursive calls to tell the function if it should take input from typing or from the arrow keys
* @return void
*/
void Interface::setBPM(const std::map<std::string, std::array<bool, 8>>& sequence, bool edit) {
    clearScreen();
    displayMainMenu(sequence);
    if (edit) {
        std::cout << "Type in your bpm and press Enter to save:\n";
        std::cin >> BPM;
        if (BPM == 0) {
            clearScreen();
            std::cout << "\x1b[91mBPM cannot be zero\x1b[97m\n";
            Sleep(750);
            setBPM(sequence, true);
        }
        return;
    }
    std::cout << "\nPress the up and down arrows to scroll BPM.\n\n'E': Type it\n'Enter': Confirm\n";
    char ch = _getch();
    while (ch != 13) {
        if (ch == 101) {
            BPM = 0;
            return setBPM(sequence, true);
        }
        if (ch == 72) {
            BPM = BPM + 10;
            return setBPM(sequence, false);
        }
        if (ch == 80) {
            BPM = BPM - 10;
            return setBPM(sequence, false);
        }
        ch = _getch();
    }
    return;
}

/**
* @brief a method to name the pattern
*/
void Interface::setNewName() {
    clearScreen();
    std::cout << "Please enter a name for your pattern:\n";
    std::string name = "";
    while (name == "") {
        std::getline(std::cin, name);
    }
    std::cout << "Confirm name change to: \"" << name << "\" by pressing Enter, or cancel by pressing any other key";
    char ch = _getch();
    if (ch != 13) {
        return;
    }
    patternName = name;
    return;
}

/**
* @brief a method to perform an action based on user input
* @param[in] sequence, the seequence we will be performing actions on
* @param[in] E, the audio engine we will use to play sounds
* @return int, -1 if we should close the program, 0 otherwise
*/
int Interface::performAction(char choice, std::map<std::string, std::array<bool, 8>>& sequence, Audio_Engine& E) {
    bool exit = false;
    switch (choice) {
    case 49: {
        editSequence(sequence, E);
        break;
    }
    case 32: {
        if (!sequence.empty()) {
            playSequence(sequence, E);
        }
        else {
            clearScreen();
            std::cout << "Sequence is Empty.";
            Sleep(750);
            
        }
        
        break;
    }
    case 50: {
        if (!sequence.empty()) {
            setBPM(sequence, false);
        }
        else {
            clearScreen();
            std::cout << "\x1b[91mSequence is Empty.\x1b[97m";
            Sleep(750);

        }
        
        break;
    }
    case 51: {
        setNewName();
        break;
    }
    case 52: {
        clearScreen();
        std::cout << "\x1b[92mHave a good day.\x1b[97m";
        Sleep(1000);
        return -1;
        break;
    }
    default:
        clearScreen();
        std::cout << "\x1b[91mInvalid choice. Please try again.\x1b[97m\n";
        Sleep(750);

    }
    return 0;
}


/**
* @brief class to perform unit tests
*/
int Interface::_test() {
    int status = 0;
    Audio_Engine E = Audio_Engine::Audio_Engine();
    // Test 1: Constructor
    try {
        Interface a;
    }
    catch (std::exception& e) {
        std::cout << "Interface constructor failed. Details: " << e.what() << std::endl;
        return 1;
    }

    // Test 2: getKeyByIndex
    try {
        Interface a;
        std::map<std::string, std::array<bool, 8>> testSequence;
        testSequence["Kick"] = { true, false, true, false, true, false, true, false };
        testSequence["Snare"] = { false, true, false, true, false, true, false, true };

        auto result = a.getKeyByIndex(1, testSequence);
        if (result.first != "Kick" || result.second != std::array<bool, 8>{true, false, true, false, true, false, true, false}) {
            throw std::runtime_error("getKeyByIndex returned unexpected result.");
        }
    }
    catch (std::exception& e) {
        std::cout << "getKeyByIndex test failed. Details: " << e.what() << std::endl;
        return 2;
    }

    // Test 3: addSound
    try {
        Interface a;
        std::map<std::string, std::array<bool, 8>> sequence;
        a.addSound(1, sequence, E);

        a.addSound(2, sequence, E);
        a.addSound(3, sequence, E);
        if (sequence.size() != 3 || sequence.find("Kick 70s 1.wav") == sequence.begin()) {
            throw std::runtime_error("addSound did not add the expected sound.");
        }
    }
    catch (std::exception& e) {
        std::cout << "addSound test failed. Details: " << e.what() << std::endl;
        return 3;
    }


    // Test 4: editSequence, then setBPM

    
    try {
        Interface a;
        std::map<std::string, std::array<bool, 8>> testSequence;

        a.performAction(49, testSequence, E);
        a.performAction(50, testSequence, E);
    }
    catch (std::exception& e) {
        std::cout << "setBPM test failed. Details: " << e.what() << std::endl;
        return 4;
    }
    

    // Test 5: performAction (exit)
    try {
        Interface a;
        std::map<std::string, std::array<bool, 8>> testSequence;
        int result = a.performAction('4', testSequence, E);
        if (result != -1) {
            throw std::runtime_error("performAction did not return expected value for exit action.");
        }
    }
    catch (std::exception& e) {
        std::cout << "performAction (exit) test failed. Details: " << e.what() << std::endl;
        return 5;
    }

    // Test 6: performAction (invalid action)
    try {
        Interface a;
        std::map<std::string, std::array<bool, 8>> testSequence;
        int result = a.performAction('9', testSequence, E);
        if (result != 0) {
            throw std::runtime_error("performAction did not return expected value for invalid action.");
        }
    }
    catch (std::exception& e) {
        std::cout << "performAction (invalid action) test failed. Details: " << e.what() << std::endl;
        return 6;
    }

    // Test 7: playSequence
    try {
        Interface a;
        std::map<std::string, std::array<bool, 8>> testSequence;
        playSequence(testSequence, E);
    }
    catch (std::exception& e) {
        std::cout << "playSequence didn't run as expected." << e.what() << std::endl;
        return 7;
    }

    std::cout << "All tests passed successfully." << std::endl;
    return 0;
}

#ifndef INTERFACE_H
#define INTERFACE_H

#include <array>
#include <map>
#include <string>
#include "Clock.h"
#include "Interface.h"
#include "Audio_Engine.h"

class Interface {
public:
    static void displaySequence(const std::map<std::string, std::array<bool, 8>>& sequence);
    static void displayPlayerSequence(const std::map<std::string, std::array<bool, 8>>& sequence, int headIndex);
    static void displayMainMenu(const std::map<std::string, std::array<bool, 8>>& sequence);
    static void displayPlayerMenu(const std::map<std::string, std::array<bool, 8>>& sequence, int index);
    static void soundEditDisplay(const std::map<std::string, std::array<bool, 8>>& sequence, int toChange, std::pair<std::string, std::array<bool, 8>>& keyAndVals);
    static void editSound(std::map<std::string, std::array<bool, 8>>& sequence, std::pair<std::string, std::array<bool, 8>>& keyAndVals, int soundIndex);
    static std::pair<std::string, std::array<bool, 8>> getKeyByIndex(int soundIndex, const std::map<std::string, std::array<bool, 8>>& sequence);
    static void addSound(int newSound, std::map<std::string, std::array<bool, 8>>& sequence, Audio_Engine& E);
    static void editSequence(std::map<std::string, std::array<bool, 8>>& sequence, Audio_Engine& E);
    static void playSequence(const std::map<std::string, std::array<bool, 8>>& sequence, Audio_Engine& E);
    static void setBPM(const std::map<std::string, std::array<bool, 8>>& sequence, bool edit);
    static void setNewName();
    static int performAction(char choice, std::map<std::string, std::array<bool, 8>>& sequence, Audio_Engine& E);
    static int _test();
};

#endif // INTERFACE_H

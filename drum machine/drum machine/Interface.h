#ifndef INTERFACE_H
#define INTERFACE_H

#include <array>
#include <map>
#include <string>

class Interface {
public:
    static void displaySequence(const std::map<std::string, std::array<bool, 8>>& sequence);
    static void displayMainMenu(const std::map<std::string, std::array<bool, 8>>& sequence);
    static void soundEditDisplay(const std::map<std::string, std::array<bool, 8>>& sequence, int toChange, std::pair<std::string, std::array<bool, 8>>& keyAndVals);
    static void editSound(std::map<std::string, std::array<bool, 8>>& sequence, std::pair<std::string, std::array<bool, 8>>& keyAndVals, int soundIndex);
    static std::pair<std::string, std::array<bool, 8>> getKeyByIndex(int soundIndex, const std::map<std::string, std::array<bool, 8>>& sequence);
    static void addSound(int newSound, std::map<std::string, std::array<bool, 8>>& sequence);
    static int editSequence(std::map<std::string, std::array<bool, 8>>& sequence);
    static int playSequence(const std::map<std::string, std::array<bool, 8>>& sequence);
    static int setBPM(const std::map<std::string, std::array<bool, 8>>& sequence, bool edit);
    static int setNewName();
    static int performAction(char choice, std::map<std::string, std::array<bool, 8>>& sequence);
    static int _test();
};

#endif // INTERFACE_H

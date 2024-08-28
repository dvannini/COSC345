#ifndef INTERFACE_H
#define INTERFACE_H

#include <array>
#include <map>
#include <string>

class Interface {
public:
    static void displaySequence(const std::map<std::string, std::array<bool, 8>>& sequence);
    static void displayMainMenu(const std::map<std::string, std::array<bool, 8>>& sequence);
    static void soundEditDisplay(const std::pair<std::string, std::array<bool, 8>>& keyAndVals);
    static void editSound(std::map<std::string, std::array<bool, 8>>& sequence, std::pair<std::string, std::array<bool, 8>>& keyAndVals);
    static std::pair<std::string, std::array<bool, 8>> getKeyByIndex(int soundIndex, const std::map<std::string, std::array<bool, 8>>& sequence);
    static void addSound(int newSound, std::map<std::string, std::array<bool, 8>>& sequence);
    static int editSequence(std::map<std::string, std::array<bool, 8>>& sequence);
    static int playSequence(const std::map<std::string, std::array<bool, 8>>& sequence);
    static int setBPM(const std::map<std::string, std::array<bool, 8>> sequence, bool edite);
    static int setNewName();
    static int performAction(int choice, std::map<std::string, std::array<bool, 8>>& sequence);
};

#endif // INTERFACE_H

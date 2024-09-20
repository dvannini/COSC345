#pragma once
#ifndef INTERFACE_H
#define INTERFACE_H

#include <array>
#include <map>
#include <string>
#include "Clock.h"
#include "Interface.h"
#include "Audio_Engine.h"
#include <Windows.h>

//color macros for terminal writing
#define YELLOW 14 
#define RED 12
#define WHITE 15
#define GREEN 10

#define WIDTH 8
#define HEIGHT 3
#define SCREEN_SIZE WIDTH*HEIGHT //width x height

class Interface {
public:
    Interface();
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

    static void displaySequenceWithIndicator(const std::map<std::string, std::array<bool, 8>>& sequence, int currentBeat);
    
    static int _test();
    
private:
    static HANDLE hConsole;
    static CHAR_INFO* screen;
    
};

#endif // INTERFACE_H

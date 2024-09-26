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

#define WIDTH 40 //8
#define HEIGHT 25 //3


#define SCREEN_SIZE WIDTH*HEIGHT //width x height

//for sound list
#define S_WIDTH 10
#define S_HEIGHT 10


#define ESC "\x1b"
#define CSI "\x1b["
class Interface {
public:
    Interface();
    
    static void displayMainMenu(const std::map<std::string, std::array<bool, 8>>& sequence);
    
    static void addSound(int newSound, std::map<std::string, std::array<bool, 8>>& sequence); //Audio_Engine& E
    
    static void playSequence(std::map<std::string, std::array<bool, 8>>& sequence); //  Audio_Engine& E
    
    static int performAction(char choice, std::map<std::string, std::array<bool, 8>>& sequence); // Audio_Engine& E
    
    static void selectSound(std::map<std::string, std::array<bool, 8>>& sequence);
    //static void editRow(std::map<std::string, std::array<bool, 8>>& sequence);
    /**
     * Shows the sequence editor.
     * 
     * \param sequence
     */
    static void showEditor(std::map<std::string, std::array<bool, 8>>& sequence, int segment);
    /**
     * Updates the screen.
     * 
     */
    static void refresh();
    
    /**
     * Simple method to draw a step sequencer cell.
     * 
     * \param i - x coord
     * \param j - y coord
     * \param on - whether this step will sound
     * \param altView - velocity/pitch view (not yet implemented)
     */
    static void drawCell(int v, int h, bool on);
    static void drawPlayhead(int i, int size);
    static int _test();
    static Audio_Engine* E;
    
private:
    static HANDLE hConsole;
    static CHAR_INFO* screen; /// sequencer canvas
    static CHAR_INFO* bSounds; //sound list

    static void drawBox(COORD pos, int sizeX, int sizeY);
    static void drawLine(COORD pos, int length, bool horizontal = true, bool ends = false);
    
    static int windowX;
    static int windowY;

    static SHORT originX;
    static SHORT originY;

    static SMALL_RECT region; /// the region to read or write console buffer content
    static bool altView;

    static bool status;

    static int selection;

    static int pIndex; /// index of playhead when playing the pattenr

    static bool exit_;

    
};

#endif // INTERFACE_H

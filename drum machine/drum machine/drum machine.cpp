// drum machine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>
#include "resource.h"
#include <thread>
#pragma comment(lib, "winmm.lib")

int main()
{
    /*
        Sequencer:
        0 - Nothing
        1 - Kick
        2 - Snare
    */
    
    int sequence[] = { 4, 1, 4, 1, 4, 1, 4, 0 };

    for (int i = 0; i < 100; i++) {
        // Switch case for drum selection
        switch (sequence[i % 8]) {
        case 0:
            break;
        case 1:
            PlaySound(L"../Assets/Kick 70s 1.wav", NULL, SND_FILENAME | SND_ASYNC);
            std::cout << "played kick.";
            break;
        case 2:
            PlaySound(L"../Assets/Snare 70s MPC 3.wav", NULL, SND_FILENAME | SND_ASYNC);
            std::cout << "played snare.";
            break;
        case 3:
            PlaySound(L"../Assets/Hihat Closed 80s UK Disco Vinyl.wav", NULL, SND_FILENAME | SND_ASYNC);
            std::cout << "played HiHat.";
            break;
        case 4:
            PlaySound(L"../cosc345/drum machine/Assets/very-fat-808.wav", NULL, SND_FILENAME | SND_ASYNC);
            std::cout << "played HiHat.";
            break;
        }
        //idr_wave is the imported sound id wave1: kick wave2: snare wave3: hihat
        //first parameter: sound file to play
        //second: leave as null most of the time
        //third: flags for where or how to play the sound

        Sleep(500);//sleep to let sound play while program is running
    }
    return 0;
}



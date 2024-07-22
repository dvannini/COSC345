// drum machine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>
#include "resource.h"

#pragma comment(lib, "winmm.lib")

int main()
{
    /*
        Sequencer:
        0 - Nothing
        1 - Kick
        2 - Snare
    */
    int sequence[] = { 1, 0, 2, 0, 0, 1, 2, 0 };
    for (int i = 0; i < 100; i++) {
        // Switch case for drum selection
        switch (sequence[i % 8]) {
        case 0:
            break;
        case 1:
            PlaySound(MAKEINTRESOURCE(IDR_WAVE1), NULL, SND_RESOURCE | SND_ASYNC);
            break;
        case 2:
            PlaySound(MAKEINTRESOURCE(IDR_WAVE2), NULL, SND_RESOURCE | SND_ASYNC);
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



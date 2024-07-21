// drum machine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>
#include "resource.h"

#pragma comment(lib, "winmm.lib")

int main()
{
    PlaySound(MAKEINTRESOURCE(IDR_WAVE1), NULL, SND_RESOURCE | SND_ASYNC); //idr_wave is the imported sound id wave1: kick wave2: snare wave3: hihat
    //first parameter: sound file to play
    //second: leave as null most of the time
    //third: flags for where or how to play the sound

    Sleep(1000);//sleep to let sound play while program is running
    return 0;
}



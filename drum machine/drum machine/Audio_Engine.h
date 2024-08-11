#pragma once
#include <filesystem>
#include <iostream>
#include <Windows.h>
class Audio_Engine
{
public:
	Audio_Engine(); //constructor class
	void loadSound(char* sound); // load sounds into virtual memory
	void play(int sound);

};


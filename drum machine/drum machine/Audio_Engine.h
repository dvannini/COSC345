#pragma once
#include <filesystem>
class Audio_Engine
{
public:
	Audio_Engine(); //constructor class
	void loadSound(char* sound); // load sounds into virtual memory
	void play();

private:
	char** mem; //the memory matrix, initialized with the sounds used on project startup (at least for now)
	//queue soundQueue -- the queue of sound events to accumulate and buffer
	

};


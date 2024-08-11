#include <vector>
#include <chrono>
#include <iostream>
#include "Audio_Engine.h"

#pragma once
class Sequence {
public:
	Sequence();
	Sequence(std::vector<int>);
	void playSequence(int msPerBeat);
private:
	std::vector<int> sequence;
};
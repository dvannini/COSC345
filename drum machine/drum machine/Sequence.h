#include <vector>
#include <chrono>
#include <iostream>
#include "Audio_Engine.h"

#pragma once
class Sequence {
public:
	Sequence();
	Sequence(std::vector<int>);
	std::vector<int> getSequence();
	void setSequence(std::vector<int>);
	void playSequence(int, int);
	static int test_();
private:
	std::vector<int> sequence;
};
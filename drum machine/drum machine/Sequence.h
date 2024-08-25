#include <vector>
#include <chrono>
#include <iostream>
#include "Audio_Engine.h"

#pragma once
class Sequence {
public:
	Sequence();
	~Sequence();
	Sequence(std::vector<std::vector<int>>);
	std::vector<std::vector<int>> getSequence();
	void setSequence(std::vector<std::vector<int>>);
	void playSequence(int, int);
	std::vector<int> getColumn(int playhead);
	static int test_();
private:
	std::vector<std::vector<int>> sequence;
};
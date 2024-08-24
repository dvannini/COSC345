#pragma once
#ifndef CLOCK_H
#define CLOCK_H
#include <chrono>
class Clock
{
public:
	Clock(int tempo);
	~Clock();
	void startClock();
	void setBPM(int BPM);
	bool interval();
	static int test_();

private:
	//uint64_t time = 0;
	std::chrono::high_resolution_clock::time_point time;
	uint64_t tempo_ms;
};
#endif



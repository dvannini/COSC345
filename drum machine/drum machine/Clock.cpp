#include "Clock.h"
#include <iostream>

Clock::Clock(int tempo) {
	this->tempo_ms = (60000 / tempo) / 2;
}

Clock::~Clock() {

}


void Clock::startClock() {
	time = std::chrono::high_resolution_clock::now();
}

void Clock::setBPM(int BPM) {
	tempo_ms = (60000 / BPM) / 2;
}


bool Clock::interval() {
	auto timeNow = std::chrono::high_resolution_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(timeNow - time).count();

	if (elapsed >= tempo_ms) {
		time = std::chrono::high_resolution_clock::now();
		
		return true;
	}
	else {
		return false;
	}
}


int Clock::test_() {
	int bpm = 120;
	try {
		Clock c(bpm);
		c.startClock();
	}
	catch (std::exception& e) {
		std::cerr << "Constructor failed" << e.what();
		return 1;
	}
	try {
		Clock c(bpm);
		c.startClock();

	}
	catch (std::exception& e) {
		throw std::exception("interval function failed");
		return 2;
	}
	return 0;
	

}


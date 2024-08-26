#include "Clock.h"
#include <iostream>
/*****************************************************************//**
 * \file   Clock.cpp
 * \brief  a class to handle clock timings for the sequencer
 *
 * \author Ben Addison, Alex Haszard
 * \date   August 2024
 *********************************************************************/
 /**
  * Constructor for clock. sets the tempo of the drum machine
  *
  */
Clock::Clock(int tempo) {
	this->tempo_ms = (60000 / tempo) / 2;
}
/**
 * Destructor for clock.
 *
 */
Clock::~Clock() {

}

/**
 * Starts running the clock at the time of calling the function. Should be used when user plays the sequence
 *
 */
void Clock::startClock() {
	time = std::chrono::high_resolution_clock::now();
}

void Clock::setBPM(int BPM) {
	tempo_ms = (60000 / BPM) / 2;
}

/**
 * Signals when a time interval (beat); determined by the tempo is reached.
 *
 * \return bool - when a time interval has been met
 */
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

/**
 * Test class for the clock.
 *
 * \return 0 - tests pass, 1 - tests fail
 */
int Clock::test_() {
	int bpm = 120;
	try {
		Clock c(bpm);
		c.startClock();
	}
	catch (std::exception& e) {
		std::cerr << "Constructor failed" << e.what();
	}
	try {
		Clock c(bpm);
		c.startClock();

	}
	catch (std::exception& e) {
		throw std::exception("interval function failed")
	}
	
	

}


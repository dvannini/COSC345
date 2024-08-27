#include <vector>
#include <chrono>
#include <iostream>
#include "Audio_Engine.h"

#pragma once
/**
 * Sequence class to store and process sequence data.
 */
class Sequence {
public:
	/**
	 * Default constructor, inits with a simple 2-step rhythm.
	 *
	 * 
	 */
	Sequence();
	/**
	 * Default destructor.
	 * 
	 */
	~Sequence();
	/**
	 * Constructor function with desired sequence data
	 *
	 * \param sequenceIn an Int vector which contains the 1-based index of each sound to play (0 is nothing).
	 */
	Sequence(std::vector<std::vector<int>> sequenceIn);
	/**
	* Getter function for sequence variable
	*
	* \return sequence variable
	*/
	std::vector<std::vector<int>> getSequence();
	/**
	 * Setter function for sequence variable
	 *
	 * \param sequence variable to be updated
	 */
	void setSequence(std::vector<std::vector<int>>);
	
	/**
	 * Gets a column of sounds to play at a given playhead in the sequence.
	 *
	 * \param playhead - the index of the sequence to grab sounds from
	 * \return a vector of ints representing the sound IDs to play
	 */
	std::vector<int> getColumn(int playhead);
	/**
	 * Test function
	 *
	 * \return 0 if all tests pass.\n 1 if default constructor (or getter) fails\n 2 if constructor fails\n 3 if setter function fails\n 4 if playSequence fails.
	 */
	static int test_();
private:
	std::vector<std::vector<int>> sequence; ///<the doubly int vector to store the sequence the data
};
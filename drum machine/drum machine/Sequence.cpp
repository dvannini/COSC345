#include "Sequence.h"
#include "Clock.h"

/**
 * Default Constructor function
 * Takes no input, and uses a basic DNB kick and snare sequence.
 */
Sequence::Sequence()
{
    sequence = {
        {1, 0, 0, 0, 0, 1, 0, 0},
        {0, 0, 2, 0, 0, 0, 2, 0},
        {0, 0, 0, 0, 3, 0, 0, 0}
    }; //doubly vector of ints
}

Sequence::~Sequence() {

}

/**
 * Constructor function
 *
 * \param sequenceIn an Int vector which contains the 1-based index of each sound to play (0 is nothing).
 */
Sequence::Sequence(std::vector<std::vector<int>> sequenceIn)
{
	sequence = sequenceIn;
}

/**
 * Getter function for sequence variable
 *
 * \return sequence variable
 */
std::vector<std::vector<int>> Sequence::getSequence()
{
    return sequence;
}

/**
 * Setter function for sequence variable
 *
 * \param sequence variable to be updated
 */
void Sequence::setSequence(std::vector<std::vector<int>> sequenceIn)
{
    sequence = sequenceIn;
}


/**
 * Gets a column of sounds to play at a given playhead in the sequence.
 * 
 * \param playhead - the index of the sequence to grab sounds from
 * \return a vector of ints representing the sound IDs to play
 */
std::vector<int> Sequence::getColumn(int playhead) {
    std::vector<int> data = { sequence[0][playhead], sequence[1][playhead], sequence[2][playhead] };
    
    return data;
}

/**
 * Test function
 *
 * \return 0 if all tests pass.\n 1 if default constructor (or getter) fails\n 2 if constructor fails\n 3 if setter function fails\n 4 if playSequence fails.
 */
int Sequence::test_()
{
    std::vector<std::vector<int>> testSequence = {
        {1, 0, 0, 0},
        {0, 0, 2, 0},
        {0, 0, 0, 0}
    }; //doubly vector of ints
    Sequence testDefaultCon = Sequence::Sequence();
    Sequence testCon = Sequence::Sequence(testSequence);
    // test default constructor (and getter)
    if (testDefaultCon.getSequence().size() != 3 ) return 1;
    // test constructor with given sequence
    if (testCon.getSequence().size() != 3) return 2;
    // test setter function
    testDefaultCon.setSequence(testSequence);
    if (testDefaultCon.getSequence().size() != 3) return 3;
    return 0;
}

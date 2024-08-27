#include "Sequence.h"
#include "Clock.h"


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


Sequence::Sequence(std::vector<std::vector<int>> sequenceIn)
{
	sequence = sequenceIn;
}


std::vector<std::vector<int>> Sequence::getSequence()
{
    return sequence;
}


void Sequence::setSequence(std::vector<std::vector<int>> sequenceIn)
{
    sequence = sequenceIn;
}



std::vector<int> Sequence::getColumn(int playhead) {
    std::vector<int> data = { sequence[0][playhead], sequence[1][playhead], sequence[2][playhead] };
    
    return data;
}


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

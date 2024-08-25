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
 * Plays the sequence with a given BPM
 *
 * \param msPerBeat how many milliseconds per beat, which essentially determines the BPM of playback.
 * \param numberOfLoops how many times the loop will play.
 */
void Sequence::playSequence(int bpm, int numberOfLoops)
{
    
    //Audio_Engine engine = Audio_Engine::Audio_Engine();
    //// Time at beginning of loop
    //uint64_t startTime = std::chrono::duration_cast<std::chrono::milliseconds>(
    //    std::chrono::system_clock::now().time_since_epoch()
    //).count();

    //int soundIndex = 0;
    //engine.Preload("../Assets/Snare 70s MPC 3.wav", "snare");
    //engine.Preload("../Assets/Kick 70s 1.wav", "kick");
    //engine.Preload("../Assets/Hihat Closed 80s UK Disco Vinyl.wav", "hat");
    //std::vector<const char*> t = {"kick", "snare", "hat"};
    //while (soundIndex / sequence.size() < numberOfLoops) {
    //    // Time at current point in loop
    //    uint64_t currentTime = std::chrono::duration_cast<std::chrono::milliseconds>(
    //        std::chrono::system_clock::now().time_since_epoch()
    //    ).count();
    //    // Once the time passed is greater than or equal to the ms per beat
    //    if (currentTime - startTime >= msPerBeat) {
    //        std::cout << soundIndex << std::endl;
    //        // Play the sound and increment the index variable
    //        int index = sequence[soundIndex % sequence.size()];
    //        if (index != 0) engine.PlaySound_(t[index - 1]);//sequence[soundIndex % sequence.size()]);
    //        soundIndex++;
    //        // Add the ms per beat to the start time
    //        startTime += msPerBeat;
    //    }
    //}
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

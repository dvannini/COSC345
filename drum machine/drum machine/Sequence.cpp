#include "Sequence.h"

/**
 * Default Constructor function
 * Takes no input, and uses a basic DNB kick and snare sequence.
 */
Sequence::Sequence()
{
    sequence = { 1, 0, 2, 0, 0, 1, 2, 0 };
}

/**
 * Constructor function
 *
 * \param sequenceIn an Int vector which contains the 1-based index of each sound to play (0 is nothing).
 */
Sequence::Sequence(std::vector<int> sequenceIn)
{
	sequence = sequenceIn;
}

/**
 * Getter function for sequence variable
 *
 * \return sequence variable
 */
std::vector<int> Sequence::getSequence()
{
    return sequence;
}

/**
 * Setter function for sequence variable
 *
 * \param sequence variable to be updated
 */
void Sequence::setSequence(std::vector<int> sequenceIn)
{
    sequence = sequenceIn;
}

/**
 * Plays the saved sequence until the numberOfLoops is reached, with the BPM decided by the msPerBeat variable
 *
 * \param msPerBeat how many milliseconds per beat, which essentially determines the BPM of playback.
 * \param numberOfLoops how many times the loop will play.
 */
void Sequence::playSequence(int msPerBeat, int numberOfLoops)
{
    Audio_Engine engine = Audio_Engine::Audio_Engine();
    // Time at beginning of loop
    uint64_t startTime = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch()
    ).count();

    int soundIndex = 0;
    engine.Preload("../Assets/Snare 70s MPC 3.wav", "snare");
    engine.Preload("../Assets/Kick 70s 1.wav", "kick");
    engine.Preload("../Assets/Hihat Closed 80s UK Disco Vinyl.wav", "hat");
    std::vector<const char*> t = {"kick", "snare", "hat"};
    while (soundIndex / sequence.size() < numberOfLoops) {
        // Time at current point in loop
        uint64_t currentTime = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()
        ).count();
        // Once the time passed is greater than or equal to the ms per beat
        if (currentTime - startTime >= msPerBeat) {
            std::cout << soundIndex << std::endl;
            // Play the sound and increment the index variable
            int index = sequence[soundIndex % sequence.size()];
            if (index != 0) engine.PlaySound_(t[index - 1]);//sequence[soundIndex % sequence.size()]);
            soundIndex++;
            // Add the ms per beat to the start time
            startTime += msPerBeat;
        }
    }
}


/**
 * Test function
 *
 * \return 0 if all tests pass.\n 1 if default constructor (or getter) fails\n 2 if constructor fails\n 3 if setter function fails\n 4 if playSequence fails.
 */
int Sequence::test_()
{
    std::vector<int> testSequence = { 0,1,2,3 };
    Sequence testDefaultCon = Sequence::Sequence();
    Sequence testCon = Sequence::Sequence(testSequence);
    // test default constructor (and getter)
    if (testDefaultCon.getSequence().size() != 8) return 1;
    // test constructor with given sequence
    if (testCon.getSequence().size() != 4) return 2;
    // test setter function
    testDefaultCon.setSequence(testSequence);
    if (testDefaultCon.getSequence().size() != 4) return 3;
    // ensure playSequence runs without errors
    try {
        testCon.playSequence(1000, 1);
    }
    catch (...) {
        return 4;
    }
    return 0;
}

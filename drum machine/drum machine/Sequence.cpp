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
 * Plays the saved sequence indefinitely, with the BPM decided by the msPerBeat variable
 *
 * \param msPerBeat how many milliseconds per beat, which essentially determines the BPM of playback.
 */
void Sequence::playSequence(int msPerBeat)
{
    Audio_Engine engine = Audio_Engine::Audio_Engine();
    // Time at beginning of loop
    uint64_t startTime = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch()
    ).count();

    int soundIndex = 0;
    engine.Preload("./Assets/Hihat Closed 56 TL.wav", "hat");
    while (true) {
        // Time at current point in loop
        uint64_t currentTime = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()
        ).count();
        // Once the time passed is greater than or equal to the ms per beat
        if (currentTime - startTime >= msPerBeat) {
            std::cout << soundIndex << std::endl;
            // Play the sound and increment the index variable
            engine.PlaySound_("hat");//sequence[soundIndex % sequence.size()]);
            soundIndex++;
            // Add the ms per beat to the start time
            startTime += msPerBeat;
        }
    }
}

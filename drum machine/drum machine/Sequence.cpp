#include "Sequence.h"

// Default initializer (generic dnb sequence)
Sequence::Sequence()
{
    sequence = { 1, 0, 2, 0, 0, 1, 2, 0 };
}

Sequence::Sequence(std::vector<int> sequenceIn)
{
	sequence = sequenceIn;
}

void Sequence::playSequence(int msPerBeat)
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
    std::vector<const char*> t = {"kick", "hat", "kick", "hat", "kick", "hat", "kick", "kick"};
    while (true) {
        // Time at current point in loop
        uint64_t currentTime = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()
        ).count();
        // Once the time passed is greater than or equal to the ms per beat
        if (currentTime - startTime >= msPerBeat) {
            std::cout << soundIndex << std::endl;
            // Play the sound and increment the index variable
            engine.PlaySound_(t[soundIndex % sequence.size()]);//sequence[soundIndex % sequence.size()]);
            soundIndex++;
            // Add the ms per beat to the start time
            startTime += msPerBeat;
        }
    }
}

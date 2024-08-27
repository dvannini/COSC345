#pragma once
#ifndef AUDIO_ENGINE_H
#define AUDIO_ENGINE_H

#include <windows.h>
#include <mmsystem.h>
#include <vector>
#include <string>
#include <unordered_map>
/**
 * The backend for for audio related functions.
 */
class Audio_Engine {
public:
    /**
     * Constructor class for audio engine. Initializes the audio device to write to, prepares audio buffers and inits the audio format
     *
     */
    Audio_Engine();
    /**
     * Destructor class frees up audio headers and closes waveout device
     *
     */
    ~Audio_Engine();
    /**
     * Used to load sounds into memory at project init for playback later.
     *
     * \param filename the sound to preload into memory
     * \param id the identification to reference the sound data
     */
    void Preload(const std::string& filename, int id);
    /**
     * Plays a sound with a given ID. Must preload sounds before playing
     *
     * \param id - the ID of the sound to play
     */
    void PlaySound_(int id);
    
     /**
      * Test classes for the audio engine.
      *
      * \return 0 - if successful, 1 - if fail
      */
    static int _test(); 

private:
    static const int NUM_BUFFERS = 8; //8 sound events simulataneously max
    static const int BUFFER_SIZE = 8192; //in bytes

    HWAVEOUT hWaveOut;



    std::vector<WAVEHDR> waveHeaders; 
    int currentBufferIndex;

    struct WaveData {
        WAVEFORMATEX waveFormat;
        std::vector<BYTE> audioData;
    };

    std::unordered_map<int, WaveData> sounds_;
    /**
     * Loads a wave file with a given filename and prepends neccessary headers for the .WAV format.
     *
     * \param filename the file to load
     * \return the wavedata struct (headers and sample data)
     */
    WaveData LoadWave(const std::string& filename);
    /**
     * Takes a queue of sound events and sums their audio together. Writes to waveout device.
     *
     * \param q - the queue of sound events
     * \param sumHeader - a pointer to the WAVEHDR to write the mixed data to
     */
    void mixData(std::vector<WAVEHDR> q, WAVEHDR* sumHeader); //sum simultaneous audio events into one audio stream, if just one sound, just leave unmodified
    /**
     * Collects and sends sound events to be mixed.
     * \param q - The sound event queue.
     */
    void Process_(std::vector<WAVEHDR> q);
};

#endif // AUDIO_ENGINE_H

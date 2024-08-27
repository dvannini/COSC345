/**
 * @file Audio_Engine.h
 * @brief Backend for audio-related functions.
 *
 * This file defines the Audio_Engine class, which manages audio playback,
 * loading sound files into memory, and mixing audio data.
 */

#pragma once
#ifndef AUDIO_ENGINE_H
#define AUDIO_ENGINE_H

#include <windows.h>
#include <mmsystem.h>
#include <vector>
#include <string>
#include <unordered_map>

 /**
  * @brief The backend for audio-related functions.
  *
  * The Audio_Engine class handles initializing the audio device, loading sounds,
  * playing sounds, and mixing audio data for simultaneous playback.
  */
class Audio_Engine {
public:
    /**
     * @brief Constructor for Audio_Engine.
     *
     * Initializes the audio device, prepares audio buffers, and sets up the audio format.
     */
    Audio_Engine();

    /**
     * @brief Destructor for Audio_Engine.
     *
     * Frees up audio headers and closes the wave output device.
     */
    ~Audio_Engine();

    /**
     * @brief Preloads a sound file into memory.
     *
     * This method loads a sound file and associates it with an ID for later playback.
     *
     * @param filename The path to the sound file to load.
     * @param id The identification number used to reference the sound data.
     */
    void Preload(const std::string& filename, int id);

    /**
     * @brief Plays a sound by its ID.
     *
     * The sound must have been preloaded using Preload().
     *
     * @param id The ID of the sound to play.
     */
    void PlaySound_(int id);

    /**
     * @brief Runs tests for the audio engine.
     *
     * This method tests the functionality of the audio engine.
     *
     * @return 0 if successful, 1 if it fails.
     */
    static int _test();

private:
    static const int NUM_BUFFERS = 8; ///< Maximum number of simultaneous sound events.
    static const int BUFFER_SIZE = 8192; ///< Buffer size in bytes.

    HWAVEOUT hWaveOut; ///< Handle to the wave output device.

    std::vector<WAVEHDR> waveHeaders; ///< Vector of wave headers for audio buffers.
    int currentBufferIndex; ///< Index of the current buffer.

    struct WaveData {
        WAVEFORMATEX waveFormat; ///< Audio format information.
        std::vector<BYTE> audioData; ///< Audio data.
    };

    std::unordered_map<int, WaveData> sounds_; ///< Map of sound IDs to their corresponding wave data.

    /**
     * @brief Loads a wave file and prepares necessary headers.
     *
     * This method reads a wave file and prepares it for playback by loading
     * the file's data and setting up the appropriate headers.
     *
     * @param filename The path to the wave file to load.
     * @return The WaveData struct containing the audio format and data.
     */
    WaveData LoadWave(const std::string& filename);

    /**
     * @brief Mixes multiple sound events into one audio stream.
     *
     * This method takes a queue of sound events and sums their audio together
     * before sending it to the wave output device. If there is only one sound,
     * it is left unmodified.
     *
     * @param q The queue of sound events.
     * @param sumHeader A pointer to the WAVEHDR structure to write the mixed data to.
     */
    void mixData(std::vector<WAVEHDR> q, WAVEHDR* sumHeader);

    /**
     * @brief Processes and sends sound events to be mixed.
     *
     * This method collects sound events from the queue and sends them to be mixed.
     *
     * @param q The queue of sound events.
     */
    void Process_(std::vector<WAVEHDR> q);
};

#endif // AUDIO_ENGINE_H


//#pragma once
//#ifndef AUDIO_ENGINE_H
//#define AUDIO_ENGINE_H
//
//#include <windows.h>
//#include <mmsystem.h>
//#include <vector>
//#include <string>
//#include <unordered_map>
///**
// * The backend for for audio related functions.
// */
//class Audio_Engine {
//public:
//    /**
//     * Constructor class for audio engine. Initializes the audio device to write to, prepares audio buffers and inits the audio format
//     *
//     */
//    Audio_Engine();
//    /**
//     * Destructor class frees up audio headers and closes waveout device
//     *
//     */
//    ~Audio_Engine();
//    /**
//     * Used to load sounds into memory at project init for playback later.
//     *
//     * \param filename the sound to preload into memory
//     * \param id the identification to reference the sound data
//     */
//    void Preload(const std::string& filename, int id);
//    /**
//     * Plays a sound with a given ID. Must preload sounds before playing
//     *
//     * \param id - the ID of the sound to play
//     */
//    void PlaySound_(int id);
//    
//     /**
//      * Test classes for the audio engine.
//      *
//      * \return 0 - if successful, 1 - if fail
//      */
//    static int _test(); 
//
//private:
//    static const int NUM_BUFFERS = 8; //8 sound events simulataneously max
//    static const int BUFFER_SIZE = 8192; //in bytes
//
//    HWAVEOUT hWaveOut;
//
//
//
//    std::vector<WAVEHDR> waveHeaders; 
//    int currentBufferIndex;
//
//    struct WaveData {
//        WAVEFORMATEX waveFormat;
//        std::vector<BYTE> audioData;
//    };
//
//    std::unordered_map<int, WaveData> sounds_;
//    /**
//     * Loads a wave file with a given filename and prepends neccessary headers for the .WAV format.
//     *
//     * \param filename the file to load
//     * \return the wavedata struct (headers and sample data)
//     */
//    WaveData LoadWave(const std::string& filename);
//    /**
//     * Takes a queue of sound events and sums their audio together. Writes to waveout device.
//     *
//     * \param q - the queue of sound events
//     * \param sumHeader - a pointer to the WAVEHDR to write the mixed data to
//     */
//    void mixData(std::vector<WAVEHDR> q, WAVEHDR* sumHeader); //sum simultaneous audio events into one audio stream, if just one sound, just leave unmodified
//    /**
//     * Collects and sends sound events to be mixed.
//     * \param q - The sound event queue.
//     */
//    void Process_(std::vector<WAVEHDR> q);
//};
//
//#endif // AUDIO_ENGINE_H

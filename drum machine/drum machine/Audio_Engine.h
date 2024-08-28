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
    void Preload(const std::string& filename, const std::string& id);
    void PlaySound_(std::string id);
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

    std::unordered_map<std::string, WaveData> sounds_;

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
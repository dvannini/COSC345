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
#include <queue>
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
     * Preloads the sound into memory for playback.
     *
     * \param filename - the file path to the sound
     * \param id - an identifier for the sound
     */
    void Preload(const std::string& filename, const std::string& id);
    /**
     * Unloads a sound from memory.
     *
     * \param id - the id to be unloaded
     */
    void Unload(const std::string& id);
    /**
     * Plays a sound.
     *
     * \param id - the sound to play, shoudl be pre-loaded
     */
    void PlaySound_(std::string id);
    /**
     * Test function for audio engine.
     *
     * \return
     */
    static int _test();
    /**
     * tells the audio engine to stop adding sounds to the queue and play them..
     *
     */
    void tick();

private:

    static const int NUM_BUFFERS = 2; ///< Maximum number of simultaneous sound events.
    static const int BUFFER_SIZE = 8192; ///< Buffer size in bytes.
    static constexpr size_t maxBufferSize = 1024 * 1024; //1mb
    HWAVEOUT hWaveOut; ///< Handle to the wave output device.

    std::vector<WAVEHDR> waveHeaders; ///< Vector of wave headers for audio buffers.
    std::queue<WAVEHDR> soundQueue; ///< The queue of sound events for simultaneous playback
    int voiceIndex; ///< Index of the current buffer.
    std::vector<char> mixedBuffer;
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
    static void mixData(HWAVEOUT hwaveout, std::vector<WAVEHDR>& q, WAVEHDR* sumHeader);

    void mixAudio(std::queue<WAVEHDR>& q, WAVEHDR* mixedHeader);
    /**
     * @brief Processes and sends sound events to be mixed.
     *
     * This method collects sound events from the queue and sends them to be mixed.
     *
     * @param q The queue of sound events.
     */
    void Process_(std::queue<WAVEHDR>& q); //vector
    /**
     * Displays any errors when playing audio. for devs.
     *
     * \param error - the error code to interpret
     */
    void printWaveOutError(MMRESULT error);
};

#endif // AUDIO_ENGINE_H
#pragma once
#include "Audio_Engine.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cstring>
#include <assert.h>
#pragma comment(lib, "winmm.lib")

/**
 * Constructor class for audio engine. Initializes the audio device to write to, prepares audio buffers and inits the audio format
 *
 */
Audio_Engine::Audio_Engine() : hWaveOut(nullptr), currentBufferIndex(0) {
    // Initialize waveOut handle
    // Prepare the WAVEHDR structures
    // Open the waveform audio output device
    // Initialize a generic pcm wave format to use for headers
    WaveData wd;
    wd.waveFormat.wFormatTag = WAVE_FORMAT_PCM;
    wd.waveFormat.nChannels = 2;  // stereo sound
    wd.waveFormat.nSamplesPerSec = 44100;  // 44.1 kHz sample rate
    wd.waveFormat.wBitsPerSample = 24;  // 24-bit
    wd.waveFormat.nBlockAlign = wd.waveFormat.nChannels * (wd.waveFormat.wBitsPerSample / 8);
    wd.waveFormat.nAvgBytesPerSec = wd.waveFormat.nSamplesPerSec * wd.waveFormat.nBlockAlign;

    if (waveOutOpen(&hWaveOut, WAVE_MAPPER, &wd.waveFormat, 0, 0, CALLBACK_NULL) != MMSYSERR_NOERROR) {
        throw std::runtime_error("Failed to open waveform output device.");
    }

    for (int i = 0; i < NUM_BUFFERS; i++) {
        WAVEHDR waveHeader = {};
        waveHeader.lpData = nullptr;
        waveHeader.dwBufferLength = BUFFER_SIZE;
        waveHeader.dwFlags = 0;
        waveHeader.dwLoops = 0;

        if (waveOutPrepareHeader(hWaveOut, &waveHeader, sizeof(WAVEHDR)) != MMSYSERR_NOERROR) {
            waveOutClose(hWaveOut);
            throw std::runtime_error("Failed to prepare wave header.");
        }

        waveHeaders.push_back(waveHeader);
    }
}
/**
 * Destructor class frees up audio headers and closes waveout device
 *
 */
Audio_Engine::~Audio_Engine() {

    for (auto& header : waveHeaders) {
        waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
        //delete[] header.lpData; CODE REVIEW SECTION, MAKE SURE DEALLOCATION IS CALM IN TESTS
    }
    if (hWaveOut) {
        waveOutClose(hWaveOut);
    }
}
/**
 * Used to load sounds into memory at project init for playback later.
 *
 * \param filename the sound to preload into memory
 * \param id the identification to reference the sound data
 */
void Audio_Engine::Preload(const std::string& filename, std::string id) {
    sounds_[id] = LoadWave(filename);
    return;
}
void Audio_Engine::PlaySound_(std::string id) {
    if (waveOutReset(hWaveOut) != MMSYSERR_NOERROR) { // stop waveform and reset waveform playhead to beginning
        std::cout << "could not stop playback successfully.";
        throw std::runtime_error("program has carked it");
    }
    auto data = sounds_.find(id);
    if (data == sounds_.end()) {
        throw std::runtime_error("Sound not found in mapping. Make sure to preload before playing a sound");
    }

    WaveData& waveData = data->second;

    WAVEHDR& currentHeader = waveHeaders[currentBufferIndex];
    currentHeader.lpData = reinterpret_cast<LPSTR>(waveData.audioData.data());
    currentHeader.dwBufferLength = static_cast<DWORD>(waveData.audioData.size());



    // Write data to the output device

    if (waveOutWrite(hWaveOut, &currentHeader, sizeof(WAVEHDR)) != MMSYSERR_NOERROR) {

        std::cout << "error has occured";
        throw std::runtime_error("Failed to write to wave output device.");
    }

}
/**
 * Loads a wave file with a given filename and prepends neccessary headers for the .WAV format.
 *
 * \param filename the file to load
 * \return the wavedata struct (headers and sample data)
 */
Audio_Engine::WaveData Audio_Engine::LoadWave(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Failed to open wave file.");
    }

    // Read RIFF header
    char riffHeader[4];
    file.read(riffHeader, 4);
    if (std::strncmp(riffHeader, "RIFF", 4) != 0) {
        throw std::runtime_error("Invalid wave file: missing RIFF header.");
    }

    file.ignore(4); // Skip file size bit

    // Read WAVE header
    char waveHeader[4];
    file.read(waveHeader, 4);
    if (std::strncmp(waveHeader, "WAVE", 4) != 0) {
        throw std::runtime_error("Invalid wave file: missing WAVE header.");
    }

    // Read fmt chunk
    char fmtHeader[4];
    file.read(fmtHeader, 4);
    if (std::strncmp(fmtHeader, "fmt ", 4) != 0) {
        throw std::runtime_error("Invalid wave file: missing fmt header.");
    }

    uint32_t fmtChunkSize;
    file.read(reinterpret_cast<char*>(&fmtChunkSize), 4);

    WaveData waveData;
    file.read(reinterpret_cast<char*>(&waveData.waveFormat), fmtChunkSize);

    // Read data chunk
    char dataHeader[4];
    file.read(dataHeader, 4);
    if (std::strncmp(dataHeader, "data", 4) != 0) {
        throw std::runtime_error("Invalid wave file: missing data header.");
    }

    uint32_t dataChunkSize;
    file.read(reinterpret_cast<char*>(&dataChunkSize), 4);

    waveData.audioData.resize(dataChunkSize);
    file.read(reinterpret_cast<char*>(waveData.audioData.data()), dataChunkSize);

    return waveData;
}
/**
 * Test classes for the audio engine.
 *
 * \return 0 - if successful, 1 - if fail
 */
int Audio_Engine::_test() {
    //test cases in here
    int status = 0;
    try { //constructor all good
        Audio_Engine a;

    }
    catch (std::exception& e) {
        std::cout << "Audio engine constructor failed. Details: " << e.what();
        status += 1;
    }
    try { //headers all good
        Audio_Engine a;
        if (a.waveHeaders.size() == 0) {
            throw std::exception("waveHeaders failed to initialize.");
        }

    }
    catch (std::exception& e) {
        std::cout << "Audio Engine waveHeaders has failed. Details: " << e.what();
        status += 1;
    }
    try { //load invalid waveform
        Audio_Engine a;
        a.LoadWave("this will fail");
        status += 1;
    }
    catch (std::exception& e) {
        std::cout << "Loadwave Failed Succesfully and as expected. ";

    }

    try { //final test to make sure all previous tests have passed

        assert(status == 0); //should be 0 if all tests pass
    }
    catch (std::exception& e) {
        std::cout << "Audio Engine tests have failed.";
        return 1;
    }

    return 0;
}
/**
 * Takes a queue of sound events and sums their audio together.
 *
 * \param q - the queue of sound events
 * \param sumHeader - a pointer to the WAVEHDR to write the mixed data to
 */
void mixData(std::vector<WAVEHDR> q, WAVEHDR* sumHeader) {
    int sampleCount = q.front().dwBufferLength / 3; // 3 bytes per 24-bit sample
    int32_t* mixedData = new int32_t[sampleCount]; // Use 32-bit integers for intermediate storage and more headroom
    int numHeaders = q.size();
    memset(mixedData, 0, sampleCount * sizeof(int32_t));

    for (int i = 0; i < sampleCount; i++) {
        int32_t sum = 0;

        for (int j = 0; j < numHeaders; j++) {
            uint8_t* currentData = (uint8_t*)(q[j].lpData) + i * 3;

            int32_t sample = (int32_t(currentData[2]) << 16) | (int32_t(currentData[1]) << 8) | int32_t(currentData[0]);

            // Sign extension for 24-bit value to 32-bit
            if (sample & 0x800000) {
                sample |= 0xFF000000; // Extend the sign bit
            }

            sum += sample;
        }

        // clips audio data to prevent overflow
        if (sum > 8388607) sum = 8388607;
        if (sum < -8388608) sum = -8388608;

        // Store back as 24-bit value
        mixedData[i] = sum;
    }

    // Convert the mixed 32-bit samples back to 24-bit and store in the mixed header buffer
    uint8_t* mixedBuffer = new uint8_t[sampleCount * 3];
    for (int i = 0; i < sampleCount; i++) {
        mixedBuffer[i * 3] = mixedData[i] & 0xFF;
        mixedBuffer[i * 3 + 1] = (mixedData[i] >> 8) & 0xFF;
        mixedBuffer[i * 3 + 2] = (mixedData[i] >> 16) & 0xFF;
    }

    sumHeader->lpData = (LPSTR)mixedBuffer;
    sumHeader->dwBufferLength = sampleCount * 3;
    sumHeader->dwFlags = 0;

    delete[] mixedData;
    return;
}
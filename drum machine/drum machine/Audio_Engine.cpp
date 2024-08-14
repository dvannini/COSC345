#pragma once
#include "Audio_Engine.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cstring>
#include <assert.h>
//#include <unordered_map> // to store the wave file data in memory
#pragma comment(lib, "winmm.lib")


Audio_Engine::Audio_Engine() : hWaveOut(nullptr), currentBufferIndex(0) {
    // Initialize waveOut handle
    // Prepare the WAVEHDR structures
    // Open the waveform audio output device
    // Initialize a generic pcm wave format to use for headers
    WaveData wd;
    wd.waveFormat.wFormatTag = WAVE_FORMAT_PCM;
    wd.waveFormat.nChannels = 2;  // Example: stereo
    wd.waveFormat.nSamplesPerSec = 44100;  // Example: 44.1 kHz
    wd.waveFormat.wBitsPerSample = 24;  // Example: 24-bit audio
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
        } //move this to playsound to prepare the next header

        waveHeaders.push_back(waveHeader);
    }
}

Audio_Engine::~Audio_Engine() {
    //unprepare all headers
    for (auto& header : waveHeaders) {
        waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
        delete[] header.lpData;
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
    sounds_[id] = LoadWave(filename); //map filename to wave data, referenced by provided id
    return;
}
void Audio_Engine::PlaySound_(std::string id) {
    if (waveOutReset(hWaveOut) != MMSYSERR_NOERROR) { // stop waveform
        std::cout << "could not stop playback successfully.";
        throw std::runtime_error("program has carked it");
    }
    auto data = sounds_.find(id);
    if (data == sounds_.end()) { //end of map
        throw std::runtime_error("Sound not found in mapping. ensure preload is working");
    }

    WaveData& waveData = data->second; //second item in map is the wave data, first is filename

    WAVEHDR& currentHeader = waveHeaders[currentBufferIndex];
    //std::memcpy(currentHeader.lpData, waveData.audioData.data(), waveData.audioData.size()); //dest, src, size
    currentHeader.lpData = reinterpret_cast<LPSTR>(waveData.audioData.data());
    currentHeader.dwBufferLength = static_cast<DWORD>(waveData.audioData.size());
    
    

    // Write data to the output device
    
    if (waveOutWrite(hWaveOut, &currentHeader, sizeof(WAVEHDR)) != MMSYSERR_NOERROR) {
        
        //waveOutUnprepareHeader(hWaveOut, &waveHeader, sizeof(WAVEHDR)); get rid of this eventually
        //waveOutClose(hWaveOut);
        std::cout << "error has occured";
        throw std::runtime_error("Failed to write to wave output device.");
    }
    //std::cout << "buffer index:" << std::to_string(currentBufferIndex);

    // Wait until the sound finishes playing
    //while (!(waveHeader.dwFlags & WHDR_DONE)) {
    //    Sleep(500);//replace with Alex's timekeeping function
    //}

    // Clean up
    /*waveOutUnprepareHeader(hWaveOut, &waveHeader, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
    hWaveOut = nullptr;*/

    //cycle through the 4 buffers for audio playback
    currentBufferIndex = (currentBufferIndex + 1) % NUM_BUFFERS;
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

    file.ignore(4); // Skip file size

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

int Audio_Engine::_test() {
    
    return 0;
}

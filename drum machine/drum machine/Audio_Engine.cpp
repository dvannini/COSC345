#pragma once
#include "Audio_Engine.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cstring>
//#include <unordered_map> // to store the wave file data in memory
#pragma comment(lib, "winmm.lib")


Audio_Engine::Audio_Engine() : hWaveOut(nullptr) {
    // Initialize waveOut handle

}

Audio_Engine::~Audio_Engine() {
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
    auto data = sounds_.find(id);
    if (data == sounds_.end()) { //end of map
        throw std::runtime_error("Sound not found in mapping. ensure preload is working");
    }

    WaveData& waveData = data->second; //second item in map is the wave data, first is filename

    // Open the waveform audio output device
    if (waveOutOpen(&hWaveOut, WAVE_MAPPER, &waveData.waveFormat, 0, 0, CALLBACK_NULL) != MMSYSERR_NOERROR) {
        throw std::runtime_error("Failed to open waveform output device.");
    }

    // Prepare the WAVEHDR structure
    waveHeader.lpData = reinterpret_cast<LPSTR>(waveData.audioData.data());
    waveHeader.dwBufferLength = static_cast<DWORD>(waveData.audioData.size());
    waveHeader.dwFlags = 0;
    waveHeader.dwLoops = 0;

    if (waveOutPrepareHeader(hWaveOut, &waveHeader, sizeof(WAVEHDR)) != MMSYSERR_NOERROR) {
        waveOutClose(hWaveOut);
        throw std::runtime_error("Failed to prepare wave header.");
    }

    // Write data to the output device
    if (waveOutWrite(hWaveOut, &waveHeader, sizeof(WAVEHDR)) != MMSYSERR_NOERROR) {
        waveOutUnprepareHeader(hWaveOut, &waveHeader, sizeof(WAVEHDR));
        waveOutClose(hWaveOut);
        throw std::runtime_error("Failed to write to wave output device.");
    }

    // Wait until the sound finishes playing
    while (!(waveHeader.dwFlags & WHDR_DONE)) {
        Sleep(500);//replace with Alex's timekeeping function
    }

    // Clean up
    waveOutUnprepareHeader(hWaveOut, &waveHeader, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
    hWaveOut = nullptr;
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

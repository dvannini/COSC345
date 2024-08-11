#pragma once
#ifndef AUDIO_ENGINE_H
#define AUDIO_ENGINE_H

#include <windows.h>
#include <mmsystem.h>
#include <vector>
#include <string>
#include <unordered_map>
class Audio_Engine {
public:
    Audio_Engine();
    ~Audio_Engine();
    void Preload(const std::string& filename, std::string id);
    void PlaySound_(std::string id);

private:
    HWAVEOUT hWaveOut;
    WAVEHDR waveHeader;
    struct WaveData {
        WAVEFORMATEX waveFormat;
        std::vector<BYTE> audioData;
    };

    std::unordered_map<std::string, WaveData> sounds_;

    WaveData LoadWave(const std::string& filename);
};

#endif // AUDIO_ENGINE_H

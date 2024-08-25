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
    void Preload(const std::string& filename, int id);
    void PlaySound_(int id);
    int _test();

private:
    static const int NUM_BUFFERS = 8; //8 sound events simulataneously max
    static const int BUFFER_SIZE = 8192; //in bytes

    HWAVEOUT hWaveOut;



    std::vector<WAVEHDR> waveHeaders; //contains multiple sound events
    int currentBufferIndex;

    struct WaveData {
        WAVEFORMATEX waveFormat;
        std::vector<BYTE> audioData;
    };

    std::unordered_map<int, WaveData> sounds_;

    WaveData LoadWave(const std::string& filename);

    void mixData(std::vector<WAVEHDR> q, WAVEHDR* sumHeader); //sum simultaneous audio events into one audio stream, if just one sound, just leave unmodified

    void Process_(std::vector<WAVEHDR> q); //audio events are sent here to then be sent to the wave out device
};

#endif // AUDIO_ENGINE_H

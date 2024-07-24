#include <windows.h>
#include <mmsystem.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

// Link against winmm.lib
#pragma comment(lib, "winmm.lib")

struct WavHeader {
    char riff[4];
    unsigned int overall_size;
    char wave[4];
    char fmt_chunk_marker[4];
    unsigned int length_of_fmt;
    unsigned short format_type;
    unsigned short channels;
    unsigned int sample_rate;
    unsigned int byterate;
    unsigned short block_align;
    unsigned short bits_per_sample;
    char data_chunk_header[4];
    unsigned int data_size;
};

std::vector<short> loadWav(const char* filename, WavHeader& header) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Unable to open file " << filename << std::endl;
        return {};
    }

    file.read(reinterpret_cast<char*>(&header), sizeof(WavHeader));
    std::vector<short> data(header.data_size / sizeof(short));
    file.read(reinterpret_cast<char*>(data.data()), header.data_size);

    return data;
}

std::vector<short> mixBuffers(const std::vector<short>& buffer1, const std::vector<short>& buffer2) {
    size_t minSize = std::min(buffer1.size(), buffer2.size());
    std::vector<short> mixedBuffer(minSize);

    for (size_t i = 0; i < minSize; ++i) {
        int mixedSample = static_cast<int>(buffer1[i]) + static_cast<int>(buffer2[i]);
        mixedBuffer[i] = static_cast<short>(std::clamp(mixedSample, -32768, 32767));
    }

    return mixedBuffer;
}

bool playBuffer(const std::vector<short>& buffer, const WavHeader& header) {
    WAVEFORMATEX wf;
    wf.wFormatTag = WAVE_FORMAT_PCM;
    wf.nChannels = header.channels;
    wf.nSamplesPerSec = header.sample_rate;
    wf.nAvgBytesPerSec = header.byterate;
    wf.nBlockAlign = header.block_align;
    wf.wBitsPerSample = header.bits_per_sample;
    wf.cbSize = 0;

    HWAVEOUT hWaveOut;
    if (waveOutOpen(&hWaveOut, WAVE_MAPPER, &wf, 0, 0, CALLBACK_NULL) != MMSYSERR_NOERROR) {
        std::cerr << "Unable to open wave output device." << std::endl;
        return false;
    }

    WAVEHDR waveHdr;
    waveHdr.lpData = reinterpret_cast<LPSTR>(const_cast<short*>(buffer.data()));
    waveHdr.dwBufferLength = buffer.size() * sizeof(short);
    waveHdr.dwFlags = 0;
    waveHdr.dwLoops = 0;

    if (waveOutPrepareHeader(hWaveOut, &waveHdr, sizeof(WAVEHDR)) != MMSYSERR_NOERROR) {
        std::cerr << "Failed to prepare wave header." << std::endl;
        return false;
    }

    if (waveOutWrite(hWaveOut, &waveHdr, sizeof(WAVEHDR)) != MMSYSERR_NOERROR) {
        std::cerr << "Failed to write audio buffer." << std::endl;
        return false;
    }

    while (!(waveHdr.dwFlags & WHDR_DONE)) {
        Sleep(200);
    }

    waveOutUnprepareHeader(hWaveOut, &waveHdr, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);

    return true;
}

int main() {
    WavHeader header1, header2;
    std::vector<short> buffer1 = loadWav("Hihat Closed 80s UK Disco Vinyl.wav", header1);
    std::vector<short> buffer2 = loadWav("Kick 70s 1.wav", header2);

    if (header1.sample_rate != header2.sample_rate || header1.channels != header2.channels || header1.bits_per_sample != header2.bits_per_sample) {
        std::cerr << "Incompatible WAV files." << std::endl;
        return -1;
    }

    std::vector<short> mixedBuffer = mixBuffers(buffer1, buffer2);

    if (!playBuffer(mixedBuffer, header1)) {
        std::cerr << "Failed to play mixed sound." << std::endl;
        return -1;
    }

    return 0;
}

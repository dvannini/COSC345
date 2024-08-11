#include "Audio_Engine.h"

Audio_Engine::Audio_Engine()
{
}

void Audio_Engine::play(int sound)
{
        switch (sound) {
        case 0:
            break;
        case 1:
            PlaySound(L"../Assets/Kick 70s 1.wav", NULL, SND_FILENAME | SND_ASYNC);
            std::cout << "played kick." << std::endl;
            break;
        case 2:
            PlaySound(L"../Assets/Snare 70s MPC 3.wav", NULL, SND_FILENAME | SND_ASYNC);
            std::cout << "played snare." << std::endl;
            break;
        case 3:
            PlaySound(L"../Assets/Hihat Closed 80s UK Disco Vinyl.wav", NULL, SND_FILENAME | SND_ASYNC);
            std::cout << "played HiHat." << std::endl;
            break;
        case 4:
            PlaySound(L"../Assets/very-fat-808.wav", NULL, SND_FILENAME | SND_ASYNC);
            std::cout << "played 808." << std::endl;
            break;
        }
}

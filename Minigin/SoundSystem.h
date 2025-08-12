#pragma once
#include <string>
#include <mutex>
#include <SDL_mixer.h>

namespace dae {

    class SoundSystem
    {
    public:
        
        virtual ~SoundSystem();
        virtual void PlaySound(const std::string& soundFile, float volume = 1.0f) = 0;
        virtual void StopSound(int soundID) = 0;
        virtual void PauseSound() = 0;

    private:
        class Impl;
        std::unique_ptr<Impl> m_pImpl;
    };
}

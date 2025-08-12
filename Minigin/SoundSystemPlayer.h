#pragma once
#include "SoundSystem.h"

namespace dae
{
	class SoundSystemPlayer : public SoundSystem
	{
	public:
		SoundSystemPlayer() = default;

		void PlaySound(const std::string& soundFile, float volume = 1.0f) override;
		void StopSound(int soundID) override;
		void PauseSound() override;
	private:
		std::mutex m_Mutex;
		Mix_Chunk* m_CurrentSound{ nullptr };
		int m_CurrentSoundID{ -1 };
		bool m_IsPaused{ false };
	};
}


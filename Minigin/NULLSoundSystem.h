#pragma once
#include "SoundSystem.h"

namespace dae
{
	class NULLSoundSystem : public SoundSystem
	{
		public:

		virtual void PlaySound(const std::string& /*soundFile*/, float /*volume = 1.0f*/) {}
		virtual void StopSound(int /*soundID*/) {}
		virtual void PauseSound() {}
	};
}


#pragma once
#include "SoundSystem.h"

namespace dae
{
	class ServiceLocator
	{
	public:
		static SoundSystem* getAudio() { return service_; }

		static void provide(SoundSystem* service)
		{
			service_ = service;
		}

	private:
		static SoundSystem* service_;
	};
};


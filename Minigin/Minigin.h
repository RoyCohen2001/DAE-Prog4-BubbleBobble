#pragma once
#include <string>
#include <functional>

namespace dae
{
	class Minigin
	{
	public:
		static constexpr int Width{ 500 };
		static constexpr int Height{ 480 };

		explicit Minigin(const std::string& dataPath);
		~Minigin();
		void Run(const std::function<void()>& load);

		Minigin(const Minigin& other) = delete;
		Minigin(Minigin&& other) = delete;
		Minigin& operator=(const Minigin& other) = delete;
		Minigin& operator=(Minigin&& other) = delete;

	private:
		float fixed_time_step = 0.016f;
		long ms_per_frame = 16;
	};
}
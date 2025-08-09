#pragma once
#include <map>
#include "Singleton.h"
#include "Gamepad.h"
#include <vector>
#include "Command.h"

namespace dae
{
	enum class InputState
	{
		Pressed,       
		DownThisFrame, 
		UpThisFrame    
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:
		InputManager(const InputManager& other) = delete;
		InputManager(InputManager&& other) = delete;
		InputManager& operator=(const InputManager& other) = delete;
		InputManager& operator=(InputManager&& other) = delete;

		

		bool ProcessInput();

		void ClearBindings();
		void BindCommandToGamepad(int controllerIdx, InputState state, Button button, Command* command);
		void BindCommandToKeyboard(unsigned int key, Command* command);

	private:
		friend class Singleton<InputManager>;

		InputManager();
		~InputManager() = default;

		bool ProcessKeyboardInput();
		void ProcessControllerInput();

		std::vector<std::unique_ptr<Gamepad>> m_pGamepads;
		std::vector<std::map<Button, std::pair<Command*, InputState>>> m_GamepadCommands;

		std::map<unsigned int, Command*> m_KeyboardCommands;

		unsigned int buttonsPressedThisFrame{};
		unsigned int buttonsReleasedThisFrame{};
	};
}

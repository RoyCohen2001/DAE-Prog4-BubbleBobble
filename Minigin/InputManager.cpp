#include <SDL.h>
#include "InputManager.h"

#include <iostream>


namespace dae {

	bool InputManager::ProcessInput()
	{
		ProcessControllerInput();
		
		if (!ProcessKeyboardInput()) {
			return false;
		}
		return true;
	}

	InputManager::InputManager()
	{

		m_pGamepads.emplace_back(std::make_unique<Gamepad>(0)); // Player 1
		m_pGamepads.emplace_back(std::make_unique<Gamepad>(1)); // Player 2

		m_GamepadCommands.resize(2);
	}

	void InputManager::ClearBindings()
	{
		for (auto& gamepadCommands : m_GamepadCommands)
		{
			gamepadCommands.clear();
		}
		if (!m_KeyboardCommands.empty())
		{
			m_KeyboardCommands.clear();
		}
	}

	void InputManager::BindCommandToGamepad(int controllerIdx, InputState state, Button button, Command* command)
	{
		m_GamepadCommands[controllerIdx][button] = std::make_pair(command, state);
	}
	
	void InputManager::BindCommandToKeyboard(unsigned int key, Command* command)
	{
		m_KeyboardCommands[key] = command;
	}
	
	bool InputManager::ProcessKeyboardInput()
	{
		SDL_Event e;
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				return false;
			}
			if (e.type == SDL_KEYDOWN) {
				if (e.key.keysym.sym == SDLK_ESCAPE) {
					return false;
				}
			}
			if (e.type == SDL_MOUSEBUTTONDOWN) {;
			}

			for (const auto& [key, command] : m_KeyboardCommands)
			{
				if (SDL_GetKeyboardState(nullptr)[key] && command)
				{
					command->Execute();
				}
			}
		}

		return true;
	}

	void InputManager::ProcessControllerInput()
	{
		for (size_t i = 0; i < m_pGamepads.size(); ++i)
		{
			m_pGamepads[i]->Update();
			for (const auto& [button, commandPair] : m_GamepadCommands[i])
			{
				Command* command = commandPair.first;
				InputState state = commandPair.second;

				bool execute = false;
				switch (state)
				{
				case InputState::Pressed:
					execute = m_pGamepads[i]->IsPressed(button);
					break;
				case InputState::DownThisFrame:
					execute = m_pGamepads[i]->IsDownThisFrame(button);
					break;
				case InputState::UpThisFrame:
					execute = m_pGamepads[i]->IsUpThisFrame(button);
					break;
				}
				if (execute && command)
					command->Execute();
			}
		}
	}
	
}


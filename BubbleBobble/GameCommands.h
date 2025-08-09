#pragma once
#include "Command.h"
#include "GameActor.h"
#include "SceneManager.h"
#include "MenuManager.h"
#include <iostream>

namespace dae {

	class GameCommands : public Command
	{
		GameActor* m_actor;
	protected:
		GameActor* GetGameActor() const { return m_actor; }
	public:
		GameCommands(GameActor* actor);
		virtual ~GameCommands();
	};

	class Move : public GameCommands
	{
	public:
		Move(GameActor* actor, const glm::vec2& direction) :
			GameCommands(actor),
			m_Direction(direction)
		{
		}

		void Execute() override
		{
			GetGameActor()->Move(m_Direction);
		}
	private:
		glm::vec2 m_Direction;
	};

	class Jump : public GameCommands
	{
	public:
		Jump(GameActor* actor) : GameCommands(actor) {}

		void Execute() override
		{
			GetGameActor()->Jump();
		}
	};

	class Shoot : public GameCommands
	{
	public:
		Shoot(GameActor* actor) : GameCommands(actor) {}

		void Execute() override
		{
			GetGameActor()->Shoot();
		}
	};

	class DropDown : public GameCommands
	{
	public:
		DropDown(GameActor* actor) : GameCommands(actor) {}
	
		void Execute() override
		{
			GetGameActor()->DropDown();
		}
	};

	class Pause : public GameCommands
	{
	public:
		Pause(GameActor* actor) : GameCommands(actor) {}

		void Execute() override
		{
			GetGameActor()->Pause();
		}
	};

	// MENU COMMANDS
	class MenuSelect : public GameCommands
	{
	public:
		MenuSelect(GameActor* actor, MenuManager* menuManager) : GameCommands(actor), m_MenuManager(menuManager) {}
		void Execute() override
		{
			if (m_MenuManager) {
				m_MenuManager->Select();

				std::cout << "Selected index: " << m_MenuManager->GetSelectedIndex() << std::endl;
			}
		}
	private:
		MenuManager* m_MenuManager;
	};

	class MenuMoveUp : public GameCommands
	{
	public:
		MenuMoveUp(GameActor* actor, MenuManager* menuManager) : GameCommands(actor), m_MenuManager(menuManager) {}
		void Execute() override
		{
			if (m_MenuManager) {
				if (m_MenuManager->GetSelectedIndex() <= 3 && m_MenuManager->GetSelectedIndex() > 0)
				{
					m_MenuManager->MoveUp();
					GetGameActor()->SetPosition(
						GetGameActor()->GetPosition().x,
						GetGameActor()->GetPosition().y - 25);
				}

				std::cout << "Selected index: " << m_MenuManager->GetSelectedIndex() << std::endl;
			}
		}
	private:
		MenuManager* m_MenuManager;
	};

	class MenuMoveDown : public GameCommands
	{
	public:
		MenuMoveDown(GameActor* actor, MenuManager* menuManager) : GameCommands(actor), m_MenuManager(menuManager) {}
		void Execute() override
		{
			if (m_MenuManager) {
				if (m_MenuManager->GetSelectedIndex() < 3 && m_MenuManager->GetSelectedIndex() >= 0)
				{
					m_MenuManager->MoveDown();
					GetGameActor()->SetPosition(
						GetGameActor()->GetPosition().x,
						GetGameActor()->GetPosition().y + 25);
				}
				std::cout << "Selected index: " << m_MenuManager->GetSelectedIndex() << std::endl;
			}
		}
	private:
		MenuManager* m_MenuManager;
	};


}

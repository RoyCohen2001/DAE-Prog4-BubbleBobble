#include <SDL.h>

#pragma once
#if _DEBUG
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"

#include "FPSComponent.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "TextComponent.h"
#include "RenderComponent.h"
#include "Scene.h"
#include "TrashTheCache.h"
#include "InputManager.h"
#include "GameCommands.h"
#include "GameActor.h"
#include "Util.h"
#include <iostream>

#include "AnimationComponent.h"
#include "ColliderComponent.h"
#include "LevelLoader.h"

using namespace dae;

static std::vector<std::shared_ptr<dae::GameObject>> g_MenuOptions;


void SetInputMappingController(dae::GameActor* actor, int controller)
{
	// Movement
	dae::InputManager::GetInstance().BindCommandToGamepad(controller, dae::InputState::Pressed, dae::Button::DPAD_LEFT, new dae::Move(actor, glm::vec2{ -1, 0 }));
	dae::InputManager::GetInstance().BindCommandToGamepad(controller, dae::InputState::Pressed, dae::Button::DPAD_RIGHT, new dae::Move(actor, glm::vec2{ 1, 0 }));

	// Jump
	dae::InputManager::GetInstance().BindCommandToGamepad(controller, dae::InputState::DownThisFrame, dae::Button::A, new dae::Jump(actor));
	dae::InputManager::GetInstance().BindCommandToGamepad(controller, dae::InputState::Pressed, dae::Button::DPAD_UP, new dae::Jump(actor));

	// Drop down/fall through platform
	dae::InputManager::GetInstance().BindCommandToGamepad(controller, dae::InputState::DownThisFrame, dae::Button::DPAD_DOWN , new dae::DropDown(actor));

	// Shoot bubble
	dae::InputManager::GetInstance().BindCommandToGamepad(controller, dae::InputState::DownThisFrame, dae::Button::B, new dae::Shoot(actor));

	// Pause/Menu
	dae::InputManager::GetInstance().BindCommandToGamepad(controller, dae::InputState::DownThisFrame, dae::Button::START, new dae::Pause(actor));
}

void SetInputMappingKeyboard(dae::GameActor* actor)
{
	// Movement
	dae::InputManager::GetInstance().BindCommandToKeyboard(SDL_SCANCODE_LEFT, new dae::Move(actor, glm::vec2{ -1, 0 }));
	dae::InputManager::GetInstance().BindCommandToKeyboard(SDL_SCANCODE_RIGHT, new dae::Move(actor, glm::vec2{ 1, 0 }));

	// Jump
	dae::InputManager::GetInstance().BindCommandToKeyboard(SDL_SCANCODE_UP, new dae::Jump(actor));
	dae::InputManager::GetInstance().BindCommandToKeyboard(SDL_SCANCODE_SPACE, new dae::Jump(actor));

	// Drop down/fall through platform
	dae::InputManager::GetInstance().BindCommandToKeyboard(SDL_SCANCODE_DOWN, new dae::DropDown(actor));

	// Shoot bubble
	dae::InputManager::GetInstance().BindCommandToKeyboard(SDL_SCANCODE_Z, new dae::Shoot(actor));

	// Pause/Menu
	dae::InputManager::GetInstance().BindCommandToKeyboard(SDL_SCANCODE_RETURN, new dae::Pause(actor));
}

void AddTextures()
{
	auto avatarTexture = dae::ResourceManager::GetInstance().LoadTexture("Avatar.png");
}

std::vector<std::shared_ptr<dae::GameObject>> SetGameActorsSingle()
{
	std::vector<std::shared_ptr<dae::GameObject>> actors;

	// replace with generic texture loading
	auto bubTexture = dae::ResourceManager::GetInstance().LoadTexture("Avatar.png");

	int widthTex = bubTexture->GetSize().x / 7;
	int heightTex = bubTexture->GetSize().y / 6;

	// Player 1 components
	auto bub = std::make_shared<dae::GameObject>();
	auto* bubActor = bub->AddComponent<dae::GameActor>();
	auto* collider = bub->AddComponent<dae::ColliderComponent>();
	auto* bubAnimationTexture = bub->AddComponent<dae::AnimationComponent>(bubTexture, widthTex, heightTex, 5, 0.15f);
	
	// Setup Player 1
	bubActor->SetPosition(100, 100);
	bubActor->SetSpeed(200.f);
	bubActor->SetSize(glm::vec2(30, 30));

	collider->SetSize(bubActor->GetSize());
	bubAnimationTexture->SetSize(bubActor->GetSize());

	actors.push_back(bub);

	// Set input mapping for Player 1
	SetInputMappingController(bubActor, 0);
	SetInputMappingKeyboard(bubActor);

	return actors;
}

std::vector<std::shared_ptr<dae::GameObject>> SetGameActorsCoop()
{
	std::vector<std::shared_ptr<dae::GameObject>> actors;

	// Player 1
	actors = SetGameActorsSingle();

	// *********************************************************

	// Player 2
	//auto Bomberman2 = std::make_shared<dae::GameObject>();
	//auto Bomberman2Texture = dae::ResourceManager::GetInstance().LoadTexture("Sprites/Bomberman2_NoAnim.png");
	//Bomberman2->AddComponent<dae::RenderComponent>(Bomberman2Texture);
	//Bomberman2->AddComponent<dae::GameActor>();
	//Bomberman2->GetComponent<dae::RenderComponent>()->SetSize(30, 40);
	//
	//auto* bombermanActor2 = Bomberman2->GetComponent<dae::GameActor>();
	//bombermanActor2->SetPosition(200, 100);
	//bombermanActor2->SetSpeed(200.f);
	//
	//actors.push_back(Bomberman2);
	//
	//
	//// Set input mapping for Player 2
	//SetInputMappingController(bombermanActor2, 1);

	return actors;
}

void LoadVersus()
{
	//auto& scene = dae::SceneManager::GetInstance().CreateScene("Versus");

	//auto actors = {};
	//for (auto actor : actors)
	//{
	//	scene.Add(actor);
	//}
}

void LoadCoop()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Coop");

	auto actors = SetGameActorsCoop();
	for (auto actor : actors)
	{
		scene.Add(actor);
	}
}

void LoadHighScoreMenu()
{
	//auto& scene = dae::SceneManager::GetInstance().CreateScene("HighScoreMenu");
}

void LoadGame()
{
	//InputManager::GetInstance().ClearBindings();

	auto& scene = dae::SceneManager::GetInstance().CreateScene("Game");

	LevelLoader::LoadLevel("../Data/Level1.txt", scene, 0);

	auto actors = SetGameActorsSingle();

	for (auto actor : actors)
	{
		scene.Add(actor);
	}
}

void LoadMainMenu()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("MainMenu");

	auto background = std::make_shared<dae::GameObject>();
	auto backgroundTexture = dae::ResourceManager::GetInstance().LoadTexture("BubbleBobbleLogo.png");
	background->AddComponent<dae::RenderComponent>(backgroundTexture);
	background->SetPosition(0, 0);
	background->GetComponent<dae::RenderComponent>()->SetSize(WIDTH, HEIGHT / 1.5);

	scene.Add(background);

	auto font = dae::ResourceManager::GetInstance().LoadFont("Retro.otf", 15);

	g_MenuOptions.clear();

	auto option1 = std::make_shared<dae::GameObject>();
	std::string option1Text = "SINGLE PLAYER";
	option1->AddComponent<dae::TextComponent>(option1Text, font);
	option1->GetComponent<dae::TextComponent>()->Update(0.f);

	float placement = static_cast<float>(option1->GetComponent<dae::TextComponent>()->GetTexture()->GetSize().x);
	option1->SetPosition(
		static_cast<float>(WIDTH) / 2.f - placement / 2.f
		, static_cast<float>(HEIGHT) / 2.f + 80);

	scene.Add(option1);
	g_MenuOptions.push_back(option1);

	auto option2 = std::make_shared<dae::GameObject>();
	std::string option2Text = "COOP";
	option2->AddComponent<dae::TextComponent>(option2Text, font);
	option2->GetComponent<dae::TextComponent>()->Update(0.f);
	option2->SetPosition(static_cast<float>(WIDTH) / 2.f - static_cast<float>(option2->GetComponent<dae::TextComponent>()->GetTexture()->GetSize().x) / 2.f
		, static_cast<float>(HEIGHT) / 2.f + 105);
	scene.Add(option2);
	g_MenuOptions.push_back(option2);


	auto option3 = std::make_shared<dae::GameObject>();
	std::string option3Text = "VERSUS";
	option3->AddComponent<dae::TextComponent>(option3Text, font);
	option3->GetComponent<dae::TextComponent>()->Update(0.f);
	option3->SetPosition(static_cast<float>(WIDTH) / 2.f - static_cast<float>(option3->GetComponent<dae::TextComponent>()->GetTexture()->GetSize().x) / 2.f
		, static_cast<float>(HEIGHT) / 2.f + 130);
	scene.Add(option3);
	g_MenuOptions.push_back(option3);

	auto option4 = std::make_shared<dae::GameObject>();
	std::string option4Text = "HIGHSCORES";
	option4->AddComponent<dae::TextComponent>(option4Text, font);
	option4->GetComponent<dae::TextComponent>()->Update(0.f);
	option4->SetPosition(static_cast<float>(WIDTH) / 2.f - static_cast<float>(option4->GetComponent<dae::TextComponent>()->GetTexture()->GetSize().x) / 2.f
		, static_cast<float>(HEIGHT) / 2.f + 155);
	scene.Add(option4);
	g_MenuOptions.push_back(option4);

	auto footer = std::make_shared<dae::GameObject>();
	std::string footerText = "GAME REMADE BY ROY COHEN";
	footer->AddComponent<dae::TextComponent>(footerText, font);
	footer->GetComponent<dae::TextComponent>()->Update(0.f);
	footer->SetPosition(static_cast<float>(WIDTH) / 2.f - static_cast<float>(footer->GetComponent<dae::TextComponent>()->GetTexture()->GetSize().x) / 2.f
		, static_cast<float>(HEIGHT) - 40);
	scene.Add(footer);


	// Select pointer
	auto select = std::make_shared<dae::GameObject>();
	auto pointerTexture = dae::ResourceManager::GetInstance().LoadTexture("MenuPointer.png");
	select->AddComponent<dae::RenderComponent>(pointerTexture);
	select->AddComponent<dae::GameActor>();
	select->GetComponent<dae::RenderComponent>()->SetSize(15, 15);
	
	auto* selectActor = select->GetComponent<dae::GameActor>();
	selectActor->SetGravityOff();
	selectActor->SetPosition(100,
		static_cast<float>(HEIGHT) / 2.f + 80);
	
	scene.Add(select);
	
	static dae::MenuManager menuManager;
	menuManager.SetOptions(g_MenuOptions);
	
	menuManager.SetActions({
	   [] { LoadGame(); dae::SceneManager::GetInstance().SetActiveScene("Game"); }, // SINGLE PLAYER
	   [] { LoadCoop();  dae::SceneManager::GetInstance().SetActiveScene("Coop"); }, // COOP
	   [] { LoadVersus();  dae::SceneManager::GetInstance().SetActiveScene("Versus"); }, // VERSUS
	   [] { LoadHighScoreMenu();  dae::SceneManager::GetInstance().SetActiveScene("HighScores"); } // HIGHSCORES
		});
	
	dae::InputManager::GetInstance().BindCommandToGamepad(0, dae::InputState::DownThisFrame, dae::Button::DPAD_DOWN, new dae::MenuMoveDown(selectActor, &menuManager));
	dae::InputManager::GetInstance().BindCommandToGamepad(0, dae::InputState::DownThisFrame, dae::Button::DPAD_UP, new dae::MenuMoveUp(selectActor, &menuManager));
	dae::InputManager::GetInstance().BindCommandToGamepad(0, dae::InputState::DownThisFrame, dae::Button::A, new dae::MenuSelect(selectActor, &menuManager));

	dae::InputManager::GetInstance().BindCommandToKeyboard(SDL_SCANCODE_DOWN, new dae::MenuMoveDown(selectActor, &menuManager));
	dae::InputManager::GetInstance().BindCommandToKeyboard(SDL_SCANCODE_UP, new dae::MenuMoveUp(selectActor, &menuManager));
	dae::InputManager::GetInstance().BindCommandToKeyboard(SDL_SCANCODE_RETURN, new dae::MenuSelect(selectActor, &menuManager));

}

void load()
{
	LoadMainMenu();
	//LoadGame();

	auto& sceneManager = SceneManager::GetInstance();
	sceneManager.SetActiveScene("MainMenu");
}

int main(int, char* []) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}
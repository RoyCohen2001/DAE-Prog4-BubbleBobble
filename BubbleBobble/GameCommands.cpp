#include "GameCommands.h"

using namespace dae;

GameCommands::GameCommands(GameActor* actor) :
	m_actor(actor)
{
}

GameCommands::~GameCommands()
{
	delete m_actor;
	m_actor = nullptr;
}


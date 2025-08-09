#pragma once
#include "Minigin.h"

constexpr float WIDTH = dae::Minigin::Width;
constexpr float HEIGHT = dae::Minigin::Height;

// Player-related events
enum class PlayerEvent
{
    DIE,
    JUMP,
    SHOOT,
    EAT,
    TAKE_DAMAGE,
    RESPAWN,
    SCORE_CHANGED,
    BUBBLED,         
    COLLECT_POWERUP  
};

// Enemy-related events
enum class EnemyEvent
{
    DIE,
    TAKE_DAMAGE,
    RESPAWN,
    BUBBLED,         
    POPPED           
};

// Bubble-related events
enum class BubbleEvent
{
    SPAWNED,
    POPPED,
    TRAP_ENEMY,      
    TRAP_PLAYER      
};

// Power-up and item events
enum class PowerupEvent
{
    SPAWNED,
    COLLECTED,
    EXPIRED
};

// Game flow events
enum class GameFlowEvent
{
    EXIT,
    WIN,
    RESTART,
    LOST,
    CONTINUE,
    LEVEL_START,
    LEVEL_COMPLETE,
    TIME_UP,
    BONUS_STAGE
};

// Game mode events
enum class GameModeEvent
{
    SINGLE,
    COOP,
    PVP,
    HIGHSCORES
};

// Menu and navigation events
enum class MenuEvent
{
    BACK,
    UP,
    DOWN,
    SELECT,
    NAVIGATE
};
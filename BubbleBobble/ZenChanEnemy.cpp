#include "ZenChanEnemy.h"

using namespace dae;

ZenChanEnemy::ZenChanEnemy(GameObject* owner)
    : EnemyActor(owner)
    , m_Rng(std::random_device{}())
{
}

void ZenChanEnemy::Update(float deltaTime)
{
    EnemyActor::Update(deltaTime);

    if (!IsBubbled())
    {
        m_TimeSinceLastJump += deltaTime;
        if (m_TimeSinceLastJump >= m_JumpCooldown)
        {
            JumpRandomly();
            m_TimeSinceLastJump = 0.0f;
        }
    }
}

void ZenChanEnemy::JumpRandomly()
{
}

void ZenChanEnemy::SetJumpCooldown(float cooldown)
{
    m_JumpCooldown = cooldown;
}

void ZenChanEnemy::SetEnraged()
{
    m_IsEnraged = true;
}

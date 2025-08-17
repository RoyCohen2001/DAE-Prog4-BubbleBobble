#pragma once
#include "EnemyActor.h"
#include <random>

namespace dae {

    class ZenChanEnemy : public EnemyActor
    {
    public:
        ZenChanEnemy(GameObject* owner);

        void Update(float deltaTime) override;
        void JumpRandomly();
        void SetJumpCooldown(float cooldown);
        void SetEnraged();

    private:
        float m_JumpCooldown{ 1.5f };
        float m_TimeSinceLastJump{ 0.0f };
        bool m_IsEnraged{ false };

        // For random jump direction
        std::mt19937 m_Rng;
        std::uniform_real_distribution<float> m_DirDist{ -1.0f, 1.0f };
    };

}

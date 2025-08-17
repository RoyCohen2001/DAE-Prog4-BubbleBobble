#pragma once
#include "EnemyActor.h"

namespace dae {

    class MaitaEnemy : public EnemyActor
    {
    public:
        MaitaEnemy(GameObject* owner);

        void Update(float deltaTime) override;
        void OnNotify(Event event, GameObject* gameObject) override;

        void ThrowRock();
        void SetRockThrowCooldown(float cooldown);

    private:
        float m_RockThrowCooldown{ 2.0f };
        float m_TimeSinceLastThrow{ 0.0f };
    };

}

#pragma once
#include "GameActor.h"

namespace dae {

    class EnemyActor : public GameActor
    {
    public:
        EnemyActor(GameObject* owner);

        void Update(float deltaTime) override;
        void OnNotify(Event event, GameObject* gameObject) override;

        void SetPatrolArea(float left, float right);
        void TakeDamage(int amount);
    private:
        bool m_IsInBubble{};
		bool ApplyGravity{ true };
		glm::vec2 m_Direction{ 0.0f, 0.0f };

        float m_PatrolLeft{ 0.0f };
        float m_PatrolRight{ 0.0f };
        int m_Health{ 1 };
        float m_PatrolSpeed{ 50.0f };
    };

}


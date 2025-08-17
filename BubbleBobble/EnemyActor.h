#pragma once
#include "AnimationComponent.h"
#include "GameActor.h"

namespace dae {

    class EnemyActor : public GameActor
    {
    public:
        EnemyActor(GameObject* owner);

        void Update(float deltaTime) override;
        void OnNotify(Event event, GameObject* gameObject) override;

        void SetPatrolArea(float left, float right);

        // Bubble mechanics
        void Bubble();     
        void PopBubble();   

        bool IsBubbled() const { return m_IsInBubble; }


        void OnCollision(GameObject* other) override;

    private:
        bool m_IsInBubble{ false };
        float m_BubbleTimer{ 0.0f };
        static constexpr float m_BubbleDuration{ 10.0f };
        float m_BubbleRiseSpeed{ 10.f };

        glm::vec2 m_Direction{ 0.0f, 0.0f };

        float m_PatrolLeft{ 0.0f };
        float m_PatrolRight{ 0.0f };
        float m_PatrolSpeed{ 50.0f };

        void Respawn();

        AnimationComponent* animComp = GetOwner()->GetComponent<AnimationComponent>();
    };

}
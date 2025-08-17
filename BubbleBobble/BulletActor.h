#pragma once
#include "GameActor.h"

namespace dae {
    class BulletActor : public GameActor
    {
    public:
        BulletActor(GameObject* owner, const glm::vec2& direction, float speed);

        void Update(float deltaTime) override;
		void Render() const override {}
        
        void OnCollision(GameObject* other) override;


        void Activate(const glm::vec2& position, const glm::vec2& direction, float speed);
        void Deactivate();
        bool IsActive() const { return m_Active; }

    private:
        glm::vec2 m_Direction;
        float m_Speed;

        const float m_MaxDistance{ 20.f };
        float m_Travelled{ 0.0f };
        bool m_Active{ false };

        void TransformToBalloon();
    };
}


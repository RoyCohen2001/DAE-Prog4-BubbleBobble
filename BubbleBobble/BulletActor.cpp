#include "BulletActor.h"
#include "BalloonActor.h"
#include "GameObject.h"


namespace dae {
    BulletActor::BulletActor(GameObject* owner, const glm::vec2& direction, float speed)
        : GameActor(owner), m_Direction(direction), m_Speed(speed)
    {
    }

    void BulletActor::Update(float deltaTime)
    {
        if (m_Active) {
            float distance = m_Speed * deltaTime;
            m_Travelled += distance;
            Move(m_Direction * distance);

            if (m_Travelled >= m_MaxDistance)
            {
                TransformToBalloon();
                SetDelete();
            }
        }
    }

    void BulletActor::Activate(const glm::vec2& /*position*/, const glm::vec2& direction, float speed)
    {
//        SetPosition(position.x, position.y);
        m_Direction = direction;
        m_Speed = speed;
        m_Travelled = 0.0f;
        m_Active = true;
    }

    void BulletActor::Deactivate()
    {
        m_Active = false;
    }

    void BulletActor::OnCollision(GameObject* other)
    {
        if (other->GetTag() == ObjectType::Wall)
        {
            TransformToBalloon();
            Deactivate();
        }

        if (other->GetTag() == ObjectType::Enemy)
        {
            Deactivate();
        }
    }

    void BulletActor::TransformToBalloon()
    {
       // auto* balloonObj = new GameObject();
       // glm::vec3 pos = GetPosition();
       // balloonObj->SetPosition(pos.x, pos.y);
       // balloonObj->AddComponent<BalloonActor>(balloonObj);
        // Add balloonObj to the scene
    }
}

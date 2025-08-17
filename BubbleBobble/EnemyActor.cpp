#include "EnemyActor.h"
#include <iostream>

namespace dae {

    EnemyActor::EnemyActor(GameObject* owner)
        : GameActor(owner)
    {
    }

    void EnemyActor::Update(float deltaTime)
    {
        if (m_IsInBubble)
        {
            m_BubbleTimer += deltaTime;


            glm::vec3 pos = GetPosition();
            float newY = pos.y - m_BubbleRiseSpeed * deltaTime;
            newY = std::max(newY, 20.f);

            SetPosition(pos.x, newY);

            if (m_BubbleTimer >= m_BubbleDuration)
            {
                Respawn();
            }
            return;
        }

        glm::vec3 pos = GetPosition();
        float newX = pos.x + m_Direction.x * m_PatrolSpeed * deltaTime;

        if (newX < m_PatrolLeft) {
            newX = m_PatrolLeft;
            m_Direction.x = 1;
        }
        else if (newX > m_PatrolRight) {
            newX = m_PatrolRight;
            m_Direction.x = -1;
        }

        Move(glm::vec2(m_Direction));
        GameActor::Update(deltaTime);
    }

    void EnemyActor::OnNotify(Event /*event*/, GameObject* /*gameObject*/)
    {
        //if (event == static_cast<Event>(PlayerEvent::SHOOT)) {
        //    Bubble();
        //}
        // Add collision event for player here later
    }

    void EnemyActor::SetPatrolArea(float left, float right)
    {
        m_PatrolLeft = left;
        m_PatrolRight = right;
    }

    void EnemyActor::Bubble()
    {
        if (!m_IsInBubble)
        {
            m_IsInBubble = true;
            m_BubbleTimer = 0.0f;


        }
    }

    void EnemyActor::PopBubble()
    {
        if (m_IsInBubble)
        {
            m_IsInBubble = false;
            m_BubbleTimer = 0.0f;
            // Handle enemy death 
        }
    }

    void EnemyActor::OnCollision(GameObject* other)
    {
        if (other->GetTag() == ObjectType::Player)
        {
	        std::cout << "Enemy collided with player!\n";
        } 
    }

    void EnemyActor::Respawn()
    {
        m_IsInBubble = false;
        m_BubbleTimer = 0.0f;
    }

}

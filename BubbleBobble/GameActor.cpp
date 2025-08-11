#include "GameActor.h"
#include "ResourceManager.h"
#include <iostream>
#include "LevelLoader.h"
#include "ColliderComponent.h"
#include "Collision.h"
#include "RenderComponent.h"

using namespace dae;

GameActor::GameActor(GameObject* owner) :
    Component(owner),
    m_Transform{}
{

}

void dae::GameActor::OnNotify(Event event, GameObject* gameObject)
{

    Notify(event, gameObject);
}

void GameActor::Update(float deltaTime)
{
    glm::vec3 pos = GetPosition();
    float newX = pos.x;
    float newY = pos.y;

    // --- Horizontal movement ---
    if (m_MoveDirection.x != 0.0f) {
        float intendedX = pos.x + m_MoveDirection.x * m_Speed * deltaTime;
        bool blocked = false;
        const auto& solidBlocks = dae::LevelLoader::GetSolidBlocks();
        for (const auto& block : solidBlocks) {
            auto* collider = block->GetComponent<ColliderComponent>();
            if (!collider) continue;
            glm::vec3 blockPos3 = block->GetTransform().GetPosition();
            glm::vec2 blockPos(blockPos3.x, blockPos3.y);

            glm::vec2 playerPos(intendedX, pos.y); // Only X changes
            if (dae::Collision::CheckColliding(playerPos, m_Size, blockPos, collider->GetSize())) {
                blocked = true;
                break;
            }
        }
        if (!blocked) newX = intendedX;
    }

    // --- Gravity and vertical movement ---
    if (ApplyGravity) {
        m_VelocityY += m_Gravity * deltaTime;
    }
    float intendedY = newY + m_VelocityY * deltaTime;

    bool landed = false;
    bool hitCeiling = false;
    const auto& solidBlocks = dae::LevelLoader::GetSolidBlocks();
    for (const auto& block : solidBlocks) {
        auto* collider = block->GetComponent<ColliderComponent>();
        if (!collider) continue;
        glm::vec3 blockPos3 = block->GetTransform().GetPosition();
        glm::vec2 blockPos(blockPos3.x, blockPos3.y);

        glm::vec2 playerPos(newX, intendedY); // Use updated X
        if (dae::Collision::CheckColliding(playerPos, m_Size, blockPos, collider->GetSize())) {
            if (m_VelocityY > 0) {
                // Falling: landed on block
                intendedY = blockPos.y - m_Size.y;
                m_VelocityY = 0.0f;
                m_IsGrounded = true;
                landed = true;
            }
            else if (m_VelocityY < 0) {
                // Jumping: hit the bottom of a block (ceiling)
                intendedY = blockPos.y + collider->GetSize().y;
                m_VelocityY = 0.0f;
                hitCeiling = true;
            }
            break;
        }
    }
    if (!landed) m_IsGrounded = false;

    SetPosition(newX, intendedY);
    m_MoveDirection = { 0.0f, 0.0f };
}

void GameActor::SetSpeed(float speed)
{
    m_Speed = speed;
}

void GameActor::SetPosition(float x, float y)
{
    GetOwner()->SetPosition(x, y);
}

glm::vec3 dae::GameActor::GetPosition() const
{
    return GetOwner()->GetTransform().GetPosition();
}

void GameActor::Move(const glm::vec2& direction)
{
    m_MoveDirection = direction;
    if (direction.x > 0) m_FacingLeft = true;
    else if (direction.x < 0) m_FacingLeft = false;

}

void GameActor::Shoot()
{
    if (m_IsShooting) return;
    m_IsShooting = true;
    m_TimeSinceLastShot = 0.0f;
    // Implement shooting logic here
    std::cout << "Shooting\n";
}

void GameActor::Jump()
{
    if (!m_IsGrounded) return;
    m_VelocityY = m_JumpSpeed;
    m_IsGrounded = false;
    m_IsJumping = true;
    m_TimeSinceJump = 0.0f;
    std::cout << "Jumping\n";
}

void GameActor::Pause()
{
    // Implement pause logic here
    std::cout << "Pausing\n";
}

void GameActor::DropDown()
{
    // Implement drop down logic here
    std::cout << "Dropping down\n";
}

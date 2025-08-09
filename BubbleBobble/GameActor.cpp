#include "GameActor.h"
#include "ResourceManager.h"
#include <iostream>

#include "RenderComponent.h"

using namespace dae;

GameActor::GameActor(GameObject* owner, const std::string& path) :
    Component(owner),
    m_Transform{},
    m_Texture{ ResourceManager::GetInstance().LoadTexture(path) }
{

}

void dae::GameActor::OnNotify(Event event, GameObject* gameObject)
{

    Notify(event, gameObject);
}

void GameActor::Update(float deltaTime)
{
    if (m_MoveDirection != glm::vec2{ 0.0f, 0.0f })
    {
        auto pos = GetOwner()->GetTransform().GetPosition();
        SetPosition(pos.x + m_MoveDirection.x * m_Speed * deltaTime, pos.y + m_MoveDirection.y * m_Speed * deltaTime);
        m_MoveDirection = glm::vec2{ 0.0f, 0.0f };
    }


}

void GameActor::Render() const
{
    if (!m_Texture) return;

    auto renderComponent = dae::RenderComponent(GetOwner(), m_Texture);
    renderComponent.Render();
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

    std::cout << "Moving\n";
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
    if (m_IsJumping) return;
    m_IsJumping = true;
    m_TimeSinceJump = 0.0f;
    // Implement jumping logic here
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

#include "ColliderComponent.h"

using namespace dae;

dae::ColliderComponent::ColliderComponent(dae::GameObject* owner) :
	Component(owner),
	m_Size(1.0f, 1.0f)
{
}

const glm::vec2& dae::ColliderComponent::GetSize() const
{
	return m_Size;
}

void dae::ColliderComponent::SetSize(float width, float height)
{
	m_Size = glm::vec2(width, height);
}

void dae::ColliderComponent::SetSize(glm::vec2 size)
{
	m_Size = size;
}
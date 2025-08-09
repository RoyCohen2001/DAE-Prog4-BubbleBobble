#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

dae::GameObject::~GameObject() = default;

void dae::GameObject::FixedUpdate(float /*fixedTimeStep*/) {}

void dae::GameObject::Update(float deltaTime)
{
    for (const auto& component : m_Components)
    {
        component->Update(deltaTime);
    }
}

void dae::GameObject::Render() const
{
    for (const auto& component : m_Components)
    {
        component->Render();
    }
}

void dae::GameObject::SetPosition(float x, float y)
{
    m_Transform.SetPosition(x, y, 0.0f);
}

void dae::GameObject::SetParent(GameObject* parent, bool keepWorldPosition)
{
    if (IsChild(parent) || parent == this || m_Parent == parent)
        return;

    if (parent == nullptr)
    {
        SetLocalPosition(GetWorldPosition());
    }
    else
    {
        if (keepWorldPosition)
        {
            SetLocalPosition(GetWorldPosition() - parent->GetWorldPosition());
        }
        SetPositionDirty();
    }

    if (m_Parent)
    {
        m_Parent->RemoveChild(this);
    }

    m_Parent = parent;

    if (m_Parent)
    {
        m_Parent->AddChild(this);
    }
}

void dae::GameObject::SetLocalPosition(const glm::vec3& pos)
{
    m_Transform.SetPosition(pos.x, pos.y, pos.z);
    SetPositionDirty();
}

dae::GameObject* dae::GameObject::GetParent() const
{
    return m_Parent;
}

size_t dae::GameObject::ChildCount() const
{
    return m_Children.size();
}

dae::GameObject* dae::GameObject::GetChildAt(unsigned int index) const
{
    if (index < m_Children.size())
    {
        return m_Children[index];
    }
    return nullptr;
}

void dae::GameObject::RemoveChild(GameObject* child)
{
    m_Children.erase(std::remove(m_Children.begin(), m_Children.end(), child), m_Children.end());
}

void dae::GameObject::AddChild(GameObject* child)
{
    m_Children.push_back(child);
}

void dae::GameObject::SetPositionDirty()
{
	for (auto child : m_Children)
	{
		child->SetPositionDirty();
	}
}

bool dae::GameObject::IsChild(GameObject* child) const
{
	for (auto c : m_Children)
	{
		if (c == child)
			return true;
	}
	return false;
}

glm::vec3 dae::GameObject::GetWorldPosition() const
{
    if (m_Parent)
    {
        return m_Parent->GetWorldPosition() + m_Transform.GetPosition();
    }
    return m_Transform.GetPosition();
}

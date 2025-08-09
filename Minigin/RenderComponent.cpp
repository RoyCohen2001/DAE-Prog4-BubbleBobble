#include "RenderComponent.h"
#include "Renderer.h"

dae::RenderComponent::RenderComponent(GameObject* owner,const std::shared_ptr<Texture2D>& texture)
	: Component(owner),
	m_Texture{ texture }
{
}

void dae::RenderComponent::Render() const
{
	if (m_Texture)
	{
		auto owner = GetOwner();
		if (owner)
		{
			const auto& pos = GetOwner()->GetTransform().GetPosition();
			Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y, m_Width, m_Height);
		}
	}
}

void dae::RenderComponent::SetTexture(std::shared_ptr<Texture2D> texture)
{
	m_Texture = texture;

	if (m_Texture)
	{
		auto size = m_Texture->GetSize();
		m_Width = static_cast<float>(size.x);
		m_Height = static_cast<float>(size.y);
	}
}

void dae::RenderComponent::SetSize(float width, float height)
{
	m_Width = width;
	m_Height = height;
}

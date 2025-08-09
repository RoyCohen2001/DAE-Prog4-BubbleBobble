#include "RenderComponent.h"
#include "Renderer.h"

dae::RenderComponent::RenderComponent(GameObject* owner,const std::shared_ptr<Texture2D>& texture)
	: Component(owner),
	m_Texture{ texture }
{
	if (m_Texture)
	{
		auto size = m_Texture->GetSize();
		m_Width = static_cast<float>(size.x);
		m_Height = static_cast<float>(size.y);

		// Set default src rect to full texture
		m_SrcRect = { 0, 0, size.x, size.y };
	}
}

void dae::RenderComponent::Render() const
{
	if (!m_Texture) return;

	SDL_Rect dstRect;
	dstRect.x = static_cast<int>(GetOwner()->GetTransform().GetPosition().x);
	dstRect.y = static_cast<int>(GetOwner()->GetTransform().GetPosition().y);
	dstRect.w = static_cast<int>(m_Width);
	dstRect.h = static_cast<int>(m_Height);

	SDL_RenderCopy(
		Renderer::GetInstance().GetSDLRenderer(),
		m_Texture->GetSDLTexture(),
		&m_SrcRect,
		&dstRect
	);
}

void dae::RenderComponent::SetTexture(std::shared_ptr<Texture2D> texture)
{
	m_Texture = texture;

	if (m_Texture)
	{
		auto size = m_Texture->GetSize();
		m_Width = static_cast<float>(size.x);
		m_Height = static_cast<float>(size.y);

		// If m_SrcRect is not set (w or h is 0), set it to the full texture
		if (m_SrcRect.w == 0 || m_SrcRect.h == 0) {
			m_SrcRect = { 0, 0, size.x, size.y };
		}
	}
}

void dae::RenderComponent::SetSize(float width, float height)
{
	m_Width = width;
	m_Height = height;
}

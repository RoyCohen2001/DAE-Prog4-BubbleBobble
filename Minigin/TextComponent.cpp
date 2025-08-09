#include <stdexcept>
#include <SDL_ttf.h>
#include "TextComponent.h"
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"

dae::TextComponent::TextComponent(GameObject* owner,const std::string& text, std::shared_ptr<Font> font)
	: Component(owner),
	m_needsUpdate(true), 
	m_text(text), 
	m_font(std::move(font)),
	m_texture(nullptr)
{ 
}

void dae::TextComponent::Update(float /*deltaTime*/)
{	
	if (m_needsUpdate)
	{
		constexpr SDL_Color color = { 255, 255, 255, 255 };
		const auto surf = TTF_RenderText_Blended(m_font->GetFont(), m_text.c_str(), color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			SDL_FreeSurface(surf);
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}

		m_texture = std::make_shared<Texture2D>(texture);
		SDL_FreeSurface(surf);

		m_needsUpdate = false;
	}
}

void dae::TextComponent::Render() const
{
	if (m_texture)
	{
		const auto& pos = GetOwner()->GetTransform().GetPosition();
		Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y);
	}
}

void dae::TextComponent::SetText(const std::string& text)
{
	m_text = text;
	m_needsUpdate = true;
}

void dae::TextComponent::SetSize(const unsigned int size)
{
	m_font = m_font->WithSize(size);
	m_needsUpdate = true;
}

std::shared_ptr<dae::Texture2D> dae::TextComponent::GetTexture() const
{
	return m_texture;
}



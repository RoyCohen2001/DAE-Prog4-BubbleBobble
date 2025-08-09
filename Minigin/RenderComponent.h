#pragma once
#include <SDL_rect.h>

#include "GameObject.h"
#include "Texture2D.h"

namespace dae
{
	class RenderComponent final : public Component
	{
	public:
		RenderComponent(GameObject* owner,const std::shared_ptr<Texture2D>& texture);
		void Update(float /*deltaTime*/) override {}
		void Render() const override;
		void SetTexture(std::shared_ptr<Texture2D> texture);

		void SetSize(float width, float  height);

		void SetSourceRect(const SDL_Rect& rect) { m_SrcRect = rect; }
		const SDL_Rect& GetSourceRect() const { return m_SrcRect; }


	private:
		std::shared_ptr<Texture2D> m_Texture;
		float m_Width{  0 };
		float m_Height{ 0 };

		SDL_Rect m_SrcRect{ 0, 0, 0, 0 };

	};
}


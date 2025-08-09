#pragma once
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

	private:
		std::shared_ptr<Texture2D> m_Texture;
		float m_Width{  0 };
		float m_Height{ 0 };
	};
}


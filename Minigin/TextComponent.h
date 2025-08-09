#pragma once
#include <string>
#include <memory>
#include "GameObject.h"

namespace dae
{
	class Font;
	class Texture2D;
	class TextComponent : public Component
	{
	public:
		void Update(float deltaTime) override;
		void Render() const override;

		void SetText(const std::string& text);
		void SetSize(const unsigned int size);	

		std::shared_ptr<Texture2D> GetTexture() const;

		TextComponent(GameObject* owner, const std::string& text, std::shared_ptr<Font> font);

		~TextComponent() override = default;
		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;
	private:
		bool m_needsUpdate;
		std::string m_text;
		std::shared_ptr<Font> m_font;
		std::shared_ptr<Texture2D> m_texture;
	};
}

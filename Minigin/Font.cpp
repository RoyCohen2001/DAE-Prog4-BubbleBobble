#include <stdexcept>
#include <SDL_ttf.h>
#include "Font.h"

TTF_Font* dae::Font::GetFont() const {
	return m_font;
}

dae::Font::Font(const std::string& fullPath, unsigned int size) 
	: m_font(nullptr)
	, m_size(size)
	, m_fullPath(fullPath)
{
	m_font = TTF_OpenFont(fullPath.c_str(), size);
	if (m_font == nullptr) 
	{
		throw std::runtime_error(std::string("Failed to load font: ") + SDL_GetError());
	}
}

dae::Font::~Font()
{
	TTF_CloseFont(m_font);
}

std::shared_ptr<dae::Font> dae::Font::WithSize(unsigned int size) const
{
	return std::make_shared<Font>(m_fullPath, size);
}
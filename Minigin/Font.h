#pragma once
#include <string>
#include <memory>
#include <SDL_ttf.h>

struct _TTF_Font;
namespace dae
{
	/**
	 * Simple RAII wrapper for a _TTF_Font
	 */
	class Font final
	{
	public:
		_TTF_Font* GetFont() const;
		explicit Font(const std::string& fullPath, unsigned int size);

		std::shared_ptr<Font> WithSize(unsigned int size) const;


		~Font();

		Font(const Font &) = delete;
		Font(Font &&) = delete;
		Font & operator= (const Font &) = delete;
		Font & operator= (const Font &&) = delete;
	private:
		std::string m_fullPath;
		_TTF_Font* m_font;
		unsigned int m_size;
	};
}

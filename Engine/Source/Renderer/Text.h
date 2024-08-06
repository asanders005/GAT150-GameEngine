#pragma once
#include "../Resources/Resource.h"
#include <string>

class Font;
class Renderer;
struct Color;
struct SDL_Texture;

class Text
{
public:
	Text() = default;
	Text(res_t<Font> font, bool centered = false) : m_font{ font }, m_centered{ centered } {}
	~Text();

	void SetFont(res_t<Font> font) { m_font = font; }

	bool Create(Renderer& renderer, const std::string& text, const Color& color);
	void Draw(Renderer& renderer, int x, int y);

private:
	res_t<Font> m_font{ nullptr };
	SDL_Texture* m_texture{ nullptr };
	bool m_centered = false;
};
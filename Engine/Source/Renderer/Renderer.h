#pragma once
#include "Color.h"
#include <SDL.h>
#include <string>
#include <SDL_ttf.h>
#include <SDL_image.h>

struct Vector2;

class Renderer
{
public:
	Renderer() = default;

	bool Initialize();
	void Shutdown();

	bool CreateWindow(std::string title, int width, int height);
	void BeginFrame();
	void EndFrame();

	void SetColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
	void SetColor(Color& c);

	void DrawLine(int x1, int y1, int x2, int y2);
	void DrawLine(float x1, float y1, float x2, float y2);
	void DrawLine(Vector2& v1, Vector2& v2);

	void DrawPoint(int x, int y);
	void DrawPoint(float x, float y);
	void DrawPoint(Vector2& v);

	void DrawRect(int x, int y, int w, int h);
	void DrawRect(float x, float y, float w, float h);
	void DrawRect(Vector2& v, float w, float h);

	void DrawTexture(class Texture* texture, float x, float y, float angle = 0.0f);
	void DrawTexture(class Texture* texture, const struct Transform& transform, bool hflip = 0);

	int GetWidth() const { return m_width; }
	int GetHeight() const { return m_height; }

	friend class Text;
	friend class Texture;

private:
	SDL_Window* m_window{ nullptr };
	SDL_Renderer* m_renderer{ nullptr };

	int m_width{ 0 }, m_height{ 0 };
};
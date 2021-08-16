#pragma once

class Window {
public:
	Window();
	~Window();

	void render(SDL_Texture* Layer = NULL, int x = 0, int y = 0, int Width = 0, int Height = 0, SDL_Rect* clip = NULL);
	void renderText(int x = 0, int y = 0, const char* text = "", TTF_Font* font = NULL, SDL_Color textColor = { 0,0,0 });
	SDL_Texture* loadFromFilee(const char* path);
	void update();
	void clear(SDL_Color* color);
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
};
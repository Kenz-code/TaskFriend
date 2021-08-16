#pragma once

class Texture {
public:
	Texture();
	~Texture();

	void loadFromFile(const char* path);

	void render(int x, int y, SDL_Rect* clip);

	void free();

	int getWidth() {
		return Width;
	}
	int getHeight() {
		return Height;
	}

private:
	SDL_Texture* Layer;

	int Width;
	int Height;

};

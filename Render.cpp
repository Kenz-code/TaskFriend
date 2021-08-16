#include <iostream>
#include <SDL.h>
#undef main
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "Texture.h"
#include "Render.h"

Window::Window() {
	if (SDL_Init(SDL_INIT_EVERYTHING) > 0) {
		std::cout << "SDL failed to init :( ooooooooooooooof" << "             #loooooooooooooooooooooooooooooollereressssssssssssssssssssssssss" << std::endl;
	}
	else {
		window = SDL_CreateWindow("TaskFriend", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);
		SDL_Surface* windowIco = IMG_Load("Ico/Ico.png");
		SDL_SetWindowIcon(window, windowIco);
		if (window == NULL) {
			std::cout << "The window failed to open!" << std::endl;
		}
		else {
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (renderer == NULL) {
				std::cout << "The renderer failed to open!" << std::endl;
			}
			else {
				if (!(IMG_Init(IMG_INIT_PNG))) {
					std::cout << "oopers poopers img didnt init #looooooooooooooooleresrssssss" << std::endl;
				}
				else {
					if (!TTF_Init() == -1) {
						std::cout << "ladies and gentlemen, ttf didnt  init dododoododododdoododdoodododooooooooooooododododododo error:" << SDL_GetError() << std::endl;
					}
					Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

				}
			}
		}
	}
}

Window::~Window() {
	SDL_DestroyWindow(window);
	window = NULL;
	SDL_DestroyRenderer(renderer);
	renderer = NULL;
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void Window::render(SDL_Texture* Layer, int x, int y, int Width, int Height, SDL_Rect* clip) {
	// Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, Width, Height };
	if (clip != NULL) {
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}
	SDL_RenderCopy(renderer, Layer, NULL, &renderQuad);
}
void Window::renderText(int x, int y, const char* text, TTF_Font* font, SDL_Color textColor)
{
	SDL_Surface* surfaceMessage = TTF_RenderText_Blended(font, text, textColor);
	SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

	SDL_Rect src;
	src.x = 0;
	src.y = 0;
	src.w = surfaceMessage->w;
	src.h = surfaceMessage->h;

	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.w = src.w;
	dst.h = src.h;

	SDL_RenderCopy(renderer, message, &src, &dst);
	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(message);
}

SDL_Texture* Window::loadFromFilee(const char* path) {
	SDL_Texture* texture = NULL;
	texture = IMG_LoadTexture(renderer, path);

	if (texture == NULL)
		std::cout << "Failed to load texture. Error: " << SDL_GetError() << std::endl;

	return texture;
}
void Window::update() {
	SDL_RenderPresent(renderer);
}
void Window::clear(SDL_Color* color) {
	SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, 0xFF);
	SDL_RenderClear(renderer);
	
}
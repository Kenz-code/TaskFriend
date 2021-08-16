#include <iostream>
#include <SDL.h>
#undef main
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "Texture.h"
#include "Render.h"

Texture::Texture() {
	Layer = NULL;
}
Texture::~Texture() {
	Layer = NULL;
}
void Texture::free() {
        //Free texture if it exists
        if (Layer != NULL)
        {
            SDL_DestroyTexture(Layer);
            Layer = NULL;
            Width = 0;
            Height = 0;
        }
}
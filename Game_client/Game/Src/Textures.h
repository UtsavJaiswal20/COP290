#pragma once

#include "Game.h"

class Textures
{
public:
	static SDL_Texture* maketexture(const char* name);
	static void draw(SDL_Texture* text, SDL_Rect srect, SDL_Rect drect, SDL_RendererFlip flip);
};
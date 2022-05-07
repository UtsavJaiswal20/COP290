#include "Textures.h"

SDL_Texture* Textures::maketexture(const char* name) {

	SDL_Surface* surf = IMG_Load(name);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, surf);
	SDL_FreeSurface(surf);

	return texture;
}

void Textures::draw(SDL_Texture* text, SDL_Rect srect, SDL_Rect drect, SDL_RendererFlip flip)
{
	SDL_RenderCopyEx(Game::renderer, text, &srect, &drect, NULL, NULL, flip);
}

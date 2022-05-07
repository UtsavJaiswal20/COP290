#pragma once

#include "EntitySystem.h"
#include "SDL.h"

class MapTile : public Component
{
public:

	SDL_Texture* text;
	SDL_Rect srect, drect;
	Vector2 posi;

	MapTile() = default;

	MapTile(int sx, int sy, int x, int y, int tsize, int tscale, const char* name) {
		text = Textures::maketexture(name);
		posi.x = x;
		posi.y = y;
		srect.x = sx;
		srect.y = sy;
		srect.w = srect.h = tsize;
		drect.x = x ;
		drect.y = y;
		drect.h = drect.w = tsize * tscale;
	}

	~MapTile() {
		SDL_DestroyTexture(text);
	}

	void update() override {
		drect.x = posi.x - Game::cam.x;
		drect.y = posi.y - Game::cam.y;
	}

	void draw() override {
		if ((drect.x + drect.w > 0) && (drect.x < 1000) && (drect.y + drect.h > 0) && (drect.y < 800)) {
			Textures::draw(text, srect, drect, SDL_FLIP_NONE);
		}		
	}

};
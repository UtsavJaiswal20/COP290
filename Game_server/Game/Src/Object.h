#pragma once

#include "Game.h"

class Object
{
public:
	Object(char* texture, int x, int y);
	~Object();
	void update();
	void render();

private:
	int xc, yc;
	SDL_Rect srect, drect;
	SDL_Texture* objtex;
};
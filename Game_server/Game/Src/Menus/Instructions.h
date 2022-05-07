#pragma once
#include "SDL.h"
#include "SDL_ttf.h"

class Instructions
{
public:
	SDL_Rect posi;
	SDL_Color color[2];
	SDL_Texture* text;
	SDL_Texture* btext;
	SDL_Surface* imenu;
	SDL_Surface* bsurf;
	Uint32 time, ctime;
	int fps;
	int x, y;
	bool select;
	TTF_Font* font;
	const char* instr[3];

	Instructions() {
		color[0] = { 255, 239, 130 , 255 };
		color[1] = { 239, 211, 69, 255 };

	}
	~Instructions(){}
	void makeinstrmenu() {

	}
};
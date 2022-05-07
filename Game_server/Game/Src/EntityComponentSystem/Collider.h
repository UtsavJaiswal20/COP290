#pragma once

#include <string>
#include "Components.h"
#include "SDL.h"
#include "../Textures.h"

class Collider : public Component
{
public:

	SDL_Rect wall;
	std::string tag;

	SDL_Texture* text;
	SDL_Rect srect, drect;

	PositionComponent* posi;

	Collider(std::string s) {
		tag = s;
	}
	Collider(std::string s, int xc, int yc, int size) {
		tag = s;
		wall.x = xc;
		wall.y = yc;
		wall.h = wall.w = size;
	}

	void initialize() override{
		if (!entity->hascomponent<PositionComponent>())
		{
			entity->addComponent<PositionComponent>();
		}
		posi = &entity->getComponent<PositionComponent>();
		text = Textures::maketexture("Resources/Black.png");
		srect = { 0,0,32,32 };
		drect = { wall.x,wall.y,wall.w,wall.h };
	}

	void update() override {
		if (tag != "ground") {
			wall.x = static_cast<int>(posi->pos.x);
			wall.y = static_cast<int>(posi->pos.y);
			wall.w = posi->width * posi->scale;
			wall.h = posi->height * posi->scale;
		}

		drect.x = wall.x - Game::cam.x ;
		drect.y = wall.y - Game::cam.y;
	}

	void draw() override {
		Textures::draw(text, srect, drect, SDL_FLIP_NONE);
	}
};
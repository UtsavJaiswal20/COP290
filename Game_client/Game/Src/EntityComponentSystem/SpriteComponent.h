#pragma once

#include "Components.h"
#include "SDL.h"
#include "../Textures.h"
#include "Animated.h"
#include <map>
#include <SDL_ttf.h>
#include <SDL_image.h>

class SpriteComponent : public Component
{
private:
	PositionComponent* posi;
	SDL_Texture* text;
	SDL_Rect srect, drect;

	bool animated = false;
	int frames = 0;
	int delay = 100;

public:

	int aID = 0;

	std::map<const char*, Animated> animations;

	SDL_RendererFlip spriteflip = SDL_FLIP_NONE;

	SpriteComponent() = default;
	SpriteComponent(const char* name) {
		settex(name);
	}
	SpriteComponent(const char* name, bool isanimated) {
		animated = isanimated;

		Animated idle = Animated(0, 3, 100);
		Animated walk = Animated(1, 8, 100);

		animations.emplace("Idle", idle);
		animations.emplace("Walk", walk);

		play("Idle");

		settex(name);
	}
	~SpriteComponent() {
		SDL_DestroyTexture(text);
	}
	void settex(const char* name) {
		text = Textures::maketexture(name);
	}
	void initialize() override {

		posi = &entity->getComponent<PositionComponent>();

		srect.x = srect.y = 0;
		srect.w = posi->width;
		srect.h = posi->height;
	}
	void update() override {
		if (animated) {
			srect.x = srect.w * static_cast<int>((SDL_GetTicks() / delay)% frames);
		}
		srect.y = aID * posi->height;
		drect.x = (int)posi->pos.x - Game::cam.x;
		drect.y = (int)posi->pos.y - Game::cam.y;
		drect.h = posi->height * posi->scale;
		drect.w = posi->width * posi->scale;
	}
	void draw() override {
		Textures::draw(text, srect, drect, spriteflip);
		int x = posi->pos.x;
		int y = posi->pos.y;
		if (((x > 11 * 4 * 32) && (x < 13 * 4 * 32) && (y > 19 * 4 * 32) && (y < 20 * 4 * 32)) ||
			((x > 11 * 4 * 32) && (x < 13 * 4 * 32) && (y > 14 * 4 * 32) && (y < 15 * 4 * 32)) ||
			((x > 28 * 4 * 32) && (x < 30 * 4 * 32) && (y > 14 * 4 * 32) && (y < 15 * 4 * 32)) ||
			((x > 52 * 4 * 32) && (x < 54 * 4 * 32) && (y > 20 * 4 * 32) && (y < 21 * 4 * 32)) ||
			((x > 61 * 4 * 32) && (x < 63 * 4 * 32) && (y > 25 * 4 * 32) && (y < 26 * 4 * 32)) ||
			((x > 39 * 4 * 32) && (x < 41 * 4 * 32) && (y > 28 * 4 * 32) && (y < 29 * 4 * 32)) ||
			((x > 5 * 4 * 32) && (x < 7 * 4 * 32) && (y > 35 * 4 * 32) && (y < 36 * 4 * 32)) ||
			((x > 28 * 4 * 32) && (x < 30 * 4 * 32) && (y > 14 * 4 * 32) && (y < 15 * 4 * 32)) ||
			((x > 46 * 4 * 32) && (x < 48 * 4 * 32) && (y > 34 * 4 * 32) && (y < 35 * 4 * 32))) {
			TTF_Font* font;
			font = TTF_OpenFont("Resources/Sample.ttf", 40);
			SDL_Rect ssrrect;
			SDL_Color scolor = { 255, 255, 255, 255 };
			SDL_Texture* text;
			SDL_Surface* menu;
			const char* label = "YULU";
			menu = TTF_RenderText_Solid(font, label, scolor);
			text = SDL_CreateTextureFromSurface(Game::renderer, menu);
			SDL_FreeSurface(menu);
			SDL_QueryTexture(text, NULL, NULL, &ssrrect.w, &ssrrect.h);
			ssrrect.x = 500 - (ssrrect.w / 2);
			ssrrect.y = 700;
			SDL_RenderCopy(Game::renderer, text, NULL, &ssrrect);
		}
		if (((x > 4 * 4 * 32) && (x < 8 * 4 * 32) && (y > 19 * 4 * 32) && (y < 20 * 4 * 32)) ||
			((x > 20 * 4 * 32) && (x < 24 * 4 * 32) && (y > 19 * 4 * 32) && (y < 20 * 4 * 32)) ||
			((x > 2 * 4 * 32) && (x < 3 * 4 * 32) && (y > 22 * 4 * 32) && (y < 26 * 4 * 32)) ||
			((x > 45 * 4 * 32) && (x < 49 * 4 * 32) && (y > 14 * 4 * 32) && (y < 15 * 4 * 32)) ||
			((x > 50 * 4 * 32) && (x < 51 * 4 * 32) && (y > 9 * 4 * 32) && (y < 13 * 4 * 32)) ||
			((x > 59 * 4 * 32) && (x < 63 * 4 * 32) && (y > 3 * 4 * 32) && (y < 4 * 4 * 32)) ||
			((x > 5 * 4 * 32) && (x < 9 * 4 * 32) && (y > 41 * 4 * 32) && (y < 42 * 4 * 32)) ||
			((x > 21 * 4 * 32) && (x < 25 * 4 * 32) && (y > 41 * 4 * 32) && (y < 42 * 4 * 32)) ||
			((x > 54 * 4 * 32) && (x < 58 * 4 * 32) && (y > 25 * 4 * 32) && (y < 26 * 4 * 32))) {
			TTF_Font* font;
			font = TTF_OpenFont("Resources/Sample.ttf", 40);
			SDL_Rect ssrrect;
			SDL_Color scolor = { 255, 255, 255, 255 };
			SDL_Texture* text;
			SDL_Surface* menu;
			const char* label = "HOSTEL";
			menu = TTF_RenderText_Solid(font, label, scolor);
			text = SDL_CreateTextureFromSurface(Game::renderer, menu);
			SDL_FreeSurface(menu);
			SDL_QueryTexture(text, NULL, NULL, &ssrrect.w, &ssrrect.h);
			ssrrect.x = 500 - (ssrrect.w / 2);
			ssrrect.y = 700;
			SDL_RenderCopy(Game::renderer, text, NULL, &ssrrect);
		}
		if (((x > 26 * 4 * 32) && (x < 30 * 4 * 32) && (y > 28 * 4 * 32) && (y < 29 * 4 * 32))) {
			TTF_Font* font;
			font = TTF_OpenFont("Resources/Sample.ttf", 40);
			SDL_Rect ssrrect;
			SDL_Color scolor = { 255, 255, 255, 255 };
			SDL_Texture* text;
			SDL_Surface* menu;
			const char* label = "BHARTI SCHOOL";
			menu = TTF_RenderText_Solid(font, label, scolor);
			text = SDL_CreateTextureFromSurface(Game::renderer, menu);
			SDL_FreeSurface(menu);
			SDL_QueryTexture(text, NULL, NULL, &ssrrect.w, &ssrrect.h);
			ssrrect.x = 500 - (ssrrect.w / 2);
			ssrrect.y = 700;
			SDL_RenderCopy(Game::renderer, text, NULL, &ssrrect);
		}
		if (((x > 8 * 4 * 32) && (x < 12 * 4 * 32) && (y > 28 * 4 * 32) && (y < 29 * 4 * 32)) ||
			((x > 33 * 4 * 32) && (x < 37 * 4 * 32) && (y > 35 * 4 * 32) && (y < 36 * 4 * 32)) ||
			((x > 35 * 4 * 32) && (x < 39 * 4 * 32) && (y > 19 * 4 * 32) && (y < 20 * 4 * 32))) {
			TTF_Font* font;
			font = TTF_OpenFont("Resources/Sample.ttf", 40);
			SDL_Rect ssrrect;
			SDL_Color scolor = { 255, 255, 255, 255 };
			SDL_Texture* text;
			SDL_Surface* menu;
			const char* label = "SPORT";
			menu = TTF_RenderText_Solid(font, label, scolor);
			text = SDL_CreateTextureFromSurface(Game::renderer, menu);
			SDL_FreeSurface(menu);
			SDL_QueryTexture(text, NULL, NULL, &ssrrect.w, &ssrrect.h);
			ssrrect.x = 500 - (ssrrect.w / 2);
			ssrrect.y = 700;
			SDL_RenderCopy(Game::renderer, text, NULL, &ssrrect);
		}
		if (((x > 34 * 4 * 32) && (x < 38 * 4 * 32) && (y > 28 * 4 * 32) && (y < 29 * 4 * 32)) ||
			((x > 30 * 4 * 32) && (x < 34 * 4 * 32) && (y > 28 * 4 * 32) && (y < 29 * 4 * 32)) ||
			((x > 20 * 4 * 32) && (x < 24 * 4 * 32) && (y > 28 * 4 * 32) && (y < 29 * 4 * 32)) ||
			((x > 12 * 4 * 32) && (x < 16 * 4 * 32) && (y > 28 * 4 * 32) && (y < 29 * 4 * 32))) {
			TTF_Font* font;
			font = TTF_OpenFont("Resources/Sample.ttf", 40);
			SDL_Rect ssrrect;
			SDL_Color scolor = { 255, 255, 255, 255 };
			SDL_Texture* text;
			SDL_Surface* menu;
			const char* label = "FOOD";
			menu = TTF_RenderText_Solid(font, label, scolor);
			text = SDL_CreateTextureFromSurface(Game::renderer, menu);
			SDL_FreeSurface(menu);
			SDL_QueryTexture(text, NULL, NULL, &ssrrect.w, &ssrrect.h);
			ssrrect.x = 500 - (ssrrect.w / 2);
			ssrrect.y = 700;
			SDL_RenderCopy(Game::renderer, text, NULL, &ssrrect);
		}
		if (((x > 44 * 4 * 32) && (x < 48 * 4 * 32) && (y > 28 * 4 * 32) && (y < 29 * 4 * 32)) ||
			((x > 44 * 4 * 32) && (x < 48 * 4 * 32) && (y > 20 * 4 * 32) && (y < 21 * 4 * 32))) {
			TTF_Font* font;
			font = TTF_OpenFont("Resources/Sample.ttf", 40);
			SDL_Rect ssrrect;
			SDL_Color scolor = { 255, 255, 255, 255 };
			SDL_Texture* text;
			SDL_Surface* menu;
			const char* label = "STUDY SPOT";
			menu = TTF_RenderText_Solid(font, label, scolor);
			text = SDL_CreateTextureFromSurface(Game::renderer, menu);
			SDL_FreeSurface(menu);
			SDL_QueryTexture(text, NULL, NULL, &ssrrect.w, &ssrrect.h);
			ssrrect.x = 500 - (ssrrect.w / 2);
			ssrrect.y = 700;
			SDL_RenderCopy(Game::renderer, text, NULL, &ssrrect);
		}
		if (((x > 66 * 4 * 32) && (x < 67 * 4 * 32) && (y > 35 * 4 * 32) && (y < 38 * 4 * 32))) {
			TTF_Font* font;
			font = TTF_OpenFont("Resources/Sample.ttf", 40);
			SDL_Rect ssrrect;
			SDL_Color scolor = { 255, 255, 255, 255 };
			SDL_Texture* text;
			SDL_Surface* menu;
			const char* label = "IIT MARKET";
			menu = TTF_RenderText_Solid(font, label, scolor);
			text = SDL_CreateTextureFromSurface(Game::renderer, menu);
			SDL_FreeSurface(menu);
			SDL_QueryTexture(text, NULL, NULL, &ssrrect.w, &ssrrect.h);
			ssrrect.x = 500 - (ssrrect.w / 2);
			ssrrect.y = 700;
			SDL_RenderCopy(Game::renderer, text, NULL, &ssrrect);
		}
	}
	void play(const char* animname) {
		frames = animations[animname].frames;
		delay = animations[animname].delay;
		aID = animations[animname].index;
	}
};
#pragma once

#include "../Game.h"
#include "EntitySystem.h"
#include "Components.h"
#include "../Menus/PauseMenu.h"
#include <WinSock2.h>

class KeyboardInputs : public Component
{
public:
	PositionComponent* posi;
	SpriteComponent* sprite;
	int x, y;
	bool yselect, yjselect;

	void initialize() override {
		posi = &entity->getComponent<PositionComponent>();
		sprite = &entity->getComponent<SpriteComponent>();
		x = y = 0;
		yselect = false;
		yjselect = false;
	}

	void update() override {
		bool exit = false;
		bool exit2 = false;
		bool exit3 = false;
		bool exit4 = false;
		bool exit5 = false;
		bool exit6 = false;
		if (Game::event.type == SDL_KEYDOWN) {
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_w:
				posi->movement.y = -1;
				//posi->score++;
				sprite->play("Walk");
				break;
			case SDLK_a:
				posi->movement.x = -1;
				sprite->play("Walk");
				sprite->spriteflip = SDL_FLIP_HORIZONTAL;
				break;
			case SDLK_s:
				posi->movement.y = 1;
				sprite->play("Walk");
				break;
			case SDLK_d:
				posi->movement.x = 1;
				sprite->play("Walk");
				break;
			default:
				break;
			}
		}
		if (Game::event.type == SDL_KEYUP) {
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_w:
				posi->movement.y = 0;
				sprite->play("Idle");
				yjselect = false;
				break;
			case SDLK_a:
				posi->movement.x = 0;
				sprite->play("Idle");
				sprite->spriteflip = SDL_FLIP_NONE;
				yjselect = false;
				break;
			case SDLK_s:
				posi->movement.y = 0;
				sprite->play("Idle");
				yjselect = false;
				break;
			case SDLK_d:
				posi->movement.x = 0;
				sprite->play("Idle");
				yjselect = false;
				break;
			case SDLK_e:
				x = posi->pos.x;
				y = posi->pos.y;
				if (((x > 11 * 4 * 32) && (x < 13 * 4 * 32) && (y > 19 * 4 * 32) && (y < 20 * 4 * 32)) ||
					((x > 11 * 4 * 32) && (x < 13 * 4 * 32) && (y > 14 * 4 * 32) && (y < 15 * 4 * 32)) ||
					((x > 28 * 4 * 32) && (x < 30 * 4 * 32) && (y > 14 * 4 * 32) && (y < 15 * 4 * 32)) ||
					((x > 52 * 4 * 32) && (x < 54 * 4 * 32) && (y > 20 * 4 * 32) && (y < 21 * 4 * 32)) ||
					((x > 61 * 4 * 32) && (x < 63 * 4 * 32) && (y > 25 * 4 * 32) && (y < 26 * 4 * 32)) ||
					((x > 39 * 4 * 32) && (x < 41 * 4 * 32) && (y > 28 * 4 * 32) && (y < 29 * 4 * 32)) ||
					((x > 5 * 4 * 32) && (x < 7 * 4 * 32) && (y > 35 * 4 * 32) && (y < 36 * 4 * 32)) ||
					((x > 28 * 4 * 32) && (x < 30 * 4 * 32) && (y > 14 * 4 * 32) && (y < 15 * 4 * 32)) ||
					((x > 46 * 4 * 32) && (x < 48 * 4 * 32) && (y > 34 * 4 * 32) && (y < 35 * 4 * 32))) {
					if ((posi->speed==15)&&!yjselect) {
						//std::cout << "stop" << std::endl;
						posi->speed = 5;
						yselect = false;
						yjselect = true;
						SDL_Delay(500);
					}
					else if((posi->speed == 5)&&!yjselect) {
						//std::cout << "start" << std::endl;
						posi->speed = 15;
						yselect = true;
						yjselect = true;
						SDL_Delay(500);
					}
				}
				if (((x > 4 * 4 * 32) && (x < 8 * 4 * 32) && (y > 19 * 4 * 32) && (y < 20 * 4 * 32)) ||
					((x > 20 * 4 * 32) && (x < 24 * 4 * 32) && (y > 19 * 4 * 32) && (y < 20 * 4 * 32)) ||
					((x > 2 * 4 * 32) && (x < 3 * 4 * 32) && (y > 22 * 4 * 32) && (y < 26 * 4 * 32)) ||
					((x > 45 * 4 * 32) && (x < 49 * 4 * 32) && (y > 14 * 4 * 32) && (y < 15 * 4 * 32)) ||
					((x > 50 * 4 * 32) && (x < 51 * 4 * 32) && (y > 9 * 4 * 32) && (y < 13 * 4 * 32)) ||
					((x > 59 * 4 * 32) && (x < 63 * 4 * 32) && (y > 3 * 4 * 32) && (y < 4 * 4 * 32)) ||
					((x > 5 * 4 * 32) && (x < 9 * 4 * 32) && (y > 41 * 4 * 32) && (y < 42 * 4 * 32)) ||
					((x > 21 * 4 * 32) && (x < 25 * 4 * 32) && (y > 41 * 4 * 32) && (y < 42 * 4 * 32)) ||
					((x > 54 * 4 * 32) && (x < 58 * 4 * 32) && (y > 25 * 4 * 32) && (y < 26 * 4 * 32))){
					if (exit == false) {
						exit = mmenu();
					}
				}
				if (((x > 26 * 4 * 32) && (x < 30 * 4 * 32) && (y > 28 * 4 * 32) && (y < 29 * 4 * 32))) {
					if (exit2 == false) {
						exit2 = bmenu();
					}
				}
				if (((x > 8 * 4 * 32) && (x < 12 * 4 * 32) && (y > 28 * 4 * 32) && (y < 29 * 4 * 32)) ||
					((x > 33 * 4 * 32) && (x < 37 * 4 * 32) && (y > 35 * 4 * 32) && (y < 36 * 4 * 32)) ||
					((x > 35 * 4 * 32) && (x < 39 * 4 * 32) && (y > 19 * 4 * 32) && (y < 20 * 4 * 32))) {
					if (exit3 == false) {
						exit3 = smenu();
					}
				}
				if (((x > 34 * 4 * 32) && (x < 38 * 4 * 32) && (y > 28 * 4 * 32) && (y < 29 * 4 * 32)) ||
					((x > 30 * 4 * 32) && (x < 34 * 4 * 32) && (y > 28 * 4 * 32) && (y < 29 * 4 * 32)) ||
					((x > 20 * 4 * 32) && (x < 24 * 4 * 32) && (y > 28 * 4 * 32) && (y < 29 * 4 * 32)) ||
					((x > 12 * 4 * 32) && (x < 16 * 4 * 32) && (y > 28 * 4 * 32) && (y < 29 * 4 * 32))) {
					if (exit4 == false) {
						exit4 = emenu();
					}
				}
				if (((x > 44 * 4 * 32) && (x < 48 * 4 * 32) && (y > 28 * 4 * 32) && (y < 29 * 4 * 32)) ||
					((x > 44 * 4 * 32) && (x < 48 * 4 * 32) && (y > 20 * 4 * 32) && (y < 21 * 4 * 32))) {
					if (exit5 == false) {
						exit5 = stmenu();
					}
				}
				if (((x > 66 * 4 * 32) && (x < 67 * 4 * 32) && (y > 35 * 4 * 32) && (y < 38 * 4 * 32))) {
					if (exit6 == false) {
						exit6 = mamenu();
					}
				}
				break;
			default:
				break;
			}
		}
	}
	bool mmenu() {
		SDL_Rect pos[3]{};
		const char* label[3] = { "EATING/SLEEPING", "BATHING", "POLTU"};
		TTF_Font* font;
		font = TTF_OpenFont("Resources/Sample.ttf", 40);
		SDL_Color color[3] = { { 255, 255, 255, 255 }, { 127, 127, 127, 255 }, { 0, 0, 0, 255 } };
		SDL_Texture* text[3]{};
		SDL_Surface* menu[3]{};
		Uint32 time = 0;
		Uint32 ctime = 32;
		int fps = 50;
		int x = 0;
		int y = 0;
		bool select[3] = { false, false, false };
		menu[0] = TTF_RenderText_Solid(font, label[0], color[0]);
		text[0] = SDL_CreateTextureFromSurface(Game::renderer, menu[0]);
		SDL_FreeSurface(menu[0]);
		menu[1] = TTF_RenderText_Solid(font, label[1], color[0]);
		text[1] = SDL_CreateTextureFromSurface(Game::renderer, menu[1]);
		SDL_FreeSurface(menu[1]);
		menu[2] = TTF_RenderText_Solid(font, label[2], color[0]);
		text[2] = SDL_CreateTextureFromSurface(Game::renderer, menu[2]);
		SDL_FreeSurface(menu[2]);
		SDL_QueryTexture(text[0], NULL, NULL, &pos[0].w, &pos[0].h);
		SDL_QueryTexture(text[1], NULL, NULL, &pos[1].w, &pos[1].h);
		SDL_QueryTexture(text[2], NULL, NULL, &pos[2].w, &pos[2].h);
		pos[0].x = 500 - (pos[0].w / 2);
		pos[0].y = 350;
		pos[1].x = 500 - (pos[1].w / 2);
		pos[1].y = 370 + pos[0].h;
		pos[2].x = 500 - (pos[2].w / 2);
		pos[2].y = 390 + pos[0].h + pos[1].h;

		SDL_SetRenderDrawColor(Game::renderer, 0, 0, 255, 255);
		SDL_RenderClear(Game::renderer);
		SDL_RenderCopy(Game::renderer, text[0], NULL, &pos[0]);
		SDL_RenderCopy(Game::renderer, text[1], NULL, &pos[1]);
		SDL_RenderCopy(Game::renderer, text[2], NULL, &pos[2]);
		SDL_RenderPresent(Game::renderer);
		SDL_Event eventt;
		int flag = 0;
		bool f2 = true;
		while (f2) {
			time = SDL_GetTicks();
			SDL_PollEvent(&eventt);
			switch (eventt.type)
			{
			case SDL_QUIT:
				flag = 2;
				f2 = false;
				break;
			case SDL_KEYDOWN:
				if (eventt.key.keysym.sym == SDLK_ESCAPE) {
					flag = 1;
					f2 = false;
				}
				break;
			case SDL_MOUSEMOTION:
				x = eventt.motion.x;
				y = eventt.motion.y;
				for (int i = 0; i <= 2; i++) {
					if ((x >= pos[i].x) && (x <= pos[i].x + pos[i].w) && (y >= pos[i].y) && (y <= pos[i].y + pos[i].h)) {
						if (!select[i]) {
							select[i] = 1;
							menu[i] = TTF_RenderText_Solid(font, label[i], color[1]);
							text[i] = SDL_CreateTextureFromSurface(Game::renderer, menu[i]);
							SDL_FreeSurface(menu[i]);
						}
					}
					else {
						if (select[i]) {
							select[i] = 0;
							menu[i] = TTF_RenderText_Solid(font, label[i], color[0]);
							text[i] = SDL_CreateTextureFromSurface(Game::renderer, menu[i]);
							SDL_FreeSurface(menu[i]);
						}
					}
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				x = eventt.button.x;
				y = eventt.button.y;
				for (int i = 0; i <=2; i++) {
					if ((x >= pos[i].x) && (x <= pos[i].x + pos[i].w) && (y >= pos[i].y) && (y <= pos[i].y + pos[i].h)) {
						flag = i + 3;
						f2 = false;
						break;
					}
				}
				break;
			default:
				break;
			}
			if (flag == 1) {
				Game::isRunning = true;
				SDL_Delay(1000);
				return true;
				break;
			}
			else if (flag == 2) {
				Game::isRunning = false;
				SDL_Delay(1000);
				return true;
				break;
			}
			else if (flag == 3) {
				posi->energy = 100;
				posi->score += 50;
				SDL_Delay(2000);
				return true;
				break;
			}
			else if (flag == 4) {
				posi->hygiene = 100;
				posi->score += 50;
				SDL_Delay(1000);
				return true;
				break;
			}
			else if (flag == 5) {
				posi->popularity += 10;
				if (posi->popularity > 100) {
					posi->popularity = 100;
				}
				posi->score += 25;
				SDL_Delay(1000);
				return true;
				break;
			}
			else {
				SDL_RenderClear(Game::renderer);
				SDL_RenderCopy(Game::renderer, text[0], NULL, &pos[0]);
				SDL_RenderCopy(Game::renderer, text[1], NULL, &pos[1]);
				SDL_RenderCopy(Game::renderer, text[2], NULL, &pos[2]);
				SDL_RenderPresent(Game::renderer);
				ctime = SDL_GetTicks() - time;
				if (ctime < (1000 / fps)) {
					SDL_Delay((1000 / fps) - ctime);
				}
			}
		}
	}
	bool bmenu() {
		SDL_Rect pos[1]{};
		const char* label[1] = { "INTERN" };
		TTF_Font* font;
		font = TTF_OpenFont("Resources/Sample.ttf", 40);
		SDL_Color color[3] = { { 255, 255, 255, 255 }, { 127, 127, 127, 255 }, { 0, 0, 0, 255 } };
		SDL_Texture* text[1]{};
		SDL_Surface* menu[1]{};
		Uint32 time = 0;
		Uint32 ctime = 32;
		int fps = 50;
		int x = 0;
		int y = 0;
		bool select[1] = { false };
		menu[0] = TTF_RenderText_Solid(font, label[0], color[0]);
		text[0] = SDL_CreateTextureFromSurface(Game::renderer, menu[0]);
		SDL_FreeSurface(menu[0]);
		SDL_QueryTexture(text[0], NULL, NULL, &pos[0].w, &pos[0].h);
		pos[0].x = 500 - (pos[0].w / 2);
		pos[0].y = 400;

		SDL_SetRenderDrawColor(Game::renderer, 0, 0, 255, 255);
		SDL_RenderClear(Game::renderer);
		SDL_RenderCopy(Game::renderer, text[0], NULL, &pos[0]);
		SDL_RenderPresent(Game::renderer);
		SDL_Event eventt;
		int flag = 0;
		bool f2 = true;
		while (f2) {
			time = SDL_GetTicks();
			SDL_PollEvent(&eventt);
			switch (eventt.type)
			{
			case SDL_QUIT:
				flag = 2;
				f2 = false;
				break;
			case SDL_KEYDOWN:
				if (eventt.key.keysym.sym == SDLK_ESCAPE) {
					flag = 1;
					f2 = false;
				}
				break;
			case SDL_MOUSEMOTION:
				x = eventt.motion.x;
				y = eventt.motion.y;
				for (int i = 0; i < 1; i++) {
					if ((x >= pos[i].x) && (x <= pos[i].x + pos[i].w) && (y >= pos[i].y) && (y <= pos[i].y + pos[i].h)) {
						if (!select[i]) {
							select[i] = 1;
							menu[i] = TTF_RenderText_Solid(font, label[i], color[1]);
							text[i] = SDL_CreateTextureFromSurface(Game::renderer, menu[i]);
							SDL_FreeSurface(menu[i]);
						}
					}
					else {
						if (select[i]) {
							select[i] = 0;
							menu[i] = TTF_RenderText_Solid(font, label[i], color[0]);
							text[i] = SDL_CreateTextureFromSurface(Game::renderer, menu[i]);
							SDL_FreeSurface(menu[i]);
						}
					}
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				x = eventt.button.x;
				y = eventt.button.y;
				for (int i = 0; i < 1; i++) {
					if ((x >= pos[i].x) && (x <= pos[i].x + pos[i].w) && (y >= pos[i].y) && (y <= pos[i].y + pos[i].h)) {
						flag = i + 3;
						f2 = false;
						break;
					}
				}
				break;
			default:
				break;
			}
			if (flag == 1) {
				Game::isRunning = true;
				SDL_Delay(1000);
				return true;
				break;
			}
			else if (flag == 2) {
				Game::isRunning = false;
				SDL_Delay(1000);
				return true;
				break;
			}
			else if (flag == 3) {
				posi->money += 50;
				posi->score += 100;
				SDL_Delay(2000);
				return true;
				break;
			}
			else {
				SDL_RenderClear(Game::renderer);
				SDL_RenderCopy(Game::renderer, text[0], NULL, &pos[0]);
				SDL_RenderPresent(Game::renderer);
				ctime = SDL_GetTicks() - time;
				if (ctime < (1000 / fps)) {
					SDL_Delay((1000 / fps) - ctime);
				}
			}
		}
	}
	bool smenu() {
		SDL_Rect pos[1]{};
		const char* label[1] = { "PLAY" };
		TTF_Font* font;
		font = TTF_OpenFont("Resources/Sample.ttf", 40);
		SDL_Color color[3] = { { 255, 255, 255, 255 }, { 127, 127, 127, 255 }, { 0, 0, 0, 255 } };
		SDL_Texture* text[1]{};
		SDL_Surface* menu[1]{};
		Uint32 time = 0;
		Uint32 ctime = 32;
		int fps = 50;
		int x = 0;
		int y = 0;
		bool select[1] = { false };
		menu[0] = TTF_RenderText_Solid(font, label[0], color[0]);
		text[0] = SDL_CreateTextureFromSurface(Game::renderer, menu[0]);
		SDL_FreeSurface(menu[0]);
		SDL_QueryTexture(text[0], NULL, NULL, &pos[0].w, &pos[0].h);
		pos[0].x = 500 - (pos[0].w / 2);
		pos[0].y = 400;

		SDL_SetRenderDrawColor(Game::renderer, 0, 0, 255, 255);
		SDL_RenderClear(Game::renderer);
		SDL_RenderCopy(Game::renderer, text[0], NULL, &pos[0]);
		SDL_RenderPresent(Game::renderer);
		SDL_Event eventt;
		int flag = 0;
		bool f2 = true;
		while (f2) {
			time = SDL_GetTicks();
			SDL_PollEvent(&eventt);
			switch (eventt.type)
			{
			case SDL_QUIT:
				flag = 2;
				f2 = false;
				break;
			case SDL_KEYDOWN:
				if (eventt.key.keysym.sym == SDLK_ESCAPE) {
					flag = 1;
					f2 = false;
				}
				break;
			case SDL_MOUSEMOTION:
				x = eventt.motion.x;
				y = eventt.motion.y;
				for (int i = 0; i < 1; i++) {
					if ((x >= pos[i].x) && (x <= pos[i].x + pos[i].w) && (y >= pos[i].y) && (y <= pos[i].y + pos[i].h)) {
						if (!select[i]) {
							select[i] = 1;
							menu[i] = TTF_RenderText_Solid(font, label[i], color[1]);
							text[i] = SDL_CreateTextureFromSurface(Game::renderer, menu[i]);
							SDL_FreeSurface(menu[i]);
						}
					}
					else {
						if (select[i]) {
							select[i] = 0;
							menu[i] = TTF_RenderText_Solid(font, label[i], color[0]);
							text[i] = SDL_CreateTextureFromSurface(Game::renderer, menu[i]);
							SDL_FreeSurface(menu[i]);
						}
					}
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				x = eventt.button.x;
				y = eventt.button.y;
				for (int i = 0; i < 1; i++) {
					if ((x >= pos[i].x) && (x <= pos[i].x + pos[i].w) && (y >= pos[i].y) && (y <= pos[i].y + pos[i].h)) {
						flag = i + 3;
						f2 = false;
						break;
					}
				}
				break;
			default:
				break;
			}
			if (flag == 1) {
				Game::isRunning = true;
				SDL_Delay(1000);
				return true;
				break;
			}
			else if (flag == 2) {
				Game::isRunning = false;
				SDL_Delay(1000);
				return true;
				break;
			}
			else if (flag == 3) {
				posi->hygiene -= 40;
				posi->energy -= 25;
				if (posi->hygiene < 0) {
					posi->hygiene = 0;
				}
				if (posi->energy < 0) {
					posi->energy = 0;
				}
				posi->score += 50;
				SDL_Delay(2000);
				return true;
				break;
			}
			else {
				SDL_RenderClear(Game::renderer);
				SDL_RenderCopy(Game::renderer, text[0], NULL, &pos[0]);
				SDL_RenderPresent(Game::renderer);
				ctime = SDL_GetTicks() - time;
				if (ctime < (1000 / fps)) {
					SDL_Delay((1000 / fps) - ctime);
				}
			}
		}
	}
	bool emenu() {
		SDL_Rect pos[1]{};
		const char* label[1] = { "EAT(MONEY>=25)" };
		TTF_Font* font;
		font = TTF_OpenFont("Resources/Sample.ttf", 40);
		SDL_Color color[3] = { { 255, 255, 255, 255 }, { 127, 127, 127, 255 }, { 0, 0, 0, 255 } };
		SDL_Texture* text[1]{};
		SDL_Surface* menu[1]{};
		Uint32 time = 0;
		Uint32 ctime = 32;
		int fps = 50;
		int x = 0;
		int y = 0;
		bool select[1] = { false };
		menu[0] = TTF_RenderText_Solid(font, label[0], color[0]);
		text[0] = SDL_CreateTextureFromSurface(Game::renderer, menu[0]);
		SDL_FreeSurface(menu[0]);
		SDL_QueryTexture(text[0], NULL, NULL, &pos[0].w, &pos[0].h);
		pos[0].x = 500 - (pos[0].w / 2);
		pos[0].y = 400;

		SDL_SetRenderDrawColor(Game::renderer, 0, 0, 255, 255);
		SDL_RenderClear(Game::renderer);
		SDL_RenderCopy(Game::renderer, text[0], NULL, &pos[0]);
		SDL_RenderPresent(Game::renderer);
		SDL_Event eventt;
		int flag = 0;
		bool f2 = true;
		while (f2) {
			time = SDL_GetTicks();
			SDL_PollEvent(&eventt);
			switch (eventt.type)
			{
			case SDL_QUIT:
				flag = 2;
				f2 = false;
				break;
			case SDL_KEYDOWN:
				if (eventt.key.keysym.sym == SDLK_ESCAPE) {
					flag = 1;
					f2 = false;
				}
				break;
			case SDL_MOUSEMOTION:
				x = eventt.motion.x;
				y = eventt.motion.y;
				for (int i = 0; i < 1; i++) {
					if ((x >= pos[i].x) && (x <= pos[i].x + pos[i].w) && (y >= pos[i].y) && (y <= pos[i].y + pos[i].h)) {
						if (!select[i]) {
							select[i] = 1;
							menu[i] = TTF_RenderText_Solid(font, label[i], color[1]);
							text[i] = SDL_CreateTextureFromSurface(Game::renderer, menu[i]);
							SDL_FreeSurface(menu[i]);
						}
					}
					else {
						if (select[i]) {
							select[i] = 0;
							menu[i] = TTF_RenderText_Solid(font, label[i], color[0]);
							text[i] = SDL_CreateTextureFromSurface(Game::renderer, menu[i]);
							SDL_FreeSurface(menu[i]);
						}
					}
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				x = eventt.button.x;
				y = eventt.button.y;
				for (int i = 0; i < 1; i++) {
					if ((x >= pos[i].x) && (x <= pos[i].x + pos[i].w) && (y >= pos[i].y) && (y <= pos[i].y + pos[i].h)) {
						flag = i + 3;
						f2 = false;
						break;
					}
				}
				break;
			default:
				break;
			}
			if (flag == 1) {
				Game::isRunning = true;
				SDL_Delay(1000);
				return true;
				break;
			}
			else if (flag == 2) {
				Game::isRunning = false;
				SDL_Delay(1000);
				return true;
				break;
			}
			else if (flag == 3) {
				posi->money -= 40;
				if (posi->money < 0) {
					posi->money += 40;
				}
				else {
					posi->score += 50;
					posi->energy = 100;
				}
				SDL_Delay(2000);
				return true;
				break;
			}
			else {
				SDL_RenderClear(Game::renderer);
				SDL_RenderCopy(Game::renderer, text[0], NULL, &pos[0]);
				SDL_RenderPresent(Game::renderer);
				ctime = SDL_GetTicks() - time;
				if (ctime < (1000 / fps)) {
					SDL_Delay((1000 / fps) - ctime);
				}
			}
		}
	}
	bool stmenu() {
		SDL_Rect pos[1]{};
		const char* label[1] = { "STUDY" };
		TTF_Font* font;
		font = TTF_OpenFont("Resources/Sample.ttf", 40);
		SDL_Color color[3] = { { 255, 255, 255, 255 }, { 127, 127, 127, 255 }, { 0, 0, 0, 255 } };
		SDL_Texture* text[1]{};
		SDL_Surface* menu[1]{};
		Uint32 time = 0;
		Uint32 ctime = 32;
		int fps = 50;
		int x = 0;
		int y = 0;
		bool select[1] = { false };
		menu[0] = TTF_RenderText_Solid(font, label[0], color[0]);
		text[0] = SDL_CreateTextureFromSurface(Game::renderer, menu[0]);
		SDL_FreeSurface(menu[0]);
		SDL_QueryTexture(text[0], NULL, NULL, &pos[0].w, &pos[0].h);
		pos[0].x = 500 - (pos[0].w / 2);
		pos[0].y = 400;

		SDL_SetRenderDrawColor(Game::renderer, 0, 0, 255, 255);
		SDL_RenderClear(Game::renderer);
		SDL_RenderCopy(Game::renderer, text[0], NULL, &pos[0]);
		SDL_RenderPresent(Game::renderer);
		SDL_Event eventt;
		int flag = 0;
		bool f2 = true;
		while (f2) {
			time = SDL_GetTicks();
			SDL_PollEvent(&eventt);
			switch (eventt.type)
			{
			case SDL_QUIT:
				flag = 2;
				f2 = false;
				break;
			case SDL_KEYDOWN:
				if (eventt.key.keysym.sym == SDLK_ESCAPE) {
					flag = 1;
					f2 = false;
				}
				break;
			case SDL_MOUSEMOTION:
				x = eventt.motion.x;
				y = eventt.motion.y;
				for (int i = 0; i < 1; i++) {
					if ((x >= pos[i].x) && (x <= pos[i].x + pos[i].w) && (y >= pos[i].y) && (y <= pos[i].y + pos[i].h)) {
						if (!select[i]) {
							select[i] = 1;
							menu[i] = TTF_RenderText_Solid(font, label[i], color[1]);
							text[i] = SDL_CreateTextureFromSurface(Game::renderer, menu[i]);
							SDL_FreeSurface(menu[i]);
						}
					}
					else {
						if (select[i]) {
							select[i] = 0;
							menu[i] = TTF_RenderText_Solid(font, label[i], color[0]);
							text[i] = SDL_CreateTextureFromSurface(Game::renderer, menu[i]);
							SDL_FreeSurface(menu[i]);
						}
					}
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				x = eventt.button.x;
				y = eventt.button.y;
				for (int i = 0; i < 1; i++) {
					if ((x >= pos[i].x) && (x <= pos[i].x + pos[i].w) && (y >= pos[i].y) && (y <= pos[i].y + pos[i].h)) {
						flag = i + 3;
						f2 = false;
						break;
					}
				}
				break;
			default:
				break;
			}
			if (flag == 1) {
				Game::isRunning = true;
				SDL_Delay(1000);
				return true;
				break;
			}
			else if (flag == 2) {
				Game::isRunning = false;
				SDL_Delay(1000);
				return true;
				break;
			}
			else if (flag == 3) {
				posi->energy -= 50;
				if (posi->energy < 0) {
					posi->energy = 0;
				}
				posi->score += 150;
				SDL_Delay(2000);
				return true;
				break;
			}
			else {
				SDL_RenderClear(Game::renderer);
				SDL_RenderCopy(Game::renderer, text[0], NULL, &pos[0]);
				SDL_RenderPresent(Game::renderer);
				ctime = SDL_GetTicks() - time;
				if (ctime < (1000 / fps)) {
					SDL_Delay((1000 / fps) - ctime);
				}
			}
		}
	}
	bool mamenu() {
		SDL_Rect pos[1]{};
		const char* label[1] = { "BUY(MONEY>=40)" };
		TTF_Font* font;
		font = TTF_OpenFont("Resources/Sample.ttf", 40);
		SDL_Color color[3] = { { 255, 255, 255, 255 }, { 127, 127, 127, 255 }, { 0, 0, 0, 255 } };
		SDL_Texture* text[1]{};
		SDL_Surface* menu[1]{};
		Uint32 time = 0;
		Uint32 ctime = 32;
		int fps = 50;
		int x = 0;
		int y = 0;
		bool select[1] = { false };
		menu[0] = TTF_RenderText_Solid(font, label[0], color[0]);
		text[0] = SDL_CreateTextureFromSurface(Game::renderer, menu[0]);
		SDL_FreeSurface(menu[0]);
		SDL_QueryTexture(text[0], NULL, NULL, &pos[0].w, &pos[0].h);
		pos[0].x = 500 - (pos[0].w / 2);
		pos[0].y = 400;

		SDL_SetRenderDrawColor(Game::renderer, 0, 0, 255, 255);
		SDL_RenderClear(Game::renderer);
		SDL_RenderCopy(Game::renderer, text[0], NULL, &pos[0]);
		SDL_RenderPresent(Game::renderer);
		SDL_Event eventt;
		int flag = 0;
		bool f2 = true;
		while (f2) {
			time = SDL_GetTicks();
			SDL_PollEvent(&eventt);
			switch (eventt.type)
			{
			case SDL_QUIT:
				flag = 2;
				f2 = false;
				break;
			case SDL_KEYDOWN:
				if (eventt.key.keysym.sym == SDLK_ESCAPE) {
					flag = 1;
					f2 = false;
				}
				break;
			case SDL_MOUSEMOTION:
				x = eventt.motion.x;
				y = eventt.motion.y;
				for (int i = 0; i < 1; i++) {
					if ((x >= pos[i].x) && (x <= pos[i].x + pos[i].w) && (y >= pos[i].y) && (y <= pos[i].y + pos[i].h)) {
						if (!select[i]) {
							select[i] = 1;
							menu[i] = TTF_RenderText_Solid(font, label[i], color[1]);
							text[i] = SDL_CreateTextureFromSurface(Game::renderer, menu[i]);
							SDL_FreeSurface(menu[i]);
						}
					}
					else {
						if (select[i]) {
							select[i] = 0;
							menu[i] = TTF_RenderText_Solid(font, label[i], color[0]);
							text[i] = SDL_CreateTextureFromSurface(Game::renderer, menu[i]);
							SDL_FreeSurface(menu[i]);
						}
					}
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				x = eventt.button.x;
				y = eventt.button.y;
				for (int i = 0; i < 1; i++) {
					if ((x >= pos[i].x) && (x <= pos[i].x + pos[i].w) && (y >= pos[i].y) && (y <= pos[i].y + pos[i].h)) {
						flag = i + 3;
						f2 = false;
						break;
					}
				}
				break;
			default:
				break;
			}
			if (flag == 1) {
				Game::isRunning = true;
				SDL_Delay(1000);
				return true;
				break;
			}
			else if (flag == 2) {
				Game::isRunning = false;
				SDL_Delay(1000);
				return true;
				break;
			}
			else if (flag == 3) {
				if (posi->money >= 40) {
					posi->money -= 40;
					posi->score += 150;
				}
				
				SDL_Delay(2000);
				return true;
				break;
			}
			else {
				SDL_RenderClear(Game::renderer);
				SDL_RenderCopy(Game::renderer, text[0], NULL, &pos[0]);
				SDL_RenderPresent(Game::renderer);
				ctime = SDL_GetTicks() - time;
				if (ctime < (1000 / fps)) {
					SDL_Delay((1000 / fps) - ctime);
				}
			}
		}
	}
};
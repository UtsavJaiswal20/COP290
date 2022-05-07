#pragma once
#include "SDL_ttf.h"
#include "SDL_image.h"
#include "SDL.h"
#include "SDL_mixer.h"
#include "../Game.h"

class PauseMenu
{
public:
	SDL_Rect pos[3];
	const char* label[3] = { "RESUME", "INSTRUCTIONS", "EXIT"};
	TTF_Font* font;
	SDL_Color color[2];
	SDL_Texture* text[3];
	SDL_Surface* menu[3];
	Uint32 time, ctime;
	int fps;
	int x, y;
	bool select[4];
	SDL_Surface* name2;
	SDL_Texture* tex2;
	SDL_Rect nrect2, brect;
	SDL_Surface* mbutton;
	SDL_Texture* btex;

	PauseMenu() {
		//SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 255, 0, 255));
		color[0] = { 255, 239, 130 , 255 };
		color[1] = { 239, 211, 69, 255 };

		fps = 50;

		select[0] = false;
		select[1] = false;
		select[2] = false;
		select[3] = false;

		x = y = 0;
		time = ctime = 0;

		font = TTF_OpenFont("Resources/Sample.ttf", 55);

		brect = { 700, 560, 28, 28 };

		name2 = TTF_RenderText_Solid(font, "ANDHA DEPRESSION", color[0]);
		tex2 = SDL_CreateTextureFromSurface(Game::renderer, name2);
		SDL_FreeSurface(name2);
		SDL_QueryTexture(tex2, NULL, NULL, &nrect2.w, &nrect2.h);
		nrect2.x = 400 - (nrect2.w / 2);
		nrect2.y = 40;


		font = TTF_OpenFont("Resources/Sample.ttf", 30);

		mbutton = IMG_Load("Resources/Music_on.png");
		btex = SDL_CreateTextureFromSurface(Game::renderer, mbutton);
		SDL_FreeSurface(mbutton);

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

		pos[0].x = 400 - (pos[0].w / 2);
		pos[0].y = 400;
		pos[1].x = 400 - (pos[1].w / 2);
		pos[1].y = 420 + pos[0].h;
		pos[2].x = 400 - (pos[2].w / 2);
		pos[2].y = 440 + pos[0].h + pos[1].h;

		SDL_SetRenderDrawColor(Game::renderer, 130, 149, 75, 127);
		SDL_RenderClear(Game::renderer);
		SDL_RenderCopy(Game::renderer, btex, NULL, &brect);
		SDL_RenderCopy(Game::renderer, tex2, NULL, &nrect2);
		SDL_RenderCopy(Game::renderer, text[0], NULL, &pos[0]);
		SDL_RenderCopy(Game::renderer, text[1], NULL, &pos[1]);
		SDL_RenderCopy(Game::renderer, text[2], NULL, &pos[2]);
		SDL_RenderPresent(Game::renderer);
	}
	~PauseMenu() {}
	int makepmenu() {
		SDL_Event event;
		while (1) {
			time = SDL_GetTicks();
			while (SDL_PollEvent(&event)) {
				switch (event.type)
				{
				case SDL_QUIT:
					Game::isRunning = false;
					SDL_StopTextInput();
					return 0;
				case SDL_MOUSEMOTION:
					x = event.motion.x;
					y = event.motion.y;
					for (int i = 0; i < 3; i++) {
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
					x = event.button.x;
					y = event.button.y;
					for (int i = 0; i < 2; i++) {
						if ((x >= pos[i].x) && (x <= pos[i].x + pos[i].w) && (y >= pos[i].y) && (y <= pos[i].y + pos[i].h)) {
							//if (i == 0) {
								/*Mix_FreeChunk(Game::music);
								Game::music = NULL;
								Mix_CloseAudio();
								Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096);
								Game::music = Mix_LoadWAV("Resources/Audiosample2.wav");
								Mix_PlayChannel(-1, Game::music, -1);*/
							//}
							return i;
						}
					}
					//if ((x >= brect.x) && (x <= brect.x + brect.w) && (y >= brect.y) && (y <= brect.y + brect.h)) {
						/*if (select[3]) {
							select[3] = false;
							Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096);
							Game::music = Mix_LoadWAV("Resources/Audiosample1.wav");
							Mix_PlayChannel(-1, Game::music, -1);
							mbutton = IMG_Load("Resources/Music_on.png");
							btex = SDL_CreateTextureFromSurface(Game::renderer, mbutton);
							SDL_FreeSurface(mbutton);
						}
						else {
							select[3] = true;
							Mix_FreeChunk(Game::music);
							Game::music = NULL;
							Mix_CloseAudio();
							mbutton = IMG_Load("Resources/Music_off.png");
							btex = SDL_CreateTextureFromSurface(Game::renderer, mbutton);
							SDL_FreeSurface(mbutton);
						}*/
					//}
					break;
				case SDL_KEYDOWN:
					//std::cout << "3" << std::endl;
					if (event.key.keysym.sym == SDLK_ESCAPE) {
						return 0;
					}
					break;
				default:
					break;
				}
			}
			//std::cout << "hello" << std::endl;
			SDL_RenderClear(Game::renderer);
			SDL_RenderCopy(Game::renderer, btex, NULL, &brect);
			SDL_RenderCopy(Game::renderer, tex2, NULL, &nrect2);
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
	void clean() {
		SDL_DestroyTexture(btex);
		SDL_DestroyTexture(tex2);
		SDL_DestroyTexture(text[0]);
		SDL_DestroyTexture(text[1]);
		SDL_DestroyTexture(text[2]);
	}
};
#pragma once
#include "SDL_ttf.h"
#include "SDL_image.h"
#include "SDL.h"
#include "SDL_mixer.h"
#include "../Game.h"
#include <cstring>
#include <string>

class StartMenu
{
public:
	SDL_Rect pos[2];
	const char* label[2] = { "START", "EXIT" };
	TTF_Font* font;
	SDL_Color color[3];
	SDL_Texture* text[2];
	SDL_Surface* menu[2];
	Uint32 time, ctime;
	int fps;
	int x, y;
	bool select[4];
	SDL_Surface* name;
	SDL_Surface* name1;
	SDL_Surface* name2;
	SDL_Surface* namesurf;
	SDL_Texture* tex;
	SDL_Texture* tex1;
	SDL_Texture* tex2;
	SDL_Texture* nametex;
	SDL_Rect nrect, nrect1, nrect2, namerect, brect;
	SDL_Surface* mbutton;
	SDL_Texture* btex;

	StartMenu() {
		//SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 255, 0, 255));
		color[0] = { 255, 239, 130 , 255 };
		color[1] = { 239, 211, 69, 255 };
		color[2] = { 0, 0, 0, 255 };

		fps = 50;

		select[0] = false;
		select[1] = false;
		select[2] = false;
		select[3] = false;

		x = y = 0;
		time = ctime = 0;

		font = TTF_OpenFont("Resources/Sample.ttf", 65);

		brect = { 900, 720, 42, 42 };

		name2 = TTF_RenderText_Solid(font, "LIFE IN IIT", color[2]);
		tex2 = SDL_CreateTextureFromSurface(Game::renderer, name2);
		SDL_FreeSurface(name2);
		SDL_QueryTexture(tex2, NULL, NULL, &nrect2.w, &nrect2.h);
		nrect2.x = 500 - (nrect2.w / 2);
		nrect2.y = 60;


		font = TTF_OpenFont("Resources/Sample.ttf", 40);

		name1 = TTF_RenderText_Solid(font, Game::playerr, color[0]);
		tex1 = SDL_CreateTextureFromSurface(Game::renderer, name1);
		SDL_FreeSurface(name1);
		SDL_QueryTexture(tex1, NULL, NULL, &nrect1.w, &nrect1.h);
		nrect1.x = 130;
		nrect1.y = 260;

		name = TTF_RenderText_Solid(font, Game::player_name, color[0]);
		tex = SDL_CreateTextureFromSurface(Game::renderer, name);
		SDL_FreeSurface(name);
		SDL_QueryTexture(tex, NULL, NULL, &nrect.w, &nrect.h);
		nrect.x = 130;
		nrect.y = 270 + nrect1.h;
		namerect.w = nrect.w + 24;
		namerect.h = nrect.h + 8;
		namerect.x = nrect.x - 12;
		namerect.y = nrect.y - 4;
		namesurf = IMG_Load("Resources/Gray.png");
		nametex = SDL_CreateTextureFromSurface(Game::renderer, namesurf);
		SDL_FreeSurface(namesurf);

		mbutton = IMG_Load("Resources/Music_on.png");
		btex = SDL_CreateTextureFromSurface(Game::renderer, mbutton);
		SDL_FreeSurface(mbutton);

		menu[0] = TTF_RenderText_Solid(font, label[0], color[0]);
		text[0] = SDL_CreateTextureFromSurface(Game::renderer, menu[0]);
		SDL_FreeSurface(menu[0]);
		menu[1] = TTF_RenderText_Solid(font, label[1], color[0]);
		text[1] = SDL_CreateTextureFromSurface(Game::renderer, menu[1]);
		SDL_FreeSurface(menu[1]);
		SDL_QueryTexture(text[0], NULL, NULL, &pos[0].w, &pos[0].h);
		SDL_QueryTexture(text[1], NULL, NULL, &pos[1].w, &pos[1].h);

		pos[0].x = 500 - (pos[0].w / 2);
		pos[0].y = 450;
		pos[1].x = 500 - (pos[1].w / 2);
		pos[1].y = 470 + pos[0].h;
		//std::cout << "1.2" << std::endl;

		SDL_SetRenderDrawColor(Game::renderer, 130, 149, 75, 255);
		SDL_RenderClear(Game::renderer);
		SDL_RenderCopy(Game::renderer, nametex, NULL, &namerect);
		SDL_RenderCopy(Game::renderer, btex, NULL, &brect);
		SDL_RenderCopy(Game::renderer, tex, NULL, &nrect);
		SDL_RenderCopy(Game::renderer, tex1, NULL, &nrect1);
		SDL_RenderCopy(Game::renderer, tex2, NULL, &nrect2);
		SDL_RenderCopy(Game::renderer, text[0], NULL, &pos[0]);
		SDL_RenderCopy(Game::renderer, text[1], NULL, &pos[1]);
		//std::cout << "1.2" << std::endl;
		SDL_RenderPresent(Game::renderer);
	}
	~StartMenu() {}
	int makemenu() {
		SDL_Event event;
		while (1) {
			SDL_StartTextInput();
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
					for (int i = 0; i < 2; i++) {
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
							SDL_StopTextInput();
							if (i == 0) {
								Mix_FreeChunk(Game::music);
								Game::music = NULL;
								Mix_CloseAudio();
								Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096);
								Game::music = Mix_LoadWAV("Resources/Audiosample.wav");
								Mix_PlayChannel(-1, Game::music, -1);
							}
							return i;
						}
					}
					if ((x >= namerect.x) && (x <= namerect.x + namerect.w) && (y >= namerect.y) && (y <= namerect.y + namerect.h)) {
						Game::player_name = "";
						name = TTF_RenderText_Solid(font, Game::player_name, color[0]);
						tex = SDL_CreateTextureFromSurface(Game::renderer, name);
						SDL_FreeSurface(name);
						select[2] = 1;
						namesurf = IMG_Load("Resources/Black.png");
						nametex = SDL_CreateTextureFromSurface(Game::renderer, namesurf);
						SDL_FreeSurface(namesurf);
						//std::cout << "1" << std::endl;
					}
					else {
						//std::cout << "2" << std::endl;
						select[2] = 0;
						namesurf = IMG_Load("Resources/Gray.png");
						nametex = SDL_CreateTextureFromSurface(Game::renderer, namesurf);
						SDL_FreeSurface(namesurf);
					}
					if ((x >= brect.x) && (x <= brect.x + brect.w) && (y >= brect.y) && (y <= brect.y + brect.h)) {
						if (select[3]) {
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
						}
					}
					break;
				case SDL_KEYDOWN:
					//std::cout << "3" << std::endl;
					if (event.key.keysym.sym == SDLK_ESCAPE) {
						Game::isRunning = false;
						SDL_StopTextInput();
						return 0;
					}
					if ((select[2] == 1)) {
						/*std::cout << "4" << std::endl;
						const char* cc = SDL_GetScancodeName(event.key.keysym.scancode);
						std::cout << cc << std::endl;
						const char* c = cc;
						const char* nammmm = Game::player_name;
						char* str1 = (char*)c;
						char* str2 = (char*)nammmm;
						char* str3 = (char*)malloc(1 + strlen(str1) + strlen(str2));
						strcpy(str3, c);
						strcat(str3, nammmm);
						Game::player_name = (const char*)str3;*/
						//std::cout << str3 << std::endl;
						name = TTF_RenderText_Solid(font, Game::player_name, color[0]);
						tex = SDL_CreateTextureFromSurface(Game::renderer, name);
						SDL_FreeSurface(name);
						SDL_QueryTexture(tex, NULL, NULL, &nrect.w, &nrect.h);
					}
					break;
				default:
					break;
				}
			}
			//std::cout << "hello" << std::endl;
			SDL_RenderClear(Game::renderer);
			SDL_RenderCopy(Game::renderer, nametex, NULL, &namerect);
			SDL_RenderCopy(Game::renderer, btex, NULL, &brect);
			SDL_RenderCopy(Game::renderer, tex, NULL, &nrect);
			SDL_RenderCopy(Game::renderer, tex1, NULL, &nrect1);
			SDL_RenderCopy(Game::renderer, tex2, NULL, &nrect2);
			SDL_RenderCopy(Game::renderer, text[0], NULL, &pos[0]);
			SDL_RenderCopy(Game::renderer, text[1], NULL, &pos[1]);
			SDL_RenderPresent(Game::renderer);
			ctime = SDL_GetTicks() - time;
			if (ctime < (1000 / fps)) {
				SDL_Delay((1000 / fps) - ctime);
			}
		}
	}
private:


};
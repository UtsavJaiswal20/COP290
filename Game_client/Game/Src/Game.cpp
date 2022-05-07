#include "Game.h"
#include "Textures.h"
#include "Map.h"
#include "EntityComponentSystem/Components.h"
#include "Vector2.h"
#include "Collision.h"
#include "Menus/PauseMenu.h"
#include "SDL.h"
#include <string>

Map* map;
Manager manager;

//PauseMenu* pmenu;
//int ptemp;

SDL_Renderer* Game::renderer;
SDL_Event Game::event;
const char* Game::player_name = "NAMELESSS WONDER";
const char* Game::playerr = "Type player name:";
Mix_Chunk* Game::music;

bool Game::isRunning = false;
int Game::sscore = 0;

SDL_Rect Game::cam = {0, 0, 1000, 800};

auto& player(manager.addEntity());

Game::Game()
{}

Game::~Game()
{}

void Game::initialize(const char* Windowtitle, int width, int height, bool isfullscreen)
{
	sscore = 0;
	int flag = 0;	

	if (isfullscreen){
		flag = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING)==0)
	{
		window = SDL_CreateWindow(Windowtitle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flag);
		SDL_GetWindowSize(window, &width, &height);
		//cam = { 100, 0, width - 100, height };
		//std::cout << width << " " << height << std::endl;
		renderer = SDL_CreateRenderer(window, -1, 0);

		if (renderer){
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		}

		isRunning = true;
	}

	map = new Map("Resources/tileset2.png", 4, 32);

	map->makemap("Resources/tilemap2.map", 70, 45);

	player.addComponent<PositionComponent>(1);
	player.addComponent<SpriteComponent>("Resources/Player.png", true);
	player.addComponent<KeyboardInputs>();
	player.addComponent<Collider>("player");
	player.addGroup(groupplayer1);

}

auto& tiles(manager.getGroup(Game::groupmap));
auto& player1(manager.getGroup(Game::groupplayer1));
auto& pcol(manager.getGroup(Game::groupcollider));

void Game::handleEvents()
{
	bool exit = false;
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT :
		isRunning = false;
		break;

	case SDL_KEYDOWN:
		if (event.key.keysym.sym == SDLK_ESCAPE && exit == false ) {
			exit = pmenu();			
		}
		break;
	default:
		isRunning = true;
		break;
	}
}

bool Game::pmenu(){
	SDL_Rect pos[2]{};
	const char* label[2] = { "RESUME", "EXIT" };
	TTF_Font* font;
	font = TTF_OpenFont("Resources/Sample.ttf", 40);
	SDL_Color color[2] = { { 255, 255, 255, 255 }, { 127, 127, 127, 255 } };
	SDL_Texture* text[2]{};
	SDL_Surface* menu[2]{};
	Uint32 time = 0;
	Uint32 ctime = 32;
	int fps = 50;
	int x = 0;
	int y = 0;
	bool select[2] = { false, false };
	menu[0] = TTF_RenderText_Solid(font, label[0], color[0]);
	text[0] = SDL_CreateTextureFromSurface(renderer, menu[0]);
	SDL_FreeSurface(menu[0]);
	menu[1] = TTF_RenderText_Solid(font, label[1], color[0]);
	text[1] = SDL_CreateTextureFromSurface(renderer, menu[1]);
	SDL_FreeSurface(menu[1]);
	SDL_QueryTexture(text[0], NULL, NULL, &pos[0].w, &pos[0].h);
	SDL_QueryTexture(text[1], NULL, NULL, &pos[1].w, &pos[1].h);
	pos[0].x = 500 - (pos[0].w / 2);
	pos[0].y = 400;
	pos[1].x = 500 - (pos[1].w / 2);
	pos[1].y = 420 + pos[0].h;

	SDL_SetRenderDrawColor(renderer, 130, 149, 75, 255);
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, text[0], NULL, &pos[0]);
	SDL_RenderCopy(renderer, text[1], NULL, &pos[1]);
	SDL_RenderPresent(renderer);
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
				flag = 2;
				f2 = false;
			}
			else if (eventt.key.keysym.sym == SDLK_w) {
				flag = 1;
				f2 = false;
			}
			else if (eventt.key.keysym.sym == SDLK_s) {
				flag = 2;
				f2 = false;
			}
			break;;
		case SDL_MOUSEMOTION:
			x = eventt.motion.x;
			y = eventt.motion.y;
			for (int i = 0; i < 2; i++) {
				if ((x >= pos[i].x) && (x <= pos[i].x + pos[i].w) && (y >= pos[i].y) && (y <= pos[i].y + pos[i].h)) {
					if (!select[i]) {
						select[i] = 1;
						menu[i] = TTF_RenderText_Solid(font, label[i], color[1]);
						text[i] = SDL_CreateTextureFromSurface(renderer, menu[i]);
						SDL_FreeSurface(menu[i]);
					}
				}
				else {
					if (select[i]) {
						select[i] = 0;
						menu[i] = TTF_RenderText_Solid(font, label[i], color[0]);
						text[i] = SDL_CreateTextureFromSurface(renderer, menu[i]);
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
					flag = i + 1;
					f2 = false;
					break;
				}
			}
			break;
		default:
			break;
		}
		if (flag == 1) {
			isRunning = true;
			SDL_Delay(1000);
			return true;
			break;
		}
		else if (flag == 2) {
			isRunning = false;
			SDL_Delay(1000);
			return false;
			break;
		}
		else {
			SDL_RenderClear(renderer);
			SDL_RenderCopy(renderer, text[0], NULL, &pos[0]);
			SDL_RenderCopy(renderer, text[1], NULL, &pos[1]);
			SDL_RenderPresent(renderer);
			ctime = SDL_GetTicks() - time;
			if (ctime < (1000 / fps)) {
				SDL_Delay((1000 / fps) - ctime);
			}
		}
	}
}

void Game::update()
{
	SDL_Rect pcoll = player.getComponent<Collider>().wall;
	Vector2 pposi = player.getComponent<PositionComponent>().pos;

	manager.refresh();
	manager.update();

	for (auto& c : pcol) {
		SDL_Rect ccoll = c->getComponent<Collider>().wall;
		if (Collision::iscollision(pcoll, ccoll)) {
			player.getComponent<PositionComponent>().pos = pposi;
		}
	}

	cam.x = player.getComponent<PositionComponent>().pos.x - 400;
	cam.y = player.getComponent<PositionComponent>().pos.y - 320;

	if (cam.x < 0) {
		cam.x = 0;
	}
	if (cam.x + cam.w>=70*2*2*32) {
		cam.x = 70*2*32*2 - cam.w;
	}
	if (cam.y < 0) {
		cam.y = 0;
	}
	if (cam.y + cam.h>=45*2*2*32) {
		cam.y = 45*2*2*32 - cam.h;
	}

}

void Game::render()
{
	SDL_RenderClear(renderer);
	for (auto& t : tiles) {
		t->draw();
	}
	/*for (auto& pc : pcol) {
		pc->draw();
	}*/

	for (auto& p1 : player1) {
		p1->draw();
	}
	SDL_Rect srect = { 0, 0, 200, 200 };
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	TTF_Font* font;
	const char* label[5] = { "SCORE", "Popularity", "Energy", "Money", "Hygiene" };
	std::string score[5];
	score[0] = std::to_string(player.getComponent<PositionComponent>().score);
	sscore = player.getComponent<PositionComponent>().score;
	score[1] = std::to_string(player.getComponent<PositionComponent>().popularity);
	score[2] = std::to_string(player.getComponent<PositionComponent>().energy);
	score[3] = std::to_string(player.getComponent<PositionComponent>().money);
	score[4] = std::to_string(player.getComponent<PositionComponent>().hygiene);
	std::string temp;
	//std::cout << label[0] << std::endl;
	//std::cout << label[1] << std::endl;
	//std::cout << label[2] << std::endl;
	//std::cout << label[3] << std::endl;
	//std::cout << label[4] << std::endl;
	
	//std::cout << label[0] << std::endl;
	SDL_Rect srrect[5]{};
	SDL_Color color[2] = { {0, 0, 0, 255}, {0, 0, 255, 255} };
	SDL_Texture* texttt[5]{};
	SDL_Surface* menu[5]{};
	font = TTF_OpenFont("Resources/Sample.ttf", 30);
	//std::cout << label[0] << std::endl;
	temp = (std::string)label[0] + " : " + score[0];
	label[0] = temp.c_str();
	menu[0] = TTF_RenderText_Solid(font, label[0], color[1]);
	texttt[0] = SDL_CreateTextureFromSurface(renderer, menu[0]);
	SDL_FreeSurface(menu[0]);
	SDL_QueryTexture(texttt[0], NULL, NULL, &srrect[0].w, &srrect[0].h);
	srrect[0].x = 10 + srect.x;
	srrect[0].y = 10 + srect.y;
	font = TTF_OpenFont("Resources/Sample.ttf", 20);
	//std::cout << srrect[0].x << " " << srrect[0].y << " " << srrect[0].w << " " << srrect[0].h << std::endl;
	//std::cout << label[1] << std::endl;
	temp = (std::string)label[1] + " : " + score[1];
	label[1] = temp.c_str();
	menu[1] = TTF_RenderText_Solid(font, label[1], color[0]);
	texttt[1] = SDL_CreateTextureFromSurface(renderer, menu[1]);
	SDL_FreeSurface(menu[1]);
	SDL_QueryTexture(texttt[1], NULL, NULL, &srrect[1].w, &srrect[1].h);
	srrect[1].x = 10 + srect.x;
	srrect[1].y = srrect[0].y + srrect[0].h + 5;

	//std::cout << label[2] << std::endl;
	temp = (std::string)label[2] + " : " + score[2];
	label[2] = temp.c_str();
	menu[2] = TTF_RenderText_Solid(font, label[2], color[0]);
	texttt[2] = SDL_CreateTextureFromSurface(renderer, menu[2]);
	SDL_FreeSurface(menu[2]);
	SDL_QueryTexture(texttt[2], NULL, NULL, &srrect[2].w, &srrect[2].h);
	srrect[2].x = 10 + srect.x;
	srrect[2].y = srrect[1].y + srrect[1].h + 5;

	//std::cout << label[3] << std::endl;
	temp = (std::string)label[3] + " : " + score[3];
	label[3] = temp.c_str();
	menu[3] = TTF_RenderText_Solid(font, label[3], color[0]);
	texttt[3] = SDL_CreateTextureFromSurface(renderer, menu[3]);
	SDL_FreeSurface(menu[3]);
	SDL_QueryTexture(texttt[3], NULL, NULL, &srrect[3].w, &srrect[3].h);
	srrect[3].x = 10 + srect.x;
	srrect[3].y = srrect[2].y + srrect[2].h + 5;

	//std::cout << label[4] << std::endl;
	temp = (std::string)label[4] + " : " + score[4];
	label[4] = temp.c_str();
	menu[4] = TTF_RenderText_Solid(font, label[4], color[0]);
	texttt[4] = SDL_CreateTextureFromSurface(renderer, menu[4]);
	SDL_FreeSurface(menu[4]);
	SDL_QueryTexture(texttt[4], NULL, NULL, &srrect[4].w, &srrect[4].h);
	srrect[4].x = 10 + srect.x;
	srrect[4].y = srrect[3].y + srrect[3].h + 5;
	/*for (int i = 1; i < 5; i++) {
		menu[i] = TTF_RenderText_Solid(font, label[i], color[1]);
		texttt[i] = SDL_CreateTextureFromSurface(Game::renderer, menu[i]);
		SDL_FreeSurface(menu[i]);
		SDL_QueryTexture(texttt[i], NULL, NULL, &srrect[i].w, &srrect[i].h);
		srrect[i].x = 10 + srect.x;
		srrect[i].y = srrect[i].y + srrect[i-1].h + 2;
		std::cout << srrect[i].x << " " << srrect[i].y << " " << srrect[i].w << " " << srrect[i].h << std::endl;
	}*/
	SDL_RenderFillRect(renderer, &srect);
	//SDL_RenderClear(Game::renderer);
	SDL_RenderCopy(renderer, texttt[0], NULL, &srrect[0]);
	SDL_RenderCopy(renderer, texttt[1], NULL, &srrect[1]);
	SDL_RenderCopy(renderer, texttt[2], NULL, &srrect[2]);
	SDL_RenderCopy(renderer, texttt[3], NULL, &srrect[3]);
	SDL_RenderCopy(renderer, texttt[4], NULL, &srrect[4]);
	SDL_RenderPresent(renderer);
	//SDL_Delay(10000);
}

void Game::clean()
{
	Mix_FreeChunk(music);
	music = NULL;
	Mix_CloseAudio();
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}
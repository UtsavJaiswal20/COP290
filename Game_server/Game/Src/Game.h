#pragma once

#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include <vector>

class Collider;

class Game
{

public:
	Game();
	~Game();
	void initialize(const char* Windowtitle, int width, int height, bool isfullscreen);
	void handleEvents();
	void update();
	bool isrunning(){ 
		return isRunning; 
	}
	void render();
	void clean();
	bool pmenu();
	static const char* player_name;
	static const char* playerr;
	static SDL_Renderer* renderer;
	static SDL_Event event;
	static bool isRunning;
	static int sscore;
	static SDL_Rect cam;
	static Mix_Chunk* music;
	enum GroupLabel : std::size_t {
		groupmap,
		groupplayer1,
		groupplayer2,
		groupcollider
	};
	SDL_Window* window;
private:
	int count = 0;
	
};
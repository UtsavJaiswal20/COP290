#pragma once

#include "SDL.h"

class Collider;

class Collision
{
public:
	static bool iscollision(const SDL_Rect &ra, const SDL_Rect &rb);
	static bool iscollision(const Collider &colA, const Collider &colB);
};
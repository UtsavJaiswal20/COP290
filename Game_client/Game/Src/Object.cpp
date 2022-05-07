#include "Object.h"
#include "Textures.h"

Object::Object(char* texture, int x, int y) 
{
	objtex = Textures::maketexture(texture);
	xc = x;
	yc = y;
}

void Object::update()
{	
	xc += 2;
	yc++;

	srect.x = srect.y = 0;
	srect.h = srect.w = 32;

	drect.x = xc;
	drect.y = yc;
	drect.h = drect.w = 64;
}

void Object::render()
{
	SDL_RenderCopy(Game::renderer, objtex, &srect, &drect);
}

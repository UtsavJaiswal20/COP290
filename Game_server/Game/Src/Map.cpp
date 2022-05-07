#include "Map.h"
#include <fstream>
#include "Game.h"
#include "EntityComponentSystem/EntitySystem.h"
#include "EntityComponentSystem/Components.h"

extern Manager manager;

Map::Map(const char* mfile, int mscale, int mtsize) : mapfile(mfile), mapscale(mscale), maptilesize(mtsize)
{
	scaledsize = mscale * mtsize;
}

Map::~Map()
{
}

void Map::makemap(std::string name, int row, int col)
{
	char tile;
	std::fstream mfile;
	mfile.open(name);

	int s = 0;
	int sy, sx;

	for (int j = 0; j < col; j++) {
		for (int i = 0; i < row; i++) {
			s = 0;
			mfile.get(tile);
			if (tile == '-') {
				mfile.ignore();
				mfile.ignore();
			}
			else {
				while (tile != ',') {
					s = 10 * s + atoi(&tile);
					mfile.get(tile);
				}
				sx = s % 4;
				sy = (s - sx) / 4;
				sx *= maptilesize;
				sy *= maptilesize;
				AddTile(sx, sy, i * scaledsize, j * scaledsize);
			}
			std::cout << s << " " << i << " " << j << std::endl;
		}
		mfile.ignore();
	}
	mfile.ignore();
	
	for (int j = 0; j < col; j++) {
		for (int i = 0; i < row; i++) {
			s = 0;
			sx = 0;
			sy = 0;
			mfile.get(tile);
			//std::cout << tile << std::endl;
			if (tile == '-') {
				s = -1;
				mfile.ignore();
				mfile.ignore();
			}
			else {
				while (tile != ',') {
					s = 10 * s + atoi(&tile);
					mfile.get(tile);
				}
				sx = s % 4;
				sy = (s - sx) / 4;
				//std::cout << s << " " << sx << " " << sy << std::endl;
				sx *= maptilesize;
				sy *= maptilesize;
				AddTile(sx, sy, i * scaledsize, j * scaledsize);
			}
			std::cout << s << " " << i << " " << j << std::endl;
		}
		mfile.ignore();
	}
	mfile.ignore();
	for (int j = 0; j < col; j++) {
		for (int i = 0; i < row; i++) {
			mfile.get(tile);
			if (tile == '-') {
				mfile.ignore();
				mfile.ignore();
			}
			else {
				while (tile != ',') {
					s = 10 * s + atoi(&tile);
					mfile.get(tile);
				}
				auto& colll(manager.addEntity());
				colll.addComponent<Collider>("ground", i * scaledsize, j * scaledsize, scaledsize);
				colll.addGroup(Game::groupcollider);
			}
		}
	}

	mfile.close();
}

void Map::AddTile(int sx, int sy, int x, int y) {
	auto& tile(manager.addEntity());
	tile.addComponent<MapTile>(sx, sy, x, y, maptilesize, mapscale, mapfile);
	tile.addGroup(Game::groupmap);
}
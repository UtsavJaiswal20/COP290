#pragma once

#include <string>

class Map
{
public:
	Map(const char* mfile, int mscale, int mtsize);
	~Map();
	void makemap(std::string name, int row, int col);
	void AddTile(int sx, int sy, int x, int y);
private:
	const char* mapfile;
	int mapscale;
	int maptilesize;
	int scaledsize;
};
#pragma once
#include "ElementGame.h"
#include "tinyManager.h"

class Map :
	public ElementGame
{
private:
	const char* fileTileset;
	const char* fileMapCollision;

	tinyManager::Tileset tileset;

	array2D *mapCollision;

	tinyManager* tManager;

public:
	Map();
	~Map();

	void Init(int x, int y, const char* fileMap, const char* tiles, const char* fileMapColli, int srcX, int srcY, int w, int h);
	void Render();

	int getMapa(int x, int y);
};


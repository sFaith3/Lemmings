#pragma once
#include "ElementGame.h"
#include "tinyManager.h"

class Map :
	public ElementGame
{
private:
	const char* fileTileset;
	bool tmx;

	array2D *mapa;
	tinyManager::Tileset tileset;

	tinyManager* tManager;

public:
	Map();
	~Map();

	void Init(int x, int y, bool tmx, const char* level, const char* tileset, int srcX, int srcY, int w, int h);
	void Render();

	int getMapa();
};


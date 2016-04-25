#pragma once
#include "ElementGame.h"
#include "tinyManager.h"

class Map :
	public ElementGame
{
private:
	const char* fileMap;
	const char* fileTileset;

	vector<tinyManager::Tileset> tilesets;
	vector<tinyManager::Tileset>::iterator itTilesets;

	int widthMap;
	int sizeTiles;

	//array2D *mapCollision;
	vector <vector<int> > mapCollision;

	tinyManager* tManager;

public:
	Map();
	~Map();

	void Init(int x, int y, const char* fileMap, int numLayers, const char* fileTileset, int numTilesets, int srcX, int srcY, int w, int h);
	void Render();

	int GetMapa(int x, int y);
	int GetSizeTile();

	void move(bool dreta);
};


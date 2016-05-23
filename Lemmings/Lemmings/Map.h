#pragma once
#include "ElementGame.h"
#include "tinyManager.h"

class Map :
	public ElementGame
{
private:
	const char* fileMap;
	Sint32 idFileMap;
	const char* fileTileset;
	Sint32 idFileTileset;

	vector<tinyManager::Tileset> tilesets;
	vector<tinyManager::Tileset>::iterator itTilesets;

	int widthMap;
	int sizeTiles;

	vector <vector<int> > mapCollision;

	tinyManager* tManager;

public:
	Map();
	~Map();

	void init(int x, int y, const char* fileMap, const char* layerCollision, int numLayers, const char* fileTileset, bool haveSpacingTileset, int numTilesets, int srcX, int srcY, int w, int h);
	void render();

	int GetMapa(int x, int y);
	void DestroyPosMapa(int x, int y);

	int GetSizeTile();
};


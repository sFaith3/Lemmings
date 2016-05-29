#pragma once
#include "ElementGame.h"
#include "tinyManager.h"

class Map :
	public ElementGame
{
private:
	bool mapTmx;

	const char* fileMap;
	Sint32 idFileMap;

	string rutaTilesets; // Directori on es troben els tilesets a utilitzar per a X arxiu TMX.
	vector<tinyManager::Tileset*> tilesets;
	vector<tinyManager::Tileset*>::iterator itTilesets;

	int sizeTile;

	vector <vector<int> > mapCollision;

	tinyManager* tManager;

public:
	Map();
	~Map();

	void init(int x, int y, bool mapTmx, const char* fileMap, const char* layerCollision, int numLayers, const char* rutaTilesets, bool haveSpacingTileset, int numTilesets, int srcX, int srcY, int w, int h);
	void render();

	int GetPosX();
	int GetPosY();

	int GetMapa(int x, int y);
	void DestroyPosMapa(int x, int y);
	void CrearPosMapa(int x, int y, int tipo);

	int GetWidthMap();
	int GetHeightMap();
	int GetSizeTile();
};


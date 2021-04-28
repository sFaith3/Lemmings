#pragma once
#include "ElementGame.h"
#include "tinyManager.h"

class Map :
	public ElementGame
{
private:
	bool mapTmx; // Indica si el mapa a carregar és una img normal, com un background, que no influeix en el joc. O un mapa que prové d'un arxiu tmx.

	Sint32 idFileMap;

	string rutaTilesets; // Directori on es troben els tilesets a utilitzar per a X arxiu TMX.
	vector<tinyManager::Tileset*> tilesets;
	vector<tinyManager::Tileset*>::iterator itTilesets;

	int sizeTile; // Mesura d'una tile. Per tal de calcular la posició dels elements que interactuen amb el mapa de col·lisions.

	vector <vector<int> > mapCollision; // Vector amb les dimensions X-Y del mapa de col·lisions. S'utilitza per a veure si a X punt del mapa hi ha cap impediment per al desplaçament dels Lemmings.

	tinyManager* tManager;

public:
	Map();
	~Map();

	void init(int x, int y, bool mapTmx, const char* fileMap, const char* layerCollision, int numLayers, const char* rutaTilesets, bool haveSpacingTileset, int numTilesets, int srcX, int srcY, int w, int h);
	void render();

	int GetWidthMap();
	int GetHeightMap();
	int GetSizeTile();

	void SetPositionTiles(int x, int y);
	void SetScaleTiles(float x, float y);

	int GetMapa(int x, int y);
	void DestroyPosMapa(int x, int y);
	void CrearPosMapa(int x, int y, int tipo);
	void CrearPosMapa(int x, int y, int tipo, int layer, int idTile);
};


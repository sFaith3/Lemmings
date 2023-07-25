#pragma once
#include "ElementGame.h"
#include "tinyManager.h"

class Map :
	public ElementGame
{
private:
	bool mapTMX; // Indicates whether the map to load is a normal img, like a background, that does not influence the game.
				 // Or a map coming from a TMX file.

	Sint32 idFileMap;

	string pathTilesets; // Directory where the tilesets to use for the X TMB file are located.
	vector<tinyManager::Tileset*> tilesets;
	vector<tinyManager::Tileset*>::iterator itTilesets;

	int sizeTile; // Measurament of a tile. To calculate the position of the elements that interact with the collision map.

	vector <vector<int>> mapCollision; // Vector with the X-Y dimensions of the collision map. It is used to see if there is any
									   // impediment to the Lemmings scrolling at X point on the map.

	tinyManager* tinyManager;

public:
	Map();
	~Map();

	void init(int x, int y, bool mapTMX, const char* fileMap, const char* layerCollision, int numLayers, const char* pathTilesets, bool haveSpacingTileset, int numTilesets, int srcX, int srcY, int w, int h);
	void initMapTMX(const int x, const int y, const int numLayers, const bool haveSpacingTileset, const int numTilesets, const int srcX, const int srcY);
	void loadMapAndTilesets(const int x, const int y, const int numLayers, const bool haveSpacingTileset, const int numTilesets);
	void setTilesetImgID();
	void render();

	int GetWidthMap();
	int GetHeightMap();
	int GetSizeTile();

	void SetPositionTiles(const int x, const int y);
	void SetScaleTiles(const float x, const float y);

	int GetMap(const int x, const int y);
	void ChangeMapAtPos(const int x, const int y, const int typeCollision);
	void ChangeMapAtPos(const int x, const int y, const int typeCollision, const int idTile);
	bool isWithinRangeOfMap(const int x, const int y);
};


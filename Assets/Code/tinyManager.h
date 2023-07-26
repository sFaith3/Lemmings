#ifndef TINYMANAGER_H
#define TINYMANAGER_H

#include "TinyXML\tinyxml.h"
#include "SDL\VideoManager.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

class tinyManager
{
public:
	~tinyManager();

	static tinyManager* getInstanceTinyManager();

	class Tileset {
	public:
		struct Tile {
		private:
			int srcPosX, srcPosY; // Initial clipping point of the spritesheet.
			int dstPosX, dstPosY; // Point where it will be painted.

		public:
			Tile(int _srcPosX, int _srcPosY, int _dstPosX, int _dstPosY);

			int getSrcPosX();
			int getSrcPosY();
			int getDstPosX();
			int getDstPosY();

			void IncrementDstPos(int dstX, int dstY);
			void ChangeSrcPos(int srcX, int srcY);
		};

		~Tileset();

		void init(string pathTileset, int spacing, int width, int height, int sizeXtiles, int sizeYtiles, int tileWidth, int tileHeight);
		void addTiles(const int mapPosX, const int mapPosY, const vector <vector<int>> map, Tileset* tileset, const int numMaxTilesWidth, const int numMaxTilesHeight, const int posX, const int posY);
		void render(VideoManager* videoManager);

		string getPathTileset();
		int getSizeXTiles();
		int getSizeYTiles();
		vector <vector<Tile*>> getTiles();
		int getIdImg();

		void setScaleTiles(float x, float y);
		void setIdImg(int id);

		bool isIndexOutOfRangeInTilesAtPos(const int posX, const int posY) const;
		void addTileAtPos(int posX, int posY, int srcPosX, int srcPosY, int dstPosX, int dstPosY);
		void changeTileAtPos(const int posX, const int posY, const int newTile);
		void clippingBoxToGetSrcPositions(const int width, const int height, const int tile, int& srcPosX, int& srcPosY);

	private:
		// Tileset.
		string pathTileset;
		int idImg;
		int spacing;
		int width;
		int height;

		// Tiles.
		int tileWidth, tileHeight;
		float scaleXtile, scaleYtile;
		int sizeXtiles, sizeYtiles; // Number of rows and columns of tiles to travel the vector of vectors at those positions.
		vector <vector<Tile*>> tiles;
	};

	void Init();

	int GetMapWidth();
	int GetMapHeight();
	int GetTileSize();

	void LoadTMX(const char* fileTMX, string layerCollision);
	bool IsMapCollisionLayer(const int numLayer, TiXmlElement*& layer);
	vector <vector<int>> GetMapData(vector<vector<int>> map, const string text, string num, const int layerWidth);
	vector <vector<int>> GetLoadedMap(const int numLayer);
	vector <vector<int>> GetLoadedMapCollision();
	Tileset* GetLoadedTileset(int numTilesets, bool haveSpacing, vector <vector<int>> map, int posX, int posY);
	void DestroyTMX();

private:
	tinyManager();

	static tinyManager* tInstance;

	TiXmlDocument* doc;
	string layerCollision; // Name of the TMX layer where the collision map is located.
	int mapPosX, mapPosY; // Positions of the vector of vectors 'map'.
	int mapWidth, mapHeight;
	int tileSize; // Number of tiles the map has.
};

#endif
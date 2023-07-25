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
		void changeTileAtPos(int posX, int posY, int idTile);
		void removeTileAtPos(int posX, int posY);

	private:
		// TILESET.
		string pathTileset;
		int idImg;
		int spacing;
		int width;
		int height;

		// TILES.
		int tileWidth, tileHeight;
		float scaleXtile, scaleYtile;
		int sizeXtiles, sizeYtiles; // Number of rows and columns of tiles to travel the vector of vectors at those positions.
		vector <vector<Tile*>> tiles;
	};

	void Init();

	int GetWidthMap();
	int GetHeightMap();
	int GetTileSize();

	void LoadTmx(const char* fileTMX, string layerCollision);
	vector <vector<int>> LoadMap(int numLayers);
	vector <vector<int>> LoadMapCollision();
	Tileset* LoadTileset(int numTilesets, bool haveSpacing, vector <vector<int>> map, int posX, int posY);
	void DestroyTMX();

private:
	tinyManager();

	static tinyManager* tInstance;

	TiXmlDocument* doc;
	string layerCollision; // Name of the TMX layer where the collision map is located.
	int x, y; // Positions of the vector of vectors 'map'.
	int widthMap, heightMap;
	int tileSize; // Number of tiles the map has.
};

#endif
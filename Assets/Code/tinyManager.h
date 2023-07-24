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
			int srcPosX, srcPosY; // Punt de retall inicial de l'spritesheet.
			int dstPosX, dstPosY; // Punt on es pintarà.

		public:
			Tile(int _srcPosX, int _srcPosY, int _dstPosX, int _dstPosY);

			int getSrcPosX();
			int getSrcPosY();
			int getDstPosX();
			int getDstPosY();

			void IncrementDstPos(int x, int y);
			void ChangeSrc(int srcX, int srcY);
		};

		void init(string rutaTileset, int spacing, int width, int height, int sizeXtiles, int sizeYtiles, int tileWidth, int tileHeight);
		void render(VideoManager* videoManager);

		string getRutaTileset();
		int getSizeXTiles();
		int getSizeYTiles();
		vector <vector<Tile*>> getTiles();
		int getIdImg();

		void setScaleTiles(float x, float y);
		void setIdImg(int id);

		void addTile(int posX, int posY, int srcPosX, int srcPosY, int dstPosX, int dstPosY);
		void changeTile(int x, int y, int idTile);
		void removeTile(int x, int y);

	private:
		// TILESET.
		string rutaTileset;
		int idImg;
		int spacing;
		int width;
		int height;

		// TILES.
		int tileWidth, tileHeight;
		float scaleXtile, scaleYtile;
		int sizeXtiles, sizeYtiles; // Nombre de files i columnes de tiles. Per recórre el vector de vectors en aquelles posicions.
		vector <vector<Tile*>> tiles;
	};

	void Init();

	int GetWidthMap();
	int GetHeightMap();
	int GetTileSize();

	void LoadTmx(const char* fileTMX, string layerCollision);
	vector <vector<int>> LoadMap(int numLayers);
	vector <vector<int>> LoadMapCollision();
	Tileset* LoadTileset(int numTilesets, bool haveSpacing, vector <vector<int>> mapa, int posX, int posY);
	int DestroyTMX();

private:
	tinyManager();

	static tinyManager* tInstance;

	TiXmlDocument *doc;
	string layerCollision; // Nom de la layer del tmx on es troba el mapa de col·lisions.
	int x, y; // Posicions del vector de vectors 'mapa'.
	int widthMap, heightMap;
	int tileSize; // Número de tiles que té el mapa.
};

#endif
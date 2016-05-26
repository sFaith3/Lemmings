#ifndef TINYMANAGER_H
#define TINYMANAGER_H

#include "TinyXML\tinyxml.h"
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

	class Tileset{
	public:
		struct Tile{
		private:
			int srcPosX, srcPosY;
			int tileWidth, tileHeight;
			int dstPosX, dstPosY;

		public:
			Tile(int _srcPosX, int _srcPosY, int _tileWidth, int _tileHeight, int _dstPosX, int _dstPosY){
				srcPosX = _srcPosX;
				srcPosY = _srcPosY;
				tileWidth = _tileWidth;
				tileHeight = _tileHeight;
				dstPosX = _dstPosX;
				dstPosY = _dstPosY;
			}

			int getSrcPosX(){
				return srcPosX;
			}

			int getSrcPosY(){
				return srcPosY;
			}

			int getTileWidth(){
				return tileWidth;
			}

			int getTileHeight(){
				return tileHeight;
			}

			int getDstPosX(){
				return dstPosX;
			}

			int getDstPosY(){
				return dstPosY;
			}

		};

		void init(string rutaTileset, int sizeXtiles, int sizeYtiles){
			this->rutaTileset = rutaTileset;
			this->sizeXtiles = sizeXtiles;
			this->sizeYtiles = sizeYtiles;
			tiles.clear();
			tiles.resize(sizeYtiles + 1);
			for (int i = 0; i <= sizeYtiles; i++)
				tiles[i].resize(sizeXtiles + 1);
		}

		void addTile(int posX, int posY, int srcPosX, int srcPosY, int tileWidth, int tileHeight, int dstPosX, int dstPosY){
			Tile *tile = new Tile(srcPosX, srcPosY, tileWidth, tileHeight, dstPosX, dstPosY);
			tiles[posY][posX] = tile;
		}

		string getRutaTileset(){
			return rutaTileset;
		}

		int getSizeXTiles(){
			return sizeXtiles;
		}

		int getSizeYTiles(){
			return sizeYtiles;
		}

		vector <vector<Tile*> > getTiles(){
			return tiles;
		}

		void setIdImg(int id){
			idImg = id;
		}

		int getIdImg(){
			return idImg;
		}

		void removeTile(int x, int y){
			tiles[y][x] = NULL;
		}

	private:
		string rutaTileset;
		int sizeXtiles;
		int sizeYtiles;
		int idImg;
		vector <vector<Tile*> > tiles;
	};

	void Init();
	void LoadTmx(const char* fileTMX, string layerCollision);
	vector <vector<int> > LoadMap(int numLayers);
	vector <vector<int> > LoadMapCollision();
	Tileset* LoadTileset(int numTilesets, bool haveSpacing, vector <vector<int> > mapa, int posX, int posY);

	int GetWidthMap();
	int GetHeightMap();
	int GetTileSize();

	int DestroyTMX();

private:
	tinyManager();

	static tinyManager* tInstance;

	TiXmlDocument *doc;
	string layerCollision;
	int x, y; // Posicions del vector de vectors 'mapa'.
	int widthMap, heightMap;
	int tileSize;

};

#endif
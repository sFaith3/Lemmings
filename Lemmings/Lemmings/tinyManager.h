#ifndef TINYMANAGER_H
#define TINYMANAGER_H

#include "TinyXML\tinyxml.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

//typedef int array2D[200][200];

class tinyManager
{
private:
	tinyManager();

	static tinyManager* tInstance;

	int x, y; // Posicions de l'array 'mapa[][]'.
	int widthMap;
	int tileSize;

public:
	~tinyManager();

	static tinyManager* getInstanceTinyManager();
	
	class Tileset{
	public:
		struct Tile{
		private:
			int srcPosX;
			int srcPosY;
			int tileWidth;
			int tileHeight;
			int dstPosX;
			int dstPosY;

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

		void addTile(int _srcPosX, int _srcPosY, int _tileWidth, int _tileHeight, int _dstPosX, int _dstPosY){
			Tile tile = Tile(_srcPosX, _srcPosY, _tileWidth, _tileHeight, _dstPosX, _dstPosY);
			tiles.push_back(tile);
		}

		vector<Tile> getTiles(){
			return tiles;
		}

		int getSizeTiles(){
			return tiles.size();
		}

	private:
		vector<Tile> tiles;

		//Tiles getTile(int pos);

	};	

	//array2D* LoadTmx(const char* fileTMX, int numLayers);
	vector <vector<int> > LoadTmx(const char* fileTMX, int numLayers);

	Tileset LoadTileset(const char* fileTMX, int numTilesets, vector <vector<int> > mapa);

	int GetWidthMap();
	int GetTileSize();

	//int* GetMap(const char* fileTMX);
	//int GetTileset(const char* fileTileset);

	//Sint32 getMapID(const char* fileTMX);
	//Sint32 getTilesetID(const char* fileTileset);

};

#endif
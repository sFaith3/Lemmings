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

	};

	void LoadTmx(const char* fileTMX);
	vector <vector<int> > LoadMap(int numLayers);
	vector <vector<int> > LoadMapCollision();
	Tileset LoadTileset(int numTilesets, vector <vector<int> > mapa);

	int GetWidthMap();
	int GetTileSize();

	int DestroyTMX();

private:
	tinyManager();

	static tinyManager* tInstance;

	TiXmlDocument *doc;
	int x, y; // Posicions del vector de vectors 'mapa'.
	int widthMap;
	int tileSize;

};

#endif
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
			float scaleX, scaleY;
			int dstPosX, dstPosY;

		public:
			Tile(int _srcPosX, int _srcPosY, int _tileWidth, int _tileHeight, float _scaleX, float _scaleY, int _dstPosX, int _dstPosY){
				srcPosX = _srcPosX;
				srcPosY = _srcPosY;
				tileWidth = _tileWidth;
				tileHeight = _tileHeight;
				scaleX = _scaleX;
				scaleY = _scaleY;
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

			float getScaleX(){
				return scaleX;
			}

			float getScaleY(){
				return scaleY;
			}

			int getDstPosX(){
				return dstPosX;
			}

			int getDstPosY(){
				return dstPosY;
			}

		};

		void addTile(int srcPosX, int srcPosY, int tileWidth, int tileHeight, float scaleX, float scaleY, int dstPosX, int dstPosY){
			Tile *tile = new Tile(srcPosX, srcPosY, tileWidth, tileHeight, scaleX, scaleY, dstPosX, dstPosY);
			tiles.push_back(tile);
		}

		vector<Tile*> getTiles(){
			return tiles;
		}

		int getSizeTiles(){
			return tiles.size();
		}

	private:
		vector<Tile*> tiles;

	};

	void LoadTmx(const char* fileTMX, string layerCollision);
	vector <vector<int> > LoadMap(int numLayers);
	vector <vector<int> > LoadMapCollision();
	Tileset LoadTileset(int numTilesets, bool haveSpacing, vector <vector<int> > mapa);

	int GetWidthMap();
	int GetTileSize();

	int DestroyTMX();

private:
	tinyManager();

	static tinyManager* tInstance;

	TiXmlDocument *doc;
	string layerCollision;
	int x, y; // Posicions del vector de vectors 'mapa'.
	int widthMap;
	int tileSize;

};

#endif
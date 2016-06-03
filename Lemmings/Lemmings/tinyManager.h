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

	class Tileset{
	public:
		struct Tile{
		private:
			int srcPosX, srcPosY; // Punt de retall inicial de l'spritesheet.
			int dstPosX, dstPosY; // Punt on es pintarà.

		public:
			Tile(int _srcPosX, int _srcPosY, int _dstPosX, int _dstPosY){
				srcPosX = _srcPosX;
				srcPosY = _srcPosY;
				dstPosX = _dstPosX;
				dstPosY = _dstPosY;
			}

			int getSrcPosX(){
				return srcPosX;
			}

			int getSrcPosY(){
				return srcPosY;
			}

			int getDstPosX(){
				return dstPosX;
			}

			int getDstPosY(){
				return dstPosY;
			}

			void IncrementDstPos(int x, int y){
				dstPosX += x;
				dstPosY += y;
			}

		};

		void init(string rutaTileset, int sizeXtiles, int sizeYtiles, int tileWidth, int tileHeight){
			this->rutaTileset = rutaTileset;
			this->sizeXtiles = sizeXtiles;
			this->sizeYtiles = sizeYtiles;
			tiles.clear();
			tiles.resize(sizeYtiles + 1);
			for (int i = 0; i <= sizeYtiles; i++)
				tiles[i].resize(sizeXtiles + 1);

			this->tileWidth = tileWidth;
			this->tileHeight = tileHeight;
			scaleXtile = scaleYtile = 1;
		}

		void addTile(int posX, int posY, int srcPosX, int srcPosY, int dstPosX, int dstPosY){
			Tile *tile = new Tile(srcPosX, srcPosY, dstPosX, dstPosY);
			tiles[posY][posX] = tile;
		}

		void render(VideoManager* videoManager){
			for (int j = 0; j < sizeYtiles; j++) {
				for (int i = 0; i < sizeXtiles; i++) {
					if (tiles[j][i] != NULL){
						int srcPosXtile = tiles[j][i]->getSrcPosX();
						int srcPosYtile = tiles[j][i]->getSrcPosY();
						int dstPosXtile = tiles[j][i]->getDstPosX();
						int dstPosYtile = tiles[j][i]->getDstPosY();
						videoManager->renderTexture(idImg, srcPosXtile, srcPosYtile, tileWidth, tileHeight, scaleXtile, scaleYtile, dstPosXtile, dstPosYtile, 0, 0, 0);
					}
				}
			}
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

		void setScaleTiles(float x, float y){
			scaleXtile = x;
			scaleYtile = y;
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
		// TILESET.
		string rutaTileset;
		int idImg;

		// TILES.
		int tileWidth, tileHeight;
		float scaleXtile, scaleYtile;
		int sizeXtiles, sizeYtiles; // Nombre de files i columnes de tiles. Per recórre el vector de vectors en aquelles posicions.
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
	string layerCollision; // Nom de la layer del tmx on es troba el mapa de col·lisions.
	int x, y; // Posicions del vector de vectors 'mapa'.
	int widthMap, heightMap;
	int tileSize; // Número de tiles que té el mapa.
};

#endif
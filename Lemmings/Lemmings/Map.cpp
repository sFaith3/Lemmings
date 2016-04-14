#include "Map.h"


Map::Map(){
	tManager = tinyManager::getInstanceTinyManager();
}

Map::~Map(){

}


void Map::Init(int x, int y, bool tmx, const char* fileMap, const char* tiles, int srcX, int srcY, int w, int h){
	Element::Init(x, y, fileMap, srcX, srcY, w, h);

	this->tmx = tmx;
	if (this->tmx){
		mapa = tManager->LoadTmx(fileMap);
		if (tiles != NULL){
			fileTileset = tiles;
			tileset = tManager->LoadTileset(fileMap, *mapa);

		}
	}

}


void Map::Render(){
	if (fileTileset != NULL){
		vector<tinyManager::Tileset::Tile> tiles = tileset.getTiles();
		for (int pos = 0; pos < tileset.getSizeTiles(); pos++)
			sManager->getVideoManager()->renderGraphic(sManager->getVideoManager()->getGraphicID(fileTileset), tiles[pos].getSrcPosX(), tiles[pos].getSrcPosY(), tiles[pos].getTileWidth(), tiles[pos].getTileHeight(), tiles[pos].getDstPosX(), tiles[pos].getDstPosY());
	}
	else
		sManager->getVideoManager()->renderGraphic(sManager->getVideoManager()->getGraphicID(imatge), 0, 0, width, height, 0, 0);
}


int Map::getMapa(){
	return (int)mapa;
}
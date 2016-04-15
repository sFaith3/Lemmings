#include "Map.h"


Map::Map(){
	tManager = tinyManager::getInstanceTinyManager();
}

Map::~Map(){

}


void Map::Init(int x, int y, const char* fileMap, const char* tiles, const char* fileMapColli, int srcX, int srcY, int w, int h){
	Element::Init(x, y, fileMap, srcX, srcY, w, h);

	fileTileset = tiles;
	if (fileTileset != NULL){
		array2D *mapa = tManager->LoadTmx(fileMap);
		tileset = tManager->LoadTileset(fileMap, *mapa);
	}

	fileMapCollision = fileMapColli;
	if (fileMapCollision != NULL)
		mapCollision = tManager->LoadTmx(fileMapCollision);

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


int Map::getMapa(int x, int y){
	return (int)mapCollision[x][y];
}
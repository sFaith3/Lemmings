#include "Map.h"


Map::Map(){
	fileMap = "";
	fileTileset = "";
	widthMap = 0;
	sizeTiles = 0;
	tManager = tinyManager::getInstanceTinyManager();
}

Map::~Map(){

}


void Map::init(int x, int y, const char* fileMap, int numLayers, const char* fileTileset, int numTilesets, int srcX, int srcY, int w, int h){
	Element::init(x, y, fileMap, srcX, srcY, w, h);

	tManager->LoadTmx(fileMap);
	this->fileTileset = fileTileset;
	if (fileTileset != NULL){
		for (int i = 0; i < numLayers; i++){
			vector <vector<int> > mapa = tManager->LoadMap(i);
			for (int i = 0; i < numTilesets; i++)
				tilesets.push_back(tManager->LoadTileset(i, mapa));
		}
		mapCollision = tManager->LoadMapCollision();
		widthMap = tManager->GetWidthMap();
		sizeTiles = tManager->GetTileSize();
	}
	else{
		this->fileMap = fileMap;
	}

	tManager->DestroyTMX();

}


void Map::render(){
	if (fileTileset != NULL){
		for (itTilesets = tilesets.begin(); itTilesets != tilesets.end(); itTilesets++){
			vector<tinyManager::Tileset::Tile*> tiles = itTilesets->getTiles();
			for (int pos = 0; pos < itTilesets->getSizeTiles(); pos++)
				sManager->getVideoManager()->renderGraphic(sManager->getVideoManager()->getGraphicID(fileTileset), tiles[pos]->getSrcPosX(), tiles[pos]->getSrcPosY(), tiles[pos]->getTileWidth(), tiles[pos]->getTileHeight(), tiles[pos]->getDstPosX() - posX, tiles[pos]->getDstPosY() - posY);
		}
	}
	else
		sManager->getVideoManager()->renderGraphic(sManager->getVideoManager()->getGraphicID(fileMap), 0, 0, width, height, posX, posY);
}


int Map::GetMapa(int x, int y){
	return mapCollision[y][x];
}

int Map::GetSizeTile(){
	return sizeTiles;
}
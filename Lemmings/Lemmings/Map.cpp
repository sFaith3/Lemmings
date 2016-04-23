#include "Map.h"


Map::Map(){
	tManager = tinyManager::getInstanceTinyManager();
}

Map::~Map(){

}


void Map::Init(int x, int y, const char* fileMap, int numLayers, const char* tiles, int numTilesets, const char* fileMapColli, int srcX, int srcY, int w, int h){
	Element::Init(x, y, fileMap, srcX, srcY, w, h);

	fileTileset = tiles;
	if (fileTileset != NULL){
		for (int i = 0; i < numLayers; i++){
			vector <vector<int> > mapa = tManager->LoadTmx(fileMap, i);
			for (int i = 0; i < numTilesets; i++)
				tilesets.push_back(tManager->LoadTileset(fileMap, i, mapa));
		}
		widthMap = tManager->GetWidthMap();
		sizeTiles = tManager->GetTileSize();
	}

	fileMapCollision = fileMapColli;
	if (fileMapCollision != NULL)
		mapCollision = tManager->LoadTmx(fileMapCollision, 0);

}


void Map::Render(){
	if (fileTileset != NULL){
		for (itTilesets = tilesets.begin(); itTilesets != tilesets.end(); itTilesets++){
			vector<tinyManager::Tileset::Tile> tiles = itTilesets->getTiles();
			for (int pos = 0; pos < itTilesets->getSizeTiles(); pos++)
				sManager->getVideoManager()->renderGraphic(sManager->getVideoManager()->getGraphicID(fileTileset), tiles[pos].getSrcPosX(), tiles[pos].getSrcPosY(), tiles[pos].getTileWidth(), tiles[pos].getTileHeight(), tiles[pos].getDstPosX() - posX, tiles[pos].getDstPosY() - posY);
		}
	}
	else
		sManager->getVideoManager()->renderGraphic(sManager->getVideoManager()->getGraphicID(imatge), 0, 0, width, height, posX, posY);
}


/*int Map::GetMapa(int x, int y){
	return (int)mapCollision[x][y];
}*/
int Map::GetMapa(int x, int y){
	return mapCollision[y][x];
}

int Map::GetSizeTile(){
	return sizeTiles;
}

void Map::move(bool dreta){
	if (dreta){
		if (posX + width < widthMap)
			posX += 4;
		else if (posX + width > widthMap){
			posX = widthMap - width;
		}
	}
	else{
		if (posX > 0)
			posX -= 4;
		else if (posX < 0){
			posX = 0;
		}
	}
}
#include "Map.h"


Map::Map(){
	tManager = tinyManager::getInstanceTinyManager();
}

Map::~Map(){

}


void Map::Init(int x, int y, const char* img, const char* tiles, int srcX, int srcY, int w, int h){
	Element::Init(x, y, img, srcX, srcY, w, h);
	tileset = tiles;
}


void Map::Render(){
	tManager->loadTMX(imatge, tileset);
}
#include "Map.h"


Map::Map(){
	mapTMX = false;
	idFileMap = NULL;
	pathTilesets = "";
	sizeTile = 0;

	tinyManager = tinyManager::getInstanceTinyManager();
}

Map::~Map(){
}


void Map::init(int x, int y, bool mapTMX, const char* fileMap, const char* layerCollision, int numLayers, const char* pathTilesets, bool haveSpacingTileset, int numTilesets, int srcX, int srcY, int w, int h){
	this->mapTMX = mapTMX;
	idFileMap = NULL;
	this->pathTilesets = pathTilesets;
	sizeTile = 0;
	
	tinyManager->Init();
	tinyManager->LoadTmx(fileMap, layerCollision);
	if (mapTMX){
		initMapTMX(x, y, numLayers, haveSpacingTileset, numTilesets, srcX, srcY);
	}
	else{
		idFileMap = videoManager->getTextureID(fileMap);
		Element::init(x, y, fileMap, false, srcX, srcY, w, h, 1, 1);
	}

	tinyManager->DestroyTMX();
}

void Map::initMapTMX(const int x, const int y, const int numLayers, const bool haveSpacingTileset, const int numTilesets, const int srcX, const int srcY) {
	loadMapAndTilesets(x, y, numLayers, haveSpacingTileset, numTilesets);
	sizeTile = tinyManager->GetTileSize();
	mapCollision = tinyManager->LoadMapCollision();

	Element::init(x, y, NULL, false, srcX, srcY, tinyManager->GetWidthMap(), tinyManager->GetHeightMap(), 1, 1);
}

void Map::loadMapAndTilesets(const int x, const int y, const int numLayers, const bool haveSpacingTileset, const int numTilesets) {
	for (int i = 0; i < numLayers; i++) {
		vector <vector<int> > map = tinyManager->LoadMap(i);
		if (map.empty())
			continue;

		for (int currNumTilesets = 0; currNumTilesets < numTilesets; currNumTilesets++) {
			tinyManager::Tileset* tileSet = tinyManager->LoadTileset(currNumTilesets, haveSpacingTileset, map, x, y);
			tilesets.push_back(tileSet);
		}
		setTilesetImgID();
	}
}

void Map::setTilesetImgID() {
	string idImgTileset = pathTilesets + tilesets.back()->getRutaTileset();
	const char* _idImgTileset = idImgTileset.c_str();
	tilesets.back()->setIdImg(videoManager->getTextureID(_idImgTileset));
}

void Map::render(){
	if (mapTMX){
		for (itTilesets = tilesets.begin(); itTilesets != tilesets.end(); itTilesets++)
			(*itTilesets)->render(videoManager);
	}
	else
		videoManager->renderTexture(idFileMap, 0, 0, width, height, scaleX, scaleY, posX, posY);
}


int Map::GetWidthMap(){
	return width;
}

int Map::GetHeightMap(){
	return height;
}

int Map::GetSizeTile(){
	return sizeTile;
}


void Map::SetPositionTiles(const int x, const int y){
	for (itTilesets = tilesets.begin(); itTilesets != tilesets.end(); itTilesets++){
		vector <vector<tinyManager::Tileset::Tile*> > tiles = (*itTilesets)->getTiles();
		for (int j = 0; j < (*itTilesets)->getSizeYTiles(); j++){
			for (int i = 0; i < (*itTilesets)->getSizeXTiles(); i++){
				if (tiles[j][i] != NULL)
					tiles[j][i]->IncrementDstPos(x, y);
			}
		}
	}
}

void Map::SetScaleTiles(const float x, const float y){
	for (itTilesets = tilesets.begin(); itTilesets != tilesets.end(); itTilesets++)
		(*itTilesets)->setScaleTiles(x, y);
}


int Map::GetMap(const int x, const int y){
	if (isWithinRangeOfMap(x, y))
		return mapCollision[y][x];

	return 0;
}

void Map::DestroyMapAtPos(const int x, const int y){
	if (isWithinRangeOfMap(x, y)) {
		mapCollision[y][x] = 0;
		for (itTilesets = tilesets.begin(); itTilesets != tilesets.end(); itTilesets++)
			(*itTilesets)->removeTile(x, y);
	}
}

void Map::CreateMapAtPos(const int x, const int y, const int type) {
	if (isWithinRangeOfMap(x, y)) {
		mapCollision[y][x] = type;
	}
}

void Map::CreateMapAtPos(const int x, const int y, const int type, const int layer, const int idTile) {
	if (isWithinRangeOfMap(x, y)) {
		mapCollision[y][x] = type;
		tilesets[layer]->changeTile(x, y, idTile);
	}
}

bool Map::isWithinRangeOfMap(const int x, const int y) {
	return (x >= 0 && y >= 0) && (x < mapCollision[0].size() && y < mapCollision.size());
}

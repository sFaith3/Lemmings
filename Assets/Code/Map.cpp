#include "Map.h"

Map::Map(){
	tManager = tinyManager::getInstanceTinyManager();
}

Map::~Map(){

}


void Map::init(int x, int y, bool mapTmx, const char* fileMap, const char* layerCollision, int numLayers, const char* rutaTilesets, bool haveSpacingTileset, int numTilesets, int srcX, int srcY, int w, int h){
	idFileMap = NULL;
	sizeTile = 0;
	
	this->mapTmx = mapTmx;

	tManager->Init();
	tManager->LoadTmx(fileMap, layerCollision);
	this->rutaTilesets = rutaTilesets;
	if (mapTmx){
		for (int i = 0; i < numLayers; i++){
			vector <vector<int> > mapa = tManager->LoadMap(i);
			if (mapa.size() > 0){
				for (int i = 0; i < numTilesets; i++){
					tinyManager::Tileset* tileSet = tManager->LoadTileset(i, haveSpacingTileset, mapa, x, y);
					tilesets.push_back(tileSet); // S'obté el tileset.
				}
				// Es seteja l'id de la img del tileset, que es desa al ResourceManager, en el objecte 'Tileset'.
				string idImgTileset = rutaTilesets + tilesets.back()->getRutaTileset();
				const char* _idImgTileset = idImgTileset.c_str();
				tilesets.back()->setIdImg(videoManager->getTextureID(_idImgTileset));
			}
		}
		mapCollision = tManager->LoadMapCollision();
		sizeTile = tManager->GetTileSize();
	}
	else{
		idFileMap = videoManager->getTextureID(fileMap);
	}

	if (mapTmx)
		Element::init(x, y, NULL, false, srcX, srcY, tManager->GetWidthMap(), tManager->GetHeightMap(), 1, 1);
	else
		Element::init(x, y, fileMap, false, srcX, srcY, w, h, 1, 1);

	tManager->DestroyTMX();
}

void Map::render(){
	if (mapTmx){
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


void Map::SetPositionTiles(int x, int y){
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


void Map::SetScaleTiles(float x, float y){
	for (itTilesets = tilesets.begin(); itTilesets != tilesets.end(); itTilesets++)
		(*itTilesets)->setScaleTiles(x, y);
}


int Map::GetMapa(int x, int y){
	if ((x >= 0 && y >= 0) && (x < mapCollision[0].size() && y < mapCollision.size()))
		return mapCollision[y][x];

	return 0;
}

void Map::DestroyPosMapa(int x, int y){
	if ((x >= 0 && y >= 0) && (x < mapCollision[0].size() && y < mapCollision.size())) {
		mapCollision[y][x] = 0;
		for (itTilesets = tilesets.begin(); itTilesets != tilesets.end(); itTilesets++)
			(*itTilesets)->removeTile(x, y);
	}
}

void Map::CrearPosMapa(int x, int y, int tipo){
	if ((x >= 0 && y >= 0) && (x < mapCollision[0].size() && y < mapCollision.size())) {
		mapCollision[y][x] = tipo;
	}
}

void Map::CrearPosMapa(int x, int y, int tipo, int layer, int idTile){
	if ((x >= 0 && y >= 0) && (x < mapCollision[0].size() && y < mapCollision.size())) {
		mapCollision[y][x] = tipo;
		tilesets[layer]->changeTile(x, y, idTile);
	}
}
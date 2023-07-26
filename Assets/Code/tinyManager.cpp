#include "tinyManager.h"


tinyManager* tinyManager::tInstance = nullptr;

tinyManager::tinyManager(){
	doc = nullptr;
	mapPosX = mapPosY = 0;
	mapWidth = mapHeight = 0;
	tileSize = 0;
}

tinyManager::~tinyManager(){
}


tinyManager* tinyManager::getInstanceTinyManager(){
	if (tInstance == nullptr)
		tInstance = new tinyManager();

	return tInstance;
}


#pragma region Tileset_Class
#pragma region Tile_Struct
tinyManager::Tileset::Tile::Tile(int _srcPosX, int _srcPosY, int _dstPosX, int _dstPosY) {
	srcPosX = _srcPosX;
	srcPosY = _srcPosY;
	dstPosX = _dstPosX;
	dstPosY = _dstPosY;
}


int tinyManager::Tileset::Tile::getSrcPosX() {
	return srcPosX;
}

int tinyManager::Tileset::Tile::getSrcPosY() {
	return srcPosY;
}

int tinyManager::Tileset::Tile::getDstPosX() {
	return dstPosX;
}

int tinyManager::Tileset::Tile::getDstPosY() {
	return dstPosY;
}


void tinyManager::Tileset::Tile::IncrementDstPos(int dstX, int dstY) {
	dstPosX += dstX;
	dstPosY += dstY;
}

void tinyManager::Tileset::Tile::ChangeSrcPos(int srcX, int srcY) {
	srcPosX = srcX;
	srcPosY = srcY;
}
#pragma endregion

tinyManager::Tileset::~Tileset(){
	for (int i = 0; i < tiles.size(); i++) {
		for (auto tile : tiles[i]) {
			delete tile;
		}
	}
}


void tinyManager::Tileset::init(string pathTileset, int spacing, int width, int height, int sizeXtiles, int sizeYtiles, int tileWidth, int tileHeight) {
	this->pathTileset = pathTileset;
	this->spacing = spacing;
	this->width = width;
	this->height = height;
	this->sizeXtiles = sizeXtiles;
	this->sizeYtiles = sizeYtiles;
	this->tileWidth = tileWidth;
	this->tileHeight = tileHeight;
	scaleXtile = scaleYtile = 1;

	tiles.clear();
	tiles.resize(sizeYtiles + 1);
	for (int i = 0; i <= sizeYtiles; i++)
		tiles[i].resize(sizeXtiles + 1);
}

void tinyManager::Tileset::addTiles(const int mapPosX, const int mapPosY, const vector <vector<int>> map, Tileset* tileset,
	const int numMaxTilesWidth, const int numMaxTilesHeight, const int posX, const int posY) {
	// The tileset is traversed to paint each tile. The two "for" indicate the position of the screen, multiplied
	// by the corresponding measure (X/Y) of the tile.
	for (int i = 0; i <= mapPosX; i++) {
		for (int j = 0; j <= mapPosY; j++) {
			int tile = map[j][i] - 1; // The tile ID to paint.
			int srcPosX = 0, srcPosY = 0;
			tileset->clippingBoxToGetSrcPositions(numMaxTilesWidth, numMaxTilesHeight, tile, srcPosX, srcPosY);

			int dstPosX = (i * tileWidth) + posX;
			int dstPosY = (j * tileHeight) + posY;
			tileset->addTileAtPos(i, j, srcPosX, srcPosY, dstPosX, dstPosY);
		}
	}
}

void tinyManager::Tileset::render(VideoManager* videoManager) {
	int dstPosXtile = tiles[0][0]->getDstPosX();
	int dstPosYtile = tiles[0][0]->getDstPosY();

	for (int j = 0; j < sizeYtiles; j++) {
		for (int i = 0; i < sizeXtiles; i++) {
			if (tiles[j][i] != nullptr) {
				int srcPosXtile = tiles[j][i]->getSrcPosX();
				int srcPosYtile = tiles[j][i]->getSrcPosY();
				int dstPosX = dstPosXtile + (i * tileWidth);
				int dstPosY = dstPosYtile + (j * tileHeight);

				videoManager->renderTexture(idImg, srcPosXtile, srcPosYtile, tileWidth, tileHeight,
					scaleXtile, scaleYtile, dstPosX, dstPosY);
			}
		}
		//dstPosYtile += tileHeight;
	}
}


string tinyManager::Tileset::getPathTileset() {
	return pathTileset;
}

int tinyManager::Tileset::getSizeXTiles() {
	return sizeXtiles;
}

int tinyManager::Tileset::getSizeYTiles() {
	return sizeYtiles;
}

vector <vector<tinyManager::Tileset::Tile*>> tinyManager::Tileset::getTiles() {
	return tiles;
}

int tinyManager::Tileset::getIdImg() {
	return idImg;
}


void tinyManager::Tileset::setScaleTiles(float x, float y) {
	scaleXtile = x;
	scaleYtile = y;
}

void tinyManager::Tileset::setIdImg(int id) {
	idImg = id;
}


bool tinyManager::Tileset::isIndexOutOfRangeInTilesAtPos(const int posX, const int posY) const {
	return (posY < 0 || posY >= tiles.size()) || (posX < 0 || posX >= tiles[posY].size());
}

void tinyManager::Tileset::addTileAtPos(int posX, int posY, int srcPosX, int srcPosY, int dstPosX, int dstPosY) {
	if (isIndexOutOfRangeInTilesAtPos(posX, posY))
		return;

	Tile* tile = new Tile(srcPosX, srcPosY, dstPosX, dstPosY);
	tiles[posY][posX] = tile;
}

void tinyManager::Tileset::changeTileAtPos(const int posX, const int posY, const int newTile) {
	if (isIndexOutOfRangeInTilesAtPos(posX, posY))
		return;

	int srcPosX = 0, srcPosY = 0;
	clippingBoxToGetSrcPositions(width, height, newTile, srcPosX, srcPosY);
	tiles[posY][posX]->ChangeSrcPos(srcPosX, srcPosY);
}

// A clipping box is made in the tileset, indicating where it is located.
void tinyManager::Tileset::clippingBoxToGetSrcPositions(const int width, const int height, const int tile, int& srcPosX, int& srcPosY) {
	for (int h = 1; h <= height; h++) { // Depending on the row it is in.
		if (tile < width * h) {
			// The tile ID is obtained and the total number of tiles in a row is subtracted, multiplied by the row
			// where less than 1 plus the space left between tiles. Because if it is in the first row, it does not
			// subtract any, so the X in the box obtained is already in the first row.
			srcPosX = ((tile - (width * (h - 1))) * tileWidth) + (spacing * (tile - (width * (h - 1))));
			srcPosY = ((h - 1) * tileHeight) + (spacing * (h - 1));
			break;
		}
	}
}
#pragma endregion


void tinyManager::Init(){
	mapPosX = mapPosY = 0;
	doc = nullptr;
}


int tinyManager::GetMapWidth() {
	const int _widthMap = mapWidth;
	if (mapWidth != 0)
		mapWidth = 0;

	return _widthMap;
}

int tinyManager::GetMapHeight() {
	const int _mapHeight = mapHeight;
	if (mapHeight != 0)
		mapHeight = 0;

	return _mapHeight;
}

int tinyManager::GetTileSize() {
	const int _tileSize = tileSize;
	if (tileSize != 0)
		tileSize = 0;

	return _tileSize;
}


void tinyManager::LoadTMX(const char* fileTMX, string layerCollision) {
	doc = new TiXmlDocument(fileTMX);
	this->layerCollision = layerCollision;
	if (!doc->LoadFile()) // parse file
	{
		cout << "Could not load test file '" << fileTMX << "' Error=" << doc->ErrorDesc() << ".\n" <<
			"Exiting." << endl;
	}
}

bool tinyManager::IsMapCollisionLayer(const int numLayer, TiXmlElement*& layer) {
	for (int i = 0; i < numLayer; i++) {
		layer = layer->NextSiblingElement("layer");
		if ((string)layer->Attribute("name") == layerCollision) {
			return true;
		}
	}

	return false;
}

// The 'data' information is stored in a 2-dimensional array or vector of vectors in order to know the tiles
// to be painted, thanks to their ID. And with the position of the array we know where to locate it.
vector<vector<int>> tinyManager::GetMapData(vector<vector<int>> map, const string text, string num, const int layerWidth) {
	vector<int> row;
	map.push_back(row);

	for (int i = 0; i < text.length(); i++) {
		if (text[i] == ',') {
			//map[mapPosX][mapPosY] = atoi(num.c_str());
			map[mapPosY].push_back(atoi(num.c_str()));
			num = "";

			if (mapPosX < layerWidth)
				mapPosX++;
			else {
				mapPosY++;
				mapPosX = 0;
				vector<int> row;
				map.push_back(row);
			}
		}
		else if (text[i] != ' ')
			num += text[i];
	}
	//map[mapPosX][mapPosY] = atoi(num.c_str());
	map[mapPosY].push_back(atoi(num.c_str()));

	return map;
}

vector <vector<int>> tinyManager::GetLoadedMap(const int numLayer) {
	vector <vector<int>> loadedMap; // Map of integers: map[row(y)][column(x)].

	TiXmlElement* tmxMap = doc->FirstChildElement();
	TiXmlElement* layer = tmxMap->FirstChildElement("layer");
	if (IsMapCollisionLayer(numLayer, layer)) {
		loadedMap.clear();
		loadedMap.resize(0);

		return loadedMap;
	}

	mapWidth = atoi(tmxMap->Attribute("width"));
	mapHeight = atoi(tmxMap->Attribute("height"));
	tileSize = atoi(tmxMap->Attribute("tilewidth"));

	TiXmlElement* data = layer->FirstChildElement("data");
	string text = data->GetText(); // TMX map.
	string num = ""; // Content to insert in the array.
	int layerWidth = atoi(layer->Attribute("width")) - 1;
	
	return GetMapData(loadedMap, text, num, layerWidth);
}

vector <vector<int>> tinyManager::GetLoadedMapCollision() {
	TiXmlElement* map = doc->FirstChildElement();
	tileSize = atoi(map->Attribute("tilewidth"));
	TiXmlElement* layer = map->FirstChildElement("layer");

	if ((string)layer->Attribute("name") != layerCollision) {
		bool isFound = false;
		while (!isFound) {
			layer = layer->NextSiblingElement("layer");
			if ((string)layer->Attribute("name") == layerCollision) {
				isFound = true;
			}
		}
	}
	layerCollision = "";

	vector <vector<int>> mapCollision; // Map of integers: map[row(y)][column(x)].
	TiXmlElement* data = layer->FirstChildElement("data");
	string text = data->GetText(); // TMX map.
	string num = ""; // Content to insert in the array.
	int layerWidth = atoi(layer->Attribute("width")) - 1;

	return GetMapData(mapCollision, text, num, layerWidth);
}

tinyManager::Tileset* tinyManager::GetLoadedTileset(int numTilesets, bool haveSpacing, vector <vector<int>> map, int posX, int posY) {
	TiXmlElement* tmxMap = doc->FirstChildElement();
	TiXmlElement* tileset = tmxMap->FirstChildElement("tileset");
	TiXmlElement* image = tileset->FirstChildElement("image");

	for (int i = 0; i < numTilesets; i++) {
		tileset = tileset->NextSiblingElement("tileset");
	}
	int spacing = (haveSpacing) ? atoi(tileset->Attribute("spacing")) : 0;
	int tilesetWidth = atoi(image->Attribute("width"));
	int tilesetHeigth = atoi(image->Attribute("height"));
	int tileWidth = atoi(tileset->Attribute("tilewidth"));
	int tileHeight = atoi(tileset->Attribute("tileheight"));
	int numMaxTilesWidth = tilesetWidth / (tileWidth + spacing);
	int numMaxTilesHeight = tilesetHeigth / (tileHeight + spacing);

	Tileset* _tileset = new Tileset();
	string pathTileset = image->Attribute("source");
	_tileset->init(pathTileset, spacing, tilesetWidth, tilesetHeigth, mapPosX, mapPosY, tileWidth, tileHeight);
	_tileset->addTiles(mapPosX, mapPosY, map, _tileset, numMaxTilesWidth, numMaxTilesHeight, posX, posY);

	mapPosX = mapPosY = 0;

	return _tileset;
}

void tinyManager::DestroyTMX() {
	delete doc;
	doc = nullptr;
}
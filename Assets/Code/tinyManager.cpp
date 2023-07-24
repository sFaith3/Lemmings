#include "tinyManager.h"


tinyManager* tinyManager::tInstance = nullptr;

tinyManager::tinyManager(){
	doc = nullptr;
	x = y = 0;
	widthMap = heightMap = 0;
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


void tinyManager::Tileset::Tile::IncrementDstPos(int x, int y) {
	dstPosX += x;
	dstPosY += y;
}

void tinyManager::Tileset::Tile::ChangeSrc(int srcX, int srcY) {
	srcPosX = srcX;
	srcPosY = srcY;
}
#pragma endregion

void tinyManager::Tileset::init(string rutaTileset, int spacing, int width, int height, int sizeXtiles, int sizeYtiles, int tileWidth, int tileHeight) {
	this->rutaTileset = rutaTileset;
	this->spacing = spacing;
	this->width = width;
	this->height = height;
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

void tinyManager::Tileset::render(VideoManager* videoManager) {
	int dstPosXtile = tiles[0][0]->getDstPosX();
	int dstPosYtile = tiles[0][0]->getDstPosY();
	for (int j = 0; j < sizeYtiles; j++) {
		for (int i = 0; i < sizeXtiles; i++) {
			if (tiles[j][i] != nullptr) {
				int srcPosXtile = tiles[j][i]->getSrcPosX();
				int srcPosYtile = tiles[j][i]->getSrcPosY();
				videoManager->renderTexture(idImg, srcPosXtile, srcPosYtile, tileWidth, tileHeight, scaleXtile, scaleYtile, dstPosXtile + (i * tileWidth), dstPosYtile + (j * tileHeight));
			}
		}
		//dstPosYtile += tileHeight;
	}
}


string tinyManager::Tileset::getRutaTileset() {
	return rutaTileset;
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


void tinyManager::Tileset::addTile(int posX, int posY, int srcPosX, int srcPosY, int dstPosX, int dstPosY) {
	Tile* tile = new Tile(srcPosX, srcPosY, dstPosX, dstPosY);
	tiles[posY][posX] = tile;
}

void tinyManager::Tileset::changeTile(int x, int y, int idTile) {
	int srcPosX = 0;
	int srcPosY = 0;
	// Es fa un requadre de retall al tileset, i s'indica on se situa.
	int tile = idTile; // Id de la tile a pintar.
	for (int h = 1; h <= height; h++) { // Segons la fila on es trobi.
		if (tile < width * h) {
			// S'obté la ID de la tile i se li resta el número total de tiles que hi ha en una fila, multiplicat per la fila on sigui menys 1 més l'espai que es deixa entre tile.
			// Perquè si es troba a la primera fila, no es resta cap, de manera que la x del requadre que s'obté ja és de la primera fila.
			srcPosX = ((tile - (width * (h - 1))) * tileWidth) + (spacing * (tile - (width * (h - 1))));
			srcPosY = ((h - 1) * tileHeight) + (spacing * (h - 1));
			break;
		}
	}
	tiles[y][x]->ChangeSrc(srcPosX, srcPosY);
}

void tinyManager::Tileset::removeTile(int x, int y) {
	tiles[y][x] = nullptr;
}
#pragma endregion


void tinyManager::Init(){
	x = y = 0;
	doc = nullptr;
}


int tinyManager::GetWidthMap() {
	int _widthMap = widthMap;
	if (widthMap != 0)
		widthMap = 0;

	return _widthMap;
}

int tinyManager::GetHeightMap() {
	int _heightMap = heightMap;
	if (heightMap != 0)
		heightMap = 0;

	return _heightMap;
}

int tinyManager::GetTileSize() {
	int _tileSize = tileSize;
	if (tileSize != 0)
		tileSize = 0;

	return _tileSize;
}


void tinyManager::LoadTmx(const char* fileTMX, string layerCollision){
	doc = new TiXmlDocument(fileTMX);
	this->layerCollision = layerCollision;
	if (!doc->LoadFile()) // parse file
	{
		cout << "Could not load test file '" << fileTMX << "' Error=" << doc->ErrorDesc() << ".\n" <<
			"Exiting." << endl;
		//return -1;
	}
}

vector <vector<int>> tinyManager::LoadMap(int numLayers){
	vector <vector<int>> mapa; // Mapa d'ints.  - mapa[fila(y)][columna(x)] -

	TiXmlElement *map = doc->FirstChildElement();
	widthMap = atoi(map->Attribute("width"));
	heightMap = atoi(map->Attribute("height"));
	tileSize = atoi(map->Attribute("tilewidth"));
	TiXmlElement *layer = map->FirstChildElement("layer");
	for (int i = 0; i < numLayers; i++){
		layer = layer->NextSiblingElement("layer");
		if ((string)layer->Attribute("name") == layerCollision){
			mapa.clear();
			mapa.resize(0);
			return mapa;
		}
	}

	TiXmlElement* data = layer->FirstChildElement("data");
	string text = data->GetText(); // Mapa de tmx.
	string num = ""; // Contingut a insertar a l'array.
	int layerWidth = atoi(layer->Attribute("width")) - 1;

	// Es desa l'informació de 'data' en una matriu de 2 dimensions o en un vector de vectors, per tal de saber les tiles a pintar, gràcies a la seva ID. I amb la posició de la matriu se sap on ubicar-la.
	vector<int> row;
	mapa.push_back(row);
	for (int i = 0; i < text.length(); i++){
		if (text[i] == ','){
			//mapa[x][y] = atoi(num.c_str());
			mapa[y].push_back(atoi(num.c_str()));

			num = "";

			if (x < layerWidth)
				x++;
			else{
				y++;
				x = 0;
				vector<int> row;
				mapa.push_back(row);
			}
		}
		else if (text[i] != ' ')
			num += text[i];
	}
	//mapa[x][y] = atoi(num.c_str());
	mapa[y].push_back(atoi(num.c_str()));

	return mapa;
}

vector <vector<int>> tinyManager::LoadMapCollision(){
	TiXmlElement *map = doc->FirstChildElement();
	tileSize = atoi(map->Attribute("tilewidth"));
	TiXmlElement* layer = map->FirstChildElement("layer");
	if ((string)layer->Attribute("name") != layerCollision){
		bool trobat = false;
		while (!trobat){
			layer = layer->NextSiblingElement("layer");
			if ((string)layer->Attribute("name") == layerCollision){
				trobat = true;
			}
		}
	}

	TiXmlElement* data = layer->FirstChildElement("data");
	string text = data->GetText(); // Mapa de tmx.
	vector <vector<int>> mapaCollisio; // Mapa d'ints.  - mapa[fila(y)][columna(x)] -
	string num = ""; // Contingut a insertar a l'array.
	int layerWidth = atoi(layer->Attribute("width")) - 1;

	// Es desa l'informació de 'data' en una matriu de 2 dimensions o en un vector de vectors, per tal de saber les tiles a pintar, gràcies a la seva ID. I amb la posició de la matriu se sap on ubicar-la.
	vector<int> row;
	mapaCollisio.push_back(row);
	for (int i = 0; i < text.length(); i++){
		if (text[i] == ','){
			mapaCollisio[y].push_back(atoi(num.c_str()));

			num = "";

			if (x < layerWidth)
				x++;
			else{
				y++;
				x = 0;
				vector<int> row;
				mapaCollisio.push_back(row);
			}
		}
		else if (text[i] != ' ')
			num += text[i];
	}
	mapaCollisio[y].push_back(atoi(num.c_str()));

	layerCollision = "";

	return mapaCollisio;
}

tinyManager::Tileset* tinyManager::LoadTileset(int numTilesets, bool haveSpacing, vector <vector<int>> mapa, int posX, int posY){
	TiXmlElement *map = doc->FirstChildElement();
	TiXmlElement* tileset = map->FirstChildElement("tileset");
	for (int i = 0; i < numTilesets; i++){
		tileset = tileset->NextSiblingElement("tileset");
	}
	int tileWidth = atoi(tileset->Attribute("tilewidth"));
	int tileHeight = atoi(tileset->Attribute("tileheight"));
	int spacing = 0;
	if(haveSpacing)
		spacing = atoi(tileset->Attribute("spacing"));

	TiXmlElement* image = tileset->FirstChildElement("image");
	int tilesetWidth = atoi(image->Attribute("width"));
	int tilesetHeigth = atoi(image->Attribute("height"));
	int numMaxTilesWidth = tilesetWidth / (tileWidth + spacing);
	int numMaxTilesHeight = tilesetHeigth / (tileHeight + spacing);

	Tileset *_tileset = new Tileset();
	string rutaTileset = image->Attribute("source");
	_tileset->init(rutaTileset, spacing, tilesetWidth, tilesetHeigth, x, y, tileWidth, tileHeight);
	// Es recórre el tileset per sàpiguer quina tile es pinta. Els 2 primers for's indiquen la posició de la pantalla, a la qual se li multiplica per la mesura corresponent (X/Y) de la tile.
	for (int i = 0; i <= x; i++){
		for (int j = 0; j <= y; j++){
			int srcPosX = 0;
			int srcPosY = 0;
			// Es fa un requadre de retall al tileset, i s'indica on se situa.
			int tile = mapa[j][i] - 1; // Id de la tile a pintar.
			for (int h = 1; h <= numMaxTilesHeight; h++){ // Segons la fila on es trobi.
				if (tile < numMaxTilesWidth * h){
					// S'obté la ID de la tile i se li resta el número total de tiles que hi ha en una fila, multiplicat per la fila on sigui menys 1 més l'espai que es deixa entre tile.
					// Perquè si es troba a la primera fila, no es resta cap, de manera que la x del requadre que s'obté ja és de la primera fila.
					srcPosX = ((tile - (numMaxTilesWidth * (h - 1))) * tileWidth) + (spacing * (tile - (numMaxTilesWidth * (h - 1))));
					srcPosY = ((h - 1) * tileHeight) + (spacing * (h - 1));
					break;
				}
			}
			int dstPosX = (i * tileWidth) + posX;
			int dstPosY = (j * tileHeight) + posY;

			_tileset->addTile(i, j, srcPosX, srcPosY, dstPosX, dstPosY);
		}
	}
	x = y = 0;

	return _tileset;
}

int tinyManager::DestroyTMX(){
	delete doc;
	return 1;
}
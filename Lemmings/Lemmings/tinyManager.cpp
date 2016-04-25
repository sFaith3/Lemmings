#include "tinyManager.h"

tinyManager* tinyManager::tInstance = NULL;

tinyManager::tinyManager(){
	x = y = 0;
	doc = NULL;
}


tinyManager::~tinyManager(){

}

tinyManager* tinyManager::getInstanceTinyManager(){
	if (tInstance == NULL)
		tInstance = new tinyManager();

	return tInstance;
}


void tinyManager::LoadTmx(const char* fileTMX){
	doc = new TiXmlDocument(fileTMX);
	if (!doc->LoadFile()) // parse file
	{
		cout << "Could not load test file '" << fileTMX << "' Error=" << doc->ErrorDesc() << ".\n" <<
			"Exiting." << endl;
		//return -1;
	}
}

vector <vector<int> > tinyManager::LoadMap(int numLayers){
	TiXmlElement *map = doc->FirstChildElement();
	widthMap = atoi(map->Attribute("width")) * atoi(map->Attribute("tilewidth"));
	tileSize = atoi(map->Attribute("tilewidth"));
	TiXmlElement* layer = map->FirstChildElement("layer");
	for (int i = 0; i < numLayers; i++){
		layer = layer->NextSiblingElement("layer");
	}

	TiXmlElement* data = layer->FirstChildElement("data");
	string text = data->GetText(); // Mapa de tmx.
	vector <vector<int> > mapa; // Mapa d'ints.  - mapa[fila(y)][columna(x)] -
	string num = ""; // Contingut a insertar a l'array.
	int layerWidth = atoi(layer->Attribute("width")) - 1;

	// Es desa l'informaci� de 'data' en una matriu de 2 dimensions o en un vector de vectors, per tal de saber les tiles a pintar, gr�cies a la seva ID. I amb la posici� de la matriu se sap on ubicar-la.
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

vector <vector<int> > tinyManager::LoadMapCollision(){
	TiXmlElement *map = doc->FirstChildElement();
	widthMap = atoi(map->Attribute("width")) * atoi(map->Attribute("tilewidth"));
	tileSize = atoi(map->Attribute("tilewidth"));
	TiXmlElement* layer = map->FirstChildElement("layer");
	if ((string)layer->Attribute("name") != "Collider"){
		bool trobat = false;
		while (!trobat){
			layer = layer->NextSiblingElement("layer");
			if ((string)layer->Attribute("name") == "Collider"){
				cout << layer->Attribute("name") << endl;
				trobat = true;
			}
		}
	}

	TiXmlElement* data = layer->FirstChildElement("data");
	string text = data->GetText(); // Mapa de tmx.
	vector <vector<int> > mapaCollisio; // Mapa d'ints.  - mapa[fila(y)][columna(x)] -
	string num = ""; // Contingut a insertar a l'array.
	int layerWidth = atoi(layer->Attribute("width")) - 1;

	// Es desa l'informaci� de 'data' en una matriu de 2 dimensions o en un vector de vectors, per tal de saber les tiles a pintar, gr�cies a la seva ID. I amb la posici� de la matriu se sap on ubicar-la.
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

	return mapaCollisio;
}

tinyManager::Tileset tinyManager::LoadTileset(int numTilesets, vector <vector<int> > mapa){
	TiXmlElement *map = doc->FirstChildElement();
	TiXmlElement* tileset = map->FirstChildElement("tileset");
	for (int i = 0; i < numTilesets; i++){
		tileset = tileset->NextSiblingElement("tileset");
	}
	int tileWidth = atoi(tileset->Attribute("tilewidth"));
	int tileHeight = atoi(tileset->Attribute("tileheight"));
	int spacing = atoi(tileset->Attribute("spacing"));

	TiXmlElement* image = tileset->FirstChildElement("image");
	int tilesetWidth = atoi(image->Attribute("width"));
	int tilesetHeigth = atoi(image->Attribute("height"));
	int numMaxTilesWidth = tilesetWidth / (tileWidth + spacing);
	int numMaxTilesHeight = tilesetHeigth / (tileHeight + spacing);

	Tileset _tileset;
	// Es rec�rre el tileset per s�piguer quina tile es pinta. Els 2 primers for's indiquen la posici� de la pantalla, a la qual se li multiplica per la mesura corresponent (X/Y) de la tile.
	for (int i = 0; i <= x; i++){
		for (int j = 0; j <= y; j++){
			int srcPosX = 0;
			int srcPosY = 0;
			// Es fa un requadre de retall al tileset, i s'indica on se situa.
			for (int h = 1; h <= numMaxTilesHeight; h++){ // Segons la fila on es trobi.
				if (mapa[j][i] < numMaxTilesWidth * h){
					// S'obt� la ID de la tile i se li resta el n�mero total de tiles que hi ha en una fila, multiplicat per la fila on sigui menys 1 m�s l'espai que es deixa entre tile.
					// Perqu� si es troba a la primera fila, no es resta cap, de manera que la x del requadre que s'obt� ja �s de la primera fila.
					srcPosX = (((mapa[j][i] - 1) - (numMaxTilesWidth * (h - 1))) * tileWidth) + (spacing * ((mapa[j][i] - 1) - (numMaxTilesWidth * (h - 1))));
					srcPosY = ((h - 1) * tileHeight) + (spacing * (h - 1));
					break;
				}
			}
			int dstPosX = i * tileWidth;
			int dstPosY = j * tileHeight;

			_tileset.addTile(srcPosX, srcPosY, tileWidth, tileHeight, dstPosX, dstPosY);
		}
	}
	x = y = 0;

	return _tileset;
}


int tinyManager::GetWidthMap(){
	int _widthMap = widthMap;
	if (widthMap != 0)
		widthMap = 0;

	return _widthMap;
}

int tinyManager::GetTileSize(){
	int _tileSize = tileSize;
	if (tileSize != 0)
		tileSize = 0;

	return _tileSize;
}


int tinyManager::DestroyTMX(){
	delete doc;
	return 1;
}
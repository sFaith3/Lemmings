#include "tinyManager.h"

tinyManager* tinyManager::tInstance = NULL;

tinyManager::tinyManager(){
	x = y = 0;
}


tinyManager::~tinyManager(){

}

tinyManager* tinyManager::getInstanceTinyManager(){
	if (tInstance == NULL)
		tInstance = new tinyManager();

	return tInstance;
}


array2D* tinyManager::LoadTmx(const char* fileTMX){
	TiXmlDocument doc(fileTMX);
	if (!doc.LoadFile()) //parse file
	{
		cout << "Could not load test file 'level.xml.' Error=" << doc.ErrorDesc() << ".\n" <<
			"Exiting." << endl;
		//return -1;
	}

	TiXmlElement* map = doc.FirstChildElement();
	TiXmlElement* layer = map->FirstChildElement("layer");
	TiXmlElement* data = layer->FirstChildElement("data");

	string text = data->GetText(); // Mapa de tmx.
	array2D mapa; // Mapa d'ints.
	string num = ""; // Contingut a insertar a l'array.
	int layerWidth = atoi(layer->Attribute("width")) - 1;

	// Es desa l'informació de 'data' en una matriu de 2 dimensions, per tal de saber les tiles a pintar, gràcies a la seva ID. I amb la posició de la matriu se sap on ubicar-la.
	for (int i = 0; i < text.length(); i++){
		if (text[i] == ','){
			mapa[x][y] = atoi(num.c_str());

			num = "";

			if (x < layerWidth)
				x++;
			else{
				y++;
				x = 0;
			}
		}
		else if (text[i] != ' ')
			num += text[i];
	}
	mapa[x][y] = atoi(num.c_str());

	return &mapa;
}

tinyManager::Tileset tinyManager::LoadTileset(const char* fileTMX, int mapa[64][64]){
	TiXmlDocument doc(fileTMX);
	if (!doc.LoadFile()) //parse file
	{
		cout << "Could not load test file 'level.xml.' Error=" << doc.ErrorDesc() << ".\n" <<
			"Exiting." << endl;
		//return -1;
	}

	TiXmlElement* map = doc.FirstChildElement();
	TiXmlElement* tileset = map->FirstChildElement("tileset");
	int tileWidth = atoi(tileset->Attribute("tilewidth"));
	int tileHeight = atoi(tileset->Attribute("tileheight"));
	int spacing = atoi(tileset->Attribute("spacing"));

	TiXmlElement* image = tileset->FirstChildElement("image");
	int tilesetWidth = atoi(image->Attribute("width"));
	int tilesetHeigth = atoi(image->Attribute("height"));
	int numMaxTilesWidth = tilesetWidth / (tileWidth + spacing);
	int numMaxTilesHeight = tilesetHeigth / (tileHeight + spacing);

	Tileset _tileset;
	// Es recórre el tileset per sàpiguer quina tile es pinta. Els 2 primers for's indiquen la posició de la pantalla, a la qual se li multiplica per la mesura corresponent (X/Y) de la tile.
	for (int i = 0; i <= x; i++){
		for (int j = 0; j <= y; j++){
			int srcPosX = 0;
			int srcPosY = 0;
			// Es fa un requadre de retall al tileset, i s'indica on se situa.
			for (int h = 1; h <= numMaxTilesHeight; h++){ // Segons la fila on es trobi.
				if (mapa[i][j] < numMaxTilesWidth * h){
					// S'obté la ID de la tile i se li resta el número total de tiles que hi ha en una fila, multiplicat per la fila on sigui menys 1 més l'espai que es deixa entre tile.
					// Perquè si es troba a la primera fila, no es resta cap, de manera que la x del requadre que s'obté ja és de la primera fila.
					srcPosX = (((mapa[i][j] - 1) - (numMaxTilesWidth * (h - 1))) * tileWidth) + (spacing * ((mapa[i][j] - 1) - (numMaxTilesWidth * (h - 1))));
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
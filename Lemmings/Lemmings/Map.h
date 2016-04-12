#pragma once
#include "ElementGame.h"
#include "tinyManager.h"

class Map :
	public ElementGame
{
private:
	const char* tileset;

	tinyManager* tManager;

public:
	Map();
	~Map();

	void Init(int x, int y, const char* img, const char* tiles, int srcX, int srcY, int w, int h);
	void Render();
};


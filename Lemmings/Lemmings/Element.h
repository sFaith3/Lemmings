#pragma once
#include "Utils.h"
#include "SingletonManager.h"

class Element
{
protected:
	int posX, posY; //Posició de l'element en la pantalla.
	const char* imatge;
	Sint32 idImg;
	int srcPosX, _srcPosX, srcPosY; //Posició inicial en el sprite. Per agafar una regió de l'sprite, cal fer el requadre amb width i height.
	int width, height; //Amplada i alçada de l'sprite.

	SingletonManager* sManager;

public:
	Element();
	~Element();

	void init(int x, int y, const char* img, int srcX, int srcY, int w, int h);
	void render();
};


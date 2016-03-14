#pragma once
#include "Utils.h"
class Element
{
protected:
	int posX, posY; //Posició de l'element en la pantalla.
	const char* sprite;
	int srcPosX, srcPosY; //Posició inicial en el sprite. Per agafar una regió de l'sprite, cal fer el requadre amb width i height.
	int width, height; //Amplada i alçada de l'sprite.

	SingletonManager* singletonManager;

public:
	Element();
	~Element();

	void Init(int x, int y, const char* sp, int srcX, int srcY, int w, int h);
	void Render();
};


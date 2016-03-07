#pragma once
#include "Element.h"
#include "Utils.h"
class ElementGame :
	public Element
{
protected:
	int posX, posY; //Posici� de l'element en la pantalla.
	const char* sprite;
	int srcPosX, srcPosY; //Posici� inicial en el sprite. Per agafar una regi� de l'sprite, cal fer el requadre amb width i height.
	int width, height; //Amplada i al�ada de l'sprite.

	static SingletonManager* getInstanceSingleton();

public:
	ElementGame();
	~ElementGame();

	void Init(int x, int y, const char* sp, int srcX, int srcY, int w, int h);
	void Render();
};


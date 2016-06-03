#pragma once
#include "Utils.h"
#include "SingletonManager.h"

class Element
{
protected:
	int posX, posY; // Posici� de l'element en la pantalla.
	Sint32 idImg;
	int srcPosX, _srcPosX, srcPosY; // Posici� inicial en el sprite. Per agafar una regi� de l'sprite, cal fer el requadre amb width i height.
	int width, height; // Amplada i al�ada de l'sprite.
	float scaleX, scaleY;

	VideoManager* videoManager;

public:
	Element();
	~Element();

	void init(int x, int y, const char* img, int srcX, int srcY, int w, int h, float scaleX, float scaleY);
	void render();

	int GetPosX();
	int GetPosY();
	int GetWidth();
	int GetHeight();

	void SetPosition(int x, int y);
	void SetScale(float x, float y);
};
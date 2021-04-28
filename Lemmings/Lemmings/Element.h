#pragma once
#include "Utils.h"
#include "SingletonManager.h"

class Element
{
protected:
	int posX, posY; // Posició de l'element en la pantalla.
	Sint32 idImg;
	int srcPosX, _srcPosX, srcPosY; // Posició inicial en el sprite. Per agafar una regió de l'sprite, cal fer el requadre amb width i height.
	int width, height; // Amplada i alçada de l'sprite.
	float scaleX, scaleY;

	int pixelCount;

	VideoManager* videoManager;

	AudioManager* audioManager;

public:
	Element();
	~Element();

	void init(int x, int y, const char* img, bool manipulateTexture, int srcX, int srcY, int w, int h, float scaleX, float scaleY);

	int GetPosX();
	int GetPosY();
	int GetWidth();
	int GetHeight();

	void SetPosition(int x, int y);
	void SetScale(float x, float y);

	void ChangePixelColor(Uint32 colorKey, Uint32 newColor);
};
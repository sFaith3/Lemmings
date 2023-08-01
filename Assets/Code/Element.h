#pragma once
#include "Utils.h"
#include "SingletonManager.h"

class Element
{
protected:
	int posX, posY; // Element position in the screen.
	Sint32 idImg;
	int srcPosX, _srcPosX, srcPosY; // Initial position in the sprite. To take a region from the sprite it's necessary to make the box with width and height.
	int width, height; // Width and height of the sprite.
	float scaleX, scaleY;

	int pixelCount;

	VideoManager* videoManager;
	AudioManager* audioManager;

public:
	Element();
	~Element();

	void init(int x, int y, const char* img, bool manipulateTexture, int srcX, int srcY, int w, int h, float scaleX, float scaleY);

	int getPosX();
	int getPosY();
	int getWidth();
	int getHeight();

	void setPosition(int x, int y);
	void setScale(float x, float y);

	void changePixelColor(Uint32 colorKey, Uint32 newColor);
};
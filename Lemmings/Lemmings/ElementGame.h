#pragma once
#include "Element.h"
class ElementGame :
	public Element
{
protected:
	// Animacio de SpriteSheet
	int widthSpriteSheet;
	int heightSpriteSheet;
	int toNextSpriteX;
	int toNextSpriteY;
	int numImatges;
	int contImatges;
	int fpsAnimacio, currFpsAnim;
	int numSaltsImatges;

public:
	ElementGame();
	~ElementGame();

	void init(int x, int y, const char* img, int srcX, int srcY, int w, int h, float scaleX, float scaleY, int wSpriteSheet, int hSpriteSheet, int toNextSpriteX, int numImgs, int fpsAnim);

	//Animacio de SpriteSheet
	void UpdateAnimacio();

	int GetPosX();
	int GetPosY();
	int GetWidth();
	int GetHeight();
};


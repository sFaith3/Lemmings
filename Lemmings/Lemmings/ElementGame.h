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
	int fpsAnimacio;
	bool saltaImatges;

public:
	ElementGame();
	~ElementGame();

	void init(int x, int y, const char* img, int srcX, int srcY, int w, int h);

	//Animacio de SpriteSheet
	void SetAnimacio();
};


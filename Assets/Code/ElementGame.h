#pragma once
#include "Element.h"

class ElementGame :
	public Element
{
protected:
	int widthSpriteSheet, heightSpriteSheet; // Total width and height of the spritesheet.
	int toNextSpriteX, toNextSpriteY; // Positions to get the next sprite.
	int numSprites; // The number of sprite that has that spritesheet.
	int currentSprite; // The current sprite of the animation that is being rendered.
	int timeToNextSprite, currTimeToNextSprite; // Time to change the sprite of the animation and his current time.
												// When 'currTimeToNextSprite' is equal to 'timeToNextSprite', the sprite changes.
	int numRowsSpritesheet; // Number of rows to be moved in total. When the sprite reaches the boundary of the spritesheet, without this being the last, it makes a row jump in the spritesheet
							// and is positioned in the initial X of this. The maximum number of moves per row.

public:
	ElementGame();
	~ElementGame();

	void init(int x, int y, const char* img, bool manipulateTexture, int srcX, int srcY, int w, int h, float scaleX, float scaleY, int wSpriteSheet, int hSpriteSheet, int toNextSpriteX, int numSprites, int timeToNextSprite);
	void render();

	void UpdateAnimation(); // Animation of the spritesheet.
};


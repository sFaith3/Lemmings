#include "ElementGame.h"


ElementGame::ElementGame(){
}

ElementGame::~ElementGame(){
}


void ElementGame::init(int x, int y, const char* img, bool manipulateTexture, int srcX, int srcY, int w, int h, float scaleX, float scaleY, int wSpriteSheet, int hSpriteSheet, int toNextSpriteX, int numSprites, int timeToNextSprite){
	Element::init(x, y, img, manipulateTexture, srcX, srcY, w, h, scaleX, scaleY);
	widthSpriteSheet = wSpriteSheet;
	heightSpriteSheet = hSpriteSheet;
	this->toNextSpriteX = toNextSpriteY = toNextSpriteX;
	this->numSprites = numSprites;
	currentSprite = 1;
	this->timeToNextSprite = timeToNextSprite;
	currTimeToNextSprite = 0;
	numRowsSpritesheet = 0;
}

void ElementGame::render(){
	videoManager->renderTexture(idImg, srcPosX, srcPosY, width, height, scaleX, scaleY, posX, posY, 0, 0, 0, SDL_FLIP_NONE);
}


void ElementGame::UpdateAnimation() {
	if (currTimeToNextSprite == timeToNextSprite) {
		if (currentSprite < numSprites) {
			if (srcPosX + toNextSpriteX > widthSpriteSheet) {
				srcPosY += toNextSpriteY;
				srcPosX = 0;
				numRowsSpritesheet++;
			}
			srcPosX += toNextSpriteX;
			currentSprite++;
		}
		else {
			srcPosX = _srcPosX;
			currentSprite = 1;
			if (numRowsSpritesheet > 0) {
				for (int i = 0; i < numRowsSpritesheet; i++)
					srcPosY -= toNextSpriteY;
				numRowsSpritesheet = 0;
			}
		}
		currTimeToNextSprite = 0;
	}
	else {
		currTimeToNextSprite++;
	}
}
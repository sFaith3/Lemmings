#include "ElementGame.h"


ElementGame::ElementGame(){
}


ElementGame::~ElementGame(){
}


void ElementGame::init(int x, int y, const char* img, int srcX, int srcY, int w, int h, float scaleX, float scaleY, int wSpriteSheet, int hSpriteSheet, int toNextSpriteX, int numImgs, int fpsAnim){
	Element::init(x, y, img, srcX, srcY, w, h, scaleX, scaleY);
	widthSpriteSheet = wSpriteSheet;
	heightSpriteSheet = hSpriteSheet;
	this->toNextSpriteX = toNextSpriteY = toNextSpriteX;
	numImatges = numImgs;
	contImatges = 1;
	fpsAnimacio = fpsAnim;
	currFpsAnim = 0;
	numSaltsImatges = 0;
}

void ElementGame::UpdateAnimacio(){
	if (currFpsAnim == fpsAnimacio){
		if (contImatges < numImatges){
			if (srcPosX + toNextSpriteX > widthSpriteSheet){
				srcPosY += toNextSpriteY;
				srcPosX = 0;
				numSaltsImatges++;
			}
			srcPosX += toNextSpriteX;
			contImatges++;
		}
		else{
			srcPosX = _srcPosX;
			contImatges = 1;
			if (numSaltsImatges > 0){
				for (int i = 0; i < numSaltsImatges; i++)
					srcPosY -= toNextSpriteY;
				numSaltsImatges = 0;
			}
		}
		currFpsAnim = 0;
	}
	else{
		currFpsAnim++;
	}
}
#include "ElementGame.h"


ElementGame::ElementGame(){
}


ElementGame::~ElementGame(){
}


void ElementGame::init(int x, int y, const char* img, int srcX, int srcY, int w, int h, float scaleX, float scaleY, int wSpriteSheet, int hSpriteSheet, int toNextSpriteX, int numImgs, int contImgs, bool saltaImgs, int fpsAnim){
	Element::init(x, y, img, srcX, srcY, w, h, scaleX, scaleY);
	widthSpriteSheet = wSpriteSheet;
	heightSpriteSheet = hSpriteSheet;
	this->toNextSpriteX = toNextSpriteY = toNextSpriteX;
	numImatges = numImgs;
	contImatges = contImgs;
	saltaImatges = saltaImgs;
	fpsAnimacio = fpsAnim;
}

void ElementGame::UpdateAnimacio(){
	if (fpsAnimacio == 2){
		if (contImatges < numImatges){
			if (srcPosX + toNextSpriteX > widthSpriteSheet){
				srcPosY += toNextSpriteX;
				srcPosX = 0;
				saltaImatges = true;
			}
			srcPosX += toNextSpriteX;
			contImatges++;
		}
		else{
			srcPosX = _srcPosX;
			contImatges = 1;
			if (saltaImatges){
				srcPosY -= toNextSpriteY;
			}
		}
		fpsAnimacio = 0;
	}
	else{
		fpsAnimacio++;
	}
}
#include "ElementGame.h"


ElementGame::ElementGame(){
}


ElementGame::~ElementGame(){
}


void ElementGame::init(int x, int y, const char* img, int srcX, int srcY, int w, int h){
	Element::init(x, y, img, srcX, srcY, w, h);
}

void ElementGame::SetAnimacio(){
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
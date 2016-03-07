#include "ElementGame.h"


ElementGame::ElementGame(){
}


ElementGame::~ElementGame(){
}


void ElementGame::Init(int x, int y, const char* sp, int srcX, int srcY, int w, int h){
	posX = x;
	posY = y;
	sprite = sp;
	srcPosX = srcX;
	srcPosY = srcY;
	width = w;
	height = h;
}

void ElementGame::Render(){
	getInstanceSingleton()->getVideo()->renderTexture(getInstanceSingleton()->getResource()->getGraphicID(sprite), srcPosX, srcPosY, width, height, posX, posY, 0, 0, 0);
}
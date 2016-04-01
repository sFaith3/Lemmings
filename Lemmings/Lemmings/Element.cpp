#include "Element.h"


Element::Element(){
	sManager = SingletonManager::getInstanceSingleton();
}


Element::~Element()
{
}

void Element::Init(int x, int y, const char* sp, int srcX, int srcY, int w, int h){
	posX = x;
	posY = y;
	sprite = sp;
	srcPosX = srcX;
	srcPosY = srcY;
	width = w;
	height = h;
}

void Element::Render(){
	//sManager->videoManager->renderTexture(sManager->videoManager->getTextureID(sprite), srcPosX, srcPosY, width, height, posX, posY, 0, 0, 0);
	sManager->videoManager->renderGraphic(sManager->videoManager->getGraphicID(sprite), srcPosX, srcPosY, width, height, posX, posY);
}
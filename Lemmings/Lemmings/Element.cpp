#include "Element.h"


Element::Element(){
	sManager = SingletonManager::getInstanceSingleton();
}


Element::~Element()
{
}

void Element::Init(int x, int y, const char* img, int srcX, int srcY, int w, int h){
	posX = x;
	posY = y;
	imatge = img;
	srcPosX = srcX;
	srcPosY = srcY;
	width = w;
	height = h;
}

void Element::Render(){
	//sManager->videoManager->renderTexture(sManager->videoManager->getTextureID(imatge), srcPosX, srcPosY, width, height, posX, posY, 0, 0, 0);
	sManager->getVideoManager()->renderGraphic(sManager->getVideoManager()->getGraphicID(imatge), srcPosX, srcPosY, width, height, posX, posY);
}
#include "Element.h"


Element::Element(){
	sManager = SingletonManager::getInstanceSingleton();
}


Element::~Element()
{
}

void Element::init(int x, int y, const char* img, int srcX, int srcY, int w, int h){
	posX = x;
	posY = y;
	imatge = img;
	idImg = sManager->getVideoManager()->getTextureID(imatge);
	srcPosX = _srcPosX = srcX;
	srcPosY = srcY;
	width = w;
	height = h;
}

void Element::render(){
	sManager->getVideoManager()->renderTexture(idImg, srcPosX, srcPosY, width, height, posX, posY, 0, 0, 0);
}
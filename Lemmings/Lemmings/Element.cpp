#include "Element.h"


Element::Element(){
	videoManager = SingletonManager::getInstanceSingleton()->getVideoManager();
}


Element::~Element()
{
}

void Element::init(int x, int y, const char* img, int srcX, int srcY, int w, int h, float scaleX, float scaleY){
	posX = x;
	posY = y;
	imatge = img;
	idImg = videoManager->getTextureID(imatge);
	srcPosX = _srcPosX = srcX;
	srcPosY = srcY;
	width = w;
	height = h;
	this->scaleX = scaleX;
	this->scaleY = scaleY;
}

void Element::render(){
	videoManager->renderTexture(idImg, srcPosX, srcPosY, width, height, scaleX, scaleY, posX, posY, 0, 0, 0);
}
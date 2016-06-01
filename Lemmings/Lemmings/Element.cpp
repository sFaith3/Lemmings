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


int Element::GetPosX(){
	return posX;
}

int Element::GetPosY(){
	return posY;
}

int Element::GetWidth(){
	return width;
}

int Element::GetHeight(){
	return height;
}

void Element::SetPosition(int x, int y){
	posX = x;
	posY = y;
}

void Element::SetScale(float x, float y){
	scaleX = x;
	scaleY = y;
}
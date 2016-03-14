#include "Element.h"


Element::Element()
{
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

	singletonManager = SingletonManager::getInstanceSingleton();
}

void Element::Render(){
	singletonManager->videoManager->renderTexture(singletonManager->resourceManager->getGraphicID(sprite), srcPosX, srcPosY, width, height, posX, posY, 0, 0, 0);
}
#include "Element.h"


Element::Element(){
	videoManager = SingletonManager::getInstanceSingleton()->getVideoManager();
	audioManager = SingletonManager::getInstanceSingleton()->getAudioManager();
}


Element::~Element()
{
}

void Element::init(int x, int y, const char* img, bool manipulateTexture, int srcX, int srcY, int w, int h, float scaleX, float scaleY){
	posX = x;
	posY = y;
	idImg = videoManager->getTextureID(img, manipulateTexture);
	srcPosX = _srcPosX = srcX;
	srcPosY = srcY;
	width = w;
	height = h;
	this->scaleX = scaleX;
	this->scaleY = scaleY;

	if (manipulateTexture){
		// The texture must be locked to access and get the number of pixels
		videoManager->lockTexture(idImg);
		pixelCount = videoManager->getPixelCount(height);
		videoManager->unlockTexture(idImg);
	}
}


int Element::getPosX(){
	return posX;
}

int Element::getPosY(){
	return posY;
}

int Element::getWidth(){
	return width;
}

int Element::getHeight(){
	return height;
}


void Element::setPosition(int x, int y){
	posX = x;
	posY = y;
}

void Element::setScale(float x, float y){
	scaleX = x;
	scaleY = y;
}


void Element::changePixelColor(Uint32 colorKey, Uint32 newColor){
	// Lock to manipulate pixels
	videoManager->lockTexture(idImg);
	
	Uint32* pixels = videoManager->getPixels();
	for (int i = 0; i < pixelCount; i++){
		if (pixels[i] == colorKey){
			pixels[i] = newColor;
		}
	}
	
	// Unlock to "save" manipulation
	videoManager->unlockTexture(idImg);
}
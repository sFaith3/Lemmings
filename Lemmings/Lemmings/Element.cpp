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

	contImatges = 1;
	saltaImatges = false;
	fpsAnimacio = 0;
}

void Element::Render(){
	//sManager->videoManager->renderTexture(sManager->videoManager->getTextureID(imatge), srcPosX, srcPosY, width, height, posX, posY, 0, 0, 0);
	sManager->getVideoManager()->renderGraphic(sManager->getVideoManager()->getGraphicID(imatge), srcPosX, srcPosY, width, height, posX, posY);
}

void Element::SetAnimacio(){
	if (fpsAnimacio == 2){
		if (contImatges < numImatges){
			if (srcPosX + 20 > 318){
				srcPosY += 20;
				srcPosX = 0;
				saltaImatges = true;
			}
			srcPosX += 20;
			contImatges++;
		}
		else{
			srcPosX = 0;
			contImatges = 1;
			if (saltaImatges){
				srcPosY -= 20;
			}
		}
		fpsAnimacio = 0;
	}
	else{
		fpsAnimacio++;
	}
}
#include "ElementHUD.h"


ElementHUD::ElementHUD()
{
}


ElementHUD::~ElementHUD()
{
}


void ElementHUD::render(){
	videoManager->renderTexture(idImg, srcPosX, srcPosY, width, height, scaleX, scaleY, posX, posY);
}
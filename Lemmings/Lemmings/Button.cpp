#include "Button.h"


Button::Button(){
	SingletonManager* sManager = SingletonManager::getInstanceSingleton();
	inputManager = sManager->getInputManager();
	videoManager = sManager->getVideoManager();
}


Button::~Button(){
}


int Button::GetId(){
	return id;
}


void Button::init(int _id, int _posX, int _posY, int _width, int _height, float _scaleX, float _scaleY, int _posXini, int _posYini, const char* imgNormal, const char* imgButPressed){
	id = _id;
	posX = _posX;
	posY = _posY;
	width = _width;
	height = _height;
	scaleX = _scaleX;
	scaleY = _scaleY;
	posXini = _posXini;
	posYini = _posYini;
	idImgNormal = videoManager->getTextureID(imgNormal);
	idImgButPressed = videoManager->getTextureID(imgButPressed);
	pressed = false;
}


bool Button::update(){
	if (inputManager->CheckClick()){
		int mouseX, mouseY;
		inputManager->GetMouseXY(mouseX, mouseY);
		if ((mouseX >= posX) && (mouseX <= posX + width) && (mouseY >= posY) && (mouseY <= posY + height)){
			//pressed = true;
			return true;
		}
	}
	return false;
}


void Button::render(){
	if (idImgNormal != -1)
		videoManager->renderTexture(idImgNormal, posXini, posYini, width, height, scaleX, scaleY, posX, posY, 0, 0, 0);
	
	if (pressed){
		if (idImgButPressed != -1)
			videoManager->renderTexture(idImgButPressed, posXini, posYini, width, height, scaleX, scaleY, posX, posY, 0, 0, 0);
		
		// A l'inputManager hi hauria d'haver un MOUSEBUTTONUP i s'hauria de fer
		// més comprovacions per tal de no repetir-se si el deixes pressionat.
		/*if (!inputManager->CheckClick())
			pressed = false;*/
	}
}


void Button::SetPressed(bool _pressed){
	pressed = _pressed;
}
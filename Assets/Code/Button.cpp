#include "Button.h"


Button::Button(){
	SingletonManager* sManager = SingletonManager::getInstanceSingleton();
	inputManager = sManager->getInputManager();
	videoManager = sManager->getVideoManager();
}


Button::~Button(){
}


void Button::init(int _id, int _posX, int _posY, int _width, int _height, float _scaleX, float _scaleY, int _posXini, int _posYini, const char* imgNormal, const char* imgPressed){
	id = _id;
	posX = _posX * _scaleX;
	posY = _posY * _scaleY;
	width = _width;
	height = _height;
	scaleX = _scaleX;
	scaleY = _scaleY;
	posXini = _posXini;
	posYini = _posYini;
	idImgNormal = videoManager->getTextureID(imgNormal);
	idImgPressed = videoManager->getTextureID(imgPressed);
	pressed = false;
}


bool Button::update(){
	if (inputManager->isClickLeft()){
		int mouseX, mouseY;
		inputManager->getMouseXY(mouseX, mouseY);
		if ((mouseX >= posX) && (mouseX <= posX + width) && (mouseY >= posY) && (mouseY <= posY + height))
			return true;
	}
	return false;
}


void Button::render(){
	if (idImgNormal != -1)
		videoManager->renderTexture(idImgNormal, posXini, posYini, width, height, scaleX, scaleY, posX, posY);
	
	if (pressed){
		if (idImgPressed != -1)
			videoManager->renderTexture(idImgPressed, posXini, posYini, width, height, scaleX, scaleY, posX, posY);
	}
}


int Button::getId() {
	return id;
}


void Button::setPressed(bool _pressed){
	pressed = _pressed;
}
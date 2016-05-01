#include "Button.h"

Button::Button(){
}


Button::~Button(){
}


int Button::GetId(){
	return id;
}


void Button::init(int _id, int _posX, int _posY, int _width, int _height, int _posXini, int _posYini, const char* _path){
	id = _id;
	posX = _posX;
	posY = _posY;
	width = _width;
	height = _height;
	posXini = _posXini;
	posYini = _posYini;
	path = _path;

	inputManager = sManager->getInputManager();
}


bool Button::update(){
	if (inputManager->CheckClick()){
		int mouseX, mouseY;
		inputManager->GetMouseXY(mouseX, mouseY);
		if ((mouseX >= posX) && (mouseX <= posX + width) && (mouseY >= posY) && (mouseY <= posY + height))
			return true;
	}
	return false;
}


void Button::render(){
	if (path != NULL){
		int imgB = sManager->getVideoManager()->getGraphicID(path);
		sManager->getVideoManager()->renderGraphic(imgB, posX, posY, width, height, posXini, posYini);
	}
}
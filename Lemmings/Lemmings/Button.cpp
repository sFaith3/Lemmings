#include "Button.h"

Button::Button()
{
}


Button::~Button()
{
}


string Button::GetId(){
	return id;
}

bool Button::GetClick(){
	return click;
}


void Button::init(string _id, int _posX, int _posY, int _width, int _height, int _posXini, int _posYini, const char* _path){
	id = _id;
	posX = _posX;
	posY = _posY;
	width = _width;
	height = _height;
	posXini = _posXini;
	posYini = _posYini;
	path = _path;
	click = false;
}


void Button::update(bool mouse, int posXmouse, int posYmouse){
	if (mouse){

		if ((posXmouse >= posX) && (posXmouse <= posX + width) && (posYmouse >= posY) && (posYmouse <= posY + height)){

			click = true;
		}
	}
	else if (!mouse && click)
		click = false;
}


void Button::render(){

	int imgB = sManager->getVideoManager()->getGraphicID(path);
	sManager->getVideoManager()->renderGraphic(imgB, posX, posY, width, height, posXini, posYini);
}
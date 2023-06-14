#include "Cursor.h"


Cursor* Cursor::cInstance = NULL;

Cursor::Cursor() {
	const int DimensionsNormal = 12;
	ElementHUD::init(0, 0, "Assets/Art/Images/Cursor/cursorNormal.png", false, 0, 0, DimensionsNormal, DimensionsNormal, 1, 1);

	idImgNormal = idImg;
	widthNormal = heightNormal = DimensionsNormal;
	idImgHover = videoManager->getTextureID("Assets/Art/Images/Cursor/cursorHover.png");
	const int DimensionsHover = 14;
	widthHover = heightHover = DimensionsHover;

	changedCursor = false;

	inputManager = SingletonManager::getInstanceSingleton()->getInputManager();
}


Cursor::~Cursor()
{
}


Cursor* Cursor::getInstanceCursor(){
	if (cInstance == NULL)
		cInstance = new Cursor();

	return cInstance;
}


void Cursor::update(){
	inputManager->getMouseXY(posX, posY);
	posX -= width / 2;
	posY -= height / 2;
}


bool Cursor::isCursorChanged(){
	return changedCursor;
}

void Cursor::changeCursor() {
	changedCursor = !changedCursor;
	idImg = changedCursor ? idImgHover : idImgNormal;
	width = changedCursor ? widthHover : widthNormal;
	height = changedCursor ? heightHover : heightNormal;
}
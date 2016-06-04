#include "Cursor.h"


Cursor* Cursor::cInstance = NULL;

Cursor::Cursor(){
	ElementHUD::init(0, 0, "Assets/Images/Cursor/normalCursor.png", 0, 0, 12, 12, 1, 1);

	idImg1 = idImg;
	width1 = 12;
	height1 = 12;
	idImg2 = videoManager->getTextureID("Assets/Images/Cursor/changedCursor2.png");
	width2 = 14;
	height2 = 14;

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


void Cursor::Update(){
	inputManager->GetMouseXY(posX, posY);
	posX -= width / 2;
	posY -= height / 2;
}


bool Cursor::GetChangedCursor(){
	return changedCursor;
}

void Cursor::ChangeCursor(){
	changedCursor = !changedCursor;
	if (changedCursor){
		idImg = idImg2;
		width = width2;
		height = height2;
	}
	else{
		idImg = idImg1;
		width = width1;
		height = height1;
	}
}
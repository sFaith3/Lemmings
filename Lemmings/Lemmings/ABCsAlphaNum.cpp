#include "ABCsAlphaNum.h"


ABCsAlphaNum::ABCsAlphaNum(){
	videoManager = SingletonManager::getInstanceSingleton()->getVideoManager();
	idImg = videoManager->getTextureID("Assets/Images/ABCAlphaNum/alphabet.png");
}


ABCsAlphaNum::~ABCsAlphaNum()
{
}


void ABCsAlphaNum::init(int x, int y, float scaleX, float scaleY, int alphaNum){
	posX = x;
	posY = y;

	xIni = yIni = 3;
	width = 16;
	height = 15;
	this->scaleX = scaleX;
	this->scaleY = scaleY;
	spacingX = 1;
	spacingY = 1;
	digitsMaxRow = 13;

	ChangeValue(alphaNum);
}

void ABCsAlphaNum::ChangeValue(int num){
	int pos = NULL;
	switch (num){
	case 0:
		pos = ZERO;
		break;
	case 1:
		pos = ONE;
		break;
	case 2:
		pos = TWO;
		break;
	case 3:
		pos = THREE;
		break;
	case 4:
		pos = FOUR;
		break;
	case 5:
		pos = FIVE;
		break;
	case 6:
		pos = SIX;
		break;
	case 7:
		pos = SEVEN;
		break;
	case 8:
		pos = EIGHT;
		break;
	case 9:
		pos = NINE;
		break;
	}
	
	int row = 0;
	if (pos >= ONE && pos <= ZERO)
		row = 4;

	if (row > 0)
		pos -= (digitsMaxRow * row);

	srcX = xIni + ((width + spacingX) * pos);
	srcY = yIni + ((height + spacingY) * row);
}


void ABCsAlphaNum::ChangeValue(string lletres){
	/*int pos = NULL;
	switch (alpha){ // AMB LA RESTA DE L'SPRITESHEET QUE NO SIGUIN NÚMEROS.
	case 0:
		pos = ZERO;
		break;
	case 1:
		pos = ONE;
		break;
	case 2:
		pos = TWO;
		break;
	case 3:
		pos = THREE;
		break;
	case 4:
		pos = FOUR;
		break;
	case 5:
		pos = FIVE;
		break;
	case 6:
		pos = SIX;
		break;
	case 7:
		pos = SEVEN;
		break;
	case 8:
		pos = EIGHT;
		break;
	case 9:
		pos = NINE;
		break;
	}

	int row = 0;
	if (pos >= N && pos <= Z)
		row = 1;
	else if (pos >= a && pos <= m)
		row = 2;
	else if (pos >= n && pos <= z)
		row = 3;
	//Resta spritesheets.

	if (row > 0)
		pos -= (digitsMaxRow * row);

	srcX = xIni + ((width + spacing) * pos);
	srcY = yIni + ((height + spacing) * row);*/	
}


void ABCsAlphaNum::Render(){
	videoManager->renderTexture(idImg, srcX, srcY, width, height, scaleX, scaleY, posX, posY, 0, 0, 0);
}
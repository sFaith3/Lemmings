#include "ABCsAlphaNum.h"


ABCsAlphaNum::ABCsAlphaNum(){
	videoManager = SingletonManager::getInstanceSingleton()->getVideoManager();
	idImg = videoManager->getTextureID("Assets/Art/Images/ABCsAlphaNum/alphabet.png");
}

ABCsAlphaNum::~ABCsAlphaNum(){
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

	changeValue(alphaNum);
}

void ABCsAlphaNum::init(int x, int y, float scaleX, float scaleY, char alphaLetter){
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

	changeValue(alphaLetter);
}

void ABCsAlphaNum::render(){
	videoManager->renderTexture(idImg, srcX, srcY, width, height, scaleX, scaleY, posX, posY);
}


void ABCsAlphaNum::move(int x, int y){
	posX += x;
	posY += y;
}

void ABCsAlphaNum::changeValue(int num){
	switch (num){
	case 0:
		num = ZERO;
		break;
	default:
		num += 51;
		break;
	}

	int row = 4;
	num -= (digitsMaxRow * row);

	srcX = xIni + ((width + spacingX) * num);
	srcY = yIni + ((height + spacingY) * row);
}

/*
* @param character can not be a number
*/
void ABCsAlphaNum::changeValue(char character) {
	if ((character >= 'A' && character <= 'Z') || (character >= 'a' && character <= 'z')) {
		character -= 'A';
		if (character >= 32) // -6 because in ASCII there are signs between uppercase and lowercase letters.
			character -= 6;
	}
	else {
		switch (character) {
		case '!': character = EXCLAMATION;
			break;
		case '@': character = AT;
			break;
		case '#': character = HASH;
			break;
		case '$': character = DOLLAR;
			break;
		case '%': character = PERCENT;
			break;
		default:
			break;
		}
	}

	int row = 0;
	if (character >= N && character <= Z)
		row = 1;
	else if (character >= a && character <= m)
		row = 2;
	else if (character >= n && character <= z)
		row = 3;
	else if (character >= EXCLAMATION) {
		row = 5;
		// Changes to the spritesheet set
		character += 3;
	}

	if (row > 0)
		character -= (digitsMaxRow * row);

	srcX = xIni + ((width + spacingX) * character);
	srcY = yIni + ((height + spacingY) * row);
}
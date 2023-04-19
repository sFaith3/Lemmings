#include "ABCsAlphaNum.h"


ABCsAlphaNum::ABCsAlphaNum(){
	videoManager = SingletonManager::getInstanceSingleton()->getVideoManager();
	idImg = videoManager->getTextureID("Assets/Art/Images/ABCsAlphaNum/alphabet.png");
}


ABCsAlphaNum::~ABCsAlphaNum(){
}


void ABCsAlphaNum::Init(int x, int y, float scaleX, float scaleY, int alphaNum){
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



void ABCsAlphaNum::Init(int x, int y, float scaleX, float scaleY, char alphaLetter){
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

	ChangeValue(alphaLetter);
}

void ABCsAlphaNum::Render(){
	videoManager->renderTexture(idImg, srcX, srcY, width, height, scaleX, scaleY, posX, posY);
}


void ABCsAlphaNum::Move(int x, int y){
	posX += x;
	posY += y;
}

void ABCsAlphaNum::ChangeValue(int num){
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

void ABCsAlphaNum::ChangeValue(char noNum){
	if ((noNum >= 'A' && noNum <= 'Z') || (noNum >= 'a' && noNum <= 'z')){
		noNum -= 'A';
		if (noNum >= 32)
			noNum -= 6; // -6 perquè en ASCII hi ha signes entremig de les lletres en majúscula i minúscula.
	}
	else{
		switch (noNum){
		case '!': noNum = EXCLAMATION;
			break;
		case '@': noNum = AT;
			break;
		case '#': noNum = HASH;
			break;
		case '$': noNum = DOLLAR;
			break;
		case '%': noNum = PERCENT;
			break;
		default:
			break;
		}
	}

	int row = 0;
	if (noNum >= N && noNum <= Z)
		row = 1;
	else if (noNum >= a && noNum <= m)
		row = 2;
	else if (noNum >= n && noNum <= z)
		row = 3;
	else if (noNum >= EXCLAMATION){
		row = 5;
		noNum += 3; // Canvis per a l'spritesheet posat.
	}

	if (row > 0)
		noNum -= (digitsMaxRow * row);

	srcX = xIni + ((width + spacingX) * noNum);
	srcY = yIni + ((height + spacingY) * row);
}
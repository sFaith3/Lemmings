#include "Lemming.h"


Lemming::Lemming()
{
}


Lemming::~Lemming()
{
}


void Lemming::Init(int x, int y, const char* sp, int srcX, int srcY, int w, int h){
	ElementGame::Init(x, y, sp, srcX, srcY, w, h);
	estat = FALL;
}

void Lemming::Update(){
	switch (estat){
	case IDLE:
		break;
	case MOVE:
		switch (dir){
		case 0:
			posX++;
			break;
		case 2:
			posX--;
			break;
		}
		break;
	case FALL:
		posY++;
		break;
	}
}
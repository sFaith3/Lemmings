#include "Lemming.h"


Lemming::Lemming(){

}


Lemming::~Lemming(){

}


void Lemming::Init(int x, int y, const char* sp, int srcX, int srcY, int w, int h){
	ElementGame::Init(x, y, sp, srcX, srcY, w, h);
	estat = FALL;
}

void Lemming::Update(){
	switch (estat){
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
		posY+=2;
		break;
	}
}

int Lemming::GetPosX(){
	return posX;
}

int Lemming::GetPosY(){
	return posY;
}

int Lemming::GetWidth(){
	return width;
}

int Lemming::GetHeight(){
	return height;
}

int Lemming::GetDir(){
	return dir;
}


int Lemming::GetEstat(){
	return estat;
}

void Lemming::SetMove(){
	estat = MOVE;
}

void Lemming::SetFall(){
	estat = FALL;
}


void Lemming::Moure(bool dreta){

}

void Lemming::TrencarMur(){

}

void Lemming::Levitar(){

}

void Lemming::Escalar(){

}

void Lemming::Cavar(){

}

void Lemming::Picar(){

}

void Lemming::Caure(){

}

void Lemming::Inmovilitzar(){

}

void Lemming::Construir(){

}

void Lemming::Explotar(){

}


void Lemming::SetParaigues(){

}

void Lemming::SetEscalar(){

}

#include "Lemming.h"


Lemming::Lemming(){

}


Lemming::~Lemming(){

}


void Lemming::Init(int x, int y, const char* sp, int srcX, int srcY, int w, int h){
	ElementGame::Init(x, y, sp, srcX, srcY, w, h);
	estat = FALL;
	numImatges = 4;
	paraigues = false;
	escalar = false;
	temps = 5;
	velocitat = 1;
	
}

void Lemming::Update(){
	switch (estat){
	case MOVE:
	
		Moure(dir);
		break;
	case FALL:
		Caure();
		break;
	case BREAK:

		break;
	case EXPLOSION:
		Explotar();
		break;
	}

	SetAnimacio();
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

void Lemming::SetMoure(){
	estat = MOVE;
	numImatges = 10;
}

void Lemming::SetCaure(){
	estat = FALL;
	numImatges = 10;
}


void Lemming::Moure(int dir){
	switch (dir){
	case 0:
		posX += velocitat;
		break;
	case 2:
		posX -= velocitat;
		break;
	}
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
	posY += velocitat*2;
}

void Lemming::Inmovilitzar(){

}

void Lemming::ConstruirEscala(){

}

void Lemming::Explotar(){
	if (temps > 0){
		temps -= 1;
	}
	else{
		estat = DEAD;
	}
}


void Lemming::SetParaigues(){
	paraigues = true;
}

void Lemming::SetEscalar(){
	escalar = true;
}



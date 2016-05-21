#include "Lemming.h"


Lemming::Lemming(){

}


Lemming::~Lemming(){

}


void Lemming::init(int x, int y){
	ElementGame::init(x, y, "Assets/Images/lem_ani.png", 0, 40, 10, 10, 318, 0, 20, 4, 1, false, 0);
	estat = FALL;
	dir = 0;
	flipType = SDL_FLIP_NONE;
	paraigues = false;
	escalar = false;
	temps = 5;
	velocitat = 1;
	pintW = 20;
	pintH = 20;
}

void Lemming::update(Map *fons, int x1, int y1, int x2, int y2){ //Es pot optimitzar codi. Com l'if pel SetCaure().
	switch (estat){
	case MOVE:
		if (fons->GetMapa(x1 + 1, y2) == 0 && fons->GetMapa(x2 - 1, y2) == 0)
			SetCaure();
		else if (dir == 0){ // Cap a la dreta.
			if (fons->GetMapa(x2, y2 - 1) != 0 && fons->GetMapa(x2, y2 - 2) == 0)
				Moure(true); // Diagonal cap amunt.
			else if (fons->GetMapa(x2, y2) == 0 && fons->GetMapa(x2, y2 + 1) != 0)
				Moure(false); // Cap avall.
			else if (fons->GetMapa(x2 - 1, y1 + 1) != 0)
				SetDir(2);
			else
				Moure();
		}
		else{
			if (fons->GetMapa(x1, y2 - 1) != 0 && fons->GetMapa(x1, y2 - 2) == 0)
				Moure(true); // Diagonal cap amunt.
			else if (fons->GetMapa(x1, y2) == 0 && fons->GetMapa(x1, y2 + 1) != 0)
				Moure(false); // Cap avall.
			else if (fons->GetMapa(x1, y1 + 1) != 0)
				SetDir(0);
			else
				Moure();
		}
		break;
	case FALL:
		Caure();
		if (fons->GetMapa(x1 + velocitat, y2 + velocitat) != 0 || fons->GetMapa(x2 - velocitat, y2 + velocitat) != 0)
			SetMoure();
		break;
	case BREAK:
		if (fons->GetMapa(x1, y1) == 0 && fons->GetMapa(x2, y2) == 0)
			SetCaure();
		break;
	case EXPLOSION:
		Explotar();
		if (fons->GetMapa(x1, y1) == 0 && fons->GetMapa(x2, y2) == 0)
			SetCaure();
		break;
	}

	UpdateAnimacio();
}

void Lemming::render(){
	sManager->getVideoManager()->renderTexture(idImg, srcPosX, srcPosY, pintW, pintH, posX, posY, 0, 0, 0, flipType);
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

void Lemming::SetDir(int dir){
	this->dir = dir;
	if (flipType == SDL_FLIP_NONE)
		flipType = SDL_FLIP_HORIZONTAL;
	else
		flipType = SDL_FLIP_NONE;
}

int Lemming::GetEstat(){
	return estat;
}

void Lemming::SetMoure(){
	estat = MOVE;
	numImatges = 10;
	srcPosX = _srcPosX = 0;
	srcPosY = 0;
}

void Lemming::SetCaure(){
	estat = FALL;
	numImatges = 4;
	srcPosX = _srcPosX = 0;
	srcPosY = 40;
}

void Lemming::SetMortCaure(){
	estat = DEADFALL;
	numImatges = 16;
	srcPosX = _srcPosX = 0;
	srcPosY = 220;
}

void Lemming::SetForadarParet(){
	estat = BREAK;
	numImatges = 32;
	srcPosX = _srcPosX = 0;
	srcPosY = 120;
}

void Lemming::SetObrirParaigues(){
	estat = OPENUMBRELLA;
	numImatges = 4;
	srcPosX = _srcPosX =80;
	srcPosY = 40;
	height = 16;
}

void Lemming::SetPlanejarParaigues(){
	estat = GLIDE;
	numImatges = 4;
	srcPosX = _srcPosX = 140;
	srcPosY = 40;
}

void Lemming::SetCavar(){
	estat = DIG;
	numImatges = 8;
	srcPosX = _srcPosX = 0;
	srcPosY = 160;
}

void Lemming::SetPicar(){
	estat = PICK;
	numImatges = 24;
	srcPosX = _srcPosX = 160;
	srcPosY = 160;
}

void Lemming::SetInmovilitzar(){
	estat = STOP;
	numImatges = 16;
	srcPosX = _srcPosX = 0;
	srcPosY = 60;
}

void Lemming::SetConstruirEscala(){
	estat = STAIR;
	numImatges = 11;
	srcPosX = _srcPosX = 0;
	srcPosY = 100;
}

void Lemming::SetNoEscales(){
	estat = NOSTAIR;
	numImatges = 5;
	srcPosX = _srcPosX = 200;
	srcPosY = 100;
}

void Lemming::SetEscalar(){
	estat = CLIMB;
	numImatges = 9;
	srcPosX = _srcPosX = 0;
	srcPosY = 80;
}

void Lemming::SetFinalEscalar(){
	estat = ENDCLIMB;
	numImatges = 7;
	srcPosX = _srcPosX = 180;
	srcPosY = 80;
}

void Lemming::SetExplotar(){

	estat = EXPLODING;
	numImatges = 16;
	srcPosX = _srcPosX = 0;
	srcPosY = 200;
}

void Lemming::SetExplosio(){
	estat = EXPLOSION;
	numImatges = 9;
	srcPosX = _srcPosX = 100;
	srcPosY = 260;
}

void Lemming::Moure(){
	switch (dir){
	case 0:
		posX += velocitat;
		break;
	case 2:
		posX -= velocitat;
		break;
	}
}

void Lemming::Moure(bool diagAmunt){
	if (diagAmunt){
		Moure();
		posY -= velocitat;
	}
	else
		posY += velocitat;
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



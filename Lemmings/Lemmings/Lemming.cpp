#include "Lemming.h"


Lemming::Lemming(){

}


Lemming::~Lemming(){

}


void Lemming::init(int x, int y, const char* sp, int srcX, int srcY, int w, int h){
	ElementGame::init(x, y, sp, srcX, srcY, w, h);

	widthSpriteSheet = 318;
	heightSpriteSheet = 0; // Falta definir-ho.
	toNextSpriteX = toNextSpriteY = 20;
	numImatges = 4;
	contImatges = 1;
	saltaImatges = false;
	fpsAnimacio = 0;

	estat = FALL;
	paraigues = false;
	escalar = false;
	temps = 5;
	velocitat = 1;
}

void Lemming::update(Map *fons, int x1, int y1, int x2, int y2){ //Es pot optimitzar codi. Com l'if per el SetCaure().
	switch (estat){
	case MOVE:
		if(fons->GetMapa(x1, y1) == 0 && fons->GetMapa(x2, y2) == 0)
			SetCaure();
		else if (dir == 0){ // Cap a la dreta.
			if (fons->GetMapa(x2 + 1, y2) != 0 && fons->GetMapa(x2 + 1, y2 - 1) == 0)
				Moure(true); // Diagonal cap amunt.
			else if (fons->GetMapa(x2 + 1, y2) != 0 && fons->GetMapa(x2 + 1, y2 + 1) == 0)
				Moure(false); // Diagonal cap avall.
			else if (fons->GetMapa(x2, y1) != 0)
				SetDir(2);
			else
				Moure();
		}
		else{
			if (fons->GetMapa(x1 - 1, y2) != 0 && fons->GetMapa(x1 - 1, y2 - 1) == 0)
				Moure(true); // Diagonal cap amunt.
			else if (fons->GetMapa(x1 - 1, y2) != 0 && fons->GetMapa(x1 - 1, y2 + 1) == 0)
				Moure(false); // Diagonal cap avall.
			else if (fons->GetMapa(x1, y1) != 0)
				SetDir(0);
			else
				Moure();
		}
		break;
	case FALL:
		Caure();
		if (fons->GetMapa(x1, y2 + 1) != 0 || fons->GetMapa(x2, y2 + 1) != 0)
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

void Lemming::SetDir(int dir){
	this->dir = dir;
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
	numImatges = 4;
}

void Lemming::SetTrencar(){
	estat = BREAK;
	numImatges = 32;
}

void Lemming::SetPrincipiLevitar(){
	estat = OPENUMBRELLA;
	numImatges = 4;
}

void Lemming::SetLevitar(){
	estat = GLIDE;
	numImatges = 4;
}

void Lemming::SetCavar(){
	estat = DIG;
	numImatges = 8;
}

void Lemming::SetPicar(){
	estat = PICK;
	numImatges = 24;
}

void Lemming::SetInmovilitzar(){
	estat = STOP;
	numImatges = 16;
}

void Lemming::SetConstruirEscala(){
	estat = STAIR;
	numImatges = 16;
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
	Moure();
	if (diagAmunt)
		posY -= velocitat;
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



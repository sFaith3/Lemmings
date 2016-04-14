#include "Lemming.h"


Lemming::Lemming(){
	sManager = SceneManager::getInstanceSM();
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
		if (CheckCollisionMap()){
			estat = MOVE;
			break;
		}
		posY+=2;
		break;
	}
}

bool Lemming::CheckCollisionMap(){
	int mapa[64][64] = { sManager->getMapCollisionSceneGame() };
	int x = posX / 4;
	int y = posY / 4;

	if (mapa[x][y] == 1)
		return true;

}

void Lemming::Moure(bool dreta){

}
void Lemming::TrencarMur(){}
void Lemming::Levitar(){}
void Lemming::Escalar(){}
void Lemming::Cavar(){}
void Lemming::Picar(){}
void Lemming::Caure(){}
void Lemming::Inmovilitzar(){}
void Lemming::Construir(){}
void Lemming::Explotar(){}

void Lemming::SetParaigues(){}
void Lemming::SetEscalar(){}

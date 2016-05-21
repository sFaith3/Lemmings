#include "Lemming.h"


Lemming::Lemming(){
	inputManager = sManager->getInputManager();
}


Lemming::~Lemming(){

}


void Lemming::init(int x, int y){
	ElementGame::init(x, y, "Assets/Images/lem_ani.png", 4, 0, 10, 10, 318, 0, 20, 4, 1, false, 0);

	estat = FALL;
	dir = 0;
	flipType = SDL_FLIP_NONE;
	temps = 5;
	velocitat = 1;
	paraigues = false;
	escalar = false;
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
	sManager->getVideoManager()->renderTexture(idImg, srcPosX, srcPosY, width, height, posX, posY, 0, 0, 0, flipType);
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

bool Lemming::SetSkill(int numUsos, int skill){
	int mouseX, mouseY;
	inputManager->GetMouseXY(mouseX, mouseY);
	if ((mouseX >= posX) && (mouseX <= posX + width) && (mouseY >= posY) && (mouseY <= posY + height)){
		if (numUsos > 0){
			switch (skill){ // Si no tenen l'habilitat posada, se'ls hi posa.
			case 2: // TREPAR
				if (!escalar){
					escalar = true;
					return true;
				}
				break;
			case 3: // PARAIGUES
				if (!paraigues){
					paraigues = true;
					return true;
				}
				break;
			case 4: // EXPLOSIO
				if (estat == MOVE){
					//Suposant que pot passar a aquest estat solament quan s'estigui movent.
					SetExplotar();
					return true;
				}
				break;
			case 5: // PARAT
				if (estat == MOVE){
					SetImmobilitzar();
					return true;
				}
				break;
			case 6: // ESGRAONS
				if (estat == MOVE){
					SetConstruirEscala();
					return true;
				}
				break;
			case 7: // CAVAR_LATERAL
				if (estat == MOVE){
					SetTrencar();
					return true;
				}
				break;
			case 8: // PICAR
				if (estat == MOVE){
					SetPicar();
					return true;
				}
				break;
			case 9: // CAVAR
				if (estat == MOVE){
					SetCavar();
					return true;
				}
				break;
			}
		}
	}
	return false;
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
	/*srcPosX = _srcPosX = srcX;
	srcPosY = srcY;*/
}

void Lemming::SetCaure(){
	estat = FALL;
	numImatges = 4;
	/*srcPosX = _srcPosX = srcX;
	srcPosY = srcY;*/
}

void Lemming::SetTrencar(){
	estat = BREAK;
	numImatges = 32;
	/*srcPosX = _srcPosX = srcX;
	srcPosY = srcY;*/
}

void Lemming::SetPrincipiLevitar(){
	estat = OPENUMBRELLA;
	numImatges = 4;
	/*srcPosX = _srcPosX = srcX;
	srcPosY = srcY;*/
}

void Lemming::SetLevitar(){
	estat = GLIDE;
	numImatges = 4;
	/*srcPosX = _srcPosX = srcX;
	srcPosY = srcY;*/
}

void Lemming::SetCavar(){
	estat = DIG;
	numImatges = 8;
	/*srcPosX = _srcPosX = srcX;
	srcPosY = srcY;*/
}

void Lemming::SetPicar(){
	estat = PICK;
	numImatges = 24;
	/*srcPosX = _srcPosX = srcX;
	srcPosY = srcY;*/
}

void Lemming::SetImmobilitzar(){
	estat = STOP;
	numImatges = 16;
	/*srcPosX = _srcPosX = srcX;
	srcPosY = srcY;*/
}

void Lemming::SetConstruirEscala(){
	estat = STAIR;
	numImatges = 16;
	/*srcPosX = _srcPosX = srcX;
	srcPosY = srcY;*/
}

void Lemming::SetNoEscales(){

}

void Lemming::SetExplotar(){

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

void Lemming::Immobilitzar(){

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


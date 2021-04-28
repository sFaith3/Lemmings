#include "Lemming.h"


Lemming::Lemming(){
	inputManager = SingletonManager::getInstanceSingleton()->getInputManager();
}


Lemming::~Lemming(){

}


void Lemming::init(int x, int y, int xMapa, int yMapa){
	ElementGame::init(x, y, "Assets/Images/Lemmings/lem_ani.png", false, 0, 40, 10, 10, 1, 1, 318, 0, 20, 4, 2);
	posXmapa = xMapa;
	posYmapa = yMapa;
	pintW = 20;
	pintH = 20;

	this->limitX = 8;
	
	estat = FALL;
	dir = 0;
	
	maxCaure = 0;
	tempsMax = 4;
	
	desplasament = 1;
	paraigues = false;
	escalar = false;
	mortInicial = false;
	mortFinal = false;
	explotaContador = false;
	tempsLvl = 0;

	immobilitzat = false;

	rescatat = false;

	currStairs = 0;

	idSounds[0] = audioManager->getSoundID("Assets/Audios/Sounds/beforeExplode.wav");
	idSounds[1] = audioManager->getSoundID("Assets/Audios/Sounds/explosion.wav");
	idSounds[2] = audioManager->getSoundID("Assets/Audios/Sounds/fallDead.wav");
	idSounds[3] = audioManager->getSoundID("Assets/Audios/Sounds/stair.wav");
	idSounds[4] = audioManager->getSoundID("Assets/Audios/Sounds/yippee.wav");

	flipType = SDL_FLIP_NONE;
}

void Lemming::update(Map *fons, int x1, int y1, int x2, int y2, int temps){
	switch (estat){
	case MOVE:
		if (fons->GetMapa(x1 + 1, y2 + 1) == 0 && fons->GetMapa(x2 - 1, y2 + 1) == 0)
			SetCaure();
		else if (dir == 0){ // Cap a la dreta.
			if (fons->GetMapa(x2, y2 - 1) != 0 && fons->GetMapa(x2, y2 - 2) == 0)
				Moure(true); // Diagonal cap amunt.
			else if (fons->GetMapa(x2, y2) == 0 && fons->GetMapa(x2, y2 + 1) != 0)
				Moure(false); // Cap avall.
			else if (fons->GetMapa(x2 + 1, y2 - 2) != 0){
				if (fons->GetMapa(x2 + 1, y2 - 2) == 1 && escalar){
					SetEscalar();
				}
				else{
					SetDir(2);
				}
			}
			else{
				Moure();
			}
		}
		else{
			if (fons->GetMapa(x1, y2 - 1) != 0 && fons->GetMapa(x1, y2 - 2) == 0)
				Moure(true); // Diagonal cap amunt.
			else if (fons->GetMapa(x1, y2) == 0 && fons->GetMapa(x1, y2 + 1) != 0)
				Moure(false); // Cap avall.
			else if (fons->GetMapa(x1, y2 - 2) != 0){

				if (fons->GetMapa(x1, y2 - 2) == 1 && escalar){
					SetEscalar();
				}
				else{
					SetDir(0);
				}
			}
			else
				Moure();
		}
		break;
	case FALL:
		if (paraigues){
			SetObrirParaigues();
		}
		else{
			Caure();
			if (fons->GetMapa(x1 + desplasament, y2 + desplasament) != 0 || fons->GetMapa(x2 - desplasament, y2 + desplasament) != 0){
				if (mortInicial){
					SetMortCaure();
				}
				else{
					SetMoure();
				}
			}
		}
		break;
	case BREAK:
		if ((fons->GetMapa(x1 + 1, y2 + 1) == 0 && fons->GetMapa(x1, y1 + 1) == 0) || (fons->GetMapa(x2 + 1, y2 + 1) == 0 && fons->GetMapa(x2, y1 + 1) == 0)){
			SetMoure();
		}
		else{
			TrencarMur(fons, x1, x2, y1, y2);
		}
		break;
	case GLIDE:
		Levitar();
		if (fons->GetMapa(x1 + desplasament, y2 + desplasament) != 0 || fons->GetMapa(x2 - desplasament, y2 + desplasament) != 0)
			SetMoure();
		break;
	case CLIMB:
		Escalar();
		if ((fons->GetMapa(x2, y2) == 0 && fons->GetMapa(x2, y2 + 1) == 0) && (fons->GetMapa(x2 + 1, y2) == 0 && fons->GetMapa(x2 + 1, y2 + 1) != 0) ||
			(fons->GetMapa(x1, y2) == 0 && fons->GetMapa(x1, y2 + 1) == 0) && (fons->GetMapa(x1 - 1, y2) == 0 && fons->GetMapa(x1 - 1, y2 + 1) != 0)){
			Moure();
			SetMoure();
		}
		else if (fons->GetMapa(x1, y1) == 1 && fons->GetMapa(x2, y1) == 1){
			SetCaure();
		}

		break;
	case DIG:
		if ((fons->GetMapa(x1 - 1, y1 + 1) == 0 && fons->GetMapa(x2 + 1, y1 + 1) == 0) && fons->GetMapa(x2, y2 + 1) == 0){
			SetMoure();
		}
		else{
			Cavar(fons, x2, y2);
		}
		break;
	case PICK:
		if ((fons->GetMapa(x1 - 1, y1 + 1) == 0 && fons->GetMapa(x2 + 1, y1 + 1) == 0) && fons->GetMapa(x2, y2 + 1) == 0){
			SetMoure();
		}
		else{
			Picar(fons, x2, y2);
		}
		break;
	case STOP:
		if (!immobilitzat){
			Immobilitzar(fons, x1, x2, y1, y2);
			immobilitzat = true;
		}
		break;
	case STAIR:
		if ((dir == 0 && (fons->GetMapa(x2 + 1, y2 - 1) != 0 && fons->GetMapa(x2 + 2, y2 - 1) != 0)) || // **** --- Quan la posició estigui bé, s'ha de treure el "-1" de la condició. --- ****
			(dir == 2 && (fons->GetMapa(x1 - 1, y2 - 1) != 0 && fons->GetMapa(x1 - 2, y2 - 1) != 0))){
			SetMoure();
			currStairs = 0;
			break;
		}
		else if (contImatges == 11){
			PosarEscala(fons, x1, x2, y2);
			currStairs++;
			if (currStairs == 25 || currStairs == 28 || currStairs == 33)
				audioManager->playSound(idSounds[Stair]);
		}
		else if (contImatges == numImatges){
			Moure(true);
			if (currStairs >= 32){
				SetNoEscales();
				currStairs = 0;
			}
		}
		break;
	case NOSTAIR:
		if (contImatges == numImatges){
			SetMoure();
		}
		break;
	case DEAD:

		break;
	case DEADFALL:
		if (contImatges == numImatges){
			mortFinal = true;
		}
		break;
	case OPENUMBRELLA:

		break;
	case ENDCLIMB:

		break;
	case RESCUED:
		if (!rescatat){
			if (contImatges == numImatges)
				rescatat = true;
		}
		break;
	case EXPLODING:
		if (contImatges == numImatges){
			SetExplosio();
		}
		break;
	case EXPLOSION:
		Explotar(fons, x1, y1, x2, y2);
		break;
	}

	if (explotaContador){
		TempsFinal(temps);
	}

	UpdateAnimacio();
}

void Lemming::render(){
	videoManager->renderTexture(idImg, srcPosX, srcPosY, pintW, pintH, scaleX, scaleY, posX + posXmapa, posY + posYmapa, 0, 0, 0, flipType);
}

int Lemming::GetLimitX(){
	return limitX;
}

int Lemming::GetDir(){
	return dir;
}

bool Lemming::GetMort(){
	return mortFinal;
}

bool Lemming::GetContExplotar(){
	return explotaContador;
}

bool Lemming::GetRescatat(){
	return rescatat;
}

bool Lemming::CursorOnLemming(){
	int mouseX, mouseY;
	inputManager->GetMouseXY(mouseX, mouseY);
	if ((mouseX > posX + posXmapa && mouseX < posX + posXmapa + pintW) && (mouseY > posY + posYmapa && mouseY < posY + posYmapa + height))
		return true;

	return false;
}

bool Lemming::SetSkill(int numUsos, int skill, int temps){
	if (numUsos > 0){
		switch (skill){ // Si no tenen l'habilitat posada, se'ls hi posa.
		case 2: // TREPAR
			if (!escalar && estat != STOP){
				escalar = true;
				return true;
			}
			break;
		case 3: // PARAIGUES
			if (!paraigues && estat != STOP){
				paraigues = true;
				return true;
			}
			break;
		case 4: // EXPLOSIO
			if (!explotaContador && estat != EXPLODING && estat != EXPLOSION && estat != FALL){
				SetContadorTemps(temps);
				return true;
			}
			break;
		case 5: // PARAT
			if (estat != STOP && estat != FALL && estat != CLIMB){
				SetImmobilitzar();
				return true;
			}
			break;
		case 6: // ESGRAONS
			if (estat != STAIR && estat != STOP && estat != FALL && estat != CLIMB){
				SetConstruirEscala();
				return true;
			}
			break;
		case 7: // TRENCAR MUR
			if (estat != BREAK && estat != STOP && estat != FALL && estat != CLIMB){
				SetForadarParet();
				return true;
			}
			break;
		case 8: // PICAR
			if (estat != PICK && estat != STOP && estat != FALL && estat != CLIMB){
				SetPicar();
				return true;
			}
			break;
		case 9: // CAVAR
			if (estat != DIG && estat != STOP && estat != FALL && estat != CLIMB){
				SetCavar();
				return true;
			}
			break;
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
	srcPosX = _srcPosX = 0;
	srcPosY = 0;
}

void Lemming::SetCaure(){
	estat = FALL;
	numImatges = 4;
	srcPosX = _srcPosX = 0;
	srcPosY = 40;
	maxCaure = 0;
}

void Lemming::SetMortCaure(){
	audioManager->playSound(idSounds[FallDead]);
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
	srcPosX = _srcPosX = 80;
	srcPosY = 40;
	height = 16;
	SetPlanejarParaigues();
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

void Lemming::SetImmobilitzar(){
	estat = STOP;
	numImatges = 16;
	srcPosX = _srcPosX = 0;
	srcPosY = 60;
}

void Lemming::SetConstruirEscala(){
	estat = STAIR;
	numImatges = 16;
	srcPosX = _srcPosX = 0;
	srcPosY = 100;
}

void Lemming::SetNoEscales(){
	estat = NOSTAIR;
	numImatges = 7;
	srcPosX = _srcPosX = 200;
	srcPosY = 0;
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

void Lemming::SetContadorTemps(int temps){
	explotaContador = true;
	tempsLvl = temps;
}

void Lemming::SetRescatar(){
	audioManager->playSound(idSounds[Yippee]);
	estat = RESCUED;
	numImatges = 4;
	srcPosX = _srcPosX = 20;
	srcPosY = 20;
}

void Lemming::SetExplotar(){
	audioManager->playSound(idSounds[BeforeExplode]);
	estat = EXPLODING;
	numImatges = 16;
	srcPosX = _srcPosX = 0;
	srcPosY = 200;
}

void Lemming::SetExplosio(){
	audioManager->playSound(idSounds[Explosion]);
	estat = EXPLOSION;
 	numImatges = 9;
	srcPosX = _srcPosX = 100;
	srcPosY = 260;
}

void Lemming::Moure(){
	switch (dir){
	case 0:
		posX += desplasament;
		break;
	case 2:
		posX -= desplasament;
		break;
	}
}

void Lemming::Moure(bool diagAmunt){
	if (diagAmunt){
		Moure();
		posY -= desplasament;
	}
	else
		posY += desplasament;
}

void Lemming::TrencarMur(Map *fons, int x1, int x2, int y1, int y2){
	if (contImatges == 8 || contImatges == 16 || contImatges == 24 || contImatges == 32){
		for (int i = 0; i < 3; i++){
			for (int j = 0; j < 4; j++){
				fons->DestroyPosMapa(x2 + i, y2 - j);
			}
		}
		Moure();
	}
}

void Lemming::Levitar(){
	if (contImatges == 2 || contImatges == 4){
		posY += desplasament;
	}
}

void Lemming::Escalar(){
	if (contImatges == 3 || contImatges == 6 || contImatges == 9){
		posY -= desplasament;
	}
}

void Lemming::Cavar(Map *fons, int x2, int y2){
	// Destrucció del terreny.
	if (contImatges == 6){
		for (int i = -1; i < 2; i++){
			fons->DestroyPosMapa(x2 + i, y2);
		}
		posY += desplasament;
	}
}

void Lemming::Picar(Map *fons, int x2, int y2){
	// Destrucció del terreny.
	if (contImatges == 5){
		for (int i = 0; i < 3; i++){
			for (int j = 0; j < 4; j++){
				fons->DestroyPosMapa(x2 + i, y2 - j);
			}
			fons->DestroyPosMapa(x2 + i, y2);
		}
		Moure();
		posY += desplasament;
	}
}

void Lemming::Immobilitzar(Map *fons, int x1, int x2, int y1, int y2){
	for (int i = 1; i < 3; i++){
		for (int j = -4; j < 3; j++){
			if (fons->GetMapa(x1 + i, y2 + j) == 0){
				fons->CrearPosMapa(x1 + i, y2 + j, 3);
			}

			if (fons->GetMapa((x2 - 2) + i, y2 + j) == 0){
				fons->CrearPosMapa((x2 - 2) + i, y2 + j, 3);
			}
		}
	}
}

void Lemming::PosarEscala(Map *fons, int x1, int x2, int y2){
	switch (dir){
	case 0:
		for (int i = 0; i < 3; i++){
			if (fons->GetMapa(x2 + i, y2) == 0)
				fons->CrearPosMapa(x2 + i, y2, 3, 0, 3);
		}
		break;
	case 2:
		for (int i = 0; i < 3; i++){
			if (fons->GetMapa(x1 - i, y2) == 0)
				fons->CrearPosMapa(x1 - i, y2, 3, 0, 3);
		}
		break;
	}
}

void Lemming::Caure(){
	posY += desplasament;

	if (maxCaure == 60){
		mortInicial = true;
	}
	else if (maxCaure < 60){
		maxCaure++;
	}
}

void Lemming::TempsFinal(int temps){
	int _temps = temps - tempsLvl;
	if (_temps >= tempsMax){
		SetExplotar();
		explotaContador = false;
	}
}

void Lemming::Explotar(Map *fons, int x1, int y1, int x2, int y2){
	if (contImatges == numImatges){
		// Destrucció del terreny.
		for (int i = -6; i < 3; i++){
			fons->DestroyPosMapa(x1, y2 + i);
			fons->DestroyPosMapa(x1 + 1, y2 + i);
			fons->DestroyPosMapa(x1 + 2, y2 + i);
			fons->DestroyPosMapa(x1 + 3, y2 + i);

			fons->DestroyPosMapa(x2 + 1, y2 + i);
			fons->DestroyPosMapa(x2, y2 + i);
			fons->DestroyPosMapa(x2 - 1, y2 + i);
			fons->DestroyPosMapa(x2 - 2, y2 + i);
		}
		mortFinal = true;
	}
}

void Lemming::ConstruirEscala(){

}

void Lemming::PutParaigues(){
	paraigues = true;
}

void Lemming::PutEscalar(){
	escalar = true;
}
#include "Lemming.h"


Lemming::Lemming(){
	inputManager = SingletonManager::getInstanceSingleton()->getInputManager();
}

Lemming::~Lemming(){
}


void Lemming::init(int x, int y, int xMapa, int yMapa){
	ElementGame::init(x, y, "Assets/Art/Images/Lemmings/lem_ani.png", false, 0, 40, 10, 10, 1, 1, 318, 0, 20, 4, 2);
	mapPosX = xMapa;
	mapPosY = yMapa;
	width = 20;
	height = 20;

	limitX = 8;
	
	currState = FALL;
	direction = 0;
	
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

	idSounds[0] = audioManager->getSoundID("Assets/Art/Audios/Sounds/beforeExplode.wav");
	idSounds[1] = audioManager->getSoundID("Assets/Art/Audios/Sounds/explosion.wav");
	idSounds[2] = audioManager->getSoundID("Assets/Art/Audios/Sounds/fallDead.wav");
	idSounds[3] = audioManager->getSoundID("Assets/Art/Audios/Sounds/stair.wav");
	idSounds[4] = audioManager->getSoundID("Assets/Art/Audios/Sounds/yippee.wav");

	flipType = SDL_FLIP_NONE;
}

void Lemming::update(Map* fons, int x1, int y1, int x2, int y2, int temps) {
	switch (currState) {
	case MOVE:
		if (fons->GetMap(x1 + 1, y2 + 1) == 0 && fons->GetMap(x2 - 1, y2 + 1) == 0)
			SetCaure();
		else if (direction == 0) { // Cap a la dreta.
			if (fons->GetMap(x2, y2 - 1) != 0 && fons->GetMap(x2, y2 - 2) == 0)
				Moure(true); // Diagonal cap amunt.
			else if (fons->GetMap(x2, y2) == 0 && fons->GetMap(x2, y2 + 1) != 0)
				Moure(false); // Cap avall.
			else if (fons->GetMap(x2 + 1, y2 - 2) != 0) {
				if (fons->GetMap(x2 + 1, y2 - 2) == 1 && escalar) {
					SetEscalar();
				}
				else {
					SetDirection(2);
				}
			}
			else {
				Moure();
			}
		}
		else {
			if (fons->GetMap(x1, y2 - 1) != 0 && fons->GetMap(x1, y2 - 2) == 0)
				Moure(true); // Diagonal cap amunt.
			else if (fons->GetMap(x1, y2) == 0 && fons->GetMap(x1, y2 + 1) != 0)
				Moure(false); // Cap avall.
			else if (fons->GetMap(x1, y2 - 2) != 0) {

				if (fons->GetMap(x1, y2 - 2) == 1 && escalar) {
					SetEscalar();
				}
				else {
					SetDirection(0);
				}
			}
			else
				Moure();
		}
		break;
	case FALL:
		if (paraigues) {
			SetObrirParaigues();
		}
		else {
			Caure();
			if (fons->GetMap(x1 + desplasament, y2 + desplasament) != 0 || fons->GetMap(x2 - desplasament, y2 + desplasament) != 0) {
				if (mortInicial) {
					SetMortCaure();
				}
				else {
					SetMoure();
				}
			}
		}
		break;
	case BREAK:
		if ((fons->GetMap(x1 + 1, y2 + 1) == 0 && fons->GetMap(x1, y1 + 1) == 0) || (fons->GetMap(x2 + 1, y2 + 1) == 0 && fons->GetMap(x2, y1 + 1) == 0)) {
			SetMoure();
		}
		else {
			TrencarMur(fons, x1, x2, y1, y2);
		}
		break;
	case GLIDE:
		Levitar();
		if (fons->GetMap(x1 + desplasament, y2 + desplasament) != 0 || fons->GetMap(x2 - desplasament, y2 + desplasament) != 0)
			SetMoure();
		break;
	case CLIMB:
		Escalar();
		if ((fons->GetMap(x2, y2) == 0 && fons->GetMap(x2, y2 + 1) == 0) && (fons->GetMap(x2 + 1, y2) == 0 && fons->GetMap(x2 + 1, y2 + 1) != 0) ||
			(fons->GetMap(x1, y2) == 0 && fons->GetMap(x1, y2 + 1) == 0) && (fons->GetMap(x1 - 1, y2) == 0 && fons->GetMap(x1 - 1, y2 + 1) != 0)) {
			Moure();
			SetMoure();
		}
		else if (fons->GetMap(x1, y1) == 1 && fons->GetMap(x2, y1) == 1) {
			SetCaure();
		}

		break;
	case DIG:
		if ((fons->GetMap(x1 - 1, y1 + 1) == 0 && fons->GetMap(x2 + 1, y1 + 1) == 0) && fons->GetMap(x2, y2 + 1) == 0) {
			SetMoure();
		}
		else {
			Cavar(fons, x2, y2);
		}
		break;
	case PICK:
		if ((fons->GetMap(x1 - 1, y1 + 1) == 0 && fons->GetMap(x2 + 1, y1 + 1) == 0) && fons->GetMap(x2, y2 + 1) == 0) {
			SetMoure();
		}
		else {
			Picar(fons, x2, y2);
		}
		break;
	case IMMOBILE:
		if (!immobilitzat) {
			Immobilitzar(fons, x1, x2, y1, y2);
			immobilitzat = true;
		}
		break;
	case STAIRS:
		// **** --- Quan la posici� estigui b�, s'ha de treure el "-1" de la condici�. --- ****
		if ((direction == 0 && (fons->GetMap(x2 + 1, y2 - 1) != 0 && fons->GetMap(x2 + 2, y2 - 1) != 0)) ||
			(direction == 2 && (fons->GetMap(x1 - 1, y2 - 1) != 0 && fons->GetMap(x1 - 2, y2 - 1) != 0))) {
			SetMoure();
			currStairs = 0;
			break;
		}
		else if (currentSprite == 11) {
			PosarEscala(fons, x1, x2, y2);
			currStairs++;
			if (currStairs == 25 || currStairs == 28 || currStairs == 33)
				audioManager->playSound(idSounds[Stair]);
		}
		else if (currentSprite == numSprites) {
			Moure(true);
			if (currStairs >= 32) {
				SetNoEscales();
				currStairs = 0;
			}
		}
		break;
	case NO_STAIRS:
		if (currentSprite == numSprites) {
			SetMoure();
		}
		break;
	case DEAD:

		break;
	case DEAD_FALL:
		if (currentSprite == numSprites) {
			mortFinal = true;
		}
		break;
	case OPEN_UMBRELLA:
		break;
	case END_CLIMB:
		break;
	case RESCUED:
		if (!rescatat) {
			if (currentSprite == numSprites)
				rescatat = true;
		}
		break;
	case EXPLODING:
		if (currentSprite == numSprites) {
			SetExplosio();
		}
		break;
	case EXPLOSION:
		Explotar(fons, x1, y1, x2, y2);
		break;
	}

	if (explotaContador) {
		TempsFinal(temps);
	}

	UpdateAnimation();
}

void Lemming::render(){
	videoManager->renderTexture(idImg, srcPosX, srcPosY, width, height, scaleX, scaleY, posX + mapPosX, posY + mapPosY, 0, 0, 0, flipType);
}


int Lemming::GetLimitX(){
	return limitX;
}

int Lemming::GetDirection(){
	return direction;
}

Lemming::StatesEnum Lemming::GetCurrState() {
	return currState;
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


bool Lemming::IsCursorOnLemming() {
	int mouseX, mouseY;
	inputManager->getMouseXY(mouseX, mouseY);

	return ((mouseX > posX + mapPosX && mouseX < posX + mapPosX + width)
		&& (mouseY > posY + mapPosY && mouseY < posY + mapPosY + height));
}


bool Lemming::SetSkill(int numUsos, int skill, int temps){
	if (numUsos > 0){
		switch (skill){ // Si no tenen l'habilitat posada, se'ls hi posa.
		case 2: // TREPAR
			if (!escalar && currState != IMMOBILE){
				escalar = true;
				return true;
			}
			break;
		case 3: // PARAIGUES
			if (!paraigues && currState != IMMOBILE){
				paraigues = true;
				return true;
			}
			break;
		case 4: // EXPLOSIO
			if (!explotaContador && currState != EXPLODING && currState != EXPLOSION && currState != FALL){
				SetContadorTemps(temps);
				return true;
			}
			break;
		case 5: // PARAT
			if (currState != IMMOBILE && currState != FALL && currState != CLIMB){
				SetImmobilitzar();
				return true;
			}
			break;
		case 6: // ESGRAONS
			if (currState != STAIRS && currState != IMMOBILE && currState != FALL && currState != CLIMB){
				SetConstruirEscala();
				return true;
			}
			break;
		case 7: // TRENCAR MUR
			if (currState != BREAK && currState != IMMOBILE && currState != FALL && currState != CLIMB){
				SetForadarParet();
				return true;
			}
			break;
		case 8: // PICAR
			if (currState != PICK && currState != IMMOBILE && currState != FALL && currState != CLIMB){
				SetPicar();
				return true;
			}
			break;
		case 9: // CAVAR
			if (currState != DIG && currState != IMMOBILE && currState != FALL && currState != CLIMB){
				SetCavar();
				return true;
			}
			break;
		}
	}

	return false;
}

void Lemming::SetDirection(int direction){
	this->direction = direction;
	if (flipType == SDL_FLIP_NONE)
		flipType = SDL_FLIP_HORIZONTAL;
	else
		flipType = SDL_FLIP_NONE;
}

void Lemming::SetMoure(){
	currState = MOVE;
	numSprites = 10;
	srcPosX = _srcPosX = 0;
	srcPosY = 0;
}

void Lemming::SetCaure(){
	currState = FALL;
	numSprites = 4;
	srcPosX = _srcPosX = 0;
	srcPosY = 40;
	maxCaure = 0;
}

void Lemming::SetMortCaure(){
	audioManager->playSound(idSounds[FallDead]);
	currState = DEAD_FALL;
	numSprites = 16;
	srcPosX = _srcPosX = 0;
	srcPosY = 220;
}

void Lemming::SetForadarParet(){
	currState = BREAK;
	numSprites = 32;
	srcPosX = _srcPosX = 0;
	srcPosY = 120;
}

void Lemming::SetObrirParaigues(){
	currState = OPEN_UMBRELLA;
	numSprites = 4;
	srcPosX = _srcPosX = 80;
	srcPosY = 40;
	height = 16;
	SetPlanejarParaigues();
}

void Lemming::SetPlanejarParaigues(){
	currState = GLIDE;
	numSprites = 4;
	srcPosX = _srcPosX = 140;
	srcPosY = 40;
}

void Lemming::SetCavar(){
	currState = DIG;
	numSprites = 8;
	srcPosX = _srcPosX = 0;
	srcPosY = 160;
}

void Lemming::SetPicar(){
	currState = PICK;
	numSprites = 24;
	srcPosX = _srcPosX = 160;
	srcPosY = 160;
}

void Lemming::SetImmobilitzar(){
	currState = IMMOBILE;
	numSprites = 16;
	srcPosX = _srcPosX = 0;
	srcPosY = 60;
}

void Lemming::SetConstruirEscala(){
	currState = STAIRS;
	numSprites = 16;
	srcPosX = _srcPosX = 0;
	srcPosY = 100;
}

void Lemming::SetNoEscales(){
	currState = NO_STAIRS;
	numSprites = 7;
	srcPosX = _srcPosX = 200;
	srcPosY = 0;
}

void Lemming::SetEscalar(){
	currState = CLIMB;
	numSprites = 9;
	srcPosX = _srcPosX = 0;
	srcPosY = 80;
}

void Lemming::SetFinalEscalar(){
	currState = END_CLIMB;
	numSprites = 7;
	srcPosX = _srcPosX = 180;
	srcPosY = 80;
}

void Lemming::SetExplotar() {
	audioManager->playSound(idSounds[BeforeExplode]);
	currState = EXPLODING;
	numSprites = 16;
	srcPosX = _srcPosX = 0;
	srcPosY = 200;
}

void Lemming::SetExplosio() {
	audioManager->playSound(idSounds[Explosion]);
	currState = EXPLOSION;
	numSprites = 9;
	srcPosX = _srcPosX = 100;
	srcPosY = 260;
}

void Lemming::SetContadorTemps(int temps){
	explotaContador = true;
	tempsLvl = temps;
}

void Lemming::SetRescatar(){
	audioManager->playSound(idSounds[Yippee]);
	currState = RESCUED;
	numSprites = 4;
	srcPosX = _srcPosX = 20;
	srcPosY = 20;
}


void Lemming::PutParaigues() {
	paraigues = true;
}

void Lemming::PutEscalar() {
	escalar = true;
}


void Lemming::Moure(){
	switch (direction){
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
	if (currentSprite == 8 || currentSprite == 16 || currentSprite == 24 || currentSprite == 32){
		for (int i = 0; i < 3; i++){
			for (int j = 0; j < 4; j++){
				fons->ChangeMapAtPos(x2 + i, y2 - j, 0, 0);
			}
		}
		Moure();
	}
}

void Lemming::Levitar(){
	if (currentSprite == 2 || currentSprite == 4){
		posY += desplasament;
	}
}

void Lemming::Escalar(){
	if (currentSprite == 3 || currentSprite == 6 || currentSprite == 9){
		posY -= desplasament;
	}
}

void Lemming::Cavar(Map *fons, int x2, int y2){
	// Destrucci� del terreny.
	if (currentSprite == 6){
		for (int i = -1; i < 2; i++){
			fons->ChangeMapAtPos(x2 + i, y2, 0, 0);
		}
		posY += desplasament;
	}
}

void Lemming::Picar(Map *fons, int x2, int y2){
	// Destrucci� del terreny.
	if (currentSprite == 5){
		for (int i = 0; i < 3; i++){
			for (int j = 0; j < 4; j++){
				fons->ChangeMapAtPos(x2 + i, y2 - j, 0, 0);
			}
			fons->ChangeMapAtPos(x2 + i, y2, 0, 0);
		}
		Moure();
		posY += desplasament;
	}
}

void Lemming::Immobilitzar(Map *fons, int x1, int x2, int y1, int y2){
	for (int i = 1; i < 3; i++){
		for (int j = -4; j < 3; j++){
			if (fons->GetMap(x1 + i, y2 + j) == 0){
				fons->ChangeMapAtPos(x1 + i, y2 + j, 3);
			}

			if (fons->GetMap((x2 - 2) + i, y2 + j) == 0){
				fons->ChangeMapAtPos((x2 - 2) + i, y2 + j, 3);
			}
		}
	}
}

void Lemming::PosarEscala(Map *fons, int x1, int x2, int y2){
	switch (direction){
	case 0:
		for (int i = 0; i < 3; i++){
			if (fons->GetMap(x2 + i, y2) == 0)
				fons->ChangeMapAtPos(x2 + i, y2, 3, 3);
		}
		break;
	case 2:
		for (int i = 0; i < 3; i++){
			if (fons->GetMap(x1 - i, y2) == 0)
				fons->ChangeMapAtPos(x1 - i, y2, 3, 3);
		}
		break;
	}
}

void Lemming::ConstruirEscala() {

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
	if (currentSprite == numSprites){
		// Destrucci� del terreny.
		for (int i = -6; i < 3; i++){
			fons->ChangeMapAtPos(x1, y2 + i, 0, 0);
			fons->ChangeMapAtPos(x1 + 1, y2 + i, 0, 0);
			fons->ChangeMapAtPos(x1 + 2, y2 + i, 0, 0);
			fons->ChangeMapAtPos(x1 + 3, y2 + i, 0, 0);

			fons->ChangeMapAtPos(x2 + 1, y2 + i, 0, 0);
			fons->ChangeMapAtPos(x2, y2 + i, 0, 0);
			fons->ChangeMapAtPos(x2 - 1, y2 + i, 0, 0);
			fons->ChangeMapAtPos(x2 - 2, y2 + i, 0, 0);
		}
		mortFinal = true;
	}
}
#pragma once
#include "ElementGame.h"
#include "Map.h"

class Lemming :
	public ElementGame
{
public:
	// MOVE: Moure's, FALL: Caure, BREAK: Trencar Parets, GLIDE: Levitar, DIG: Cavar,
	// STOP: Inmovilitzat, STAIR: Posar rajoles, PICK: Cavar amb el Pic,
	// EXPLOSION: Foc de l'Explosio, DEAD: El Lemming es destruït, DEADFALL: El Lemming cau d'una gran altura,
	// OPENUMBRELLA: El Lemming obra el paraigües, NOSTAIR: El Lemming es queda sense rajoles, ENDCLIMB El Lemming acaba d'escalar i torna a terra pla,
	// EXPLODING: El Lemming fa l'animacio de que va a explotar.
	enum StatesEnum {
		MOVE, FALL, BREAK, GLIDE, CLIMB, DIG, PICK, IMMOBILE, STAIRS, EXPLOSION,
		DEAD, DEAD_FALL, OPEN_UMBRELLA, NO_STAIRS, END_CLIMB, RESCUED, EXPLODING
	};
private:
	int mapPosX, mapPosY; // Desplaçament adicional, solament per al render, degut al mapa.
	int width, height; // Amplada i alçada de la imatge.

	int limitX; // Un marge per a calcular el desplaçament i que no travessi alguna cosa.

	StatesEnum currState;
	int direction; // Direcció del Lemming a l'hora de moure's. 0 / 2.

	int maxCaure;
	int tempsMax; // compte enrere de 5s.

	int desplasament;

	// Equipa X habilitats al Lemming, que les realitzarà quan compleixi certa condició.
	bool paraigues;
	bool escalar;

	bool mortInicial;
	bool mortFinal;

	bool explotaContador; // Variable que indica el començament del compte enrere de l'explosió.

	int tempsLvl; // Temps restant de la partida.

	bool immobilitzat; // Per a bloquejar aquella posició del mapa quan el Lemming s'aturi passant a l'estat "STOP".

	bool rescatat; // S'activa quan un Lemming passa per la porta.

	int currStairs;

	enum SoundsEnum {
		BeforeExplode, Explosion, FallDead, Stair, Yippee
	};
	int idSounds[5];

	SDL_RendererFlip flipType; // Gira la imatge quan canvïa la direcció.

	InputManager* inputManager;

public:
	Lemming();
	~Lemming();

	void init(int x, int y, int xMapa, int yMapa);
	void update(Map* fons, int x1, int y1, int x2, int y2, int temps);
	void render();

	int GetLimitX();
	int GetDirection();
	StatesEnum GetCurrState();
	bool GetMort();
	bool GetContExplotar();
	bool GetRescatat();

	bool IsCursorOnLemming();

	bool SetSkill(int numUsos, int skill, int temps);
	void SetDirection(int direction);
	void SetMoure();
	void SetCaure();
	void SetMortCaure();
	void SetForadarParet();
	void SetObrirParaigues();
	void SetPlanejarParaigues();
	void SetCavar();
	void SetPicar();
	void SetImmobilitzar();
	void SetConstruirEscala();
	void SetNoEscales();
	void SetEscalar();
	void SetFinalEscalar();
	void SetExplosio();
	void SetExplotar();
	void SetContadorTemps(int temps);
	void SetRescatar();

	// Equipables, com Paraigües i Escalar
	void PutParaigues();
	void PutEscalar();

	// Estats temporals 
	void Moure();
	void Moure(bool diagAmunt);
	void TrencarMur(Map* fons, int x1, int x2, int y1, int y2);
	void Levitar();
	void Escalar();
	void Cavar(Map* fons, int x2, int y2);
	void Picar(Map* fons, int x2, int y2);
	void Immobilitzar(Map* fons, int x1, int x2, int y1, int y2);
	void PosarEscala(Map* fons, int x1, int x2, int y2);
	void ConstruirEscala();
	void Caure();
	void TempsFinal(int temps);
	void Explotar(Map* fons, int x1, int y1, int x2, int y2);
};


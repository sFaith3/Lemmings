#pragma once
#include "ElementGame.h"
#include "Map.h"

// NOTA: Si els getters no s'utilitzen, s'hauràn d'esborrar. Els setters es poden deixar.
class Lemming :
	public ElementGame
{
private:
	int limitX;
	int estat;
	int dir; // Direcció del Lemming a l'hora de moure's || 0 / 2.
	int maxCaure;
	SDL_RendererFlip flipType;
	int tempsMax; // conta enrere de 5s
	int tempsLvl; // temps restant de la partida
	int desplasament;
	bool paraigues;
	bool escalar;
	bool mortInicial;
	bool mortFinal;
	bool explotaContador;
	int pintW, pintH;
	int posXmapa, posYmapa; // Desplaçament adicional, solament per al render, degut al mapa.
	
	InputManager* inputManager;

public:
	Lemming();
	~Lemming();

	void init(int x, int y, int xMapa, int yMapa);
	void update(Map *fons, int x1, int y1, int x2, int y2, int temps);
	void render();

	int GetLimitX();
	int GetDir();

	bool CursorOnLemming();
	bool SetSkill(int numUsos, int skill, int temps);

	void SetDir(int dir);
	void SetAnimacio();
	/*
	MOVE: Moures, FALL: Caure, BREAK: Trencar Parets, GLIDE: Levitar, DIG: Cavar,
	STOP: Inmovilitzat, STAIR: Posar rajoles, PICK: Cavar amb el Pic,
	EXPLOSION: Foc de l'Explosio, DEAD: El Lemming es destruït, DEADFALL: El Lemming cau d'una gran altura,
	OPENUMBRELLA: El Lemming obra el paraigües, NOSTAIR: El Lemming es queda sense rajoles, ENDCLIMB El Lemming acaba d'escalar i torna a terra pla,
	EXPLODING: El Lemming fa l'animacio de que va a explotar.
	*/
	enum EstatsEnum{
		MOVE, FALL, BREAK, GLIDE, CLIMB, DIG, PICK, STOP, STAIR, EXPLOSION, 
		DEAD, DEADFALL, OPENUMBRELLA, NOSTAIR, ENDCLIMB, EXPLODING, EXIT
	};
	int GetEstat();
	bool GetMort();
	// Sets per canviar l'Estat 
	void SetMoure();   
	void SetCaure();   

	void SetForadarParet();
	void SetObrirParaigues();
	void SetPlanejarParaigues();
	void SetCavar();
	void SetPicar();
	void SetImmobilitzar();
	void SetConstruirEscala();
	void SetNoEscales();
	void SetExplosio(); 
	void SetExplotar();
	void SetEscalar(); 
	void SetFinalEscalar(); 
	void SetMortCaure(); 
	void SetContadorTemps(int temps);

	// Estats temporals 
	void Moure();
	void Moure(bool diagAmunt);
	void TrencarMur(Map *fons, int x1, int x2, int y1, int y2);
	void Levitar();
	void Escalar();
	void Cavar(Map *fons, int x2, int y2);
	void Picar(Map *fons, int x2, int y2);
	void Caure();
	void TempsFinal(int temps);
	void ConstruirEscala();
	void Explotar(Map *fons, int x2, int y2);

	// Equipables, com Paraigües i Escalar
	void PutParaigues();
	void PutEscalar();

};


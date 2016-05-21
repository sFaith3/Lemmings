#pragma once
#include "ElementGame.h"
#include "Map.h"

// NOTA: Si els getters no s'utilitzen, s'hauràn d'esborrar. Els setters es poden deixar.
class Lemming :
	public ElementGame
{
private:
	int estat;
	int dir; // Direcció del Lemming a l'hora de moure's || 0 / 2.
	SDL_RendererFlip flipType;
	int temps;
	int velocitat;
	bool paraigues;
	bool escalar;

	InputManager* inputManager;

public:
	Lemming();
	~Lemming();

	void init(int x, int y);
	void update(Map *fons, int x1, int y1, int x2, int y2);
	void render();

	int GetPosX();
	int GetPosY();
	int GetWidth();
	int GetHeight();
	int GetDir();

	bool SetSkill(int numUsos, int skill);

	void SetDir(int dir);
	void SetAnimacio();
	/*
	MOVE: Moures, FALL: Caure, BREAK: Trencar Parets, GLIDE: Levitar, DIG: Cavar,
	STOP: Inmovilitzat, STAIR: Posar rajoles,PICK: Cavar amb el Pic 
	EXPLOSION: Explota als 5s, DEAD: El Lemming es destruit, DEADFALL: El Lemming cau d'una gran altura
	OPENUMBRELLA: El Lemming obra el paraigües, NOSTAIR: El Lemming es queda sense rajoles
	*/
	enum EstatsEnum{
		MOVE, FALL, BREAK, GLIDE, CLIMB, DIG, PICK, STOP, STAIR, EXPLOSION, 
		DEAD, DEADFALL, OPENUMBRELLA, NOSTAIR
	};
	int GetEstat();

	// Sets per canviar l'Estat 
	void SetMoure();
	void SetCaure();

	void SetTrencar();
	void SetPrincipiLevitar();
	void SetLevitar();
	void SetCavar();
	void SetPicar();
	void SetImmobilitzar();
	void SetConstruirEscala();
	void SetNoEscales();
	void SetExplotar();

	// Estats temporals 
	void Moure();
	void Moure(bool diagAmunt);
	void TrencarMur();
	void Levitar();
	void Escalar();
	void Cavar();
	void Picar();
	void Caure();
	void Immobilitzar();
	void ConstruirEscala();
	void Explotar();

	// Equipables, com Paraigües i Escalar
	void SetParaigues();
	void SetEscalar();

};


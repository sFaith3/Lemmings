#pragma once
#include "ElementGame.h"

class Lemming :
	public ElementGame
{
private:

	int estat;
	int dir; // Direcció del Lemming a l'hora de moure's || 0 / 2.
	int temps;
	bool paraigues;
	bool escalar;


public:
	Lemming();
	~Lemming();

	void Init(int x, int y, const char* sp, int srcX, int srcY, int w, int h);
	void Update();

	int GetPosX();
	int GetPosY();
	int GetWidth();
	int GetHeight();
	int GetDir();

	/*
	MOVE: Moures, FALL: Caure, BREAK: Trencar Parets, GLIDE: Planejar, DIG: Cavar,
	STOP: Inmovilitzat, STAIR: Posar Escales,PICK: Cavar amb el Pic EXPLOSION: Explota als 5s.
	*/
	enum estats{
		MOVE, FALL, BREAK, GLIDE, CLIMB, DIG, PICK, STOP, STAIR, EXPLOSION
	};

	int GetEstat();

	void SetMoure();
	void SetCaure();

	// Estats temporals 
	void Moure(int dir);
	void TrencarMur();
	void Levitar();
	void Escalar();
	void Cavar();
	void Picar();
	void Caure();
	void Inmovilitzar();
	void ConstruirEscala();
	void Explotar();
	// Equipables, com Paraigües i Escalar
	void SetParaigues();
	void SetEscalar();
};


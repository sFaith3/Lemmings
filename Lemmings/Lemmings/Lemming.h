#pragma once
#include "ElementGame.h"
class Lemming :
	public ElementGame
{
private:

	/* 
	MOVE: Moures, FALL: Caure, BREAK: Trencar Parets, GLIDE: Planejar, DIG: Cavar,
	STOP: Inmovilitzat, STAIR: Posar Escales,PICK: Cavar amb el Pic EXPLOSION: Explota als 5s
	*/
	enum estats{
		MOVE, FALL, BREAK, GLIDE, CLIMB, DIG, PICK, STOP, STAIR, EXPLOSION
	};
	int estat;
	int dir; //Direcció del Lemming a l'hora de moure's.

public:
	Lemming();
	~Lemming();

	void Init(int x, int y, const char* sp, int srcX, int srcY, int w, int h);
	void Update();

	int GetDir();
	
	// Estats temporals 
	void Moure(bool dreta);
	void TrencarMur();
	void Levitar();
	void Escalar();
	void Cavar();
	void Picar();
	void Caure();
	void Inmovilitzar();
	void Construir();
	void Explotar();
	// Equipables com Paraigües i Escalar
	void SetParaigues();
	void SetEscalar();
};


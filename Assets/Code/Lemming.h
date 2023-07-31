#pragma once
#include "ElementGame.h"
#include "Map.h"

class Lemming :
	public ElementGame
{
public:
	// MOVE: Moure's, FALL: Caure, BREAK: Trencar Parets, GLIDE: Planejar, DIG: Cavar,
	// PICK: Cavar amb el Pic, IMMOBILE: Inmovilitzat, STAIRS: Posar rajoles, EXPLOSION: Foc de l'Explosio,
	// DEAD: El Lemming es destruït, DEAD_FALL: El Lemming cau d'una gran altura,
	// OPEN_UMBRELLA: El Lemming obra el paraigües, NO_STAIRS: El Lemming es queda sense rajoles,
	// END_CLIMB: El Lemming acaba d'escalar i torna a terra pla, EXPLODING: El Lemming fa l'animacio de que va a explotar.
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

	const int fallMaxTime = 60;
	int currFallTime;
	int lifeTime; // Compte enrere de X s.

	int displacement;

	// Equipa X habilitats al Lemming, que les realitzarà quan compleixi certa condició.
	bool hasUmbrella;
	bool canClimb;

	bool initialFallenDead;
	bool isDead;

	bool isGoingToExplode; // Variable que indica el començament del compte enrere de l'explosió.

	int levelTime; // Temps restant de la partida.

	bool isImmobilized; // Per a bloquejar aquella posició del mapa quan el Lemming s'aturi passant a l'estat "STOP".

	bool isRescued; // S'activa quan un Lemming passa per la porta.

	int currNumberStairsBuilt;

	enum SoundsEnum {
		BeforeExplode, Explosion, FallenDead, Stairs, Yippee, MaxSounds
	};
	int idSounds[MaxSounds];

	SDL_RendererFlip flipType; // Gira la imatge quan canvïa la direcció.

	InputManager* inputManager;

public:
	Lemming();
	~Lemming();

	void init(int x, int y, int mapPosX, int mapPosY);
	void update(Map* map, int x1, int y1, int x2, int y2, int time);
	void render();

	int GetLimitX();
	int GetDirection();
	StatesEnum GetCurrState();
	bool GetIsDead();
	bool GetIsGoingToExplode();
	bool GetIsRescued();

	bool IsCursorOnLemming();

	bool SetSkill(int numUses, int skill, int time);
	void SetDirection(int dir);
	void SetMove();
	void SetFall();
	void SetFallenDeath();
	void SetBreakWall();
	void SetOpenUmbrella();
	void SetGlidingUmbrella();
	void SetDig();
	void SetPick();
	void SetImmobilize();
	void SetBuiltStairs();
	void SetNoStairs();
	void SetClimb();
	void SetFinalClimb();
	void SetExploding();
	void SetExplosion();
	void SetLevelTimeToExplode(int time);
	void SetRescued();

	void PutUmbrella();
	void PutClimb();

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


#pragma once
#include "ElementGame.h"
#include "Map.h"

class Lemming :
	public ElementGame
{
public:
	// BREAK: Trenca parets, STAIRS: Posa rajoles, NO_STAIRS: Es queda sense rajoles,
	// EXPLODING: Fa l'animacio de que va a explotar.
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

	int levelTime; // Temps restant del nivell.

	bool isImmobilized; // Per a bloquejar aquella posició del mapa quan el Lemming s'aturi passant a l'estat "IMMOBILE".

	bool isRescued; // S'activa quan un Lemming passa per la porta de sortida.

	int currNumberStairsBuilt;

	enum SoundsEnum {
		BeforeExplode, Explosion, FallenDead, Stairs, Yippee, MaxSounds
	};
	int idSounds[MaxSounds];

	SDL_RendererFlip flipType; // Gira la imatge quan canvia la direcció.

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

	bool IsCursorOnLemming();
	void PutUmbrella();
	void PutClimb();
	void Move();
	void Move(bool isDiagonalUp);
	void BreakWall(Map* map, int x1, int x2, int y1, int y2);
	void Glide();
	void Climb();
	void Dig(Map* map, int x2, int y2);
	void Pick(Map* map, int x2, int y2);
	void Immobilize(Map* map, int x1, int x2, int y1, int y2);
	void PutStep(Map* map, int x1, int x2, int y2);
	void BuildStairs();
	void Fall();
	void CheckExplosion(int time);
	void Explode(Map* map, int x1, int y1, int x2, int y2);
};
#pragma once
#include "ElementGame.h"
#include "Map.h"

class Lemming :
	public ElementGame
{
public:
	// BREAK: Break walls, STAIRS: Put steps, NO_STAIRS: No steps left,
	// EXPLODING: Making the animation of going to explode.
	enum StatesEnum {
		MOVE, FALL, BREAK, GLIDE, CLIMB, DIG, PICK, IMMOBILE, STAIRS, EXPLOSION,
		DEAD, DEAD_FALL, OPEN_UMBRELLA, NO_STAIRS, END_CLIMB, RESCUED, EXPLODING
	};
private:
	int mapPosX, mapPosY; // Additional displacement, only for the render, due to the map.
	int width, height; // Width and height of the image.

	int limitX; // A margin to calculate the displacement and not cross the map.

	StatesEnum currState;
	int direction; // Direction when moving: 0: Right / 2: Left.

	const int fallMaxTime = 60;
	int currFallTime;
	int lifeTime; // Countdown to Xs.

	int displacement;

	// Equip X skills that will perform them when it fulfill a certain condition.
	bool hasUmbrella;
	bool canClimb;

	bool initialFallenDead;
	bool isDead;

	bool isGoingToExplode; // Variable indicating the start of the explosion countdown.

	int levelTime; // Remaining time of level.

	bool isImmobilized; // To block that map position when stops moving to 'IMMOBILE' state.

	bool isRescued; // It's triggered when it passes through the exit door.

	int currNumberStairsBuilt;

	enum SoundsEnum {
		BeforeExplode, Explosion, FallenDead, Stairs, Yippee, MaxSounds
	};
	int idSounds[MaxSounds];

	SDL_RendererFlip flipType; // Rotates the image when the direction changes.

	InputManager* inputManager;

public:
	Lemming();
	~Lemming();

	void init(const int x, const int y, const int mapPosX, const int mapPosY);
	void update(Map* map, const int x1, const int y1, const int x2, const int y2, const int time);
	void updateMove(Map* map, const int x1, const int x2, const int y2);
	void updateFall(Map* map, const int x1, const int x2, const int y2);
	void updateBreak(Map* map, const int x1, const int y1, const int x2, const int y2);
	void updateGlide(Map* map, const int x1, const int x2, const int y2);
	void updateClimb(Map* map, const int x1, const int y1, const int x2, const int y2);
	void updateDig(Map* map, const int x1, const int y1, const int x2, const int y2);
	void updatePick(Map* map, const int x1, const int y1, const int x2, const int y2);
	void updateStairs(Map* map, const int x1, const int x2, const int y2);
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
	void Fall();
	void CheckExplosion(int time);
	void Explode(Map* map, int x1, int y1, int x2, int y2);
};
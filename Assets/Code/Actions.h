#pragma once
#include "ElementHUD.h"
#include "Background.h"
#include "Skill.h"
#include "Lemming.h"

class Actions :
	public ElementHUD
{
private:
	const int NextCheck = -2; // To check if it needs to go to the next method in update()

	vector<Skill*> skills; // Lemming skills vector.
	vector<Skill*>::iterator itSkills;

	enum ActionEnum {
		REST_VEL_SPAWN, PLUS_VEL_SPAWN, CLIMB, UMBRELLA, EXPLOSION, STANDING, STEPS, SIDE_DIG, CHIP, DIG, PAUSE, MOAB
	};

	int currButton; // To know the current ActionEnum.

	GameStats* gameStats;

	InputManager* inputManager;

public:
	Actions();
	~Actions();

	int init(float scaleX, float scaleY, string minVelSpawn, string climb, string umbrella, string explosion, string standing, string steps, string sideDig, string chip, string dig);
	void InitSkills(int x, int y, string minVelSpawn, string climb, string umbrella, string explosion, string standing, string steps, string sideDig, string chip, string dig);
	int update();
	bool IsNextCheck(int actionToReturn);
	void render();

	int CheckPressButton();
	int CheckPressNumber();

	int GetNumberUsesSkill(int skill);
	void DetractUseSkill(int skill);

	void DecrementVelocitySkill();
	void IncrementVelocitySkill();
};
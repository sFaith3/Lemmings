#pragma once
#include "ElementHUD.h"
#include "Background.h"
#include "Skill.h"
#include "Lemming.h"

class Actions :
	public ElementHUD
{
private:
	vector<Skill*> skills; // Lemming skills vector.
	vector<Skill*>::iterator itSkills;

	int currButton; // To know the current ActionEnum.

	GameStats* gameStats;
	InputManager* inputManager;

public:
	enum ActionEnum {
		REST_VEL_SPAWN, PLUS_VEL_SPAWN, CLIMB, UMBRELLA, EXPLOSION, STANDING, STEPS, SIDE_DIG, CHIP, DIG, PAUSE, MOAB, MAX_NUM_ACTIONS_ENUM = 11
	};

	Actions();
	~Actions();

	int getPressButton();
	int getPressNumber();
	int getNumberUsesSkill(const int skill);

	int init(float scaleX, float scaleY, string minVelSpawn, string climb, string umbrella, string explosion, string standing, string steps, string sideDig, string chip, string dig);
	void initSkills(int x, int y, string minVelSpawn, string climb, string umbrella, string explosion, string standing, string steps, string sideDig, string chip, string dig);
	int update();
	bool isNextCheck(const int actionToReturn);
	void render();

	void detractUseSkill(const int skill);
	void decrementVelocitySkill();
	void incrementVelocitySkill();
};
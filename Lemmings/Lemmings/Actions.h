#pragma once
#include "ElementHUD.h"
#include "Background.h"
#include "Skill.h"
#include "Lemming.h"

class Actions :
	public ElementHUD
{
private:
	// Vector d'habilitats dels Lemmings.
	vector<Skill*> skills;
	vector<Skill*>::iterator itSkills;

	enum ActionEnum{
		REST_VEL_SPAWN, PLUS_VEL_SPAWN, TREPAR, PARAIGUES, EXPLOSIO, PARAT, ESGRAONS, CAVAR_LATERAL, PICAR, CAVAR, PAUSA, MOAB
	};

	int currButton; // Indica l'ActionEnum en què es troba.

	GameStats* gameStats;

	InputManager* inputManager;

public:
	Actions();
	~Actions();

	int init(float scaleX, float scaleY, string velMinimaSpawn, string trepar, string paraigues, string explosio, string parat, string esgraons, string cavarLateral, string picar, string cavar);
	int update();
	void render();

	int GetNumberUsesSkill(int skill);
	void DetractUseSkill(int skill);

	void DecrementVelocitySkill();
	void IncrementVelocitySkill();
};
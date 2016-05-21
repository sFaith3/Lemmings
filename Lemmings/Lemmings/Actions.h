#pragma once
#include "ElementHUD.h"
#include "Background.h"
#include "Skill.h"
#include "Lemming.h"

class Actions :
	public ElementHUD
{
private:
	vector<Skill> skills;
	vector<Skill>::iterator itSkills;

	enum ActionEnum{
		REST_VEL_SPAWN, PLUS_VEL_SPAWN, TREPAR, PARAIGUES, EXPLOSIO, PARAT, ESGRAONS, CAVAR_LATERAL, PICAR, CAVAR, DD, MOAB
	};

	int currButton;

	InputManager* inputManager;

public:
	Actions();
	~Actions();

	void init(int trepar, int paraigues, int explosio, int parat, int esgraons, int cavarLateral, int picar, int cavar);
	int update();
	void render();

	int GetNumberUsesSkill(int skill);
	void DetractUseSkill(int skill);
};
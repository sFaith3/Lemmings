#pragma once
#include "ElementHUD.h"
#include "Background.h"
#include "Skill.h"
#include "Lemming.h"

class Actions :
	public ElementHUD
{
private:
	vector<Skill*> skills;
	vector<Skill*>::iterator itSkills;

	enum ActionEnum{
		REST_VEL_SPAWN, PLUS_VEL_SPAWN, TREPAR, PARAIGUES, EXPLOSIO, PARAT, ESGRAONS, CAVAR_LATERAL, PICAR, CAVAR, DD, MOAB
	};

	int currButton;

	InputManager* inputManager;

public:
	Actions();
	~Actions();

	void init(float scaleX, float scaleY, string trepar, string paraigues, string explosio, string parat, string esgraons, string cavarLateral, string picar, string cavar);
	int update();
	void render();

	int GetNumberUsesSkill(int skill);
	void DetractUseSkill(int skill);
};
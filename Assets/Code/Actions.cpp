#include "Actions.h"


Actions::Actions(){
	for (int i = 0; i < 12; i++)
		skills.push_back(new Skill());

	gameStats = GameStats::getInstanceGameStats();

	inputManager = SingletonManager::getInstanceSingleton()->getInputManager();
}


Actions::~Actions(){
}


int Actions::init(float scaleX, float scaleY, string velMinimaSpawn, string trepar, string paraigues, string explosio, string parat, string esgraons, string cavarLateral, string picar, string cavar){
	int hAction = 61;
	int x = 0;
	int y = SCREEN_HEIGHT - hAction;
	ElementHUD::init(x, y, "Assets/Art/Images/HUD/Skills/hud.png", false, 0, 0, 480, hAction, scaleX, scaleY);
	
	currButton = TREPAR;

	int xSkill = x + 1;
	int wSkill = 40;
	int hSkill = 61;
	const char* imgSkillPressed = "Assets/Art/Images/HUD/Skills/skillsPressed.png";

	skills[0]->init(REST_VEL_SPAWN, xSkill, y, wSkill, hSkill, 0, 0, NULL, NULL, velMinimaSpawn);
	xSkill += wSkill;
	skills[1]->init(PLUS_VEL_SPAWN, xSkill, y, wSkill, hSkill, 0, 0, NULL, NULL, velMinimaSpawn);
	int velMinSpawn = 0;;
	for (int i = 0; i < velMinimaSpawn.length(); i++){
		if (i == 0)
			velMinSpawn += ((int)velMinimaSpawn[i] - 48) * 10;
		else
			velMinSpawn += (int)velMinimaSpawn[i] - 48;
	}
	skills[1]->SetMinVelocity(velMinSpawn);
	xSkill += wSkill;
	skills[2]->init(TREPAR, xSkill, y, wSkill, hSkill, 0, 0, NULL, imgSkillPressed, trepar);
	xSkill += wSkill;
	skills[3]->init(PARAIGUES, xSkill, y, wSkill, hSkill, 0, 0, NULL, imgSkillPressed, paraigues);
	xSkill += wSkill;
	skills[4]->init(EXPLOSIO, xSkill, y, wSkill, hSkill, 0, 0, NULL, imgSkillPressed, explosio);
	xSkill += wSkill;
	skills[5]->init(PARAT, xSkill, y, wSkill, hSkill, 0, 0, NULL, imgSkillPressed, parat);
	xSkill += wSkill;
	skills[6]->init(ESGRAONS, xSkill, y, wSkill, hSkill, 0, 0, NULL, imgSkillPressed, esgraons);
	xSkill += wSkill;
	skills[7]->init(CAVAR_LATERAL, xSkill, y, wSkill, hSkill, 0, 0, NULL, imgSkillPressed, cavarLateral);
	xSkill += wSkill;
	skills[8]->init(PICAR, xSkill, y, wSkill, hSkill, 0, 0, NULL, imgSkillPressed, picar);
	xSkill += wSkill;
	skills[9]->init(CAVAR, xSkill, y, wSkill, hSkill, 0, 0, NULL, imgSkillPressed, cavar);
	xSkill += wSkill;
	skills[10]->init(PAUSA, xSkill, y, wSkill, hSkill, 0, 0, NULL, NULL, "NULL");
	xSkill += wSkill;
	skills[11]->init(MOAB, xSkill, y, wSkill, hSkill, 0, 0, NULL, NULL, "NULL");

	skills[currButton]->SetPressed(true);

	return currButton;
}


int Actions::update(){
	for (itSkills = skills.begin(); itSkills != skills.end(); itSkills++){
		if ((*itSkills)->update()){
			if (currButton != -1){
				int pressedBut = (*itSkills)->GetId();
				if (!gameStats->GetPause() && (pressedBut != REST_VEL_SPAWN && pressedBut != PLUS_VEL_SPAWN && pressedBut != PAUSA && pressedBut != MOAB)){
					skills[currButton]->SetPressed(false);
					(*itSkills)->SetPressed(true);
					inputManager->ResetClick();

					return (currButton != pressedBut) ? currButton = (*itSkills)->GetId() : -1;
				}

				return (*itSkills)->GetId();
			}
			return -1;
		}
	}

	int number = inputManager->CheckNumber();
	if (number != -1){
		if (number != REST_VEL_SPAWN && number != PLUS_VEL_SPAWN && number != MOAB){
			skills[currButton]->SetPressed(false);
			skills[number]->SetPressed(true);
			inputManager->ResetNumber();

			return (currButton != number) ? currButton = skills[number]->GetId() : -1;
		}

		return skills[number]->GetId();
	}

	return -1;
}


void Actions::render(){
	ElementHUD::render();

	for (itSkills = skills.begin(); itSkills != skills.end(); itSkills++){
		(*itSkills)->render();
	}
}


int Actions::GetNumberUsesSkill(int skill){
	if (skill >= 0)
		return skills[skill]->GetNumberUses();

	return 0;
}

void Actions::DetractUseSkill(int skill){
	skills[skill]->OneUseLess();
}


void Actions::DecrementVelocitySkill(){
	skills[PLUS_VEL_SPAWN]->LessVelocity();
}

void Actions::IncrementVelocitySkill(){
	skills[PLUS_VEL_SPAWN]->MoreVelocity();
}
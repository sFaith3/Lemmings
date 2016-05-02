#include "Actions.h"


Actions::Actions()
{
}


Actions::~Actions()
{
}


void Actions::init(int x, int y, const char* img, int srcX, int srcY, int w, int h){
	ElementHUD::init(x, y, img, srcX, srcY, w, h);
	
	Button action;
	int xAction = x + 1;
	int wAction = 40;
	int hAction = 61;
	action.init(REST_VEL_SPAWN, xAction, y, wAction, hAction, 0, 0, NULL);
	actions.push_back(action);
	xAction += wAction;
	action.init(PLUS_VEL_SPAWN, xAction, y, wAction, hAction, 0, 0, NULL);
	actions.push_back(action);
	xAction += wAction;
	action.init(TREPAR, xAction, y, wAction, hAction, 0, 0, NULL);
	actions.push_back(action);
	xAction += wAction;
	action.init(PARAIGUES, xAction, y, wAction, hAction, 0, 0, NULL);
	actions.push_back(action);
	xAction += wAction;
	action.init(EXPLOSIO, xAction, y, wAction, hAction, 0, 0, NULL);
	actions.push_back(action);
	xAction += wAction;
	action.init(PARAT, xAction, y, wAction, hAction, 0, 0, NULL);
	actions.push_back(action);
	xAction += wAction;
	action.init(ESGRAONS, xAction, y, wAction, hAction, 0, 0, NULL);
	actions.push_back(action);
	xAction += wAction;
	action.init(CAVAR_LATERAL, xAction, y, wAction, hAction, 0, 0, NULL);
	actions.push_back(action);
	xAction += wAction;
	action.init(PICAR, xAction, y, wAction, hAction, 0, 0, NULL);
	actions.push_back(action);
	xAction += wAction;
	action.init(CAVAR, xAction, y, wAction, hAction, 0, 0, NULL);
	actions.push_back(action);
	xAction += wAction;
	action.init(DD, xAction, y, wAction, hAction, 0, 0, NULL);
	actions.push_back(action);
	xAction += wAction;
	action.init(MOAB, xAction, y, wAction, hAction, 0, 0, NULL);
	actions.push_back(action);
}


void Actions::update(){

}


void Actions::render(){
	ElementHUD::render();

	for (itActi = actions.begin(); itActi != actions.end(); itActi++){
		itActi->render();
	}
}
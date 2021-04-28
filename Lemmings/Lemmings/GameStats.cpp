#include "GameStats.h"


GameStats* GameStats::pInstance = NULL;

GameStats::GameStats(){
	level = 1;
	pause = false;
	win = false;
}


GameStats::~GameStats(){

}


GameStats* GameStats::getInstanceGameStats(){
	if (pInstance == NULL)
		pInstance = new GameStats();

	return pInstance;
}


void GameStats::ResetLevel(){
	level = 1;
}


int GameStats::GetLevel(){
	return level;
}

bool GameStats::GetPause(){
	return pause;
}

bool GameStats::GetWin(){
	return win;
}


void GameStats::IncrementLevel(){
	level++;
}

void GameStats::SetPause(bool paused){
	pause = paused;
}

void GameStats::SetWin(bool victory){
	win = victory;
}
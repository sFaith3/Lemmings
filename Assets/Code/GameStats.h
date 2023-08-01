#ifndef GAMESTATS_H
#define GAMESTATS_H

#include "Utils.h"

class GameStats
{
private:
	GameStats();

	static GameStats* pInstance; /*<!	Singleton instance*/

	int level; // The current level.
	bool pause; // When 'pause' is true, the game is stopped.
	bool win; // It serves to know if the player passes to the next level and to show the corresponding information in 'ScenePostGame'.

public:
	~GameStats();

	//!	Gets Singleton instance.
	static GameStats* getInstanceGameStats();

	void ResetLevel();

	int GetLevel();
	bool GetPause();
	bool GetWin();

	void IncrementLevel();
	void SetPause(bool paused);
	void SetWin(bool victory);
};

#endif
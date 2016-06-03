#ifndef GAMESTATS_H
#define GAMESTATS_H

#include "Utils.h"

class GameStats
{
private:
	GameStats();

	static GameStats* pInstance; /*<!	Singleton instance*/

	int level; // Nivell de joc en què es troba.
	bool sound; // Indica si el so s'ha de mutejar a SceneGame.
	bool pause; // Quan s'activa el joc es pausa.
	bool win; // Serveix per a saber si el jugador passa de nivell i per a mostrar l'informació que pertoca a ScenePostGame.

public:
	~GameStats();

	//!	Gets Singleton instance.
	static GameStats* getInstanceGameStats();

	int GetLevel();
	bool GetSound();
	bool GetPause();
	bool GetWin();

	void IncrementLevel();
	void SetSound(bool enabled);
	void SetPause(bool paused);
	void SetWin(bool victory);
};

#endif
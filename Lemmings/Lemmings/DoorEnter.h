#pragma once
#include "ElementGame.h"

class DoorEnter :
	public ElementGame
{
private:
	int timeToBeReady; // Temps que triga a passar a l'estat següent d'obrir les portes.
	int timeToSpawn; // Temps que triga a instanciar un Lemming.
	int _timeToSpawn; // Igual que l'anterior, però aquesta fa d'auxiliar en el càlcul que es fa per variar, in game, la variable anterior.
	int lastTime; // Auxiliar per a calcular el temps en que s'ha d'instanciar un Lemming.

	bool spawnning; // S'activa quan ha completat el temps. De manera, que indica a SceneGame, quan s'ha d'instanciar un Lemming.
	int leftToSpawn; // Elements que falten per crear.

	enum EstatsEnum{
		NOT_READY, OPENNING, READY, EMPTY
	};
	int currEstat;

public:
	DoorEnter(int x, int y, int timeToSpawn, int numInstancies);
	~DoorEnter();

	void update(int temps);

	bool getSpawnning();

	void setTimeToSpawn(int temps);

	int getNumToSpawn();

	void notMoreSpawns();
};


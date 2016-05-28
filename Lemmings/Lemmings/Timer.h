#pragma once
#include "ElementHUD.h"
#include "ABCsAlphaNum.h"

class Timer :
	public ElementHUD
{
private:
	Uint32 mStarTicks;
	Uint32 mPausedTicks;
	bool mStarted;
	bool mPaused;

	bool tempsOut;
	int tempsRestant; // En segons. SDL_GetTicks() ho fa en ms.
	Uint32 lastTime;

	// Igual que 'tempsRestant'. Però, cada xifra separada, per tal de mostrar els números a la HUD.
	int minuts, primerNumSegons, segonNumSegons;
	vector<ABCsAlphaNum*> nums;
	vector<ABCsAlphaNum*>::iterator itNums;

public:
	Timer(int x, int y, string tempsRestant);
	~Timer();

	void start();
	void update();
	void render();

	void pause();
	void unpause();
	void stop();

	Uint32 getTime();
	Uint32 getTimeMs();

	bool isStarted();
	bool isPaused();

	bool getTempsOut();
};


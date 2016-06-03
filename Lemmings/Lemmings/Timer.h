#pragma once
#include "ElementHUD.h"
#include "ABCsAlphaNum.h"

class Timer :
	public ElementHUD
{
private:
	Uint32 mStarTicks; // Temps en el moment de començar a comptar. Es necesita per a calcular la diferència de temps actual del programa amb el del moment
					   // en que s'ha accionat el mètode start(). Per tal de mostrar, en la primera execució de l'update(), un 0 en comptes del temps que
					   // porti el programa executant-se.
	Uint32 mPausedTicks; // Temps en pausa. Per a calcular la diferència quan es reanudi el Timer.
	bool mStarted; // El Temps s'ha començat a comptar.
	bool mPaused; // El Temps està pausat.

	bool tempsOut; // S'ha esgotat el temps del Timer. En aquest cas va d'X a 0. Així que a 0 serà true. Es necessita per a finalitzar la partida per causa
				   // de quedar-se sense temps.
	int tempsRestant; // Temps restant en segons. SDL_GetTicks() ho fa en ms.
	Uint32 lastTime; // Temps, anterior a l'actual, en aquella execució de l'update(). Per a obtenir la diferència.

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


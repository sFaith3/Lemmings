#ifndef SCENEMENU_H
#define SCENEMENU_H

#include "Utils.h"
#include "SceneManager.h"
#include "SceneGame.h"
#include "Background.h"
#include "Button.h"

class SceneMenu :
	public Scene
{
private:
	SceneMenu();

	static SceneMenu* gInstance; /*!<	Singleton instance*/

	Background* background;

	enum ButtonsEnum{
		PLAYER = 1, MUTE_SOUND = 3, EXIT
	};
	vector<Button> buttons;
	vector<Button>::iterator itBut;

	Background imgAudios[2];

	enum AudioEnum{
		Fx, Music, Mute
	};
	int currAudio;

	SceneGame* sGame;

	SceneManager* smManager;

public:
	~SceneMenu();

	//! Gets Singleton instance.
	static SceneMenu* getInstanceSceneMenu();

	void init();
	void update();
	void render();

	void updateButtons();
	void updateInput();
};

#endif
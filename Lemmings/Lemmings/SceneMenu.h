#ifndef SCENEMENU_H
#define SCENEMENU_H

#include "Background.h"
#include "Button.h"
#include "SceneManager.h"
#include "SceneGame.h"

class SceneMenu :
	public Scene
{
private:
	SceneMenu();

	static SceneMenu* gInstance; /*!<	Singleton instance*/

	Background *fons;

	bool soJoc;

	enum ButtonsEnum{
		PLAYER = 1, NEW_LEVEL, MUTE_SOUND, EXIT
	};
	vector<Button> buttons;
	vector<Button>::iterator itBut;

	SceneGame* sGame;

	SceneManager* smManager;

public:
	~SceneMenu();

	//! Gets Singleton instance.
	static SceneMenu* getInstanceSceneMenu();

	void init();
	void update();
	void render();
};

#endif
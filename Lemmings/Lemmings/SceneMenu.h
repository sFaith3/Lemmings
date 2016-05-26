#pragma once
#include "Scene.h"
#include "Background.h"
#include "Button.h"
#include "SceneManager.h"

class SceneMenu :
	public Scene
{
private:
	Background *fons;

	enum ButtonsEnum{
		PLAYER = 1, NEW_LEVEL, AUDIO, FUN, EXIT
	};
	vector<Button> buttons;
	vector<Button>::iterator itBut;

	SceneManager* smManager;

public:
	SceneMenu();
	~SceneMenu();

	void init();
	void update();
	void render();
};
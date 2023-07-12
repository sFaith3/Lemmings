#pragma once
#include "ElementHUD.h"

class Button
{
protected:
	int id; // Name related to what to do if clicked on it. Depending on the value of this string, the code will perform X management.
	int posX, posY; // Variables that define the position on the coordinate axis. They are used to render and condition inputs.
	int width, height; // They define the rectangle of this one to be able to paint it and detect input.
	float scaleX, scaleY;
	int posXini, posYini; // X/Y position where the image is started to be taken to perform the sprite.
	Sint32 idImgNormal, idImgPressed;
	bool pressed;

	InputManager* inputManager;
	VideoManager* videoManager;

public:
	Button();
	~Button();

	void init(int _id, int _posX, int _posY, int _width, int _height, float _scaleX, float _scaleY, int _posXini, int _posYini, const char* imgNormal, const char* imgPressed);
	bool update();
	void render();

	int getId();

	void setPressed(bool _pressed);
};
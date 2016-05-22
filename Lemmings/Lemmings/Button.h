#pragma once
#include "ElementHUD.h"

class Button
{
protected:
	int id; //Nom, del lloc on porta, si es clica a sobre d'ell. Depenent de varlo d'aquest string, el codi realitzar� X gesti�.
	int posX, posY; //Variables, que defineixen la posici� en els eixos de coordenades. I s'utilitzen per a renderitzar i condicionen els inputs.
	int width, height; //Defineixen el rectangle d'aquest. Per tal de poder pintar-lo i detectar l'input.
	float scaleX, scaleY;
	int posXini, posYini; //Posici� X/Y, on es comen�a a agafar, la imatge per a realitzar l'sprite.
	Sint32 idImgNormal, idImgButPressed;
	bool pressed;

	InputManager* inputManager;
	VideoManager* videoManager;

public:
	Button();
	~Button();

	int GetId();

	void init(int _id, int _posX, int _posY, int _width, int _height, float _scaleX, float _scaleY, int _posXini, int _posYini, const char* imgNormal, const char* imgButPressed);
	bool update();
	void render();

	void SetPressed(bool _pressed);
};
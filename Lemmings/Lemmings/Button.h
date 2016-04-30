#pragma once
#include "ElementHUD.h"

class Button :
	public ElementHUD
{
private:
	string id; //Nom, del lloc on porta, si es clica a sobre d'ell. Depenent de varlo d'aquest string, el codi realitzarà X gestió.
	int posX, posY; //Variables, que defineixen la posició en els eixos de coordenades. I s'utilitzen per a renderitzar i condicionen els inputs.
	int width, height; //Defineixen el rectangle d'aquest. Per tal de poder pintar-lo i detectar l'input.
	int posXini, posYini; //Posició X/Y, on es comença a agafar, la imatge per a realitzar l'sprite.
	const char* path; //Ruta de la imatge del botó.
	bool click;

public:
	Button();
	~Button();

	string GetId();
	bool GetClick();

	void init(string _id, int _posX, int _posY, int _width, int _height, int _posXini, int _posYini, const char* _path);
	void update(bool mouse, int posXmouse, int posYmouse);
	void render();
};
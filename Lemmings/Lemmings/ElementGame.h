#pragma once
#include "Element.h"
class ElementGame :
	public Element
{
protected:
	int widthSpriteSheet, heightSpriteSheet; // Amplada i al�ada total de l'spritesheet.
	int toNextSpriteX, toNextSpriteY; // Posicions que ha de rec�rre per arribar al seg�ent sprite.
	int numImatges; // N�mero d'imatges que t� aquell spritesheet.
	int contImatges; // Sprite actual de l'animaci� que s'est� pintant.
	int fpsAnimacio, currFpsAnim; // Temps que triga en canviar d'animaci� i temps actual que t� en aquell moment.
								  // Quan currFpsAnim es igual a fpsAnimacio, l'sprite canv�a.
	int numSaltsImatges; // Nombre de files qu� ha de despla�ar-se en total. Quan l'sprite arribi al l�mit de l'spritesheet, sense ser aquest l'�ltim, realitza un salt de fila en l'spritesheet.
						 // i es posiciona a la x inicial d'aquest. S'indica el nombre m�xim de despla�aments per fila.

public:
	ElementGame();
	~ElementGame();

	void init(int x, int y, const char* img, int srcX, int srcY, int w, int h, float scaleX, float scaleY, int wSpriteSheet, int hSpriteSheet, int toNextSpriteX, int numImgs, int fpsAnim);

	void UpdateAnimacio(); // Animacio de SpriteSheet.
};


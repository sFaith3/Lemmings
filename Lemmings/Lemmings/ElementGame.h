#pragma once
#include "Element.h"
class ElementGame :
	public Element
{
protected:
	int widthSpriteSheet, heightSpriteSheet; // Amplada i alçada total de l'spritesheet.
	int toNextSpriteX, toNextSpriteY; // Posicions que ha de recórre per arribar al següent sprite.
	int numImatges; // Número d'imatges que té aquell spritesheet.
	int contImatges; // Sprite actual de l'animació que s'està pintant.
	int fpsAnimacio, currFpsAnim; // Temps que triga en canviar d'animació i temps actual que té en aquell moment.
								  // Quan currFpsAnim es igual a fpsAnimacio, l'sprite canvïa.
	int numSaltsImatges; // Nombre de files què ha de desplaçar-se en total. Quan l'sprite arribi al límit de l'spritesheet, sense ser aquest l'últim, realitza un salt de fila en l'spritesheet.
						 // i es posiciona a la x inicial d'aquest. S'indica el nombre màxim de desplaçaments per fila.

public:
	ElementGame();
	~ElementGame();

	void init(int x, int y, const char* img, int srcX, int srcY, int w, int h, float scaleX, float scaleY, int wSpriteSheet, int hSpriteSheet, int toNextSpriteX, int numImgs, int fpsAnim);

	void UpdateAnimacio(); // Animacio de SpriteSheet.
};


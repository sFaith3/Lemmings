#ifndef VIDEOMANAGER_H
#define VIDEOMANAGER_H

#include "SDL.h"

class VideoManager
{
private:
	VideoManager();

	static VideoManager* vInstance; /*!<	Singleton instance*/

	bool texture = true;
	//The actual hardware texture
	void* mPixels;
	int mPitch; // The pitch is basically the width of the texture in memory (in bytes).

	float deltaTime;
	int lastTime;
	float msFrame; 
	
public:
	~VideoManager();

	//! Gets Singleton instance.
	static VideoManager* getInstanceVideo();

	Sint32 addGraphic(const char* file);
	Sint32 getGraphicID(const char* file);
	Sint32 addTexture(const char* file);
	Sint32 addTextureManipulation(const char* file);
	Sint32 getTextureID(const char* file, bool textureManipulation = false);
	
	Uint32 getTime();
	Uint32 getColor(Uint8 r, Uint8 g, Uint8 b);
	Uint32 getColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

	//Pixel manipulators
	bool lockTexture(int img);
	bool unlockTexture(int img);
	void* getPixelsVoid();
	int getPitch();
	Uint32* getPixels();
	int getPixelCount(int height);

	void setCursorRelative(bool active);

	void renderGraphic(int img, int srcPosX, int srcPosY, int width, int height, int dstPosX, int dstPosY);
	/*!
	\params scale s'ha de tenir en compte que aquest es multiplica per un integer, i que el resultat d'aquella operació no pot ser float.
	*/
	void renderTexture(int img, int srcPosX, int srcPosY, int width, int height, float scaleX, float scaleY, int dstPosX, int dstPosY);
	/*!
	\params scale s'ha de tenir en compte que aquest es multiplica per un integer, i que el resultat d'aquella operació no pot ser float.
	*/
	void renderTexture(int img, int srcPosX, int srcPosY, int width, int height, float scaleX, float scaleY, int dstPosX, int dstPosY, double angle, int centerX, int centerY, SDL_RendererFlip flip);
	
	void clearScreen(unsigned int color_key);
	void updateScreen();

	void updateTime();
	void waitTime(int ms);

	void close();

	SDL_Window* gWindow;
	SDL_Surface* gScreenSurface;
	SDL_Renderer* gScreenRenderer;
};

#endif
#ifndef VIDEOMANAGER_H
#define VIDEOMANAGER_H

#include "Utils.h"

class VideoManager
{
private:
	float deltaTime;
	int lastTime;
	float msFrame; 
	static VideoManager* vInstance;

public:
	VideoManager();
	~VideoManager();

	void playAudio(int audio);
	
	void PauseAudio();

	void ResumeAudio();

	bool isAudioPaused();

	void renderTexture(int img, int src_posX, int src_posY, int src_width, int src_height, int dst_posX, int dst_posY, double angle, int centerX, int centerY);



	void clearScreen(unsigned int color_key);
	void updateScreen();

	int getTime();
	float getDeltaTime();
	void UpdateTime();
	void waitTime(int ms);

	void setCursorRelative(bool active);

	void close();
	static VideoManager* getInstanceVideo();

	SDL_Window* gWindow;
	SDL_Surface* gScreenSurface;
	SDL_Renderer* renderer;

};
#endif
#include "VideoManager.h"
#include "ResourceManager.h"

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "Utils.h"

VideoManager* VideoManager::vInstance = NULL;

VideoManager::VideoManager(){
	gWindow = NULL;
	gScreenSurface = NULL;
	renderer = NULL;
	SDL_Init(SDL_INIT_EVERYTHING);
	gWindow = SDL_CreateWindow("Examen SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (gWindow == NULL)
	{
		printf("Window could not be created! SDL Error: %s\n", SDL_GetError());

	}
	else
	{
		//Create renderer for window
		renderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
		if (renderer == NULL)
		{
			printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
			
		}
		else
		{
			//Initialize renderer color
			SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

			//Initialize PNG loading
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) & imgFlags))
			{
				printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
			}
		}
	}

	//Audio.
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
	}

	Mix_AllocateChannels(128);

	msFrame =(float)FPS / 1000.0f;
}

VideoManager::~VideoManager(){

}

VideoManager* VideoManager::getInstanceVideo(){
	if (vInstance == NULL){

		vInstance = new VideoManager();
	}
	return vInstance;
}

void VideoManager::playAudio(int audio){
	Mix_Chunk *sound = ResourceManager::getInstanceResourceManager()->getAudioByID(audio);
	Mix_PlayChannel(1, sound, 0);
}


void VideoManager::PauseAudio(){
	Mix_Pause(-1);
}

bool VideoManager::isAudioPaused(){
	return Mix_Paused(-1);
}


void VideoManager::ResumeAudio(){
	Mix_Resume(-1);
}



void VideoManager::setCursorRelative(bool active){
	if (active)
		SDL_SetRelativeMouseMode(SDL_TRUE);
	else
		SDL_SetRelativeMouseMode(SDL_FALSE);
}

Sint32 VideoManager::graphicID(const char* file){
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(file);
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", file, IMG_GetError());
	}
	else
	{
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", file, SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}
	return ResourceManager::getInstanceResourceManager()->getGraphicID(file, newTexture);
}

void VideoManager::renderTexture(int img, int src_posX, int src_posY, int src_width, int src_height, int dst_posX, int dst_posY, double angle, int centerX, int centerY){
	SDL_Rect r, rectAux;
	rectAux.x = src_posX;
	rectAux.y = src_posY;
	rectAux.w = src_width;
	rectAux.h = src_height;
	r.x = dst_posX;
	r.y = dst_posY;
	r.w = src_width;
	r.h = src_height;
	SDL_Texture *origin = ResourceManager::getInstanceResourceManager()->getGraphicByID(img);

	SDL_Point center;

	center.x = centerX;
	center.y = centerY;

	SDL_RenderCopyEx(renderer, origin, &rectAux, &r, angle, &center, SDL_FLIP_NONE);
}

void VideoManager::clearScreen(unsigned int color_key){
	//Clear screen
	SDL_SetRenderDrawColor(renderer, color_key, color_key, color_key, color_key);
	SDL_RenderClear(renderer);
}
void VideoManager::updateScreen(){
	//Update screen
	SDL_RenderPresent(renderer);
}

int VideoManager::getTime(){
	return SDL_GetTicks();
}

void VideoManager::waitTime(int ms){
	deltaTime = 0;
	lastTime = -1;
	SDL_Delay(ms);
	lastTime = getTime();
}

void VideoManager::close(){
	SDL_DestroyWindow(gWindow);
	SDL_Quit();
}

float VideoManager::getDeltaTime(){
	return deltaTime;
}

void VideoManager::UpdateTime(){
	if (lastTime != -1){
		int currentTime = getTime();
		deltaTime = (float)(currentTime - lastTime) / 1000;

		//Para evitar que el input del raton se ralentize, se elima la restriccion a 60 FPS
		if (deltaTime < msFrame){
			//waitTime((msFrame - deltaTime)*1000);
			//deltaTime = msFrame;
		}
		lastTime = currentTime;
	}
}
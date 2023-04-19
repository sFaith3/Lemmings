#include "VideoManager.h"
#include "ResourceManager.h"
#include "..\Utils.h"

VideoManager* VideoManager::vInstance = NULL;

VideoManager::VideoManager(){
	gWindow = NULL;
	gScreenSurface = NULL;
	gScreenRenderer = NULL;

	SDL_Init(SDL_INIT_EVERYTHING);

	gWindow = SDL_CreateWindow("Lemmings", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN /*SDL_WINDOW_FULLSCREEN*/);
	if (gWindow == NULL)
		cout << "Window could not be created! SDL Error: " << SDL_GetError() << endl;
	else{
		if (!texture){
			gScreenSurface = SDL_GetWindowSurface(gWindow);
			if (gScreenSurface == NULL)
				cout << "Window surface could not be created! SDL Error: " << SDL_GetError() << endl;
		}
		else{
			//Create gScreenRenderer for window
			gScreenRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gScreenRenderer == NULL)
				cout << "gScreenRenderer could not be created! SDL Error: " << SDL_GetError() << endl;
			else{
				//Initialize gScreenRenderer color
				SDL_SetRenderDrawColor(gScreenRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
					cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << endl;
			}
		}
	}

	deltaTime = 0.0f;
	lastTime = 0;
	msFrame = FPS;
}

VideoManager::~VideoManager(){

}


VideoManager* VideoManager::getInstanceVideo(){
	if (vInstance == NULL)
		vInstance = new VideoManager();

	return vInstance;
}


Sint32 VideoManager::addGraphic(const char* file){
	//The final optimized image
	SDL_Surface* optimizedSurface = NULL;
	SDL_Surface* surfaceFormatInfo = gScreenSurface;
	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(file);
	if (loadedSurface == NULL){
		cout << "Unable to load image '" << file << "'! SDL_image Error: " << IMG_GetError() << endl;
		return -1;
	}

	SDL_SetSurfaceBlendMode(surfaceFormatInfo, SDL_BLENDMODE_BLEND);
	//Convert surface to screen format
	// Save Alpha values from surface info
	Uint32 Old_Amask = surfaceFormatInfo->format->Amask;
	Uint32 Old_Aloss = surfaceFormatInfo->format->Aloss;
	Uint32 Old_Ashift = surfaceFormatInfo->format->Ashift;
	// Force Alpha values
	surfaceFormatInfo->format->Amask = 0xFF000000;
	surfaceFormatInfo->format->Aloss = 0;
	surfaceFormatInfo->format->Ashift = 24;
	// Convert to screen format
	optimizedSurface = SDL_ConvertSurface(loadedSurface, surfaceFormatInfo->format, NULL);
	// Restore alpha values for surface info
	surfaceFormatInfo->format->Amask = (Uint8)Old_Amask;
	surfaceFormatInfo->format->Aloss = (Uint8)Old_Aloss;
	surfaceFormatInfo->format->Ashift = (Uint8)Old_Ashift;
	if (optimizedSurface == NULL){
		cout << "Unable to optimize image '" << file << "'! SDL Error: " << SDL_GetError() << endl;
		return -1;
	}

	//Get rid of old loaded surface
	SDL_FreeSurface(loadedSurface);

	return ResourceManager::getInstanceResourceManager()->createGraphic(file, optimizedSurface);
}

Sint32 VideoManager::getGraphicID(const char* file){
	Sint32 id = ResourceManager::getInstanceResourceManager()->getGraphicID(file);
	if (id != -1)
		return id;

	return addGraphic(file);
}

Sint32 VideoManager::addTexture(const char* file){
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(file);
	if (loadedSurface == NULL)
		cout << "Unable to load image '" << file << "'! SDL_image Error: " << IMG_GetError() << endl;
	else{
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(gScreenRenderer, loadedSurface);
		if (newTexture == NULL){
			cout << "Unable to create texture from '" << file << "'! SDL Error: " << SDL_GetError() << endl;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return ResourceManager::getInstanceResourceManager()->createTexture(file, newTexture);
}

Sint32 VideoManager::addTextureManipulation(const char* file){
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(file);
	if (loadedSurface == NULL)
		cout << "Unable to load image '" << file << "'! SDL_image Error: " << IMG_GetError() << endl;
	else{
		//Convert surface to display format
		SDL_Surface* formattedSurface = SDL_ConvertSurface(loadedSurface, SDL_GetWindowSurface(gWindow)->format, NULL);
		if (formattedSurface == NULL){
			cout << "Unable to convert loaded surface to display format! SDL Error: " << SDL_GetError() << endl;
		}
		else{
			//Create blank stremeable texture
			newTexture = SDL_CreateTexture(gScreenRenderer, SDL_GetWindowPixelFormat(gWindow), SDL_TEXTUREACCESS_STREAMING, formattedSurface->w, formattedSurface->h);
			if (newTexture == NULL){
				cout << "Unable to create blank texture from '" << file << "'! SDL Error: " << SDL_GetError() << endl;
			}
			else{
				//Lock texture for manipulation
				SDL_LockTexture(newTexture, NULL, &mPixels, &mPitch);

				//Copy loaded/formatted surface pixels
				memcpy(mPixels, formattedSurface->pixels, formattedSurface->pitch * formattedSurface->h);

				//Unlock texture to update
				SDL_UnlockTexture(newTexture);
				mPixels = NULL;
			}

			//Get rid of old formatted surface
			SDL_FreeSurface(formattedSurface);
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return ResourceManager::getInstanceResourceManager()->createTexture(file, newTexture);
}

Sint32 VideoManager::getTextureID(const char* file, bool textureManipulation){
	if (file == NULL)
		return -1;

	int id = ResourceManager::getInstanceResourceManager()->getTextureID(file);
	if (id != -1)
		return id;

	if (textureManipulation)
		return addTextureManipulation(file);
	else
		return addTexture(file);
}


Uint32 VideoManager::getTime(){
	return SDL_GetTicks();
}

Uint32 VideoManager::getColor(Uint8 r, Uint8 g, Uint8 b){
	return SDL_MapRGB(SDL_GetWindowSurface(gWindow)->format, r, g, b);
}

Uint32 VideoManager::getColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a){
	return SDL_MapRGBA(SDL_GetWindowSurface(gWindow)->format, r, g, b, a);
}


bool VideoManager::lockTexture(int img){
	bool success = true;

	//Texture is already locked
	if (mPixels != NULL){
		cout << "Texture is already locked!\n";
		success = false;
	}
	//Lock texture
	else{
		SDL_Texture *mTexture = ResourceManager::getInstanceResourceManager()->getTextureByID(img);
		if (SDL_LockTexture(mTexture, NULL, &mPixels, &mPitch) != 0){
			cout << "Unable to lock texture! " << SDL_GetError() << endl;
			success = false;
		}
	}

	return success;
}

bool VideoManager::unlockTexture(int img){
	bool success = true;

	//Texture is not locket
	if (mPixels == NULL){
		cout << "Texture is not locked!\n";
		success = false;
	}
	//Unlock texture
	else{
		SDL_Texture *mTexture = ResourceManager::getInstanceResourceManager()->getTextureByID(img);
		SDL_UnlockTexture(mTexture);
		mPixels = NULL;
		mPitch = 0;
	}

	return success;
}

void* VideoManager::getPixelsVoid(){
	return mPixels;
}

int VideoManager::getPitch(){
	return mPitch;
}

Uint32* VideoManager::getPixels(){
	if (getPixelsVoid() != NULL){
		return (Uint32*)getPixelsVoid();
	}
	else{
		cout << "This texture is not locked!\n";

		return NULL;
	}
}

int VideoManager::getPixelCount(int height){
	//Get pixel data
	int pixelCount = NULL;
	if (getPixelsVoid() != NULL){
		Uint32* pixels = (Uint32*)getPixelsVoid();
		pixelCount = (getPitch() / 4) * height;
	}
	else{
		cout << "Some texture is not locked!\n";
	}

	return pixelCount;
}


void VideoManager::setCursorRelative(bool active){
	if (active)
		SDL_SetRelativeMouseMode(SDL_TRUE);
	else
		SDL_SetRelativeMouseMode(SDL_FALSE);
}


void VideoManager::renderGraphic(int img, int srcPosX, int srcPosY, int width, int height, int dstPosX, int dstPosY){
	if (img != -1){
		SDL_Rect rectAux, r;
		rectAux.x = srcPosX;
		rectAux.y = srcPosY;
		rectAux.w = width;
		rectAux.h = height;
		r.x = dstPosX;
		r.y = dstPosY;
		r.w = width;
		r.h = height;

		SDL_Surface *origin = ResourceManager::getInstanceResourceManager()->getGraphicByID(img);

		SDL_BlitSurface(origin, &rectAux, gScreenSurface, &r);
	}
}

void VideoManager::renderTexture(int img, int srcPosX, int srcPosY, int width, int height, float scaleX, float scaleY, int dstPosX, int dstPosY){
	if (img != -1){
		SDL_Rect rectAux, r;
		rectAux.x = srcPosX;
		rectAux.y = srcPosY;
		rectAux.w = width;
		rectAux.h = height;
		r.x = (int)(dstPosX * scaleX);
		r.y = (int)(dstPosY * scaleY);
		r.w = (int)(width * scaleX);
		r.h = (int)(height * scaleY);

		SDL_Texture *origin = ResourceManager::getInstanceResourceManager()->getTextureByID(img);

		SDL_RenderCopy(gScreenRenderer, origin, &rectAux, &r);
	}
}

void VideoManager::renderTexture(int img, int srcPosX, int srcPosY, int width, int height, float scaleX, float scaleY, int dstPosX, int dstPosY, double angle, int centerX, int centerY, SDL_RendererFlip flip){
	if (img != -1){
		SDL_Rect rectAux, r;
		rectAux.x = srcPosX;
		rectAux.y = srcPosY;
		rectAux.w = width;
		rectAux.h = height;
		r.x = (int)(dstPosX * scaleX);
		r.y = (int)(dstPosY * scaleY);
		r.w = (int)(width * scaleX);
		r.h = (int)(height * scaleY);

		SDL_Texture *origin = ResourceManager::getInstanceResourceManager()->getTextureByID(img);

		SDL_Point center;
		center.x = centerX;
		center.y = centerY;

		SDL_RenderCopyEx(gScreenRenderer, origin, &rectAux, &r, angle, &center, flip);
	}
}


void VideoManager::clearScreen(unsigned int color_key){
	if (!texture)
		SDL_FillRect(gScreenSurface, NULL, color_key);
	else{
		//Clear screen
		SDL_SetRenderDrawColor(gScreenRenderer, color_key, color_key, color_key, color_key);
		SDL_RenderClear(gScreenRenderer);
	}
}

void VideoManager::updateScreen(){
	if (!texture)
		SDL_UpdateWindowSurface(gWindow);
	else{
		//Update screen
		SDL_RenderPresent(gScreenRenderer);
	}
}


void VideoManager::updateTime() {
	if (lastTime != -1) {
		int currentTime = getTime();
		deltaTime = (float)(currentTime - lastTime);
		if (deltaTime < msFrame) {
			waitTime(msFrame - deltaTime);
			deltaTime = msFrame;
		}
		lastTime = currentTime;
	}
}

void VideoManager::waitTime(int ms){
	deltaTime = 0;
	lastTime = -1;
	SDL_Delay(ms);
	lastTime = getTime();
}


void VideoManager::close(){
	SDL_FreeSurface(gScreenSurface);
	SDL_DestroyWindow(gWindow);
	SDL_Quit();
}
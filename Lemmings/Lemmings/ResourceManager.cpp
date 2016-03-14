#include "ResourceManager.h"

#include "SDL_image.h"
#include "SDL_mixer.h"
#include "Utils.h"

ResourceManager* ResourceManager::pInstance = NULL;

ResourceManager::ResourceManager()
{
	mFirstFreeSlot = -1;
	mFirstFreeSlotAudio = -1;
}

ResourceManager::~ResourceManager()
{
}

ResourceManager* ResourceManager::getInstanceResourceManager(){
	if (pInstance == NULL){

		pInstance = new ResourceManager();
	}

	return pInstance;
}

void ResourceManager::removeGraphic(const char* file){
	Sint32 pos = -1;
	for (map<string, Sint32>::iterator it = mIDMap.begin(); it != mIDMap.end(); it++){
		if (it->first == file){
			pos = it->second;
			mIDMap.erase(it);
			break;
		}
	}
	if (pos != -1){
		SDL_FreeSurface(mGraphicsVector[pos]);
		mGraphicsVector[pos] = NULL;
		if (pos < mFirstFreeSlot)
			mFirstFreeSlot = pos;
	}
}

void ResourceManager::removeGraphic(Sint32 ID){
	Sint32 pos = -1;
	for (map<string, Sint32>::iterator it = mIDMap.begin(); it != mIDMap.end(); it++){
		if (it->second == ID){
			pos = it->second;
			mIDMap.erase(it);
			break;
		}
	}
	if (pos != -1){
		SDL_FreeSurface(mGraphicsVector[pos]);
		mGraphicsVector[pos] = NULL;
		if (pos < mFirstFreeSlot)
			mFirstFreeSlot = pos;
	}
}

Sint32 ResourceManager::getGraphicID(const char* file, SDL_Texture* newTexture){
	for (map<string, Sint32>::iterator it = mIDMap.begin(); it != mIDMap.end(); it++){
		if (it->first == file)
			return it->second;
	}
	return addGraphic(file, newTexture);

}

string ResourceManager::getGraphicPathByID(Sint32 ID){
	for (map<string, Sint32>::iterator it = mIDMap.begin(); it != mIDMap.end(); it++){
		if (it->second == ID)
			return (string)it->first;
	}
	return "Error";
}

void ResourceManager::getGraphicSize(Sint32 img, int &width, int &height){
	width = mGraphicsVector[img]->w;
	height = mGraphicsVector[img]->h;

}

int ResourceManager::getGraphicWidth(Sint32 img){
	return mGraphicsVector[img]->w;

}

int ResourceManager::getGraphicHeight(Sint32 img){
	return mGraphicsVector[img]->h;


}

void ResourceManager::getColorGraphic(Sint32 ID, Uint8* R, Uint8* G, Uint8* B){
	SDL_GetSurfaceColorMod(mGraphicsVector[ID], R, G, B);
}

SDL_Texture* ResourceManager::getGraphicByID(Sint32 ID){
	return mTextureVector[ID];
}

void ResourceManager::setAlphaGraphic(Sint32 ID, Uint8 alpha_value){
	SDL_SetSurfaceAlphaMod(mGraphicsVector[ID], alpha_value);
}

void ResourceManager::setColorGraphic(Sint32 ID, Uint8 R, Uint8 G, Uint8 B){
	SDL_SetSurfaceColorMod(mGraphicsVector[ID], R, G, B);
}

void ResourceManager::printLoadedGraphics(){
	for (map<string, Sint32>::iterator it = mIDMap.begin(); it != mIDMap.end(); it++){
		cout << it->first << endl;
	}

}

Sint32 ResourceManager::createGraphic(const char* name, SDL_Texture* newTexture){

	return addGraphic(name, newTexture);

}

Sint32 ResourceManager::createGraphic(const char* name, SDL_Texture* newTexture, Uint16 width, Uint16 height){

	Sint32 pos = addGraphic(name, newTexture);
	if (pos != -1){
		mGraphicsVector[pos]->h = height;
		mGraphicsVector[pos]->w = width;
	}
	return pos;
}



/*
Sint32 ResourceManager::addGraphic(const char* file){
	//The final optimized image
	SDL_Surface* optimizedSurface = NULL;
	VideoManager* sVideo = VideoManager::getInstanceVideo();
	SDL_Surface* surfaceFormatInfo = sVideo->gScreenSurface;
	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(file);
	if (loadedSurface == NULL)
	{
		cout << "Unable to load image " << file << "! SDL_image Error: " << IMG_GetError() << endl;
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
	surfaceFormatInfo->format->Amask = (Uint8) Old_Amask;
	surfaceFormatInfo->format->Aloss = (Uint8) Old_Aloss;
	surfaceFormatInfo->format->Ashift =(Uint8) Old_Ashift;
	if (optimizedSurface == NULL)
	{
		cout << "Unable to optimize image " << file << "! SDL Error: " << SDL_GetError() << endl;
		return -1;
	}

	//Get rid of old loaded surface
	SDL_FreeSurface(loadedSurface);
	Sint32 pos = -1;
	if (mFirstFreeSlot != -1){
		mGraphicsVector[mFirstFreeSlot] = optimizedSurface;
		mIDMap.emplace(file, mFirstFreeSlot);
		pos = mFirstFreeSlot;
		updateFirstFreeSlotGraphic();
	}
	else{
		mGraphicsVector.push_back(optimizedSurface);
		pos = mGraphicsVector.size() - 1;
		mIDMap.emplace(file, pos);
	}
	return pos;
}*/



Sint32 ResourceManager::addGraphic(const char* file, SDL_Texture* newTexture){	
	Sint32 pos = -1;
	if (mFirstFreeSlot != -1){
		mTextureVector[mFirstFreeSlot] = newTexture;
		mIDMap.emplace(file, mFirstFreeSlot);
		pos = mFirstFreeSlot;
		updateFirstFreeSlotGraphic();
	}
	else{
		mTextureVector.push_back(newTexture);
		pos = mTextureVector.size() - 1;
		mIDMap.emplace(file, pos);
	}
	return pos;
}


SDL_Surface* ResourceManager::getGraphic(const char* file, SDL_Texture* newTexture){
	map<string, Sint32>::iterator it = mIDMap.find(file);

	if (it != mIDMap.end()){
		Sint32 pos = it->second;
		return mGraphicsVector[pos];
	}
	return mGraphicsVector[addGraphic(file, newTexture)];


}

Sint32 ResourceManager::searchGraphic(SDL_Surface* img){
	for (unsigned int i = 0; i < mGraphicsVector.size(); i++){
		if (mGraphicsVector[i] == img){
			return i;
		}
	}
	return -1;
}

Uint32 ResourceManager::updateFirstFreeSlotGraphic(){
	mFirstFreeSlot = -1;
	for (unsigned int i = 0; i < mGraphicsVector.size(); i++){
		if (mGraphicsVector[i] == NULL){
			mFirstFreeSlot = i;
			break;
		}
	}
	return mFirstFreeSlot;
}




//Comprueba si el pixel no tiene mucha transparencia en la posision X Y de la surface ID
bool  ResourceManager::GetAlphaXY(int ID, int x, int y)
{
	SDL_Surface* surface = mGraphicsVector[ID];

	if (x >= 0 && y >= 0 && x < surface->w && y < surface->h){
		if (SDL_MUSTLOCK(surface))
		{
			//Lock the surface
			SDL_LockSurface(surface);
		}
		int bpp = surface->format->BytesPerPixel;
		Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
		Uint32 pixelColor = 0;

		switch (bpp)
		{
		case 1:
			pixelColor = *p;
			break;
		case 2:
			pixelColor = *(Uint16*)p;
			break;
		case 3:
			if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
				pixelColor = p[0] << 16 | p[1] << 8 | p[2];
			else
				pixelColor = p[0] | p[1] << 8 | p[2] << 16;
			break;
		case 4:
			pixelColor = *(Uint32*)p;
			break;
		}

		Uint8 red, green, blue, alpha;
		SDL_GetRGBA(pixelColor, surface->format, &red, &green, &blue, &alpha);
		if (SDL_MUSTLOCK(surface))
		{
			SDL_UnlockSurface(surface);
		}
		return alpha > 220;
	}
	return false;
}

//Modifica el alpha de algunos pixels para crear un efecto de explosion
void ResourceManager::EditSurfaceMuroBullet(int ID, int x, int y)
{
	SDL_Surface* surface = mGraphicsVector[ID];
	//If the surface must be locked
	if (SDL_MUSTLOCK(surface))
	{
		//Lock the surface
		SDL_LockSurface(surface);
	}

	//Modificar el alpha de los pixels
	Uint32 pixel = SDL_MapRGBA(surface->format, 0, 0, 0, 0);

	//Crea una especie de rombo curvado, que se va desvaneciendo en funcion de los random
	for (int i = -10; i < 10; i++){
		for (int j = -20; j < 20; j++){

			if (x + i >= 0 && y + j >= 0 && x + i < surface->w && y + j < surface->h){
				if (abs(i * j) < 25 || (rand() % 2 == 0 && abs(i * j) < 100) || (abs(i * j) < 150 && rand() % 8 == 0)){

					put_pixel32(surface, x + i, y + j, pixel);
				}
			}
		}
	}


	//Unlock surface
	if (SDL_MUSTLOCK(surface))
	{
		SDL_UnlockSurface(surface);
	}
}



//Modifica el alpha de algunos pixels para crear un efecto de explosion
void ResourceManager::EditSurfaceMuroEnemy(int ID, int x, int y, int w, int h)
{
	SDL_Surface* surface = mGraphicsVector[ID];
	//If the surface must be locked
	if (SDL_MUSTLOCK(surface))
	{
		//Lock the surface
		SDL_LockSurface(surface);
	}


	//Modificar el alpha de los pixels
	Uint32 pixel = SDL_MapRGBA(surface->format, 0, 0, 0, 0);
	for (int i = 0; i < w ; i++){
		for (int j = 0; j < h; j++){
			if (x + i >= 0 && y + j >= 0 && x + i < surface->w && y + j < surface->h)
				put_pixel32(surface, x + i, y + j, pixel);
			
		}
	}

	

	//Unlock surface
	if (SDL_MUSTLOCK(surface))
	{
		SDL_UnlockSurface(surface);
	}
}



void ResourceManager::put_pixel32(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
	//Convert the pixels to 32 bit
	Uint32 *pixels = (Uint32 *)surface->pixels;

	//Set the pixel
	pixels[(y * surface->w) + x] = pixel;
}



Sint32 ResourceManager::getAudioID(const char* file){
	for (map<string, Sint32>::iterator it = mIDMap.begin(); it != mIDMap.end(); it++){
		if (it->first == file)
			return it->second;
	}
	return addAudio(file);
}


Sint32 ResourceManager::addAudio(const char* file){
	Mix_Chunk* sound = Mix_LoadWAV(file);
	if (sound == NULL)
	{
		printf("Failed to load sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		return -1;
	}
	Sint32 pos = -1;
	if (mFirstFreeSlotAudio != -1){
		mAudioVector[mFirstFreeSlotAudio] = sound ;
		mIDMap.emplace(file, mFirstFreeSlotAudio);
		pos = mFirstFreeSlot;
		updateFirstFreeSlotAudio();
	}
	else{
		mAudioVector.push_back(sound);
		pos = mAudioVector.size() - 1;
		mIDMap.emplace(file, pos);
	}
	return pos;
}
Uint32 ResourceManager::updateFirstFreeSlotAudio(){
	mFirstFreeSlotAudio = -1;
	for (unsigned int i = 0; i < mAudioVector.size(); i++){
		if (mAudioVector[i] == NULL){
			mFirstFreeSlotAudio = i;
			break;
		}
	}
	return mFirstFreeSlotAudio;
}


void ResourceManager::removeAudio(Sint32 ID){
	Mix_FreeChunk(mAudioVector[ID]);
	mAudioVector[ID] = NULL;
	if (ID < mFirstFreeSlotAudio)
		mFirstFreeSlotAudio = ID;
	
}


Mix_Chunk* ResourceManager::getAudioByID(Sint32 ID){
	return mAudioVector[ID];
}

#include "AudioManager.h"
#include "ResourceManager.h"
#include "SDL_mixer.h"
#include <iostream>

AudioManager* AudioManager::aInstance = NULL;

AudioManager::AudioManager(){
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << endl;

	Mix_AllocateChannels(128);
}


AudioManager::~AudioManager(){
}


AudioManager* AudioManager::getInstanceAudio(){
	if (aInstance == NULL)
		aInstance = new AudioManager();

	return aInstance;
}


Sint32 AudioManager::addAudio(const char* file){
	Mix_Chunk* sound = Mix_LoadWAV(file);
	if (sound == NULL){
		cout << "Failed to load sound effect! SDL_mixer Error:" << Mix_GetError() << endl;
		return -1;
	}
	return ResourceManager::getInstanceResourceManager()->addAudio(file, sound);

}

Sint32 AudioManager::getAudioID(const char* file){
	if (file == NULL)
		return -1;

	int id = ResourceManager::getInstanceResourceManager()->getAudioID(file);
	if (id != -1)
		return id;

	return addAudio(file);
}


/*void AudioManager::playMusic(int audio){
	Mix_Music *music = ResourceManager::getInstanceResourceManager()->getAudioByID(audio);
	Mix_PlayMusic(music, 0);
}*/

/*void AudioManager::playMusic(int audio, int loop){
Mix_Music *music = ResourceManager::getInstanceResourceManager()->getAudioByID(audio);
Mix_PlayMusic(music, loop);
}*/

void AudioManager::playSound(int audio){
	Mix_Chunk *sound = ResourceManager::getInstanceResourceManager()->getAudioByID(audio);
	Mix_PlayChannel(1, sound, 0);
}

void AudioManager::playSound(int audio, int loop){
	Mix_Chunk *sound = ResourceManager::getInstanceResourceManager()->getAudioByID(audio);
	Mix_PlayChannel(1, sound, loop);
}


void AudioManager::pauseMusic(){
	Mix_PauseMusic();
}

void AudioManager::pauseSound(){
	Mix_Pause(-1);
}


bool AudioManager::isMusicPaused(){
	return Mix_PausedMusic();
}

bool AudioManager::isSoundPaused(){
	return Mix_Paused(-1);
}


void AudioManager::resumeMusic(){
	Mix_ResumeMusic();
}

void AudioManager::resumeSound(){
	Mix_Resume(-1);
}
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

void AudioManager::playAudio(int audio){
	Mix_Chunk *sound = ResourceManager::getInstanceResourceManager()->getAudioByID(audio);
	Mix_PlayChannel(1, sound, 0);
}


void AudioManager::PauseAudio(){
	Mix_Pause(-1);
}

bool AudioManager::isAudioPaused(){
	return Mix_Paused(-1);
}


void AudioManager::ResumeAudio(){
	Mix_Resume(-1);
}
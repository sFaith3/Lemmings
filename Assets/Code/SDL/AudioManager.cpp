#include "AudioManager.h"
#include "ResourceManager.h"
#include <iostream>

AudioManager *AudioManager::aInstance = NULL;

AudioManager::AudioManager()
{
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << endl;

	Mix_AllocateChannels(16);

	setVolumeMusic(Volume);
	setVolumeSound(Volume);
}

AudioManager::~AudioManager()
{
}

AudioManager *AudioManager::getInstanceAudio()
{
	if (aInstance == NULL)
		aInstance = new AudioManager();

	return aInstance;
}

Sint32 AudioManager::addMusic(const char *file)
{
	Mix_Music *music = Mix_LoadMUS(file);
	if (music == NULL)
	{
		cout << "Failed to load music! SDL_music Error:" << Mix_GetError() << endl;
		return -1;
	}
	return ResourceManager::getInstanceResourceManager()->addMusic(file, music);
}

Sint32 AudioManager::getMusicID(const char *file)
{
	if (file == NULL)
		return -1;

	int id = ResourceManager::getInstanceResourceManager()->getMusicID(file);
	if (id != -1)
		return id;

	return addMusic(file);
}

Sint32 AudioManager::addSound(const char *file)
{
	Mix_Chunk *sound = Mix_LoadWAV(file);
	if (sound == NULL)
	{
		cout << "Failed to load sound effect! SDL_mixer Error:" << Mix_GetError() << endl;
		return -1;
	}
	return ResourceManager::getInstanceResourceManager()->addSound(file, sound);
}

Sint32 AudioManager::getSoundID(const char *file)
{
	if (file == NULL)
		return -1;

	int id = ResourceManager::getInstanceResourceManager()->getSoundID(file);
	if (id != -1)
		return id;

	return addSound(file);
}

void AudioManager::playMusic(int audio)
{
	Mix_Music *music = ResourceManager::getInstanceResourceManager()->getMusicByID(audio);
	Mix_PlayMusic(music, 0);
}

void AudioManager::playMusic(int audio, int loop)
{
	Mix_Music *music = ResourceManager::getInstanceResourceManager()->getMusicByID(audio);
	Mix_PlayMusic(music, loop);
}

void AudioManager::playSound(int audio)
{
	Mix_Chunk *sound = ResourceManager::getInstanceResourceManager()->getSoundByID(audio);
	Mix_PlayChannel(-1, sound, 0);
}

void AudioManager::playSound(int audio, int loop)
{
	Mix_Chunk *sound = ResourceManager::getInstanceResourceManager()->getSoundByID(audio);
	Mix_PlayChannel(-1, sound, loop);
}

void AudioManager::pauseMusic()
{
	Mix_PauseMusic();
}

void AudioManager::pauseSound()
{
	Mix_Pause(-1);
}

bool AudioManager::isMusicPaused()
{
	return Mix_PausedMusic();
}

bool AudioManager::isSoundPaused()
{
	return Mix_Paused(-1);
}

void AudioManager::resumeMusic()
{
	Mix_ResumeMusic();
}

void AudioManager::resumeSound()
{
	Mix_Resume(-1);
}

void AudioManager::setVolumeMusic(int vol)
{
	Mix_VolumeMusic(vol);
}

void AudioManager::setVolumeSound(int vol)
{
	Mix_Volume(-1, vol);
}

void AudioManager::stopMusic()
{
	Mix_HaltMusic();
}

void AudioManager::stopSounds()
{
	Mix_HaltChannel(-1);
}
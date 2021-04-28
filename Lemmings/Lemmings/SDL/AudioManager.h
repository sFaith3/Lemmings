#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include "SDL.h"

class AudioManager
{
private:
	AudioManager();

	static AudioManager* aInstance; /*!<	Singleton instance*/

public:
	~AudioManager();

	//! Gets Singleton instance.
	static AudioManager* getInstanceAudio();

	Sint32 addMusic(const char* file);
	Sint32 getMusicID(const char* file);
	Sint32 addSound(const char* file);
	Sint32 getSoundID(const char* file);

	void playMusic(int audio);
	void playMusic(int audio, int loop);
	void playSound(int audio);
	void playSound(int audio, int loop);

	void pauseMusic();
	void pauseSound();
	bool isMusicPaused();
	bool isSoundPaused();

	void resumeMusic();
	void resumeSound();

	void setVolumeMusic(int vol);
	void setVolumeSound(int vol);

	void stopMusic();
	void stopSounds();
};

#endif
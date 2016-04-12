#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include "SDL.h"

class AudioManager
{
private:
	AudioManager();

	static AudioManager* aInstance;

public:
	~AudioManager();

	static AudioManager* getInstanceAudio();

	void playAudio(int audio);
	void PauseAudio();
	void ResumeAudio();
	bool isAudioPaused();
};

#endif
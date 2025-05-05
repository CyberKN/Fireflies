#pragma once

#ifndef __IGFEB10_IG500_SOUNDMANAGER_H__
#define __IGFEB10_IG500_SOUNDMANAGER_H__

// Library Includes
#include <vector>
#include <fmod.h>
#include <fmod.hpp>

// Local Includes
#include "defines.h"

// Types

// Constants
typedef enum _ESOUNDCHANNEL
{
	SOUNDCHANNEL_SOUNDEFFECTS,
	SOUNDCHANNEL_MUSIC,

	//Must be last on list
	SOUNDCHANNEL_ALL
} ESoundChannel;

// Prototypes


class CSoundManager
{
    // Member Functions
public:
	CSoundManager();
	virtual ~CSoundManager();

	virtual bool Initialise();
	virtual void Process();

	virtual int LoadSoundFromFile(const char* _kpcFile);

	virtual bool SetPaused(bool _bResult);

	virtual bool PlaySound(unsigned int _uiSoundID, bool _bLoop = false, bool _bIsMusic = false);
	virtual bool StopSound(unsigned int _uiSoundID);
	virtual bool IsSoundPlaying(unsigned int _uiSoundID);

	virtual void SetSFXVolume(float _fVolume);
	virtual void SetMusicVolume(float _fVolume);

	virtual void ReleaseSound(unsigned int _uiSoundID);
	virtual void ReleaseAll();

protected:
	virtual bool GetSoundExists(unsigned int _uiSoundID) const;

private:

    // Member Variables
public:
protected:
	FMOD::System* m_pSystem;

	//Because fmod fails to hold its own volumes
	float m_fSFXVolume;
	float m_fMusicVolume;
	std::vector<FMOD::Sound*> m_vecSoundHandles;
	std::vector<FMOD::Channel*> m_vecSoundChannels;

private:
};

#endif // __IGFEB10_IG500_SOUNDMANAGER_H__


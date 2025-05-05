// Library Includes

// Local Includes
#include "iniparser.h"

// This Include
#include "soundManager.h"

// Static Variables

// Static Function Prototypes

// Implementation

/**
* @DESC		sound manager constructor
* @AUTHOR	Josh van den Heever
**/
CSoundManager::CSoundManager()
: m_pSystem(0)
, m_fSFXVolume(1.0f)
, m_fMusicVolume(1.0f)
{
}

/**
* @DESC		sound manager destructor
* @AUTHOR	Josh van den Heever
**/
CSoundManager::~CSoundManager()
{
	ReleaseAll();

	if (m_pSystem)
	{
		m_pSystem->release();
	}
}

/**
* @DESC		Initialises the sound manager using default values
* @AUTHOR	Josh van den Heever
* @RETURN	result of the initialisation
**/
bool CSoundManager::Initialise()
{
	bool bResult = true;

	FMOD_RESULT hr = FMOD::System_Create(&m_pSystem);
	if (hr != FMOD_OK)
	{
		//oh no
		bResult = false;
	}

	if (bResult)
	{
		hr = m_pSystem->init(150, FMOD_INIT_NORMAL, 0);	// Initialize FMOD.
		if (hr != FMOD_OK)
		{
			bResult = false;
		}

		m_pSystem->setSpeakerMode(FMOD_SPEAKERMODE_STEREO);
		m_pSystem->setSoftwareChannels(100);
		m_pSystem->setHardwareChannels(32, 64, 32, 64);
	}

	CINIParser* pParser = new CINIParser();

	if (pParser->LoadIniFile("Settings.ini"))
	{
		int iMusicVolume = 0;
		int iSoundFXVolume = 0;

		//Loading the music volume...
		pParser->GetIntValue("settings", "MusicVolume", iMusicVolume);
		//Loading the SFX volume...
		pParser->GetIntValue("settings", "SFXVolume", iSoundFXVolume);

		float fSFXVolume = static_cast<float>(iSoundFXVolume) / 10.0f;
		float fMusicVolume = static_cast<float>(iMusicVolume) / 10.0f;

		SetSFXVolume(fSFXVolume);
		SetMusicVolume(fMusicVolume);
	}

	delete pParser;
	pParser = 0;

	

	return (bResult);
}

/**
* @DESC		Process function updates the sound engine every frame
* @AUTHOR	Josh van den Heever
**/
void CSoundManager::Process()
{
	m_pSystem->update();
}

/**
* @DESC		Loads a sound from the file and stores it in the sound vector
* @AUTHOR	Josh van den Heever
* @PARAM _kpcFile	The filename of the desired sound file to load
* @RETURN	The ID of the newly loaded sound, -1 if invalid
**/
int CSoundManager::LoadSoundFromFile(const char* _kpcFile)
{
	int uiResult = -1;

	FMOD::Sound *sound;
	FMOD_RESULT result = m_pSystem->createSound(_kpcFile, FMOD_DEFAULT, 0, &sound);		// FMOD_DEFAULT uses the defaults.  These are the same as FMOD_LOOP_OFF | FMOD_2D | FMOD_HARDWARE.
	if (result == FMOD_OK)
	{
		uiResult = static_cast<int>(m_vecSoundHandles.size());
		m_vecSoundHandles.push_back(sound);
		m_vecSoundChannels.push_back(0);
	}

	return (uiResult);
}

/**
* @DESC		Sets the paused state of the sound channels
* @AUTHOR	Josh van den Heever
* @PARAM _bResult	the desired state of the pause to set the channels to
* @RETURN	the result of the pausing
**/
bool CSoundManager::SetPaused(bool _bResult)
{
	bool bResult = false;

	for(unsigned int i = 0; i < m_vecSoundChannels.size(); ++i)
	{
		m_vecSoundChannels[i]->setPaused(_bResult);
	}

	return (bResult);
}

/**
* @DESC		Plays the sound with the specified ID
* @AUTHOR	Josh van den Heever
* @PARAM _uiSoundID	The ID of the sound you wish to play
* @PARAM _bLoop		Whether the sound should loop or not after hitting a loop point or end of file
* @PARAM _bIsMusic	if the sound with specified ID is music (determines the channel the sound will be played on
* @RETURN	the result of the sound playing
**/
bool CSoundManager::PlaySound(unsigned int _uiSoundID, bool _bLoop, bool _bIsMusic)
{
	bool bResult = false;

	FMOD::Sound* pSound = 0;

	if (GetSoundExists(_uiSoundID))
	{
		pSound = m_vecSoundHandles[_uiSoundID];

		if (_bLoop)
		{	pSound->setMode(FMOD_LOOP_NORMAL);
		}
		else
		{
			pSound->setMode(FMOD_LOOP_OFF);
		}

		if (_bIsMusic)
		{
			FMOD_RESULT result = m_pSystem->playSound(FMOD_CHANNEL_FREE, pSound, false, &m_vecSoundChannels[_uiSoundID]);
			m_vecSoundChannels[_uiSoundID]->setVolume(m_fMusicVolume);
			if (result == FMOD_OK)
			{
				bResult = true;
			}
		}
		else
		{
			FMOD_RESULT result = m_pSystem->playSound(FMOD_CHANNEL_FREE, pSound, false, &m_vecSoundChannels[_uiSoundID]);
			m_vecSoundChannels[_uiSoundID]->setVolume(m_fSFXVolume);
			if (result == FMOD_OK)
			{
				bResult = true;
			}
		}
	}

	return (bResult);
}

/**
* @DESC		Checks if sound is playing
* @AUTHOR	Kurt Nadworny
**/
bool CSoundManager::IsSoundPlaying(unsigned int _uiSoundID)
{
	bool bResult = false;

	m_vecSoundChannels[_uiSoundID]->isPlaying(&bResult);

	return(bResult);
}


/**
* @DESC		Sets the volume of the sound effects channel
* @AUTHOR	Josh van den Heever
* @PARAM _fVolume	The desired sound level of the SFX channel (1.0 is 100%)
**/
bool CSoundManager::StopSound(unsigned int _uiSoundID)
{
	bool bResult = false;


	if (m_vecSoundChannels[_uiSoundID])
	{
		if (m_vecSoundChannels[_uiSoundID]->stop() == FMOD_OK)
		{
			bResult = true;
		}
	}
		


	return (bResult);
}

/**
* @DESC		Sets the volume of the sound effects channel
* @AUTHOR	Josh van den Heever
* @PARAM _fVolume	The desired sound level of the SFX channel (1.0 is 100%)
**/
void CSoundManager::SetSFXVolume(float _fVolume)
{
	m_fSFXVolume = _fVolume;
}

/**
* @DESC		Sets the volume of the music channel
* @AUTHOR	Josh van den Heever
* @PARAM _fVolume	The desired sound level of the music channel (1.0 is 100%)
**/
void CSoundManager::SetMusicVolume(float _fVolume)
{
	m_fMusicVolume = _fVolume;
}

/**
* @DESC		Releases the sound with the specified ID from memory
* @AUTHOR	Josh van den Heever
* @PARAM _uiSoundID		The ID of the sound you wish to release from memory
**/
void CSoundManager::ReleaseSound(unsigned int _uiSoundID)
{
	if (GetSoundExists(_uiSoundID))
	{
		m_vecSoundHandles[_uiSoundID]->release();
		m_vecSoundHandles[_uiSoundID] = 0;
		m_vecSoundChannels[_uiSoundID] = 0;
	}
}

/**
* @DESC		Releases all sounds from memory
* @AUTHOR	Josh van den Heever
**/
void CSoundManager::ReleaseAll()
{
	for (unsigned int i = 0; i < m_vecSoundHandles.size(); ++i)
	{
		m_vecSoundHandles[i]->release();
		m_vecSoundHandles[i] = 0;
		m_vecSoundChannels[i] = 0;
	}

	m_vecSoundHandles.clear();
	m_vecSoundChannels.clear();
}

/**
* @DESC		Returns whether or not a sound with the specified ID exists
* @AUTHOR	Josh van den Heever
* @PARAM _uiSoundID		The ID of the sound you wish to check existance of
* @RETURN	true if the sound exists in memory
**/
bool CSoundManager::GetSoundExists(unsigned int _uiSoundID) const
{
	bool bResult = false;

	if (_uiSoundID < m_vecSoundHandles.size() && _uiSoundID >= 0)
	{
		bResult = (m_vecSoundHandles[_uiSoundID] != 0);
	}

	return (bResult);
}
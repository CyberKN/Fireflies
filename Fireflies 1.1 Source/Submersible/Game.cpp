// Library Includes
#include <d3dx9.h>
#include <d3d9.h>

// Local Includes
#include "Clock.h"

#include "Menu.h"

// This include
#include "Game.h"

// Constants

// Static Variables

CGame* CGame::s_pGame = 0;

// Static Function Prototypes

// Implementation

CGame::CGame()
:m_pClock(0)
,m_hApplicationInstance(0)
,m_hMainWindow(0)
,m_fDeltaTick(0)
,m_iWindowOffsetX(0)
,m_iWindowOffsetY(0)
,m_iWindowHeight(0)
,m_iWindowWidth(0)
,m_bHasFocus(true)
,m_pSoundManager(0)
,m_pSpriteManager(0)
,m_pTextManager(0)
,m_pSession(0)
,m_pEditor(0)
,m_pMenu(0)
,m_iSleepTime(0)
,m_eGameState(GAMESTATE_MENU)
,m_eLastState(GAMESTATE_MENU)
,m_strLevelName("")
{

}

CGame::~CGame()
{	
	if(m_pSession)
	{
		delete m_pSession;
		m_pSession = 0;
	}

	if(m_pEditor)
	{
		delete m_pEditor;
		m_pEditor = 0;
	}

	if(m_pMenu)
	{
		delete m_pMenu;
		m_pMenu = 0;
	}

	if(m_pSoundManager)
	{
		m_pSoundManager->ReleaseAll();
		delete m_pSoundManager;
		m_pSoundManager = 0;
	}

	if(m_pSpriteManager)
	{
		delete m_pSpriteManager;
		m_pSpriteManager = 0;
	}

	if(m_pTextManager)
	{
		delete m_pTextManager;
		m_pTextManager = 0;
	}


	for(unsigned int i = 0 ; i < m_XboxVec.size(); ++i)
	{
		delete m_XboxVec[i];
		m_XboxVec[i] = 0;
	}

	delete m_pClock;
	m_pClock = 0;

	m_DirectX3DRenderer.Shutdown();

}

/**
* Game Initialisation !
* 
* @Author Kurt
* @param _hInstance			instance to set the application to
* @param _hWnd				handle to the main window
* @param _iWidth			width of the game window / screen
* @param _iHeight			height of the game window / screen
*
* @return True
*/
bool CGame::Initialise(HINSTANCE _hInstance, HWND _hWnd, int _iWidth, int _iHeight)
{
	
	m_hApplicationInstance = _hInstance;
	m_hMainWindow = _hWnd;

	m_iWindowHeight = _iHeight;
	m_iWindowWidth = _iWidth;

	m_pClock = new CClock();
	m_pClock->Initialise();
	m_pClock->Process();

	m_Keyboard.Initialise();
	m_Mouse.Initialise();

	for(int i = 0; i < 4; ++i)
	{

		m_XboxVec.push_back(new CXInput);
		m_XboxVec[i]->dwUserIndex = i;

		m_XboxVec[i]->Initialise();
	}

	m_DirectX3DRenderer.Initialise(_iWidth, _iHeight, m_hMainWindow, false);

	m_pSoundManager = new CSoundManager;
	m_pSoundManager->Initialise();
	InitSounds();

	m_pSpriteManager = new CSpriteManager;
	m_pSpriteManager->Initialise();

	m_pTextManager = new CTextManager;
	m_pTextManager->Initialise();

	m_pMenu = new CMenu;
	m_pMenu->Initialise(MENU_MAIN);

	PlayGameSound(SOUNDID_GameMusic);

	/*m_pEditor = new CEditor;
	m_pEditor->Initialise(m_pSpriteManager);*/

//	m_pSession = new CSession;
//	m_pSession->Initialise(m_pSpriteManager);
	



	return(true);
}

/**
* Drawing process for entire game !
* 
* @Author Kurt
*/
void CGame::Draw()
{
	m_DirectX3DRenderer.Clear(0,0,0);
	m_DirectX3DRenderer.StartRender(0,0,0);


	for(int k = 0; k < static_cast<int>(m_DirectX3DRenderer.vViewport.size()); ++k)
	{
		if(m_pMenu)
		{
			m_pMenu->Draw();
		}
		else if(m_pSession)
		{
			m_pSession->Draw();
		}
		else if(m_pEditor)
		{
			m_pEditor->Draw();
		}
	}

	
	m_DirectX3DRenderer.EndRender();
	
}


void CGame::Process(float _fDeltaTick)
{
	m_fDeltaTick = _fDeltaTick;

	m_pSoundManager->Process();

	if(!m_pSoundManager->IsSoundPlaying(m_vecSounds[(int)SOUNDID_GameMusic]))
	{
		PlayGameSound(SOUNDID_GameMusic);
	}

	
	if(m_eLastState != m_eGameState)
	{
		SwapState();
	}

	if(m_pMenu)
	{
		m_pMenu->Process(_fDeltaTick);
	}
	else if(m_pSession)
	{
		m_pSession->Process(_fDeltaTick);
	}
	else if(m_pEditor)
	{
		m_pEditor->Process();
	}

}

void CGame::ExecuteOneFrame()
{
	float fDT = m_pClock->GetDeltaTick();
	
	if(fDT > 0.02f)
	{
		m_iSleepTime -= 5;
	}
	else if(fDT < 0.016f)
	{
		m_iSleepTime += 5;
	}

	if(m_iSleepTime < 0)
	{
		m_iSleepTime = 0;
	}
			
		
	m_Mouse.Process();
		
	m_Keyboard.Process();

	for(unsigned int i = 0; i < m_XboxVec.size(); ++i)
	{
		m_XboxVec[i]->Process();
	}


	if(fDT < 0.1f)
	{
		Process(fDT*1);
		/*for(int i = 0; i < 4; ++i)
		{
			Process(fDT*0.25f);
		}*/
	}
	else
	{
		Process(0.1f);
	}

	Draw();


#ifdef _DEBUG

	float fFramesPerSecond = 1.0f / fDT;
	SetWindowTextA(m_hMainWindow, FloatToString(fFramesPerSecond).c_str());

#endif // _DEBUG

	m_pClock->Process();
	
	
	Sleep(m_iSleepTime);
}

/**
* function to return the instance of the game to the caller.
* 
* @Author Kurt
*
* @return instance of current game running
*/
CGame&
CGame::GetInstance()
{
	if(s_pGame == 0)
	{
		s_pGame = new CGame();
	}

	return(*s_pGame);
}

/**
* Destroys the game instance. only call this at the end of the game.
* 
* @Author Kurt
*/
void CGame::DestroyInstance()
{
	delete s_pGame;
	s_pGame = 0;
}

/**
* Call to get the application instance
* 
* @Author Kurt
*
* @return instance of the application
*/
HINSTANCE CGame::GetAppInstance()
{
	return(m_hApplicationInstance);
}

/**
* Returns the main window
* 
* @Author Kurt
*
* @return handle to the main window
*/
HWND CGame::GetWindow() 
{
	return(m_hMainWindow);
}

/**
* to get the viewports X value
* 
* @Author Kurt
*
* @return viewports X value
*/
int CGame::GetViewportX() const
{
	return(m_iViewportX);
}

/**
* Get Viewports Y value
* 
* @Author Kurt
*
* @return viewports Y value
*/
int CGame::GetViewportY() const
{
	return(m_iViewportY);
}

/**
* call to get the viewports height
* 
* @Author Kurt
*
* @return viewports height
*/
int CGame::GetViewportHeight() const
{
	return(m_iViewportHeight);
}

/**
* call to get the viewports width
* 
* @Author Kurt
*
* @return viewports width
*/
int CGame::GetViewportWidth() const
{
	return(m_iViewportWidth);
}


/**
* Modifies the current game state variable.
* 
* @Author Kurt
*
* @return viewports width
*/
void CGame::SetNewState(EGameState _eGS, std::string _strLevelName)
{
	m_eGameState = _eGS;
	m_strLevelName = _strLevelName;
}

/**
* Deletes and initialises new state objects, based on the current and last gamestate variables.
* 
* @Author Kurt
*
* @return viewports width
*/
void CGame::SwapState()
{
	switch(m_eLastState) 
	{
		case GAMESTATE_MENU:
		{
			delete m_pMenu;
			m_pMenu = 0;
		}
		break;
		case GAMESTATE_SESSION:
		case GAMESTATE_TUTORIAL:
		{
			delete m_pSession;
			m_pSession = 0;
		}
		break;
		case GAMESTATE_EDITOR:
		{
			delete m_pEditor;
			m_pEditor = 0;
		}
		break;
	}

	switch(m_eGameState) 
	{
		case GAMESTATE_MENU:
		{
			m_pMenu = new CMenu;
			m_pMenu->Initialise(MENU_MAIN);
		}
		break;
		case GAMESTATE_SESSION:
		{
			m_pSession = new CSession;
			m_pSession->Initialise(m_pSpriteManager, m_strLevelName);
		}
		break;
		case GAMESTATE_EDITOR:
		{
			m_pEditor = new CEditor;
			m_pEditor->Initialise(m_pSpriteManager, m_strLevelName);
		}
		break;
		case GAMESTATE_TUTORIAL:
		{
			m_pSession = new CTutorial;
			m_pSession->Initialise(m_pSpriteManager, "Tutorial/Tutorial");
		}
		break;
	}

	m_eLastState = m_eGameState;
	
}


void CGame::InitSounds()
{
	
	
	m_vecSounds.push_back(m_pSoundManager->LoadSoundFromFile("Sounds/MissleFiring.mp3"));

	m_vecSounds.push_back(m_pSoundManager->LoadSoundFromFile("Sounds/Kill1.mp3"));
	m_vecSounds.push_back(m_pSoundManager->LoadSoundFromFile("Sounds/Kill2.mp3"));
	m_vecSounds.push_back(m_pSoundManager->LoadSoundFromFile("Sounds/Kill3.mp3"));
	
	m_vecSounds.push_back(m_pSoundManager->LoadSoundFromFile("Sounds/MSC.mp3"));
	
	m_vecSounds.push_back(m_pSoundManager->LoadSoundFromFile("Sounds/PowerUp.mp3"));

	m_vecSounds.push_back(m_pSoundManager->LoadSoundFromFile("Sounds/PowerDown.mp3"));



}

void CGame::PlayGameSound(ESoundID _SoundID)
{
	switch(_SoundID)
	{
	case SOUNDID_ButtonPress:
		{
			m_pSoundManager->PlaySoundW(m_vecSounds[(int)SOUNDID_ButtonPress]);
		}
		break;
	case SOUNDID_UnitDeath:
		{
			int iRand = rand() % 3;
			
			m_pSoundManager->PlaySoundW(m_vecSounds[(int)SOUNDID_UnitDeath+iRand]);
		}
		break;
	case SOUNDID_GameMusic:
		{
			m_pSoundManager->PlaySoundW(m_vecSounds[(int)SOUNDID_GameMusic], true, true);
		}
		break;
	default:
		{
			m_pSoundManager->PlaySoundW(m_vecSounds[(int)_SoundID]);
		}
	}

}

void CGame::StopSounds()
{
	for(unsigned int i = 0; i < m_vecSounds.size(); ++i)
	{
		m_pSoundManager->StopSound(m_vecSounds[i]);
	}
}





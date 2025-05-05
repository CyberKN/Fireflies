#pragma once

#if !defined(__GAME_H__)
#define __GAME_H__

// Library Includes
#include <windows.h>
#include "clock.h"
#include <d3dx9.h>
#include <d3d9.h>

#include "utils.h"

// Local Includes
#include "D3DRenderer.h"
#include "DialogBox.h"
#include "DInputKeyboard.h"
#include "DInputMouse.h"
#include "eXInput.h"
#include "INIParser.h"
#include "SpriteManager.h"
#include "TextManager.h"
#include "Soundmanager.h"
#include "Session.h"
#include "Editor.h"
#include "Tutorial.h"


// Types

enum EGameState
{
	GAMESTATE_MENU,
	GAMESTATE_EDITOR,
	GAMESTATE_SESSION,
	GAMESTATE_TUTORIAL
};

// Constants

// Prototypes

class CMenu;

class CGame
{
// Member Functions
public:
	virtual ~CGame();

	virtual bool Initialise(HINSTANCE _hInstance, HWND _hWnd, int _iWidth, int _iHeight);

	virtual void Process(float _fDeltaTick);
	virtual void Draw();

	void ExecuteOneFrame();

	static CGame& GetInstance();
	static void DestroyInstance();

	
	HINSTANCE GetAppInstance();
	HWND GetWindow();      

	int GetViewportX() const;
	int GetViewportY() const;
	int GetViewportHeight() const;
	int GetViewportWidth() const;

	D3DXMATRIX* GetViewMatrix();
	D3DXMATRIX* GetProjectionMatrix();

	void PopulateViewMatrix();
	void PopulateProjectionMatrix();

	CSpriteManager* GetSpriteManager(){return(m_pSpriteManager);};
	CTextManager* GetTextManager(){return(m_pTextManager);};
	CSoundManager* GetSoundManager(){return(m_pSoundManager);};

	CSession* GetSession(){return(m_pSession);};
	CEditor* GetEditor(){return(m_pEditor);};

	void SetHasFocus(bool _bHasFocus){m_bHasFocus = _bHasFocus;};
	bool HasFocus(){return(m_bHasFocus);};

	void SetNewState(EGameState _eGS, std::string _strLevelName = "");
	EGameState GetGameState(){return(m_eGameState);};
	void SwapState();

	void InitSounds();
	void PlayGameSound(ESoundID _SoundID);
	void StopSounds();
	



protected:

private:
	CGame();
	CGame(const CGame& _kr);
	CGame& operator= (const CGame& _kr);

// Member Variables
public:

	float m_fDeltaTick;

	CDialogBox m_DialogBox;

	CD3DRenderer m_DirectX3DRenderer;
	CDInputKeyboard m_Keyboard;
	CDInputMouse m_Mouse;
	std::vector<CXInput*> m_XboxVec;
	CINIParser m_INIParser;


	
	int m_iWindowHeight;
	int m_iWindowWidth;
	

	int m_iWindowOffsetX;
	int m_iWindowOffsetY;	

protected:
	CClock* m_pClock;

	HINSTANCE m_hApplicationInstance;
	HWND m_hMainWindow;

	static CGame* s_pGame;

	int m_iViewportX;
	int m_iViewportY;
	int m_iViewportHeight;
	int m_iViewportWidth;

	int m_iSleepTime;

	
	bool m_bHasFocus;

	CTextManager* m_pTextManager;
	CSpriteManager* m_pSpriteManager;
	CSoundManager* m_pSoundManager;

	CSession*	m_pSession;
	CEditor*	m_pEditor;
	CMenu*		m_pMenu;

	EGameState m_eGameState;
	EGameState m_eLastState;
	std::string m_strLevelName;
	std::vector<int> m_vecSounds;

private:

};

#endif // __Game_H__

#pragma once

#if !defined(__Session_H__)
#define __Session_H__

// Library Includes
#include "utils.h"


// Local Includes
#include "TipBox.h"
#include "INIParser.h"
#include "UnitManager.h"
#include "ExplosionManager.h"
#include "LanternManager.h"
#include "Lantern.h"
#include "PlayerManager.h"
#include "NodeLinkManager.h"
// Types

// Constants

// Prototypes

class CCursor;
class CSpriteManager;
class CMenu;



class CSession
{
// Member Functions
public:
	CSession();
	~CSession();
	void Initialise(CSpriteManager* _pSpriteManager, std::string _strLevelName = "");
	virtual void Process(float _fDeltaTick);
	void Draw();
	CUnitManager* GetUnitManager();
	CExplosionManager* GetExplosionManager(){return(&m_ExplosionManager);};
	CLanternManager* GetLanternManager(){return(&m_LanternManager);};
	CPlayerManager* GetPlayerManager(){return(&m_PlayerManager);};
	void SetPaused(bool _b){m_bPaused = _b;};
	void CheckForWin();

protected:

private:

// Member Variables
public:

	CSpriteManager* m_pSpriteManager;
	CINIParser m_INIParser;
	CINIParser m_SavedGameINIParser;
	int m_iSound_Music;

	CUnitManager m_UnitManager;
	CExplosionManager m_ExplosionManager;
	CLanternManager m_LanternManager;
	CPlayerManager m_PlayerManager;
	CNodeLinkManager m_NodeLinkManager;
	CCursor* m_pCursor;
	bool m_bPaused;
	float m_fDefaultZoom;
	float m_fDefaultOffsetX;
	float m_fDefaultOffsetY;
	bool m_bGameWon;
	float m_fGameOverFadeTimer;
	CSpriteDataShell m_FadeSprite;
	CSpriteDataShell m_BGSprite;

	CTipBox m_TipBox;

	unsigned int m_iCollisionChecks;

	CMenu* m_pPauseMenu;




	

protected:

private:

};

#endif // __Session_H__

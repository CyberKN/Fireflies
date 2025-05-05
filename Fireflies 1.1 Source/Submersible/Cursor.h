#pragma once

#if !defined(__Cursor_H__)
#define __Cursor_H__

// Library Includes
#include "GameEntity.h"

// Local Includes

// Types

// Constants

// Prototypes

class CPlayer;


class CCursor : public CGameEntity
{
// Member Functions
public:
	CCursor();
	~CCursor();
	void Initialise(CPlayer* _pPlayer);
	void Process(float _fDeltaTick, bool _bTutorialMode = false);
	void Draw();
	void ProcessSpriteAnimation(float _fDeltaTick);
	void DisplayDebugInfo();
	void CalculateZoomPosition();
	
	void SetFakeClick(bool _b){m_bFakeClick = _b;};
	bool GetFakeClick(){return(m_bFakeClick);};

protected:

private:

// Member Variables
public:
	CSpriteDataShell m_SpriteAnimated;

	bool m_bClick;
	float m_fSelectedX;
	float m_fSelectedY;

	float m_fSelectSize;

	CPlayer* m_pPlayer;

	bool m_bTutorialMode;
	bool m_bFakeClick;

protected:

private:

};

#endif // __Cursor_H__

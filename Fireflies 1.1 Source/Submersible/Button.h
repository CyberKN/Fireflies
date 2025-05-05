#pragma once

#if !defined(__Button_H__)
#define __Button_H__

// Library Includes

// Local Includes
#include "MenuItem.h"

// Types

enum EButtonState
{
	BSTATE_UP,
	BSTATE_OVER,
	BSTATE_DOWN
};

// Constants

// Prototypes

class CMenu;


class CButton : public CMenuItem
{
// Member Functions
public:
	CButton();
	~CButton();
	void Initialise(EMenuItemType _eMenuItemType, float _fX, float _fY, CMenu* _pParentMenu);
	void Process(float _fDeltaTick);
	void Draw();
	void SetState(EButtonState _eBS){m_eButtonState = _eBS;};
	EButtonState GetState(EButtonState _eBS){return(m_eButtonState);};
	void Activate();
	void SetData(std::string _strData){m_strButtonData = _strData;};
	std::string GetData(){return(m_strButtonData);};
	void SetDrawData(bool _b){m_bDrawData = _b;};

	bool IsHighlighted(){return(m_bHighlighted);};
	void SetHighlighted(bool _b){m_bHighlighted = _b;};

protected:

private:

// Member Variables
public:


protected:

	CSpriteDataShell m_DownSprite;
	CSpriteDataShell m_OverSprite;
	EButtonState m_eButtonState;
	std::string m_strButtonData;
	bool m_bDrawData;
	bool m_bHighlighted;

private:

};

#endif // __Button_H__

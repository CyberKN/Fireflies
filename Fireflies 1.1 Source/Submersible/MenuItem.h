#pragma once

#if !defined(__MenuItem_H__)
#define __MenuItem_H__

// Library Includes

// Local Includes

#include "GameEntity.h"

// Types

enum EMenuItemType
{
	MENUBUTTON_STATIC = 0,
	MENUBUTTON_LEVEL_EDITOR,
	MENUBUTTON_QUIT,
	MENUBUTTON_EXIT,
	MENUBUTTON_START,
	MENUBUTTON_LEVEL_SELECT,
	MENUBUTTON_LEVEL_PREVIEW,
	MENUBUTTON_BACK,
	MENUBUTTON_RESUME,
	MENUBUTTON_SAVE,
	MENUBUTTON_CONFIRM_OVERWRITE,
	MENUBUTTON_ABORT_OVERWRITE,
	MENUBUTTON_CYCLEUP,
	MENUBUTTON_CYCLEDOWN,
	MENUBUTTON_TUTORIAL,
	MENUBUTTON_CREDITS
};

// Constants

// Prototypes

class CMenu;


class CMenuItem: public CGameEntity
{
// Member Functions
public:
	CMenuItem();
	~CMenuItem();
	virtual void Initialise(EMenuItemType _eMenuItemType, float _fX, float _fY, std::string _strSpriteFilePath, CMenu* _pParentMenu);
	virtual void Process(float _fDeltaTick);
	virtual void Draw();

protected:

private:

// Member Variables
public:
	CMenu* m_pParentMenu;
	EMenuItemType m_eType;

protected:

private:

};

#endif // __MenuItem_H__

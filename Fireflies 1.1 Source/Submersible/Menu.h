#pragma once

#if !defined(__Menu_H__)
#define __Menu_H__

// Library Includes

#include "defines.h"
#include "utils.h"
#include "SpriteDataShell.h"
#include "ChoiceChecker.h"

// Local Includes


// Types
enum EMenuType
{
	MENU_MAIN,
	MENU_LEVEL,
	MENU_PAUSE,
	MENU_LEVEL_EDITOR,
	MENU_PAUSE_EDITOR,
	MENU_OVERWRITE,
	MENU_CREDITS
};

// Constants

// Prototypes

class CButton;
class CNameForm;
class CLevelPreviewer;


class CMenu
{
// Member Functions
public:
	CMenu();
	~CMenu();
	virtual void Initialise(EMenuType _MenuType, CMenu* _pParentMenu = 0);
	virtual void Process(float _fDeltaTick);
	virtual void Draw();
	void OpenSubMenu(EMenuType _MenuType);
	void CloseSubMenu();
	CMenu* GetSubMenu(){return(m_pSubMenu);};
	CMenu* GetParentMenu(){return(m_pParentMenu);};
	void SetAsClosed(){m_bOpen = false;};
	bool IsOpen(){return(m_bOpen);};
	void GenerateLevelList(std::string directoryName);
	void ListFilesInDirectory(std::string directoryName, std::vector<std::string>& _vecFileNames);

	void SetLevelName(std::string _strName){m_strLevelName = _strName;};
	std::string GetLevelName(){return(m_strLevelName);};

	void PreviewLevel(std::string _strLevelName);

	EMenuType GetMenuType(){return(m_eMenuType);};
	CNameForm* GetNameForm(){return(m_pNameForm);};

	void CloseNameForm(bool _bSave);
	void OpenNameForm();
	void OpenChoiceChecker(ECheckerType _eCheckerType);

	bool CycleLevelsUp();
	bool CycleLevelsDown();

	void ProcessScrolling();

	void ProcessMenuSpecificVisualElements(float _fDeltaTick);



protected:

private:

// Member Variables
public:
	std::vector<CSpriteDataShell> m_vecBackgroundSprites;
	std::vector<CButton*> m_vecButtons;
	std::vector<CButton*> m_vecLevelButtons;
	unsigned int m_iListTop;
	CButton* m_pSelectedButton;
	CMenu* m_pSubMenu;
	CMenu* m_pParentMenu;
	bool m_bOpen;
	EMenuType m_eMenuType;
	CNameForm* m_pNameForm;
	CLevelPreviewer* m_pPreviewer;
	CChoiceChecker* m_pChecker;
	CSpriteDataShell m_BackgroundSprite;

	std::string m_strLevelName;


protected:

private:

};

#endif // __Menu_H__

#pragma once

#if !defined(__NameForm_H__)
#define __NameForm_H__

// Library Includes

// Local Includes
#include "MenuItem.h"
#include "TextBox.h"

// Types

// Constants

// Prototypes

class CMenu;
class CChoiceChecker;

class CNameForm : public CMenuItem
{
// Member Functions
public:
	CNameForm();
	~CNameForm();
	void Initialise(std::string _strDefaultName, CMenu* _pParentMenu);
	void Process(float _fDeltaTick);
	void Draw();
	void GetListOfFiles();
	void CancelOverwrite();

	std::string GetString(){return(m_strFileName);};

protected:

private:

// Member Variables
public:
	CTextBox m_TextBox;
	std::string m_strFileName;
	float m_fCursorTimer;
	bool m_bCursorVisible;
	CSpriteDataShell m_BGSprite;
	CSpriteDataShell m_BoxSprite;
	std::vector<std::string> m_vecFileNames;
	CMenu* m_pParentMenu;
	CChoiceChecker* m_pOverwriteChecker;

	//CMenu* m_pOverwriteMenu;

protected:

private:

};

#endif // __NameForm_H__

#pragma once

#if !defined(__ChoiceChecker_H__)
#define __ChoiceChecker_H__

// Library Includes

// Local Includes
#include "MenuItem.h"

// Types

enum ECheckerType
{
	CHECKER_Overwrite,
	CHECKER_Quit,
	CHECKER_Exit
};

// Constants

// Prototypes


class CChoiceChecker : public CMenuItem
{
// Member Functions
public:
	CChoiceChecker();
	~CChoiceChecker();
	void Initialise(ECheckerType _eCheckerType, CMenu* _pParentMenu);
	void Process();
	void Draw();
	void Confirm();
	bool IsOpen(){return(m_bOpen);};

protected:

private:

// Member Variables
public:
	

protected:
	CMenu* m_pParentMenu;
	CSpriteDataShell m_ConfirmButton;
	CSpriteDataShell m_CancelButton;
	CSpriteDataShell* m_pSelectedButton;
	bool m_bOpen;
	ECheckerType m_eCheckerType;

private:

};

#endif // __ChoiceChecker_H__

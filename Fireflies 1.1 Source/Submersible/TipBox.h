#pragma once

#if !defined(__TipBox_H__)
#define __TipBox_H__

// Library Includes

// Local Includes
#include "SpriteDataShell.h"
#include "TextBox.h"

// Types

// Constants

// Prototypes


class CTipBox
{
// Member Functions
public:
	CTipBox();
	~CTipBox();
	void Initialise();
	void Process(float _fDeltaTick);
	void Open(std::string _strTip);
	void Draw();
	

protected:

private:

// Member Variables
public:
	bool m_bOpen;
	float m_fAlphaTimer;
	CTextBox m_TextBox;
	CSpriteDataShell m_TipBackground;

protected:

private:

};

#endif // __TipBox_H__

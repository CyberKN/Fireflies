#pragma once

#if !defined(__TextBox_H__)
#define __TextBox_H__

// Library Includes
#include "SpriteDataShell.h"
#include <string>

// Local Includes

// Types

// Constants

// Prototypes


class CTextBox
{
// Member Functions
public:
	CTextBox();
	~CTextBox();
	void Initialise(int _iMaxCharsPerLine, float _fX, float _fY, int _iSize, bool _bRevealed, bool _bCentered, float _fLetterRevealSpeed);
	void Process(float _fDeltaTick);
	void Draw();
	void SetString(std::string _str){*m_pTextString = _str;};
	std::string GetString(){return(*m_pTextString);};
	void SetColor(int _iAlpha, int _iRed, int _iGreen, int _iBlue);

protected:

private:

// Member Variables
public:
	int m_iMaxCharsPerLine;
	int m_iRevealedChars;
	float m_fX;
	float m_fY;
	int m_iSize;
	std::string* m_pTextString;
	bool m_bRevealed;
	bool m_bCentered;

	int m_iRed;
	int m_iBlue;
	int m_iGreen;
	int m_iAlpha;

	float m_fLetterRevealSpeed;
	
	float m_fAddCharTimer;


protected:

private:

};

#endif // __TextBox_H__

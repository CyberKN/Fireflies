// Library Includes

// Local Includes

// This include
#include "TextBox.h"
#include "game.h"

// Constants

// Static Variables

// Static Function Prototypes

// Implementation
CTextBox::CTextBox()
:m_iMaxCharsPerLine(-1)
,m_iRevealedChars(0)
,m_fAddCharTimer(0)
,m_fX(0)
,m_fY(0)
,m_iSize(1)
,m_fLetterRevealSpeed(1)
,m_bRevealed(true)
,m_bCentered(false)
,m_iAlpha(255)
,m_iRed(255)
,m_iGreen(255)
,m_iBlue(255)
,m_pTextString(0)
{
	m_pTextString = 0;
	m_pTextString = new std::string("NULL STRING");
}

CTextBox::~CTextBox()
{
	delete m_pTextString;
	m_pTextString = 0;

}

void CTextBox::Initialise(int _iMaxCharsPerLine, float _fX, float _fY, int _iSize, bool _bRevealed, bool _bCentered, float _fLetterRevealSpeed)
{
	m_iMaxCharsPerLine = _iMaxCharsPerLine;
	m_fX = _fX;
	m_fY = _fY;
	m_iSize = _iSize;
	m_fLetterRevealSpeed = _fLetterRevealSpeed;
	m_bRevealed = _bRevealed;	
	m_bCentered = _bCentered;

}

void CTextBox::Process(float _fDeltaTick)
{
	if(!m_bRevealed)
	{
		m_fAddCharTimer += _fDeltaTick;

		if(m_fAddCharTimer >= m_fLetterRevealSpeed)
		{
			m_fAddCharTimer = 0;
			m_iRevealedChars += 1;
		}
	}

}

void CTextBox::Draw()
{
	CGame::GetInstance().GetTextManager()->Draw(this, *m_pTextString);
}

void CTextBox::SetColor(int _iAlpha, int _iRed, int _iGreen, int _iBlue)
{
	m_iAlpha = _iAlpha;
	m_iRed = _iRed;
	m_iGreen = _iGreen;
	m_iBlue = _iBlue;
}


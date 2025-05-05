// Library Includes

// Local Includes

// This include
#include "TipBox.h"
#include "defines.h"

// Constants

// Static Variables

// Static Function Prototypes

// Implementation

CTipBox::CTipBox()
:m_bOpen(false)
,m_fAlphaTimer(0)
{

}

CTipBox::~CTipBox()
{

}

void CTipBox::Initialise()
{
	m_TipBackground.Initialise(SPRITE_Block4Sides, 1);
	m_TipBackground.TranslateAbsolute(350, 575);
	m_TipBackground.SetIgnoreOffset(true);

	m_TextBox.Initialise(256, 400, 200, 4, true, true, 1);

}

void CTipBox::Process(float _fDeltaTick)
{
	if(m_fAlphaTimer > 7)
	{
		m_bOpen = false;
		m_fAlphaTimer = 1;
	}

	if(m_bOpen)
	{
		m_fAlphaTimer += _fDeltaTick;
	}
	else
	{
		m_fAlphaTimer -= _fDeltaTick;
	}

}

void CTipBox::Open(std::string _strTip)
{
	m_TextBox.SetString(_strTip);

	m_bOpen = true;
	m_fAlphaTimer = 0;

}

void CTipBox::Draw()
{	
	if(m_fAlphaTimer >= 1)
	{
		m_TextBox.m_iAlpha = 255;
		m_TipBackground.SetColor(170, 255, 255, 255);
	}
	else if(m_fAlphaTimer <=0)
	{
		m_TextBox.m_iAlpha = 0;
		m_TipBackground.SetColor(0, 255, 255, 255);
	}
	else
	{
		m_TextBox.m_iAlpha = static_cast<int>(m_fAlphaTimer * 255);
		m_TipBackground.SetColor(static_cast<int>(m_fAlphaTimer * 170), 255, 255, 255); 
	}

	if(m_fAlphaTimer > 0)
	{
		//m_TipBackground.Draw();
		m_TextBox.Draw();
	}

}

// Library Includes 

// Local Includes 

// This Includes 
#include "SpriteDataShell.h" 
#include "game.h"

// Static Variables 

// Static Function Prototypes

// Implementation

CSpriteDataShell::CSpriteDataShell()
:m_fX(0)
,m_fY(0)
,m_fRotation(0)
,m_fTimer(0)
,m_fXScale(1)
,m_fYScale(1)
,m_iAlpha(255)
,m_iRed(255)
,m_iBlue(255)
,m_iGreen(255)
,m_SpriteID(SPRITE_Block4Sides)
,m_fFrameSpeed(1.0f)
,m_iNumFrames(1)
,m_iCurrentFrame(0)
,m_bIgnoreOffset(0)
{


}

CSpriteDataShell::~CSpriteDataShell()
{


}


bool CSpriteDataShell::Initialise(ESpriteID _SpriteID, float _fScale)
{
	m_SpriteID = _SpriteID;

	m_iNumFrames = CGame::GetInstance().GetSpriteManager()->GetTotalFrames(m_SpriteID);

	m_fXScale = _fScale;
	m_fYScale = _fScale;
	

	return(true);
}


void CSpriteDataShell::TranslateAbsolute(float _iX, float _iY)
{
	m_fX = _iX;
	m_fY = _iY;
}


float CSpriteDataShell::GetX()
{
	return(m_fX);
}


float CSpriteDataShell::GetY()
{
	return(m_fY);
}


void CSpriteDataShell::Draw()
{
	CGame::GetInstance().GetSpriteManager()->Draw(this);
	
}

void CSpriteDataShell::SetRotate(float _fradians)
{
	m_fRotation = _fradians;
}

void CSpriteDataShell::SetColor(int _iAlpha, int _iRed, int _iGreen, int _iBlue)
{
	m_iAlpha = _iAlpha;
	m_iRed = _iRed;
	m_iGreen = _iGreen;
	m_iBlue = _iBlue;
}

float CSpriteDataShell::GetRotate()
{
	return(m_fRotation);

}

int CSpriteDataShell::GetAlpha()
{
	return(m_iAlpha);

}
int CSpriteDataShell::GetRed()
{
	return(m_iRed);
}
int CSpriteDataShell::GetGreen()
{
	return(m_iGreen);
}
int CSpriteDataShell::GetBlue()
{
	return(m_iBlue);
}

void CSpriteDataShell::SetScaleX(float _f)
{
	m_fXScale = _f;
}
void CSpriteDataShell::SetScaleY(float _f)
{
	m_fYScale = _f;
}

float CSpriteDataShell::GetScaleX()
{
	return(m_fXScale);
}
float CSpriteDataShell::GetScaleY()
{
	return(m_fYScale);
}

ESpriteID CSpriteDataShell::GetSpriteID()
{
	return(m_SpriteID);
}

void CSpriteDataShell::Process(float _fDeltaTick)
{
	m_fTimer += _fDeltaTick;

	if(m_fTimer > m_fFrameSpeed)
	{
		m_fTimer = 0;
		++m_iCurrentFrame;
		if(m_iCurrentFrame > m_iNumFrames-1)
		{
			m_iCurrentFrame = 0;
		}
	}
}

int CSpriteDataShell::GetCurrentFrame()
{
	return(m_iCurrentFrame);
}

void CSpriteDataShell::SetSpeed(float _fSpeed)
{
	m_fFrameSpeed = _fSpeed;
}

bool CSpriteDataShell::IgnoreOffset()
{
	return(m_bIgnoreOffset);
}

void  CSpriteDataShell::SetIgnoreOffset(bool _b)
{
	m_bIgnoreOffset = _b;
}

float CSpriteDataShell::GetHeight()
{
	return(CGame::GetInstance().GetSpriteManager()->GetHeight(m_SpriteID)*m_fYScale);
}

float CSpriteDataShell::GetWidth()
{
	return(CGame::GetInstance().GetSpriteManager()->GetWidth(m_SpriteID)*m_fXScale);
}
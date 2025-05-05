// Library Includes

// Local Includes

//#include "resource.h"
#include "Game.h"
#include "utils.h"

// This include
#include "SpriteGDI.h"

// Constants

// Static Variables

HDC CSpriteGDI::s_hSharedSpriteDC = 0;
int CSpriteGDI::s_iRefCount = 0;

// Static Function Prototypes

// Implementation

CSpriteGDI::CSpriteGDI()
: m_iX(0)
, m_iY(0)
{
	++s_iRefCount;
}

CSpriteGDI::~CSpriteGDI()
{
	DeleteObject(m_hSprite);
	
	--s_iRefCount;

	if(s_iRefCount == 0)
	{
		DeleteDC(s_hSharedSpriteDC);
	}
}

bool CSpriteGDI::Initialise(std::string _strFileName)
{
	HINSTANCE hInstance = CGame::GetInstance().GetAppInstance();

	if (!s_hSharedSpriteDC)
	{
		s_hSharedSpriteDC = CreateCompatibleDC(NULL);
	}

	
	m_hSprite = (HBITMAP) ::LoadImage (0, StringToWString(_strFileName).c_str(),IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	VALIDATE(m_hSprite);

	GetObject(m_hSprite, sizeof(BITMAP), &m_bitmapSprite);

	return(true);
}

void CSpriteGDI::Deinitialise()
{
	DeleteObject(m_hSprite);
}

void CSpriteGDI::Draw()
{
	


}

void CSpriteGDI::Process(float fDeltaTick)
{
	
}	

int const CSpriteGDI::GetWidth()
{
	return(m_bitmapSprite.bmWidth);
}

int const CSpriteGDI::GetHeight() 
{
	return(m_bitmapSprite.bmHeight);
}

int const CSpriteGDI::GetX()
{
	return(m_iX);
}

int const CSpriteGDI::GetY()
{
	return(m_iY);
}

void CSpriteGDI::SetX(int _i)
{
	m_iX = _i;
}

void CSpriteGDI::SetY(int _i)
{
	m_iY = _i;
}

void CSpriteGDI::TranslateRelative(int _iX, int _iY)
{
	m_iX += _iX;
	m_iY += _iY;
}

void CSpriteGDI::TranslateAbsolute(int _iX, int _iY)
{
	m_iX = _iX;
	m_iY = _iY;
}
	
COLORREF CSpriteGDI::GetPixel(int _iX, int _iY)
{
	HGDIOBJ hGDIObj = SelectObject(s_hSharedSpriteDC, m_hSprite);

	COLORREF clrRef = ::GetPixel(s_hSharedSpriteDC, _iX, _iY);

	SelectObject(s_hSharedSpriteDC, hGDIObj);

	return(clrRef);
}




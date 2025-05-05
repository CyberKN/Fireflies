#pragma once

#if !defined(__SPRITEGDI_H__)
#define __SPRITEGDI_H__

// Library Includes

#include "windows.h"
#include <string>
#include "linkedlist.h"
#include "vector.h"

// Local Includes

// Types

// Constants

// Prototypes


class CSpriteGDI
{
// Member Functions
public:
	CSpriteGDI();
	virtual ~CSpriteGDI();
	virtual bool Initialise(std::string _strFileName);
	virtual void Deinitialise();
	virtual void Process(float fDeltaTick);
	virtual void Draw();
	int const GetWidth();
	int const GetHeight();
	int const GetX();
	int const GetY();
	void SetX(int _i);
	void SetY(int _i);
	void TranslateRelative(int _iX, int _iY);
	void TranslateAbsolute(int _iX, int _iY);
	COLORREF GetPixel(int _iX, int _iY);



protected:

private:
	CSpriteGDI(const CSpriteGDI& _kr);
	CSpriteGDI& operator= (const CSpriteGDI& _kr);

// Member Variables
public:

protected:
	static int s_iRefCount;
	static HDC s_hSharedSpriteDC;
	int m_iX;
	int m_iY;
	HBITMAP m_hSprite;
	BITMAP m_bitmapSprite;


private:

};

#endif // __SPRITEGDI_H__

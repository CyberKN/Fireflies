#pragma once

#ifndef __IGFEB10_IG500_SPRITE_H__
#define __IGFEB10_IG500_SPRITE_H__

// Library Includes 
#include <d3d9.h>
#include <d3dx9.h>

// Local Includes 
#include "defines.h"

// Types 

// Constants 

// Prototypes 

class CSpriteManager;


class CSprite
{
		// Member Functions
public:
	CSprite();
	~CSprite();
	bool Initialise(LPCWSTR _SrcFile, int _iXSize, int _iYSize, float _fScale, CSpriteManager* _pManager);
	void TranslateAbsolute(float _iX, float _iY);
	float GetX();
	float GetY();
	void SetRotate(float _fradians);
	void SetColor(int _iAlpha, int _iRed, int _iGreen, int _iBlue);
	void Draw();

protected:

private:

		// Member Variables
public:
	LPDIRECT3DTEXTURE9 m_pSource;

	int m_iSizeX;
	int m_iSizeY;
	int m_iFrameWidth;
	int m_iFrameHeight;
	float m_fXScale;
	float m_fYScale;
	float m_fRotation;
	D3DCOLOR m_Colour;

	LPD3DXSPRITE m_pSprite;
	D3DXVECTOR3 m_Pos;
	D3DXIMAGE_INFO m_ImageInfo;
	CSpriteManager* m_pManager;

protected:

private:

};

#endif // __IGFEB10_IG500_SPRITE_H__

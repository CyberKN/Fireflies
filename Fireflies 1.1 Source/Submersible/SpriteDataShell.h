#pragma once

#ifndef __IGFEB10_IG500_SPRITEDATASHELL_H__
#define __IGFEB10_IG500_SPRITEDATASHELL_H__

// Library Includes 
#include <d3d9.h>
#include <d3dx9.h>

// Local Includes 
#include "defines.h"

// Types 

// Constants 

// Prototypes 


class CSpriteDataShell
{
		// Member Functions
public:
	CSpriteDataShell();
	~CSpriteDataShell();
	bool Initialise(ESpriteID _SpriteID, float _fScale);
	void TranslateAbsolute(float _iX, float _iY);
	float GetX();
	float GetY();
	void SetRotate(float _fradians);
	void SetColor(int _iAlpha, int _iRed, int _iGreen, int _iBlue);
	void Draw();

	void SetSpeed(float _fSpeed);

	float GetRotate();
	int GetAlpha();
	int GetRed();
	int GetGreen();
	int GetBlue();

	void SetScaleX(float _f);
	void SetScaleY(float _f);

	float GetScaleX();
	float GetScaleY();

	float GetHeight();
	float GetWidth();

	ESpriteID GetSpriteID();

	void Process(float _fDeltaTick);
	int GetCurrentFrame();

	bool IgnoreOffset();
	void SetIgnoreOffset(bool _b);





protected:



private:



public:

protected:

	float m_fXScale;
	float m_fYScale;
	float m_fRotation;
	int m_iCurrentFrame;
	int m_iRed;
	int m_iGreen;
	int m_iBlue;
	int m_iAlpha;
	bool m_bAnimatedSprite;
	float m_fTimer;
	float m_fFrameSpeed;
	ESpriteID m_SpriteID;
	int m_iNumFrames;
	bool m_bIgnoreOffset;

	float m_fX;
	float m_fY;
	unsigned int m_iSpriteSizeX;
	unsigned int m_iSpriteSizeY;

private:

};

#endif // __IGFEB10_IG500_SPRITEDATASHELL_H__

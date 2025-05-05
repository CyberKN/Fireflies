#pragma once

#if !defined(__ANIMATEDSPRITE_H__)
#define __ANIMATEDSPRITE_H__

// Library Includes
#include <windows.h>
#include <vector>

// Local Includes
#include "sprite.h"

// Types

// Prototypes


class CAnimatedSprite : public CSprite
{
	// Member Functions
public:
	CAnimatedSprite();
	~CAnimatedSprite();
	float GetX();
	float GetY();
	void SetRotate(float _fradians);
	void Draw();
	void Draw(RECT _rect);

	void Process(float _fDeltaTick);
	void AddFrame(int _iX, int _iY);
	void SetSpeed(float _fSpeed);
	void SetWidth(int _iWidth);
	void SetHeight(int _iHeight);
	int GetFrameWidth();
	int GetFrameHeight();

	void ClearVector();

protected:

private:

	// Member Variables
public:

	int m_iCurrentSprite;
	float m_fFrameSpeed;
	std::vector<int> m_vectorFramesX;
	std::vector<int> m_vectorFramesY;
	float m_fTimeElapsed;
	int m_iFrameCounter;
	unsigned int m_iCircuitsCompleted;

protected:


private:

}; 

#endif // __ANIMATEDSPRITE_H__

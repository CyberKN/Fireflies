#pragma once

#if !defined(__GameEntity_H__)
#define __GameEntity_H__

// Library Includes


#include <vector>
#include <d3d9.h>
#include <d3dx9.h>

// Local Includes

#include "2DBoundingBox.h"
#include "SpriteDataShell.h"

// Types

// Constants

// Prototypes


class CGameEntity
{
// Member Functions
public:
	CGameEntity();
	~CGameEntity();
	virtual void Initialise();
	virtual void Process(float _fDeltaTick);
	virtual void Draw();

	void SetPosition(float _fX, float _fY);
	D3DXVECTOR2* GetPosition();
	float GetX();
	float GetY();
	
	void SetRotation(float _fRotation);
	float GetRotation();

	void SetVelocity(float _fVelocityX, float _fVelocityY);
	void AddVelocity(float _fVelocityX, float _fVelocityY);
	D3DXVECTOR2* GetVelocity();
	float GetVelocityX();
	float GetVelocityY();

	C2DBoundingBox* GetBoundingBox();

protected:

private:

// Member Variables
public:
	
	CSpriteDataShell m_Sprite;

protected:

	D3DXVECTOR2 m_MoveVec;
	D3DXVECTOR2 m_PosVec;
	float m_fRotation;
	C2DBoundingBox m_BoundingBox;

private:



};

#endif // __GameEntity_H__

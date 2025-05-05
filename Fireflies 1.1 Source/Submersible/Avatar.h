//  File Name   :   Avatar.h
//  Description :   CAvatar Header File
//  Author      :   Kurt Nadworny
//  Mail        :   kurt.nadworny@mediadesign.school.nz
//

#pragma once

#if !defined(__Avatar_H__)
#define __Avatar_H__

// Library Includes

// Local Includes

#include "gameEntity.h"

// Types

// Constants

// Prototypes


class CAvatar : public CGameEntity
{
// Member Functions
public:
	CAvatar();
	~CAvatar();
	void Initialise();
	void Process(float _fDeltaTick);
	void ProcessRespawn(float _fDeltaTick);
	bool ProcessMovementKeyboard(float _fDeltaTick);
	bool ProcessMovementXbox(float _fDeltaTick);
	void Draw();
	void MoveUp(float _fDeltaTick);
	void MoveDown(float _fDeltaTick);
	void MoveLeft(float _fDeltaTick);
	void MoveRight(float _fDeltaTick);
	void Fire();
	void ApplyDrag(float _fDeltaTick);
	void Die();

protected:

private:

// Member Variables
public:
	float m_fBubbleTimer;
	bool m_bFacingLeft;
	float m_fHealth;
	float m_fInvincibleTimer;
	float m_fSemiTransparentTimer;
	bool m_bSemiTransparent;
	bool m_bFiringKeyReleased;
	float m_fReloadTimer;
	bool m_bPressureWarning;
	bool m_bMovingX;
	bool m_bMovingY;

	int m_iCashCount;
	int m_iHullRatingLevel;
	int m_iBallastTanksLevel;
	int m_iEngineLevel;
	int m_iLightingLevel;
	int m_iReloadLevel;
	bool m_bGameComplete;
	bool m_bAlive;
	float m_fRespawnTimer;
	float m_fInvincibleTime;

	int m_iSound_PressureWarning;
	int m_iSound_Explode;

protected:

private:

};

#endif // __Avatar_H__

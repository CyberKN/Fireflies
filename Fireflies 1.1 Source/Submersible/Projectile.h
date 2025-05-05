//  File Name   :   Projectile.h
//  Description :   CProjectile Header File
//  Author      :   Kurt Nadworny
//  Mail        :   kurt.nadworny@mediadesign.school.nz
//

#pragma once

#if !defined(__Projectile_H__)
#define __Projectile_H__

// Library Includes

#include "GameEntity.h"
#include "player.h"

// Local Includes

// Types

// Constants

// Prototypes


class CProjectile : public CGameEntity
{
// Member Functions
public:
	CProjectile();
	~CProjectile();
	virtual void Initialise(float _fX, float m_fY, bool _bFriendly, D3DXVECTOR2 _MoveVec, int _iSound_Die);
	virtual void Process(float _fDeltaTick, CPlayer* _pPlayer);
	virtual void Explode(float _fSize);

protected:

private:

// Member Variables
public:
	int m_iDamage;
	float m_fDeathTimer;
	int m_iSound_Die;

protected:

private:

};

#endif // __Projectile_H__

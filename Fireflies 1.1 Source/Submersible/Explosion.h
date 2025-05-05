#pragma once

#if !defined(__Explosion_H__)
#define __Explosion_H__

// Library Includes
#include "utils.h"
#include "GameEntity.h"

// Local Includes

// Types

// Constants

// Prototypes


class CExplosion : public CGameEntity
{
// Member Functions
public:
	CExplosion();
	~CExplosion();
	void Initialise();
	void Process(float _fDeltaTick);
	void ApplyForce();

protected:

private:

// Member Variables
public:
	float m_fLifeTime;
	bool m_bDead;

protected:

private:

};

#endif // __Explosion_H__

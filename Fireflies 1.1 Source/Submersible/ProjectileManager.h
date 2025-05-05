#pragma once

#if !defined(__ProjectileManager_H__)
#define __ProjectileManager_H__

// Library Includes

// Local Includes

#include "Projectile.h"
#include "Enemy.h"
#include "ExplosionManager.h"

// Types

// Constants

// Prototypes


class CProjectileManager
{
// Member Functions
public:
	CProjectileManager();
	~CProjectileManager();
	void Initialise();
	void Process(float _fDeltaTick, CPlayer* _pPlayer);
	void AddProjectile(float _fX, float _fY, int _iType, D3DXVECTOR2 _MoveVec);
	void RemoveOffscreenProjectiles(float _fPlayerDepth);
	void ProcessEnemyProjectileCollision(CEnemy* _pEnemy);
	void ProcessPlayerProjectileCollision(CPlayer* _pPlayer);
	void Draw();

protected:

private:

// Member Variables
public:
	std::vector<CProjectile*> m_PlayerProjectileVec;
	std::vector<CProjectile*> m_EnemyProjectileVec;

	int m_iSound_TorpedoFire;
	int m_iSound_TorpedoImpact;


protected:

private:

};

#endif // __ProjectileManager_H__

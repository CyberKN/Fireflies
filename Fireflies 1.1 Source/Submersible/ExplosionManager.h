#pragma once

#if !defined(__ExplosionManager_H__)
#define __ExplosionManager_H__

// Library Includes
#include "utils.h"

// Local Includes

// Types

// Constants

// Prototypes

class CExplosion;


class CExplosionManager
{
// Member Functions
public:
	CExplosionManager();
	~CExplosionManager();
	void Process(float _fDeltaTick);
	void Draw();
	void CreateExplosion(float _fX, float _fY);

protected:

private:

// Member Variables
public:
	std::vector<CExplosion*> m_vecExplosions;

protected:

private:

};

#endif // __ExplosionManager_H__

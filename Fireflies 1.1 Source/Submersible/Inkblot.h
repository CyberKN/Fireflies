#pragma once

#if !defined(__Inkblot_H__)
#define __Inkblot_H__

// Library Includes

// Local Includes

#include "Projectile.h"

// Types

// Constants

// Prototypes


class CInkblot : public CProjectile
{
// Member Functions
public:
CInkblot();
~CInkblot();
void Initialise(float _fX, float m_fY, bool _bFriendly, D3DXVECTOR2 _MoveVec, int _iSound_Die);
void Process(float _fDeltaTick, CPlayer* _pPlayer);

protected:

private:

// Member Variables
public:

protected:

private:

};

#endif // __Inkblot_H__

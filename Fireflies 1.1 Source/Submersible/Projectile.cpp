//  File Name   :   Projectile.cpp
//  Description :   CProjectile Implementation File
//  Author      :   Kurt Nadworny
//  Mail        :   kurt.nadworny@mediadesign.school.nz
//



// Library Includes

// Local Includes

// This include
#include "Projectile.h"

// Constants

// Static Variables

// Static Function Prototypes

// Implementation

CProjectile::CProjectile()
:m_iSound_Die(-1)
{

}

CProjectile::~CProjectile()
{

}


void CProjectile::Initialise(float _fX, float m_fY, bool _bFriendly, D3DXVECTOR2 _MoveVec, int _iSound_Die)
{


}
void CProjectile::Process(float _fDeltaTick, CPlayer* _pPlayer)
{

}

void CProjectile::Explode(float _fSize)
{

}

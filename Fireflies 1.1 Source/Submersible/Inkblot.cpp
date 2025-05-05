//  File Name   :   Inkblot.cpp
//  Description :   CInkblot Implementation File
//  Author      :   Kurt Nadworny
//  Mail        :   kurt.nadworny@mediadesign.school.nz
//



// Library Includes

// Local Includes

// This include
#include "Inkblot.h"

// Constants

// Static Variables

// Static Function Prototypes

// Implementation

CInkblot::CInkblot()
{

}

CInkblot::~CInkblot()
{

}

void CInkblot::Initialise(float _fX, float _fY, bool _bFriendly, D3DXVECTOR2 _MoveVec, int _iSound_Die)
{
	m_Sprite.Initialise(SPRITE_InkBlot, 1);
	m_BoundingBox.SetSize(10, 10);
	m_fDeathTimer = 3600;
	m_iSound_Die = _iSound_Die;

	m_iDamage = 10;

	m_PosVec.x = _fX;
	m_PosVec.y = _fY;

	m_MoveVec.x = _MoveVec.x;
	m_MoveVec.y = _MoveVec.y;

	
	float fSpeed = sqrtf((m_MoveVec.x * m_MoveVec.x)+(m_MoveVec.y * m_MoveVec.y));

	m_MoveVec.x = m_MoveVec.x / fSpeed;
	m_MoveVec.y = m_MoveVec.y / fSpeed;

	m_Sprite.SetRotate(-atan(m_MoveVec.y/m_MoveVec.x));

	m_MoveVec.x = m_MoveVec.x * 50;
	m_MoveVec.y = m_MoveVec.y * 50;
}

void CInkblot::Process(float _fDeltaTick, CPlayer* _pPlayer)
{
	m_Sprite.SetRotate(m_Sprite.GetRotate() + _fDeltaTick);

	CGameEntity::Process(_fDeltaTick);

}

//void CInkblot::Explode(float _fSize)
//{
//
//}
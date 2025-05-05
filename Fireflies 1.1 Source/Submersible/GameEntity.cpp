// Library Includes

// Local Includes

// This include
#include "GameEntity.h"
#include "utils.h"

// Constants

// Static Variables

// Static Function Prototypes

// Implementation

CGameEntity::CGameEntity()
{
	m_MoveVec.x = 0;
	m_MoveVec.y = 0;

	m_PosVec.x = 0;
	m_PosVec.y = 0;

}

CGameEntity::~CGameEntity()
{

}

void CGameEntity::Initialise()
{


}

void CGameEntity::Process(float _fDeltaTick)
{
	m_PosVec.x += m_MoveVec.x*_fDeltaTick;
	m_PosVec.y += m_MoveVec.y*_fDeltaTick;

	m_BoundingBox.UpdatePosition(m_PosVec.x, m_PosVec.y);
	m_Sprite.Process(_fDeltaTick);

	

}

void CGameEntity::Draw()
{
	m_Sprite.TranslateAbsolute(m_PosVec.x, m_PosVec.y);
	m_Sprite.Draw();
}


void CGameEntity::SetPosition(float _fX, float _fY)
{
	m_PosVec.x = _fX;
	m_PosVec.y = _fY;
}
float CGameEntity::GetX()
{
	return(m_PosVec.x);
}
float CGameEntity::GetY()
{
	return(m_PosVec.y);
}
	
void CGameEntity::SetRotation(float _fRotation)
{
	m_fRotation = _fRotation;
}

float CGameEntity::GetRotation()
{
	return(m_fRotation);
}

void CGameEntity::SetVelocity(float _fVelocityX, float _fVelocityY)
{
	m_MoveVec.x = _fVelocityX;
	m_MoveVec.y = _fVelocityY;
}
void CGameEntity::AddVelocity(float _fVelocityX, float _fVelocityY)
{
	m_MoveVec.x += _fVelocityX;
	m_MoveVec.y += _fVelocityY;
}
float CGameEntity::GetVelocityX()
{
	return(m_MoveVec.x);

}
float CGameEntity::GetVelocityY()
{
	return(m_MoveVec.y);
}

D3DXVECTOR2* CGameEntity::GetPosition()
{
	return(&m_PosVec);
}

D3DXVECTOR2* CGameEntity::GetVelocity()
{
	return(&m_MoveVec);
}


C2DBoundingBox* CGameEntity::GetBoundingBox()
{
	return(&m_BoundingBox);
}


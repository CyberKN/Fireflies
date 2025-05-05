// Library Includes

// Local Includes

// This include
#include "Explosion.h"
#include "Game.h"

// Constants

const float k_fForce = 30;

// Static Variables

// Static Function Prototypes

// Implementation

/**
* Constructor
*/
CExplosion::CExplosion()
{
	m_fLifeTime = 0;
	m_bDead = false;
}

/**
* Destructor
*/
CExplosion::~CExplosion()
{

}

/**
* Initialises the explosion
*/
void CExplosion::Initialise()
{
	m_Sprite.Initialise(SPRITE_Firefly, 0);
	m_fLifeTime = 0;
	m_BoundingBox.SetSize(15, 15);
	m_bDead = false;
}

/**
* Processes the Explosion
* @param _fDeltaTick - the amount of time that has elapsed since the last frame
*/
void CExplosion::Process(float _fDeltaTick)
{
	m_Sprite.SetScaleX(m_Sprite.GetScaleX() + _fDeltaTick*5);
	m_Sprite.SetScaleY(m_Sprite.GetScaleY() + _fDeltaTick*5);


	m_fLifeTime += _fDeltaTick;
}

/**
* Applies the Explosive force to all nearby units
*/
void CExplosion::ApplyForce()
{
	unsigned int iVecSize = CGame::GetInstance().GetSession()->GetUnitManager()->GetUnitTotal();

	for(unsigned int i = 0; i < iVecSize; ++i)
	{
		CUnit* pUnit = CGame::GetInstance().GetSession()->GetUnitManager()->GetUnit(i);

		if(pUnit->GetBoundingBox()->CircleCollsionCheck(&m_BoundingBox))
		{
			D3DXVECTOR2 vVelocity = m_PosVec - *pUnit->GetPosition();
			D3DXVec2Normalize(&vVelocity, &vVelocity);
			pUnit->AddVelocity(-vVelocity.x*k_fForce, -vVelocity.y*k_fForce);
		}
	}
}


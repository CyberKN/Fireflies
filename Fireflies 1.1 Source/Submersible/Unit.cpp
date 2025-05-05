// Library Includes

// Local Includes

// This include
#include "utils.h"
#include "Unit.h"
#include "Game.h"


// Constants

const float k_fFriendlyFieldSize = 5;
const float k_fEnemyFieldSize = 40;

const int k_iSpriteAlpha = 200;

// Static Variables

// Static Function Prototypes

// Implementation

/**
* Constructor
*/
CUnit::CUnit()
{
	m_bSelected = false;
	m_vContainerNodes[0] = 0;
	m_vContainerNodes[1] = 0;
	m_vContainerNodes[2] = 0;
	m_vContainerNodes[3] = 0;
	m_bAlive = true;
	m_vContainerNodesEnemy[0] = 0;
	m_vContainerNodesEnemy[1] = 0;
	m_vContainerNodesEnemy[2] = 0;
	m_vContainerNodesEnemy[3] = 0;
	m_UnitState = US_Dead;
	m_vTarget.x = 99999;
}

/**
* Destructor
*/
CUnit::~CUnit()
{
	m_pLockedUnit = 0;
}

/**
* Initialises the Unit
*/
void CUnit::Initialise()
{
	m_Sprite.Initialise(SPRITE_Firefly, 0.3f);
	m_Sprite.SetColor(k_iSpriteAlpha, 50, 100, 255);
	//m_Sprite.SetScaleX(0.1f);
	//m_Sprite.SetScaleY(0.1f);
	m_BoundingBox.SetSize(3, 3);
	m_PField.SetSize(k_fFriendlyFieldSize, k_fFriendlyFieldSize);
	m_EnemyPField.SetSize(k_fEnemyFieldSize, k_fEnemyFieldSize);


	ClearTarget();
	m_bAlive = true;
	m_pLockedUnit = 0;
	m_bDeathlocked = false;
	m_fTwinkleTimer = 0;
	m_fRange = 0;
	m_fAliveTime = 0;

	SetPosition(350, 350);
}

/**
* Process the Unit's movement
* @param _fDeltaTick - The Time that has elapsed since the last frame
*/
void CUnit::Process(float _fDeltaTick)
{
	if(m_bDeathlocked)
	{
		if(!m_pLockedUnit->IsDeathlocked() || !m_pLockedUnit->IsAlive())
		{
			m_bDeathlocked = false;
		}

		m_MoveVec = *GetPosition() - *m_pLockedUnit->GetPosition();
		if(D3DXVec2LengthSq(&m_MoveVec) < 50)
		{
			Kill();
			m_pLockedUnit->Kill();
			CGame::GetInstance().GetSession()->GetExplosionManager()->CreateExplosion(GetX(), GetY());	
			CGame::GetInstance().PlayGameSound(SOUNDID_UnitDeath);
		}
		else
		{
			D3DXVec2Normalize(&m_MoveVec, &m_MoveVec);

			m_MoveVec *= -100;
		}

	}
	else
	{
		if(HasTargetCoord())
		{
			D3DXVECTOR2 vDistToTarget = m_PosVec - m_vTarget;
			if(D3DXVec2LengthSq(&vDistToTarget) < 25/*(5*5)*/ && D3DXVec2LengthSq(&m_MoveVec) < 900/*(30*30)*/)
			{
				ClearTarget();
			}
			else
			{
				m_MoveVec -= (vDistToTarget)*_fDeltaTick;
			}

		}
		m_MoveVec *= 1-_fDeltaTick;

		if(D3DXVec2LengthSq(&m_MoveVec) > k_fMaxUnitSpeed*k_fMaxUnitSpeed)
		{
			D3DXVec2Normalize(&m_MoveVec, &m_MoveVec);
			m_MoveVec*= k_fMaxUnitSpeed;
		}
	}

	m_fTwinkleTimer += _fDeltaTick*5;

	m_fAlpha = 0.7f + (0.3f*sinf(m_fTwinkleTimer));

	m_Sprite.SetColor((int)(m_fAlpha*k_iSpriteAlpha), m_Sprite.GetRed(), m_Sprite.GetGreen(), m_Sprite.GetBlue());
	
	m_fAliveTime += _fDeltaTick;
	CGameEntity::Process(_fDeltaTick);
	m_PField.UpdatePosition(m_PosVec.x, m_PosVec.y);
	m_EnemyPField.UpdatePosition(m_PosVec.x, m_PosVec.y);
}

/**
* Sets the Unit's Target position
* @param _fX - Target X Coord
* @param _fY - Target Y Coord
*/
void CUnit::SetTarget(float _fX, float _fY)
{
	m_vTarget.x = _fX;
	m_vTarget.y = _fY;
}

/**
* Resets the Unit's container of wwhich nodes it intersects
*/
void CUnit::ResetContainers()
{
	m_vContainerNodes[0] = 0;
	m_vContainerNodes[1] = 0;
	m_vContainerNodes[2] = 0;
	m_vContainerNodes[3] = 0;

	m_vContainerNodesEnemy[0] = 0;
	m_vContainerNodesEnemy[1] = 0;
	m_vContainerNodesEnemy[2] = 0;
	m_vContainerNodesEnemy[3] = 0;

}

/**
* Adds a Node which contains the unit to the unit's container of Nodes (We need to go deeper)
* @param _pContainerNode -  A Pointer to the Node which contains the Unit.
* @return False if  more than four containers try to add the unit, as something is wrong.
*/
bool CUnit::AddContainer(CSpatialNode* _pContainerNode)
{
	for(unsigned int i = 0; i < 4; ++i)
	{
		if(!m_vContainerNodes[i])
		{
			m_vContainerNodes[i] = _pContainerNode;
			return(true);
		}
	}

	//There should never be more than 4 containers
	return(false);

}


/**
* Adds a Node which contains the unit to the unit's container of Nodes (We need to go deeper)
* @param _pContainerNode -  A Pointer to the Node which contains the Unit.
* @return False if  more than four containers try to add the unit, as something is wrong.
*/
bool CUnit::AddContainerEnemy(CSpatialNode* _pContainerNode)
{
	for(unsigned int i = 0; i < 4; ++i)
	{
		if(!m_vContainerNodesEnemy[i])
		{
			m_vContainerNodesEnemy[i] = _pContainerNode;
			return(true);
		}
	}

	//There should never be more than 4 containers
	return(false);

}

/**
* Checks if the node is matched with with this unit.
* @param _pContainerNode -  A Pointer to the Node which may contain the Unit.
* @return True if the node contaitns the Unit
*/
bool CUnit::IsMatchedWithContainer(CSpatialNode* _pContainerNode)
{
	for(unsigned int i = 0; i < 4; ++i)
	{
		if(m_vContainerNodes[i] == _pContainerNode)
		{
			return(true);
		}
	}

	//This Container does not already contain this node.
	return(false);
}

/**
* Checks if the node is matched with with this unit.
* @param _pContainerNode -  A Pointer to the Node which may contain the Unit.
* @return True if the node contaitns the Unit
*/
bool CUnit::IsMatchedWithContainerEnemy(CSpatialNode* _pContainerNode)
{
	for(unsigned int i = 0; i < 4; ++i)
	{
		if(m_vContainerNodesEnemy[i] == _pContainerNode)
		{
			return(true);
		}
	}

	//This Container does not already contain this node.
	return(false);
}


/**
* Applies a potential field velocity to the unit based on the coordinates of another unit
* @param _pUnit -  A Pointer to the Node which may contain the Unit.
* @param _bAllied - True if the other unit is allied with this unit
*/
void CUnit::ApplyPotentialField(CUnit* _pUnit, bool _bAllied)
{
	D3DXVECTOR2 vField = (*_pUnit->GetPosition()) - m_PosVec;
	float fLength = D3DXVec2Length(&vField);

	float fDistMultiplier = (k_fFriendlyFieldSize*2) - fLength;
	float fFieldPower = CGame::GetInstance().m_fDeltaTick * fDistMultiplier;

	if(_bAllied)
	{ 

		fDistMultiplier /= k_fFriendlyFieldSize;
		if(!_pUnit->HasTargetCoord())
		{
			fFieldPower *= fDistMultiplier*1;
		}
		else
		{
			fFieldPower *= fDistMultiplier*0.1f;
		}
		_pUnit->AddVelocity(vField.x*fFieldPower, vField.y*fFieldPower);
		AddVelocity(vField.x*-fFieldPower, vField.y*-fFieldPower);	
		
	}
	else
	{
		fDistMultiplier /= k_fFriendlyFieldSize;
		fFieldPower *= fDistMultiplier*10;
		_pUnit->AddVelocity(vField.x*-fFieldPower, vField.y*-fFieldPower);
		AddVelocity(vField.x*fFieldPower, vField.y*fFieldPower);
	}
}


/**
* Applies an orbital velocity to the unit if the unit is within a certain distance of the lantern
* @param _pLantern -  a pointer to the lantern object
* @param _fDeltaTick - time elapsed since the last frame
*/
void CUnit::ApplyLanternOrbitVelocity(CLantern* _pLantern, float _fDeltaTick)
{
	if(m_bAlive && !HasTargetCoord())
	{
		if(_pLantern->GetPlayerID() == m_PlayerID)
		{
			D3DXVECTOR2 vDist = *(_pLantern->GetPosition()) - m_PosVec;
			float fLength = D3DXVec2Length(&vDist);

			if(fLength < 100)
			{
				D3DXVec2Normalize(&vDist, &vDist);

				vDist *= _fDeltaTick*50;//* (fLength*0.01);

				float fAngleRadians = 0.875f;

				AddVelocity(vDist.x*cosf(fAngleRadians) - vDist.y*sinf(fAngleRadians),
							vDist.x*sinf(fAngleRadians) + vDist.y*cosf(fAngleRadians));

			}
		}
	}
}

/**
* Sets the unit's PlayerID, and set's it's sprite's colour appropriately
* @param _PlayerID -  PlayerID to set to the Unit
*/
void CUnit::SetPlayerID(EPlayerID _PlayerID)
{
	m_PlayerID = _PlayerID;

	if(m_PlayerID == PLAYER_1)
	{
		m_Sprite.SetColor(k_iSpriteAlpha, 0, 0, 255);
	}
	else if(m_PlayerID == PLAYER_2)
	{
		m_Sprite.SetColor(k_iSpriteAlpha, 255, 0, 0);
	}
	else if(m_PlayerID == PLAYER_3)
	{
		m_Sprite.SetColor(k_iSpriteAlpha, 0, 255, 0);
	}
}

/**
* Sets whether the unit is selected, and set's it's sprite's colour appropriately
* @param _b - Whether the unit is selected.
*/
void CUnit::SetSelected(bool _b)
{
	if(m_bSelected != _b)
	{
		m_bSelected = _b;

		if(m_bSelected)
		{
			m_Sprite.SetColor(255, m_Sprite.GetRed(), m_Sprite.GetGreen(), m_Sprite.GetBlue());
		}
		else
		{
			SetPlayerID(m_PlayerID);
		}
	}
	
}

/**
* Kills the unit
*/
void CUnit::Kill()
{
	m_bAlive = false;
	ClearTarget();
	
}

/**
* Checks if the unit has collided with a lantern. 
* @param _pLantern - The lantern to check against. 
*/
void CUnit::CheckLanternCollision(CLantern* _pLantern)
{
	if(m_bAlive)
	{
		if(m_vTarget && m_vTarget == *(_pLantern->GetPosition()))
		{
			if(m_BoundingBox.BoxCollsionCheck(_pLantern->GetBoundingBox()))
			{
				_pLantern->ApplyUnit(this);
			}
		}
	}
}

/**
* Locks the unit's movement to force it towards a nearby enemy.
* @param _pLantern - The lantern to check against. 
*/
void CUnit::DeathlockUnit(CUnit* _pUnit)
{
	if(m_bDeathlocked)
	{
		assert("Unit is already deathlocked!");
	}
	m_bDeathlocked = true;
	m_pLockedUnit = _pUnit;
}

/**
* Clears the Unit's current target, effectivly stopping it.
*/
void CUnit::ClearTarget()
{
	m_vTarget.x = 99999;
}


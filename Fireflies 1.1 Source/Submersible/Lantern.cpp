// Library Includes

// Local Includes

// This include
#include "Lantern.h"
#include "utils.h"
#include "Game.h"

// Constants

const float k_fSpawnTime = 0.5f;
const float k_fUnitEffect = 1.0f;
const float k_fNearbyUnitRadius = 100.f;
const float k_fOrbitalAngleRadians = D3DX_PI*0.4f;//0.875f;
const float k_fOrbitalSpeed = 30.f;

// Static Variables

// Static Function Prototypes

// Implementation


/*
*	Constructor
*/
CLantern::CLantern()
{
	m_fSpawnTimer = 0;
	m_PlayerID = PLAYER_N;
	m_fHealth = 0;
	m_bAligned = false;
	m_iLevel = 0;
	m_FriendlyUnitEffect = UE_Capture;
	m_fUpgradeStatus = 0;
	m_iUnitsSpawned = 0;
	m_iMaxLevel = 2;
	m_iNearbyUnitCount = 0;
	m_bFrontline = false;
	m_bSelected = false;
}

/*
*	Destructor
*/
CLantern::~CLantern()
{

}


/*
*	Initialises the Lantern
*/
void CLantern::Initialise(EPlayerID _PlayerID)
{
	m_Sprite.Initialise(SPRITE_Base1, 0.25f);
	m_Sprite2.Initialise(SPRITE_Base2, 0.25f);
	m_Sprite3.Initialise(SPRITE_Base3, 0.25f);
	m_vecSprites.push_back(&m_Sprite);
	m_vecSprites.push_back(&m_Sprite2);
	m_vecSprites.push_back(&m_Sprite3);

	m_OverSprite.Initialise(SPRITE_Hover, 0.1f);
	m_OverSprite.SetColor(150, 255, 255, 255);
		
	m_UpgradeSprite.Initialise(SPRITE_Hover, 0.1f);
	m_UpgradeSprite.SetColor(0, 255, 255, 255);

	m_HealthSprite.Initialise(SPRITE_Link, 1);
	m_BoundingBox.SetSize(15, 15);


	if(_PlayerID != PLAYER_N)
	{
		m_fHealth = 100;
		m_iLevel = 2;
		m_iMaxLevel = 3;
		SetNewEffect(UE_UpgradeTwo);
		m_bFrontline = true;
	}
	else
	{
		m_UpgradeSprite.SetScaleX(2);
		m_UpgradeSprite.SetScaleY(2);

	}

	SetPlayerID(_PlayerID);
			

}

void CLantern::Draw()
{
	SetPlayerID(m_PlayerID);

	
	m_UpgradeSprite.TranslateAbsolute(m_PosVec.x, m_PosVec.y);
	m_UpgradeSprite.Draw();
	
	m_OverSprite.TranslateAbsolute(m_PosVec.x, m_PosVec.y);
	m_OverSprite.Draw();

	for(int i = m_iMaxLevel; i > 0; --i)
	{

		if(m_iLevel >= i)
		{
			m_vecSprites[i-1]->SetColor(m_Sprite.GetAlpha(), m_Sprite.GetRed(), m_Sprite.GetGreen(), m_Sprite.GetBlue());
		}
		else
		{
			m_vecSprites[i-1]->SetColor(255, 50, 50, 50);
		}
		
		m_vecSprites[i-1]->TranslateAbsolute(m_PosVec.x, m_PosVec.y);
		m_vecSprites[i-1]->Draw();
	}

}

void CLantern::Process(float _fDeltaTick)
{
	m_fSpawnTimer += _fDeltaTick;

	if(m_fSpawnTimer > k_fSpawnTime)
	{
		m_fSpawnTimer = 0;
		if(m_bAligned)
		{
			if(m_fHealth > 100 || m_PlayerID != PLAYER_N)
			{
				SpawnUnits();
			}
		}
	}

	DetermineCurrentEffect();

	CGameEntity::Process(_fDeltaTick);

	D3DXVECTOR2 vDist;
	CUnit* pUnit = 0;
	float fMaxAngle;

	//Apply Orbital Velocity
	for(unsigned int k = 0; k < m_iNearbyUnitCount; ++k)
	{
		pUnit = m_vecNearbyUnits[k];

		if(pUnit->IsAlive() && !pUnit->HasTargetCoord())
		{
			if(m_PlayerID == pUnit->GetPlayerID() && m_bAligned == true)
			{
				vDist = m_PosVec - *(pUnit->GetPosition());

				float fLength = D3DXVec2Length(&vDist);

				if(fLength > 50)
				{
			
					D3DXVec2Normalize(&vDist, &vDist);

					vDist *= _fDeltaTick*k_fOrbitalSpeed;//* (fLength*0.01);

					fMaxAngle = (50 - (fLength-50)) * 0.02f * k_fOrbitalAngleRadians;

					pUnit->AddVelocity(vDist.x*cosf(fMaxAngle) - vDist.y*sinf(fMaxAngle),
								vDist.x*sinf(fMaxAngle) + vDist.y*cosf(fMaxAngle));
				}
				else
				{
					D3DXVec2Normalize(&vDist, &vDist);

					vDist *= _fDeltaTick*k_fOrbitalSpeed;//* (fLength*0.01);

					fMaxAngle = k_fOrbitalAngleRadians;

					pUnit->AddVelocity(vDist.x*cosf(fMaxAngle) - vDist.y*sinf(fMaxAngle),
								vDist.x*sinf(fMaxAngle) + vDist.y*cosf(fMaxAngle));

				}
				
			}
		}
		//Also do Collision Checks
		pUnit->CheckLanternCollision(this);
	}

	//This re-ording of functions fixes that horrible bug we just had, where units were being killed and reassigned
	//after they had been added to the nearby list. I Think.
	RepopulateNearbyUnitList();


	//Is this Lantern on the frontline?
	CheckIfFrontlineLantern();


	//Update Sprite
	SetPlayerID(m_PlayerID);

	//update the upgrade flare sprite
	if(m_UpgradeSprite.GetScaleX() < 2)
	{
		m_UpgradeSprite.SetScaleX(m_UpgradeSprite.GetScaleX() + _fDeltaTick*3);
		m_UpgradeSprite.SetScaleY(m_UpgradeSprite.GetScaleY() + _fDeltaTick*3);

		if(m_UpgradeSprite.GetScaleX() > 2)
		{
			m_UpgradeSprite.SetScaleX(2);
			m_UpgradeSprite.SetScaleY(2);
		}

		int iAlpha = (int)((m_UpgradeSprite.GetScaleX()*0.5f)*255);
		iAlpha = 255 - iAlpha;
		m_UpgradeSprite.SetColor(iAlpha, m_Sprite.GetRed(), m_Sprite.GetGreen(), m_Sprite.GetBlue());
	}

	//Update Hover Sprite
	if(m_bSelected)
	{
		float fScale = 0.2f + 0.1f*m_iMaxLevel;
		m_OverSprite.SetScaleX(m_OverSprite.GetScaleX() + _fDeltaTick*3);
		m_OverSprite.SetScaleY(m_OverSprite.GetScaleY() + _fDeltaTick*3);
		if(m_OverSprite.GetScaleX() > fScale)
		{
			m_OverSprite.SetScaleX(fScale);
			m_OverSprite.SetScaleY(fScale);
		}
	}
	else
	{
		if(m_OverSprite.GetScaleX() > 0.1f)
		{
			m_OverSprite.SetScaleX(m_OverSprite.GetScaleX() - _fDeltaTick*3);
			m_OverSprite.SetScaleY(m_OverSprite.GetScaleY() - _fDeltaTick*3);
		}
	}
	
}

void CLantern::CheckIfFrontlineLantern()
{
	m_bFrontline = false;

	if(m_bAligned)
	{
		CLanternManager* pLanternManager = CGame::GetInstance().GetSession()->GetLanternManager();
		unsigned int iLanternTotal = pLanternManager->GetLanternTotal();
		CLantern* pAlliedLantern;
		CLantern* pEnemyLantern;
		D3DXVECTOR2 vDist;
		D3DXVECTOR2 vAllyDist;
		float fSquareDistance;
		float fSquareAllyDistance;

		for(unsigned int i = 0; i < iLanternTotal && m_bFrontline == false; ++i)
		{
			pEnemyLantern = pLanternManager->GetLantern(i);
			if(pEnemyLantern->GetPlayerID() == m_PlayerID)
			{
				continue;
			}

			vDist = *(GetPosition()) - *(pEnemyLantern->GetPosition());
			fSquareDistance = D3DXVec2LengthSq(&vDist);

			for(unsigned int k = 0; k < iLanternTotal; ++k)
			{
				m_bFrontline = true;
				pAlliedLantern = pLanternManager->GetLantern(k);

				if(pAlliedLantern == this || pAlliedLantern->GetPlayerID() != m_PlayerID || !pAlliedLantern->IsAligned())
				{
					continue;
				}

				vAllyDist = *(pAlliedLantern->GetPosition()) - *(pEnemyLantern->GetPosition());
				fSquareAllyDistance = D3DXVec2LengthSq(&vAllyDist);
				if(fSquareAllyDistance < fSquareDistance)
				{
					m_bFrontline = false;
					break;
				}
			}
		}
	}

}

void CLantern::SpawnUnits()
{

	float x = 0;
	float y = 0;

	while(x == 0 && y == 0)
	{
		x = RandFloat(-1, 1);
		y = RandFloat(-1, 1);
	}

	D3DXVECTOR2 vInitMovement = D3DXVECTOR2((float)x, (float)y);
	D3DXVec2Normalize(&vInitMovement, &vInitMovement);
	vInitMovement *= RandFloat(30, k_fMaxUnitSpeed); 

	if(m_iLevel > 0)
	{
		++m_iUnitsSpawned;
		CUnit* newUnit = CGame::GetInstance().GetSession()->GetUnitManager()->GetNewUnit();
		newUnit->Initialise();
		newUnit->SetPlayerID(m_PlayerID);
		newUnit->SetVelocity(vInitMovement.x, vInitMovement.y);
		newUnit->SetPosition(m_PosVec.x, m_PosVec.y);
	}

	if(m_iLevel > 2)
	{
		++m_iUnitsSpawned;
		++m_iUnitsSpawned;
		D3DXVECTOR2 vInitMovement2;
		float fThird = 2.07f;

		vInitMovement2.x = vInitMovement.x*cosf(fThird) - vInitMovement.y*sinf(fThird);
		vInitMovement2.y = vInitMovement.x*sinf(fThird) + vInitMovement.y*cosf(fThird);

		CUnit* newUnit = CGame::GetInstance().GetSession()->GetUnitManager()->GetNewUnit();
		newUnit->Initialise();
		newUnit->SetPlayerID(m_PlayerID);
		newUnit->SetVelocity(vInitMovement2.x, vInitMovement2.y);
		newUnit->SetPosition(m_PosVec.x, m_PosVec.y);

		D3DXVECTOR2 vInitMovement3;
		vInitMovement3.x = vInitMovement2.x*cosf(fThird) - vInitMovement2.y*sinf(fThird);
		vInitMovement3.y = vInitMovement2.x*sinf(fThird) + vInitMovement2.y*cosf(fThird);

		CUnit* newUnit2 = CGame::GetInstance().GetSession()->GetUnitManager()->GetNewUnit();
		newUnit2->Initialise();
		newUnit2->SetPlayerID(m_PlayerID);
		newUnit2->SetVelocity(vInitMovement3.x, vInitMovement3.y);
		newUnit2->SetPosition(m_PosVec.x, m_PosVec.y);
	}
	else if(m_iLevel > 1)
	{
		++m_iUnitsSpawned;
		CUnit* newUnit = CGame::GetInstance().GetSession()->GetUnitManager()->GetNewUnit();
		newUnit->Initialise();
		newUnit->SetPlayerID(m_PlayerID);
		newUnit->SetVelocity(-vInitMovement.x, -vInitMovement.y);
		newUnit->SetPosition(m_PosVec.x, m_PosVec.y);
	}


}

void CLantern::DrawHealthBarSprite()
{
	if(m_PlayerID == PLAYER_N)
	{
		m_Sprite.SetColor(0, 200, 200, 200);
	}
	else if(m_PlayerID == PLAYER_1)
	{
		m_HealthSprite.SetColor(255, 0, 0, 255);
	}
	else if(m_PlayerID == PLAYER_2)
	{
		m_HealthSprite.SetColor(255, 255, 0, 0);
	}
	else if(m_PlayerID == PLAYER_3)
	{
		m_HealthSprite.SetColor(255, 0, 255, 0);
	}


	m_HealthSprite.SetRotate(0.5f*D3DX_PI);
	m_HealthSprite.TranslateAbsolute(m_PosVec.x, m_PosVec.y-50);
	m_HealthSprite.SetScaleY(m_fHealth*0.002f);
	m_HealthSprite.SetScaleX(0.03f);
	m_HealthSprite.Draw();

	m_HealthSprite.TranslateAbsolute(m_PosVec.x, m_PosVec.y-65);
	m_HealthSprite.SetScaleY(m_fUpgradeStatus*0.002f);
	m_HealthSprite.SetScaleX(0.03f);
	m_HealthSprite.Draw();
}


void CLantern::ApplyUnit(CUnit* _pUnit)
{
	if(m_iLevel == 3 && _pUnit->GetPlayerID() == m_PlayerID && m_fHealth == 100)
	{
		return;
	}

	if(m_PlayerID == PLAYER_N)
	{
		SetPlayerID(_pUnit->GetPlayerID());
	}

	if(_pUnit->GetPlayerID() == m_PlayerID)
	{
		if(m_fHealth == 100 && _pUnit->GetLanternEffect() != GetUnitEffect())
		{
			return;
		}
		else
		{
			if(m_fHealth < 100)
			{
				m_fHealth += k_fUnitEffect;
				if(m_fHealth >= 100)
				{
					m_fHealth = 100;
					if(m_iLevel == 0)
					{
						SetLevel(1);
						CGame::GetInstance().PlayGameSound(SOUNDID_PowerUp);
						m_UpgradeSprite.SetScaleX(0);
						m_UpgradeSprite.SetScaleY(0);
						SetPlayerID(m_PlayerID);
						DetermineCurrentEffect();
					}
				}
			}
			else if(m_iLevel < GetMaxLevel())
			{
				m_fUpgradeStatus += k_fUnitEffect;
				if(m_fUpgradeStatus >= 100)
				{
					if(GetUnitEffect() == UE_UpgradeOne)
					{
						SetLevel(2);
						m_fUpgradeStatus = 0;
						DetermineCurrentEffect();
						
						m_UpgradeSprite.SetScaleX(0);
						m_UpgradeSprite.SetScaleY(0);
						
						
						CGame::GetInstance().PlayGameSound(SOUNDID_PowerUp);
					}
					else if(GetUnitEffect() == UE_UpgradeTwo)
					{
						SetLevel(3);
						m_fUpgradeStatus = 0;
						DetermineCurrentEffect();
						
						CGame::GetInstance().PlayGameSound(SOUNDID_PowerUp);
						m_UpgradeSprite.SetScaleX(0);
						m_UpgradeSprite.SetScaleY(0);
					}
				}
			}
			else
			{
				return;
			}
		}
	}
	else
	{
		m_fHealth -= k_fUnitEffect;
	}

	if(m_fHealth <= 0)
	{
		if(m_bAligned)
		{
			CGame::GetInstance().PlayGameSound(SOUNDID_PowerDown);
		}
		SetPlayerID(PLAYER_N);
		m_bAligned = false;
		SetLevel(0);
		m_fUpgradeStatus = 0;
	}

	_pUnit->Kill();
	
}

void CLantern::SetPlayerID(EPlayerID _PlayerID)
{
	m_PlayerID = _PlayerID;

	if(m_PlayerID == PLAYER_N || (m_fHealth < 100 && !m_bAligned))
	{
		m_Sprite.SetColor(255, 200, 200, 200);
	}
	else if(m_PlayerID == PLAYER_1)
	{
		m_Sprite.SetColor(255, 0, 0, 255);
		m_bAligned = true;
	}
	else if(m_PlayerID == PLAYER_2)
	{
		m_Sprite.SetColor(255, 255, 0, 0);
		m_bAligned = true;
	}
	else if(m_PlayerID == PLAYER_3)
	{
		m_Sprite.SetColor(255, 0, 255, 0);
		m_bAligned = true;
	}
}

void CLantern::SetSelected(bool _b)
{
	m_bSelected = _b;
	
}

unsigned int CLantern::GetNearbyFriendlyUnitTotal(EPlayerID _PlayerID, bool _bIdle)
{
	CUnit* pUnit = 0;
	unsigned int iNearbyUnits = 0;

	for(unsigned int k = 0; k < m_iNearbyUnitCount; ++k)
	{
		pUnit = m_vecNearbyUnits[k];

		if(pUnit->IsAlive() && !pUnit->HasTargetCoord())
		{
			if(_bIdle)
			{
				if(!pUnit->HasTargetCoord() && _PlayerID == pUnit->GetPlayerID())
				{
					++iNearbyUnits;
				}
			}
			else if(_PlayerID == pUnit->GetPlayerID())
			{
				++iNearbyUnits;
			}
		}

	}

	return(iNearbyUnits);
}


unsigned int CLantern::GetNearbyEnemyUnitTotal(EPlayerID _PlayerID)
{
	CUnit* pUnit = 0;
	unsigned int iNearbyUnits = 0;

	for(unsigned int k = 0; k < m_iNearbyUnitCount; ++k)
	{
		pUnit = m_vecNearbyUnits[k];

		if(pUnit->IsAlive())
		{
			if(_PlayerID != pUnit->GetPlayerID())
			{
				++iNearbyUnits;
			}
		}

	}

	return(iNearbyUnits);
}

void CLantern::OrderUnitsToTarget(EPlayerID _PlayerID, CLantern* _pTargetLantern)
{
	CUnit* pUnit = 0;
	
	for(unsigned int k = 0; k < m_iNearbyUnitCount; ++k)
	{
		pUnit = m_vecNearbyUnits[k];

		if(pUnit->IsAlive() && !pUnit->HasTargetCoord())
		{
			if(_PlayerID == pUnit->GetPlayerID())
			{
				pUnit->SetTarget(_pTargetLantern->GetX(), _pTargetLantern->GetY());			
				_pTargetLantern->SetupUnitTarget(pUnit);
			}
		}
	}
}

void CLantern::OrderUnitsToTargetSoft(EPlayerID _PlayerID, CLantern* _pTargetLantern)
{
	CUnit* pUnit = 0;
	
	for(unsigned int k = 0; k < m_iNearbyUnitCount; ++k)
	{
		pUnit = m_vecNearbyUnits[k];

		if(pUnit->IsAlive() && !pUnit->HasTargetCoord())
		{
			if(_PlayerID == pUnit->GetPlayerID())
			{
				pUnit->SetTarget(_pTargetLantern->GetX(), _pTargetLantern->GetY());
				_pTargetLantern->SetupUnitTarget(pUnit);
				pUnit->SetLanternEffect(UE_Ignore);
			}
		}
	}
}

CLantern* CLantern::FindNearbyUnclaimedBase(EPlayerID _PlayerID)
{
	CLanternManager* pLanternManager = CGame::GetInstance().GetSession()->GetLanternManager();
	CLantern* pLantern = 0;
	CLantern* pBestLantern = 0;
	float fBestDistanceSquared = 0;

	float fDistSquared = 0;
	D3DXVECTOR2 vDist;

	unsigned int iRequiredUnitsForCapture = 0;

	for(unsigned int i = 0; i < pLanternManager->GetLanternTotal(); ++i)
	{
		pLantern = pLanternManager->GetLantern(i);

		if(!pLantern->IsAligned())
		{
			if(m_PlayerID == pLantern->GetPlayerID())
			{
				iRequiredUnitsForCapture = 110 - (int)pLantern->GetHealth();
			}
			else
			{
				iRequiredUnitsForCapture = 110 + (int)pLantern->GetHealth();
			}

			if(GetNearbyFriendlyUnitTotal(m_PlayerID, true) < iRequiredUnitsForCapture)
			{
				continue;
			}

			vDist = m_PosVec - *(pLantern->GetPosition());
			fDistSquared = D3DXVec2LengthSq(&vDist);

			if(!pBestLantern || fDistSquared < fBestDistanceSquared)
			{
				pBestLantern = pLantern;
				fBestDistanceSquared = fDistSquared;
			}
		}
	}


	//now, also consider any valid lanterns where the difference in distance is less than 20%.
	std::vector<CLantern*> vecPossibleLanterns;

	if(pBestLantern)
	{
		vecPossibleLanterns.push_back(pBestLantern);
		float fBestDistance = sqrtf(fBestDistanceSquared);

		for(unsigned int i = 0; i < pLanternManager->GetLanternTotal(); ++i)
		{
			pLantern = pLanternManager->GetLantern(i);

			if(!pLantern->IsAligned() && pLantern != pBestLantern)
			{
				if(m_PlayerID == pLantern->GetPlayerID())
				{
					iRequiredUnitsForCapture = 110 - (int)pLantern->GetHealth();
				}
				else
				{
					iRequiredUnitsForCapture = 110 + (int)pLantern->GetHealth();
				}

				if(GetNearbyFriendlyUnitTotal(m_PlayerID, true) < iRequiredUnitsForCapture)
				{
					continue;
				}

				vDist = m_PosVec - *(pLantern->GetPosition());
				fDistSquared = D3DXVec2LengthSq(&vDist);

				if(sqrtf(fDistSquared)*0.8f <= fBestDistance)
				{
					vecPossibleLanterns.push_back(pLantern);
				}
			}
		}

		unsigned int iRand = vecPossibleLanterns.size();
		unsigned int iRandomLantern;
		for(unsigned int  i = 0; i < 10; ++i)
		{
			iRandomLantern = rand() % iRand;
		}

		pBestLantern = vecPossibleLanterns[iRandomLantern];
	}

	return(pBestLantern);

}
CLantern* CLantern::FindNearbyEnemyBase(EPlayerID _PlayerID)
{
	CLanternManager* pLanternManager = CGame::GetInstance().GetSession()->GetLanternManager();
	CLantern* pLantern = 0;
	CLantern* pBestLantern = 0;
	float fBestDistanceSquared = 0;

	float fDistSquared = 0;
	D3DXVECTOR2 vDist;

	unsigned int iRequiredUnitsForCapture = 0;

	for(unsigned int i = 0; i < pLanternManager->GetLanternTotal(); ++i)
	{
		pLantern = pLanternManager->GetLantern(i);

		if(pLantern->GetPlayerID() != m_PlayerID && pLantern->IsAligned())
		{
			
			iRequiredUnitsForCapture = 100 + (int)pLantern->GetHealth() + (pLantern->GetLevel()*30);
			
			if(GetNearbyFriendlyUnitTotal(m_PlayerID, true) < iRequiredUnitsForCapture)
			{
				continue;
			}

			vDist = m_PosVec - *(pLantern->GetPosition());
			fDistSquared = D3DXVec2LengthSq(&vDist);

			if(!pBestLantern || (fDistSquared < fBestDistanceSquared && pBestLantern->GetLevel() >= pLantern->GetLevel()))
			{
				pBestLantern = pLantern;
				fBestDistanceSquared = fDistSquared;
			}
		}
	}

	//now, also consider any valid lanterns where the difference in distance is not relevant.
	std::vector<CLantern*> vecPossibleLanterns;

	if(pBestLantern)
	{
		vecPossibleLanterns.push_back(pBestLantern);
		float fBestDistance = sqrtf(fBestDistanceSquared);

		for(unsigned int i = 0; i < pLanternManager->GetLanternTotal(); ++i)
		{
			pLantern = pLanternManager->GetLantern(i);

			if(pLantern->GetPlayerID() != m_PlayerID && pLantern->IsAligned() && pLantern != pBestLantern)
			{
			
				iRequiredUnitsForCapture = 100 + (int)pLantern->GetHealth() + (pLantern->GetLevel()*30);
			
				if(GetNearbyFriendlyUnitTotal(m_PlayerID, true) < iRequiredUnitsForCapture)
				{
					continue;
				}

				vDist = m_PosVec - *(pLantern->GetPosition());
				fDistSquared = D3DXVec2LengthSq(&vDist);

				if(sqrtf(fDistSquared)*0.8f <= fBestDistance)
				{
					vecPossibleLanterns.push_back(pLantern);
				}
			}
		}

		unsigned int iRand = vecPossibleLanterns.size();
		unsigned int iRandomLantern;
		for(unsigned int  i = 0; i < 10; ++i)
		{
			iRandomLantern = rand() % iRand;
		}

		pBestLantern = vecPossibleLanterns[iRandomLantern];
	}

	return(pBestLantern);

}
bool CLantern::IsThisTargetAcceptableRisk(CLantern* _pTargetLantern)
{
	int iArmySize = GetNearbyFriendlyUnitTotal(m_PlayerID, true);

	int iTargetLevel = _pTargetLantern->GetLevel();

	if(iArmySize > iTargetLevel*150)
	{
		return(true);
	}

	return(false);
}

void CLantern::SetupUnitTarget(CUnit* _pUnit)
{
	_pUnit->SetLanternEffect(GetUnitEffect());
	if(GetPlayerID() != PLAYER_N && GetPlayerID() != _pUnit->GetPlayerID())
	{
		_pUnit->SetLanternEffect(UE_Capture);
	}
	else if(GetHealth() < 100)
	{
		if(IsAligned())
		{
			_pUnit->SetLanternEffect(UE_Heal);
		}
		else
		{
			_pUnit->SetLanternEffect(UE_Capture);
		}
	}
}

/*
* Sets the Lantern's new Unit-Lantern Relationship and stops any nearby friendly units currently seeking it (to prevent congestion)
*/
void CLantern::SetNewEffect(EUnitEffect _eEffect)
{	
	m_FriendlyUnitEffect = _eEffect;
}

CLantern* CLantern::GetNearbyBaseUnderAttack(EPlayerID _PlayerID)
{
	CLanternManager* pLanternManager = CGame::GetInstance().GetSession()->GetLanternManager();
	CLantern* pLantern = 0;
	CLantern* pBestLantern = 0;
	float fBestDistanceSquared = 0;

	float fDistSquared = 0;
	D3DXVECTOR2 vDist;
	int iFriendlyUnitsNearby = 0;
	int iEnemyUnitsNearby = 0;



	for(unsigned int i = 0; i < pLanternManager->GetLanternTotal(); ++i)
	{
		pLantern = pLanternManager->GetLantern(i);

		if(pLantern->GetPlayerID() == m_PlayerID && pLantern->IsAligned() && pLantern != this)
		{
			iFriendlyUnitsNearby = pLantern->GetNearbyFriendlyUnitTotal(m_PlayerID, false);
			iEnemyUnitsNearby = pLantern->GetNearbyEnemyUnitTotal(m_PlayerID);
			if(iEnemyUnitsNearby > iFriendlyUnitsNearby && pLantern->m_fHealth < 100)
			{
				vDist = m_PosVec - *(pLantern->GetPosition());
				fDistSquared = D3DXVec2LengthSq(&vDist);

				if(!pBestLantern || (fDistSquared < fBestDistanceSquared && pBestLantern->GetLevel() >= pLantern->GetLevel()))
				{
					pBestLantern = pLantern;
					fBestDistanceSquared = fDistSquared;
				}
			}
		}
	}

	return(pBestLantern);
}

void CLantern::AddNearbyUnitToList(CUnit* _pUnit)
{
	unsigned int iVectorSize = m_vecNearbyUnits.size();

	if(iVectorSize)
	{
		CUnit** PtrPtr = &m_vecNearbyUnits[0];

		//Find an empty pointer, and make it point to the unit.
		for(unsigned int i = 0; i < iVectorSize; ++i)
		{
			if(!*PtrPtr)
			{
				*PtrPtr = _pUnit;
				++m_iNearbyUnitCount;
			
				//We've found a pointer, stop searching.
				return;
			}

			PtrPtr++;
		}
	}

	//we didn't find an empty pointer, add one.
	m_vecNearbyUnits.push_back(_pUnit);
	++m_iNearbyUnitCount;
}


bool CLantern::IsFrontlineLantern()
{
	return(m_bFrontline);
}

CLantern* CLantern::GetNearbyFrontlineLantern()
{
	CLanternManager* pLanternManager = CGame::GetInstance().GetSession()->GetLanternManager();
	CLantern* pLantern = 0;
	CLantern* pBestLantern = 0;
	float fBestDistanceSquared = 0;

	float fDistSquared = 0;
	D3DXVECTOR2 vDist;



	for(unsigned int i = 0; i < pLanternManager->GetLanternTotal(); ++i)
	{
		pLantern = pLanternManager->GetLantern(i);

		if(pLantern->IsAligned() && pLantern->GetPlayerID() == m_PlayerID && pLantern->IsFrontlineLantern())
		{
			vDist = m_PosVec - *(pLantern->GetPosition());
			fDistSquared = D3DXVec2LengthSq(&vDist);

			if(!pBestLantern || fDistSquared < fBestDistanceSquared)
			{
				pBestLantern = pLantern;
				fBestDistanceSquared = fDistSquared;
			}
		}
	}

	return(pBestLantern);

}

void CLantern::PreventCongestion(CUnit* _pUnit)
{
	//if It's a friendly unit
	if(_pUnit->GetPlayerID() == m_PlayerID)
	{
		//if it's trying to get to me
		if(_pUnit->HasTargetCoord() && _pUnit->GetTargetCoord() == *(GetPosition()))
		{
			//if it's late to the party
			if(_pUnit->GetLanternEffect() != GetUnitEffect() || GetUnitEffect() == UE_None)
			{
				//tell it to stop trying already!
				_pUnit->ClearTarget();
			}
		}
	}
}

void CLantern::DetermineCurrentEffect()
{
	if(m_bAligned)
	{
		if(m_fHealth < 100)
		{
			SetNewEffect(UE_Heal);
		}
		else
		{
			if(m_iLevel == GetMaxLevel())
			{
				SetNewEffect(UE_None);
			}
			else if(m_iLevel == 1)
			{
				SetNewEffect(UE_UpgradeOne);
			}
			else
			{
				SetNewEffect(UE_UpgradeTwo);
			}
		}
	}
	else
	{
		SetNewEffect(UE_Capture);
	}
}

void CLantern::RepopulateNearbyUnitList()
{
	float fDistSquared = 0;
	float fMinDistSquared = k_fNearbyUnitRadius*k_fNearbyUnitRadius;
	D3DXVECTOR2 vDist;
	
	CUnit* pUnit = 0;
	unsigned int iUnitTotal = CGame::GetInstance().GetSession()->GetUnitManager()->GetUnitTotal();

	//Empty Unit List
	for(unsigned int i = 0; i < m_vecNearbyUnits.size(); ++i)
	{
		if(m_vecNearbyUnits[i])
		{
			m_vecNearbyUnits[i]->m_fRange = 0;
		}
		m_vecNearbyUnits[i] = 0;
	}
	m_iNearbyUnitCount = 0;

	//Get Nearby Units
	for(unsigned int k = 0; k < iUnitTotal; ++k)
	{
		pUnit = CGame::GetInstance().GetSession()->GetUnitManager()->GetUnit(k);

		if(pUnit->IsAlive())
		{
			vDist = m_PosVec - *(pUnit->GetPosition());

			fDistSquared = D3DXVec2Length(&vDist);
			if(fDistSquared < k_fNearbyUnitRadius)
			{
				PreventCongestion(pUnit);
				AddNearbyUnitToList(pUnit);
			}
		}
	}
}

void CLantern::Update()
{
	CGameEntity::Process(0);
}

void CLantern::SpawnInitUnits()
{
	int i = 0;
	if(m_iLevel == 1)
	{
		i = 90;
	}
	else if(m_iLevel == 2)
	{
		i = 45;
	}
	else if(m_iLevel == 3)
	{
		i = 30;
	}

	while(i > 0)
	{
		SpawnUnits();
		--i;
	}
}





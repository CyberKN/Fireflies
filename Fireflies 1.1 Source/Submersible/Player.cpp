// Library Includes

// Local Includes

// This include
#include "Player.h"
#include "Game.h"

// Constants

const int k_iUnitsRequiredForAIAggression = 100;

// Static Variables

// Static Function Prototypes

// Implementation

CPlayer::CPlayer()
{
	m_PlayerID = PLAYER_1;
	m_iCurrentUnitCount = 0;
	m_iSizeOfMyUnitsVec = 0;
	m_bIsHuman = true;
	m_iCurrentLantern = 0;
	m_pLanternManager = 0;
}

CPlayer::~CPlayer()
{
	EmptyUnitList();

}

void CPlayer::Initialise(EPlayerID _PlayerID,  bool _bIsHuman)
{
	m_PlayerID = _PlayerID;
	m_bIsHuman = _bIsHuman;
	m_pLanternManager = CGame::GetInstance().GetSession()->GetLanternManager();

}

void CPlayer::Process(float _fDeltaTick)
{
	if(!m_bIsHuman)
	{
		ProcessAI();
	}
}

void CPlayer::Draw()
{

}

void CPlayer::EmptyUnitList()
{
	for(unsigned int i = 0; i < m_iSizeOfMyUnitsVec; ++i)
	{
		m_vecMyUnits[i] = 0;
	}
	m_iCurrentUnitCount = 0;
}


void CPlayer::AddUnitToList(CUnit* _pUnit)
{
	//Find an empty pointer, and make it point to the unit.
	if(m_iSizeOfMyUnitsVec)
	{
		CUnit** PtrPtr = &m_vecMyUnits[0];

		for(unsigned int i = 0; i < m_iSizeOfMyUnitsVec; ++i)
		{		
			if(!*PtrPtr)
			{
				*PtrPtr = _pUnit;
				++m_iCurrentUnitCount;
			
				//We've found a pointer, stop searching.
				return;
			}
			PtrPtr++;
		}
	}

	//we didn't find an empty pointer, add one.
	m_vecMyUnits.push_back(_pUnit);
	++m_iSizeOfMyUnitsVec;
	++m_iCurrentUnitCount;
}

unsigned int CPlayer::GetUnitTotal()
{
	return(m_iCurrentUnitCount);
}

CUnit* CPlayer::GetUnit(unsigned int _i)
{
	return(m_vecMyUnits[_i]);
}

/*
 * Processes tha AI for this Frame
 */
void CPlayer::ProcessAI()
{
	//Get the Next Lantern in the list
	++m_iCurrentLantern;
	if(m_iCurrentLantern >= m_pLanternManager->GetLanternTotal())
	{
		m_iCurrentLantern = 0;
	}
	CLantern* pLantern = m_pLanternManager->GetLantern(m_iCurrentLantern);
	CLantern* pTargetLantern = 0;

	//Do I Own This Lantern?
	if(pLantern->GetPlayerID() == m_PlayerID && pLantern->IsAligned())
	{
		//Is this Lantern damaged or only partially upgraded?
		if(pLantern->GetHealth() < 100 || pLantern->GetUpgradeStatus() > 0)
		{
			//because one unit at a time looks sorta lame
			if(pLantern->GetNearbyFriendlyUnitTotal(m_PlayerID, true) > 10)
			{
				pLantern->OrderUnitsToTarget(m_PlayerID, pLantern);
				//End Turn
				return;
			}
		}

		//Are there any nearby allied Lanterns under attack I can send aid to?
		pTargetLantern = pLantern->GetNearbyBaseUnderAttack(m_PlayerID);
		if(pTargetLantern)
		{
			if(pLantern->GetNearbyFriendlyUnitTotal(m_PlayerID, true) >= 40)
			{
				pLantern->OrderUnitsToTarget(m_PlayerID, pTargetLantern);
				//End Turn
				return;
			}
		}

		//Is this NOT a Frontline Lantern?
		if(!pLantern->IsFrontlineLantern())
		{
			//Can this base be upgraded?
			if(pLantern->GetLevel() < pLantern->GetMaxLevel())
			{
				if(pLantern->GetNearbyFriendlyUnitTotal(m_PlayerID, true) >= 10)
				{
					pLantern->OrderUnitsToTarget(m_PlayerID, pLantern);
				}

			}
			//if not, reinforce nearest frontline Lantern.
			else
			{
				if(pLantern->GetNearbyFriendlyUnitTotal(m_PlayerID, true) >= 20)
				{
					CLantern* pFrontlineLantern = pLantern->GetNearbyFrontlineLantern();
					if(pFrontlineLantern)
					{
						pLantern->OrderUnitsToTargetSoft(m_PlayerID, pFrontlineLantern);
					}
				}
			}
				//End Turn
				return;
		}

		//Are there any nearby unclaimed Lanterns?
		pTargetLantern = pLantern->FindNearbyUnclaimedBase(m_PlayerID);
		if(pTargetLantern)
		{
			pLantern->OrderUnitsToTarget(m_PlayerID, pTargetLantern);
			//End Turn
			return;
		}

		//Can This Lantern be Upgraded?
		if(pLantern->GetLevel() < pLantern->GetMaxLevel())
		{
			if(pLantern->GetNearbyFriendlyUnitTotal(m_PlayerID, true) >= 110)
			{
				pLantern->OrderUnitsToTarget(m_PlayerID, pLantern);
				//End Turn
				return;
			}
		}

		//Are there any nearby enemy Lanterns?
		pTargetLantern = pLantern->FindNearbyEnemyBase(m_PlayerID);
		if(pTargetLantern)
		{
			pLantern->OrderUnitsToTarget(m_PlayerID, pTargetLantern);
			//End Turn
			return;

		}
	}
	//or Is It Unclaimed/Hostile?
	else if(pLantern->IsAligned() == false || pLantern->GetPlayerID() != m_PlayerID)
	{
		//Send any nearby Units of Mine to start capturing it.
		pLantern->OrderUnitsToTarget(m_PlayerID, pLantern);
	}
}

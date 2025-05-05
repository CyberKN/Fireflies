// Library Includes

// Local Includes

// This include
#include "PlayerManager.h"
#include "Game.h"

// Constants

// Static Variables

// Static Function Prototypes

// Implementation

CPlayerManager::CPlayerManager()
{

}

CPlayerManager::~CPlayerManager()
{
	for(unsigned int i = 0; i < m_vecPlayers.size(); ++i)
	{
		delete m_vecPlayers[i];
		m_vecPlayers[i] = 0;
	}

}

void CPlayerManager::Initialise()
{
	CPlayer* pPlayer = 0;

	pPlayer = new CPlayer;
	pPlayer->Initialise(PLAYER_1, true);
	m_vecPlayers.push_back(pPlayer);

	pPlayer = new CPlayer;
	pPlayer->Initialise(PLAYER_2);
	m_vecPlayers.push_back(pPlayer);

	pPlayer = new CPlayer;
	pPlayer->Initialise(PLAYER_3);
	m_vecPlayers.push_back(pPlayer);

}
void CPlayerManager::SortUnits()
{
	for(unsigned int i = 0; i < m_vecPlayers.size(); ++i)
	{
		m_vecPlayers[i]->EmptyUnitList();
	}

	CUnitManager* pUnitManager = CGame::GetInstance().GetSession()->GetUnitManager();
	unsigned int iUnitTotal = pUnitManager->GetUnitTotal();
	CUnit* pUnit = 0;

	for(unsigned int z = 0; z < iUnitTotal; ++z)
	{
		pUnit = pUnitManager->GetUnit(z);
		if(pUnit->IsAlive())
		{
			m_vecPlayers[static_cast<int>(pUnit->GetPlayerID())]->AddUnitToList(pUnit);
		}
	}
	
}
void CPlayerManager::Process(float _fDeltaTick)
{
	SortUnits();

	for(unsigned int i = 0; i < m_vecPlayers.size(); ++i)
	{
		m_vecPlayers[i]->Process(_fDeltaTick);
	}

}

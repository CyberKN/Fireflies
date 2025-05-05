#pragma once

#if !defined(__Player_H__)
#define __Player_H__

// Library Includes
#include "Unit.h"

// Local Includes


// Types

// Constants

// Prototypes

class CLanternManager;

class CPlayer
{
// Member Functions
public:
	CPlayer();
	~CPlayer();
	void Initialise(EPlayerID _PlayerID, bool _bIsHuman = false);
	void Process(float _fDeltaTick);
	void Draw();
	void EmptyUnitList();
	void AddUnitToList(CUnit* _pUnit);
	unsigned int GetUnitTotal();
	CUnit* GetUnit(unsigned int _i);
	void ProcessAI();


protected:

private:

// Member Variables
public:
	


protected:

	EPlayerID m_PlayerID;
	std::vector<CUnit*> m_vecMyUnits;
	unsigned int m_iSizeOfMyUnitsVec;
	unsigned int m_iCurrentUnitCount;
	bool m_bIsHuman;
	unsigned int m_iCurrentLantern;
	CLanternManager* m_pLanternManager;
	
	


private:

};

#endif // __Player_H__

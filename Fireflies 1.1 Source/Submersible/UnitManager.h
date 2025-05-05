#pragma once

#if !defined(__UnitManager_H__)
#define __UnitManager_H__

// Library Includes
#include "utils.h"
#include "SpriteDataShell.h"

// Local Includes

// Types

// Constants

// Prototypes

class CUnit;



class CUnitManager
{
// Member Functions
public:
	CUnitManager();
	~CUnitManager();
	void Initialise();
	void Process(float _fDeltaTick);
	void Draw();
	void DrawHighlight();
	void AddUnit(CUnit* _pUnit);
	CUnit* GetUnit(int _iIndex);
	unsigned int GetUnitTotal();
	CUnit* GetNewUnit();

protected:

private:

// Member Variables
public:

protected:

private:
	std::vector<CUnit*> m_vecAllUnits;
	CSpriteDataShell m_HighlighterSprite;

};

#endif // __UnitManager_H__

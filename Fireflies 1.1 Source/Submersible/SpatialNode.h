#pragma once

#if !defined(__SpatialNode_H__)
#define __SpatialNode_H__

// Library Includes

#include "utils.h"
#include "TextBox.h"
// Local Includes

// Types

// Constants

// Prototypes

class C2DBoundingBox;
class CUnit;


class CSpatialNode
{
// Member Functions
public:
	CSpatialNode();
	~CSpatialNode();
	void Initialise(float _fX, float _fY, float _fSizeX, float _fSizeY);
	void AddUnit(CUnit* _pUnit);
	void Empty();
	void Draw();
	C2DBoundingBox* GetBoundingBox(){return(m_pBB);};

	unsigned int& GetUnitTotal();
	CUnit* GetUnit(unsigned int _i);

protected:

private:

// Member Variables
public:

protected:

	C2DBoundingBox* m_pBB;
	std::vector<CUnit*> m_vecUnits;
	unsigned int m_iUnitTotal;
	CTextBox TestBox;

private:

};

#endif // __SpatialNode_H__

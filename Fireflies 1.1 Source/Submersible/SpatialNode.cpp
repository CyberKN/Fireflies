// Library Includes

// Local Includes

// This include
#include "SpatialNode.h"
#include "2DBoundingBox.h"
#include "Unit.h"
#include "Game.h"

// Constants

// Static Variables

// Static Function Prototypes

// Implementation

CSpatialNode::CSpatialNode()
{
	m_iUnitTotal = 0;
}

CSpatialNode::~CSpatialNode()
{
	delete m_pBB;
	m_pBB = 0;
	Empty();
}

void CSpatialNode::Initialise(float _fX, float _fY, float _fSizeX, float _fSizeY)
{
	m_pBB = new C2DBoundingBox;
	m_pBB->SetSize(_fSizeX, _fSizeY);
	m_pBB->UpdatePosition(_fX, _fY);

	TestBox.Initialise(255, m_pBB->m_fX, m_pBB->m_fY + m_pBB->m_fHeight, 4, true, false, 1);
	TestBox.m_iBlue = RandInt(0, 255);
	TestBox.m_iGreen = RandInt(0, 255);
	TestBox.m_iRed = RandInt(0, 255);
}

void CSpatialNode::Draw()
{
	//TestBox.m_fX = CGame::GetInstance().m_Mouse.m_iMousePosX;
	//TestBox.m_fY = CGame::GetInstance().m_iWindowHeight - CGame::GetInstance().m_Mouse.m_iMousePosY;
	//TestBox.m_TextString = IntToString(m_vecUnits.size());
	//TestBox.Draw();
	m_pBB->Draw();
}

void CSpatialNode::AddUnit(CUnit* _pUnit)
{
	//_pUnit->m_Sprite.SetColor(TestBox.m_iAlpha, TestBox.m_iRed, TestBox.m_iGreen, TestBox.m_iBlue);
	m_vecUnits.push_back(_pUnit);
	++m_iUnitTotal;
}

void CSpatialNode::Empty()
{
	m_vecUnits.resize(0);
	m_iUnitTotal = 0;
}

unsigned int& CSpatialNode::GetUnitTotal()
{
	return(m_iUnitTotal);
}

CUnit* CSpatialNode::GetUnit(unsigned int _i)
{
	return(m_vecUnits[_i]);
}

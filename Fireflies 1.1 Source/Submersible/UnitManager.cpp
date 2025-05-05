// Library Includes

// Local Includes
#include "Unit.h"
// This include
#include "UnitManager.h"

// Constants

// Static Variables

// Static Function Prototypes

// Implementation

CUnitManager::CUnitManager()
{

}

CUnitManager::~CUnitManager()
{
	for(unsigned int i = 0; i < m_vecAllUnits.size(); ++i)
	{
		delete m_vecAllUnits[i];
		m_vecAllUnits[i] = 0;
	}

}

void CUnitManager::Initialise()
{
	m_HighlighterSprite.Initialise(SPRITE_Firefly, 0.1f);

}

void CUnitManager::Process(float _fDeltaTick)
{
	for(unsigned int i = 0; i < m_vecAllUnits.size(); ++i)
	{
		if(m_vecAllUnits[i]->IsAlive())
		{
			m_vecAllUnits[i]->Process(_fDeltaTick);
		}
	}
}

void CUnitManager::Draw()
{
	for(unsigned int i = 0; i < m_vecAllUnits.size(); ++i)
	{
		if(m_vecAllUnits[i]->IsAlive())
		{
			m_vecAllUnits[i]->Draw();
		}
	}
	DrawHighlight();
}

void CUnitManager::DrawHighlight()
{
	for(unsigned int i = 0; i < m_vecAllUnits.size(); ++i)
	{
		if(m_vecAllUnits[i]->IsAlive())
		{
			if(m_vecAllUnits[i]->IsSelected())
			{
				m_HighlighterSprite.SetScaleX(0.2f);
				m_HighlighterSprite.SetScaleY(0.2f);
				m_HighlighterSprite.SetColor(255, 255, 255, 255);
			}
			else
			{
				m_HighlighterSprite.SetColor((int)(m_vecAllUnits[i]->GetSpriteAlpha()*255), 255, 255, 255);
			}

			m_HighlighterSprite.TranslateAbsolute(m_vecAllUnits[i]->GetX(), m_vecAllUnits[i]->GetY());
			m_HighlighterSprite.Draw();

			if(m_vecAllUnits[i]->IsSelected())
			{
				m_HighlighterSprite.SetScaleX(0.1f);
				m_HighlighterSprite.SetScaleY(0.1f);
			}
		}
	}
}



void CUnitManager::AddUnit(CUnit* _pUnit)
{
	m_vecAllUnits.push_back(_pUnit);
}

CUnit* CUnitManager::GetUnit(int _iIndex)
{
	return(m_vecAllUnits[_iIndex]);
}

unsigned int CUnitManager::GetUnitTotal()
{
	return(m_vecAllUnits.size());
}

CUnit* CUnitManager::GetNewUnit()
{
	for(unsigned int i = 0; i < m_vecAllUnits.size(); ++i)
	{
		if(!m_vecAllUnits[i]->IsAlive())
		{
			return(m_vecAllUnits[i]);
		}
	}

	//We have no spare units- make a new one.

	CUnit* pNewUnit = new CUnit;
	m_vecAllUnits.push_back(pNewUnit);
	return(pNewUnit);
}

// Library Includes

// Local Includes
#include "Lantern.h"

// This include
#include "NodeLinkManager.h"

// Constants

// Static Variables

// Static Function Prototypes

// Implementation

CNodeLinkManager::CNodeLinkManager()
{

}

CNodeLinkManager::~CNodeLinkManager()
{
	
	for(unsigned int i = 0; i < m_vecLinks.size(); ++i)
	{
		delete m_vecLinks[i];
		m_vecLinks[i] = 0;
	}

}


void CNodeLinkManager::Initialise(CLanternManager* _pLanternManager)
{
	m_pLanternManager = _pLanternManager;

	for(unsigned int i = 0; i < m_pLanternManager->GetLanternTotal(); ++i)
	{
		for(unsigned int k = i+1; k < m_pLanternManager->GetLanternTotal(); ++k)
		{
			if(IsConnectionDesirable(m_pLanternManager->GetLantern(i), m_pLanternManager->GetLantern(k)))
			{
				CNodeLink* pLink = new CNodeLink;
				pLink->Initialise(m_pLanternManager->GetLantern(i), m_pLanternManager->GetLantern(k));
				m_vecLinks.push_back(pLink);
			}
		}
	}

}


bool CNodeLinkManager::IsConnectionDesirable(CLantern* pLantern1, CLantern* pLantern2)
{
	CLantern* pComparedLantern = 0;
	D3DXVECTOR2 Line1;
	D3DXVECTOR2 Line2;
	D3DXVECTOR2 Line1Norm;
	D3DXVECTOR2 Line2Norm;
	float fDot;
	float fLength1;
	float fLength2;

	for(unsigned int i = 0; i < m_pLanternManager->GetLanternTotal(); ++i)
	{
		pComparedLantern = m_pLanternManager->GetLantern(i);

		if(pComparedLantern != pLantern1 && pComparedLantern != pLantern2)
		{
			Line1 = *pLantern2->GetPosition() - *pLantern1->GetPosition();
			Line2 = *pComparedLantern->GetPosition() - *pLantern1->GetPosition();
			D3DXVec2Normalize(&Line1Norm, &Line1);
			D3DXVec2Normalize(&Line2Norm, &Line2);

			fDot = D3DXVec2Dot(&Line1Norm, &Line2Norm);
			fLength1 = D3DXVec2Length(&Line1);
			fLength2 = D3DXVec2Length(&Line2);
			float fAngle = acosf(fDot)/3.14f * 180;

			if(fabs(fDot) >=1 || fabs(fAngle) < 60)
			{
				if(fLength1*0.9f > fLength2)
				{
					return(false);
				}
			}


		}
	}

	return(true);

}

void CNodeLinkManager::Process(float _fDeltatick)
{
	for(unsigned int i = 0; i < m_vecLinks.size(); ++i)
	{
		m_vecLinks[i]->Process(_fDeltatick);
	}
}
void CNodeLinkManager::Draw()
{
	for(unsigned int i = 0; i < m_vecLinks.size(); ++i)
	{
		m_vecLinks[i]->Draw();
	}
}

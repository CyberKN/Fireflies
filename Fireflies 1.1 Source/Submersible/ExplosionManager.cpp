// Library Includes

// Local Includes

// This include
#include "ExplosionManager.h"
#include "Explosion.h"

// Constants

const float k_fExplosionLifetime = 0.3f;

// Static Variables

// Static Function Prototypes

// Implementation

CExplosionManager::CExplosionManager()
{

}

CExplosionManager::~CExplosionManager()
{
	for(unsigned int i = 0; i < m_vecExplosions.size(); ++i)
	{
		delete m_vecExplosions[i];
		m_vecExplosions[i] = 0;
	}
}

void CExplosionManager::Process(float _fDeltaTick)
{
	for(unsigned int i = 0; i < m_vecExplosions.size(); ++i)
	{
		if(!m_vecExplosions[i]->m_bDead)
		{
			m_vecExplosions[i]->Process(_fDeltaTick);

			if(m_vecExplosions[i]->m_fLifeTime > k_fExplosionLifetime)
			{
				m_vecExplosions[i]->m_bDead = true;
			}
		}
	}
}
void CExplosionManager::Draw()
{
	for(unsigned int i = 0; i < m_vecExplosions.size(); ++i)
	{
		if(!m_vecExplosions[i]->m_bDead)
		{
			m_vecExplosions[i]->Draw();
		}
	}
}

void CExplosionManager::CreateExplosion(float _fX, float _fY)
{
	CExplosion* pNewExplosion = 0;

	for(unsigned int i = 0; i < m_vecExplosions.size(); ++i)
	{
		if(m_vecExplosions[i]->m_bDead)
		{
			pNewExplosion = m_vecExplosions[i];
			break;
		}
	}

	//We have no spare units- make a new one.

	if(!pNewExplosion)
	{
		pNewExplosion = new CExplosion;
		m_vecExplosions.push_back(pNewExplosion);
	}

	pNewExplosion->Initialise();
	pNewExplosion->SetPosition(_fX, _fY);
	pNewExplosion->GetBoundingBox()->UpdatePosition(_fX, _fY);
	pNewExplosion->ApplyForce();
	
}
//  File Name   :   ProjectileManager.cpp
//  Description :   CProjectileManager Implementation File
//  Author      :   Kurt Nadworny
//  Mail        :   kurt.nadworny@mediadesign.school.nz
//



// Library Includes

// Local Includes

// This include
#include "ProjectileManager.h"
#include "Inkblot.h"
#include "Torpedo.h"
#include "Enemy.h"
#include "game.h"

// Constants

// Static Variables

// Static Function Prototypes

// Implementation

CProjectileManager::CProjectileManager()
{

}

CProjectileManager::~CProjectileManager()
{
	for(unsigned int i = 0; i < m_EnemyProjectileVec.size(); ++i)
	{	
		if(m_EnemyProjectileVec[i])
		{
			delete m_EnemyProjectileVec[i];
			m_EnemyProjectileVec[i] = 0;
		}
	}

	for(unsigned int i = 0; i < m_PlayerProjectileVec.size(); ++i)
	{	
		if(m_PlayerProjectileVec[i])
		{
			delete m_PlayerProjectileVec[i];
			m_PlayerProjectileVec[i] = 0;
		}
	}

	CGame::GetInstance().m_Session.m_SoundManager.ReleaseSound(m_iSound_TorpedoFire);
	CGame::GetInstance().m_Session.m_SoundManager.ReleaseSound(m_iSound_TorpedoImpact);

}

void CProjectileManager::Initialise()
{
	m_iSound_TorpedoFire = CGame::GetInstance().m_Session.m_SoundManager.LoadSoundFromFile("Sounds/MissleFiring.mp3");
	m_iSound_TorpedoImpact = CGame::GetInstance().m_Session.m_SoundManager.LoadSoundFromFile("Sounds/TinyExplosion.mp3");
}

void CProjectileManager::Process(float _fDeltaTick, CPlayer* _pPlayer)
{
	for(unsigned int i = 0; i < m_EnemyProjectileVec.size(); ++i)
	{	
		if(m_EnemyProjectileVec[i])
		{
			m_EnemyProjectileVec[i]->Process(_fDeltaTick, _pPlayer);
		}
	}

	for(unsigned int i = 0; i < m_PlayerProjectileVec.size(); ++i)
	{	
		if(m_PlayerProjectileVec[i])
		{
			m_PlayerProjectileVec[i]->Process(_fDeltaTick, _pPlayer);
		}
	}

	//Remove Dead Projectiles
	for(unsigned int i = 0; i < m_EnemyProjectileVec.size(); ++i)
	{
		if(m_EnemyProjectileVec[i])
		{
			if(m_EnemyProjectileVec[i]->m_fDeathTimer < 0)
			{
				m_EnemyProjectileVec[i]->Explode(0.7f);
				CGame::GetInstance().m_Session.m_SoundManager.PlaySound(m_EnemyProjectileVec[i]->m_iSound_Die);
				delete m_EnemyProjectileVec[i];
				m_EnemyProjectileVec[i] = 0;			
			}
		}
	}

	RemoveOffscreenProjectiles(_pPlayer->m_Avatar.m_PosVec.y);

}

void CProjectileManager::AddProjectile(float _fX, float _fY, int _iType, D3DXVECTOR2 _MoveVec)
{

	if(_iType == 0)
	//Type is Player Torpedo
	{
		CGame::GetInstance().m_Session.m_SoundManager.PlaySound(m_iSound_TorpedoFire);
		int iNewProjectilePos = -1;
		for(unsigned int i = 0; i < m_PlayerProjectileVec.size(); ++i)
		{
			if(!m_PlayerProjectileVec[i])
			{
				iNewProjectilePos = i;
				i = static_cast<unsigned int>(m_PlayerProjectileVec.size());
			}
		}

		if(iNewProjectilePos != -1)
		{
			m_PlayerProjectileVec[iNewProjectilePos] = new CTorpedo;
			m_PlayerProjectileVec[iNewProjectilePos]->Initialise(_fX, _fY, true, _MoveVec, m_iSound_TorpedoImpact);
		}
		else 
		{
			CProjectile* pTempProjectile = new CTorpedo;
			pTempProjectile->Initialise(_fX, _fY, true, _MoveVec, m_iSound_TorpedoImpact);
			m_PlayerProjectileVec.push_back(pTempProjectile);
			pTempProjectile = 0;
		}
	}
	else if(_iType == 1)
	//Type is Enemy Inkblot
	{
		int iNewProjectilePos = -1;
		for(unsigned int i = 0; i < m_EnemyProjectileVec.size(); ++i)
		{
			if(!m_EnemyProjectileVec[i])
			{
				iNewProjectilePos = i;
				i = static_cast<unsigned int>(m_EnemyProjectileVec.size());
			}
		}

		if(iNewProjectilePos != -1)
		{
			m_EnemyProjectileVec[iNewProjectilePos] = new CInkblot;
			m_EnemyProjectileVec[iNewProjectilePos]->Initialise(_fX, _fY, false, _MoveVec, m_iSound_TorpedoImpact);
		}
		else 
		{
			CProjectile* pTempProjectile = new CInkblot;
			pTempProjectile->Initialise(_fX, _fY, false, _MoveVec, m_iSound_TorpedoImpact);
			m_EnemyProjectileVec.push_back(pTempProjectile);
			pTempProjectile = 0;
		}
	}
	else if(_iType == 2)
	//Type is Enemy Torpedo
	{
		CGame::GetInstance().m_Session.m_SoundManager.PlaySound(m_iSound_TorpedoFire);
		int iNewProjectilePos = -1;
		for(unsigned int i = 0; i < m_EnemyProjectileVec.size(); ++i)
		{
			if(!m_EnemyProjectileVec[i])
			{
				iNewProjectilePos = i;
				i = static_cast<unsigned int>(m_EnemyProjectileVec.size());
			}
		}

		if(iNewProjectilePos != -1)
		{
			m_EnemyProjectileVec[iNewProjectilePos] = new CTorpedo;
			m_EnemyProjectileVec[iNewProjectilePos]->Initialise(_fX, _fY, false, _MoveVec, m_iSound_TorpedoImpact);
		}
		else 
		{
			CProjectile* pTempProjectile = new CTorpedo;
			pTempProjectile->Initialise(_fX, _fY, false, _MoveVec, m_iSound_TorpedoImpact);
			m_EnemyProjectileVec.push_back(pTempProjectile);
			pTempProjectile = 0;
		}
	}

}
void CProjectileManager::Draw()
{
	for(unsigned int i = 0; i < m_EnemyProjectileVec.size(); ++i)
	{	
		if(m_EnemyProjectileVec[i])
		{
			m_EnemyProjectileVec[i]->Draw();
		}
	}

	for(unsigned int i = 0; i < m_PlayerProjectileVec.size(); ++i)
	{	
		if(m_PlayerProjectileVec[i])
		{
			m_PlayerProjectileVec[i]->Draw();
		}
	}

}

void CProjectileManager::RemoveOffscreenProjectiles(float _fPlayerDepth)
{
	for(unsigned int i = 0; i < m_PlayerProjectileVec.size(); ++i)
	{
		if(m_PlayerProjectileVec[i])
		{
			if(fabs(m_PlayerProjectileVec[i]->m_PosVec.y - _fPlayerDepth) > 450
			|| m_PlayerProjectileVec[i]->m_PosVec.x > 700
			|| m_PlayerProjectileVec[i]->m_PosVec.x < 0
			|| m_PlayerProjectileVec[i]->m_PosVec.y > 0
			|| m_PlayerProjectileVec[i]->m_PosVec.y < -10000)
			{
			
				delete m_PlayerProjectileVec[i];
				m_PlayerProjectileVec[i] = 0;
			
			}
		}
	}

	for(unsigned int i = 0; i < m_EnemyProjectileVec.size(); ++i)
	{
		if(m_EnemyProjectileVec[i])
		{
			if(fabs(m_EnemyProjectileVec[i]->m_PosVec.y - _fPlayerDepth) > 450
			|| m_EnemyProjectileVec[i]->m_PosVec.x > 700
			|| m_EnemyProjectileVec[i]->m_PosVec.x < 0
			|| m_EnemyProjectileVec[i]->m_PosVec.y > 0
			|| m_EnemyProjectileVec[i]->m_PosVec.y < -10000)
			{
			
				delete m_EnemyProjectileVec[i];
				m_EnemyProjectileVec[i] = 0;
			
			}
		}
	}
}


void CProjectileManager::ProcessEnemyProjectileCollision(CEnemy* _pEnemy)
{
	for(unsigned int i = 0; i < m_PlayerProjectileVec.size(); ++i)
	{
		if(m_PlayerProjectileVec[i])
		{
			if(_pEnemy->m_BoundingBox.BoxCollsionCheck(&m_PlayerProjectileVec[i]->m_BoundingBox))
			{
				_pEnemy->m_iHealth -= 1;
				m_PlayerProjectileVec[i]->Explode(0.7f);
				CGame::GetInstance().m_Session.m_SoundManager.PlaySound(m_PlayerProjectileVec[i]->m_iSound_Die);
				delete m_PlayerProjectileVec[i];
				m_PlayerProjectileVec[i] = 0;
			}
		}
	}
}


void CProjectileManager::ProcessPlayerProjectileCollision(CPlayer* _pPlayer)
{
	if(_pPlayer->m_Avatar.m_fInvincibleTimer <= 0)
	{
		for(unsigned int i = 0; i < m_EnemyProjectileVec.size(); ++i)
		{
			if(m_EnemyProjectileVec[i])
			{
				if(_pPlayer->m_Avatar.m_BoundingBox.BoxCollsionCheck(&m_EnemyProjectileVec[i]->m_BoundingBox))
				{
					_pPlayer->m_Avatar.m_fHealth -= static_cast<float>(m_EnemyProjectileVec[i]->m_iDamage);
					_pPlayer->m_Avatar.m_fInvincibleTimer = _pPlayer->m_Avatar.m_fInvincibleTime;
					m_EnemyProjectileVec[i]->Explode(0.7f);
					CGame::GetInstance().m_Session.m_SoundManager.PlaySound(m_EnemyProjectileVec[i]->m_iSound_Die);
					delete m_EnemyProjectileVec[i];
					m_EnemyProjectileVec[i] = 0;
				}
			}
		}
	}
}


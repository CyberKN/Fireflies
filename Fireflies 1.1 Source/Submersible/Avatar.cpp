//  File Name   :   Avatar.cpp
//  Description :   CAvatar Implementation File
//  Author      :   Kurt Nadworny
//  Mail        :   kurt.nadworny@mediadesign.school.nz
//



// Library Includes

// Local Includes

// This include
#include "Avatar.h"
#include "game.h"

// Constants

// Static Variables

// Static Function Prototypes

// Implementation

CAvatar::CAvatar()
:m_fBubbleTimer(0.08f)
,m_bFacingLeft(0)
,m_fHealth(100)
,m_fInvincibleTimer(0)
,m_fSemiTransparentTimer(0)
,m_bSemiTransparent(false)
,m_bFiringKeyReleased(false)
,m_fReloadTimer(0)
,m_iHullRatingLevel(0)
,m_iBallastTanksLevel(1)
,m_iEngineLevel(1)
,m_iLightingLevel(0)
,m_iReloadLevel(0)
,m_bGameComplete(0)
,m_bAlive(true)
,m_fRespawnTimer(0)
,m_bMovingY(0)
,m_bMovingX(0)
,m_iCashCount(0)
,m_fInvincibleTime(2)
{

}

CAvatar::~CAvatar()
{
	
	CGame::GetInstance().m_Session.m_SoundManager.ReleaseSound(m_iSound_PressureWarning);
	CGame::GetInstance().m_Session.m_SoundManager.ReleaseSound(m_iSound_Explode);

}

void CAvatar::Initialise()
{
	m_PosVec.x = 250;
	m_PosVec.y = 0;

	m_Sprite.Initialise(SPRITE_PlayerSub, 1);
	m_BoundingBox.SetSize(84, 47);

	CGame::GetInstance().m_Session.m_INIParser.GetFloatValue("InitPlayerTraits", "InitPlayerHealth", m_fHealth);
	CGame::GetInstance().m_Session.m_INIParser.GetFloatValue("InitPlayerTraits", "InitPlayerDepth", m_PosVec.y);
	CGame::GetInstance().m_Session.m_INIParser.GetIntValue("InitPlayerTraits", "InitHullRatingLevel",m_iHullRatingLevel);
	CGame::GetInstance().m_Session.m_INIParser.GetIntValue("InitPlayerTraits", "InitBallastTanksLevel",m_iBallastTanksLevel);
	CGame::GetInstance().m_Session.m_INIParser.GetIntValue("InitPlayerTraits", "InitEngineLevel",m_iEngineLevel);
	CGame::GetInstance().m_Session.m_INIParser.GetIntValue("InitPlayerTraits", "InitLightingLevel",m_iLightingLevel);
	CGame::GetInstance().m_Session.m_INIParser.GetIntValue("InitPlayerTraits", "InitReloadLevel",m_iReloadLevel);
	CGame::GetInstance().m_Session.m_INIParser.GetIntValue("InitPlayerTraits", "InitCashCount",m_iCashCount);

	CGame::GetInstance().m_Session.m_INIParser.GetFloatValue("InitPlayerTraits", "InvincibleTime",m_fInvincibleTime);

	m_PosVec.y = -m_PosVec.y;


	m_iSound_PressureWarning = CGame::GetInstance().m_Session.m_SoundManager.LoadSoundFromFile("Sounds/Warning.mp3");
	m_iSound_Explode = CGame::GetInstance().m_Session.m_SoundManager.LoadSoundFromFile("Sounds/explosion.mp3");


}

void CAvatar::Process(float _fDeltaTick)
{
	bool bMoving = false;


//	if(!CGame::GetInstance().m_Session.IsAMenuOpen())
	{
		m_bMovingX = false;
		m_bMovingY = false;

		bMoving = ProcessMovementXbox(_fDeltaTick);
			
		if(!bMoving)
		{
			bMoving = ProcessMovementKeyboard(_fDeltaTick);
		}

		ApplyDrag(_fDeltaTick);
	}

	



	if(m_bFacingLeft)
	{
		m_Sprite.SetScaleX(-1);
		m_Sprite.SetRotate((0.02f*m_MoveVec.y)*D3DX_PI*0.10f);
	}
	else
	{
		m_Sprite.SetScaleX(1);
		m_Sprite.SetRotate((0.02f*-m_MoveVec.y)*D3DX_PI*0.10f);
	}


	if(bMoving)
	{
		m_fBubbleTimer -= _fDeltaTick;
	}

	if(m_fBubbleTimer < 0)
	{
		m_fBubbleTimer = 0.12f;

		float fEngineOffsetY = (m_MoveVec.y*-0.25f) - 8;

		if(m_bFacingLeft)
		{
			CGame::GetInstance().m_Session.m_pWorld->m_BubbleManager.AddBubble(m_PosVec.x+40, m_PosVec.y+fEngineOffsetY, 5);
		}
		else
		{
			CGame::GetInstance().m_Session.m_pWorld->m_BubbleManager.AddBubble(m_PosVec.x-40, m_PosVec.y+fEngineOffsetY, 5);
		}
	}
	

	
	CGameEntity::Process(_fDeltaTick);

	if(m_PosVec.x < 0)
	{
		m_PosVec.x = 0;
		m_MoveVec.x = 0;
	}
	else if(m_PosVec.x > 700)
	{
		m_PosVec.x = 700;
		m_MoveVec.x = 0;
	}

	if(m_PosVec.y > 0)
	{
		m_PosVec.y = 0;
	}
	else if(m_PosVec.y < -10000)
	{
		if(!m_bGameComplete)
		{
			CGame::GetInstance().m_Session.m_WinMenu.m_bIsOpen = true;
			m_MoveVec.x = 0;
			m_bGameComplete = true;
		}
		m_PosVec.y = -10000;
	}


	if(m_fInvincibleTimer > 0)
	{
		m_fInvincibleTimer -= _fDeltaTick;
		m_fSemiTransparentTimer -= _fDeltaTick;
		if(m_fSemiTransparentTimer < 0)
		{
			m_fSemiTransparentTimer = 0.05f;
			if(m_bSemiTransparent)
			{
				m_bSemiTransparent = false;
			}
			else
			{
				m_bSemiTransparent = true;
			}
		}
	}
	else
	{
		m_bSemiTransparent = false;
	}


	m_fReloadTimer -= _fDeltaTick;

//	if(!CGame::GetInstance().m_Session.IsAMenuOpen())
	{
		if(CGame::GetInstance().m_Keyboard.m_bEnterKeyPressed 
		|| CGame::GetInstance().m_Keyboard.m_bSpaceKeyPressed
		|| CGame::GetInstance().m_XboxVec[0]->m_bAbuttonPressed
		|| CGame::GetInstance().m_XboxVec[0]->m_fRightTrigger > 0.3f)
		{
			if(CGame::GetInstance().m_Session.m_pWorld->m_bPlayerSurfaced)
			{
				if(m_bFiringKeyReleased)
				{
					m_MoveVec.y = 0;
					m_MoveVec.x = 0;

					CGame::GetInstance().m_Session.m_UpgradeMenu.m_bIsOpen = true;
					CGame::GetInstance().m_Session.m_UpgradeMenu.m_bKeyReleased = false;
				}
				m_bFiringKeyReleased = false;
			}
			else
			{
				Fire();
			}
		}
		else
		{
			m_bFiringKeyReleased = true;
		}
	}

	if(m_iHullRatingLevel == 0 && m_PosVec.y < -1000)
	{
		m_bPressureWarning = true;
	} 
	else if(m_iHullRatingLevel == 1 && m_PosVec.y < -3000)
	{
		m_bPressureWarning = true;
	}
	else if(m_iHullRatingLevel == 2 && m_PosVec.y < -7000)
	{
		m_bPressureWarning = true;
	}
	else 
	{
		m_bPressureWarning = false;		
	}

	if(m_bPressureWarning)
	{
		m_fHealth -= _fDeltaTick*10;
		if(!CGame::GetInstance().m_Session.m_SoundManager.IsSoundPlaying(m_iSound_PressureWarning))
		{
			CGame::GetInstance().m_Session.m_SoundManager.PlaySound(m_iSound_PressureWarning);
		}
	}
}


bool CAvatar::ProcessMovementKeyboard(float _fDeltaTick)
{
	bool bMoving = false;
	if(CGame::GetInstance().m_Keyboard.m_bUpArrowKeyPressed)
	{
		MoveUp(_fDeltaTick);
		bMoving = true;
	}
	else if(CGame::GetInstance().m_Keyboard.m_bDownArrowKeyPressed)
	{
		MoveDown(_fDeltaTick);
		bMoving = true;
	}


	if(CGame::GetInstance().m_Keyboard.m_bRightArrowKeyPressed)
	{
		MoveRight(_fDeltaTick);
		bMoving = true;
	}
	else if(CGame::GetInstance().m_Keyboard.m_bLeftArrowKeyPressed)
	{
		MoveLeft(_fDeltaTick);
		bMoving = true;
	}

	return(bMoving);

}

bool CAvatar::ProcessMovementXbox(float _fDeltaTick)
{
	bool bMoving = false;
	if(CGame::GetInstance().m_XboxVec[0]->m_fLeftThumbStickY > 0)
	{
		MoveUp(_fDeltaTick);
		bMoving = true;
	}
	else if(CGame::GetInstance().m_XboxVec[0]->m_fLeftThumbStickY < 0)
	{
		MoveDown(_fDeltaTick);
		bMoving = true;
	}

	if(CGame::GetInstance().m_XboxVec[0]->m_fLeftThumbStickX > 0)
	{
		MoveRight(_fDeltaTick);
		bMoving = true;
	}
	else if(CGame::GetInstance().m_XboxVec[0]->m_fLeftThumbStickX < 0)
	{
		MoveLeft(_fDeltaTick);
		bMoving = true;
	}
	

	return(bMoving);

}

void CAvatar::Draw()
{
	if(m_bAlive)
	{

		if(m_bSemiTransparent)
		{
			m_Sprite.SetColor(80, 255, 255, 255);
		}
		else
		{
			m_Sprite.SetColor(255, 255, 255, 255);
		}
		

		CGameEntity::Draw();
	}
}

void CAvatar::ProcessRespawn(float _fDeltaTick)
{
	m_fRespawnTimer-= _fDeltaTick;

	if(m_fRespawnTimer < 3)
	{
		m_PosVec.x = 350;
		m_PosVec.y = 0;
		m_MoveVec.x = 0;
		m_MoveVec.y = 0;
		m_bFacingLeft = true;
		m_fHealth = 100;
		m_bPressureWarning = false;
		CGame::GetInstance().m_Session.m_pWorld->m_bPlayerSurfaced = true;
	}

	if(m_fRespawnTimer < 0)
	{
		m_bAlive = true;
	}

}

void CAvatar::MoveUp(float _fDeltaTick)
{
	if(m_MoveVec.y < 50+(10*m_iBallastTanksLevel))
	{
		m_MoveVec.y += _fDeltaTick*(50*m_iBallastTanksLevel);
	}
	m_bMovingY = true;
}
void CAvatar::MoveDown(float _fDeltaTick)
{
	if(m_MoveVec.y > -40+(-10*m_iBallastTanksLevel))
	{
		m_MoveVec.y -= _fDeltaTick*(50*m_iBallastTanksLevel);
	}
	m_bMovingY = true;
}

void CAvatar::MoveRight(float _fDeltaTick)
{
	if(m_MoveVec.x < 40+(10*m_iEngineLevel))
	{
		m_MoveVec.x += _fDeltaTick*(50*m_iEngineLevel);
	}
	if(m_bFacingLeft)
	{
		m_bFacingLeft = false;
	}
	m_bMovingX = true;
}

void CAvatar::MoveLeft(float _fDeltaTick)
{
	if(m_MoveVec.x > -40+(-10*m_iEngineLevel))
	{
		m_MoveVec.x -= _fDeltaTick*(50*m_iEngineLevel);
	}
	if(!m_bFacingLeft)
	{
		m_bFacingLeft = true;
	}
	m_bMovingX = true;
}

void CAvatar::Fire()
{
	if(m_bFiringKeyReleased && m_fReloadTimer < 0)
	{
		m_bFiringKeyReleased = false;
		m_fReloadTimer = 0.9f -(0.2f*m_iReloadLevel);

		float fNoseOffsetY = (m_MoveVec.y*0.4f) - 10;

		if(m_bFacingLeft)
		{
			CGame::GetInstance().m_Session.m_pWorld->m_ProjectileManager.AddProjectile(m_PosVec.x-40, m_PosVec.y+fNoseOffsetY, 0, D3DXVECTOR2(-200, m_MoveVec.y*2));
		}
		else
		{
			CGame::GetInstance().m_Session.m_pWorld->m_ProjectileManager.AddProjectile(m_PosVec.x+40, m_PosVec.y+fNoseOffsetY, 0, D3DXVECTOR2(200, m_MoveVec.y*2));
		}
	}
}

void CAvatar::ApplyDrag(float _fDeltaTick)
{
	if(!m_bMovingY)
	{
		if(fabs(m_MoveVec.y) > 0.01f)
		{
			m_MoveVec.y = m_MoveVec.y*(1.0f-(_fDeltaTick*2));
		}
		else
		{
			m_MoveVec.y = 0.0f;
		}	
	}

	if(!m_bMovingX)
	{
		if(fabs(m_MoveVec.x) > 0.01f)
		{
			m_MoveVec.x = m_MoveVec.x*(1.0f-(_fDeltaTick*2));
		}
		else
		{
			m_MoveVec.x = 0.0f;
		}	
	}
	
}

void CAvatar::Die()
{
	CGame::GetInstance().m_Session.m_pWorld->m_ExplosionManager.AddExplosion(m_PosVec.x, m_PosVec.y, 1.4f);
	CGame::GetInstance().m_Session.m_SoundManager.PlaySound(m_iSound_Explode);
	CGame::GetInstance().m_Session.m_pWorld->m_Ship.m_PosVec.x = -625;
	CGame::GetInstance().m_Session.m_pWorld->m_Ship.m_MoveVec.x = 200;
	m_fRespawnTimer = 5;
	m_bAlive = false;
	m_fInvincibleTimer = m_fInvincibleTime;
	m_fHealth = 0;

}

// Library Includes

// Local Includes

// This include
#include "Tutorial.h"
#include "Game.h"
#include "SpatialManager.h"
#include "Cursor.h"
#include "SpriteManager.h"
#include "Menu.h"

// Constants

// Static Variables

#define EVT_0_InitCursor		0.0f
#define EVT_1_GrabUnits			2.0f
#define EVT_2_MoveToNewBase		3.0f
#define EVT_3_DropUnits			5.0f
#define EVT_4_MoveToFirstBase	12.0f
#define EVT_5_GrabUnits			14.0f
#define EVT_6_MoveToNewBase		15.0f
#define EVT_7_DropUnits			17.0f
#define EVT_8_GrabUnits			25.0f
#define EVT_9_MoveToEnemyBase	26.0f
#define EVT_10_DropUnits		28.0f
#define EVT_11_GrabUnits		35.0f
#define EVT_12_DropUnits		35.5f
#define EVT_13_FadeOut			40.0f

// Static Function Prototypes

// Implementation

CTutorial::CTutorial()
{
	m_fEventTimer = 0;
}

CTutorial::~CTutorial()
{

}

void CTutorial::Process(float _fDeltaTick)
{
	
	if(CGame::GetInstance().m_Keyboard.WasKeyPressed(KEYID_ESC))
	{
		m_bPaused = !m_bPaused;
	}

	if(m_bPaused && !m_pPauseMenu)
	{
		m_pPauseMenu = new CMenu;
		m_pPauseMenu->Initialise(MENU_PAUSE);
	}
	else if(!m_bPaused && m_pPauseMenu)
	{
		delete m_pPauseMenu;
		m_pPauseMenu = 0;
	}

	if(m_bPaused)
	{
		m_pPauseMenu->Process(_fDeltaTick);
	}
	else
	{
		ProcessTutorial(_fDeltaTick);

		if(!m_bGameWon)
		{
			/*if(fabs(CGame::GetInstance().m_Mouse.GetMovement(MOUSEMOVE_Z)) > 0)
			{
				float fCursorOldPosX = m_pCursor->GetPosition()->x;
				float fCursorOldPosY = m_pCursor->GetPosition()->y;
				m_pSpriteManager->AdjustZoom(CGame::GetInstance().m_Mouse.GetMovement(MOUSEMOVE_Z) * m_pSpriteManager->GetZoom());

				if(m_pSpriteManager->GetZoom() < 0.01f)
				{
					m_pSpriteManager->SetZoom(0.01f);
				}
				else if(m_pSpriteManager->GetZoom() > 10.0f)
				{
					m_pSpriteManager->SetZoom(10.0f);
				}

				m_pCursor->CalculateZoomPosition();
				
				m_pSpriteManager->AdjustDrawOffsetX(-(fCursorOldPosX - m_pCursor->GetPosition()->x));
				m_pSpriteManager->AdjustDrawOffsetY(-(fCursorOldPosY - m_pCursor->GetPosition()->y));

			}
			

			if( CGame::GetInstance().m_Mouse.IsButtonDown(MOUSEBID_MIDDLE))
			{
				m_pSpriteManager->AdjustDrawOffsetX(CGame::GetInstance().m_Mouse.GetMovement(MOUSEMOVE_X)*(1/m_pSpriteManager->GetZoom()));
				m_pSpriteManager->AdjustDrawOffsetY(-CGame::GetInstance().m_Mouse.GetMovement(MOUSEMOVE_Y)*(1/m_pSpriteManager->GetZoom()));
			}*/

			CSpatialManager::GetInstance()->EmptyGrid();
			m_LanternManager.Process(_fDeltaTick);
			m_NodeLinkManager.Process(_fDeltaTick);
			m_UnitManager.Process(_fDeltaTick);
			m_ExplosionManager.Process(_fDeltaTick);
			m_pCursor->Process(_fDeltaTick, true);
			m_PlayerManager.Process(_fDeltaTick);

			CSpatialManager::GetInstance()->PopulateGridUsingHashVal();

			CSpatialManager::GetInstance()->ProcessCollisions();
			CSpatialManager::GetInstance()->ProcessEnemyCollisions();

			CheckForWin();
		}
		else
		{
			CSpatialManager::GetInstance()->EmptyGrid();
			m_LanternManager.Process(_fDeltaTick);
			m_UnitManager.Process(_fDeltaTick);
			m_ExplosionManager.Process(_fDeltaTick);
			m_PlayerManager.Process(_fDeltaTick);

			CSpatialManager::GetInstance()->PopulateGridUsingHashVal();

			CSpatialManager::GetInstance()->ProcessCollisions();

			m_pSpriteManager->AdjustDrawOffsetX((m_fDefaultOffsetX - m_pSpriteManager->GetDrawOffsetX())*_fDeltaTick*1.0f);
			m_pSpriteManager->AdjustDrawOffsetY((m_fDefaultOffsetY - m_pSpriteManager->GetDrawOffsetY())*_fDeltaTick*1.0f);
			m_pSpriteManager->AdjustZoom((m_fDefaultZoom - m_pSpriteManager->GetZoom())*_fDeltaTick*1.0f);

			m_fGameOverFadeTimer += _fDeltaTick;

			if(m_fGameOverFadeTimer > 4)
			{
				m_FadeSprite.SetColor((int)((m_fGameOverFadeTimer-4)*255), 255, 255, 255);
				
				if(m_fGameOverFadeTimer > 5)
				{
					CGame::GetInstance().SetNewState(GAMESTATE_MENU);
					m_FadeSprite.SetColor(255, 255, 255, 255);
				}
			}
		}
	}

}


void CTutorial::ProcessTutorial(float _fDeltaTick)
{
	m_fEventTimer += _fDeltaTick;

	m_TipBox.Process(_fDeltaTick);


	
	if(m_fEventTimer < EVT_1_GrabUnits)
	{
		m_TipBox.Open("Click and Drag a group of units to a base to claim it.");
		D3DXVECTOR2 m_vStartPoint = D3DXVECTOR2(695, 409);
		D3DXVECTOR2 m_vEndPoint = D3DXVECTOR2(395, 309);
		float fScalar = (m_fEventTimer)*0.5f;
		D3DXVECTOR2 vLine;
		D3DXVECTOR2 vPos;

		vLine = m_vStartPoint - m_vEndPoint;

			
		vPos = m_vStartPoint + (-vLine*SmoothStep(fScalar));

		m_pCursor->SetPosition(vPos.x, vPos.y);

	}
	if(m_fEventTimer > EVT_1_GrabUnits && m_fEventTimer < EVT_2_MoveToNewBase)
	{
		if(!m_pCursor->GetFakeClick())
		{
			m_pCursor->SetFakeClick(true);
		}
	}
	else if(m_fEventTimer > EVT_2_MoveToNewBase && m_fEventTimer < EVT_3_DropUnits)
	{
		if(m_fEventTimer < EVT_2_MoveToNewBase + 2)
		{
			D3DXVECTOR2 m_vStartPoint = D3DXVECTOR2(395, 309);
			D3DXVECTOR2 m_vEndPoint = D3DXVECTOR2(-40, 309);
			float fScalar = (m_fEventTimer - EVT_2_MoveToNewBase)*0.5f;
			D3DXVECTOR2 vLine;
			D3DXVECTOR2 vPos;

			vLine = m_vStartPoint - m_vEndPoint;
			
			vPos = m_vStartPoint + (vLine*SmoothStep(fScalar));
			m_pSpriteManager->SetDrawOffset(vPos.x - 395, vPos.y - 309);

			
			vPos = m_vStartPoint + (-vLine*(fScalar));

			m_pCursor->SetPosition(vPos.x, vPos.y);
		}
	}
	else if(m_fEventTimer > EVT_3_DropUnits && m_fEventTimer < EVT_4_MoveToFirstBase)
	{
		if(m_pCursor->GetFakeClick())
		{
			m_LanternManager.GetLantern(0)->SpawnInitUnits();
			m_pCursor->SetFakeClick(false);
		}
	}
	else if(m_fEventTimer > EVT_4_MoveToFirstBase && m_fEventTimer < EVT_5_GrabUnits)
	{
		if(m_fEventTimer < EVT_4_MoveToFirstBase + 2)
		{
			D3DXVECTOR2 m_vEndPoint = D3DXVECTOR2(395, 309);
			D3DXVECTOR2 m_vStartPoint = D3DXVECTOR2(-40, 309);
			float fScalar = (m_fEventTimer - EVT_4_MoveToFirstBase)*0.5f;
			D3DXVECTOR2 vLine;
			D3DXVECTOR2 vPos;

			vLine = m_vEndPoint - m_vStartPoint;
			
			vPos = m_vEndPoint + (vLine*SmoothStep(1-fScalar));
			m_pSpriteManager->SetDrawOffset(vPos.x - 395, vPos.y - 309);

			
			vPos = m_vStartPoint + (vLine*(fScalar));

			m_pCursor->SetPosition(vPos.x, vPos.y);
		}
	}
	else if(m_fEventTimer > EVT_5_GrabUnits && m_fEventTimer < EVT_6_MoveToNewBase)
	{
		m_pCursor->SetFakeClick(true);
	}
	else if(m_fEventTimer > EVT_6_MoveToNewBase && m_fEventTimer < EVT_7_DropUnits)
	{
		if(m_fEventTimer < EVT_6_MoveToNewBase + 2)
		{
			D3DXVECTOR2 m_vStartPoint = D3DXVECTOR2(395, 309);
			D3DXVECTOR2 m_vEndPoint = D3DXVECTOR2(-40, 309);
			float fScalar = (m_fEventTimer - EVT_6_MoveToNewBase)*0.5f;
			D3DXVECTOR2 vLine;
			D3DXVECTOR2 vPos;

			vLine = m_vStartPoint - m_vEndPoint;
			
			vPos = m_vStartPoint + (vLine*SmoothStep(fScalar));
			m_pSpriteManager->SetDrawOffset(vPos.x - 395, vPos.y - 309);

			
			vPos = m_vStartPoint + (-vLine*(fScalar));

			m_pCursor->SetPosition(vPos.x, vPos.y);
		}
	}
	else if(m_fEventTimer > EVT_7_DropUnits && m_fEventTimer < EVT_8_GrabUnits)
	{
		if(m_pCursor->GetFakeClick())
		{
			m_pCursor->SetFakeClick(false);
			m_TipBox.Open("Invest units into a base to increase it's level. Higher level bases produce more units.");
		}

	}
	else if(m_fEventTimer > EVT_8_GrabUnits && m_fEventTimer < EVT_9_MoveToEnemyBase)
	{
		m_pCursor->SetFakeClick(true);
	}
	else if(m_fEventTimer > EVT_9_MoveToEnemyBase && m_fEventTimer < EVT_10_DropUnits)
	{
		if(m_LanternManager.GetLantern(1)->GetNearbyUnitTotal() < 300 && m_fEventTimer > EVT_9_MoveToEnemyBase + 1)
		{
			m_LanternManager.GetLantern(1)->SpawnInitUnits();
		}
		if(m_fEventTimer < EVT_9_MoveToEnemyBase + 2)
		{
			D3DXVECTOR2 m_vStartPoint = D3DXVECTOR2(-40, 309);
			D3DXVECTOR2 m_vEndPoint = D3DXVECTOR2(-459, 309);
			float fScalar = (m_fEventTimer - EVT_9_MoveToEnemyBase)*0.5f;
			D3DXVECTOR2 vLine;
			D3DXVECTOR2 vPos;

			vLine = m_vStartPoint - m_vEndPoint;
			
			vPos = m_vStartPoint + (vLine*SmoothStep(fScalar));
			m_pSpriteManager->SetDrawOffset(vPos.x + 459+40, vPos.y - 309);

			
			vPos = m_vStartPoint + (-vLine*(fScalar));

			m_pCursor->SetPosition(vPos.x, vPos.y);
		}
	}
	else if(m_fEventTimer > EVT_10_DropUnits && m_fEventTimer < EVT_11_GrabUnits)
	{
		if(m_pCursor->GetFakeClick())
		{
			m_pCursor->SetFakeClick(false);
			m_TipBox.Open("Order units to attack enemy bases to capture them. ");
		}
	}
	else if(m_fEventTimer > EVT_11_GrabUnits && m_fEventTimer < EVT_12_DropUnits)
	{
		if(!m_pCursor->GetFakeClick())
		{
			m_pCursor->SetFakeClick(true);
		}
	}
	else if(m_fEventTimer > EVT_12_DropUnits && m_fEventTimer < EVT_13_FadeOut)
	{
		if(m_pCursor->GetFakeClick())
		{
			m_pCursor->SetFakeClick(false);
		}
	}
	else if(m_fEventTimer > EVT_13_FadeOut)
	{
		m_bGameWon = true;
	}
}

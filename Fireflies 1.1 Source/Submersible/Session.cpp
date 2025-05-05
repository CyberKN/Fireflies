// Library Includes

// Local Includes

// This include
#include "Session.h"
#include "Game.h"
#include "SpatialManager.h"
#include "Cursor.h"
#include "SpriteManager.h"
#include "Menu.h"
// Constants


// Static Variables

// Static Function Prototypes

// Implementation

CSession::CSession()
:m_pSpriteManager(0)
,m_iCollisionChecks(0)
,m_bPaused(false)
,m_pPauseMenu(0)
,m_fDefaultZoom(1)
,m_fDefaultOffsetX(0)
,m_fDefaultOffsetY(0)
,m_bGameWon(false)
,m_fGameOverFadeTimer(0)
{

}

CSession::~CSession()
{

	delete m_pCursor;
	m_pCursor = 0;

	if(m_pPauseMenu)
	{
		delete m_pPauseMenu;
		m_pPauseMenu = 0;
	}

	CSpatialManager::DestroyInstance();
	
	m_pSpriteManager->SetZoom(1);
	m_pSpriteManager->SetDrawOffset(0, 0);
	m_pSpriteManager = 0;

}

void CSession::Initialise(CSpriteManager* _pSpriteManager, std::string _strLevelName)
{
	m_TipBox.Initialise();
	m_pSpriteManager = _pSpriteManager;
	m_UnitManager.Initialise();
	m_LanternManager.Initialise(_strLevelName);
	m_NodeLinkManager.Initialise(&m_LanternManager);

	m_PlayerManager.Initialise();


	m_pCursor = new CCursor;
	m_pCursor->Initialise(m_PlayerManager.GetPlayer((unsigned int)PLAYER_1));

	CSpatialManager::GetInstance()->Initialise();

	CINIParser ViewParser;
	ViewParser.LoadIniFile("Levels\\"+_strLevelName+".ini");
	ViewParser.GetFloatValue("DefaultView", "zoom", m_fDefaultZoom);
	ViewParser.GetFloatValue("DefaultView", "X", m_fDefaultOffsetX);
	ViewParser.GetFloatValue("DefaultView", "Y", m_fDefaultOffsetY);

	m_pSpriteManager->SetDrawOffset(m_fDefaultOffsetX,m_fDefaultOffsetY);
	m_pSpriteManager->SetZoom(m_fDefaultZoom);

	m_FadeSprite.Initialise(SPRITE_Block4Sides, 50);
	m_FadeSprite.SetColor(0, 255, 255, 255);
	m_FadeSprite.TranslateAbsolute(400, 300);
	m_FadeSprite.SetIgnoreOffset(true);

	m_BGSprite.Initialise(SPRITE_BG, 1);
	m_BGSprite.TranslateAbsolute(400, 300);
	m_BGSprite.SetIgnoreOffset(true);



}

void CSession::Process(float _fDeltaTick)
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
		if(!m_bGameWon)
		{
			if(fabs(CGame::GetInstance().m_Mouse.GetMovement(MOUSEMOVE_Z)) > 0)
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
			}

			CSpatialManager::GetInstance()->EmptyGrid();
			m_LanternManager.Process(_fDeltaTick);
			m_NodeLinkManager.Process(_fDeltaTick);
			m_UnitManager.Process(_fDeltaTick);
			m_ExplosionManager.Process(_fDeltaTick);
			m_pCursor->Process(_fDeltaTick);
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


void CSession::Draw()
{
	//int iLowX = (-CGame::GetInstance().GetSpriteManager()->GetDrawOffsetX())/340;
	//int iLowY = (-CGame::GetInstance().GetSpriteManager()->GetDrawOffsetY())/340;
	//int iHighX = (CGame::GetInstance().m_iWindowWidth - CGame::GetInstance().GetSpriteManager()->GetDrawOffsetX())/340;
	//int iHighY = (CGame::GetInstance().m_iWindowHeight - CGame::GetInstance().GetSpriteManager()->GetDrawOffsetY())/340;

	//for(int i = iLowX-1; i < iHighX+1; ++i)
	//{
	//	for(int k = iLowY-1; k < iHighY+1; ++k)
	//	{
			//m_BGSprite.TranslateAbsolute((i*340)+170, (k*340)+170);
			//m_BGSprite.Draw();
	//	}
	//}




	m_NodeLinkManager.Draw();
	m_LanternManager.Draw();

	m_pSpriteManager->BeginBatch(SPRITE_Firefly);
	m_UnitManager.Draw();
	m_ExplosionManager.Draw();
	m_pSpriteManager->EndBatch();


	m_LanternManager.DrawHealthBarSprites();

	/*m_pSpriteManager->BeginBatch(SPRITE_Block4Sides);
	CSpatialManager::GetInstance()->Draw();
	m_pSpriteManager->EndBatch();*/

	if(!m_bPaused && !m_bGameWon)
	{
		m_pCursor->Draw();
	}

	m_TipBox.Draw();

	m_FadeSprite.Draw();

	//CTextBox TestBox;
	//TestBox.Initialise(255, 0, 150, 10, true, false, 1);
	//TestBox.m_iBlue = 255;
	//TestBox.m_iRed = 0;
	//TestBox.SetString(FloatToString(1.f/(float)(CGame::GetInstance().m_fDeltaTick)));
	////TestBox.Draw();
	//TestBox.m_fY -= 50;
	//TestBox.SetString(IntToString(m_iCollisionChecks));
	////TestBox.Draw();
	//m_iCollisionChecks = 0;

	//TestBox.m_fY -= 50;

	//int iBlueUnits = 0;
	//int iRedUnits = 0;
	//int iGreenUnits = 0;

	//for(unsigned int i = 0; i < m_UnitManager.GetUnitTotal(); ++i)
	//{
	//	if(GetUnitManager()->GetUnit(i)->IsAlive())
	//	{
	//		if(GetUnitManager()->GetUnit(i)->GetPlayerID() == PLAYER_1)
	//		{
	//			++iBlueUnits;
	//		}
	//		else if(GetUnitManager()->GetUnit(i)->GetPlayerID() == PLAYER_2)
	//		{
	//			++iRedUnits;
	//		}
	//		else if(GetUnitManager()->GetUnit(i)->GetPlayerID() == PLAYER_3)
	//		{
	//			++iGreenUnits;
	//		}
	//	}
	//}
	//TestBox.m_iRed = 0;
	//TestBox.m_iBlue = 255;
	//TestBox.m_iGreen = 50;
	//TestBox.SetString(IntToString(iBlueUnits));
	//TestBox.Draw();
	//TestBox.m_iBlue = 0;
	//TestBox.m_iRed = 255;
	//TestBox.m_fX += 100;
	//TestBox.SetString(IntToString(iRedUnits));
	//TestBox.Draw();
	//TestBox.m_iRed = 0;
	//TestBox.m_iGreen = 255;
	//TestBox.m_fX += 100;
	//TestBox.SetString(IntToString(iGreenUnits));
	//TestBox.Draw();

	if(m_pPauseMenu)
	{
		m_pPauseMenu->Draw();
	}

}


CUnitManager* CSession::GetUnitManager()
{
	return(&m_UnitManager);
}


void CSession::CheckForWin()
{
	int iPlayerBases[4] = {0, 0, 0, 0};

	for(unsigned int i = 0; i < m_LanternManager.GetLanternTotal(); ++i)
	{
		++iPlayerBases[static_cast<int>(m_LanternManager.GetLantern(i)->GetPlayerID())];
	}

	if((!iPlayerBases[0] && !iPlayerBases[1]) || (!iPlayerBases[1] && !iPlayerBases[2]) || (!iPlayerBases[0] && !iPlayerBases[2]))
	{
		m_bGameWon = true;
	}
}





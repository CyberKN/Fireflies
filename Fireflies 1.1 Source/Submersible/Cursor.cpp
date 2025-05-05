// Library Includes

// Local Includes

// This include
#include "Cursor.h"
#include "Player.h"
#include "Game.h"

// Constants

// Static Variables

// Static Function Prototypes

// Implementation

/**
* Constructor
*/
CCursor::CCursor()
{
	m_bTutorialMode = false;
	m_bFakeClick = false;
	m_bClick = false;
	m_fSelectSize = 1;
	m_pPlayer = 0;
}

/**
* Destructor
*/
CCursor::~CCursor()
{
}


/**
* Initialises the cursor
*/
void CCursor::Initialise(CPlayer* _pPlayer)
{
	m_pPlayer = _pPlayer;
	m_Sprite.Initialise(SPRITE_Cursor, m_fSelectSize);
	m_Sprite.SetColor(50, 0, 0, 255);

	m_SpriteAnimated.Initialise(SPRITE_Cursor, m_fSelectSize);
	m_SpriteAnimated.SetColor(100, 0, 0, 255);
}

/**
* Processes the Cursor's main function
* @param _fDeltaTick - Time elapsed since last frame
*/
void CCursor::Process(float _fDeltaTick, bool _bTutorialMode)
{
	m_bTutorialMode = _bTutorialMode;
	CSpriteManager* pSpriteManager = CGame::GetInstance().GetSpriteManager();

	if(!m_bTutorialMode)
	{
		CalculateZoomPosition();
	}



	m_fSelectSize = 1*(1/pSpriteManager->GetZoom());
	if(m_fSelectSize < 0.1f)
	{
		m_fSelectSize = 0.1f;
	}
	m_Sprite.SetScaleX(m_fSelectSize);
	m_Sprite.SetScaleY(m_fSelectSize);

	if(!m_bTutorialMode && CGame::GetInstance().m_Mouse.IsButtonDown(MOUSEBID_LEFT) || m_bFakeClick)
	{
		//If the Mouse button was not pressed prior to this, mark this location for selecting units
		if(!m_bClick)
		{
			m_bClick = true;
			m_fSelectedX = m_PosVec.x;
			m_fSelectedY = m_PosVec.y;
		}

		//CUnitManager* pUnitManager = CGame::GetInstance().GetSession()->GetUnitManager();
		unsigned int iUnitTotal = m_pPlayer->GetUnitTotal();
		CUnit* pUnit = 0;
		
		m_BoundingBox.SetSize(100*m_fSelectSize, 100*m_fSelectSize);
		m_BoundingBox.UpdatePosition(m_fSelectedX, m_fSelectedY);

		C2DBoundingBox* pBB = &m_BoundingBox;

		CLantern* pNearestLantern = 0;
		CLantern* pLantern = 0;

		CLanternManager* pLanternManager = CGame::GetInstance().GetSession()->GetLanternManager();

		C2DBoundingBox tempbox;
		tempbox.UpdatePosition(m_PosVec.x, m_PosVec.y);
		tempbox.SetSize(20, 20);



		//Lantern-Cursor-Collision

		for(unsigned int i = 0; i < pLanternManager->GetLanternTotal(); ++i)
		{
			pLantern = pLanternManager->GetLantern(i);
			pLantern->SetSelected(false);
			if((&tempbox)->CircleCollsionCheck(pLantern->GetBoundingBox()))
			{
				if(!pNearestLantern)
				{
					pNearestLantern = pLantern;
				}
				else
				{
					D3DXVECTOR2 vNearestDistance = m_PosVec - *(pNearestLantern->GetPosition());
					D3DXVECTOR2 vDistance = m_PosVec - *(pLantern->GetPosition());
					float fNearestDistance = D3DXVec2Length(&vNearestDistance);
					float fDistance = D3DXVec2Length(&vDistance);

					if(fNearestDistance < fDistance)
					{
						pNearestLantern = pLantern;
					}
				}
			}
		}

		if(pNearestLantern)
		{
			pNearestLantern->SetSelected(true);
		}


		//Unit-Cursor-Collision
		for(unsigned int z = 0; z < iUnitTotal; ++z)
		{
			pUnit = m_pPlayer->GetUnit(z);

			pUnit->SetSelected(false);

			if(pUnit->IsAlive() && pUnit->GetBoundingBox()->CircleCollsionCheck(pBB))
			{
				pUnit->SetSelected(true);
			}			
		}
	
	}
	else
	{
		if(m_bClick)
		{
			m_bClick = false;

			float fOffsetX = m_fSelectedX - m_PosVec.x;
			float fOffsetY = m_fSelectedY - m_PosVec.y;

			float fTargetX;
			float fTargetY;

		
			//CUnitManager* pUnitManager = CGame::GetInstance().GetSession()->GetUnitManager();
			unsigned int iUnitTotal = m_pPlayer->GetUnitTotal();
			CUnit* pUnit = 0;
		
			m_BoundingBox.SetSize(32*m_fSelectSize, 32*m_fSelectSize);
			m_BoundingBox.UpdatePosition(m_fSelectedX, m_fSelectedY);

			C2DBoundingBox* pBB = &m_BoundingBox;

			CLantern* pLantern = 0;

			CLanternManager* pLanternManager = CGame::GetInstance().GetSession()->GetLanternManager();

			for(unsigned int i = 0; i < pLanternManager->GetLanternTotal(); ++i)
			{
				pLantern = pLanternManager->GetLantern(i);

				if(pLantern->IsSelected())
				{
					pLantern->SetSelected(false);
					break;
				}
				pLantern = 0;
				
			}


			for(unsigned int z = 0; z < iUnitTotal; ++z)
			{
				pUnit = m_pPlayer->GetUnit(z);
				if(pUnit->IsSelected())
				{
					pUnit->SetSelected(false);

					if(pLantern)
					{
						fTargetX = pLantern->GetX();
						fTargetY = pLantern->GetY();
						pLantern->SetupUnitTarget(pUnit);
					}
					else
					{
						fTargetX = pUnit->GetPosition()->x - fOffsetX;
						fTargetX = (fTargetX + m_PosVec.x)*0.5f;

						fTargetY = pUnit->GetPosition()->y - fOffsetY;
						fTargetY = (fTargetY + m_PosVec.y)*0.5f;
					}

					pUnit->SetTarget(fTargetX, fTargetY);
				}
			}
		}

	}

	ProcessSpriteAnimation(_fDeltaTick);
}


	
/**
* Draws the Cursor
*/
void CCursor::Draw()
{
	m_SpriteAnimated.TranslateAbsolute(m_PosVec.x, m_PosVec.y);
	if(!m_bClick)
	{
		m_Sprite.TranslateAbsolute(m_PosVec.x, m_PosVec.y);
	}
	else
	{
		m_Sprite.TranslateAbsolute(m_fSelectedX, m_fSelectedY);
	}

	m_Sprite.Draw();
	m_SpriteAnimated.Draw();


#ifdef _DEBUG
	if(CGame::GetInstance().m_Mouse.IsButtonDown(MOUSEBID_RIGHT))
	{
		DisplayDebugInfo();
	}
#endif // _DEBUG

}

/**
* Processes the Cursor's Sprite Animation
* @param _fDeltaTick - Time elapsed since last frame
*/
void CCursor::ProcessSpriteAnimation(float _fDeltaTick)
{
	if(!m_bTutorialMode && CGame::GetInstance().m_Mouse.IsButtonDown(MOUSEBID_LEFT) || m_bFakeClick)
	{
		
		m_SpriteAnimated.SetScaleX(m_SpriteAnimated.GetScaleX() - _fDeltaTick*m_fSelectSize*4);
		m_SpriteAnimated.SetScaleY(m_SpriteAnimated.GetScaleY() - _fDeltaTick*m_fSelectSize*4);
		
		if(m_SpriteAnimated.GetScaleX() < 0.33f)
		{
			m_SpriteAnimated.SetScaleX(0.33f);
			m_SpriteAnimated.SetScaleY(0.33f);
		}
	}
	else
	{
		
		m_SpriteAnimated.SetScaleX(m_fSelectSize);
		m_SpriteAnimated.SetScaleY(m_fSelectSize);

		m_SpriteAnimated.SetScaleX(m_SpriteAnimated.GetScaleX() + _fDeltaTick*m_fSelectSize*4);
		m_SpriteAnimated.SetScaleY(m_SpriteAnimated.GetScaleY() + _fDeltaTick*m_fSelectSize*4);
		
		if(m_SpriteAnimated.GetScaleX() > m_fSelectSize)
		{
			m_SpriteAnimated.SetScaleX(m_fSelectSize);
			m_SpriteAnimated.SetScaleY(m_fSelectSize);
		}
	}

	float fAlpha = 1-(m_SpriteAnimated.GetScaleX() / m_fSelectSize);
	m_SpriteAnimated.SetColor((int)(fAlpha*255), 0, 0, 255);

}

void CCursor::DisplayDebugInfo()
{
	CUnitManager* pUnitManager = CGame::GetInstance().GetSession()->GetUnitManager();
		unsigned int iUnitTotal = pUnitManager->GetUnitTotal();
		CUnit* pUnit = 0;
		
		m_BoundingBox.SetSize(32*m_fSelectSize, 32*m_fSelectSize);
		m_BoundingBox.UpdatePosition(m_fSelectedX, m_fSelectedY);

		C2DBoundingBox* pBB = &m_BoundingBox;

		CLantern* pNearestLantern = 0;
		CLantern* pLantern = 0;

		CLanternManager* pLanternManager = CGame::GetInstance().GetSession()->GetLanternManager();

		C2DBoundingBox tempbox;
		tempbox.UpdatePosition(m_PosVec.x, m_PosVec.y);
		tempbox.SetSize(20, 20);



		//Lantern-Cursor-Collision

		for(unsigned int i = 0; i < pLanternManager->GetLanternTotal(); ++i)
		{
			pLantern = pLanternManager->GetLantern(i);
			pLantern->SetSelected(false);
			if((&tempbox)->CircleCollsionCheck(pLantern->GetBoundingBox()))
			{
				if(!pNearestLantern)
				{
					pNearestLantern = pLantern;
				}
				else
				{
					D3DXVECTOR2 vNearestDistance = m_PosVec - *(pNearestLantern->GetPosition());
					D3DXVECTOR2 vDistance = m_PosVec - *(pLantern->GetPosition());
					float fNearestDistance = D3DXVec2Length(&vNearestDistance);
					float fDistance = D3DXVec2Length(&vDistance);

					if(fNearestDistance < fDistance)
					{
						pNearestLantern = pLantern;
					}
				}
			}
		}

		CTextBox TempTB;
		TempTB.Initialise(64, 0, 0, 3, true, false, 1);

		if(pNearestLantern)
		{
			TempTB.m_fX = (float)CGame::GetInstance().m_Mouse.GetX();
			TempTB.m_fY = (float)(CGame::GetInstance().m_iWindowHeight - CGame::GetInstance().m_Mouse.GetY());
			TempTB.SetString("Units: " + IntToString(pNearestLantern->GetNearbyUnitTotal()));
			TempTB.Draw();
			TempTB.m_fY -= 10;
			TempTB.SetString("Pos: " + IntToString((int)pNearestLantern->GetX()) + ", " +  IntToString((int)pNearestLantern->GetY()));
			TempTB.Draw();

			if(pNearestLantern->IsFrontlineLantern())
			{
				TempTB.m_fY -= 10;
				TempTB.SetString("FRONTLINE");
				TempTB.Draw();
			}
		}


		//Unit-Cursor-Collision
		for(unsigned int z = 0; z < iUnitTotal; ++z)
		{
			pUnit = pUnitManager->GetUnit(z);


			if(pUnit->IsAlive() && pUnit->GetBoundingBox()->CircleCollsionCheck(&tempbox))
			{
				TempTB.m_fX = (CGame::GetInstance().m_Mouse.GetPosition(MOUSEPOS_X) + (pUnit->GetX() - GetX()));
				TempTB.m_fY = CGame::GetInstance().m_iWindowHeight - (CGame::GetInstance().m_Mouse.GetPosition(MOUSEPOS_Y) + (GetY() - pUnit->GetY()));
				if(pUnit->HasTargetCoord())
				{
					TempTB.SetString("Target:" + IntToString((int)pUnit->GetTargetCoord().x) + ", " + IntToString((int)pUnit->GetTargetCoord().y));
				}
				else
				{
					TempTB.SetString("No Target");
				}
				TempTB.Draw();
			}			
		}

}

void CCursor::CalculateZoomPosition()
{
	CSpriteManager* pSpriteManager = CGame::GetInstance().GetSpriteManager();

	m_PosVec.x = (float)CGame::GetInstance().m_Mouse.GetPosition(MOUSEPOS_X);
	m_PosVec.y = (float)CGame::GetInstance().m_iWindowHeight - CGame::GetInstance().m_Mouse.GetPosition(MOUSEPOS_Y);

	float fScreenCentreX = 400;
	float fScreenCentreY = 300;

	float fZoom = (pSpriteManager->GetZoom());
	float fInvertZoom = 1/(pSpriteManager->GetZoom());

	float m_fZoomOffsetX = (m_PosVec.x - fScreenCentreX)*(fInvertZoom-1) - (pSpriteManager->GetDrawOffsetX());
	float m_fZoomOffsetY = (m_PosVec.y - fScreenCentreY)*(fInvertZoom-1) - (pSpriteManager->GetDrawOffsetY());

	m_PosVec.x = m_PosVec.x +m_fZoomOffsetX;
	m_PosVec.y = m_PosVec.y +m_fZoomOffsetY;

}
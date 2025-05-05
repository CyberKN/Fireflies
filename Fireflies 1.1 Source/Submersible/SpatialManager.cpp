// Library Includes

// Local Includes

// This include
#include "SpatialManager.h"
#include "Game.h"
#include "SpatialNode.h"

// Constants

// Static Variables


CSpatialManager* CSpatialManager::s_pSpatialManager = 0;

// Static Function Prototypes

// Implementation

/**
* Constructor
*/
CSpatialManager::CSpatialManager()
{

}

/**
* Destructor
*/
CSpatialManager::~CSpatialManager()
{

	for(unsigned int i = 0; i < m_iGridSizeX; ++i)
	{
		for(unsigned int k = 0; k < m_iGridSizeY; ++k)
		{
			delete m_DynamicGrid[i][k];
			m_DynamicGrid[i][k] = 0;
		}
	}

	for(unsigned int i = 0; i < m_iEnemyGridSizeX; ++i)
	{
		for(unsigned int k = 0; k < m_iEnemyGridSizeY; ++k)
		{
			delete m_DynamicEnemyGrid[i][k];
			m_DynamicEnemyGrid[i][k] = 0;
		}
	}
}

/**
* Initialises the Spatial Grid For use
*/
void CSpatialManager::Initialise()
{
	CLanternManager* pLanternManager = CGame::GetInstance().GetSession()->GetLanternManager();
	float fLeftEdge = pLanternManager->GetLantern(0)->GetX();
	float fRightEdge = pLanternManager->GetLantern(0)->GetX();
	float fTopEdge = pLanternManager->GetLantern(0)->GetY();
	float fBottomEdge = pLanternManager->GetLantern(0)->GetY();

	for(unsigned int i = 1 ; i < pLanternManager->GetLanternTotal(); ++i)
	{
		if(pLanternManager->GetLantern(i)->GetX() < fLeftEdge)
		{
			fLeftEdge = pLanternManager->GetLantern(i)->GetX();
		}

		if(pLanternManager->GetLantern(i)->GetX() > fRightEdge)
		{
			fRightEdge = pLanternManager->GetLantern(i)->GetX();
		}

		if(pLanternManager->GetLantern(i)->GetY() > fTopEdge)
		{
			fTopEdge = pLanternManager->GetLantern(i)->GetY();
		}

		if(pLanternManager->GetLantern(i)->GetY() < fBottomEdge)
		{
			fBottomEdge = pLanternManager->GetLantern(i)->GetY();
		}
	}

	fLeftEdge -=200;
	fRightEdge +=200;
	fTopEdge +=200;
	fBottomEdge -=200;

	TestSprite.Initialise(SPRITE_Block4Sides, 1);
	TestSprite.TranslateAbsolute((fLeftEdge+fRightEdge)*0.5f, (fBottomEdge+fTopEdge)*0.5f);
	TestSprite.SetScaleX((fRightEdge-fLeftEdge)/64);
	TestSprite.SetScaleY((fTopEdge-fBottomEdge)/64);
	TestSprite.SetColor(200, 255, 0, 0);


	float fTotalGridSizeX = fRightEdge - fLeftEdge;
	float fTotalGridSizeY = fTopEdge - fBottomEdge;

	//Friendly Grid
	m_iGridSizeX = (int)(fTotalGridSizeX/k_fNodeSize);
	m_iGridSizeY = (int)(fTotalGridSizeY/k_fNodeSize);

	m_iGridOffsetX = (int)fLeftEdge;
	m_iGridOffsetY = (int)fBottomEdge;

	m_DynamicGrid.resize(m_iGridSizeX);
	for(unsigned int i = 0; i < m_DynamicGrid.size(); ++i)
	{
		m_DynamicGrid[i].resize(m_iGridSizeY);
	}

	for(unsigned int i = 0; i < m_iGridSizeX; ++i)
	{
		for(unsigned int k = 0; k < m_iGridSizeY; ++k)
		{
			m_DynamicGrid[i][k] = new CSpatialNode;
			m_DynamicGrid[i][k]->Initialise(((float)i+0.5f)*k_fNodeSize + fLeftEdge,
											 ((float)k+0.5f)*k_fNodeSize+ fBottomEdge,
											 k_fNodeSize,
											 k_fNodeSize);
		}
	}

	//Enemy Grid
	m_iEnemyGridSizeX = (int)(fTotalGridSizeX/k_fEnemyNodeSize);
	m_iEnemyGridSizeY = (int)(fTotalGridSizeY/k_fEnemyNodeSize);

	m_DynamicEnemyGrid.resize(m_iEnemyGridSizeX);
	for(unsigned int i = 0; i < m_iEnemyGridSizeX; ++i)
	{
		m_DynamicEnemyGrid[i].resize(m_iEnemyGridSizeY);
	}

	for(unsigned int i = 0; i < m_iEnemyGridSizeX; ++i)
	{
		for(unsigned int k = 0; k < m_iEnemyGridSizeY; ++k)
		{
			m_DynamicEnemyGrid[i][k] = new CSpatialNode;
			m_DynamicEnemyGrid[i][k]->Initialise(((float)i+0.5f)*k_fEnemyNodeSize + fLeftEdge,
											 ((float)k+0.5f)*k_fEnemyNodeSize+ fBottomEdge,
											 k_fEnemyNodeSize,
											 k_fEnemyNodeSize);
		}
	}


	////Friendly Grid
	//float fGridSizeX = (float)(static_cast<unsigned int>(CGame::GetInstance().m_iWindowWidth)/k_uGridSizeX);
	//float fGridSizeY = (float)(static_cast<unsigned int>(CGame::GetInstance().m_iWindowHeight)/k_uGridSizeY);

	//for(unsigned int i = 0; i < k_uGridSizeX; ++i)
	//{
	//	for(unsigned int k = 0; k < k_uGridSizeY; ++k)
	//	{
	//		m_Grid[i][k] = new CSpatialNode;
	//		m_Grid[i][k]->Initialise(((float)i+0.5f)*fGridSizeX,
	//								 ((float)k+0.5f)*fGridSizeY,
	//								 fGridSizeX,
	//								 fGridSizeY);
	//	}
	//}

	////Enemy Grid
	//fGridSizeX = (float)(static_cast<unsigned int>(CGame::GetInstance().m_iWindowWidth)/k_uEnemyGridSizeX);
	//fGridSizeY = (float)(static_cast<unsigned int>(CGame::GetInstance().m_iWindowHeight)/k_uEnemyGridSizeY);

	//for(unsigned int i = 0; i < k_uEnemyGridSizeX; ++i)
	//{
	//	for(unsigned int k = 0; k < k_uEnemyGridSizeY; ++k)
	//	{
	//		m_EnemyGrid[i][k] = new CSpatialNode;
	//		m_EnemyGrid[i][k]->Initialise(((float)i+0.5f)*fGridSizeX,
	//								 ((float)k+0.5f)*fGridSizeY,
	//								 fGridSizeX,
	//								 fGridSizeY);
	//	}
	//}

}

/**
* Gets a pointer to the instance of the Spatial Manager, and creates one if it doesn't exist yet.
* @return a pointer to the spatial Manager
*/
CSpatialManager*
CSpatialManager::GetInstance()
{
	if(s_pSpatialManager == 0)
	{
		s_pSpatialManager = new CSpatialManager();
	}

	return(s_pSpatialManager);
}

/**
* Deletes the spatial manager object
*/
void CSpatialManager::DestroyInstance()
{
	delete s_pSpatialManager;
	s_pSpatialManager = 0;
}

/**
* Draws Each node; Should only be used for debugging purposes.
*/
void CSpatialManager::Draw()
{
	for(unsigned int i = 0; i < m_iGridSizeX; ++i)
	{
		for(unsigned int k = 0; k < m_iGridSizeY; ++k)
		{
			m_DynamicGrid[i][k]->Draw();
		}
	}

	for(unsigned int i = 0; i < m_iEnemyGridSizeX; ++i)
	{
		for(unsigned int k = 0; k < m_iEnemyGridSizeY; ++k)
		{
			//m_DynamicEnemyGrid[i][k]->Draw();
		}
	}
}


/**
* Determines which nodes contain which units using Hash values, and populates each node's unit containers with pointers to those units.
*/
void CSpatialManager::PopulateGridUsingHashVal()
{
	CUnitManager* pUnitManager  = CGame::GetInstance().GetSession()->GetUnitManager();
	unsigned int iUnitTotal = pUnitManager->GetUnitTotal();
	CUnit* pUnit = 0;
	unsigned int i;
	unsigned int z;
	CSpatialNode* pNode = 0;
	C2DBoundingBox* pBB = 0;
	D3DXVECTOR2* pPoint = 0;
	int x;
	int y; 
	float fX;
	float fY;

	int iWindowX = CGame::GetInstance().m_iWindowWidth;
	int iWindowY = CGame::GetInstance().m_iWindowHeight;


	for(z = 0; z < iUnitTotal; ++z)
	{
		pUnit = pUnitManager->GetUnit(z);
		if(pUnit->IsAlive())
		{
			pBB = pUnit->GetBoundingBox();
			for(i = 0; i < 4; ++i)
			{

				pPoint = &pBB->PointVec1[i];

				fX = pPoint->x-(float)m_iGridOffsetX;
				fX /= m_iGridSizeX*k_fNodeSize;
				fX *= m_iGridSizeX;

				fY = pPoint->y-(float)m_iGridOffsetY;
				fY /= m_iGridSizeX*k_fNodeSize;
				fY *= m_iGridSizeY;

				
				x = ClampInt(int(fX), 0, (m_iGridSizeX-1));
				y = ClampInt(int(fY), 0, (m_iGridSizeY-1));

				pNode = m_DynamicGrid[x][y];

				if(!pUnit->IsMatchedWithContainer(pNode))
				{
					pNode->AddUnit(pUnit);
					pUnit->AddContainer(pNode);
				}
			}
		}			
	}

	//Enemy Grid
	pUnit = 0;
	pNode = 0;
	pBB = 0;
	pPoint = 0;	

	
	for(z = 0; z < iUnitTotal; ++z)
	{
		pUnit = pUnitManager->GetUnit(z);
		if(pUnit->IsAlive())
		{
			pBB = pUnit->GetBoundingBox();
			for(i = 0; i < 4; ++i)
			{

				pPoint = &pBB->PointVec1[i];

				fX = pPoint->x-(float)m_iGridOffsetX;
				fX /= m_iEnemyGridSizeX*k_fEnemyNodeSize;
				fX *= m_iEnemyGridSizeX;

				fY = pPoint->y-(float)m_iGridOffsetY;
				fY /= m_iEnemyGridSizeY*k_fEnemyNodeSize;
				fY *= m_iEnemyGridSizeY;

				
				x = ClampInt(int(fX), 0, (m_iEnemyGridSizeX-1));
				y = ClampInt(int(fY), 0, (m_iEnemyGridSizeY-1));

				pNode = m_DynamicEnemyGrid[x][y];

				if(!pUnit->IsMatchedWithContainer(pNode))
				{
					pNode->AddUnit(pUnit);
					pUnit->AddContainer(pNode);
				}
			}
		}			
	}

	/*for(z = 0; z < iUnitTotal; ++z)
	{
		pUnit = pUnitManager->GetUnit(z);
		if(pUnit->IsAlive())
		{
			pBB = pUnit->GetBoundingBox();
			for(i = 0; i < 4; ++i)
			{

				pPoint = &pBB->PointVec1[i];

				x = (int)((pPoint->x/iWindowX)*k_uEnemyGridSizeX);
				y = (int)((pPoint->y/iWindowY)*k_uEnemyGridSizeY);

				x = ClampInt(x, 0, (k_uEnemyGridSizeX-1));
				y = ClampInt(y, 0, (k_uEnemyGridSizeY-1));

				pNode = m_EnemyGrid[x][y];

				if(!pUnit->IsMatchedWithContainerEnemy(pNode))
				{
					pNode->AddUnit(pUnit);
					pUnit->AddContainerEnemy(pNode);
				}
			}
		}			
	}*/
}

/**
* Resets the spatial grid's nodes' unit containers.
*/
void CSpatialManager::EmptyGrid()
{
	unsigned int i;
	unsigned int k;
	CSpatialNode* pNode;

	//for(i = 0; i < k_uGridSizeX; ++i)
	//{
	//	for(k = 0; k < k_uGridSizeY; ++k)
	//	{
	//		pNode = m_Grid[i][k];
	//		pNode->Empty();

	//	}
	//}

	//for(i = 0; i < k_uEnemyGridSizeX; ++i)
	//{
	//	for(k = 0; k < k_uEnemyGridSizeY; ++k)
	//	{
	//		pNode = m_EnemyGrid[i][k];
	//		pNode->Empty();

	//	}
	//}

	for(i = 0; i < m_iGridSizeX; ++i)
	{
		for(k = 0; k < m_iGridSizeY; ++k)
		{
			pNode = m_DynamicGrid[i][k];
			pNode->Empty();

		}
	}

	for(i = 0; i < m_iEnemyGridSizeX; ++i)
	{
		for(k = 0; k < m_iEnemyGridSizeY; ++k)
		{
			pNode = m_DynamicEnemyGrid[i][k];
			pNode->Empty();

		}
	}

	CUnitManager* pUnitManager  = CGame::GetInstance().GetSession()->GetUnitManager();
	unsigned int iUnitTotal = pUnitManager->GetUnitTotal();
	unsigned int z;

	for(z = 0; z < iUnitTotal; ++z)
	{
		pUnitManager->GetUnit(z)->ResetContainers();
	}

	
}

/**
* Checks for and applies effect of unit-unit collision. 
*/
void CSpatialManager::ProcessCollisions()
{
	CUnitManager* pUnitManager  = CGame::GetInstance().GetSession()->GetUnitManager();
	unsigned int iUnitTotal = pUnitManager->GetUnitTotal();
	CUnit* pUnit1 = 0;
	CUnit* pUnit2 = 0;
	unsigned int i;
	unsigned int k;
	unsigned int z;
	unsigned int n;
	unsigned int iStartFromHere = 0;
	CSpatialNode* pNode = 0;
	C2DBoundingBox* pBB = 0;
	bool bAllied;
	unsigned int iXSize = m_DynamicGrid.size();
	unsigned int iYSize = m_DynamicGrid[0].size();

	//Loop Through all squares along the X Axis
	for(i = 0; i < iXSize; ++i)
	{
		//Loop Through all squares along the Y Axis
		for(k = 0; k < iYSize; ++k)
		{
			pNode = m_DynamicGrid[i][k];
			iUnitTotal = pNode->GetUnitTotal();
			iStartFromHere = 0;
			
			//For Each Unit in this square
			for(z = 0; z < iUnitTotal; ++z)
			{

				pUnit1 = pNode->GetUnit(z);
				if(!pUnit1->IsAlive())
				{
					//If It's Dead, Skip It.
					continue;
				}
				pBB = pUnit1->GetBoundingBox();

				//For every other Unit in this square
				for(n = iStartFromHere; n < iUnitTotal; ++n)
				{
					pUnit2 = pNode->GetUnit(n);

					if(!pUnit2->IsAlive())
					{
						//If It's Dead, Skip It.
						continue;
					}

					if(pUnit1 != pUnit2)
					{
						if(pUnit2->GetPotentialField()->CircleCollsionCheck(pBB))
						{
							//Apply Potential Field effects - Repel if allied, attract if opposed
							bAllied = pUnit1->GetPlayerID() == pUnit2->GetPlayerID();
							pUnit2->ApplyPotentialField(pUnit1, bAllied);
							
							if(!bAllied && pUnit2->GetBoundingBox()->BoxCollsionCheck(pBB))
							{
								if(pUnit1->GetDeathlockUnit() == pUnit2)
								{
									pUnit2->Kill();
									pUnit1->Kill();
									CGame::GetInstance().GetSession()->GetExplosionManager()->CreateExplosion(pUnit1->GetX(), pUnit1->GetY());
								}
								//Break out of the loop;
								n = iUnitTotal;
							}	
						}
					}
				}
				++iStartFromHere;
			}
		}
	}

	
}

/**
* Checks for and applies effect of unit-unit collision (Enemies Only). 
*/
void CSpatialManager::ProcessEnemyCollisions()
{
	CUnitManager* pUnitManager  = CGame::GetInstance().GetSession()->GetUnitManager();
	unsigned int iUnitTotal = pUnitManager->GetUnitTotal();
	CUnit* pUnit1 = 0;
	CUnit* pUnit2 = 0;
	unsigned int i;
	unsigned int k;
	unsigned int z;
	unsigned int n;
	unsigned int iStartFromHere = 0;
	CSpatialNode* pNode = 0;
	C2DBoundingBox* pBB = 0;

	//Loop Through all squares along the X Axis
	for(i = 0; i < m_iEnemyGridSizeX; ++i)
	{
		//Loop Through all squares along the Y Axis
		for(k = 0; k < m_iEnemyGridSizeY; ++k)
		{
			pNode = m_DynamicEnemyGrid[i][k];
			iUnitTotal = pNode->GetUnitTotal();
			iStartFromHere = 0;
			
			//For Each Unit in this square
			for(z = 0; z < iUnitTotal; ++z)
			{

				pUnit1 = pNode->GetUnit(z);
				if(!pUnit1->IsAlive() || pUnit1->IsDeathlocked())
				{
					//If It's Dead, Skip It.
					continue;
				}
				pBB = pUnit1->GetBoundingBox();

				//For every other Unit in this square
				for(n = iStartFromHere; n < iUnitTotal; ++n)
				{
					pUnit2 = pNode->GetUnit(n);

					if(!pUnit2->IsAlive() || pUnit2->IsDeathlocked())
					{
						//If It's Dead, Skip It.
						continue;
					}

					if(pUnit1->GetPlayerID() == pUnit2->GetPlayerID())
					{
						//Same Team. Skip It.
						continue;
					}

					if(pUnit1 != pUnit2)
					{
						if(pUnit2->GetEnemyPotentialField()->CircleCollsionCheck(pBB))
						{
							//pUnit1->Kill();
							//pUnit2->Kill();
							pUnit1->DeathlockUnit(pUnit2);
							pUnit2->DeathlockUnit(pUnit1);
							
							//Break out of the loop;
							n = iUnitTotal;

						}
					}
				}
				++iStartFromHere;
			}
		}
	}

	
}
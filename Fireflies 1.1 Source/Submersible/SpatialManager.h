#pragma once

#if !defined(__SpatialManager_H__)
#define __SpatialManager_H__

// Library Includes

#include "utils.h"
#include "SpriteDataShell.h"
// Local Includes

// Types

// Constants

const unsigned int k_uGridSizeX = 50;
const unsigned int k_uGridSizeY = 50;

const unsigned int k_uEnemyGridSizeX = 20;
const unsigned int k_uEnemyGridSizeY = 20;

const float k_fNodeSize = 16;
const float k_fEnemyNodeSize = 40;

// Prototypes

class CSpatialNode;

class CSpatialManager
{
// Member Functions
public:
	CSpatialManager();
	~CSpatialManager();
	static CSpatialManager* GetInstance();
	static void DestroyInstance();
	void ProcessCollisions();
	void ProcessEnemyCollisions();
	void Initialise();
	void PopulateGridUsingHashVal();
	void EmptyGrid();
	void Draw();

protected:

private:

// Member Variables
public:

protected:

	static CSpatialManager* s_pSpatialManager;

	//CSpatialNode* m_Grid[k_uGridSizeX][k_uGridSizeY];

	//CSpatialNode* m_EnemyGrid[k_uEnemyGridSizeX][k_uEnemyGridSizeY];

	std::vector<std::vector<CSpatialNode*>> m_DynamicGrid;
	std::vector<std::vector<CSpatialNode*>> m_DynamicEnemyGrid;

	int m_iGridOffsetX;
	int m_iGridOffsetY;

	unsigned int m_iGridSizeX;
	unsigned int m_iGridSizeY;

	
	unsigned int m_iEnemyGridSizeX;
	unsigned int m_iEnemyGridSizeY;

	CSpriteDataShell TestSprite;



private:

};

#endif // __SpatialManager_H__

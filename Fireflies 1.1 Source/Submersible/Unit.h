#pragma once

#if !defined(__Unit_H__)
#define __Unit_H__

// Library Includes

// Local Includes

#include "GameEntity.h"

// Types

enum EPlayerID
{
	PLAYER_1,
	PLAYER_2,
	PLAYER_3,
	PLAYER_N
};


enum EUnitEffect
{
	UE_None,
	UE_Heal,
	UE_UpgradeOne,
	UE_UpgradeTwo,
	UE_UpgradeThree,
	UE_Capture,
	UE_Ignore
};

enum EUnitState
{
	US_Dead,
	US_Deathlocked,
	US_Moving,
	US_Idle
};

// Constants

const float k_fMaxUnitSpeed = 80;

// Prototypes

class CSpatialNode;
class CLantern;


class CUnit : public CGameEntity
{
// Member Functions
public:
	CUnit();
	~CUnit();
	void Initialise();
	void Process(float _fDeltaTick);
	void SetTarget(float _fX, float _fY);

	void ResetContainers();
	bool AddContainer(CSpatialNode* _pContainerNode);
	bool IsMatchedWithContainer(CSpatialNode* _pContainerNode);

	
	bool AddContainerEnemy(CSpatialNode* _pContainerNode);
	bool IsMatchedWithContainerEnemy(CSpatialNode* _pContainerNode);

	C2DBoundingBox* GetPotentialField(){return(&m_PField);};
	C2DBoundingBox* GetEnemyPotentialField(){return(&m_EnemyPField);};

	void ApplyPotentialField(CUnit* _pUnit, bool _bAllied);
	void ApplyLanternOrbitVelocity(CLantern* _pLantern, float _fDeltaTick);

	void CheckLanternCollision(CLantern* _pLantern);

	EUnitEffect GetLanternEffect(){return(m_LanternEffect);};
	void SetLanternEffect(EUnitEffect _e){m_LanternEffect = _e;};
	void DeathlockUnit(CUnit* _pOpposingUnit);
	bool IsDeathlocked(){return(m_bDeathlocked);};
	CUnit* GetDeathlockUnit(){return(m_pLockedUnit);};
	float GetSpriteAlpha(){return(m_fAlpha);};




	void SetPlayerID(EPlayerID _PlayerID);
	EPlayerID& GetPlayerID(){return(m_PlayerID);};

	void SetSelected(bool _b);
	bool IsSelected(){return(m_bSelected);};

	bool& IsAlive(){return(m_bAlive);};
	void Kill();

	D3DXVECTOR2 GetTargetCoord(){return(m_vTarget);};

	bool HasTargetCoord(){return(m_vTarget.x != 99999);};

	
	void ClearTarget();




protected:

private:

// Member Variables
public:

	
	CSpatialNode* m_vContainerNodes[4];
	CSpatialNode* m_vContainerNodesEnemy[4];
	C2DBoundingBox m_PField;
	C2DBoundingBox m_EnemyPField;
	float m_fRange;
	float m_fAliveTime;


protected:
	EUnitState m_UnitState;
	EUnitEffect m_LanternEffect;
	bool m_bSelected;
	EPlayerID m_PlayerID;
	bool m_bAlive;
	bool m_bDeathlocked;
	CUnit* m_pLockedUnit;
	float m_fTwinkleTimer;
	float m_fAlpha;
	D3DXVECTOR2 m_vTarget;



private:

};

#endif // __Unit_H__

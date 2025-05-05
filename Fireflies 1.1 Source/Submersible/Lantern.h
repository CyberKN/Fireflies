#pragma once

#if !defined(__Lantern_H__)
#define __Lantern_H__

// Library Includes
#include "GameEntity.h"
#include "Unit.h"

// Local Includes

// Types

// Constants

// Prototypes


class CLantern : public CGameEntity
{
// Member Functions
public:
	CLantern();
	~CLantern();
	void Initialise(EPlayerID _PlayerID);
	void Process(float _fDeltaTick);
	void Draw();
	void SpawnUnits();
	void DrawHealthBarSprite();
	void ApplyUnit(CUnit* _pUnit);

	EPlayerID GetPlayerID(){return(m_PlayerID);};
	void SetPlayerID(EPlayerID _PlayerID);

	float GetHealth(){return(m_fHealth);};
	void SetHealth(float _fHealth){m_fHealth = _fHealth;};

	float GetUpgradeStatus(){return(m_fUpgradeStatus);};

	void SetLevel(int _iLevel){m_iLevel = _iLevel;};
	int GetLevel(){return(m_iLevel);};
	int GetMaxLevel(){return(m_iMaxLevel);};
	void SetMaxLevel(int _iMaxLevel){m_iMaxLevel = _iMaxLevel;};

	EUnitEffect GetUnitEffect(){return(m_FriendlyUnitEffect);};
	void SetNewEffect(EUnitEffect _eEffect);
	void DetermineCurrentEffect();

	bool IsSelected(){return(m_bSelected);};
	void SetSelected(bool _b);

	bool IsAligned(){return(m_bAligned);};
	void SetAligned(bool _b){m_bAligned = _b;};

	void SetupUnitTarget(CUnit* _pUnit);

	void PreventCongestion(CUnit* _pUnit);

	void AddNearbyUnitToList(CUnit* _pUnit);
	
	CUnit* GetNearbyUnit(unsigned int _i){return(m_vecNearbyUnits[_i]);};
	unsigned int GetNearbyUnitTotal(){return(m_iNearbyUnitCount);};
	void RepopulateNearbyUnitList();

	//AI Functions
	unsigned int GetNearbyFriendlyUnitTotal(EPlayerID _PlayerID, bool _bIdle);
	unsigned int GetNearbyEnemyUnitTotal(EPlayerID _PlayerID);
	void OrderUnitsToTarget(EPlayerID _PlayerID, CLantern* _pTargetLantern);
	void OrderUnitsToTargetSoft(EPlayerID _PlayerID, CLantern* _pTargetLantern);
	CLantern* FindNearbyUnclaimedBase(EPlayerID _PlayerID);
	CLantern* FindNearbyEnemyBase(EPlayerID _PlayerID);
	bool IsThisTargetAcceptableRisk(CLantern* _pTargetLantern);
	CLantern* GetNearbyBaseUnderAttack(EPlayerID _PlayerID);
	bool IsFrontlineLantern();
	void CheckIfFrontlineLantern();
	CLantern* GetNearbyFrontlineLantern();
	void SpawnInitUnits();

	//Editor Function
	void Update();




protected:

private:

// Member Variables
public:

protected:

	int m_iLevel;
	int m_iMaxLevel;
	EPlayerID m_PlayerID;
	float m_fSpawnTimer;
	float m_fHealth;
	float m_fUpgradeStatus;
	CSpriteDataShell m_HealthSprite;
	bool m_bSelected;
	bool m_bAligned;
	EUnitEffect m_FriendlyUnitEffect;
	EUnitEffect m_EnemyUnitEffect;
	unsigned int m_iUnitsSpawned;
	std::vector<CUnit*> m_vecNearbyUnits;
	unsigned int m_iNearbyUnitCount;
	bool m_bFrontline;
	CSpriteDataShell m_Sprite2;
	CSpriteDataShell m_Sprite3;
	CSpriteDataShell m_OverSprite;
	CSpriteDataShell m_UpgradeSprite;
	std::vector<CSpriteDataShell*> m_vecSprites;



private:

};

#endif // __Lantern_H__

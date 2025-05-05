#pragma once

#if !defined(__LanternManager_H__)
#define __LanternManager_H__

// Library Includes

#include "utils.h"
#include "Unit.h"

// Local Includes

// Types

// Constants

// Prototypes

class CLantern;

class CLanternManager
{
// Member Functions
public:
	CLanternManager();
	~CLanternManager();
	void Initialise(std::string _strLevelName);
	void Process(float _fDeltaTick);
	void Draw();
	void DrawHealthBarSprites();
	void AddLantern(float _fX, float _fY, int _iLevel, EPlayerID _PlayerID);
	CLantern* GetLantern(int _iIndex);
	unsigned int GetLanternTotal();
	void Load(std::string _strLevelName);

protected:

private:

// Member Variables
public:

protected:

	std::vector<CLantern*> m_vecLanterns;

private:

};

#endif // __LanternManager_H__

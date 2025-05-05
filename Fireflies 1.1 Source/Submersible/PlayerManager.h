#pragma once

#if !defined(__PlayerManager_H__)
#define __PlayerManager_H__

// Library Includes

// Local Includes
#include "Player.h"

// Types

// Constants

// Prototypes


class CPlayerManager
{
// Member Functions
public:
	CPlayerManager();
	~CPlayerManager();
	void Initialise();
	CPlayer* GetPlayer(unsigned int _i){return(m_vecPlayers[_i]);};
	void SortUnits();
	void Process(float _fDeltaTick);

protected:

private:

// Member Variables
public:
	std::vector<CPlayer*> m_vecPlayers;

protected:

private:

};

#endif // __PlayerManager_H__

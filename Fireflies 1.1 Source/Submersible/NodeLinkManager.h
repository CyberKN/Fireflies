#pragma once

#if !defined(__NodeLinkManager_H__)
#define __NodeLinkManager_H__

// Library Includes

// Local Includes
#include "NodeLink.h"
#include "LanternManager.h"

// Types

// Constants

// Prototypes


class CNodeLinkManager
{
// Member Functions
public:
	CNodeLinkManager();
	~CNodeLinkManager();
	void Initialise(CLanternManager* _pLanternManager);
	bool IsConnectionDesirable(CLantern* pLantern1, CLantern* pLantern2);
	void Process(float _fDeltatick);
	void Draw();

protected:

private:

// Member Variables
public:

	CLanternManager* m_pLanternManager;
	std::vector<CNodeLink*> m_vecLinks;

protected:

private:

};

#endif // __NodeLinkManager_H__

#pragma once

#if !defined(__NodeLink_H__)
#define __NodeLink_H__

// Library Includes

// Local Includes
#include "GameEntity.h"

// Types

// Constants

// Prototypes

class CLantern;


class CNodeLink : public CGameEntity
{
// Member Functions
public:
	CNodeLink();
	~CNodeLink();
	void Initialise(CLantern* _pStartPointLantern, CLantern* _pEndPointLantern);
	void Process(float _fDeltaTick);
	void Draw();
	D3DXVECTOR2& GetStartPoint(){return(m_vStartPoint);};
	D3DXVECTOR2& GetEndPoint(){return(m_vEndPoint);};
	CLantern* GetStartLantern(){return(m_pStartLantern);};
	CLantern* GetEndLantern(){return(m_pEndLantern);};

protected:

private:

// Member Variables
public:


protected:

	D3DXVECTOR2 m_vStartPoint;
	D3DXVECTOR2 m_vEndPoint;
	CLantern* m_pStartLantern;
	CLantern* m_pEndLantern;
	bool m_bStartToEnd;

	CSpriteDataShell m_PulseSprite;
	float m_fPulseTimer;

private:

};

#endif // __NodeLink_H__

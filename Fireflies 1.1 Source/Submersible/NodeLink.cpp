// Library Includes

// Local Includes
#include "Lantern.h"

// This include
#include "NodeLink.h"

// Constants

// Static Variables

// Static Function Prototypes

// Implementation

CNodeLink::CNodeLink()
{
	m_fPulseTimer = 0;
	m_pStartLantern = 0;
	m_pEndLantern = 0;
	m_bStartToEnd = true;

}

CNodeLink::~CNodeLink()
{
	m_pStartLantern = 0;
	m_pEndLantern = 0;
}

void CNodeLink::Initialise(CLantern* _pStartPointLantern, CLantern* _pEndPointLantern)
{
	m_pStartLantern = _pStartPointLantern;
	m_pEndLantern = _pEndPointLantern;

	D3DXVECTOR2 _vStartPoint = *_pStartPointLantern->GetPosition();
	D3DXVECTOR2 _vEndPoint = *_pEndPointLantern->GetPosition();

	if(_vStartPoint.x < _vEndPoint.x)
	{
		m_vStartPoint = _vStartPoint;
		m_vEndPoint = _vEndPoint;
	}
	else
	{
		m_vStartPoint = _vEndPoint;
		m_vEndPoint = _vStartPoint;
	}

	
	D3DXVECTOR2 vDist = m_vEndPoint - m_vStartPoint;
	float fDist = D3DXVec2Length(&vDist);

	m_Sprite.Initialise(SPRITE_Link, 0.05f);
	m_Sprite.SetColor(100, 0, 255, 255);
	
	m_Sprite.SetScaleY(fDist/300.0f);

	D3DXVec2Normalize(&vDist, &vDist);

	D3DXVECTOR2 vUp = D3DXVECTOR2(0, 1);

	float fDot = D3DXVec2Dot(&vUp, &vDist);

	

	m_PosVec = m_vEndPoint + m_vStartPoint;

	m_PosVec *= 0.5f;

	m_fRotation = acosf(fDot);


	m_Sprite.SetRotate(m_fRotation);

	m_PulseSprite.Initialise(SPRITE_Pulse, 0.07f);
	m_PulseSprite.SetScaleY(0.1f);
	m_PulseSprite.SetRotate(m_fRotation);
	m_PulseSprite.SetColor(100, 0, 255, 255);
}

void CNodeLink::Process(float _fDeltaTick)
{
	m_fPulseTimer += _fDeltaTick;

	if(m_fPulseTimer > 0)
	{
		if(m_fPulseTimer < 1)
		{
			float fScalar = m_fPulseTimer;
			D3DXVECTOR2 vLine;
			D3DXVECTOR2 vStart;
			D3DXVECTOR2 vPos;
			if(m_bStartToEnd)
			{
				vLine = m_vEndPoint - m_vStartPoint;
				vStart = m_vStartPoint;
			}
			else
			{
				vLine = m_vStartPoint - m_vEndPoint;
				vStart = m_vEndPoint;
			}
			vPos = vStart + (vLine*fScalar);
			m_PulseSprite.TranslateAbsolute(vPos.x, vPos.y);

		}
		else
		{
			m_fPulseTimer = -1;
			m_bStartToEnd = ((rand() % 2) == 0);
		}
	}

	if(m_pStartLantern->GetPlayerID() == m_pEndLantern->GetPlayerID() 
	&& m_pStartLantern->GetPlayerID() != PLAYER_N 
	&& m_pStartLantern->IsAligned() 
	&& m_pEndLantern->IsAligned())
	{
		switch(m_pStartLantern->GetPlayerID())
		{
		case PLAYER_1:
			{
				m_Sprite.SetColor(100, 0, 0, 255);
			}
			break;
		case PLAYER_2:
			{
				m_Sprite.SetColor(100, 255, 0, 0);
			}
			break;
		case PLAYER_3:
			{
				m_Sprite.SetColor(100, 0, 255, 0);
			}
			break;
		}
	}
	else
	{
		m_Sprite.SetColor(100, 255, 255, 255);
	}

	m_PulseSprite.SetColor(m_Sprite.GetAlpha(), m_Sprite.GetRed(), m_Sprite.GetGreen(), m_Sprite.GetBlue());

}

void CNodeLink::Draw()
{
	CGameEntity::Draw();
	if(m_fPulseTimer > 0)
	{
		m_PulseSprite.Draw();
	}
}

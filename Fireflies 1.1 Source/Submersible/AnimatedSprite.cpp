// Library Includes

// Local Includes

#include "game.h"

// This Includes
#include "animatedsprite.h"

// Static Variables

// Static Function Prototypes

// Implementation


CAnimatedSprite::CAnimatedSprite()
:m_fFrameSpeed(1.0f)
,m_fTimeElapsed(0.0f)
,m_iCurrentSprite(0)
,m_iFrameCounter(0)
,m_iCircuitsCompleted(0)
{

}
CAnimatedSprite::~CAnimatedSprite()
{
	m_vectorFramesX.clear();
	m_vectorFramesY.clear();
	m_iCurrentSprite = 0;
}

void CAnimatedSprite::Process(float _fDeltaTick)
{
	m_fTimeElapsed += _fDeltaTick;

	if (m_fTimeElapsed >= m_fFrameSpeed && m_fFrameSpeed != 0.0f)
	{
		m_fTimeElapsed = 0.0f;
		++m_iCurrentSprite;

		if (m_iCurrentSprite >= static_cast<int>(m_vectorFramesX.size() ) )
		{
			m_iCurrentSprite = 0;

			++m_iCircuitsCompleted;
		}
	}

	
}

void CAnimatedSprite::Draw()
{
	if(m_pSprite)
	{
		float fXScale = m_fXScale;
		float fYScale = m_fYScale;

		if(!m_pManager->IsBatchDrawing())
		{
			m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
		}

		RECT ResizeRect;
		ResizeRect.top = static_cast<LONG>(0+m_vectorFramesY[m_iCurrentSprite]);
		ResizeRect.bottom = static_cast<LONG>(m_iSizeY+m_vectorFramesY[m_iCurrentSprite]);
		ResizeRect.left = static_cast<LONG>(0+m_vectorFramesX[m_iCurrentSprite]);
		ResizeRect.right = static_cast<LONG>(m_iSizeX+m_vectorFramesX[m_iCurrentSprite]);

		D3DXVECTOR2 spriteCentre=D3DXVECTOR2(m_iSizeX*0.5f*fXScale, m_iSizeY*0.5f*fYScale);

		// Screen position of the sprite
		D3DXVECTOR2 trans=D3DXVECTOR2(m_Pos.x-(spriteCentre.x),CGame::GetInstance().m_DirectX3DRenderer.m_iScreenHeight-(m_Pos.y+(spriteCentre.y)));

		//trans.x = (float)(int)trans.x;
		//trans.y = (float)(int)trans.y;
		//D3DXVECTOR2 trans=D3DXVECTOR2(m_Pos.x-(spriteCentre.x),m_Pos.y-(spriteCentre.y));

		
		float rotation = m_fRotation;

		// Build our matrix to rotate, scale and position our sprite
		D3DXMATRIX mat;

		D3DXVECTOR2 scaling(fXScale,fYScale);

		// out, scaling centre, scaling rotation, scaling, rotation centre, rotation, translation
		D3DXMatrixTransformation2D(&mat,NULL,0.0,&scaling,&spriteCentre,rotation,&trans);

		// Tell the sprite about the matrix
		m_pSprite->SetTransform(&mat);

		// Draw the sprite 
		m_pSprite->Draw(m_pSource,&ResizeRect,NULL,NULL, m_Colour);

		if(!m_pManager->IsBatchDrawing())
		{
			m_pSprite->End();
		}
	}
}


void CAnimatedSprite::AddFrame(int _iX, int _iY)
{
	m_vectorFramesX.push_back(_iX);
	m_vectorFramesY.push_back(_iY);
}

void CAnimatedSprite::SetRotate(float _fradians)
{
	m_fRotation = _fradians;
}

void CAnimatedSprite::SetSpeed(float _fSpeed)
{
	m_fFrameSpeed = _fSpeed;
}
void CAnimatedSprite::SetWidth(int _iWidth)
{
	m_iFrameWidth = _iWidth;
}
void CAnimatedSprite::SetHeight(int _iHeight)
{
	m_iFrameHeight = _iHeight;
}

int CAnimatedSprite::GetFrameWidth()
{
	return(m_iFrameWidth);
}

int CAnimatedSprite::GetFrameHeight()
{
	return(m_iFrameHeight);
}

void CAnimatedSprite::ClearVector()
{
	m_vectorFramesX.clear();
	m_vectorFramesY.clear();
	m_iCurrentSprite = 0;
}
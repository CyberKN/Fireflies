// Library Includes

// Local Includes

// This include
#include "2DBoundingBox.h"
#include <vector>
#include <d3dx9.h>
#include "Game.h"

// Constants

// Static Variables

// Static Function Prototypes

// Implementation

C2DBoundingBox::C2DBoundingBox()
{
	m_fX = 0;
	m_fY = 0;
	m_fHeight = 1;
	m_fWidth = 1;

	m_Sprite.Initialise(SPRITE_Block4Sides, 1);
	m_Sprite.SetColor(50, 255, 255, 255);

	pBox1 = new TMiniBox;
	pBox2 = 0;
}

C2DBoundingBox::~C2DBoundingBox()
{
	delete pBox1;
	pBox1 = 0;
	pBox2 = 0;

}

void C2DBoundingBox::UpdatePosition(float _fX, float _fY)
{
	m_fX = _fX;
	m_fY = _fY;

	pBox1->vPos.x = _fX;
	pBox1->vPos.y = _fY;

	
	PointVec1[0] = (D3DXVECTOR2(pBox1->vPos.x + pBox1->vSize.x, pBox1->vPos.y + pBox1->vSize.y));
	PointVec1[1] = (D3DXVECTOR2(pBox1->vPos.x - pBox1->vSize.x, pBox1->vPos.y + pBox1->vSize.y));
	PointVec1[2] = (D3DXVECTOR2(pBox1->vPos.x + pBox1->vSize.x, pBox1->vPos.y - pBox1->vSize.y));
	PointVec1[3] = (D3DXVECTOR2(pBox1->vPos.x - pBox1->vSize.x, pBox1->vPos.y - pBox1->vSize.y));


	m_Sprite.TranslateAbsolute(m_fX, m_fY);
}

void C2DBoundingBox::SetSize(float _fWidth, float _fHeight)
{
	m_fWidth = _fWidth;
	m_fHeight = _fHeight;

	pBox1->vSize.x = _fWidth*0.5f;
	pBox1->vSize.y = _fHeight*0.5f;

	m_Sprite.SetScaleX(m_fWidth/64.f);
	m_Sprite.SetScaleY(m_fHeight/64.f);
}

bool C2DBoundingBox::BoxCollsionCheck(C2DBoundingBox* _BoundingBox)
{
	CGame::GetInstance().GetSession()->m_iCollisionChecks++;

	pBox2 = _BoundingBox->pBox1;

	PointVec2[0] = _BoundingBox->PointVec1[0];
	PointVec2[1] = _BoundingBox->PointVec1[1];
	PointVec2[2] = _BoundingBox->PointVec1[2];
	PointVec2[3] = _BoundingBox->PointVec1[3];


	for(int i = 0; i < 4; ++i)
	{
		if((PointVec2[i].x < pBox1->vPos.x + pBox1->vSize.x)
		&& (PointVec2[i].x > pBox1->vPos.x - pBox1->vSize.x))
		{
			if((PointVec2[i].y < pBox1->vPos.y + pBox1->vSize.y)
			&& (PointVec2[i].y > pBox1->vPos.y - pBox1->vSize.y))
			{
				return(true);
			}

		}
	}

	for(int i = 0; i < 4; ++i)
	{
		if((PointVec1[i].x < pBox2->vPos.x + pBox2->vSize.x)
		&& (PointVec1[i].x > pBox2->vPos.x - pBox2->vSize.x))
		{
			if((PointVec1[i].y < pBox2->vPos.y + pBox2->vSize.y)
			&& (PointVec1[i].y > pBox2->vPos.y - pBox2->vSize.y))
			{
				return(true);
			}
		}
	}

	return(false);

}


bool C2DBoundingBox::CircleCollsionCheck(C2DBoundingBox* _BoundingBox)
{
	if(CGame::GetInstance().GetSession())
	{
		CGame::GetInstance().GetSession()->m_iCollisionChecks++;
	}

	bCircleCollision = false;

	a = m_fX - _BoundingBox->m_fX;

	b = m_fY - _BoundingBox->m_fY;

	c = (a*a) + (b*b);

	if(c <= (m_fWidth*m_fWidth) + (_BoundingBox->m_fWidth*_BoundingBox->m_fWidth))
	{
		bCircleCollision = true;
	}
		
	return(bCircleCollision);
}

void C2DBoundingBox::Draw()
{
	m_Sprite.Draw();
}


bool C2DBoundingBox::PointCollsionCheck(float _fX, float _fY)
{
	D3DXVECTOR2 vPoint = D3DXVECTOR2(_fX, _fY);

	if((vPoint.x < pBox1->vPos.x + pBox1->vSize.x)
	&& (vPoint.x > pBox1->vPos.x - pBox1->vSize.x))
	{
		if((vPoint.y < pBox1->vPos.y + pBox1->vSize.y)
		&& (vPoint.y > pBox1->vPos.y - pBox1->vSize.y))
		{
			return(true);
		}

	}

	return(false);

}

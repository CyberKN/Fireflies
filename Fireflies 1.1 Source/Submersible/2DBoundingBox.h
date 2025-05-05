#pragma once

#if !defined(__2DBoundingBox_H__)
#define __2DBoundingBox_H__

// Library Includes
#include "SpriteDataShell.h"

// Local Includes

// Types

// Constants

// Prototypes

struct TMiniBox
{
	D3DXVECTOR2 vPos;
	D3DXVECTOR2 vSize;
};


class C2DBoundingBox
{
// Member Functions
public:
	C2DBoundingBox();
	~C2DBoundingBox();
	void UpdatePosition(float _fX, float _fY);
	void SetSize(float _fWidth, float _fHeight);
	bool BoxCollsionCheck(C2DBoundingBox* _BoundingBox);
	bool CircleCollsionCheck(C2DBoundingBox* _BoundingBox);
	bool PointCollsionCheck(float _fX, float _fY);

	void Draw();

protected:

private:

// Member Variables
public:
	float m_fHeight;
	float m_fWidth;
	float m_fX;
	float m_fY;
	CSpriteDataShell m_Sprite;

	TMiniBox* pBox1;
	TMiniBox* pBox2;

	D3DXVECTOR2 PointVec1[4];
	D3DXVECTOR2 PointVec2[4];

	//Memory For circle Collision Check
	float a;
	float b;
	float c;	
	bool bCircleCollision;


protected:

private:

};

#endif // __2DBoundingBox_H__

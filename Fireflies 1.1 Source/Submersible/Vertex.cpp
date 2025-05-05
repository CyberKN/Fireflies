// Library Includes

// Local Includes

// This include
#include "Vertex.h"

// Constants

// Static Variables

// Static Function Prototypes

// Implementation

CVertex::CVertex()
{

}

CVertex::CVertex(float _fX, float _fY, float _fZ, D3DXVECTOR3 _vecNormals)
:m_vecPosition(_fX, _fY, _fZ)
{
	m_vecNormals.x = _vecNormals.x;
	m_vecNormals.y = _vecNormals.y;
	m_vecNormals.z = _vecNormals.z;

}
CVertex::CVertex(float _fX, float _fY, float _fZ, D3DXVECTOR3 _vecNormals, float _fV, float _fU)
:m_vecPosition(_fX, _fY, _fZ)
,m_fV(_fV)
,m_fU(_fU)
{
	m_vecNormals.x = _vecNormals.x;
	m_vecNormals.y = _vecNormals.y;
	m_vecNormals.z = _vecNormals.z;
}

CVertex::~CVertex()
{

}




D3DXVECTOR3* CVertex::Get()
{
	return(&m_vecPosition);
}

float CVertex::GetX() const
{
	return(m_vecPosition.x);
}

float CVertex::GetY() const
{
	return(m_vecPosition.y);
}

float CVertex::GetZ() const
{
	return(m_vecPosition.z);
}

void CVertex::SetX(float _f)
{
	m_vecPosition.x = _f;
}

void CVertex::SetY(float _f)
{
	m_vecPosition.y = _f;
}

void CVertex::SetZ(float _f)
{
	m_vecPosition.z = _f;
}



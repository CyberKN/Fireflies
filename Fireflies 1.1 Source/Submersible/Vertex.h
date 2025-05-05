#pragma once

#if !defined(__VERTEX_H__)
#define __VERTEX_H__

// Library Includes
#include <d3dx9.h>

// Local Includes

// Types

// Constants

// Prototypes


class CVertex
{
// Member Functions
public:
	CVertex();
	CVertex(float _fX, float _fY, float _fZ, D3DXVECTOR3 _vecNormals);
	CVertex(float _fX, float _fY, float _fZ, D3DXVECTOR3 _vecNormals, float _fV, float _fU);
	~CVertex();

	D3DXVECTOR3* Get();
	float GetX() const;
	float GetY() const;
	float GetZ() const;
	void SetX(float _f);
	void SetY(float _f);
	void SetZ(float _f);

protected:

private:

// Member Variables
public:


	D3DXVECTOR3 m_vecPosition;
	D3DXVECTOR3 m_vecNormals;
	float m_fV;
	float m_fU;


protected:

private:

};

#endif // __VERTEX_H__

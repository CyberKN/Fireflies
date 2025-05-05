#pragma once

#if !defined(__IGCamera_H__)
#define __IGCamera_H__

// Library Includes
#include <d3d9.h>
#include <d3dx9.h>

// Local Includes
#include "camera.h"

// Types

// Constants

// Prototypes


class CIGCamera : public CCamera
{
// Member Functions
public:
	CIGCamera();
	~CIGCamera();

	bool Initialise(CViewport* _pViewport, 
							float _fFov, 
							ECameraMode _eMode, 
							float _fNearClip, 
							float _fFarClip, 
							unsigned int _uiID);
	void SetClipPlanes(float _fNear, float _fFar);
	float GetNearPlane();
	float GetFarPlane();

	void SetFOV(float _fFOV);

	void SetView3D(D3DXVECTOR3& _rvectRight,
							D3DXVECTOR3& _rvectUp,
							D3DXVECTOR3& _rvectDir,
							D3DXVECTOR3& _rvectPos);

	void SetViewLookAt(D3DXVECTOR3& _rvectPos,
								D3DXVECTOR3& _rvectLook,
								D3DXVECTOR3& _rvectUp);

	void SetViewMatrix(D3DXMATRIX& _rmatView);
	void SetProjMatrix(D3DXMATRIX& _rmatProj);

	void SetMode(ECameraMode _eMode);
	void ResetMatricies();
	void Reset3DMatricies();
	void Reset2DMatricies();

	D3DXVECTOR3& GetPosition();

	void SetX(float _fVal);
	void SetY(float _fVal);
	void SetZ(float _fVal);

	float GetX();
	float GetY();
	float GetZ();

	void SetRoll(float _fVal);
	void SetPitch(float _fVal);
	void SetYaw(float _fVal);
	float GetRoll();
	float GetPitch();
	float GetYaw();

	D3DXMATRIX* GetViewMatrix();
	D3DXMATRIX* GetProjMatrix();

	void UpdateRenderer();

protected:

private:

// Member Variables
public:
	CViewport* m_pViewport;
	float m_fFov;
	ECameraMode m_eMode ;
	float m_fNear;
	float m_fFar;
	unsigned int m_uiID;
	
	D3DXVECTOR3 PosVec;
	D3DXVECTOR3 RotVec;
	D3DXMATRIX m_matProj;
	D3DXMATRIX m_matView;

	float m_fZMove;
	float m_fXMove;
	float m_fYMove;


protected:

private:

};

#endif // __IGCamera_H__

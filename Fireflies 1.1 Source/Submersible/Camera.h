#pragma once

#if !defined(__Camera_H__)
#define __Camera_H__

// Library Includes

#include <d3d9.h>
#include <d3dx9.h>

// Local Includes


// Types
enum ECameraMode
{
	INVALID_CAMERAMODE,
	CAMERAMODE_ORTHOGONAL,
	CAMERAMODE_PERSEPECTIVE,
	MAX_CAMERAMODE
};

enum ECameraType
{
	INVALID_CAMERATYPE,
	CAMERATYPE_DEBUG,
	CAMERATYPE_1ST_PERSON,
	CAMERATYPE_3RD_PERSON
};

// Constants

// Prototypes
class CViewport;

class CCamera
{
// Member Functions
public:

	CCamera()
	{
	}
	virtual ~CCamera()
	{
	}

	virtual bool Initialise(CViewport* _pViewport, 
							float _fFov, 
							ECameraMode _eMode, 
							float _fNearClip, 
							float _fFarClip, 
							unsigned int _uiID) = 0;
	virtual void SetClipPlanes(float _fNear, float _fFar) = 0;
	virtual float GetNearPlane() = 0;
	virtual float GetFarPlane() = 0;

	virtual void SetFOV(float _fFOV) = 0;

	virtual void SetView3D(D3DXVECTOR3& _rvectRight,
							D3DXVECTOR3& _rvectUp,
							D3DXVECTOR3& _rvectDir,
							D3DXVECTOR3& _rvectPos) = 0;

	virtual void SetViewLookAt(D3DXVECTOR3& _rvectPos,
								D3DXVECTOR3& _rvectLook,
								D3DXVECTOR3& _rvectUp) = 0;

	virtual void SetViewMatrix(D3DXMATRIX& _rmatView) = 0;
	virtual void SetProjMatrix(D3DXMATRIX& _rmatProj) = 0;

	virtual void SetMode(ECameraMode _eMode) = 0;
	virtual void ResetMatricies() = 0;

	virtual D3DXVECTOR3& GetPosition() = 0;

	virtual void SetX(float _fVal) = 0;
	virtual void SetY(float _fVal) = 0;
	virtual void SetZ(float _fVal) = 0;
	virtual float GetX() = 0;
	virtual float GetY() = 0;
	virtual float GetZ() = 0;

	virtual void SetRoll(float _fVal) = 0;
	virtual void SetPitch(float _fVal) = 0;
	virtual void SetYaw(float _fVal) = 0;
	virtual float GetRoll() = 0;
	virtual float GetPitch() = 0;
	virtual float GetYaw() = 0;

	virtual D3DXMATRIX* GetViewMatrix() = 0;
	virtual D3DXMATRIX* GetProjMatrix() = 0;

	virtual void UpdateRenderer() = 0;

protected:

private:

// Member Variables
public:

protected:

private:

};

#endif // __Camera_H__

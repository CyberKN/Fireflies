

#pragma once

#if !defined(__Viewport_H__)
#define __Viewport_H__

// Library Includes

#include <d3d9.h>
#include <d3dx9.h>

// Local Includes
#include "camera.h"

// Types

enum EShadeMode
{
	INVALID_MODE = 0
};

// Constants

// Prototypes

enum EShadeMode;

class CViewport
{
// Member Functions
public:

	CViewport()
	{
	}
	virtual ~CViewport()
	{
	}

	virtual bool Initialise(unsigned int _uiX,
							unsigned int _uiY, 
							unsigned int _uiWidth, 
							unsigned int _uiHeight, 
							D3DCOLOR _ClearColor,
							bool _bZClear = true) = 0;

	virtual CCamera* CreateCamera(float _fFOV,
									ECameraMode _eMode, 
									float _fNearClip, 
									float _fFarClip, 
									unsigned int& _ruiCameraID) = 0;

	virtual CCamera* GetCamera(unsigned int _uiCameraID) = 0;

	virtual bool SetActiveCamera(unsigned int _uiCameraID) = 0;
	virtual CCamera* GetActiveCamera() = 0;

	virtual D3DVIEWPORT9*  GetD3DViewport() = 0;

	virtual unsigned int GetWidth() = 0;
	virtual unsigned int GetHeight() = 0;
	virtual unsigned int GetXPos() = 0;
	virtual unsigned int GetYPos() = 0;



	virtual bool DoZClear() = 0;

	virtual D3DCOLOR GetClearColor() = 0;

	virtual void SetWireColor(D3DCOLORVALUE& _rColorWire) = 0;

	virtual D3DCOLORVALUE& GetWireColor() = 0;

	//Shade Mode Functions
	virtual EShadeMode GetShadeMode() = 0;
	virtual void SetShadeMode(EShadeMode _eShadeMode) = 0;


protected:

private:

// Member Variables
public:

protected:

private:

};

#endif // __Viewport_H__

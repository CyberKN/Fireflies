#pragma once

#if !defined(__IGViewport_H__)
#define __IGViewport_H__

// Library Includes
#include <vector>

// Local Includes
#include "Viewport.h"
#include "IGCamera.h"

// Types

// Constants

// Prototypes


class CIGViewport : public CViewport
{
// Member Functions
public:
	CIGViewport();
	~CIGViewport();

	bool Initialise(unsigned int _uiX,
							unsigned int _uiY, 
							unsigned int _uiWidth, 
							unsigned int _uiHeight, 
							D3DCOLOR _ClearColor,
							bool _bZClear = true);

	CCamera* CreateCamera(float _fFOV,
									ECameraMode _eMode, 
									float _fNearClip, 
									float _fFarClip, 
									unsigned int& _ruiCameraID);

	CCamera* GetCamera(unsigned int _uiCameraID);

	bool SetActiveCamera(unsigned int _uiCameraID);
	CCamera* GetActiveCamera();

	D3DVIEWPORT9*  GetD3DViewport();

	unsigned int GetWidth();
	unsigned int GetHeight();
	unsigned int GetXPos();
	unsigned int GetYPos();

	bool DoZClear();

	D3DCOLOR GetClearColor();

	void SetWireColor(D3DCOLORVALUE& _rColorWire);

	D3DCOLORVALUE& GetWireColor();

	//Shade Mode Functions
	EShadeMode GetShadeMode();
	void SetShadeMode(EShadeMode _eShadeMode);

protected:

private:

// Member Variables
public:
		D3DCOLORVALUE Color;
		D3DCOLOR m_ClearColor;
		D3DCOLORVALUE m_WireColor;
		EShadeMode m_eMode;
		std::vector<CCamera*> vCamera;
		CCamera* m_pActiveCamera;
		D3DVIEWPORT9 m_D3DViewport;

protected:

private:

};

#endif // __IGViewport_H__

#pragma once

#if !defined(__D3DRenderer_H__)
#define __D3DRenderer_H__

// Library Includes
#include <vector>

#include <string>
#include <d3dx9.h>
#include <d3d9.h>

// Local Includes
#include "Renderer.h"
#include "IGViewport.h"

// Types

// Constants

// Prototypes


class CD3DRenderer : public IRenderer
{
// Member Functions
public:
	CD3DRenderer();
	~CD3DRenderer();
	bool Initialise(int _iWidth, int _iHeight, HWND _hWindow, bool _bFullscreen);
	bool Shutdown();
	void SetClearColour(float _fRed, float _fGreen, float _fBlue);
	void Clear( bool _bTarget, bool _bDepth, bool _bStencil);
	void StartRender( bool _bTarget, bool _bDepth, bool _bStencil);
	void EndRender();
	void Render(unsigned int _uiStaticId);
	void DumpBackBufferToDisk(LPCWSTR _pcFileName);

protected:

private:

// Member Variables
public:
	HWND m_hWindow;
	LPDIRECT3D9 m_pDirect3D;
	D3DPRESENT_PARAMETERS d3dpp;
	LPDIRECT3DDEVICE9 m_pDevice;
	D3DCOLOR m_ClearColor;
	int m_iScreenWidth;
	int m_iScreenHeight;
	bool m_bFullscreen;
	bool m_bDefaultResolutionParameters;
	bool m_bRenderingScene;

	CIGViewport* m_pActiveViewport;
	std::vector<CIGViewport*> vViewport;

protected:

private:

};

#endif // __D3DRenderer_H__

#pragma once

#if !defined(__Renderer_H__)
#define __Renderer_H__

// Library Includes
#include <d3dx9.h>
#include <d3d9.h>

// Local Includes
#include "defines.h"

// Types

// Constants

// Prototypes


class IRenderer
{
// Member Functions
public:
	IRenderer()
	{
	}
	virtual ~IRenderer()
	{
	}
	virtual bool Initialise(int _iWidth, int _iHeight, HWND _hWindow, bool _bFullscreen) = 0;
	virtual bool Shutdown() = 0;
	virtual void SetClearColour(float _fRed, float _fGreen, float _fBlue) = 0;
	virtual void Clear( bool _bTarget, bool _bDepth, bool _bStencil) = 0;
	virtual void StartRender( bool _bTarget, bool _bDepth, bool _bStencil) = 0;
	virtual void EndRender() = 0;
	virtual void DumpBackBufferToDisk(LPCWSTR _pcFileName) = 0;


protected:

private:
	IRenderer(const IRenderer& _kr);
	IRenderer& operator= (const IRenderer& _kr);

// Member Variables
public:

protected:

private:

};

#endif // __Renderer_H__

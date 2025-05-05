// Library Includes

// Local Includes
//#include <DXErr.h>
// This include
#include "D3DRenderer.h"
#include "Game.h"


// Constants

// Static Variables

// Static Function Prototypes

// Implementation

CD3DRenderer::CD3DRenderer()
:m_iScreenHeight(0)
,m_iScreenWidth(0)
,m_bFullscreen(0)
,m_bRenderingScene(0)
,m_bDefaultResolutionParameters(1)
,m_pActiveViewport(0)
,m_pDevice(0)
,m_pDirect3D(0)
{
}
CD3DRenderer::~CD3DRenderer()
{

}

/**
* Initialisation of the game renderer.
* 
* @Author Kurt
* @param _iWidth			Width of screen / game window
* @param _iHeight			Height of screen / game window
* @param _hWindow			handle to the window
* @param _bFullscreen		Bool for if the game should be run in full screen or not
* 
* @return true.
*/
bool CD3DRenderer::Initialise(int _iWidth, int _iHeight, HWND _hWindow, bool _bFullscreen)
{
	//Populate member data using parameters

	m_iScreenHeight = _iHeight;
	m_iScreenWidth = _iWidth;
	m_bFullscreen = _bFullscreen;
	m_hWindow = _hWindow;

	D3DDISPLAYMODE mode;
	D3DCAPS9 caps;

	m_pDirect3D = Direct3DCreate9(D3D_SDK_VERSION);

	int iAdapter = D3DADAPTER_DEFAULT;

	m_pDirect3D->GetAdapterDisplayMode(iAdapter, &mode);

	m_pDirect3D->GetDeviceCaps(iAdapter, D3DDEVTYPE_HAL, &caps);

	DWORD dwVertProcessing = 0;

	if(caps.VertexProcessingCaps != 0)
	{
		dwVertProcessing = D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_PUREDEVICE;
	}
	else
	{
		dwVertProcessing = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	}

	if(_bFullscreen)
	{
		d3dpp.FullScreen_RefreshRateInHz = mode.RefreshRate;
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
	}
	else
	{
		d3dpp.FullScreen_RefreshRateInHz = 0;
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	}

	d3dpp.BackBufferFormat = mode.Format;
	d3dpp.BackBufferCount = 1;
	d3dpp.EnableAutoDepthStencil = true;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24X8;
	d3dpp.hDeviceWindow = m_hWindow;
	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality = 0;
	d3dpp.Windowed = !m_bFullscreen;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.Flags = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;

	//CGame::GetInstance().m_INIParser.GetBoolValue("GameInfo", "AutoDetectResolution", m_bDefaultResolutionParameters);

	if(m_bDefaultResolutionParameters)
	{
		if(m_bFullscreen)
		{
			d3dpp.BackBufferHeight = mode.Height;
			d3dpp.BackBufferWidth = mode.Width;
		}
		else
		{
			d3dpp.BackBufferHeight = _iHeight;// - 26;
			d3dpp.BackBufferWidth = _iWidth;// - 6;
		}
	}
	else
	{
		int iGetWidth = 0;
		int iGetHeight = 0;
		CGame::GetInstance().m_INIParser.GetIntValue("GameInfo", "FrameBufferWidth", iGetWidth);
		CGame::GetInstance().m_INIParser.GetIntValue("GameInfo", "FrameBufferHeight", iGetHeight);
		d3dpp.BackBufferHeight = iGetHeight;
		d3dpp.BackBufferWidth = iGetWidth;
	}

	m_iScreenWidth = d3dpp.BackBufferWidth;
	m_iScreenHeight = d3dpp.BackBufferHeight;

	HRESULT hr = m_pDirect3D->CreateDevice(	iAdapter, 
											D3DDEVTYPE_HAL, 
											m_hWindow, 
											dwVertProcessing, 
											&d3dpp, 
											&m_pDevice);



	m_pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	
	m_pDevice->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);
	m_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	m_pDevice->SetRenderState(D3DRS_SPECULARENABLE, TRUE);
	m_pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	m_pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	m_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCCOLOR);
	m_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//D3DXMatrixIdentity(&m_matView);
	//D3DXVECTOR3 pEye(0, 0, 0);
	//D3DXVECTOR3 pAt(0, 0, 1);
	//D3DXVECTOR3 pUp(0, 1,0);
	//D3DXMatrixLookAtLH(&m_matView, &pEye, &pAt, &pUp);
	//m_pDevice->SetTransform(D3DTS_VIEW, &m_matView);


	float kfNear = 0.1f;
	float kfFar = 10000.0f;




	int m_iNumViewports = 1;
	for(int i = 0; i < m_iNumViewports; ++i)
	{
		CIGViewport* pNewViewport = new CIGViewport;
		pNewViewport->Initialise(0, (m_iScreenHeight/m_iNumViewports)*i, m_iScreenWidth, m_iScreenHeight/m_iNumViewports, D3DCOLOR_XRGB(0, 0, 0));
		vViewport.push_back(pNewViewport);
		pNewViewport = 0;
	}
	
	vViewport[0]->SetActiveCamera(0);

	m_pActiveViewport = vViewport[0];
//	CalculateProjectionMatrix(3.14159f/4, kfNear, kfFar);
	return(true);


}

/**
* This function shuts down the renderer and releases / deletes pointers and memory.
* 
* @Author Kurt
* @return true.
*/
 bool CD3DRenderer::Shutdown()
{

	for(int i = 0; i < static_cast<int>(vViewport.size()); ++i)
	{
		delete vViewport[i];
		vViewport[i] = 0;
	}
	m_pActiveViewport = 0;

	m_pDevice->Release();
	m_pDevice = 0;

	m_pDirect3D->Release();
	m_pDirect3D = 0;

	return(true);
}

 /**
* Sets the member m_ClearColour to the color specified
* 
* @Author Kurt
* @param _fRed			amount of red in colour
* @param _fGreen		amount of green in colour
* @param _fBlue			amount of blue in colour
*/
 void CD3DRenderer::SetClearColour(float _fRed, float _fGreen, float _fBlue)
{
	m_ClearColor = D3DCOLOR_COLORVALUE(_fRed,_fGreen,_fBlue, 0.0f);
}

 /**
* Clears the screen / viewports
* 
* @Author Kurt
* @param _bTarget			Target to clear
* @param _bDepth			Depth to clear
* @param _bStencil			Stencil to clear
*/
 void CD3DRenderer::Clear(bool _bTarget, bool _bDepth, bool _bStencil)
{
	for(int i = 0; i < static_cast<int>(vViewport.size()); ++i)
	{
		m_pDevice->SetViewport(vViewport[i]->GetD3DViewport());
		m_pDevice->Clear(0, NULL, D3DCLEAR_TARGET| D3DCLEAR_ZBUFFER, vViewport[i]->GetClearColor(), 1.0, 0);
	}	
}

 /**
* Begins the rendering process
* 
* @Author Kurt
* @param all			unused
*/
 void CD3DRenderer::StartRender( bool _bTarget, bool _bDepth, bool _bStencil)
{
	m_pDevice->BeginScene();

}

 /**
* This function Ends the rendering process and presents what was rendered.
* 
* @Author Kurt
*/
 void CD3DRenderer::EndRender()
{
	m_pDevice->EndScene();

	HRESULT HDeviceStatus = m_pDevice->Present(NULL, NULL, NULL, NULL);

	if(HDeviceStatus != D3D_OK)
	{
		CGame::GetInstance().GetSpriteManager()->OnLostDevice();
		CGame::GetInstance().GetTextManager()->OnLostDevice();

		m_pDevice->Reset(&d3dpp);

		CGame::GetInstance().GetSpriteManager()->OnResetDevice();
		CGame::GetInstance().GetTextManager()->OnResetDevice();
	}

}


/**
* Function to take screenshots and save them into a file
* 
* @Author Kurt
* @param _pcFileName			name of file for the screen shot to save to
*/
void CD3DRenderer::DumpBackBufferToDisk(LPCWSTR _pcFileName)
{

	LPDIRECT3DSURFACE9 pSurface = 0;

	m_pDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &pSurface);

	D3DXSaveSurfaceToFile(_pcFileName, D3DXIFF_PNG, pSurface ,NULL, 0);

}


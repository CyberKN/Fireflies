// Library Includes

// Local Includes
#include "game.h"

// This include
#include "IGViewport.h"

// Constants

// Static Variables

// Static Function Prototypes

// Implementation

CIGViewport::CIGViewport()
:m_pActiveCamera(0)
{
}

CIGViewport::~CIGViewport()
{
	for(int i = 0; i < static_cast<int>(vCamera.size()); ++i)
	{
		delete vCamera[i];
		vCamera[i] = 0;
	}
	m_pActiveCamera = 0;

}

/**
* initialisation of viewports position
* 
* @Author Kurt
* @param _uiX				starting X position for viewport
* @param _uiY				starting Y position for viewport
* @param _uiWidth			Width of the viewport
* @param _uiHeight			Height of the viewport
* @param _ClearColor		what to set the m_ClearColor variable to
* @param _bZClear			unused
*
* @return True
*/
bool CIGViewport::Initialise(unsigned int _uiX,
						unsigned int _uiY, 
						unsigned int _uiWidth, 
						unsigned int _uiHeight, 
						D3DCOLOR _ClearColor,
						bool _bZClear)
{
	//Set Members
	m_D3DViewport.X = _uiX;
	m_D3DViewport.Y = _uiY;
	m_D3DViewport.MaxZ = 0.99f;
	m_D3DViewport.MinZ = 0.01f;
	m_D3DViewport.Width = _uiWidth;
	m_D3DViewport.Height = _uiHeight;
	m_ClearColor = _ClearColor;

	unsigned int uiCameraID = 0;
	unsigned int uiThirdPersonCameraID = 2;
	vCamera.push_back(0);

	return(true);
}


/**
* Function to create a new camera with the viewport.
* 
* @Author Kurt
* @param _fFOV				field of view for the camera to be created with
* @param _eMode				mode of camera wanted (example : first person )
* @param _fNearClip			The near clipping distance for the camera
* @param _fFarClip			The far clipping distance for the camera
* @param _ruiCameraID		The ID of the camera
*
* @return pointer to the camera created
*/
CCamera* CIGViewport::CreateCamera(float _fFOV,
								ECameraMode _eMode, 
								float _fNearClip, 
								float _fFarClip, 
								unsigned int& _ruiCameraID)
{
	//Create a new camera
	CCamera* pNewCamera = 0;
	//if(_ruiCameraID == 1)
	//{
	//	pNewCamera = new CFirstPersonCamera;
	//}
	//else if(_ruiCameraID == 2)
	//{
	//	pNewCamera = new CThirdPersonCamera;
	//	//pNewCamera->SetTargetObject(&CGame::GetInstance().m_GameSession->m_Player1.m_Turret.m_3DObject);
	//}
	//else 
	//{
	//	pNewCamera = new CDebugCamera;
	//}


	////initialise the camera
	//pNewCamera->Initialise(this, _fFOV, _eMode, _fNearClip, _fFarClip, _ruiCameraID);


	
	//Return the camera
	return(pNewCamera);
}

/**
* Function to get the camera id matching the viewport
* 
* @Author Kurt
* @param _uiCameraID			id of camera to get
*
* @return viewports camera ID
*/
CCamera* CIGViewport::GetCamera(unsigned int _uiCameraID)
{
	return(vCamera[_uiCameraID]);
}

/**
* Set the active camera to be the camera ID passed in
* 
* @Author Kurt
* @param _uiCameraID			camera id to set the viewport to use
*
* @return True
*/
bool CIGViewport::SetActiveCamera(unsigned int _uiCameraID)
{
	m_pActiveCamera = vCamera[_uiCameraID];
	return(true);
}

/**
* Function to return the active camera
* 
* @Author Kurt
*
* @return Current active camera
*/
CCamera* CIGViewport::GetActiveCamera()
{
	return(m_pActiveCamera);
}

/**
* function to get this Viewports information
* 
* @Author Kurt
*
* @return reference to the viewport
*/
D3DVIEWPORT9*  CIGViewport::GetD3DViewport()
{
	return(&m_D3DViewport);
}

/**
* function to get the width of the viewport
* 
* @Author Kurt
*
* @return viewport width
*/
unsigned int CIGViewport::GetWidth()
{
	//Return the Viewport width
	return(static_cast<unsigned int>(m_D3DViewport.Width));
}

/**
* function to get the height of the viewport
* 
* @Author Kurt
*
* @return viewports height
*/
unsigned int CIGViewport::GetHeight()
{
	//Return the Viewport height
	return(static_cast<unsigned int>(m_D3DViewport.Height));
}

/**
* function to get the x position of the viewport (starting position of screen)
* 
* @Author Kurt
*
* @return viewports X member value
*/
unsigned int CIGViewport::GetXPos()
{
	//Return the Viewport xpos
	return(static_cast<unsigned int>(m_D3DViewport.X));
}

/**
* function to get the y position of the viewport (starting position of screen)
* 
* @Author Kurt
*
* @return viewports Y member value
*/
unsigned int CIGViewport::GetYPos()
{
	//Return the Viewport ypos
	return(static_cast<unsigned int>(m_D3DViewport.Y));
}

/**
* Empty function
* 
* @Author Kurt
*
* @return True
*/
bool CIGViewport::DoZClear()
{

	return(true);
}

/**
* function to get the clear color member variable value
* 
* @Author Kurt
*
* @return Clear color value
*/
D3DCOLOR CIGViewport::GetClearColor()
{
	return(m_ClearColor);
}

/**
* Function to set the wire colour in a viewport
* 
* @Author Kurt
* @param _rColorWire			reference of the colour wanted to set the wires colour to
*/
void CIGViewport::SetWireColor(D3DCOLORVALUE& _rColorWire)
{
	m_WireColor = _rColorWire;
}

/**
* function to get the wire colour
* 
* @Author Kurt
*
* @return current member variable wire colour
*/
D3DCOLORVALUE& CIGViewport::GetWireColor()
{
	return(m_WireColor);
}

/**
* Function to get the current shade mode
* 
* @Author Kurt
*
* @return enum value for the shade mode
*/
EShadeMode CIGViewport::GetShadeMode()
{

	return(m_eMode);
}


/**
* function to set the shade mode
* 
* @Author Kurt
* @param _eShadeMode			mode to set the m_eMode to use for shading
*/
void CIGViewport::SetShadeMode(EShadeMode _eShadeMode)
{
	m_eMode = _eShadeMode;
}



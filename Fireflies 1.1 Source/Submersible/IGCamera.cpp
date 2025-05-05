// Library Includes

// Local Includes
#include "Viewport.h"

// This include
#include "IGCamera.h"
#include "Game.h"

// Constants

// Static Variables

// Static Function Prototypes

// Implementation

CIGCamera::CIGCamera()
:m_pViewport(0)
,m_fFov(0)
,m_eMode(INVALID_CAMERAMODE)
,m_fNear(0)
,m_fFar(0)
,m_uiID(-1)
,m_fZMove(0)
,m_fXMove(0)
,m_fYMove(0)
{
	//Set all matricies to identity.
}

CIGCamera::~CIGCamera()
{

}

/**
* Camera Initialisation
* 
* @Author Kurt
* @param _pViewport			viewport pointer for the camera to be made with
* @param _fFov				field of view for the camera
* @param _eMode				mode for the camera (1st person etc)
* @param _fNearClip			closest the camera can see - where the sight range begins
* @param _fFarClip			furtherest the camera can see - where the sight range ends
* @param _uiID				ID of camera
*
* @return True
*/
bool CIGCamera::Initialise(CViewport* _pViewport, 
						float _fFov, 
						ECameraMode _eMode, 
						float _fNearClip, 
						float _fFarClip, 
						unsigned int _uiID)
{
	//Assert on a valid _pViewport pointer

	//Set all members.
	m_pViewport = _pViewport;
	m_fFov = _fFov;
	m_eMode =  _eMode;
	m_fNear = _fNearClip;
	m_fFar = _fFarClip;
	m_uiID = _uiID;

	PosVec.x = 0;
	PosVec.y = 0;
	PosVec.z = 0;

	RotVec.x = 0;
	RotVec.y = 0;
	RotVec.z = 0;

	//Call Reset Matricies
	ResetMatricies();

	return(true);
}

/**
* Function to set the clipping planes of the camera
* 
* @Author Kurt
* @param _fNear				near clipping plane to set camera to
* @param _fFar				far clipping plane to set camera to
*/
void CIGCamera::SetClipPlanes(float _fNear, float _fFar)
{
	//Set Members
	m_fNear = _fNear;
	m_fFar = _fFar;


	//Make sure they make sense!
}

/**
* function to get m_fNear
* 
* @Author Kurt
*
* @return m_fNear
*/
float CIGCamera::GetNearPlane()
{
	return(m_fNear);
}

/**
* function to get the far plane
* 
* @Author Kurt
*
* @return m_fFar
*/
float CIGCamera::GetFarPlane()
{
	return(m_fFar);
}

/**
* function to set the field of view
* 
* @Author Kurt
* @param _fFOV			what to set the Field Of View to
*/
void CIGCamera::SetFOV(float _fFOV)
{
		m_fFov = _fFOV;
}

/**
* Function to set the 3D view to equal (changes view of camera). sets view matrix.
* 
* @Author Kurt
* @param _rvectRight			vector containing the 'Right' information
* @param _rvectUp				vector containing the 'up' information
* @param _rvectDir				vector containing the 'direction' information
* @param _rvectPos				vector containing the current position
*/
void CIGCamera::SetView3D(D3DXVECTOR3& _rvectRight,
						D3DXVECTOR3& _rvectUp,
						D3DXVECTOR3& _rvectDir,
						D3DXVECTOR3& _rvectPos)
{
	//Populate view Matrix
	D3DXMatrixIdentity(&m_matView);
	

	D3DXMatrixLookAtLH(&m_matView, &_rvectPos, &_rvectDir, &_rvectUp);



	//Send the view matrix to the rendering device. 
	CGame::GetInstance().m_DirectX3DRenderer.m_pDevice->SetTransform(D3DTS_VIEW, &m_matView);
	
}

/**
* calls the function above : SetView3D
* 
* @Author Kurt
* @param _rvectPos			position vector to set the view to
* @param _rvectLook			look vector to set the view to
* @param _rvectUp			up vector to srt the view to
*
* @return True
*/
void CIGCamera::SetViewLookAt(D3DXVECTOR3& _rvectPos,
							D3DXVECTOR3& _rvectLook,
							D3DXVECTOR3& _rvectUp)
{
	//convert between LookAt and setting the 3D view.
	
	//Calculate the Dir Vector

	//Calculate the Right Vector

	//Calculate the Up Vector.

	//Call SetView3D
	SetView3D(_rvectUp, _rvectUp, _rvectLook, _rvectPos);

}

/**
* sets the view matrix
* 
* @Author Kurt
* @param _rmatView			view matrix, to set the member variable view matrix to
*/
void CIGCamera::SetViewMatrix(D3DXMATRIX& _rmatView)
{
	//Store the View Matrix
	m_matView = _rmatView;

	//Calculate the World View Projection Matrix.

	//Set the view matrix on the rendering device. 
	CGame::GetInstance().m_DirectX3DRenderer.m_pDevice->SetTransform(D3DTS_VIEW, &m_matView);

}

/**
* function to set the projection matrix
* 
* @Author Kurt
* @param _rmatProj			matrix to set m_matProj to
*/
void CIGCamera::SetProjMatrix(D3DXMATRIX& _rmatProj)
{
	//Store the Projection matrix.
	m_matProj = _rmatProj;

	//calculate the World View Projection Matrix.

	//Set the projection matrix on the rendering device. 
	CGame::GetInstance().m_DirectX3DRenderer.m_pDevice->SetTransform(D3DTS_PROJECTION, &m_matProj);

}


/**
* sets / changes the current camera mode and resets matricies
* 
* @Author Kurt
* @param _eMode			mode to set the camera mode to
*/
void CIGCamera::SetMode(ECameraMode _eMode)
{
	//Set the mode.
	m_eMode = _eMode;

	//Call resetMatricies
	ResetMatricies();
}

/**
* call to reset matricies (3D only)
* 
* @Author Kurt
*/
void CIGCamera::ResetMatricies()
{
	//Switch on the mode
	Reset3DMatricies();
	//Call the appropriate method.
}

/**
* resets the matricies to be an identity.
* 
* @Author Kurt
*/
void CIGCamera::Reset3DMatricies()
{	
	//Use D3DX to create projection matricies.
	D3DXMatrixIdentity(&m_matProj);

	//Depending on the mode...
	//Call D3DXMatrixOrthoLH or D3DXMatrixPerspectiveFovLH
	if(m_eMode == CAMERAMODE_ORTHOGONAL)
	{
		D3DXMatrixOrthoLH(&m_matProj, static_cast<float>(m_pViewport->GetWidth()), static_cast<float>(m_pViewport->GetHeight()), 1.0f, 100.0f);
	}
	else if(m_eMode == CAMERAMODE_PERSEPECTIVE)
	{
		D3DXMatrixPerspectiveFovLH(&m_matProj, 1, m_fFov, 0.01f, 100.0f);
	}

	//Set the Projection Matrix on the rendering device.

	
	CGame::GetInstance().m_DirectX3DRenderer.m_pDevice->SetTransform(D3DTS_PROJECTION, &m_matProj);

}

/**
* function not called. 
* 
* @Author Kurt
*/
void CIGCamera::Reset2DMatricies()
{

	//Create a normal Ortho Projection Matrix...
	//using D3DXMatrixOrthoLH.

	//Create a view matrix.
	D3DXMatrixIdentity(&m_matProj);
	//Set the world matrix to identity
	D3DXMatrixOrthoLH(&m_matProj, static_cast<float>(m_pViewport->GetWidth()/20), static_cast<float>(m_pViewport->GetHeight()/20), 0.01f, 10000.0f);
	CGame::GetInstance().m_DirectX3DRenderer.m_pDevice->SetTransform(D3DTS_PROJECTION, &m_matProj);
	//Call the upddateRenderer method.
}

/**
* get the camera position
* 
* @Author Kurt
*
* @return positino vector of camera
*/
D3DXVECTOR3& CIGCamera::GetPosition()
{
	return(PosVec);
}

/**
* set cameras X position
* 
* @Author Kurt
* @param _fVal			value to set the cameras position to
*/
void CIGCamera::SetX(float _fVal)
{
	m_fXMove = _fVal;
}

/**
* Sets cameras Y position
* 
* @Author Kurt
* @param _fVal			value to set Y to
*/
void CIGCamera::SetY(float _fVal)
{
	m_fYMove = _fVal;
}

/**
* function to set the Z value of the cameras position
* 
* @Author Kurt
* @param _fVal			value to set the Z position of camera to
*/
void CIGCamera::SetZ(float _fVal)
{
	m_fZMove = _fVal;
}

/**
* call to get the cameras X value
* 
* @Author Kurt
*
* @return cameras X value
*/
float CIGCamera::GetX()
{
	return(PosVec.x);
}

/**
* call to get the cameras Y value
* 
* @Author Kurt
*
* @return cameras Y value
*/
float CIGCamera::GetY()
{
	return(PosVec.y);
}

/**
* call to get the cameras Z value
* 
* @Author Kurt
*
* @return cameras Z value
*/
float CIGCamera::GetZ()
{
	return(PosVec.z);
}

/**
* Sets the roll for rotation
* 
* @Author Kurt
* @param _fVal			value to set roll to
*/
void CIGCamera::SetRoll(float _fVal)
{
	if(_fVal > 2*(3.14f))
	{
		_fVal = _fVal - 2*(3.14f);
	}
	else if(_fVal < 0)
	{
		_fVal = _fVal + 2*(3.14f);
	}
	RotVec.z = _fVal;
}

/**
* Sets the pitch for rotation
* 
* @Author Kurt
* @param _fVal			value to set the pitch rotation to
*/
void CIGCamera::SetPitch(float _fVal)
{
	if(_fVal > 2*(3.14f))
	{
		_fVal = _fVal - 2*(3.14f);
	}
	else if(_fVal < 0)
	{
		_fVal = _fVal + 2*(3.14f);
	}
	RotVec.y = _fVal;
}

/**
* Sets the yaw for rotation
* 
* @Author Kurt
* @param _fVal			value to set the yaw rotation to
*/
void CIGCamera::SetYaw(float _fVal)
{
	if(_fVal > 2*(3.14f))
	{
		_fVal = _fVal - 2*(3.14f);
	}
	else if(_fVal < 0)
	{
		_fVal = _fVal + 2*(3.14f);
	}
	RotVec.x = _fVal;
}

/**
* call to get camera roll
* 
* @Author Kurt
*
* @return roll value
*/
float CIGCamera::GetRoll()
{
	return(RotVec.z);
}

/**
* call to get camera pitch
* 
* @Author Kurt
*
* @return pitch value
*/
float CIGCamera::GetPitch()
{
	return(RotVec.y);
}

/**
* call to get camera yaw
* 
* @Author Kurt
*
* @return roll yaw
*/
float CIGCamera::GetYaw()
{
	return(RotVec.x);
}

/**
* call to get the view matrix of the camera
* 
* @Author Kurt
*
* @return view matrix
*/
D3DXMATRIX* CIGCamera::GetViewMatrix()
{

	return(&m_matView);
}

/**
* call to get the projection matrix of camera
* 
* @Author Kurt
*
* @return projection matrix
*/
D3DXMATRIX* CIGCamera::GetProjMatrix()
{

	return(&m_matProj);
}

/**
* This function updates the renderer and sets it to be the correct position & rotation
* 
* @Author Kurt
*/
void CIGCamera::UpdateRenderer()
{


	//Set the View Matrix

	D3DXMatrixIdentity(&m_matView);

	D3DXVECTOR3 up = D3DXVECTOR3(0.0f,1.0f,0.0f);
	D3DXVECTOR3 look = D3DXVECTOR3(0.0f,0.0f,1.0f);
	D3DXVECTOR3 right = D3DXVECTOR3(1.0f,0.0f,0.0f);

	D3DXMATRIX yawMatrix;
	D3DXMatrixRotationAxis(&yawMatrix, &up, RotVec.x);

	D3DXVec3TransformCoord(&look, &look, &yawMatrix); 
	D3DXVec3TransformCoord(&right, &right, &yawMatrix);

	D3DXMATRIX pitchMatrix;
	D3DXMatrixRotationAxis(&pitchMatrix, &right, RotVec.y);

	D3DXVec3TransformCoord(&look, &look, &pitchMatrix); 
	D3DXVec3TransformCoord(&up, &up, &pitchMatrix);

	D3DXMATRIX rollMatrix;
	D3DXMatrixRotationAxis(&rollMatrix, &look, RotVec.z);

	D3DXVec3TransformCoord(&right, &right, &rollMatrix); 
	D3DXVec3TransformCoord(&up, &up, &rollMatrix);


	m_matView._11 = right.x; m_matView._12 = up.x; m_matView._13 = look.x;
	m_matView._21 = right.y; m_matView._22 = up.y; m_matView._23 = look.y;
	m_matView._31 = right.z; m_matView._32 = up.z; m_matView._33 = look.z;

	PosVec += look*m_fZMove;    // Move forward
	PosVec += right*m_fXMove;   // Move right (strafe)
	PosVec += up*m_fYMove;      // Move up

	m_matView._41 = - D3DXVec3Dot(&PosVec, &right ); 
	m_matView._42 = - D3DXVec3Dot(&PosVec, &up );
	m_matView._43 = - D3DXVec3Dot(&PosVec, &look );

	m_fZMove = 0;
	m_fXMove = 0;
	m_fYMove = 0;

	CGame::GetInstance().m_DirectX3DRenderer.m_pDevice->SetTransform(D3DTS_VIEW, &m_matView);
	//Set the Projection Matrix. 
	CGame::GetInstance().m_DirectX3DRenderer.m_pDevice->SetTransform(D3DTS_PROJECTION, &m_matProj);

}





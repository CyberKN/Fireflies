// Library Includes 
#include <windows.h>

// Local Includes 

// This Includes 
#include "Sprite.h" 
#include "game.h"
#include "SpriteManager.h"

// Static Variables 

// Static Function Prototypes

// Implementation

CSprite::CSprite()
:m_pSource(0)
,m_pSprite(0)
,m_fRotation(0)
,m_Colour(0xFFFFFFFF)
,m_pManager(0)
{
	//Set the default poistion of the sprite to (0,0).
	m_Pos.x = 0;
	m_Pos.z = 0;
	m_Pos.y = 0;

}

CSprite::~CSprite()
{
	if(m_pSource != 0)
	{
		m_pSource->Release();
		m_pSource = 0;
	}
	if(m_pSprite != 0)
	{
		m_pSprite->Release();
		m_pSprite = 0;
	}
	m_pManager = 0;
}

/**
* @DESC		Initialises the Sprite Object
* @AUTHOR	Kurt Nadworny
* @PARAM	_SrcFile: The source file location of the sprite's texture
* @PARAM	_iSizeX: The desired width of the sprite in pixels
* @PARAM	_iSizeY: The desired height of the sprite in pixels
* @PARAM	_fScale: The desired  modfication to the scale of the sprite, relative to it's original dimensions.
* @RETURN	Whether or not the Initialisation was successful.
**/
bool CSprite::Initialise(LPCWSTR _SrcFile, int _iXSize, int _iYSize, float _fScale, CSpriteManager* _pManager)
{
	bool bResult = false;

	m_iFrameWidth = _iXSize;
	m_iFrameHeight = _iYSize;
	m_fXScale = _fScale;
	m_fYScale = _fScale;
	m_pManager = _pManager;

	ZeroMemory(&m_ImageInfo, sizeof(D3DXIMAGE_INFO));
	HRESULT hr2 = D3DXGetImageInfoFromFile(_SrcFile, &m_ImageInfo);

	D3DXCreateSprite(CGame::GetInstance().m_DirectX3DRenderer.m_pDevice, &m_pSprite);

	m_iSizeX = m_ImageInfo.Width;
	m_iSizeY = m_ImageInfo.Height;

	if(m_iFrameWidth == 0)
	{
		m_iFrameWidth = m_ImageInfo.Width;
		m_iFrameHeight = m_ImageInfo.Height;
	}

	HRESULT hr1 = D3DXCreateTextureFromFileEx(CGame::GetInstance().m_DirectX3DRenderer.m_pDevice,
												_SrcFile,
												m_ImageInfo.Width,
												m_ImageInfo.Height,
												D3DX_DEFAULT,
												NULL,
												D3DFMT_FROM_FILE,
												D3DPOOL_MANAGED, 
												D3DX_FILTER_LINEAR,
												D3DX_DEFAULT, 
												D3DXCOLOR(0, 1, 0, 1),
												&m_ImageInfo, 
												NULL,
												&m_pSource);

	if(hr1 == D3D_OK)
	{
		ZeroMemory(&m_ImageInfo, sizeof(D3DXIMAGE_INFO));
		HRESULT hr2 = D3DXGetImageInfoFromFile(_SrcFile, &m_ImageInfo);
		bResult = true;
	}
	else
	{
		m_pSprite->Release();
		m_pSprite = 0;	
		assert(("Specified texture file Not Found.", false));

	}

	return (bResult);
}

/**
* @DESC		Tranlates the Sprite Object to a new location on the screen
* @AUTHOR	Kurt Nadworny
* @PARAM	_iX: The desired position of the sprite on the x-axis
* @PARAM	_iY: The desired position of the sprite on the y-axis
**/
void CSprite::TranslateAbsolute(float _iX, float _iY)
{
	m_Pos.x = _iX;
	m_Pos.y = _iY;
}

/**
* @DESC		Tranlates the Sprite Object to a new location on the screen
* @AUTHOR	Kurt Nadworny
* @RETURN	The position of the sprite on the x-axis
**/
float CSprite::GetX()
{
	return(m_Pos.x);
}

/**
* @DESC		Tranlates the Sprite Object to a new location on the screen
* @AUTHOR	Kurt Nadworny
* @RETURN	The position of the sprite on the y-axis
**/
float CSprite::GetY()
{
	return(m_Pos.y);
}

/**
* @DESC		Draws the Sprite Object
* @AUTHOR	Kurt Nadworny
**/
void CSprite::Draw()
{
	if(m_pSprite)
	{
		float fXScale = m_fXScale;
		float fYScale = m_fYScale;
		m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);

		RECT ResizeRect;
		ResizeRect.top = static_cast<LONG>(0);
		ResizeRect.bottom = static_cast<LONG>(m_iSizeY);
		ResizeRect.left = static_cast<LONG>(0);
		ResizeRect.right = static_cast<LONG>(m_iSizeX);

		D3DXVECTOR2 spriteCentre=D3DXVECTOR2(m_iSizeX*0.5f*m_fXScale, m_iSizeY*0.5f*m_fYScale);

		// Screen position of the sprite
		D3DXVECTOR2 trans=D3DXVECTOR2(m_Pos.x-(spriteCentre.x),CGame::GetInstance().m_DirectX3DRenderer.m_iScreenHeight-(m_Pos.y+(spriteCentre.y)));

		trans.x = (float)(int)trans.x;
		trans.y = (float)(int)trans.y;
		//D3DXVECTOR2 trans=D3DXVECTOR2(m_Pos.x-(spriteCentre.x),m_Pos.y-(spriteCentre.y));

		float rotation= m_fRotation;

		// Build our matrix to rotate, scale and position our sprite
		D3DXMATRIX mat;

		D3DXVECTOR2 scaling(fXScale,fYScale);

		// out, scaling centre, scaling rotation, scaling, rotation centre, rotation, translation
		D3DXMatrixTransformation2D(&mat,NULL,0.0,&scaling,&spriteCentre,rotation,&trans);

		// Tell the sprite about the matrix
		m_pSprite->SetTransform(&mat);

		// Draw the sprite 
		m_pSprite->Draw(m_pSource,&ResizeRect,NULL,NULL, m_Colour);

		m_pSprite->End();
	}
}

void CSprite::SetRotate(float _fradians)
{
	m_fRotation = _fradians;
}

void CSprite::SetColor(int _iAlpha, int _iRed, int _iGreen, int _iBlue)
{
	m_Colour = D3DCOLOR_ARGB(_iAlpha, _iRed, _iGreen, _iBlue);
}

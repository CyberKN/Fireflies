#define BUTTONDOWN(name, key) (name.rgbButtons[key] & 0x80)

// Library Includes

// Local Includes
#include "Game.h"

// This include
#include "DInputMouse.h"

// Constants

// Static Variables

// Static Function Prototypes

// Implementation

CDInputMouse::CDInputMouse()
:pDIDevice(0)
,m_pDI(0)
,m_pMouseState(0)
,m_pLastMouseState(0)
,m_bLockMouse(false)
{

}

CDInputMouse::~CDInputMouse()
{
	m_pDI->Release();
	m_pDI = 0;
	pDIDevice->Release();
	pDIDevice = 0;

	if(m_pMouseState)
	{
		delete m_pMouseState;
		m_pMouseState = 0;
	}

	if(m_pLastMouseState)
	{
		delete m_pLastMouseState;
		m_pLastMouseState = 0;
	}
}

void CDInputMouse::Initialise()
{
	DirectInput8Create(CGame::GetInstance().GetAppInstance(), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pDI, NULL);	

	HRESULT hr = m_pDI->CreateDevice(GUID_SysMouse, &pDIDevice, NULL);

	pDIDevice->SetDataFormat(&c_dfDIMouse);

	pDIDevice->SetCooperativeLevel(CGame::GetInstance().GetWindow(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	
	HRESULT hr2 = pDIDevice->Acquire();

	m_pMouseState = new TMouseState;
	m_pLastMouseState = 0;

	for(unsigned int i = 0; i < 2; ++i)
	{
		m_pMouseState->bButtonStates[MOUSEBID_LEFT] = false;
		m_pMouseState->bButtonStates[MOUSEBID_RIGHT] = false;
		m_pMouseState->bButtonStates[MOUSEBID_MIDDLE] = false;

		m_pMouseState->fMoveStates[MOUSEMOVE_X] = 0;
		m_pMouseState->fMoveStates[MOUSEMOVE_Y] = 0;
		m_pMouseState->fMoveStates[MOUSEMOVE_Z] = 0;

		m_pMouseState->iPosStates[MOUSEPOS_X] = 0;
		m_pMouseState->iPosStates[MOUSEPOS_Y] = 0;

		if(!m_pLastMouseState)
		{
			m_pLastMouseState = m_pMouseState;
			m_pMouseState = new TMouseState;
		}
	}
}	

void CDInputMouse::Process()
{
	HRESULT hr2 = pDIDevice->Acquire();

	DIMOUSESTATE MouseState;
	ZeroMemory(&MouseState, sizeof(MouseState));

	pDIDevice->GetDeviceState( sizeof(MouseState), (LPVOID)&MouseState );

	//Set the "Current" state as the Last State
	TMouseState* tempMouseState = m_pLastMouseState;
	m_pLastMouseState = m_pMouseState;
	m_pMouseState = tempMouseState;

	//Get the New Current States
	m_pMouseState->bButtonStates[MOUSEBID_LEFT] = BUTTONDOWN(MouseState, 0) != 0;
	m_pMouseState->bButtonStates[MOUSEBID_RIGHT] = BUTTONDOWN(MouseState, 1) != 0;
	m_pMouseState->bButtonStates[MOUSEBID_MIDDLE] = BUTTONDOWN(MouseState, 2) != 0;

	m_pMouseState->fMoveStates[MOUSEMOVE_X] = static_cast<float>(MouseState.lX);
	m_pMouseState->fMoveStates[MOUSEMOVE_Y] = static_cast<float>(MouseState.lY);
	m_pMouseState->fMoveStates[MOUSEMOVE_Z] = static_cast<float>(MouseState.lZ)*0.001f;

	POINT PCursorPos;
	GetCursorPos(&PCursorPos);

	if(CGame::GetInstance().m_DirectX3DRenderer.m_bFullscreen)
	{
		m_pMouseState->iPosStates[MOUSEPOS_X] = PCursorPos.x - CGame::GetInstance().m_iWindowOffsetX;
		m_pMouseState->iPosStates[MOUSEPOS_Y] = PCursorPos.y - CGame::GetInstance().m_iWindowOffsetY;
	}
	else
	{
		m_pMouseState->iPosStates[MOUSEPOS_X] = PCursorPos.x - CGame::GetInstance().m_iWindowOffsetX - 2;
		m_pMouseState->iPosStates[MOUSEPOS_Y] = PCursorPos.y - CGame::GetInstance().m_iWindowOffsetY - 23;
	}

	if(m_bLockMouse && CGame::GetInstance().HasFocus())
	{
		int iMiddleX = CGame::GetInstance().m_iWindowOffsetX + (int)((float)CGame::GetInstance().m_iWindowWidth*0.5f);
		int iMiddleY = CGame::GetInstance().m_iWindowOffsetY + (int)((float)CGame::GetInstance().m_iWindowHeight*0.5f);
		SetCursorPos(iMiddleX, iMiddleY);
	}
}

bool CDInputMouse::IsButtonDown(EMouseButtonID _e)
{
	return(m_pMouseState->bButtonStates[_e]);
}

bool CDInputMouse::WasButtonPressed(EMouseButtonID _e)
{
	return(m_pMouseState->bButtonStates[_e] && !m_pLastMouseState->bButtonStates[_e]);
}

bool CDInputMouse::WasButtonReleased(EMouseButtonID _e)
{
	return(!m_pMouseState->bButtonStates[_e] && m_pLastMouseState->bButtonStates[_e]);
}

bool CDInputMouse::WasAnyButtonPressed()
{
	for(unsigned int i = 0; i < KEYID_MAX; ++i)
	{
		if(WasButtonPressed((EMouseButtonID)i))
		{
			return(true);
		}
	}
	
	return(false);
}

bool CDInputMouse::IsAnyButtonDown()
{
	for(unsigned int i = 0; i < KEYID_MAX; ++i)
	{
		if(IsButtonDown((EMouseButtonID)i))
		{
			return(true);
		}
	}
	
	return(false);
}

float CDInputMouse::GetMovement(EMouseMoveID _e)
{
	return(m_pMouseState->fMoveStates[_e]);
}

int CDInputMouse::GetPosition(EMousePositionID _e)
{
	return(m_pMouseState->iPosStates[_e]);
}

void CDInputMouse::SetMouseLocked(bool _b)
{
	m_bLockMouse = _b;
}

bool CDInputMouse::IsMouseLocked()
{
	return(m_bLockMouse);
}

int CDInputMouse::GetX()
{
	return(m_pMouseState->iPosStates[MOUSEPOS_X]);
}

int CDInputMouse::GetY()
{
	return(m_pMouseState->iPosStates[MOUSEPOS_Y]);
}

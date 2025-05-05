#ifndef DIRECTINPUT_VERSION
#define DIRECTINPUT_VERSION 0x0800
#endif

#define KEYDOWN(name, key) (name[key] & 0x80)

// Library Includes
#include <dinput.h>

// Local Includes
#include "Game.h"

// This include
#include "DInputKeyboard.h"

// Constants

// Static Variables

// Static Function Prototypes

// Implementation
//

//BOOL CALLBACK DIEnumDevicesCallback(DIDEVICEINSTANCE* lpddi, VOID* pContext)
//{
//	HRESULT hr;
//
//	hr = m_pDI->CreateDevice(GUID_SysKeyboard, &pDIDevice, NULL);
//
//
//	if( FAILED(hr) )
//	{
//		return(DIENUM_CONTINUE);
//	}
//	else
//	{
//		return(DIENUM_STOP);
//	}
//
//}

CDInputKeyboard::CDInputKeyboard()
:pDIDevice(0)
,m_pDI(0)
,m_pKeyState(0)
,m_pLastKeyState(0)
{

}

CDInputKeyboard::~CDInputKeyboard()
{
	m_pDI->Release();
	m_pDI = 0;
	pDIDevice->Release();
	pDIDevice = 0;

	if(m_pKeyState)
	{
		delete m_pKeyState;
		m_pKeyState = 0;
	}

	if(m_pLastKeyState)
	{
		delete m_pLastKeyState;
		m_pLastKeyState = 0;
	}

}

void CDInputKeyboard::Initialise()
{
	DirectInput8Create(CGame::GetInstance().GetAppInstance(), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pDI, NULL);	

	HRESULT hr = m_pDI->CreateDevice(GUID_SysKeyboard, &pDIDevice, NULL);

	pDIDevice->SetDataFormat(&c_dfDIKeyboard);

	pDIDevice->SetCooperativeLevel(CGame::GetInstance().GetWindow(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	
	HRESULT hr2 = pDIDevice->Acquire();

	m_pKeyState = new TKeyState;
	m_pLastKeyState = new TKeyState;

	for(unsigned int i = 0; i < KEYID_MAX; ++i)
	{
		m_pKeyState->bKeyStates[i] = false;
		m_pLastKeyState->bKeyStates[i] = false;
	}



}	


void CDInputKeyboard::Process()
{
	HRESULT hr2 = pDIDevice->Acquire();

	char buffer[256];
	
	memset(buffer, 0, 256);

	pDIDevice->GetDeviceState( sizeof(buffer), (LPVOID)&buffer );

	//Set the "Current" state as the Last State
	TKeyState* tempKeyState = m_pLastKeyState;
	m_pLastKeyState = m_pKeyState;
	m_pKeyState = tempKeyState;

	//Get the New Current States
	m_pKeyState->bKeyStates[KEYID_Q] = KEYDOWN(buffer, DIK_Q) != 0;
	m_pKeyState->bKeyStates[KEYID_W] = KEYDOWN(buffer, DIK_W) != 0;
	m_pKeyState->bKeyStates[KEYID_E] = KEYDOWN(buffer, DIK_E) != 0;
	m_pKeyState->bKeyStates[KEYID_R] = KEYDOWN(buffer, DIK_R) != 0;
	m_pKeyState->bKeyStates[KEYID_T] = KEYDOWN(buffer, DIK_T) != 0;
	m_pKeyState->bKeyStates[KEYID_Y] = KEYDOWN(buffer, DIK_Y) != 0;
	m_pKeyState->bKeyStates[KEYID_U] = KEYDOWN(buffer, DIK_U) != 0;
	m_pKeyState->bKeyStates[KEYID_I] = KEYDOWN(buffer, DIK_I) != 0;
	m_pKeyState->bKeyStates[KEYID_O] = KEYDOWN(buffer, DIK_O) != 0;
	m_pKeyState->bKeyStates[KEYID_P] = KEYDOWN(buffer, DIK_P) != 0;
	m_pKeyState->bKeyStates[KEYID_A] = KEYDOWN(buffer, DIK_A) != 0;
	m_pKeyState->bKeyStates[KEYID_S] = KEYDOWN(buffer, DIK_S) != 0;
	m_pKeyState->bKeyStates[KEYID_D] = KEYDOWN(buffer, DIK_D) != 0;
	m_pKeyState->bKeyStates[KEYID_F] = KEYDOWN(buffer, DIK_F) != 0;
	m_pKeyState->bKeyStates[KEYID_G] = KEYDOWN(buffer, DIK_G) != 0;
	m_pKeyState->bKeyStates[KEYID_H] = KEYDOWN(buffer, DIK_H) != 0;
	m_pKeyState->bKeyStates[KEYID_J] = KEYDOWN(buffer, DIK_J) != 0;
	m_pKeyState->bKeyStates[KEYID_K] = KEYDOWN(buffer, DIK_K) != 0;
	m_pKeyState->bKeyStates[KEYID_L] = KEYDOWN(buffer, DIK_L) != 0;
	m_pKeyState->bKeyStates[KEYID_Z] = KEYDOWN(buffer, DIK_Z) != 0;
	m_pKeyState->bKeyStates[KEYID_X] = KEYDOWN(buffer, DIK_X) != 0;
	m_pKeyState->bKeyStates[KEYID_C] = KEYDOWN(buffer, DIK_C) != 0;
	m_pKeyState->bKeyStates[KEYID_V] = KEYDOWN(buffer, DIK_V) != 0;
	m_pKeyState->bKeyStates[KEYID_B] = KEYDOWN(buffer, DIK_B) != 0;
	m_pKeyState->bKeyStates[KEYID_N] = KEYDOWN(buffer, DIK_N) != 0;
	m_pKeyState->bKeyStates[KEYID_M] = KEYDOWN(buffer, DIK_M) != 0;
	m_pKeyState->bKeyStates[KEYID_1] = KEYDOWN(buffer, DIK_1) != 0;
	m_pKeyState->bKeyStates[KEYID_2] = KEYDOWN(buffer, DIK_2) != 0;
	m_pKeyState->bKeyStates[KEYID_3] = KEYDOWN(buffer, DIK_3) != 0;
	m_pKeyState->bKeyStates[KEYID_4] = KEYDOWN(buffer, DIK_4) != 0;
	m_pKeyState->bKeyStates[KEYID_5] = KEYDOWN(buffer, DIK_5) != 0;
	m_pKeyState->bKeyStates[KEYID_6] = KEYDOWN(buffer, DIK_6) != 0;
	m_pKeyState->bKeyStates[KEYID_7] = KEYDOWN(buffer, DIK_7) != 0;
	m_pKeyState->bKeyStates[KEYID_8] = KEYDOWN(buffer, DIK_8) != 0;
	m_pKeyState->bKeyStates[KEYID_9] = KEYDOWN(buffer, DIK_9) != 0;
	m_pKeyState->bKeyStates[KEYID_0] = KEYDOWN(buffer, DIK_0) != 0;
	m_pKeyState->bKeyStates[KEYID_F1] = KEYDOWN(buffer, DIK_F1) != 0;
	m_pKeyState->bKeyStates[KEYID_F2] = KEYDOWN(buffer, DIK_F2) != 0;
	m_pKeyState->bKeyStates[KEYID_F3] = KEYDOWN(buffer, DIK_F3) != 0;
	m_pKeyState->bKeyStates[KEYID_F4] = KEYDOWN(buffer, DIK_F4) != 0;
	m_pKeyState->bKeyStates[KEYID_F5] = KEYDOWN(buffer, DIK_F5) != 0;
	m_pKeyState->bKeyStates[KEYID_F6] = KEYDOWN(buffer, DIK_F6) != 0;
	m_pKeyState->bKeyStates[KEYID_F7] = KEYDOWN(buffer, DIK_F7) != 0;
	m_pKeyState->bKeyStates[KEYID_F8] = KEYDOWN(buffer, DIK_F8) != 0;
	m_pKeyState->bKeyStates[KEYID_F9] = KEYDOWN(buffer, DIK_F9) != 0;
	m_pKeyState->bKeyStates[KEYID_F10] = KEYDOWN(buffer, DIK_F10) != 0;
	m_pKeyState->bKeyStates[KEYID_F11] = KEYDOWN(buffer, DIK_F11) != 0;
	m_pKeyState->bKeyStates[KEYID_F12] = KEYDOWN(buffer, DIK_F12) != 0;
	m_pKeyState->bKeyStates[KEYID_NUM0] = KEYDOWN(buffer, DIK_NUMPAD0) != 0;
	m_pKeyState->bKeyStates[KEYID_NUM1] = KEYDOWN(buffer, DIK_NUMPAD1) != 0;
	m_pKeyState->bKeyStates[KEYID_NUM2] = KEYDOWN(buffer, DIK_NUMPAD2) != 0;
	m_pKeyState->bKeyStates[KEYID_NUM3] = KEYDOWN(buffer, DIK_NUMPAD3) != 0;
	m_pKeyState->bKeyStates[KEYID_NUM4] = KEYDOWN(buffer, DIK_NUMPAD4) != 0;
	m_pKeyState->bKeyStates[KEYID_NUM5] = KEYDOWN(buffer, DIK_NUMPAD5) != 0;
	m_pKeyState->bKeyStates[KEYID_NUM6] = KEYDOWN(buffer, DIK_NUMPAD6) != 0;
	m_pKeyState->bKeyStates[KEYID_NUM7] = KEYDOWN(buffer, DIK_NUMPAD7) != 0;
	m_pKeyState->bKeyStates[KEYID_NUM8] = KEYDOWN(buffer, DIK_NUMPAD8) != 0;
	m_pKeyState->bKeyStates[KEYID_NUM9] = KEYDOWN(buffer, DIK_NUMPAD9) != 0;
	m_pKeyState->bKeyStates[KEYID_MINUS] = KEYDOWN(buffer, DIK_SUBTRACT) != 0;
	m_pKeyState->bKeyStates[KEYID_PLUS] = KEYDOWN(buffer, DIK_ADD) != 0;
	m_pKeyState->bKeyStates[KEYID_RIGHT] = KEYDOWN(buffer, DIK_RIGHT) != 0;
	m_pKeyState->bKeyStates[KEYID_LEFT] = KEYDOWN(buffer, DIK_LEFT) != 0;
	m_pKeyState->bKeyStates[KEYID_UP] = KEYDOWN(buffer, DIK_UP) != 0;
	m_pKeyState->bKeyStates[KEYID_DOWN] = KEYDOWN(buffer, DIK_DOWN) != 0;
	m_pKeyState->bKeyStates[KEYID_PGUP] = KEYDOWN(buffer, DIK_PRIOR) != 0;
	m_pKeyState->bKeyStates[KEYID_PGDOWN] = KEYDOWN(buffer, DIK_NEXT) != 0;
	m_pKeyState->bKeyStates[KEYID_ESC] = KEYDOWN(buffer, DIK_ESCAPE) != 0;
	m_pKeyState->bKeyStates[KEYID_BACK] = KEYDOWN(buffer, DIK_BACKSPACE) != 0;
	m_pKeyState->bKeyStates[KEYID_SPACE] = KEYDOWN(buffer, DIK_SPACE) != 0;
	m_pKeyState->bKeyStates[KEYID_ENTER] = KEYDOWN(buffer, DIK_RETURN) != 0;
	m_pKeyState->bKeyStates[KEYID_LSHIFT] = KEYDOWN(buffer, DIK_LSHIFT) != 0;
	m_pKeyState->bKeyStates[KEYID_RSHIFT] = KEYDOWN(buffer, DIK_RSHIFT) != 0;
	m_pKeyState->bKeyStates[KEYID_LCTRL] = KEYDOWN(buffer, DIK_LCONTROL) != 0;
	m_pKeyState->bKeyStates[KEYID_RCTRL] = KEYDOWN(buffer, DIK_RCONTROL) != 0;

}


bool CDInputKeyboard::IsKeyDown(EKeyID _e)
{
	return(m_pKeyState->bKeyStates[_e]);
}
bool CDInputKeyboard::WasKeyPressed(EKeyID _e)
{
	return(m_pKeyState->bKeyStates[_e] && !m_pLastKeyState->bKeyStates[_e]);
}

bool CDInputKeyboard::WasKeyReleased(EKeyID _e)
{
	return(!m_pKeyState->bKeyStates[_e] && m_pLastKeyState->bKeyStates[_e]);
}

bool CDInputKeyboard::WasAnyKeyPressed()
{
	for(unsigned int i = 0; i < KEYID_MAX; ++i)
	{
		if(WasKeyPressed((EKeyID)i))
		{
			return(true);
		}
	}
	
	return(false);
}

bool CDInputKeyboard::IsAnyKeyDown()
{
	for(unsigned int i = 0; i < KEYID_MAX; ++i)
	{
		if(IsKeyDown((EKeyID)i))
		{
			return(true);
		}
	}
	
	return(false);
}

void CDInputKeyboard::UpdateKeyMidFrame(EKeyID _e)
{
	m_pLastKeyState->bKeyStates[_e] = m_pKeyState->bKeyStates[_e];
}

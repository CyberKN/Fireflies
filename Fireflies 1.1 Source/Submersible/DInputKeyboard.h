#pragma once

#if !defined(__DInputKeyboard_H__)
#define __DInputKeyboard_H__

// Local Includes
#include "defines.h"

// Library Includes
#include <dinput.h>

// Types

enum EKeyID
{
	KEYID_A,
	KEYID_B,
	KEYID_C,
	KEYID_D,
	KEYID_E,
	KEYID_F,
	KEYID_G,
	KEYID_H,
	KEYID_I,
	KEYID_J,
	KEYID_K,
	KEYID_L,
	KEYID_M,
	KEYID_N,
	KEYID_O,
	KEYID_P,
	KEYID_Q,
	KEYID_R,
	KEYID_S,
	KEYID_T,
	KEYID_U,
	KEYID_V,
	KEYID_W,
	KEYID_X,
	KEYID_Y,
	KEYID_Z,
	KEYID_0,
	KEYID_1,
	KEYID_2,
	KEYID_3,
	KEYID_4,
	KEYID_5,
	KEYID_6,
	KEYID_7,
	KEYID_8,
	KEYID_9,
	KEYID_F1,
	KEYID_F2,
	KEYID_F3,
	KEYID_F4,
	KEYID_F5,
	KEYID_F6,
	KEYID_F7,
	KEYID_F8,
	KEYID_F9,
	KEYID_F10,
	KEYID_F11,
	KEYID_F12,
	KEYID_NUM0,
	KEYID_NUM1,
	KEYID_NUM2,
	KEYID_NUM3,
	KEYID_NUM4,
	KEYID_NUM5,
	KEYID_NUM6,
	KEYID_NUM7,
	KEYID_NUM8,
	KEYID_NUM9,
	KEYID_MINUS,
	KEYID_PLUS,
	KEYID_RIGHT,
	KEYID_LEFT,
	KEYID_UP,
	KEYID_DOWN,
	KEYID_PGUP,
	KEYID_PGDOWN,
	KEYID_ESC,
	KEYID_BACK,
	KEYID_SPACE,
	KEYID_ENTER,
	KEYID_LSHIFT,
	KEYID_RSHIFT,
	KEYID_LCTRL,
	KEYID_RCTRL,
	KEYID_MAX


};

struct TKeyState
{
	bool bKeyStates[KEYID_MAX];
};

// Constants

// Prototypes


class CDInputKeyboard
{
// Member Functions
public:
	CDInputKeyboard();
	~CDInputKeyboard();
	void Initialise();
	void Process(); 
	bool IsKeyDown(EKeyID _e);
	bool WasKeyPressed(EKeyID _e);
	bool WasKeyReleased(EKeyID _e);
	bool IsAnyKeyDown();
	bool WasAnyKeyPressed();
	void UpdateKeyMidFrame(EKeyID _e);



protected:

private:

// Member Variables
public:
	IDirectInput8* m_pDI;
	IDirectInputDevice8* pDIDevice;

protected:

	TKeyState* m_pKeyState;
	TKeyState* m_pLastKeyState;

private:

};

#endif // __DInputKeyboard_H__

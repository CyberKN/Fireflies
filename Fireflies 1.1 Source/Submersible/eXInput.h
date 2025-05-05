#pragma once

#if !defined(__XInput_H__)
#define __XInput_H__

// Library Includes
#include "d3d9.h"
#include "d3dx9.h"
#include "XInput.h"

// Local Includes

// Types
/*
#define XINPUT_GAMEPAD_DPAD_UP          0x00000001
#define XINPUT_GAMEPAD_DPAD_DOWN        0x00000002
#define XINPUT_GAMEPAD_DPAD_LEFT        0x00000004
#define XINPUT_GAMEPAD_DPAD_RIGHT       0x00000008
#define XINPUT_GAMEPAD_START            0x00000010
#define XINPUT_GAMEPAD_BACK             0x00000020
#define XINPUT_GAMEPAD_LEFT_THUMB       0x00000040
#define XINPUT_GAMEPAD_RIGHT_THUMB      0x00000080
#define XINPUT_GAMEPAD_LEFT_SHOULDER    0x0100
#define XINPUT_GAMEPAD_RIGHT_SHOULDER   0x0200
#define XINPUT_GAMEPAD_A                0x1000
#define XINPUT_GAMEPAD_B                0x2000
#define XINPUT_GAMEPAD_X                0x4000
#define XINPUT_GAMEPAD_Y                0x8000
*/


// Constants

// Prototypes


class CXInput
{
// Member Functions
public:

	CXInput();
	~CXInput();
	bool Initialise();
	void Process(); 
	void SetRumble(float _fLeft, float _fRight);
	void AddRumble(float _fLeft, float _fRight);

	float GetRumbleLeft();
	float GetRumbleRight();

	bool RetrieveState();
	void ReadTriggers(XINPUT_STATE& _rState);
	void ReadAnalogueSticks(XINPUT_STATE& _rState);
	void ReadButtons(XINPUT_STATE& _rState);


protected:

private:

// Member Variables
public:

	float m_fLeftThumbStickX;
	float m_fLeftThumbStickY;
	float m_fRightThumbStickX;
	float m_fRightThumbStickY;

	float m_fLeftThumbStickDeadZone;
	float m_fRightThumbStickDeadZone;

	float m_fLeftTrigger;
	float m_fRightTrigger;

	bool m_bAbuttonPressed;
	bool m_bBbuttonPressed;
	bool m_bXbuttonPressed;
	bool m_bYbuttonPressed;
	bool m_bLBbuttonPressed;
	bool m_bRBbuttonPressed;
	bool m_bBACKbuttonPressed;
	bool m_bSTARTbuttonPressed;
	bool m_bLSbuttonPressed;
	bool m_bRSbuttonPressed;
	bool m_bUPbuttonPressed;
	bool m_bRIGHTbuttonPressed;
	bool m_bLEFTbuttonPressed;
	bool m_bDOWNbuttonPressed;

	bool m_bButtonsReleased;
	int m_iNumButtonsPressed;

	bool m_bConnected;

	XINPUT_STATE xState;
	DWORD dwUserIndex;
	XINPUT_VIBRATION m_RumbleData;

protected:

private:

};

#endif // __XInput_H__

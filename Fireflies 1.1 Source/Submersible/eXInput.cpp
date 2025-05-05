// Library Includes

// Local Includes

// This include
#include "eXInput.h"
#include "Game.h"

// Constants

// Static Variables

// Static Function Prototypes

// Implementation

CXInput::CXInput()
:m_bConnected(0)
,m_bAbuttonPressed(0)
,m_bBbuttonPressed(0)
,m_bXbuttonPressed(0)
,m_bYbuttonPressed(0)
,m_bLBbuttonPressed(0)
,m_bRBbuttonPressed(0)
,m_bBACKbuttonPressed(0)
,m_bSTARTbuttonPressed(0)
,m_bLSbuttonPressed(0)
,m_bRSbuttonPressed(0)
,m_bUPbuttonPressed(0)
,m_bRIGHTbuttonPressed(0)
,m_bLEFTbuttonPressed(0)
,m_bDOWNbuttonPressed(0)
,m_fLeftThumbStickDeadZone(0.3f)
,m_fRightThumbStickDeadZone(0.3f)
,m_bButtonsReleased(1)
,m_iNumButtonsPressed(0)
,m_fLeftThumbStickX(0)
,m_fLeftThumbStickY(0)
,m_fRightThumbStickX(0)
,m_fRightThumbStickY(0)
,m_fLeftTrigger(0)
,m_fRightTrigger(0)
{
	SetRumble(0, 0);
}

CXInput::~CXInput()
{
		SetRumble(0, 0);
}

bool CXInput::Initialise()
{
	SetRumble(0, 0);

	DWORD dw = XInputGetState(dwUserIndex, &xState);

	if(dw == ERROR_SUCCESS)
	{
		m_bConnected = true;
		//return(true);
	}

	return(true);
}

void CXInput::Process()
{
	
	RetrieveState();

	if(m_bConnected)
	{
		float fDeltaTick = CGame::GetInstance().m_fDeltaTick*3;



		if(GetRumbleLeft() > 0.05f)
		{
			SetRumble(GetRumbleLeft()-fDeltaTick, GetRumbleRight());
		}
		else
		{
			SetRumble(0, GetRumbleRight());
		}

		if(GetRumbleRight() > 0.05f)
		{
			SetRumble(GetRumbleLeft(), GetRumbleRight()-fDeltaTick);
		}
		else
		{
			SetRumble(GetRumbleLeft(), 0);
		}
	}

}

void CXInput::SetRumble(float _fLeft, float _fRight)
{
	float fLeftRumble =  _fLeft*65535.0f;
	float fRightRumble = _fRight*65535.0f;
	m_RumbleData.wLeftMotorSpeed = static_cast<unsigned int>(fLeftRumble);
	m_RumbleData.wRightMotorSpeed = static_cast<unsigned int>(fRightRumble);

	XInputSetState(dwUserIndex, &m_RumbleData);
}

void CXInput::AddRumble(float _fLeft, float _fRight)
{
	float fLeftRumble = (GetRumbleLeft()+ _fLeft)*65535.0f;
	float fRightRumble = (GetRumbleRight()+ _fRight)*65535.0f;

	if(fLeftRumble > 65535.0f)
	{
		fLeftRumble = 65535.0f;
	}
	if(fRightRumble > 65535.0f)
	{
		fRightRumble = 65535.0f;
	}
	m_RumbleData.wLeftMotorSpeed = static_cast<unsigned int>(fLeftRumble);
	m_RumbleData.wRightMotorSpeed = static_cast<unsigned int>(fRightRumble);

	XInputSetState(dwUserIndex, &m_RumbleData);
}

float CXInput::GetRumbleLeft()
{
	float fRumbleLeft = static_cast<float>(m_RumbleData.wLeftMotorSpeed)/65535.0f;
	return (fRumbleLeft);
}

float CXInput::GetRumbleRight()
{
	float fRumbleRight = static_cast<float>(m_RumbleData.wRightMotorSpeed)/65535.0f;
	return (fRumbleRight);
}

bool CXInput::RetrieveState()
{
	DWORD dw = XInputGetState(dwUserIndex, &xState);

	if(dw != ERROR_SUCCESS)
	{
		return(false);
	}
	else
	{
		m_bConnected = true;
		ReadTriggers(xState);
		ReadAnalogueSticks(xState);
		ReadButtons(xState);
	}
	return(true);
}

void CXInput::ReadTriggers(XINPUT_STATE& _rState)
{
	m_fLeftTrigger = static_cast<float>(_rState.Gamepad.bLeftTrigger)/255.0f;
	m_fRightTrigger = static_cast<float>(_rState.Gamepad.bRightTrigger)/255.0f;
}

void CXInput::ReadAnalogueSticks(XINPUT_STATE& _rState)
{
	m_fLeftThumbStickX  = static_cast<float>(_rState.Gamepad.sThumbLX)/32768.0f;
	m_fLeftThumbStickY  = static_cast<float>(_rState.Gamepad.sThumbLY)/32768.0f;
	m_fRightThumbStickX  = static_cast<float>(_rState.Gamepad.sThumbRX)/32768.0f;
	m_fRightThumbStickY  = static_cast<float>(_rState.Gamepad.sThumbRY)/32768.0f;

	if(m_fLeftThumbStickX < m_fLeftThumbStickDeadZone && m_fLeftThumbStickX > -m_fLeftThumbStickDeadZone)
	{
		m_fLeftThumbStickX = 0.0f;
	}

	if(m_fLeftThumbStickY < m_fLeftThumbStickDeadZone && m_fLeftThumbStickY > -m_fLeftThumbStickDeadZone)
	{
		m_fLeftThumbStickY = 0.0f;
	}

	if(m_fRightThumbStickX < m_fRightThumbStickDeadZone && m_fRightThumbStickX > -m_fRightThumbStickDeadZone)
	{
		m_fRightThumbStickX = 0.0f;
	}

	if(m_fRightThumbStickY < m_fRightThumbStickDeadZone && m_fRightThumbStickY > -m_fRightThumbStickDeadZone)
	{
		m_fRightThumbStickY = 0.0f;
	}


}

void CXInput::ReadButtons(XINPUT_STATE& _rState)
{
	WORD wButtonState =  _rState.Gamepad.wButtons; 

	if(m_iNumButtonsPressed > 0)
	{
		m_bButtonsReleased = false;
	}
	else
	{
		m_bButtonsReleased = true;
	}

	m_iNumButtonsPressed = 0;

	if(wButtonState & XINPUT_GAMEPAD_A)
	{
		++m_iNumButtonsPressed;
		m_bAbuttonPressed = true;
	}
	else
	{
		m_bAbuttonPressed = false;
	}

	if(wButtonState & XINPUT_GAMEPAD_B)
	{
		++m_iNumButtonsPressed;
		m_bBbuttonPressed = true;
	}
	else
	{
		m_bBbuttonPressed = false;
	}

	if(wButtonState & XINPUT_GAMEPAD_X)
	{
		++m_iNumButtonsPressed;
		m_bXbuttonPressed = true;
	}
	else
	{
		m_bXbuttonPressed = false;
	}

	if(wButtonState & XINPUT_GAMEPAD_Y)
	{
		++m_iNumButtonsPressed;
		m_bYbuttonPressed = true;
	}
	else
	{
		m_bYbuttonPressed = false;
	}

	if(wButtonState & XINPUT_GAMEPAD_BACK)
	{
		++m_iNumButtonsPressed;
		m_bBACKbuttonPressed = true;
	}
	else
	{
		m_bBACKbuttonPressed = false;
	}

	if(wButtonState & XINPUT_GAMEPAD_START)
	{
		++m_iNumButtonsPressed;
		m_bSTARTbuttonPressed = true;
	}
	else
	{
		m_bSTARTbuttonPressed = false;
	}

	if(wButtonState & XINPUT_GAMEPAD_LEFT_SHOULDER)
	{
		++m_iNumButtonsPressed;
		m_bLBbuttonPressed = true;
	}
	else
	{
		m_bLBbuttonPressed = false;
	}

	if(wButtonState & XINPUT_GAMEPAD_RIGHT_SHOULDER)
	{
		++m_iNumButtonsPressed;
		m_bRBbuttonPressed = true;
	}
	else
	{
		m_bRBbuttonPressed = false;
	}

	if(wButtonState & XINPUT_GAMEPAD_RIGHT_THUMB)
	{
		++m_iNumButtonsPressed;
		m_bRSbuttonPressed = true;
	}
	else
	{
		m_bRSbuttonPressed = false;
	}

	if(wButtonState & XINPUT_GAMEPAD_LEFT_THUMB)
	{
		++m_iNumButtonsPressed;
		m_bLSbuttonPressed = true;
	}
	else
	{
		m_bLSbuttonPressed = false;
	}

	if(wButtonState & XINPUT_GAMEPAD_DPAD_UP)
	{
		++m_iNumButtonsPressed;
		m_bUPbuttonPressed = true;
	}
	else
	{
		m_bUPbuttonPressed = false;
	}

	if(wButtonState & XINPUT_GAMEPAD_DPAD_LEFT)
	{
		++m_iNumButtonsPressed;
		m_bLEFTbuttonPressed = true;
	}
	else
	{
		m_bLEFTbuttonPressed = false;
	}

	if(wButtonState & XINPUT_GAMEPAD_DPAD_RIGHT)
	{
		++m_iNumButtonsPressed;
		m_bRIGHTbuttonPressed = true;
	}
	else
	{
		m_bRIGHTbuttonPressed = false;
	}

	if(wButtonState & XINPUT_GAMEPAD_DPAD_DOWN)
	{
		++m_iNumButtonsPressed;
		m_bDOWNbuttonPressed = true;
	}
	else
	{
		m_bDOWNbuttonPressed = false;
	}
}

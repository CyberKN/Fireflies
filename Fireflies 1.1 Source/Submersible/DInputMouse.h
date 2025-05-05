#pragma once

#if !defined(__DInputMouse_H__)
#define __DInputMouse_H__

// Library Includes
#include <dinput.h>

// Local Includes

// Types

enum EMouseButtonID
{
	MOUSEBID_LEFT,
	MOUSEBID_RIGHT,
	MOUSEBID_MIDDLE,
	MOUSEBID_MAX
};

enum EMouseMoveID
{
	MOUSEMOVE_X,
	MOUSEMOVE_Y,
	MOUSEMOVE_Z,
	MOUSEMOVE_MAX
};

enum EMousePositionID
{
	MOUSEPOS_X,
	MOUSEPOS_Y,
	MOUSEPOS_MAX
};

struct TMouseState
{
	bool	bButtonStates[MOUSEBID_MAX];
	float	fMoveStates[MOUSEMOVE_MAX];
	int		iPosStates[MOUSEPOS_MAX];
};

// Constants

// Prototypes


class CDInputMouse
{
// Member Functions
public:
	CDInputMouse();
	~CDInputMouse();
	void Initialise();
	void Process(); 
	bool IsButtonDown(EMouseButtonID _e);
	bool WasButtonPressed(EMouseButtonID _e);	
	bool WasButtonReleased(EMouseButtonID _e);
	bool IsAnyButtonDown();
	bool WasAnyButtonPressed();

	float GetMovement(EMouseMoveID _e);
	int GetPosition(EMousePositionID _e);
	int GetX();
	int GetY();

	void SetMouseLocked(bool _b);
	bool IsMouseLocked();


protected:

private:

// Member Variables
public:
	IDirectInput8* m_pDI;
	IDirectInputDevice8* pDIDevice;

protected:

	//bool m_bRightMouseButtonPressed;
	//bool m_bLeftMouseButtonPressed;
	//bool m_bMiddleMouseButtonPressed;
	//
	//float m_fMouseMovementX;
	//float m_fMouseMovementY;
	//float m_fMouseMovementZ;

	//int m_iMousePosX;
	//int m_iMousePosY;

	TMouseState* m_pMouseState;
	TMouseState* m_pLastMouseState;

	bool m_bLockMouse;

private:

};

#endif // __DInputMouse_H__

// Library Includes

// Local Includes

#include "Game.h"
#include "resource2.h"
#include "utils.h"

// This include
#include "DialogBox.h"

// Constants

// Static Variables

// Static Function Prototypes

// Implementation

BOOL CALLBACK DebugDialogProc(HWND _hLevelDlg, UINT _msg, WPARAM _wparam, LPARAM _lparam)
{
	switch(_msg)
	{
	case WM_INITDIALOG:
		{

			HWND hEditBox = GetDlgItem(_hLevelDlg, IDC_EDIT);
			wstring boxEnter = StringToWString(FloatToString(*CGame::GetInstance().m_DialogBox.m_pModifiedValue));
			SetWindowText(hEditBox, boxEnter.c_str());


		}
		break;

	case WM_COMMAND:
		{
			switch(LOWORD(_wparam))
			{

			case WM_DESTROY:
				{
							CGame::GetInstance().m_DialogBox.m_pModifiedValue = 0;
							DestroyWindow(_hLevelDlg);
							return true;
							break;
				}
				break;
				
			case IDC_OK:
				{
						HWND hEditBox = GetDlgItem(_hLevelDlg, IDC_EDIT);
						wchar_t cMessage2[256];
						GetWindowText(hEditBox, cMessage2, 256);
						*CGame::GetInstance().m_DialogBox.m_pModifiedValue = StringToFloat(WStringToString(cMessage2));
						CGame::GetInstance().m_DialogBox.m_pModifiedValue = 0;

						DestroyWindow(_hLevelDlg);
						return true;
						break;
				}
				break;
			
			case IDC_CANCEL:
			{
						CGame::GetInstance().m_DialogBox.m_pModifiedValue = 0;
						DestroyWindow(_hLevelDlg);
						return true;
						break;
			}
			break;
			default:
				{

				}
			}
		}
		
		break;
	default:
		{
			return false;
		}
	}
	return false;
}

CDialogBox::CDialogBox()
{

}

CDialogBox::~CDialogBox()
{

}

/**
* function to open a dialog box and set the modified value to the variable passed in
* 
* @Author Kurt
* @param _pModifiedValue			value to change m_pModifiedValue to
*/
void CDialogBox::Open(float* _pModifiedValue)
{
	m_pModifiedValue = _pModifiedValue;
	DialogBox(NULL, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DebugDialogProc);
}


void CDialogBox::Close()
{

}



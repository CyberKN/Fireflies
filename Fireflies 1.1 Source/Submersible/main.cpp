
#define WIN_32_LEAN_AND_MEAN
//#define D3D_DEBUG_INFO

#ifndef DIRECTINPUT_VERSION
#define DIRECTINPUT_VERSION 0x0800
#endif

#include <windows.h>
#include <ctime>
#include <vector>
#include <windowsx.h>
#include <vld.h>

#include "Game.h"
#include "resource2.h"
#include "Clock.h"

#define WINDOW_CLASS_NAME L"Fireflies"

int iMouseX; 
int iMouseY; 

LRESULT CALLBACK WindowProc(HWND _hwnd, UINT _msg, WPARAM _wparam, LPARAM _lparam)
{
	//This is the main message handler of the system.
	PAINTSTRUCT ps; //Used in WM_PAINT
	HDC hdc;		//Handle to a device context

	//What is the message?
	switch(_msg)
	{
	case WM_CREATE:
		{
			//Do Initialization stuff here.

			//Return success
			return(0);
		}
		break;

	case WM_LBUTTONDOWN:
		{
			
		}
		break;

	case WM_RBUTTONDOWN:
		{
			
		}
		break;

	case WM_WINDOWPOSCHANGED:
		{
			tagWINDOWPOS* Windata = (tagWINDOWPOS*)_lparam;
			CGame::GetInstance().m_iWindowOffsetX = Windata->x;
			CGame::GetInstance().m_iWindowOffsetY = Windata->y;
			
		}
		break;		
	case WM_MOUSEMOVE:
		{
						
		}
		break;

	case WM_KILLFOCUS:
		{
			CGame::GetInstance().SetHasFocus(false);			
		}
		break;

	case WM_SETFOCUS:
		{
			CGame::GetInstance().SetHasFocus(true);					
		}
		break;

	case WM_COMMAND:
		{/*

			switch(LOWORD(_wparam))
			{

			default:
				{
				}			
			}*/
		}

			//http://delphi.about.com/od/objectpascalide/l/blvkc.htm
	/*case WM_KEYDOWN:
		{


		}
		break;

	case WM_KEYUP:
		{

			
		}
		break;*/

	case WM_PAINT:
		{
			//Simply validate the window.
			hdc = BeginPaint(_hwnd, &ps);

			//You would do all your painting here...

			EndPaint(_hwnd, &ps);

			//Return Success.
			return(0);
		}
		break;
	case WM_DESTROY:
		{
			//Kill the application, this sends a WM_QUIT message.
			PostQuitMessage(0);



			//Return Success.
			return(0);
		}
		break;

	default:break;
	}//End Switch

	//Process any messages that we didn't take care of...

	return(DefWindowProc(_hwnd, _msg, _wparam, _lparam));
}

HWND
CreateAndRegisterWindow(HINSTANCE _hInstance, int _iWidth, int _iHeight, LPCWSTR _pcTitle)
{


	WNDCLASSEX winclass; //this will hold the class that we create.

	//First fill in the window class structure.
	winclass.cbSize = sizeof(WNDCLASSEX);
	winclass.style = CS_HREDRAW | CS_VREDRAW;
	winclass.lpfnWndProc = WindowProc;
	winclass.cbClsExtra = 0;
	winclass.cbWndExtra = 0;
	winclass.hInstance = _hInstance;
	winclass.hIcon =  LoadIcon(_hInstance, MAKEINTRESOURCE(IDI_ICON1));
	winclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	winclass.hbrBackground = static_cast<HBRUSH>(GetStockObject(NULL));
	winclass.lpszMenuName = 0;
	winclass.lpszClassName = WINDOW_CLASS_NAME;
	winclass.hIconSm =  LoadIcon(_hInstance, MAKEINTRESOURCE(IDI_ICON1));

	//register the window class
	if (!RegisterClassEx(&winclass))
	{
		return(0);
	}

	HWND hWnd;
	//create the window
	hWnd = CreateWindowEx(NULL,	//Extended style.
			WINDOW_CLASS_NAME,
			L"Fireflies",
			WS_BORDER | WS_CAPTION | WS_SYSMENU | WS_VISIBLE | WS_MINIMIZEBOX,
			0,0,
			_iWidth, _iHeight,
			NULL,
			NULL,
			_hInstance, 
			NULL);
	if(!hWnd)
	{
		return(0);
	}

	return(hWnd);
}

int WINAPI
WinMain (HINSTANCE _hInstance, HINSTANCE _hPrevInstance, LPSTR _lpCmdLine, int nCmdShow)
{
	srand(static_cast<unsigned int>(time(0)));
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	int ix = AddFontResourceA("Images/Font/denmark.ttf");

	const int kiWidth = 800;
	const int kiHeight = 600;

	HWND hwnd = CreateAndRegisterWindow(_hInstance, kiWidth + 6 , kiHeight + 26, L"Fireflies");

	CGame& rGame = CGame::GetInstance();
	//DESIGN PATTERN: Singleton

	if(!rGame.Initialise(_hInstance, hwnd, kiWidth, kiHeight))
	{
		return(0);
	}

	while(msg.message != WM_QUIT)
	{
		if(PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			
			rGame.ExecuteOneFrame();
		}
	}

	CGame::DestroyInstance();

	
	 ix = RemoveFontResourceA("Images/Font/denmark.ttf");

	return (static_cast<int>(msg.wParam));
}







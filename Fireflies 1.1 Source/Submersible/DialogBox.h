#pragma once

#if !defined(__DialogBox_H__)
#define __DialogBox_H__

// Library Includes
#include <windows.h>
#include <ctime>
#include <string>
#include <vector>
#include <windowsx.h>

// Local Includes

// Types

using namespace std;

// Constants

// Prototypes


class CDialogBox
{
// Member Functions
public:
	CDialogBox();
	~CDialogBox();
	void Open(float* _pModifiedValue);
	void Close();

protected:

private:

// Member Variables
public:
	float* m_pModifiedValue;

protected:

private:

};

#endif // __DialogBox_H__

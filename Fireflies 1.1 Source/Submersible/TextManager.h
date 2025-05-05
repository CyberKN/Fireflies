#pragma once

#if !defined(__TextManager_H__)
#define __TextManager_H__

// Library Includes
#include "TextBox.h"
#include <vector>

// Local Includes

// Types

// Constants

// Prototypes


class CTextManager
{
// Member Functions
public:
	CTextManager();
	~CTextManager();
	void Initialise();
	void Draw(CTextBox* _pTextBox, std::string _TextString);

	
	void OnLostDevice();
	void OnResetDevice();


protected:

private:

// Member Variables
public:

	D3DXFONT_DESC m_fontDesc;

	std::vector<ID3DXFont*> m_FontVec;



protected:

private:

};

#endif // __TextManager_H__

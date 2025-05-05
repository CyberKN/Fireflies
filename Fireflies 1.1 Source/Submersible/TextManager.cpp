// Library Includes

// Local Includes

// This include
#include "TextManager.h"
#include "game.h"
#include "utils.h"

// Constants

// Static Variables

// Static Function Prototypes

// Implementation
CTextManager::CTextManager()
{

}

CTextManager::~CTextManager()
{
	for(unsigned int i = 0; i < m_FontVec.size(); ++i)
	{
		m_FontVec[i]->Release();
		m_FontVec[i] = 0;
	}



}

void CTextManager::Initialise()
{
	m_FontVec.resize(20);
	int i = 1;
	while( i != 1)
	{
		i = 1;
	}

	for(; i < 21; ++i)
	{
		ZeroMemory(&m_fontDesc, sizeof(D3DXFONT_DESC));

		float fHeight = 5*static_cast<float>(i);
		float fWidth = 2*static_cast<float>(i);


		m_fontDesc.Height = static_cast<int>(fHeight);
		m_fontDesc.Width = static_cast<int>(fWidth);

		m_fontDesc.Weight = 200;
		m_fontDesc.MipLevels = 1;
		m_fontDesc.Italic = false;
		m_fontDesc.CharSet = DEFAULT_CHARSET;
		m_fontDesc.OutputPrecision = OUT_DEFAULT_PRECIS;
		m_fontDesc.Quality = PROOF_QUALITY;
		m_fontDesc.PitchAndFamily = 0;

		//if(i < 4)
		//{
		//	wcscpy_s(m_fontDesc.FaceName, L"Arial");
		//}
		//else
		//{
		//	wcscpy_s(m_fontDesc.FaceName, L"Arial Black");
		//}
		wcscpy_s(m_fontDesc.FaceName, L"Denmark Regular");


		D3DXCreateFontIndirect(CGame::GetInstance().m_DirectX3DRenderer.m_pDevice, &m_fontDesc, &m_FontVec[i-1]);
	}


}

void CTextManager::Draw(CTextBox* _pTextBox, std::string _TextString)
{
	RECT rect;
	
	float fInvertY = CGame::GetInstance().m_iWindowHeight - _pTextBox->m_fY;

	rect.top = static_cast<LONG>(fInvertY - CGame::GetInstance().m_iWindowHeight*0.5f);
	rect.left = static_cast<LONG>(_pTextBox->m_fX - CGame::GetInstance().m_iWindowWidth*0.5f);
	rect.right = static_cast<LONG>(_pTextBox->m_fX + CGame::GetInstance().m_iWindowWidth*0.5f);
	rect.bottom = static_cast<LONG>(fInvertY + CGame::GetInstance().m_iWindowHeight*0.5f);

	int iRed = _pTextBox->m_iRed;
	int iGreen = _pTextBox->m_iGreen;
	int iBlue = _pTextBox->m_iBlue;
	int iAlpha = _pTextBox->m_iAlpha;
	int iSize = _pTextBox->m_iSize;

	if(static_cast<int>(_TextString.size()) <= _pTextBox->m_iMaxCharsPerLine)
	{
		wstring wstrText = StringToWString(_TextString);

		if(_pTextBox->m_bCentered)
		{
			m_FontVec[iSize-1]->DrawText(NULL, wstrText.c_str(), -1, &rect, DT_VCENTER | DT_CENTER, D3DCOLOR_ARGB(iAlpha, iRed, iGreen, iBlue));
		}
		else
		{

			rect.left = static_cast<LONG>(_pTextBox->m_fX);
			rect.right = static_cast<LONG>(_pTextBox->m_fX + CGame::GetInstance().m_iWindowWidth);

			m_FontVec[iSize-1]->DrawText(NULL, wstrText.c_str(), -1, &rect, DT_VCENTER | DT_LEFT, D3DCOLOR_ARGB(iAlpha, iRed, iGreen, iBlue));
		}
	}
	else
	{
		std::vector<std::string> m_Lines;
		m_Lines.resize(1);

		for(unsigned int i = 0; i < _TextString.size(); ++i)
		{
			if(m_Lines[m_Lines.size()-1].size() == _pTextBox->m_iMaxCharsPerLine)
			{
				m_Lines.resize(m_Lines.size()+1);
			}
			m_Lines[m_Lines.size()-1].push_back(_TextString[i]);
		}

		for(unsigned int i = 0; i < m_Lines.size(); ++i)
		{
			wstring wstrText = StringToWString(m_Lines[i]);

			if(_pTextBox->m_bCentered)
			{
				m_FontVec[iSize-1]->DrawText(NULL, wstrText.c_str(), -1, &rect, DT_VCENTER | DT_CENTER, D3DCOLOR_ARGB(iAlpha, iRed, iGreen, iBlue));
			}
			else
			{

				rect.left = static_cast<LONG>(_pTextBox->m_fX);
				rect.right = static_cast<LONG>(_pTextBox->m_fX + CGame::GetInstance().m_iWindowWidth);

				m_FontVec[iSize-1]->DrawText(NULL, wstrText.c_str(), -1, &rect, DT_VCENTER | DT_LEFT, D3DCOLOR_ARGB(iAlpha, iRed, iGreen, iBlue));
			}

			rect.top += 10*iSize;
		}
	}
}



void CTextManager::OnLostDevice()
{
	for(unsigned int i = 0; i < m_FontVec.size(); ++i)
	{
		m_FontVec[i]->OnLostDevice();
	}
}

void CTextManager::OnResetDevice()
{
	for(unsigned int i = 0; i < m_FontVec.size(); ++i)
	{
		m_FontVec[i]->OnResetDevice();
	}

}





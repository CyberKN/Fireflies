// Library Includes

// Local Includes
#include "INIParser.h"
#include "utils.h"

// This include
#include "SpriteManager.h"

// Constants

// Static Variables

// Static Function Prototypes

// Implementation

CSpriteManager::CSpriteManager()
:m_fDrawOffsetX(0)
,m_fDrawOffsetY(0)
,m_bBatchDrawing(false)
,m_fZoom(1)
{

}

CSpriteManager::~CSpriteManager()
{
	for(unsigned int i = 0; i < m_SpriteVec.size(); ++i)
	{
		if(m_SpriteVec[i])
		{
			delete m_SpriteVec[i];
			m_SpriteVec[i] = 0;
		}
	}

	for(unsigned int i = 0; i < m_DrawList.size(); ++i)
	{
		delete m_DrawList[i];
		m_DrawList[i] = 0;
	}

}

void CSpriteManager::Initialise()
{
	CINIParser SpriteParser;

	SpriteParser.LoadIniFile("Images\\Sprites.ini");

	std::string strFileName = "";
	int iFrameSizeX = 0;
	int iFrameSizeY = 0;
	float fDefaultScale = 1;
	int iFrameTotal = 1;
	
	int iSpriteNum = 1;
	std::string strSpriteNum = "Sprite" + IntToString(iSpriteNum);
	CAnimatedSprite* pSprite = 0;

	while(SpriteParser.SafeCheck(strSpriteNum, "FilePath"))
	{
		iFrameSizeX = 0;
		iFrameTotal = 1;
		fDefaultScale = 1;
		strFileName = "";

		SpriteParser.GetStringValue(strSpriteNum, "FilePath", strFileName);
		SpriteParser.GetIntValue(strSpriteNum, "SizeX", iFrameSizeX, true);
		SpriteParser.GetIntValue(strSpriteNum, "SizeY", iFrameSizeY, true);
		SpriteParser.GetFloatValue(strSpriteNum, "Scale", fDefaultScale, true);
		SpriteParser.GetIntValue(strSpriteNum, "FrameTotal", iFrameTotal, true);

		pSprite = new CAnimatedSprite;
		pSprite->Initialise(StringToWString(strFileName).c_str(), iFrameSizeX, iFrameSizeY, fDefaultScale, this);

		for(int i = 0; i < iFrameTotal; ++i)
		{
			pSprite->AddFrame(i*pSprite->GetFrameWidth(), 0);
		}
		
		m_SpriteVec.push_back(pSprite);

		pSprite = 0;
		++iSpriteNum;
		strSpriteNum = "Sprite" + IntToString(iSpriteNum);
	}

	/*CAnimatedSprite* pSprite = 0;

	pSprite = new CAnimatedSprite;
	pSprite->Initialise(L"Images/Block4Sides.bmp", 64, 64, 1, this);
	pSprite->AddFrame(0, 0);
	m_SpriteVec.push_back(pSprite);

	pSprite = new CAnimatedSprite;
	pSprite->Initialise(L"Images/Surface.bmp", 700, 700, 1, this);
	pSprite->AddFrame(0, 0);
	m_SpriteVec.push_back(pSprite);
	
	pSprite = new CAnimatedSprite;
	pSprite->Initialise(L"Images/PlayerSub.bmp", 84, 47, 1, this);
	pSprite->AddFrame(0, 0);
	m_SpriteVec.push_back(pSprite);

	pSprite = new CAnimatedSprite;
	pSprite->Initialise(L"Images/GoldFish.bmp", 19, 13, 1, this);
	pSprite->AddFrame(0, 0);
	m_SpriteVec.push_back(pSprite);

	pSprite = new CAnimatedSprite;
	pSprite->Initialise(L"Images/SwordFish.bmp", 72, 19, 1, this);
	pSprite->AddFrame(0, 0);
	m_SpriteVec.push_back(pSprite);

	pSprite = new CAnimatedSprite;
	pSprite->Initialise(L"Images/Shark.bmp", 102, 34, 1, this);
	pSprite->AddFrame(0, 0);
	m_SpriteVec.push_back(pSprite);

	pSprite = new CAnimatedSprite;
	pSprite->Initialise(L"Images/SquidAnim.bmp", 38, 63, 1, this);
	pSprite->AddFrame(0, 0);
	pSprite->AddFrame(39, 0);
	m_SpriteVec.push_back(pSprite);

	pSprite = new CAnimatedSprite;
	pSprite->Initialise(L"Images/EnemySub.bmp", 121, 70, 1, this);
	pSprite->AddFrame(0, 0);
	m_SpriteVec.push_back(pSprite);

	pSprite = new CAnimatedSprite;
	pSprite->Initialise(L"Images/Torpedo.bmp", 26, 6, 1, this);
	pSprite->AddFrame(0, 0);
	m_SpriteVec.push_back(pSprite);

	pSprite = new CAnimatedSprite;
	pSprite->Initialise(L"Images/InkBlot.bmp", 22, 19, 1, this);
	pSprite->AddFrame(0, 0);
	m_SpriteVec.push_back(pSprite);

	pSprite = new CAnimatedSprite;
	pSprite->Initialise(L"Images/lighting.png", 1400, 700, 1, this);
	pSprite->AddFrame(0, 0);
	m_SpriteVec.push_back(pSprite);

	pSprite = new CAnimatedSprite;
	pSprite->Initialise(L"Images/SeaFloor.bmp", 700, 700, 1, this);
	pSprite->AddFrame(0, 0);
	m_SpriteVec.push_back(pSprite);

	pSprite = new CAnimatedSprite;
	pSprite->Initialise(L"Images/TipBox.bmp", 500, 70, 1, this);
	pSprite->AddFrame(0, 0);
	m_SpriteVec.push_back(pSprite);

	pSprite = new CAnimatedSprite;
	pSprite->Initialise(L"Images/Explosion_Sprite.png", 100, 100, 1, this);
	for(int i = 0; i < 5; ++i)
	{
		pSprite->AddFrame(i*100, 0);
	}
	m_SpriteVec.push_back(pSprite);

	pSprite = new CAnimatedSprite;
	pSprite->Initialise(L"Images/Ship.bmp", 109, 60, 1, this);
	pSprite->AddFrame(0, 0);
	m_SpriteVec.push_back(pSprite);

	pSprite = new CAnimatedSprite;
	pSprite->Initialise(L"Images/MenuArrow.bmp", 32, 32, 1, this);
	pSprite->AddFrame(0, 0);
	m_SpriteVec.push_back(pSprite);

	pSprite = new CAnimatedSprite;
	pSprite->Initialise(L"Images/MainMenu.bmp", 450, 475, 1, this);
	pSprite->AddFrame(0, 0);
	m_SpriteVec.push_back(pSprite);

	pSprite = new CAnimatedSprite;
	pSprite->Initialise(L"Images/UpgradeMenu.bmp", 450, 475, 1, this);
	pSprite->AddFrame(0, 0);
	m_SpriteVec.push_back(pSprite);

	pSprite = new CAnimatedSprite;
	pSprite->Initialise(L"Images/WinMenu.bmp", 450, 475, 1, this);
	pSprite->AddFrame(0, 0);
	m_SpriteVec.push_back(pSprite);

	pSprite = new CAnimatedSprite;
	pSprite->Initialise(L"Images/PauseMenu.bmp", 300, 300, 1, this);
	pSprite->AddFrame(0, 0);
	m_SpriteVec.push_back(pSprite);

	pSprite = new CAnimatedSprite;
	pSprite->Initialise(L"Images/Bubble.bmp", 64, 64, 1, this);
	pSprite->AddFrame(0, 0);
	m_SpriteVec.push_back(pSprite);
	
	pSprite = new CAnimatedSprite;
	pSprite->Initialise(L"Images/Firefly.png", 64, 64, 1, this);
	pSprite->AddFrame(0, 0);
	m_SpriteVec.push_back(pSprite);

	pSprite = new CAnimatedSprite;
	pSprite->Initialise(L"Images/NameForm.png", 169, 60, 1, this);
	pSprite->AddFrame(0, 0);
	m_SpriteVec.push_back(pSprite);*/




}

void CSpriteManager::DrawList()
{
	for(unsigned int i = 0; i < m_DrawList.size(); ++i)
	{
		int k = static_cast<int>(m_DrawList[i]->GetSpriteID());

		m_SpriteVec[k]->TranslateAbsolute(m_DrawList[i]->GetX()+m_fDrawOffsetX, m_DrawList[i]->GetY()+m_fDrawOffsetY);
		m_SpriteVec[k]->SetColor(m_DrawList[i]->GetAlpha(),
								m_DrawList[i]->GetRed(),
								m_DrawList[i]->GetGreen(),
								m_DrawList[i]->GetBlue());
		m_SpriteVec[k]->m_iCurrentSprite = m_DrawList[i]->GetCurrentFrame();
		m_SpriteVec[k]->SetRotate(m_DrawList[i]->GetRotate());
		m_SpriteVec[k]->m_fXScale = m_DrawList[i]->GetScaleX();
		m_SpriteVec[k]->m_fYScale = m_DrawList[i]->GetScaleY();

		m_SpriteVec[k]->Draw();
	}

	for(unsigned int i = 0; i < m_DrawList.size(); ++i)
	{
		if(m_DrawList[i])
		{
			delete m_DrawList[i];
			m_DrawList[i] = 0;
		}
	}
	m_DrawList.resize(0);

}

void CSpriteManager::Draw(CSpriteDataShell* _pSDS)
{

	int k = static_cast<int>(_pSDS->GetSpriteID());

	float fScreenCentreX = 400;
	float fScreenCentreY = 300;

	if(_pSDS->IgnoreOffset())
	{
		m_SpriteVec[k]->TranslateAbsolute(_pSDS->GetX(), _pSDS->GetY());
		
		m_SpriteVec[k]->m_fXScale = _pSDS->GetScaleX();
		m_SpriteVec[k]->m_fYScale = _pSDS->GetScaleY();
	}
	else
	{
		float m_fZoomOffsetX = (_pSDS->GetX() - fScreenCentreX)*(m_fZoom-1);
		float m_fZoomOffsetY = (_pSDS->GetY() - fScreenCentreY)*(m_fZoom-1);

		m_SpriteVec[k]->TranslateAbsolute(_pSDS->GetX()+m_fZoomOffsetX+(m_fDrawOffsetX*m_fZoom), _pSDS->GetY()+m_fZoomOffsetY+(m_fDrawOffsetY*m_fZoom));
	
		m_SpriteVec[k]->m_fXScale = m_fZoom*_pSDS->GetScaleX();
		m_SpriteVec[k]->m_fYScale = m_fZoom*_pSDS->GetScaleY();
	}

	m_SpriteVec[k]->SetColor(_pSDS->GetAlpha(),
							_pSDS->GetRed(),
							_pSDS->GetGreen(),
							_pSDS->GetBlue());
	m_SpriteVec[k]->m_iCurrentSprite = _pSDS->GetCurrentFrame();
	m_SpriteVec[k]->SetRotate(_pSDS->GetRotate());


	m_SpriteVec[k]->Draw();

}

void CSpriteManager::AddToDrawList(CSpriteDataShell* _pSDS)
{
	CSpriteDataShell* pIronicShell = new CSpriteDataShell;

	pIronicShell->Initialise(_pSDS->GetSpriteID(), 1);
	pIronicShell->SetColor(_pSDS->GetAlpha(), _pSDS->GetRed(), _pSDS->GetGreen(), _pSDS->GetBlue());
	pIronicShell->SetRotate(_pSDS->GetRotate());
	pIronicShell->SetScaleX(_pSDS->GetScaleX());
	pIronicShell->SetScaleY(_pSDS->GetScaleY());
	pIronicShell->TranslateAbsolute(_pSDS->GetX(), _pSDS->GetY());
	//pIronicShell->m_iCurrentFrame = _pSDS->GetCurrentFrame();

	m_DrawList.push_back(pIronicShell);

	pIronicShell = 0;

}

int CSpriteManager::GetTotalFrames(ESpriteID _SpriteID)
{
	return(static_cast<int>(m_SpriteVec[static_cast<int>(_SpriteID)]->m_vectorFramesX.size()));
}

void CSpriteManager::SetDrawOffset(float _fX, float _fY)
{
	m_fDrawOffsetX = _fX;
	m_fDrawOffsetY = _fY;
}

void CSpriteManager::BeginBatch(ESpriteID _SpriteID)
{
	m_BatchSpriteID = _SpriteID;
	m_SpriteVec[_SpriteID]->m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	m_bBatchDrawing = true;

}
void CSpriteManager::EndBatch()
{
	m_SpriteVec[m_BatchSpriteID]->m_pSprite->End();
	m_bBatchDrawing = false;
}

unsigned int CSpriteManager::GetHeight(ESpriteID _SpriteID)
{
	return((unsigned int)m_SpriteVec[static_cast<int>(_SpriteID)]->GetFrameHeight());
}

unsigned int CSpriteManager::GetWidth(ESpriteID _SpriteID)
{
	//return(m_SpriteVec[static_cast<int>(_SpriteID)]->m_ImageInfo.Width);
	return((unsigned int)m_SpriteVec[static_cast<int>(_SpriteID)]->GetFrameWidth());
}


void CSpriteManager::OnLostDevice()
{
	for(unsigned int i = 0; i < m_SpriteVec.size(); ++i)
	{
		m_SpriteVec[i]->m_pSprite->OnLostDevice();
	}
}

void CSpriteManager::OnResetDevice()
{
	for(unsigned int i = 0; i < m_SpriteVec.size(); ++i)
	{
		m_SpriteVec[i]->m_pSprite->OnResetDevice();
	}

}





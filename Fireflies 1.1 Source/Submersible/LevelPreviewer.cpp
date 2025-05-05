// Library Includes
#include <assert.h>

// Local Includes
#include "INIParser.h"
#include "utils.h"

// This include
#include "LevelPreviewer.h"



// Constants

const float k_fPreviewPosX = 500;
const float k_fPreviewPosY = 400;

// Static Variables

// Static Function Prototypes

// Implementation

CLevelPreviewer::CLevelPreviewer()
{

}

CLevelPreviewer::~CLevelPreviewer()
{
	for(unsigned int i = 0; i < m_vecLanterns.size(); ++i)
	{
		delete m_vecLanterns[i];
		m_vecLanterns[i] = 0;
	}
}

void CLevelPreviewer::Initialise()
{
	m_Sprite.Initialise(SPRITE_LevelPreview, 1);
	m_Sprite.SetColor(255, 0, 50, 255);
	m_Sprite.TranslateAbsolute(k_fPreviewPosX, k_fPreviewPosY);
	m_TextBox.Initialise(255, k_fPreviewPosX, k_fPreviewPosY - 160, 5, true, true, 0);

	m_TextBox.SetString("");
}

void CLevelPreviewer::Load(std::string _strLevelName)
{
	for(unsigned int i = 0; i < m_vecLanterns.size(); ++i)
	{
		delete m_vecLanterns[i];
		m_vecLanterns[i] = 0;
	}
	m_vecLanterns.clear();

	CINIParser LevelParser;	
	bool bResult = LevelParser.LoadIniFile("Levels\\"+ _strLevelName +".ini");
	assert(("Specified Level Not Found.", bResult));

	int iLanternNum = 1;
	std::string strLanternNum = "Lantern" + IntToString(iLanternNum);

	
	float fX = 0;
	float fY = 0;
	int iPlayerID = 0;
	int iMaxLevel = 0;

	CSpriteDataShell* pNewSprite = 0;

	while(LevelParser.SafeCheck(strLanternNum, "PlayerID"))
	{
		LevelParser.GetFloatValue(strLanternNum, "x", fX);
		LevelParser.GetFloatValue(strLanternNum, "y", fY);
		LevelParser.GetIntValue(strLanternNum, "PlayerID", iPlayerID);
		LevelParser.GetIntValue(strLanternNum, "Max", iMaxLevel);

		iLanternNum++;
		strLanternNum = "Lantern" + IntToString(iLanternNum);

		pNewSprite = new CSpriteDataShell;
		pNewSprite->Initialise(SPRITE_Bubble, 1);

		switch(iMaxLevel)
		{
			case 1:
			{
				pNewSprite->Initialise(SPRITE_Base1, 0.25f);
			}
			break;
			case 2:
			{
				pNewSprite->Initialise(SPRITE_Base2, 0.25f);
			}
			break;
			case 3:
			{
				pNewSprite->Initialise(SPRITE_Base3, 0.25f);
			}
			break;
		}

		switch(iPlayerID)
		{
			case 0:
			{
				pNewSprite->SetColor(255, 255, 255, 255);
			}
			break;
			case 1:
			{
				pNewSprite->SetColor(255, 0, 0, 255);
			}
			break;
			case 2:
			{
				pNewSprite->SetColor(255, 255, 0, 0);
			}
			break;
			case 3:
			{
				pNewSprite->SetColor(255, 0, 255, 0);
			}
			break;
		}


		pNewSprite->TranslateAbsolute(fX, fY);

		m_vecLanterns.push_back(pNewSprite);
		pNewSprite = 0;
	}



	float fDefaultZoom;
	float fDefaultOffsetX;
	float fDefaultOffsetY;

	LevelParser.GetFloatValue("DefaultView", "zoom", fDefaultZoom);
	LevelParser.GetFloatValue("DefaultView", "X", fDefaultOffsetX);
	LevelParser.GetFloatValue("DefaultView", "Y", fDefaultOffsetY);

	fDefaultZoom *= 0.4f;
	float fScreenCentreX = 400;
	float fScreenCentreY = 300;

	for(unsigned int i = 0; i < m_vecLanterns.size(); ++i)
	{
		pNewSprite = m_vecLanterns[i];

		float fZoomOffsetX = (pNewSprite->GetX() - fScreenCentreX)*(fDefaultZoom-1);
		float fZoomOffsetY = (pNewSprite->GetY() - fScreenCentreY)*(fDefaultZoom-1);

		pNewSprite->TranslateAbsolute(pNewSprite->GetX()+fZoomOffsetX+(fDefaultOffsetX*fDefaultZoom), pNewSprite->GetY()+fZoomOffsetY+(fDefaultOffsetY*fDefaultZoom));
	
		pNewSprite->SetScaleX(fDefaultZoom*pNewSprite->GetScaleX());
		pNewSprite->SetScaleY(fDefaultZoom*pNewSprite->GetScaleY());

		pNewSprite->TranslateAbsolute(pNewSprite->GetX() - 400 + k_fPreviewPosX, pNewSprite->GetY() - 300 + k_fPreviewPosY);
	}

	m_TextBox.SetString(_strLevelName);




	//m_pSpriteManager->SetDrawOffset(fDefaultOffsetX, fDefaultOffsetY);
	//m_pSpriteManager->SetZoom(fDefaultZoom);
}

void CLevelPreviewer::Draw()
{
	m_Sprite.Draw();

	for(unsigned int i = 0; i < m_vecLanterns.size(); ++i)
	{
		m_vecLanterns[i]->Draw();
	}

	m_TextBox.Draw();
}

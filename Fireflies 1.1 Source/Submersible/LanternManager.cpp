// Library Includes

// Local Includes

// This include
#include "LanternManager.h"
#include "Lantern.h"
#include "INIParser.h"

// Constants


// Static Variables

// Static Function Prototypes

// Implementation

CLanternManager::CLanternManager()
{

}

CLanternManager::~CLanternManager()
{
	for(unsigned int i = 0; i < m_vecLanterns.size(); ++i)
	{
		delete m_vecLanterns[i];
		m_vecLanterns[i] = 0;
	}
}

void CLanternManager::Initialise(std::string _strLevelName)
{
	//AddLantern(600, 150, 2, PLAYER_1);
	//AddLantern(200, 400, 2, PLAYER_2);
	//AddLantern(400, 300, 0, PLAYER_N);

	//AddLantern(200, 100, 0, PLAYER_N);
	//AddLantern(400, 500, 0, PLAYER_N);
	//AddLantern(600, 400, 0, PLAYER_N);
	//AddLantern(100, 500, 0, PLAYER_N);

	//AddLantern(700, 500, 2, PLAYER_3);
	//AddLantern(400, 100, 0, PLAYER_N);


	if(_strLevelName == "")
	{

		float xshift = 400;
		float yshift = 300;

		float x = 220;
		float y = 0;

		for(unsigned int i = 0; i < 3; ++i)
		{
			AddLantern(xshift+x, yshift + y, 0, PLAYER_N);

			float newx = x*cosf((D3DX_PI*2)/3) - y*sinf((D3DX_PI*2)/3);
			float newy = x*sinf((D3DX_PI*2)/3) + y*cosf((D3DX_PI*2)/3);

			x = newx;
			y = newy;
		}

		EPlayerID ePlayerID = PLAYER_1;
		x = -220;
		y = 0;

		for(unsigned int i = 0; i < 3; ++i)
		{
			AddLantern(xshift+x, yshift + y, 2, ePlayerID);

			float newx = x*cosf((D3DX_PI*2)/3) - y*sinf((D3DX_PI*2)/3);
			float newy = x*sinf((D3DX_PI*2)/3) + y*cosf((D3DX_PI*2)/3);

			ePlayerID = (EPlayerID)((int)ePlayerID + 1);
			x = newx;
			y = newy;
		}


		//Pentagon
		//620, 300
		//510, 109
		//290, 109
		//180, 300
		//290, 490
		//510, 490

		//Dodecagon
		//
	}
	else
	{
		Load(_strLevelName);
	}

	for(unsigned int i = 0; i < m_vecLanterns.size(); ++i)
	{
		m_vecLanterns[i]->SpawnInitUnits();
	}

}

void CLanternManager::Process(float _fDeltaTick)
{
	for(unsigned int i = 0; i < m_vecLanterns.size(); ++i)
	{
		m_vecLanterns[i]->Process(_fDeltaTick);
	}
}

void CLanternManager::Draw()
{
	for(unsigned int i = 0; i < m_vecLanterns.size(); ++i)
	{
		m_vecLanterns[i]->Draw();
	}
}

void CLanternManager::DrawHealthBarSprites()
{
	for(unsigned int i = 0; i < m_vecLanterns.size(); ++i)
	{
		m_vecLanterns[i]->DrawHealthBarSprite();
	}
}

void CLanternManager::AddLantern(float _fX, float _fY, int _iLevel, EPlayerID _PlayerID)
{
	CLantern* newLantern = new CLantern;
	newLantern->Initialise(_PlayerID);
	newLantern->SetPosition(_fX, _fY);
	newLantern->SetLevel(_iLevel);
	m_vecLanterns.push_back(newLantern);
}
CLantern* CLanternManager::GetLantern(int _iIndex)
{
	return(m_vecLanterns[_iIndex]);

}
unsigned int CLanternManager::GetLanternTotal()
{
	return(m_vecLanterns.size());
}

void CLanternManager::Load(std::string _strLevelName)
{
	CINIParser LevelParser;
	bool bResult = LevelParser.LoadIniFile("Levels/" + _strLevelName + ".ini");

	assert(("Specified Level Not Found.", bResult));

	int iLanternNum = 1;
	std::string strLanternNum = "Lantern" + IntToString(iLanternNum);

	
	float fX = 0;
	float fY = 0;
	int iPlayerID = 0;
	int iLevel = 0;
	int iMaxLevel = 0;

	CLantern* pNewLantern = 0;

	while(LevelParser.SafeCheck(strLanternNum, "PlayerID"))
	{
		LevelParser.GetFloatValue(strLanternNum, "x", fX);
		LevelParser.GetFloatValue(strLanternNum, "y", fY);
		LevelParser.GetIntValue(strLanternNum, "PlayerID", iPlayerID);
		LevelParser.GetIntValue(strLanternNum, "Level", iLevel);
		LevelParser.GetIntValue(strLanternNum, "Max", iMaxLevel);

		iLanternNum++;
		strLanternNum = "Lantern" + IntToString(iLanternNum);

		pNewLantern = new CLantern;
		if(iPlayerID == 0)
		{
			pNewLantern->Initialise(PLAYER_N);
		}
		else
		{
			pNewLantern->Initialise(static_cast<EPlayerID>(iPlayerID-1));
		}
		pNewLantern->SetPosition(fX, fY);
		pNewLantern->SetMaxLevel(iMaxLevel);
		pNewLantern->SetLevel(iLevel);

		m_vecLanterns.push_back(pNewLantern);
		pNewLantern = 0;
	}

}

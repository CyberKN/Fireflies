// Library Includes

// Local Includes
#include "Lantern.h"
#include "Game.h"
#include "Menu.h"

// This include
#include "Editor.h"

// Constants

// Static Variables

// Static Function Prototypes

// Implementation

CEditor::CEditor()
:m_pSpriteManager(0)
,m_bPaused(false)
,m_pPauseMenu(0)
,m_pSelectedLantern(0)
,m_bShowHelp(true)
{

}

CEditor::~CEditor()
{
	for(unsigned int i = 0; i < m_vecLanterns.size(); ++i)
	{
		delete m_vecLanterns[i];
		m_vecLanterns[i] =  0;
	}

	if(m_pPauseMenu)
	{
		delete m_pPauseMenu;
		m_pPauseMenu = 0;
	}

	m_pSpriteManager->SetZoom(1);
	m_pSpriteManager->SetDrawOffset(0, 0);
}


void CEditor::Initialise(CSpriteManager* _pSpriteManager, std::string _strLevelName)
{
	m_pSpriteManager = _pSpriteManager;
	m_strLevelName = _strLevelName;

	ListFilesInDirectory("Levels");

	if(m_strLevelName == "")
	{
		//m_strLevelName = IntToString(RandInt(0, 9999) + (RandInt(0, 9999)*10000));
	}
	else
	{
		Load(m_strLevelName + ".ini");
	}

}


void CEditor::Process()
{

	if(CGame::GetInstance().m_Keyboard.WasKeyPressed(KEYID_ESC))
	{
		if(!(m_pPauseMenu && m_pPauseMenu->GetNameForm()))
		{
			m_bPaused = !m_bPaused;
		}
	}

	if(m_bPaused && !m_pPauseMenu)
	{
		m_pPauseMenu = new CMenu;
		m_pPauseMenu->Initialise(MENU_PAUSE_EDITOR);
		m_pPauseMenu->SetLevelName(m_strLevelName);
	}
	else if(!m_bPaused && m_pPauseMenu)
	{
		delete m_pPauseMenu;
		m_pPauseMenu = 0;
	}

	if(m_bPaused)
	{
		m_pPauseMenu->Process(0.016f);
	}
	else
	{
		//Adjust View/Zoom
		m_pSpriteManager->AdjustZoom(CGame::GetInstance().m_Mouse.GetMovement(MOUSEMOVE_Z) * m_pSpriteManager->GetZoom());

		if(m_pSpriteManager->GetZoom() < 0.01f)
		{
			m_pSpriteManager->SetZoom(0.01f);
		}

		if( CGame::GetInstance().m_Mouse.IsButtonDown(MOUSEBID_MIDDLE))
		{
			m_pSpriteManager->AdjustDrawOffsetX(CGame::GetInstance().m_Mouse.GetMovement(MOUSEMOVE_X)*(1/m_pSpriteManager->GetZoom()));
			m_pSpriteManager->AdjustDrawOffsetY(-CGame::GetInstance().m_Mouse.GetMovement(MOUSEMOVE_Y)*(1/m_pSpriteManager->GetZoom()));
		}


		//Update Cursor pos
		m_vCursorPos.x = (float)CGame::GetInstance().m_Mouse.GetPosition(MOUSEPOS_X);
		m_vCursorPos.y = (float)CGame::GetInstance().m_iWindowHeight - CGame::GetInstance().m_Mouse.GetPosition(MOUSEPOS_Y); - 7;

		float fScreenCentreX = 400;
		float fScreenCentreY = 300;

		float fZoom = (m_pSpriteManager->GetZoom());
		float fInvertZoom = 1/(m_pSpriteManager->GetZoom());

		float m_fZoomOffsetX = (m_vCursorPos.x - fScreenCentreX)*(fInvertZoom-1) - (m_pSpriteManager->GetDrawOffsetX());
		float m_fZoomOffsetY = (m_vCursorPos.y - fScreenCentreY)*(fInvertZoom-1) - (m_pSpriteManager->GetDrawOffsetY());

		m_vCursorPos.x = m_vCursorPos.x +m_fZoomOffsetX;
		m_vCursorPos.y = m_vCursorPos.y +m_fZoomOffsetY;

		if(m_pSelectedLantern)
		{
			m_pSelectedLantern->SetPosition(m_vCursorPos.x, m_vCursorPos.y);

			if(!CGame::GetInstance().m_Mouse.IsButtonDown(MOUSEBID_LEFT))
			{
				m_pSelectedLantern = 0;
			}
		}
		else
		{
			//find Nearest Lantern to Cursor
			CLantern* pNearestLantern = 0;
			CLantern* pLantern = 0;

			C2DBoundingBox tempbox;
			tempbox.UpdatePosition(m_vCursorPos.x, m_vCursorPos.y);
			tempbox.SetSize(20, 20);

			for(unsigned int i = 0; i < m_vecLanterns.size(); ++i)
			{
				pLantern = m_vecLanterns[i];
				pLantern->Update();

				pLantern->SetSelected(false);
				if((&tempbox)->CircleCollsionCheck(pLantern->GetBoundingBox()))
				{
					if(!pNearestLantern)
					{
						pNearestLantern = pLantern;
					}
					else
					{
						D3DXVECTOR2 vNearestDistance = m_vCursorPos - *(pNearestLantern->GetPosition());
						D3DXVECTOR2 vDistance = m_vCursorPos - *(pLantern->GetPosition());
						float fNearestDistance = D3DXVec2Length(&vNearestDistance);
						float fDistance = D3DXVec2Length(&vDistance);

						if(fNearestDistance < fDistance)
						{
							pNearestLantern = pLantern;
						}
					}
				}
			}

			if(pNearestLantern)
			{
				pNearestLantern->SetSelected(true);
			}

			ProcessInput(pNearestLantern);
		}
	}
}

void CEditor::ProcessInput(CLantern* _pLantern)
{
	if(CGame::GetInstance().m_Keyboard.WasKeyPressed(KEYID_F1))
	{
		m_bShowHelp = !m_bShowHelp;
	}
	

	if(CGame::GetInstance().m_Mouse.WasButtonPressed(MOUSEBID_LEFT))
	{
		if(_pLantern)
		{
			m_pSelectedLantern = _pLantern;
		}
		else
		{
			AddLantern(m_vCursorPos.x, m_vCursorPos.y);
		}
	}
	else if(CGame::GetInstance().m_Mouse.WasButtonPressed(MOUSEBID_RIGHT))
	{
		if(_pLantern)
		{
			m_pSelectedLantern = 0;
			RemoveLantern(_pLantern);
		
		}
	}
	else if(CGame::GetInstance().m_Keyboard.WasKeyPressed(KEYID_0))
	{
		if(_pLantern)
		{
			_pLantern->SetPlayerID(PLAYER_N);
			_pLantern->SetLevel(0);
			_pLantern->SetHealth(0);
			_pLantern->SetAligned(false);
		}
	}
	else if(CGame::GetInstance().m_Keyboard.WasKeyPressed(KEYID_1))
	{
		if(_pLantern)
		{
			if(_pLantern->GetPlayerID() == PLAYER_1)
			{
				IncreaseLanternDefaultLevel(_pLantern);
			}
			else
			{
				_pLantern->SetPlayerID(PLAYER_1);
				_pLantern->SetLevel(1);
				_pLantern->SetHealth(100);
				_pLantern->SetAligned(true);
			}
		}
	}
	else if(CGame::GetInstance().m_Keyboard.WasKeyPressed(KEYID_2))
	{
		if(_pLantern)
		{
			if(_pLantern->GetPlayerID() == PLAYER_2)
			{
				IncreaseLanternDefaultLevel(_pLantern);
			}
			else
			{
				_pLantern->SetPlayerID(PLAYER_2);
				_pLantern->SetLevel(1);
				_pLantern->SetHealth(100);
				_pLantern->SetAligned(true);
			}
		}
	}
	else if(CGame::GetInstance().m_Keyboard.WasKeyPressed(KEYID_3))
	{
		if(_pLantern)
		{
			if(_pLantern->GetPlayerID() == PLAYER_3)
			{
				IncreaseLanternDefaultLevel(_pLantern);
			}
			else
			{
				_pLantern->SetPlayerID(PLAYER_3);
				_pLantern->SetLevel(1);
				_pLantern->SetHealth(100);
				_pLantern->SetAligned(true);
			}
		}
	}
	else if(CGame::GetInstance().m_Mouse.WasButtonPressed(MOUSEBID_MIDDLE))
	{	
		if(_pLantern)
		{
			if(_pLantern->GetMaxLevel() == 3)
			{
				_pLantern->SetMaxLevel(1);
			}
			else
			{
				_pLantern->SetMaxLevel(_pLantern->GetMaxLevel()+1);
			}
		}
	
	}
}

void CEditor::Draw()
{
	for(unsigned int i = 0; i < m_vecLanterns.size(); ++i)
	{
		m_vecLanterns[i]->Draw();
	}

	if(m_bShowHelp)
	{
		CTextBox tBox;
		tBox.Initialise(1000, 10, 520, 3, true, false, 0);
		tBox.SetString("Controls:\n");
		tBox.SetString(tBox.GetString() + "F1 - Show/Hide Controls Help\n");
		tBox.SetString(tBox.GetString() + "Left Click - Add Base\n");
		tBox.SetString(tBox.GetString() + "Left Click & Drag - Move Base\n");
		tBox.SetString(tBox.GetString() + "Right Click - Remove Base\n");
		tBox.SetString(tBox.GetString() + "0, 1, 2, 3 - Set Base default player/Adjust Default base strength\n");
		tBox.SetString(tBox.GetString() + "Middle Mouse Click - Adjust Max Base Strength\n");
		tBox.SetString(tBox.GetString() + "Middle Mouse & Drag - Move View\n");
		tBox.SetString(tBox.GetString() + "Scroll wheel - Zoom View\n");
		tBox.SetString(tBox.GetString() + "Esc - Pause Menu\n");
		tBox.Draw();
	}

	if(m_pPauseMenu)
	{
		m_pPauseMenu->Draw();
	}

}


void CEditor::AddLantern(float _fX, float _fY)
{
	CLantern* newLantern = new CLantern;
	newLantern->Initialise(PLAYER_N);
	newLantern->SetPosition(_fX, _fY);
	newLantern->SetLevel(0);
	newLantern->SetMaxLevel(2);
	m_vecLanterns.push_back(newLantern);
}

void CEditor::RemoveLantern(CLantern* _pLantern)
{
	unsigned int iLanternID = 0;

	for(unsigned int i = 0; i < m_vecLanterns.size(); ++i)
	{
		if(m_vecLanterns[i] == _pLantern)
		{
			delete m_vecLanterns[i];
			m_vecLanterns[i] = 0;
			iLanternID = i;
			break;
		}
	}

	for(unsigned int i = iLanternID; i < m_vecLanterns.size()-1; ++i)
	{
		m_vecLanterns[i] = m_vecLanterns[i+1];
	}

	m_vecLanterns.pop_back();

}

bool CEditor::Load(std::string _strFile)
{
	CINIParser LevelParser;
	bool bResult = LevelParser.LoadIniFile("Levels/" + _strFile);

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

	float fDefaultZoom;
	float fDefaultOffsetX;
	float fDefaultOffsetY;

	LevelParser.GetFloatValue("DefaultView", "zoom", fDefaultZoom);
	LevelParser.GetFloatValue("DefaultView", "X", fDefaultOffsetX);
	LevelParser.GetFloatValue("DefaultView", "Y", fDefaultOffsetY);

	m_pSpriteManager->SetDrawOffset(fDefaultOffsetX, fDefaultOffsetY);
	m_pSpriteManager->SetZoom(fDefaultZoom);


	return(bResult);
}

bool CEditor::Save(std::string _strFile)
{
	CINIParser LevelParser;
	LevelParser.LoadIniFileEmpty(_strFile);

	int iLanternNum = 1;
	std::string strLanternNum = "Lantern" + IntToString(iLanternNum);

	
	std::string strX;
	std::string strY;
	std::string strPlayerID;
	std::string strLevel;
	std::string strMaxLevel;

	CLantern* pLantern = 0;

	for(unsigned int i = 0; i < m_vecLanterns.size(); ++i)
	{
		strLanternNum = "Lantern" + IntToString(i+1);
		pLantern = m_vecLanterns[i];


		if(pLantern->GetPlayerID() == PLAYER_N)
		{
			strPlayerID = "0";
		}
		else
		{
			strPlayerID = IntToString((int)pLantern->GetPlayerID()+1);
		}

		strX = FloatToString(pLantern->GetX());
		strY = FloatToString(pLantern->GetY());

		strMaxLevel = IntToString(pLantern->GetMaxLevel());
		strLevel = IntToString(pLantern->GetLevel());

		LevelParser.AddValue(strLanternNum, "x", strX);
		LevelParser.AddValue(strLanternNum, "y", strY);
		LevelParser.AddValue(strLanternNum, "PlayerID", strPlayerID);
		LevelParser.AddValue(strLanternNum, "Level", strLevel);
		LevelParser.AddValue(strLanternNum, "Max", strMaxLevel);
	}

	LevelParser.AddValue("DefaultView", "zoom", FloatToString(m_pSpriteManager->GetZoom()));
	LevelParser.AddValue("DefaultView", "X", FloatToString(m_pSpriteManager->GetDrawOffsetX()));
	LevelParser.AddValue("DefaultView", "Y", FloatToString(m_pSpriteManager->GetDrawOffsetY()));

	//LevelParser.LoadIniFile(_strFile);

	bool bResult = LevelParser.SaveIniFile();

	return(bResult);

}

void CEditor::ListFilesInDirectory(std::string directoryName)
{
	directoryName += "\\*";

    WIN32_FIND_DATA FindFileData;
	wchar_t FileName[260];
    string2wchar_t(directoryName, FileName);
    HANDLE hFind = FindFirstFile(FileName, &FindFileData);//.
	FindNextFile(hFind, &FindFileData);//..

    while (FindNextFile(hFind, &FindFileData))
	{
		std::string FileNameLessExt = wchar_t2string(FindFileData.cFileName);
		FileNameLessExt.pop_back();
		FileNameLessExt.pop_back();
		FileNameLessExt.pop_back();
		FileNameLessExt.pop_back();
        m_vecFileNames.push_back(FileNameLessExt);
	}

}

void CEditor::IncreaseLanternDefaultLevel(CLantern* _pLantern)
{
	if(_pLantern->GetLevel() == 3)
	{
		_pLantern->SetLevel(1);
	}
	else
	{
		_pLantern->SetLevel(_pLantern->GetLevel()+1);
		if(_pLantern->GetMaxLevel() < _pLantern->GetLevel())
		{
			_pLantern->SetMaxLevel(_pLantern->GetLevel());
		}
	}
}

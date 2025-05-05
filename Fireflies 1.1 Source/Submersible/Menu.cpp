// Library Includes

// Local Includes

// This include
#include "Menu.h"
#include "game.h"
#include "Button.h"
#include "NameForm.h"
#include "LevelPreviewer.h"

// Constants

// Static Variables

// Static Function Prototypes

// Implementation

CMenu::CMenu()
:m_pSelectedButton(0)
,m_pNameForm(0)
,m_pChecker(0)
,m_pPreviewer(0)
,m_pSubMenu(0)
,m_pParentMenu(0)
,m_bOpen(true)
,m_iListTop(1)
{
	m_strLevelName = "";
}

CMenu::~CMenu()
{

	m_pSelectedButton = 0;
	m_pParentMenu = 0;

	if(m_pSubMenu)
	{
		delete m_pSubMenu;
		m_pSubMenu = 0;
	}

	if(m_pNameForm)
	{
		delete m_pNameForm;
		m_pNameForm = 0;
	}

	if(m_pPreviewer)
	{
		delete m_pPreviewer;
	}

	if(m_pChecker)
	{
		delete m_pChecker;
		m_pChecker = 0;
	}
		

	for(unsigned int i = 0; i < m_vecButtons.size(); ++i)
	{
		delete m_vecButtons[i];
		m_vecButtons[i] = 0;
	}
}
void CMenu::Initialise(EMenuType _MenuType, CMenu* _pParentMenu)
{
	m_pParentMenu = _pParentMenu;
	m_eMenuType = _MenuType;

	m_BackgroundSprite.TranslateAbsolute(400, 300);
	m_BackgroundSprite.SetIgnoreOffset(true);
	m_BackgroundSprite.Initialise(SPRITE_Block4Sides, 50);
	m_BackgroundSprite.SetColor(100, 0, 0, 0);

	switch(_MenuType)
	{
		case MENU_MAIN:
		{
			
			m_BackgroundSprite.Initialise(SPRITE_BG, 2.4f);
			m_BackgroundSprite.SetColor(100, 0, 255, 0);

			m_vecBackgroundSprites.resize(1);
			m_vecBackgroundSprites[0].Initialise(SPRITE_Logo, 1);
			m_vecBackgroundSprites[0].TranslateAbsolute(500, 350);


			CButton* pbutton = new CButton;
			pbutton->Initialise(MENUBUTTON_LEVEL_SELECT, 100, 500, this);
			pbutton->SetData("NEW GAME");
			m_vecButtons.push_back(pbutton);

			pbutton = new CButton;
			pbutton->Initialise(MENUBUTTON_LEVEL_EDITOR, 100, 400, this);
			pbutton->SetData("EDITOR");
			m_vecButtons.push_back(pbutton);

			pbutton = new CButton;
			pbutton->Initialise(MENUBUTTON_TUTORIAL, 100, 300, this);
			pbutton->SetData("TUTORIAL");
			m_vecButtons.push_back(pbutton);

			pbutton = new CButton;
			pbutton->Initialise(MENUBUTTON_CREDITS, 100, 200, this);
			pbutton->SetData("CREDITS");
			m_vecButtons.push_back(pbutton);

			pbutton = new CButton;
			pbutton->Initialise(MENUBUTTON_EXIT, 100, 100, this);
			pbutton->SetData("EXIT");
			m_vecButtons.push_back(pbutton);
		}
		break;
		case MENU_LEVEL:
		{
			m_BackgroundSprite.Initialise(SPRITE_BG, 2.4f);
			m_BackgroundSprite.SetColor(100, 0, 255, 0);

			GenerateLevelList("Levels");

			CButton* pbutton = new CButton;
			pbutton->Initialise(MENUBUTTON_START, 400, 100, this);
			pbutton->SetData("START");
			m_vecButtons.push_back(pbutton);

			pbutton = new CButton;
			pbutton->Initialise(MENUBUTTON_BACK, 600, 100, this);
			pbutton->SetData("BACK");
			m_vecButtons.push_back(pbutton);

			pbutton = new CButton;
			pbutton->Initialise(MENUBUTTON_CYCLEUP, 100, 550, this);
			pbutton->SetData("^");
			pbutton->SetDrawData(true);
			m_vecButtons.push_back(pbutton);

			pbutton = new CButton;
			pbutton->Initialise(MENUBUTTON_CYCLEDOWN, 100, 50, this);
			pbutton->SetData("V");
			pbutton->SetDrawData(true);
			m_vecButtons.push_back(pbutton);

			CycleLevelsUp();

			m_pPreviewer = new CLevelPreviewer;
			m_pPreviewer->Initialise();
		}
		break;
		case MENU_LEVEL_EDITOR:
		{

			m_BackgroundSprite.Initialise(SPRITE_BG, 2.4f);
			m_BackgroundSprite.SetColor(100, 255, 255, 255);

			GenerateLevelList("Levels");

			CButton* pbutton = new CButton;
			pbutton->Initialise(MENUBUTTON_START, 400, 100, this);
			pbutton->SetData("START");
			m_vecButtons.push_back(pbutton);

			pbutton = new CButton;
			pbutton->Initialise(MENUBUTTON_BACK, 600, 100, this);
			pbutton->SetData("BACK");
			m_vecButtons.push_back(pbutton);

			pbutton = new CButton;
			pbutton->Initialise(MENUBUTTON_CYCLEUP, 100, 550, this);
			pbutton->SetData("^");
			pbutton->SetDrawData(true);
			m_vecButtons.push_back(pbutton);

			pbutton = new CButton;
			pbutton->Initialise(MENUBUTTON_CYCLEDOWN, 100, 50, this);
			pbutton->SetData("V");
			pbutton->SetDrawData(true);
			m_vecButtons.push_back(pbutton);

			CycleLevelsUp();
			

			m_pPreviewer = new CLevelPreviewer;
			m_pPreviewer->Initialise();
		}
		break;
		case MENU_PAUSE:
		{

			CButton* pbutton = new CButton;
			pbutton->Initialise(MENUBUTTON_RESUME, 100, 500, this);
			pbutton->SetData("RESUME");
			m_vecButtons.push_back(pbutton);

			pbutton = new CButton;
			pbutton->Initialise(MENUBUTTON_QUIT, 100, 400, this);
			pbutton->SetData("QUIT");
			m_vecButtons.push_back(pbutton);

			pbutton = new CButton;
			pbutton->Initialise(MENUBUTTON_EXIT, 100, 300, this);
			pbutton->SetData("EXIT");
			m_vecButtons.push_back(pbutton);
		}
		break;
		case MENU_PAUSE_EDITOR:
		{

			CButton* pbutton = new CButton;
			pbutton->Initialise(MENUBUTTON_RESUME, 100, 500, this);
			pbutton->SetData("RESUME");
			m_vecButtons.push_back(pbutton);

			pbutton = new CButton;
			pbutton->Initialise(MENUBUTTON_SAVE, 100, 400, this);
			pbutton->SetData("SAVE");
			m_vecButtons.push_back(pbutton);

			pbutton = new CButton;
			pbutton->Initialise(MENUBUTTON_QUIT, 100, 300, this);
			pbutton->SetData("QUIT");
			m_vecButtons.push_back(pbutton);

			pbutton = new CButton;
			pbutton->Initialise(MENUBUTTON_EXIT, 100, 200, this);
			pbutton->SetData("EXIT");
			m_vecButtons.push_back(pbutton);
		}
		break;
		case MENU_CREDITS:
		{
			
			m_BackgroundSprite.Initialise(SPRITE_BG, 2.4f);
			m_BackgroundSprite.SetColor(100, 255, 255, 255);

			CButton* pbutton = new CButton;
			pbutton->Initialise(MENUBUTTON_BACK, 600, 100, this);
			pbutton->SetData("BACK");
			m_vecButtons.push_back(pbutton);

			m_vecBackgroundSprites.resize(1);

			m_vecBackgroundSprites[0].Initialise(SPRITE_Credits, 1);
			m_vecBackgroundSprites[0].TranslateAbsolute(350, 350);
		}
		break;
	}

}

void CMenu::Process(float _fDeltaTick)
{
	if(!m_pSubMenu)
	{
		ProcessMenuSpecificVisualElements(_fDeltaTick);

		if(m_pChecker)
		{
			if(m_pChecker->IsOpen())
			{
				m_pChecker->Process();
			}
			else
			{
				delete m_pChecker;
				m_pChecker = 0;
			}
		}
		else if(m_pNameForm)
		{
			m_pNameForm->Process(_fDeltaTick);
		}
		else
		{

			for(unsigned int i = 0; i < m_vecButtons.size(); ++i)
			{
				m_vecButtons[i]->Process(_fDeltaTick);
			}

			if(!m_pSelectedButton)
			{

				ProcessScrolling();

				if(CGame::GetInstance().m_Mouse.WasButtonPressed(MOUSEBID_LEFT))
				{
					for(unsigned int i = 0; i < m_vecButtons.size(); ++i)
					{
						if(m_vecButtons[i]->GetBoundingBox()->PointCollsionCheck((float)CGame::GetInstance().m_Mouse.GetX(), CGame::GetInstance().m_iWindowHeight - (float)CGame::GetInstance().m_Mouse.GetY()))
						{
							m_pSelectedButton = m_vecButtons[i];
							m_pSelectedButton->SetState(BSTATE_DOWN);
						}
					}
				}
				else
				{
					for(unsigned int i = 0; i < m_vecButtons.size(); ++i)
					{
						m_vecButtons[i]->SetState(BSTATE_UP);
						if(m_vecButtons[i]->GetBoundingBox()->PointCollsionCheck((float)CGame::GetInstance().m_Mouse.GetX(), CGame::GetInstance().m_iWindowHeight - (float)CGame::GetInstance().m_Mouse.GetY()))
						{
							m_vecButtons[i]->SetState(BSTATE_OVER);
						}
					}

				}
			}
			else
			{
				if(m_pSelectedButton->GetBoundingBox()->PointCollsionCheck((float)CGame::GetInstance().m_Mouse.GetX(), CGame::GetInstance().m_iWindowHeight - (float)CGame::GetInstance().m_Mouse.GetY()))
				{
					m_pSelectedButton->SetState(BSTATE_DOWN);
					if(CGame::GetInstance().m_Mouse.WasButtonReleased(MOUSEBID_LEFT))
					{
						m_pSelectedButton->Activate();
						m_pSelectedButton = 0;
					}
				}
				else
				{
					m_pSelectedButton->SetState(BSTATE_UP);
					if(CGame::GetInstance().m_Mouse.WasButtonReleased(MOUSEBID_LEFT))
					{
						m_pSelectedButton = 0;
					}
				}
			}
		}
	}
	else
	{
		if(!m_pSubMenu->IsOpen())
		{
			CloseSubMenu();
			Process(_fDeltaTick);
		}
		else
		{
			m_pSubMenu->Process(_fDeltaTick);
		}
	}
}

void CMenu::Draw()
{
	if(m_pSubMenu)
	{
		m_pSubMenu->Draw();
	}
	else
	{
		m_BackgroundSprite.Draw();
		
		for(unsigned int i = 0; i < m_vecBackgroundSprites.size(); ++i)
		{
			m_vecBackgroundSprites[i].Draw();
		}


		for(unsigned int i = 0; i < m_vecButtons.size(); ++i)
		{
			m_vecButtons[i]->Draw();
		}

		if(m_pPreviewer)
		{
			m_pPreviewer->Draw();
		}

		if(m_pNameForm)
		{
			m_pNameForm->Draw();
		}

		if(m_pChecker)
		{
			m_pChecker->Draw();
		}

	}
}

void CMenu::OpenSubMenu(EMenuType _MenuType)
{
	m_pSubMenu = new CMenu;
	m_pSubMenu->Initialise(_MenuType, this);
}


void CMenu::CloseSubMenu()
{
	delete m_pSubMenu;
	m_pSubMenu = 0;
}

void CMenu::GenerateLevelList(std::string directoryName)
{
	std::vector<std::string> vecFileNames;

	ListFilesInDirectory(directoryName, vecFileNames);

	for(unsigned int i = 0; i < vecFileNames.size(); ++i)
	{
		CButton* pButton = new CButton;
		pButton->Initialise(MENUBUTTON_LEVEL_PREVIEW, 100, 2000, this);
		pButton->SetData(vecFileNames[i]);
		pButton->SetDrawData(true);
		m_vecLevelButtons.push_back(pButton);
		m_vecButtons.push_back(pButton);
		pButton = 0;
	}
}

void CMenu::ListFilesInDirectory(std::string directoryName, std::vector<std::string>& _vecFileNames)
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
		if(FileNameLessExt[FileNameLessExt.length()-4] == '.')
		{
			FileNameLessExt.pop_back();
			FileNameLessExt.pop_back();
			FileNameLessExt.pop_back();
			FileNameLessExt.pop_back();
			_vecFileNames.push_back(FileNameLessExt);
		}
	}

}

void CMenu::PreviewLevel(std::string _strLevelName)
{
	SetLevelName(_strLevelName);

	for(unsigned int i = 0; i < m_vecButtons.size();++i)
	{
		m_vecButtons[i]->SetHighlighted(false);
	}

	m_pPreviewer->Load(_strLevelName);
}

void CMenu::CloseNameForm(bool _bSave)
{
	if(_bSave)
	{
		m_strLevelName = m_pNameForm->GetString();
		CGame::GetInstance().GetEditor()->Save("Levels\\"+m_strLevelName+".ini");
		delete m_pNameForm;
		m_pNameForm = 0;
	}
	else
	{
		delete m_pNameForm;
		m_pNameForm = 0;
	}
}


void CMenu::OpenNameForm()
{
	m_pNameForm = new CNameForm;
	m_pNameForm->Initialise(m_strLevelName, this);
}

bool CMenu::CycleLevelsUp()
{
	if(m_iListTop == 0)
	{
		return(false);
	}

	--m_iListTop;

	for(unsigned int i = 0; i < m_vecLevelButtons.size(); ++i)
	{
		m_vecLevelButtons[i]->SetPosition(100, 2000);
	}

	for(unsigned int i = m_iListTop; i < m_vecLevelButtons.size() && i < m_iListTop + 5; ++i)
	{
		m_vecLevelButtons[i]->SetPosition(100, static_cast<float>(460 - (80*(i-m_iListTop))));
	}

	if(m_iListTop == 0)
	{
		return(false);
	}

	return(true);
}

bool CMenu::CycleLevelsDown()
{
	++m_iListTop;
	if(m_iListTop > m_vecLevelButtons.size() - 5)
	{
		--m_iListTop;
		return(false);
	}

	for(unsigned int i = 0; i < m_vecLevelButtons.size(); ++i)
	{
		m_vecLevelButtons[i]->SetPosition(100, 2000);
	}

	for(unsigned int i = m_iListTop; i < m_vecLevelButtons.size() && i < m_iListTop + 5; ++i)
	{
		m_vecLevelButtons[i]->SetPosition(100, static_cast<float>(460 - (80*(i-m_iListTop))));
	}

	if((m_iListTop + 1) > m_vecLevelButtons.size() + 5)
	{
		return(false);
	}

	return(true);
}


void CMenu::OpenChoiceChecker(ECheckerType _eCheckerType)
{
	m_pChecker = new CChoiceChecker;
	m_pChecker->Initialise(_eCheckerType, this);
}


void CMenu::ProcessScrolling()
{
	//Check for scrolling the
	float fScroll = CGame::GetInstance().m_Mouse.GetMovement(MOUSEMOVE_Z);

	if(fabs(fScroll) > 0)
	{
		for(unsigned int i = 0; i < m_vecButtons.size(); ++i)
		{
			if(m_vecButtons[i]->GetBoundingBox()->PointCollsionCheck((float)CGame::GetInstance().m_Mouse.GetX(), CGame::GetInstance().m_iWindowHeight - (float)CGame::GetInstance().m_Mouse.GetY()))
			{
				if(m_vecButtons[i]->m_eType == MENUBUTTON_LEVEL_PREVIEW)
				{
					if(fScroll < 0)
					{
						CycleLevelsDown();
					}
					else
					{
						CycleLevelsUp();
					}
					break;
				}
			}
		}
	}	

}

void CMenu::ProcessMenuSpecificVisualElements(float _fDeltaTick)
{
	switch(m_eMenuType)
	{
	case MENU_MAIN:
	case MENU_LEVEL_EDITOR:
	case MENU_CREDITS:
	case MENU_LEVEL:
		{
			if(m_BackgroundSprite.GetRotate() == 0)
			{
				if(m_BackgroundSprite.GetGreen() == 0)
				{
					m_BackgroundSprite.SetColor(100, 0, 0, m_BackgroundSprite.GetBlue()+1);
				}
				else
				{
					m_BackgroundSprite.SetColor(100, 0, m_BackgroundSprite.GetGreen()-1, 0);
				}

				if(m_BackgroundSprite.GetBlue() == 255)
				{
					m_BackgroundSprite.SetRotate(2*D3DX_PI);
				}
			}
			else if(m_BackgroundSprite.GetRotate() == 2*D3DX_PI)
			{
				if(m_BackgroundSprite.GetBlue() == 0)
				{
					m_BackgroundSprite.SetColor(100, m_BackgroundSprite.GetRed()+1, 0, 0);
				}
				else
				{
					m_BackgroundSprite.SetColor(100, 0, 0, m_BackgroundSprite.GetBlue()-1);
				}

				if(m_BackgroundSprite.GetRed() == 255)
				{
					m_BackgroundSprite.SetRotate(4*D3DX_PI);
				}
			}
			else if(m_BackgroundSprite.GetRotate() == 4*D3DX_PI)
			{
				if(m_BackgroundSprite.GetRed() == 0)
				{
					m_BackgroundSprite.SetColor(100, 0, m_BackgroundSprite.GetGreen()+1, 0);
				}
				else
				{
					m_BackgroundSprite.SetColor(100, m_BackgroundSprite.GetRed()-1, 0, 0);
				}

				if(m_BackgroundSprite.GetGreen() == 255)
				{
					m_BackgroundSprite.SetRotate(0);
				}
			}

			/*
			if(m_BackgroundSprite.GetRed() == 255 && m_BackgroundSprite.GetBlue() != 0)
			{
				m_BackgroundSprite.SetColor(100, 255, 0, m_BackgroundSprite.GetBlue()-3);
			}
			else if(m_BackgroundSprite.GetBlue() == 0 && m_BackgroundSprite.GetGreen() != 255)
			{
				m_BackgroundSprite.SetColor(100, 255, m_BackgroundSprite.GetGreen()+3, 0);
			}
			else if(m_BackgroundSprite.GetGreen() == 255 && m_BackgroundSprite.GetRed() != 0)
			{
				m_BackgroundSprite.SetColor(100, m_BackgroundSprite.GetRed()-3, 255, 0);
			}
			else if(m_BackgroundSprite.GetRed() == 0 && m_BackgroundSprite.GetBlue() != 255)
			{
				m_BackgroundSprite.SetColor(100, 0, 255, m_BackgroundSprite.GetBlue()+3);
			}
			else if(m_BackgroundSprite.GetBlue() == 255 && m_BackgroundSprite.GetGreen() != 0)
			{
				m_BackgroundSprite.SetColor(100, 0, m_BackgroundSprite.GetGreen()-3, 255);
			}
			else if(m_BackgroundSprite.GetGreen() == 0 && m_BackgroundSprite.GetRed() != 255)
			{
				m_BackgroundSprite.SetColor(100, m_BackgroundSprite.GetRed()+3, 0, 255);
			}*/
		}
		break;
	}

}


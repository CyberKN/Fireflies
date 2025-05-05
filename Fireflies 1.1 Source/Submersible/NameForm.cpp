// Library Includes

// Local Includes

// This include
#include "NameForm.h"
#include "DInputKeyboard.h"
#include "Game.h"
#include "Menu.h"
#include "ChoiceChecker.h"

// Constants

// Static Variables

// Static Function Prototypes

// Implementation

CNameForm::CNameForm()
:m_bCursorVisible(true)
,m_fCursorTimer(0)
,m_pOverwriteChecker(0)
{
	m_strFileName = "";
}

CNameForm::~CNameForm()
{
	if(m_pOverwriteChecker)
	{
		delete m_pOverwriteChecker;
		m_pOverwriteChecker = 0;
	}

	m_pParentMenu = 0;
}
void CNameForm::Initialise(std::string _strDefaultName, CMenu* _pParentMenu)
{
	m_pParentMenu = _pParentMenu;
	m_strFileName = _strDefaultName;
	m_BGSprite.Initialise(SPRITE_NameForm, 1);
	m_BGSprite.TranslateAbsolute(400, 300);
	m_BGSprite.SetIgnoreOffset(true);
	m_TextBox.Initialise(17, m_BGSprite.GetX()-78, m_BGSprite.GetY()+15, 4, true, false, 0);

}
void CNameForm::Process(float _fDeltaTick)
{
	if(m_pOverwriteChecker)
	{
		if(!m_pOverwriteChecker->IsOpen())
		{
			delete m_pOverwriteChecker;
			m_pOverwriteChecker = 0;
		}
		else
		{
			m_pOverwriteChecker->Process();
		}
	}
	else
	{
		m_fCursorTimer += _fDeltaTick;

		if(m_fCursorTimer > 0.7f)
		{
			m_bCursorVisible = !m_bCursorVisible;
			m_fCursorTimer = 0;
		}

		for(unsigned int i = 0; i < 26; ++i)
		{
			if(CGame::GetInstance().m_Keyboard.WasKeyPressed(static_cast<EKeyID>(i)))
			{
				if(CGame::GetInstance().m_Keyboard.IsKeyDown(KEYID_LSHIFT) ||CGame::GetInstance().m_Keyboard.IsKeyDown(KEYID_RSHIFT))
				{
					m_strFileName += static_cast<char>(i+65);
				}
				else
				{
					m_strFileName += static_cast<char>(i+97);
				}
			}
		}

		for(unsigned int i = 26; i < 36; ++i)
		{
			if(CGame::GetInstance().m_Keyboard.WasKeyPressed(static_cast<EKeyID>(i)))
			{
				m_strFileName += static_cast<char>(i-26+48);
			}
		}

		if(CGame::GetInstance().m_Keyboard.WasKeyPressed(KEYID_SPACE))
		{
			m_strFileName += " ";
		}

		while(m_strFileName.length() > 16)
		{
			m_strFileName.pop_back();
		}

		if(CGame::GetInstance().m_Keyboard.WasKeyPressed(KEYID_BACK))
		{
			if(m_strFileName.length() > 0)
			{
				m_strFileName.pop_back();
			}
		}

		if(CGame::GetInstance().m_Keyboard.WasKeyPressed(KEYID_ENTER) && m_strFileName != "")
		{
			GetListOfFiles();
			for(unsigned int i = 0; i < m_vecFileNames.size(); ++i)
			{
				if(m_strFileName == m_vecFileNames[i])
				{
					m_pOverwriteChecker = new CChoiceChecker;
					m_pOverwriteChecker->Initialise(CHECKER_Overwrite, m_pParentMenu);
					break;
				}
			}
			

			if(!m_pOverwriteChecker)
			{
				m_pParentMenu->CloseNameForm(true);
			}
		}

		if(CGame::GetInstance().m_Keyboard.WasKeyPressed(KEYID_ESC))
		{
			m_pParentMenu->CloseNameForm(false);
			CGame::GetInstance().m_Keyboard.UpdateKeyMidFrame(KEYID_ESC);
		}
	}




}
void CNameForm::Draw()
{
	m_BGSprite.Draw();

	m_TextBox.SetString(m_strFileName);
	if(m_bCursorVisible)
	{
		m_TextBox.SetString(m_TextBox.GetString() += "|");
	}		
	m_TextBox.Draw();

	if(m_pOverwriteChecker)
	{
		m_pOverwriteChecker->Draw();
	}


	
}

void CNameForm::GetListOfFiles()
{
	m_vecFileNames.clear();
	std::string strDirectoryName = "Levels\\*";

    WIN32_FIND_DATA FindFileData;
	wchar_t FileName[260];
    string2wchar_t(strDirectoryName, FileName);
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


void CNameForm::CancelOverwrite()
{
	m_pParentMenu->CloseSubMenu();
	//delete m_pOverwriteMenu;
	//m_pOverwriteMenu = 0;
}

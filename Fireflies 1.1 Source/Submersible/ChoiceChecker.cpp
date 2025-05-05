// Library Includes

// Local Includes
#include "Game.h"
#include "Menu.h"
#include "NameForm.h"
// This include
#include "ChoiceChecker.h"

// Constants

// Static Variables

// Static Function Prototypes

// Implementation

CChoiceChecker::CChoiceChecker()
{
	m_pParentMenu = 0;
	m_pSelectedButton = 0;
	m_bOpen = true;
}

CChoiceChecker::~CChoiceChecker()
{
	m_pSelectedButton = 0;
	m_pParentMenu = 0;
}


void CChoiceChecker::Initialise(ECheckerType _eCheckerType, CMenu* _pParentMenu)
{
	m_pParentMenu = _pParentMenu;
	m_eCheckerType = _eCheckerType;

	switch(m_eCheckerType)
	{
	case CHECKER_Overwrite:
		{
			m_Sprite.Initialise(SPRITE_CC_OverWrite, 1);
		}
		break;
	case CHECKER_Quit:
		{
			m_Sprite.Initialise(SPRITE_CC_Quit, 1);
		}
		break;
	case CHECKER_Exit:
		{
			m_Sprite.Initialise(SPRITE_CC_Exit, 1);
		}
	}

	m_Sprite.TranslateAbsolute(400, 300);
	m_Sprite.SetIgnoreOffset(true);

	m_ConfirmButton.Initialise(SPRITE_Button_Yes, 1);
	m_ConfirmButton.TranslateAbsolute(360, 260);
	m_ConfirmButton.SetIgnoreOffset(true);

	m_CancelButton.Initialise(SPRITE_Button_No, 1);
	m_CancelButton.TranslateAbsolute(440, 260);
	m_CancelButton.SetIgnoreOffset(true);

}

void CChoiceChecker::Process()
{
	m_ConfirmButton.SetColor(255, 0, 50, 255);
	m_CancelButton.SetColor(255, 0, 50, 255);

	C2DBoundingBox ButtonBox;
	ButtonBox.SetSize(m_CancelButton.GetWidth(), m_CancelButton.GetHeight());

	
	if(CGame::GetInstance().m_Mouse.WasButtonPressed(MOUSEBID_LEFT))
	{
		ButtonBox.UpdatePosition(m_CancelButton.GetX(), m_CancelButton.GetY());
		if(ButtonBox.PointCollsionCheck((float)CGame::GetInstance().m_Mouse.GetX(), CGame::GetInstance().m_iWindowHeight - (float)CGame::GetInstance().m_Mouse.GetY()))
		{
			m_pSelectedButton = &m_CancelButton;
		}

		ButtonBox.UpdatePosition(m_ConfirmButton.GetX(), m_ConfirmButton.GetY());

		if(ButtonBox.PointCollsionCheck((float)CGame::GetInstance().m_Mouse.GetX(), CGame::GetInstance().m_iWindowHeight - (float)CGame::GetInstance().m_Mouse.GetY()))
		{
			m_pSelectedButton = &m_ConfirmButton;
		}
	}
	else if(!m_pSelectedButton)
	{
		ButtonBox.UpdatePosition(m_CancelButton.GetX(), m_CancelButton.GetY());
		if(ButtonBox.PointCollsionCheck((float)CGame::GetInstance().m_Mouse.GetX(), CGame::GetInstance().m_iWindowHeight - (float)CGame::GetInstance().m_Mouse.GetY()))
		{
			m_CancelButton.SetColor(255, 255, 255, 255);
		}

		ButtonBox.UpdatePosition(m_ConfirmButton.GetX(), m_ConfirmButton.GetY());

		if(ButtonBox.PointCollsionCheck((float)CGame::GetInstance().m_Mouse.GetX(), CGame::GetInstance().m_iWindowHeight - (float)CGame::GetInstance().m_Mouse.GetY()))
		{
			m_ConfirmButton.SetColor(255, 255, 255, 255);
		}
	}

	if(m_pSelectedButton)
	{
		ButtonBox.UpdatePosition(m_pSelectedButton->GetX(), m_pSelectedButton->GetY());
		if(CGame::GetInstance().m_Mouse.WasButtonReleased(MOUSEBID_LEFT))
		{
			if(ButtonBox.PointCollsionCheck((float)CGame::GetInstance().m_Mouse.GetX(), CGame::GetInstance().m_iWindowHeight - (float)CGame::GetInstance().m_Mouse.GetY()))
			{
				m_bOpen = false;
				if(m_pSelectedButton == &m_ConfirmButton)
				{
					Confirm();
				}
			}
			else
			{
				m_pSelectedButton = 0;
			}
		}
		else
		{
			if(ButtonBox.PointCollsionCheck((float)CGame::GetInstance().m_Mouse.GetX(), CGame::GetInstance().m_iWindowHeight - (float)CGame::GetInstance().m_Mouse.GetY()))
			{
				m_pSelectedButton->SetColor(255, 255, 0, 0);
			}
			else
			{
				m_pSelectedButton->SetColor(255, 0, 100, 255);
			}
		}
	}
}

void CChoiceChecker::Draw()
{
	m_Sprite.Draw();
	m_CancelButton.Draw();
	m_ConfirmButton.Draw();
	//CTextBox tBox;
	//tBox.Initialise(16, m_ConfirmButton.GetX(), m_ConfirmButton.GetY(), 4, true, true, 0);
	//tBox.SetString("Confirm");
	//tBox.Draw();
	//
	//tBox.Initialise(16, m_CancelButton.GetX(), m_CancelButton.GetY(), 4, true, true, 0);
	//tBox.SetString("Cancel");
	//tBox.Draw();

}


void CChoiceChecker::Confirm()
{
	switch(m_eCheckerType)
	{
		case CHECKER_Overwrite:
		{
			m_pParentMenu->CloseNameForm(true);

		}
		break;
		case CHECKER_Exit:
		{
			PostQuitMessage(0);
		}
		break;
		case CHECKER_Quit:
		{
			CGame::GetInstance().SetNewState(GAMESTATE_MENU);
		}
		break;
	}


}

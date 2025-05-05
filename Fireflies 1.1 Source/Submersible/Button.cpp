// Library Includes

// Local Includes

// This include
#include "Button.h"
#include "Game.h"
#include "Menu.h"
#include "NameForm.h"

// Constants

// Static Variables

// Static Function Prototypes

// Implementation

CButton::CButton()
:m_bDrawData(false)
,m_bHighlighted(false)
{

}

CButton::~CButton()
{
	m_pParentMenu = 0;
}

void CButton::Initialise(EMenuItemType _eMenuItemType, float _fX, float _fY, CMenu* _pParentMenu)
{
	m_pParentMenu = _pParentMenu;

	switch(_eMenuItemType)
	{
		case MENUBUTTON_LEVEL_SELECT:
		{
			m_Sprite.Initialise(SPRITE_Button_New, 1);
		}
		break;
		case MENUBUTTON_LEVEL_EDITOR:
		{
			m_Sprite.Initialise(SPRITE_Button_Editor, 1);
		}
		break;
		case MENUBUTTON_QUIT:
		{
			m_Sprite.Initialise(SPRITE_Button_Quit, 1);
		}
		break;
		case MENUBUTTON_START:
		{
			m_Sprite.Initialise(SPRITE_Button_Start, 1);
		}
		break;
		case MENUBUTTON_EXIT:
		{
			m_Sprite.Initialise(SPRITE_Button_Exit, 1);
		}
		break;
		case MENUBUTTON_SAVE:
		{
			m_Sprite.Initialise(SPRITE_Button_Save, 1);
		}
		break;
		case MENUBUTTON_RESUME:
		{
			m_Sprite.Initialise(SPRITE_Button_Resume, 1);
		}
		break;
		case MENUBUTTON_BACK:
		{
			m_Sprite.Initialise(SPRITE_Button_Back, 1);
		}
		break;
		case MENUBUTTON_TUTORIAL:
		{
			m_Sprite.Initialise(SPRITE_Button_Tutorial, 1);
		}
		break;
		case MENUBUTTON_CREDITS:
		{
			m_Sprite.Initialise(SPRITE_Button_Credits, 1);
		}
		break;
		case MENUBUTTON_CYCLEUP:
		{
			m_Sprite.Initialise(SPRITE_Button_Up, 1);
		}
		break;
		case MENUBUTTON_CYCLEDOWN:
		{
			m_Sprite.Initialise(SPRITE_Button_Down, 1);
		}
		break;
		default:
		{
			m_Sprite.Initialise(SPRITE_Button_Blank, 1);
		}
	}

	
	m_PosVec.x = _fX;
	m_PosVec.y = _fY;
	m_Sprite.TranslateAbsolute(_fX, _fY);
	m_Sprite.SetIgnoreOffset(true);
	m_BoundingBox.SetSize(m_Sprite.GetWidth(), m_Sprite.GetHeight());
	m_BoundingBox.UpdatePosition(_fX, _fY);
	m_eType = _eMenuItemType;
	m_fRotation = 0;

	m_OverSprite.Initialise(SPRITE_LightRays, 0.5f);
	m_OverSprite.SetIgnoreOffset(true);
	m_OverSprite.TranslateAbsolute(_fX, _fY);
	m_OverSprite.SetColor(255, 255, 255, 255);
}

void CButton::Process(float _fDeltaTick)
{
	m_Sprite.TranslateAbsolute(m_PosVec.x, m_PosVec.y);
	m_OverSprite.TranslateAbsolute(m_PosVec.x, m_PosVec.y);
	if(m_eButtonState != BSTATE_UP)
	{
		m_OverSprite.SetScaleX(m_OverSprite.GetScaleX() + _fDeltaTick*3);
		m_OverSprite.SetScaleY(m_OverSprite.GetScaleY() + _fDeltaTick*3);
		if(m_OverSprite.GetScaleX() > 0.8f)
		{
			m_OverSprite.SetScaleX(0.8f);
			m_OverSprite.SetScaleY(0.8f);
		}
	}
	else
	{
		if(m_OverSprite.GetScaleX() > 0.5f)
		{
			m_OverSprite.SetScaleX(m_OverSprite.GetScaleX() - _fDeltaTick*3);
			m_OverSprite.SetScaleY(m_OverSprite.GetScaleY() - _fDeltaTick*3);
		}
	}

	if(m_bHighlighted)
	{
		m_Sprite.SetColor(255, 0, 255, 0);
	}
	else
	{
		m_Sprite.SetColor(255, 0, 50, 255);
	}

	if(m_eButtonState == BSTATE_DOWN)
	{
		m_Sprite.SetColor(255, 255, 0, 0);
	}
	else if(m_eButtonState == BSTATE_OVER)
	{
		m_Sprite.SetColor(255, 255, 255, 255);
	}

	/*if(m_Sprite.GetRotate() == 0)
	{
		m_Sprite.SetColor(100, 0, m_Sprite.GetGreen()-3, m_Sprite.GetBlue()+3);
		if(m_Sprite.GetBlue() == 255)
		{
			m_Sprite.SetRotate(2*D3DX_PI);
		}
	}
	else if(m_Sprite.GetRotate() == 2*D3DX_PI)
	{
		m_Sprite.SetColor(100, m_Sprite.GetRed()+3, 0, m_Sprite.GetBlue()-3);
		if(m_Sprite.GetRed() == 255)
		{
			m_Sprite.SetRotate(4*D3DX_PI);
		}
	}
	else if(m_Sprite.GetRotate() == 4*D3DX_PI)
	{
		m_Sprite.SetColor(100, m_Sprite.GetRed()-3, m_Sprite.GetGreen()+3, 0);
		if(m_Sprite.GetGreen() == 255)
		{
			m_Sprite.SetRotate(0);
		}
	}*/


	m_BoundingBox.UpdatePosition(m_PosVec.x, m_PosVec.y);
}
void CButton::Draw()
{
	m_OverSprite.Draw();
	m_Sprite.Draw();

	if(m_bDrawData)
	{
		CTextBox tBox;
		tBox.Initialise(255, m_Sprite.GetX(), m_Sprite.GetY(),4, true, true, 0);
		tBox.SetColor(m_Sprite.GetAlpha(), m_Sprite.GetRed(), m_Sprite.GetGreen(), m_Sprite.GetBlue());
		tBox.SetString(m_strButtonData);
		tBox.Draw();
	}

}

void CButton::Activate()
{
	CGame::GetInstance().PlayGameSound(SOUNDID_UnitDeath);
	switch(m_eType)
	{
		case MENUBUTTON_EXIT:
		{
			m_pParentMenu->OpenChoiceChecker(CHECKER_Exit);

		}
		break;
		case MENUBUTTON_QUIT:
		{
			m_pParentMenu->OpenChoiceChecker(CHECKER_Quit);
		}
		break;
		case MENUBUTTON_LEVEL_EDITOR:
		{
			m_pParentMenu->OpenSubMenu(MENU_LEVEL_EDITOR);
		}
		break;
		case MENUBUTTON_LEVEL_SELECT:
		{
			m_pParentMenu->OpenSubMenu(MENU_LEVEL);
		}
		break;
		case MENUBUTTON_CREDITS:
		{
			m_pParentMenu->OpenSubMenu(MENU_CREDITS);
		}
		break;
		case MENUBUTTON_LEVEL_PREVIEW:
		{
			m_pParentMenu->PreviewLevel(m_strButtonData);
			SetHighlighted(true);
		}
		break;
		case MENUBUTTON_BACK:
		{
			m_pParentMenu->SetAsClosed();
		}
		break;
		case MENUBUTTON_START:
		{
			if(m_pParentMenu->GetMenuType() == MENU_LEVEL)
			{
				if(m_pParentMenu->GetLevelName() != "")
				{
					CGame::GetInstance().SetNewState(GAMESTATE_SESSION, m_pParentMenu->GetLevelName());
				}
			}
			else
			{
				CGame::GetInstance().SetNewState(GAMESTATE_EDITOR, m_pParentMenu->GetLevelName());
			}
		}
		break;
		case MENUBUTTON_RESUME:
		{
			if(CGame::GetInstance().GetSession())
			{
				CGame::GetInstance().GetSession()->SetPaused(false);
			}
			else
			{
				CGame::GetInstance().GetEditor()->SetPaused(false);
			}
		}
		break;
		case MENUBUTTON_SAVE:
		{
			m_pParentMenu->OpenNameForm();
		}
		break;
		case MENUBUTTON_CONFIRM_OVERWRITE:
		{
			m_pParentMenu->GetParentMenu()->CloseNameForm(true);
		}
		break;
		case MENUBUTTON_ABORT_OVERWRITE:
		{
			m_pParentMenu->GetParentMenu()->CloseSubMenu();
			//m_pParentMenu->GetParentMenu()->GetNameForm()->CancelOverwrite();
		}
		break;
		case MENUBUTTON_CYCLEUP:
		{
			m_pParentMenu->CycleLevelsUp();
		}
		break;
		case MENUBUTTON_CYCLEDOWN:
		{
			m_pParentMenu->CycleLevelsDown();
		}
		break;
		case MENUBUTTON_TUTORIAL:
		{
			CGame::GetInstance().SetNewState(GAMESTATE_TUTORIAL);
		}
		break;
	}
		
}

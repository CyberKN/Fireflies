#pragma once

#if !defined(__DEFINES_H__)
#define __DEFINES_H__

#ifndef DIRECTINPUT_VERSION
#define DIRECTINPUT_VERSION 0x0800
#endif

// Library Includes

// Local Includes

// Types
typedef long VertexType;

enum ElgPrimitiveType {
	INVALID_PRIMITIVETYPE,
	IGPT_POINTLIST,
	IGPT_LINELIST,
	IGPT_LINESTRIP,
	IGPT_TRIANGLELIST,
	IGPT_TRIANGLESTRIP,
	IGPT_TRIANGLEFAN
};

enum EIgIndexType
{
	IGIT_NONE,
	IGIT_16,
	IGIT_32
};

enum ESpriteID
{
	SPRITE_Block4Sides,
	SPRITE_Bubble,
	SPRITE_Firefly,
	SPRITE_NameForm,
	SPRITE_LightRays,
	SPRITE_Base1,
	SPRITE_Base2,
	SPRITE_Base3,
	SPRITE_Link,
	SPRITE_Pulse,
	SPRITE_BG,
	SPRITE_Button_New,
	SPRITE_Button_Exit,
	SPRITE_Button_Quit,
	SPRITE_Button_Start,
	SPRITE_Button_Save,
	SPRITE_Button_Blank,
	SPRITE_Button_Resume,
	SPRITE_Button_Editor,
	SPRITE_Button_Back,
	SPRITE_Button_Yes,
	SPRITE_Button_No,
	SPRITE_CC_OverWrite,
	SPRITE_CC_Quit,
	SPRITE_CC_Exit,
	SPRITE_LevelPreview,
	SPRITE_Hover,
	SPRITE_Logo,
	SPRITE_Cursor,
	SPRITE_Button_Tutorial,
	SPRITE_Button_Credits,
	SPRITE_Credits,
	SPRITE_Button_Up,
	SPRITE_Button_Down
	
};

enum ESoundID
{
	
	SOUNDID_ButtonPress = 0,
	SOUNDID_UnitDeath = 1,
	SOUNDID_GameMusic = 4,
	SOUNDID_PowerUp,
	SOUNDID_PowerDown

};

#define VALIDATE(a) if (!a) return (false)

#endif //__DEFINES_H__

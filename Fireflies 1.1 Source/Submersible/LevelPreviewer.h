#pragma once

#if !defined(__LevelPreviewer_H__)
#define __LevelPreviewer_H__

// Library Includes

// Local Includes
#include "MenuItem.h"
#include "TextBox.h"

// Types

// Constants

// Prototypes


class CLevelPreviewer : public CMenuItem
{
// Member Functions
public:
	CLevelPreviewer();
	~CLevelPreviewer();
	void Initialise();
	void Load(std::string _strLevelName);
	void Draw();

protected:

private:

// Member Variables
public:

	CTextBox m_TextBox;
	std::vector<CSpriteDataShell*> m_vecLanterns;

protected:

private:

};

#endif // __LevelPreviewer_H__

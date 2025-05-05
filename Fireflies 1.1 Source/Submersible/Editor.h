#pragma once

#if !defined(__Editor_H__)
#define __Editor_H__

// Library Includes
#include "defines.h"
#include "utils.h"

// Local Includes

// Types

// Constants

// Prototypes

class CLantern;


class CEditor
{
// Member Functions
public:
	CEditor();
	~CEditor();
	void Initialise(CSpriteManager* _pSpriteManager, std::string _strLevelName = "");
	void Process();
	void ProcessInput(CLantern* _pLantern);
	void Draw();
	void AddLantern(float _fX, float _fY);
	void RemoveLantern(CLantern* _pLantern);
	void IncreaseLanternDefaultLevel(CLantern* _pLantern);
	bool Load(std::string _strFile);
	bool Save(std::string _strFile);
	void ListFilesInDirectory(std::string directoryName);
	
	void SetPaused(bool _b){m_bPaused = _b;};


protected:

private:

// Member Variables
public:

protected:

	CSpriteManager* m_pSpriteManager;
	std::vector<CLantern*> m_vecLanterns;
	std::string m_strLevelName;
	D3DXVECTOR2 m_vCursorPos;
	bool m_bPaused;
	CLantern* m_pSelectedLantern;
	bool m_bShowHelp;

	std::vector<std::string> m_vecFileNames;
	CMenu* m_pPauseMenu;

private:

};

#endif // __Editor_H__

// Library Includes

// Local Includes

// This include
#include "INIParser.h"
#include <windows.h>
#include <assert.h>

// Constants

// Static Variables

// Static Function Prototypes

// Implementation

CINIParser::CINIParser()
:m_strFilename("")
{
}

CINIParser::~CINIParser()
{
}

/**
* this function opens and loads the selected ini file.
*
* @Author Jared Jackson
* @param _pcFilename		This is the name of the ini file which is to be loaded.
*
*/
bool CINIParser::LoadIniFile(std::string _pcFileName)
{
	bool bResult = false;
	//Our string values for section and the current line.
	string strLine;
	string strSection;

	//Setting the filename string
	string strFilenameTemp(_pcFileName);
	m_strFilename = strFilenameTemp;

	m_filestream.open(m_strFilename.c_str());

	if (m_filestream.is_open())
	{
		while (!m_filestream.eof())
		{
			bool bReadingKey = true;
			string strKey = "";
			string strValue = "";

			getline( m_filestream, strLine );

			if (strLine == "" || strLine[0] == ';')
			{
				// if the line starts with ; this line is a comment, ignore it
				continue;
			}
			else if (strLine[0] == '[')
			{
				//if the line starts with [ Its a section, read it
				strSection = "";

				for(int i = 0; i < static_cast<int>(strLine.size()); ++i)
				{
					if (strLine[i] == '[' || strLine[i] == ']')
					{
						continue;
					}
					
					strSection += strLine[i];
				}

				continue;
			}
			else if (strLine.empty())
			{
				//string is empty, read next line
				continue;
			}

			for(int i = 0; i < static_cast<int>(strLine.size()); ++i)
			{
				if (strLine[i] == ' ')
				{
					continue;
				}
				else if (strLine[i] == '"')
				{
					continue;
				}
				else if (strLine[i] == '=')
				{
					bReadingKey = false;
					continue;
				}
				else if (strLine[i] == ';')
				{
					// the rest of the line is a comment
					break;
				}

				if (bReadingKey)
				{
					strKey += strLine[i];
				}
				else
				{
					strValue += strLine[i];
				}
			}

			if ( AddValue(strSection.c_str(), strKey.c_str(), strValue.c_str() ) )
			{

			}
		}

		m_filestream.close();
		bResult = true;
	}
	else
	{
		bResult = false;
	}

	return (bResult);
}

/*
Loads or Creates an INI file, but treats it as empty.
*/
bool CINIParser::LoadIniFileEmpty(std::string _pcFileName)
{
	bool bResult = false;

	//Our string values for section and the current line.
	string strLine;
	string strSection;

	//Setting the filename string
	string strFilenameTemp(_pcFileName);
	m_strFilename = strFilenameTemp;

	m_filestream.open(m_strFilename.c_str());

	if (m_filestream.is_open())
	{
		m_filestream.close();
		bResult = true;
	}
	else
	{
		bResult = false;
	}

	return (bResult);

}

/**
* this function adds a value into the ini file.
*
* @Author Jared Jackson
* @param _pcSection			This is the name of the section to add
* @param _pcKey				This is the name of the key to add
* @param _pcValue			this is the value to assign to the key.
*
*/
bool CINIParser::AddValue(std::string _pcSection, std::string _pcKey, std::string _pcValue)
{
	bool bResult = true;

	string strValueCheck(_pcValue);
	if (strValueCheck == "")
	{
		bResult = false;
	}
	else
	{
		string strTempKey(_pcSection);
		strTempKey += + "|";
		strTempKey += _pcKey;

		m_mapPairs[strTempKey] = strValueCheck;
	}

	return (bResult);
}

/**
* this function finds a specific string in the ini file and sets the string past in to be equal to it.
*
* @Author Jared Jackson
* @param _pcSection			This is the name of the section which the string is in
* @param _pcKey				This is the name of the key which the wanted string belongs to
* @param _pcValue			This is the string to be assigned equal to the one in the ini file
*
*/
bool CINIParser::GetStringValue(std::string _pcSection, std::string _pcKey, string &_rStrValue, bool _bSilentFail)
{
	bool bResult = false;

	string strSection(_pcSection);
	string strKey(strSection);
	strKey += "|";
	strKey += _pcKey;

	if(!m_mapPairs[strKey].empty())
	{
		_rStrValue = m_mapPairs[strKey];
		bResult = true;
	}

		
	if(!bResult && !_bSilentFail)
	{
		assert(("Failed to load data from INI", bResult));
	}

	return (bResult);
}

/**
* this function finds a specific int in the ini file and sets the int past in to be equal to it.
*
* @Author Jared Jackson
* @param _pcSection			This is the name of the section which the int is in
* @param _pcKey				This is the name of the key which the wanted int belongs to
* @param _riValue			This is the int to be assigned equal to the one in the ini file
*
*/
bool CINIParser::GetIntValue(std::string _pcSection, std::string _pcKey, int &_riValue, bool _bSilentFail)
{
	bool bResult = false;

	string strSection(_pcSection);
	string strKey(strSection);
	strKey += "|";
	strKey += _pcKey;

	if(!m_mapPairs[strKey].empty())
	{
		_riValue = atoi(m_mapPairs[strKey].c_str());
		bResult = true;
	}
	
	if(!bResult && !_bSilentFail)
	{
		assert(("Failed to load data from INI", bResult));
	}

	return (bResult);
}

/**
* this function finds a specific float in the ini file and sets the float past in to be equal to it.
*
* @Author Jared Jackson
* @param _pcSection			This is the name of the section which the float is in
* @param _pcKey				This is the name of the key which the wanted int belongs to
* @param _rfValue			This is the float to be assigned equal to the one in the ini file
*
*/
bool CINIParser::GetFloatValue(std::string _pcSection, std::string _pcKey, float &_rfValue, bool _bSilentFail)
{
	bool bResult = false;

	string strSection(_pcSection);
	string strKey(strSection);
	strKey += "|";
	strKey += _pcKey;

	if(!m_mapPairs[strKey].empty())
	{
		_rfValue = static_cast<float>(atof(m_mapPairs[strKey].c_str()));
		bResult = true;
	}

	if(!bResult && !_bSilentFail)
	{
		assert(("Failed to load data from INI", bResult));
	}

	return (bResult);
}


/**
* this function finds a specific bool in the ini file and sets the bool past in to be equal to it.
*
* @Author Jared Jackson
* @param _pcSection			This is the name of the section which the bool is in
* @param _pcKey				This is the name of the key which the wanted int belongs to
* @param _rfValue			This is the bool to be assigned equal to the one in the ini file
*
*/
bool CINIParser::GetBoolValue(std::string _pcSection, std::string _pcKey, bool &_rbValue, bool _bSilentFail)
{
	bool bResult = false;

	string strSection(_pcSection);
	string strKey(strSection);
	strKey += "|";
	strKey += _pcKey;

	if(!m_mapPairs[strKey].empty())
	{
		_rbValue = (m_mapPairs[strKey] == "true");
		bResult = true;
	}
		
	if(!bResult && !_bSilentFail)
	{
		assert(("Failed to load data from INI", bResult));
	}

	return (bResult);
}

/**
* @DESC			Saves the Ini file.
* @AUTHOR		Josh van den Heever
* @RETURN		True if file was found and saved.
*/
bool CINIParser::SaveIniFile()
{
	bool bResult = false;

	std::string strCurSection = "";
	std::string strCurLine = "";
	std::map<std::string, std::string>::iterator mapIter;
	std::map<std::string, std::string>::iterator mapBeginMinusOne;

	int iEscape = 0;
	while ( m_filestream.good() == false )
	{
		if ( 5 == ++iEscape )
		{
			// unable to clear the file
			return false;
		}
		m_filestream.clear();
	}

	m_filestream.open(m_strFilename.c_str(), std::ios::out | std::ios::trunc);

	if (m_filestream.is_open())
	{
		bResult = true;

		mapIter = m_mapPairs.end();
		--mapIter;
		mapBeginMinusOne = m_mapPairs.begin();
		--mapBeginMinusOne;

		for(;mapIter != mapBeginMinusOne; --mapIter)
		{
			std::string strSection = mapIter->first.substr(0, mapIter->first.find("|"));
			if(strSection != strCurSection)
			{
				strCurSection = strSection;
				strCurLine = '[';
				strCurLine += strCurSection;
				strCurLine += ']';
				m_filestream << strCurLine << std::endl;
			}

			strCurLine = mapIter->first.substr( mapIter->first.find("|")+1, mapIter->first.size()-1 ) + " = ";
			strCurLine += mapIter->second;

			m_filestream << strCurLine << std::endl;
		}
		m_filestream.close();
	}

	m_filestream.clear();

	return (bResult);
}



/**
* this function returns true if a key exists, and doesn't throw errors if the check fails
*
* @Author Kurt Nadworny
* @param _pcSection			This is the name of the section which the bool is in
* @param _pcKey				This is the name of the key which the wanted int belongs to
*
*/
bool CINIParser::SafeCheck(std::string _pcSection, std::string _pcKey)
{
	bool bResult = false;

	string strSection(_pcSection);
	string strKey(strSection);
	strKey += "|";
	strKey += _pcKey;

	if(!m_mapPairs[strKey].empty())
	{
		bResult = true;
	}

	return (bResult);
}
#pragma once

#if !defined(__INIParser_H__)
#define __INIParser_H__

// Library Includes
#include <map>
#include <string>
#include <fstream>

// Local Includes

// Types

using namespace std;

// Constants

// Prototypes


class CINIParser
{
// Member Functions
public:
	CINIParser();
	~CINIParser();

	bool LoadIniFile(std::string _pcFileName);
	bool LoadIniFileEmpty(std::string _pcFileName);
	bool AddValue(std::string _pcSection, std::string _pcKey, std::string _pcValue);
	bool GetStringValue(std::string _pcSection, std::string _pcKey, string& _rStrValue, bool _bSilentFail = false);
	bool GetIntValue(std::string _pcSection, std::string _pcKey, int& _riValue, bool _bSilentFail = false);
	bool GetFloatValue(std::string _pcSection, std::string _pcKey, float& _rfValue, bool _bSilentFail = false);
	bool GetBoolValue(std::string _pcSection, std::string _pcKey, bool& _rbValue, bool _bSilentFail = false);
	bool SafeCheck(std::string _pcSection, std::string _pcKey);
	bool SaveIniFile();

protected:

private:

// Member Variables
public:

protected:

private:
	map<string, string> m_mapPairs;
	string m_strFilename;
	fstream m_filestream;

};

#endif // __INIParser_H__

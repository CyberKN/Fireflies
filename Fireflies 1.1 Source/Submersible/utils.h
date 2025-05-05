// File Name		:	utils.h
// Description		:	Header File containing useful utility functions
// Author			:	Kurt Nadworny
//

#pragma once

#if !defined(__UTILS_H__)
#define __UTILS_H__

// Library Includes
#include <windows.h>
#include <assert.h>

#include <string>
#include <sstream>
#include <vector>

// Local Includes

// Types 

// Constants 

// Prototypes


/**
* Function to WStrings into strings
* 
* @Author Kurt
* @param ws			wstring that you want to convert
*
* @return wstring Converted into string
*/
inline std::string WStringToString(const std::wstring& ws)
{
	std::string s(ws.begin(), ws.end());
	s.assign(ws.begin(), ws.end());

	return s; 
}

/**
* Function to convert strings into WStrings
* 
* @Author Kurt
* @param s			string that you want to convert
*
* @return string Converted into WString
*/
inline std::wstring StringToWString(const std::string& s)
{
	std::wstring temp(s.length(),L' ');
	copy(s.begin(), s.end(), temp.begin());
	return temp; 
}

/**
* Function to convert ints into strings
* 
* @Author Kurt
* @param number			int that you want to convert
*
* @return int Converted into string
*/
inline std::string IntToString(int number)
{
	std::ostringstream strStream;

	strStream << number;
	 
	std::string str;

	str = strStream.str();
	return(str);
}


/**
* Function to convert floats into strings
* 
* @Author Kurt
* @param number			float that you want to convert
*
* @return float Converted into string
*/
inline std::string FloatToString(float number)
{
	std::ostringstream strStream;

	strStream << number;
	 
	std::string str;

	str = strStream.str();
	return(str);
}

inline std::string BoolToString(bool _b)
{
	std::string str;

	if(_b)
	{
		str = "true";
	}
	else
	{
		str = "false";
	}

	return(str);
}


/**
* Function to convert strings into floats
* 
* @Author Kurt
* @param input			string that you want to convert
*
* @return string Converted into float
*/
inline float StringToFloat(std::string input)
{
	return(static_cast<float>(atof(input.c_str())));
} 


/**
* Function to convert strings into ints
* 
* @Author Kurt
* @param input			string that you want to convert
*
* @return string Converted into int
*/
inline int StringToInt(std::string input)
{
	return(atoi(input.c_str()));
}

/**
* Function to Generate random Integers
* 
* @Author Kurt
*
* @return random int
*/
inline int RandInt(int iMin, int iMax)
{
	return(iMin + rand() % (-(iMin - ++iMax)));
}

/**
* Function to Generate random floating point numbers
* 
* @Author Kurt
*
* @return random float
*/
inline float RandFloat(float a, float b)
{
return ((b-a)*((float)rand()/RAND_MAX))+a;
}


inline int ClampInt(int iInteger, int iMin, int iMax)
{
	if(iInteger > iMax)
	{
		iInteger = iMax;
		return(iInteger);
	}
	
	if(iInteger < iMin)
	{
		iInteger = iMin;
	}

	return(iInteger);
}

template<class T>
inline T Clamp(T iInteger, T iMin, T iMax)
{
	if(iInteger > iMax)
	{
		iInteger = iMax;
		return(iInteger);
	}
	
	if(iInteger < iMin)
	{
		iInteger = iMin;
	}

	return(iInteger);
}


inline std::string GetUserNameString()
{
	TCHAR name[256];
	DWORD size = 256;
	bool bNameTest = (GetUserName( (TCHAR*)name, &size ) != 0);

	std::string strName;
	for(unsigned int i = 0; i < size; ++i)
	{
		strName += static_cast<char>(name[i]);
	}
	return(strName);
}


inline std::string wchar_t2string(const wchar_t *wchar)
{
    std::string str = "";
    int index = 0;
    while(wchar[index] != 0)
    {
        str += (char)wchar[index];
        ++index;
    }
    return str;
}

inline void string2wchar_t(const std::string &str, wchar_t * wchar)
{
   unsigned int index = 0;
    while(index < str.size())
    {
        wchar[index] = (wchar_t)str[index];
        ++index;
    }
    wchar[index] = 0;
    //return wchar;
}


inline float SmoothStep(float _fT)
{
	float fTemp = (_fT * _fT * (3.0f - 2.0f * _fT));
	Clamp(fTemp, 0.0f, 1.0f);
	return fTemp;
}





#endif // __UTILS_H__
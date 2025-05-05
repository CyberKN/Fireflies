#pragma once

#if !defined(__Vector_H__)
#define __Vector_H__

// Library Includes

// Local Includes

// Types

// Constants

// Prototypes
template <class T>
class CVector
{
public:
	CVector()
	{
		pArray = new T[1];
		uMaxLength = 1;
		uCurrentLength = 0;
	}

	~CVector()
	{
		while(uCurrentLength > 1)
		{
			pop_back();
		}

		delete[] pArray;
		pArray = 0;
	}

	unsigned int size()
	{
		return(GetSize());
	}

	unsigned int  GetSize()
	{
		return(uCurrentLength);
	}

	void push_back(T _Data)
	{
		uCurrentLength++;

		if(uCurrentLength > uMaxLength)
		{
			const unsigned int uNewSize = uMaxLength*2;

			T* tempArray = new T[uNewSize];

			uMaxLength = uNewSize;

			for(unsigned int i = 0; i < uCurrentLength; ++i)
			{
				tempArray[i] = pArray[i];
			}

			tempArray[uCurrentLength-1] = _Data;

			delete[] pArray;

			pArray = tempArray;
			tempArray = 0;
		}
		else
		{	
			pArray[uCurrentLength-1] = _Data;
		}
	}
	

	void pop_back()
	{
		if(uCurrentLength > 0)
		{
			pArray[uCurrentLength-1] = 0;		
			uCurrentLength--;
		}
	}

	T& operator[](const size_t index)
	{
		return(pArray[index]);
	}


	T* pArray;
	unsigned int uMaxLength;
	unsigned int uCurrentLength;
};

#endif // __Vector_H__
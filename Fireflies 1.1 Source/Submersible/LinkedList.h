#pragma once

#if !defined(__LinkedList_H__)
#define __LinkedList_H__

// Library Includes

// Local Includes

// Types

// Constants

// Prototypes
template <class T>
class CNode
{
public:
	CNode()
	{
		m_pNextNode = 0;
	}

	~CNode()
	{
		m_pNextNode = 0;
	}

	void SetNextNode(CNode* _pNode)
	{
		m_pNextNode = _pNode;
	}

	void SetData(T _Data)
	{
		m_Data = _Data;
	}

	CNode* GetNextNode()
	{
		return(m_pNextNode);
	}

	T GetData()
	{
		return(m_Data);
	}

	CNode* m_pNextNode;
	T m_Data;


};


template <class T>
class CLinkedList
{
public:
	CLinkedList()
	{
		m_pFirstNode = 0;
		uLength = 0;
	}

	~CLinkedList()
	{
		while(m_pFirstNode)
		{
			pop_back();
		}

	}

	CNode<T>* GetFirst()
	{
		return(m_pFirstNode);
	}

	unsigned int size()
	{
		return(GetSize());
	}

	unsigned int  GetSize()
	{
		return(uLength);
	}

	void push_back(T _Data)
	{
		if(m_pFirstNode)
		{
			CNode<T>* pTempNode = m_pFirstNode;

			while(pTempNode->GetNextNode())
			{
				pTempNode = pTempNode->GetNextNode();
			}

			CNode<T>* pNewNode = new CNode<T>;

			pNewNode->SetData(_Data);

			pTempNode->SetNextNode(pNewNode);

			pTempNode = 0;
			pNewNode = 0;
		}
		else
		{
			m_pFirstNode = new CNode<T>;
			m_pFirstNode->SetData(_Data);
		}

		uLength++;
	}

	void pop_back()
	{
		if(m_pFirstNode)
		{
			if(m_pFirstNode->GetNextNode())
			{
				CNode<T>* pTempNode = m_pFirstNode;

				while(pTempNode->GetNextNode()->GetNextNode())
				{
					pTempNode = pTempNode->GetNextNode();
				}

				delete pTempNode->GetNextNode();
				pTempNode->SetNextNode(0);
				pTempNode = 0;
			}
			else
			{
				delete m_pFirstNode;
				m_pFirstNode = 0;				
			}
			uLength--;
		}
		else
		{
			//The list is already empty.
		}
	}

	T& operator[](const size_t index)
	{
		CNode<T>* pTempNode = m_pFirstNode;

		for(size_t i=0; i<index; i++)
		{
			pTempNode = pTempNode->m_pNextNode;
		}

		return(pTempNode->m_Data);
	}


	CNode<T>* m_pFirstNode;
	unsigned int uLength;
};

#endif // __LinkedList_H__

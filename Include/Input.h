#pragma once
#include "Game.h"

typedef struct _tagKeyState
{
	bool bDown;
	bool bPressed;
	bool bUp;

	_tagKeyState() :
		bDown(false),
		bPressed (false),
		bUp(false)
	{	
	}

}KEYSTATE, *PKEYSTATE;

class CInput
{
private:
	static CInput* m_pInstance;
public :
	static CInput* GetInstance()
	{
		if (!m_pInstance)
		{
			m_pInstance = new CInput;
		}
		return m_pInstance;
	}
	static void DestroyInstance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = NULL;
		}
	}

private:
	unordered_map<int, PKEYSTATE> m_mapKeyState;
	
public:
	static CVector2 GetCursorPosition();

public:
	bool GetKeyDown(int iKey);
	bool GetKeyUp(int iKey);
	bool GetKey(int iKey);
	void Update();
	void Initialize();

private:
	CInput() {};
	~CInput() 
	{
		unordered_map<int, PKEYSTATE>::iterator iter;
		unordered_map<int, PKEYSTATE>::iterator iterEnd = m_mapKeyState.end();

		for (iter = m_mapKeyState.begin(); iter != iterEnd; ++iter)
		{
			if (iter->second)
				delete iter->second;
		}		
		m_mapKeyState.clear();
	};
};


#include "Input.h"
#include "Core.h"

CInput* CInput::m_pInstance = NULL;


CVector2 CInput::GetCursorPosition()
{
	POINT pos;
	GetCursorPos(&pos);
	ScreenToClient(GET_SINGLE(CCore)->GetWindowHandle(), &pos);
	return CVector2(pos.x, pos.y);
}

bool CInput::GetKeyDown(int iKey)
{
	unordered_map<int, PKEYSTATE>::iterator iter = m_mapKeyState.find(iKey);
	if (iter == m_mapKeyState.end())
	{
		return false;
	}
	return iter->second->bDown;
}

bool CInput::GetKeyUp(int iKey)
{
	unordered_map<int, PKEYSTATE>::iterator iter = m_mapKeyState.find(iKey);
	if (iter == m_mapKeyState.end())
	{
		return false;
	}
	return iter->second->bUp;
}

bool CInput::GetKey(int iKey)
{
	unordered_map<int, PKEYSTATE>::iterator iter = m_mapKeyState.find(iKey);
	if (iter == m_mapKeyState.end())
	{
		return false;
	}
	return iter->second->bPressed;
}

void CInput::Update()
{
	unordered_map<int, PKEYSTATE>::iterator iter;
	unordered_map<int, PKEYSTATE>::iterator iterEnd = m_mapKeyState.end();

	for (iter = m_mapKeyState.begin(); iter != iterEnd; ++iter)
	{
		bool bKeyState = GetAsyncKeyState(iter->first) & 0x8000;
		if (!iter->second->bDown && bKeyState && !iter->second->bPressed)
		{
			iter->second->bDown = true;
			iter->second->bPressed = true;
			iter->second->bUp = false;
		}
		else if (iter->second->bDown && bKeyState)
		{
			iter->second->bDown = false;
			iter->second->bPressed = true;
			iter->second->bUp = false;
		}
		else if (iter->second->bPressed && !bKeyState)
		{
			iter->second->bDown = false;
			iter->second->bPressed = false;
			iter->second->bUp = true;
		}
		else if(iter->second->bUp && !bKeyState)
		{
			iter->second->bDown = false;
			iter->second->bPressed = false;
			iter->second->bUp = false;
		}		
	}
}


void CInput::Initialize()
{
	for (int i = 1; i < 256; ++i)
	{
		m_mapKeyState.insert(make_pair(i, new KEYSTATE));
	}
}

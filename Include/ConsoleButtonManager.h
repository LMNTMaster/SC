
#pragma once
#include "Game.h"

class CConsoleButtonManager
{
private:
	static CConsoleButtonManager* m_pInstance;

public:
	static CConsoleButtonManager* GetInstance()
	{
		if (!m_pInstance)
		{
			m_pInstance = new CConsoleButtonManager;
		}
		return m_pInstance;
	}
	static void DestoryInstance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;

		}
	}

private:
	class CGameObject* m_pTargetObject;
	vector < class CGameObject* > m_vecControlPanelButton;

public:
	class CGameObject* GetTargetObject() const
	{
		return m_pTargetObject;
	}
	void AddControlPanelButton(class CGameObject* pGameObject, int idx)
	{
		m_vecControlPanelButton[idx] = pGameObject;
	}
	void UpdateControlPanel(class CGameObject* pGameObject);
	class CGameObject* GetControlPanelObject(int index)
	{
		return m_vecControlPanelButton[index];
	}
	void ClearControlPanel();

public:
	void Initialize();

private:
	CConsoleButtonManager();
	~CConsoleButtonManager();
};


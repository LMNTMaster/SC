#pragma once
#include "Game.h"
class CInfoPanelManager
{
private:
	static CInfoPanelManager* m_pInstance;
public:
	static CInfoPanelManager* GetInstance()
	{
		if (!m_pInstance)
		{
			m_pInstance = new CInfoPanelManager;
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
	list<class CGameObject*> m_CurrentContainedObjectList;
	class CLayer* m_pInfoPanelLayer;


public:
	void SetInfoPanelLayer(class CLayer* pLayer)
	{
		m_pInfoPanelLayer = pLayer;
	}
	CLayer* GetInfoPanelLayer() const
	{
		return m_pInfoPanelLayer;
	}

private:

public:

	void ClearInfoPanel();

	void UpdateInfoPanel(list<class CGameObject*> vecSelectedUnits);
	void UpdateInfoPanel(class CUnitInfo* pInfo);

public:
	void Initialize();

private:

	CInfoPanelManager();
	~CInfoPanelManager();
};


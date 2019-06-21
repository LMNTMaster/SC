#pragma once
#include "../Component.h"
class CCursor :
	public CComponent
{
private:
	friend class CInfoPanelButton;

private:
	CVector2 m_ClickedWorldPosition;
	list<class CGameObject*> m_SelectedUnitList;
	class CGameObject* m_pRect;
	bool m_bHasRequested;
	class CConsoleButton* m_pRequestedButton;
	class CGameObject* m_pRequestedButtonObject;
	bool m_bAdvancedBuildRequest;
	function<void(CVector2, class CGameObject*)> m_RequestedFunction;

	bool m_bBuildMode;
	class CGameObject* m_pBuildTarget;

	float m_fInfoPanelUpdateRate;
	float m_fInfoPanelUpdateTime;

public:
	void RemoveSelectedUnit(class CGameObject* pTarget)
	{
		list<class CGameObject*>::iterator iter;
		list<class CGameObject*>::iterator iterEnd = m_SelectedUnitList.end();
		for (iter = m_SelectedUnitList.begin(); iter != iterEnd; ++iter)
		{
			if (pTarget == *iter)
			{
				m_SelectedUnitList.erase(iter);
				break;
			}
		}
	}
	bool ContainedInSelectedUnit(class CGameObject* pTarget)
	{
		list<class CGameObject*>::iterator iter;
		list<class CGameObject*>::iterator iterEnd = m_SelectedUnitList.end();
		for (iter = m_SelectedUnitList.begin(); iter != iterEnd; ++iter)
		{
			if (pTarget == *iter)
			{
				return true;
			}
		}
		return false;
	}
	void UnSelectAllUnit();

	void EndBuildMode();

	void SetBuildTarget(bool isAdvanced, class CGameObject* pTarget);
	
	void SetBuildMode(bool bBuildMode)
	{
		m_bBuildMode = bBuildMode;
	}

	void EndRequest();
	
	list<class CGameObject*> GetSelectedUnitList() const
	{
		return m_SelectedUnitList;
	}
	void RequestFunction(class CGameObject* pButtonObject, class CConsoleButton* pButton, function<void(CVector2, class CGameObject*)> func);

public:
	void LateUpdate() override;
	void LoadComponent(FILE* pFile) override;
	void SaveComponent(FILE* pFile)override;
	CComponent* clone();

public:
	CCursor(const CCursor& component);
	CCursor();
	~CCursor();
};


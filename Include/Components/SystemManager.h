#pragma once
#include "..\Component.h"
class CSystemManager :
	public CComponent
{

private:
	CVector2 m_CurrentMouseWorldPosition;
	CVector2 m_CurrentMousePosition;
	CVector2 m_ClickedMousePosition;
	bool m_bLeftButtonClicked;

	list<class CGameObject*> m_SelectUnitList;

	class CGameObject* m_pRectRenderer;

private:
	bool Contain(CGameObject* pGameObject)
	{
		list<class CGameObject*>::iterator iter;
		list<class CGameObject*>::iterator iterEnd = m_SelectUnitList.end();
		for (iter = m_SelectUnitList.begin(); iter != iterEnd; ++iter)
		{
			if ((*iter) == pGameObject)
			{
				return true;
			}
		}
		return false;
	}

public:
	void Update() override;
	
public:
	void SaveComponent(FILE* pFile) override;
	void LoadComponent(FILE* pFile) override;
	CComponent* clone() override;


public:
	CSystemManager(const CSystemManager& component);
	CSystemManager();
	~CSystemManager();
};


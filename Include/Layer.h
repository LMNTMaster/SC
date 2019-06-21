#pragma once
#include "Game.h"	

class CLayer
{
private:
	friend class CScene;

private:
	class CScene* m_pScene;
	unsigned int m_iZOrder;
	string m_strName;
	list<class CGameObject*> m_GameObjectList;


public :
	const list<class CGameObject*>& GetAllUnit() const
	{
		return m_GameObjectList;
	}
	list<class CGameObject*> FindGameObjects(const string& strName);
	
	class CGameObject* FindGameObject(const string& strName) const;
	class CGameObject* FindGameObject(class CGameObject* pGameObject) const;
	void RemoveGameObject(class CGameObject* gameObject);
	void AddGameObject(class CGameObject* gameObject);
	
	int GetZOrder() const
	{
		return m_iZOrder;
	}
	void SetZOrder(int iZ)
	{
		m_iZOrder = iZ;
	}
	const string& GetName() const
	{
		return m_strName;
	}
	void SetName(const string& strName)
	{
		m_strName = strName; 
	}
	void SetScene(class CScene* pScene)
	{
		m_pScene = pScene;
	}
	class CScene* GetScene() const
	{
		return m_pScene;
	}

public:
	static bool VerticalSort(class CGameObject * pO1, class CGameObject * pO2);

public:
	void Initialize();
	void Start();
	void Update();
	void Render();
	void LateUpdate();

public:
	CLayer();
	virtual ~CLayer();
};


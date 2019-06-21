#pragma once
#include "Game.h"

class CScene
{
private:
	friend class CSceneManager;
	friend class CFileStream;
	
private:
	list<class CLayer*> m_LayerList;
	string m_strName;
	list<class CCollider*> m_ColliderList;
	list<class CButtonCollider*> m_ButtonColliderList;

protected:

	class CCamera* m_pCamera;
	CVector2 m_GridSize;
	CVector2 m_TileSize;
	class CTerrainRenderer* m_pTerrainRenderer;
	vector<class CPlayer*> m_vecPlayer;
public:

	void AddPlayer(class CPlayer* pPlayer)
	{
		m_vecPlayer.push_back(pPlayer);
	}
	void SetPlayerRandomColor();

	void RemovePlayer(class CPlayer* pPlayer)
	{
		vector<class CPlayer*>::iterator iter;
		vector<class CPlayer*>::iterator iterEnd = m_vecPlayer.end();
		for (iter = m_vecPlayer.begin(); iter != iterEnd; ++iter)
		{
			if ((*iter) == pPlayer)
			{
				m_vecPlayer.erase(iter);
				break;
			}
		}
	}

	CVector2 GetGridSize() const
	{
		return m_GridSize;
	}
	CVector2 GetTileSize() const
	{
		return m_TileSize;
	}
	


public:
	static bool LayerSort(CLayer * pL1, CLayer * pL2);

public:
	class CTerrainRenderer* GetTerrainRenderer() const
	{
		return m_pTerrainRenderer;
	}
	void SetTerrainRenderer(class CTerrainRenderer* pRenderer)
	{
		m_pTerrainRenderer = pRenderer;
	}
	void ClearContainUnitList();
	
	class CTile* GetTileByIndex(int idx);
	

	void AddButtonCollider(class CButtonCollider* pCollider)
	{
		m_ButtonColliderList.push_back(pCollider);
	}

	void RemoveButtonCollider(class CButtonCollider* pCollider)
	{
		list<class CButtonCollider*>::iterator iter;
		list<class CButtonCollider*>::iterator iterEnd = m_ButtonColliderList.end();

		for (iter = m_ButtonColliderList.begin(); iter != iterEnd; ++iter)
		{
			if ((*iter) == pCollider)
			{
				m_ButtonColliderList.erase(iter);
				break;
			}
		}
	}
	
	void AddCollider(class CCollider* pCollider)
	{
		m_ColliderList.push_back(pCollider);
	}
	void RemoveCollider(class CCollider* pCollider)
	{
		list<class CCollider*>::iterator iter;
		list<class CCollider*>::iterator iterEnd = m_ColliderList.end();

		for (iter = m_ColliderList.begin(); iter != iterEnd; ++iter)
		{
			if ((*iter) == pCollider)
			{
				m_ColliderList.erase(iter);
				break;
			}
		}
	}
	void SetCamera(class CCamera* pCamera)
	{
		m_pCamera = pCamera;
	}
	class CCamera* GetCamera() const
	{
		return m_pCamera;
	}

	void SortLayer();
	string GetName() const
	{
		return m_strName;
	}
	void SetName(const string& strName)
	{
		m_strName = strName;
	}
	class CLayer* CreateLayer(const string& strLayerName, int zOrder);
	class CLayer* GetLayer(const string& strLayerName) const;
	void AddLayer(class CLayer* layer);
	CLayer* FindLayer(const string& strLayerName) const;
	
	

public :
	void Initialize();
	void Start();
	void Update();
	void Render();
	void LateUpdate();
	void Collision();

public:
	CScene();
	virtual ~CScene();
};


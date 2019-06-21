#pragma once
#include "Game.h"
#include "Components\TextureRenderer.h"
#include "Collider.h"
#include "Components\ButtonCollider.h"
#include "Scene.h"
#include "Component.h"
#include "Components\Structure.h"
#include "Renderer.h"


class CGameObject
{
private:
	friend class CLayer;
	friend class CScene;
	friend class CRenderer;

private:
	CGameObject* m_pParent;
	list<CGameObject*> m_ChildrenList;
	
	class CTransform* m_pTransform;
	bool m_bDestory;
	class CLayer* m_pLayer;
	class CScene* m_pScene;
	string m_strName;
	string m_strKey;
	list<class CComponent*> m_ComponentList;
	list<class CRenderer*> m_pRendererList;
	list<class CConsoleButton*> m_ButtonList;
	bool m_bSelected;
	bool m_bAirUnit;

	class CPlayer* m_pPilot;


public:
	void SetPilot(class CPlayer* pPlayer)
	{
		m_pPilot = pPlayer;
	}
	class CPlayer* GetPilot() const
	{
		return m_pPilot;
	}

	void RemoveButton(class CConsoleButton* pButton)
	{
		list<class CConsoleButton*>::iterator iter;
		list<class CConsoleButton*>::iterator iterEnd = m_ButtonList.end();
		for (iter = m_ButtonList.begin(); iter != iterEnd; ++iter)
		{
			if (*iter == pButton)
			{
				m_ButtonList.erase(iter);
				break;
			}
		}
	}
	const list<class CConsoleButton*>& GetButtonList() const
	{
		return m_ButtonList;
	}
	void AddButton(class CConsoleButton* pButton)
	{
		m_ButtonList.push_back(pButton);
	}

	bool IsAirUnit() const
	{
		return m_bAirUnit;
	}
	void SetToAirUnit(bool bIsAirUnit)
	{
		m_bAirUnit = bIsAirUnit;
	}
	void SetSelected(bool bSelected)
	{
		m_bSelected = bSelected;
	}

	bool GetSelected() const
	{
		return m_bSelected;
	}
	void SetKey(const string& strKey)
	{
		m_strKey = strKey;
	}
	const string& GetKey() const
	{
		return m_strKey;
	}
	
	class CTransform* GetTransform() const
	{
		return m_pTransform;
	}
	CLayer* GetLayer() const
	{
		return m_pLayer;
	}
	void SetLayer(const string& strLayer);
	void SetLayer(class CLayer* pLayer)
	{
		m_pLayer = pLayer;
	}
	class CScene* GetScene() const
	{
		return m_pScene;
	}	
	void SetScene(class CScene* pScene)
	{
		m_pScene = pScene;
	}
	bool GetDestroy() const
	{
		return m_bDestory;
	}
	void SetDestroy(bool bDestroy);
	
	size_t GetComponentCount() const
	{
		return m_ComponentList.size();
	}

	const string& GetName() const
	{
		return m_strName;
	}
	void SetName(string& strName)
	{
		m_strName = strName;
	}
	CGameObject* GetParent() const
	{
		return m_pParent;
	}
	void SetParent(CGameObject* pParent)
	{
		if (!pParent->GetChild(this))
		{
			m_pParent = pParent;
			pParent->AddChild(this);
		}
	}
	void AddChild(CGameObject* pChild)
	{
		if (!GetChild(pChild))
		{
			pChild->SetParent(this);
			m_ChildrenList.push_back(pChild);
		}
	}
	unsigned int GetChildCount() const
	{
		return m_ChildrenList.size();
	}
	list<CGameObject*>* GetChildren() 
	{
		return &m_ChildrenList;
	}
	CGameObject* GetChild(string& strName) const
	{
		list<CGameObject*>::const_iterator iter;
		list<CGameObject*>::const_iterator iterEnd = m_ChildrenList.end();

		for (iter = m_ChildrenList.begin(); iter != iterEnd; ++iter)
		{
			if ((*iter)->GetName() == strName)
			{
				return *iter;
			}
		}
		return NULL;
	}
	CGameObject* GetChild(CGameObject* pGameObject) const
	{
		list<CGameObject*>::const_iterator iter;
		list<CGameObject*>::const_iterator iterEnd = m_ChildrenList.end();

		for (iter = m_ChildrenList.begin(); iter != iterEnd; ++iter)
		{
			if ((*iter)== pGameObject)
			{
				return *iter;
			}
		}
		return NULL;
	}

	list<class CRenderer*>::iterator FindRenderer(class CComponent* pComponent)
	{
		list<class CRenderer*>::iterator iter;
		list<class CRenderer*>::iterator iterEnd = m_pRendererList.end();

		for (iter = m_pRendererList.begin(); iter != iterEnd; ++iter)
		{
			if ((*iter) == dynamic_cast<class CRenderer*>(pComponent))
				return iter;
		}

		return iterEnd;
	}

	const list<class CComponent*>&  GetComponents() const
	{
		return m_ComponentList;
	}
	template<typename T>
	list<T*> GetComponents()	
	{
		list<T*> temp;
		list<CComponent*>::iterator iter;
		list<CComponent*>::iterator iterEnd = m_ComponentList.end();
	
		for (iter = m_ComponentList.begin(); iter != iterEnd; ++iter)
		{	
			T* pCastedComponent = dynamic_cast<T*>(*iter);

			if (pCastedComponent)
			{
				temp.push_back(pCastedComponent);
			}
		}
		return temp;
	}

	template<typename T>
	T* GetComponent() const
	{
		list<CComponent*>::const_iterator iter;
		list<CComponent*>::const_iterator iterEnd = m_ComponentList.end();

		for (iter = m_ComponentList.begin(); iter != iterEnd; ++iter)
		{
			T* castedComponent = dynamic_cast<T*>((*iter));
			if (castedComponent)
			{
				return castedComponent;
			}
		}
		return NULL;
	}
	template<typename T>
	T* AddComponent()
	{
		T* tempComponent = new T;
		CComponent* castedComponent = dynamic_cast<CComponent*>(tempComponent);

		if (castedComponent)
		{
			castedComponent->SetGameObject(this);
			m_ComponentList.push_back(castedComponent);

			if (dynamic_cast<class CRenderer*>(castedComponent))
			{
				m_pRendererList.push_back((class CRenderer*)tempComponent);
			}
			if (dynamic_cast<class CCollider*>(castedComponent))
			{
				if (dynamic_cast<CButtonCollider*>(castedComponent))
				{
					m_pScene->AddButtonCollider((CButtonCollider*)tempComponent);
				}
				else
				{
					if (m_pScene)
					{
						m_pScene->AddCollider((class CCollider*)tempComponent);
					}
				}				
			}
		}
		else
		{
			throw invalid_argument("–Y");
		}

		return tempComponent;
	}

	template<typename T>
	void RemoveComponent()
	{
		list<CComponent*>::iterator iter;
		list<CComponent*>::iterator iterEnd = m_ComponentList.end();

		for (iter = m_ComponentList.begin(); iter != iterEnd;)
		{
			if (dynamic_cast<T*>((*iter)))
			{
				if ((*iter)->GetComponentParentType() == PT_RENDERER)
				{
					m_pRendererList.erase(FindRenderer(*iter));
				}
				if ((*iter)->GetComponentParentType() == PT_COLLIDER)
				{
					if (dynamic_cast<class CButtonCollider*>(*iter))
					{
						m_pScene->RemoveButtonCollider(dynamic_cast<class CButtonCollider*>((*iter)));
					}
					else
					{
						m_pScene->RemoveCollider(dynamic_cast<class CCollider*>((*iter)));
					}
				}

				delete (*iter);
				iter = m_ComponentList.erase(iter);
			}
			else
				++iter;
		}
	}

public:
	void Initialize();
	void Start();
	void Update();
	void Render();
	void LateUpdate();
	void CollisionEnter();
	void CollisionStay();
	void CollisionExit();

public:
	CGameObject* clone();

public:
	CGameObject(const CGameObject& gameObject);
	CGameObject(const string& strName);
	CGameObject();
	virtual ~CGameObject();
};


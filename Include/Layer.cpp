#include "Layer.h"
#include "GameObject.h"
#include "Components\Transform.h"


list<class CGameObject*> CLayer::FindGameObjects(const string & strName)
{
	list <class CGameObject*> tempList;
	list<class CGameObject*>::iterator iter;
	list<class CGameObject*>::iterator iterEnd = m_GameObjectList.end();
	for (iter = m_GameObjectList.begin(); iter != iterEnd; ++iter)
	{
		if ((*iter)->GetName() == strName)
		{
			tempList.push_back((*iter));
		}
	}
	return tempList;
}

CGameObject * CLayer::FindGameObject(const string & strName) const
{
	list<class CGameObject*>::const_iterator iter;
	list<class CGameObject*>::const_iterator iterEnd = m_GameObjectList.end();
	for (iter = m_GameObjectList.begin(); iter != iterEnd; ++iter)
	{
		if ((*iter)->GetName() == strName)
		{
			return *iter;
		}
	}
	return NULL;
}

CGameObject * CLayer::FindGameObject(CGameObject * pGameObject) const
{
	list<class CGameObject*>::const_iterator iter;
	list<class CGameObject*>::const_iterator iterEnd = m_GameObjectList.end();
	for (iter = m_GameObjectList.begin(); iter != iterEnd; ++iter)
	{
		if ((*iter) == pGameObject)
		{
			return *iter;
		}
	}
	return NULL;
}

void CLayer::RemoveGameObject(CGameObject * gameObject)
{	
	list<class CGameObject*>::iterator iter;
	list<class CGameObject*>::iterator iterEnd = m_GameObjectList.end();
	for (iter = m_GameObjectList.begin(); iter != iterEnd;)
	{
		if ((*iter) == gameObject)
		{
			delete *iter;
			iter = m_GameObjectList.erase(iter);
		}
		else
			++iter;
	}	
}

void CLayer::AddGameObject(CGameObject * gameObject)
{
	//프로토타입에 Scene이 설정되어 있을리 없다.

	gameObject->SetLayer(this);	
	gameObject->SetScene(m_pScene);
	m_GameObjectList.push_back(gameObject);
}
bool CLayer::VerticalSort(CGameObject * pO1, CGameObject * pO2)
{
	return pO1->m_pTransform->GetPosition().y < pO2->m_pTransform->GetPosition().y;
}
void CLayer::Initialize()
{
	list<CGameObject*>::iterator iter;
	list<CGameObject*>::iterator iterEnd = m_GameObjectList.end();

	for (iter = m_GameObjectList.begin(); iter != iterEnd; ++iter)
	{
		(*iter)->Initialize();
	}
}

void CLayer::Start()
{
	list<CGameObject*>::iterator iter;
	list<CGameObject*>::iterator iterEnd = m_GameObjectList.end();

	for (iter = m_GameObjectList.begin(); iter != iterEnd; ++iter)
	{
		(*iter)->Start();
	}
}

void CLayer::Update()
{
	list<CGameObject*>::iterator iter;
	list<CGameObject*>::iterator iterEnd = m_GameObjectList.end();

	for (iter = m_GameObjectList.begin(); iter != iterEnd;)
	{
		if ((*iter)->GetDestroy())
		{
			(*iter)->Update();
			delete *iter;
			iter = m_GameObjectList.erase(iter);
		}
		else
		{
			(*iter)->Update();
			++iter;
		}
	}

	//ySort는 여기서 함.

	m_GameObjectList.sort(CLayer::VerticalSort);
}

void CLayer::Render()
{
	list<CGameObject*>::iterator iter;
	list<CGameObject*>::iterator iterEnd = m_GameObjectList.end();
	for (iter = m_GameObjectList.begin(); iter != iterEnd; ++iter)
	{
		(*iter)->Render();
	}
}

void CLayer::LateUpdate()
{
	list<CGameObject*>::iterator iter;
	list<CGameObject*>::iterator iterEnd = m_GameObjectList.end();

	for (iter = m_GameObjectList.begin(); iter != iterEnd;)
	{
		if ((*iter)->GetDestroy())
		{
			(*iter)->LateUpdate();
			delete *iter;
			iter = m_GameObjectList.erase(iter);
		}
		else
		{
			(*iter)->LateUpdate();
			++iter;
		}
	}
}

CLayer::CLayer():
	m_pScene(NULL)
{
}


CLayer::~CLayer()
{
	list<class CGameObject*>::iterator iter;
	list<class CGameObject*>::iterator iterEnd = m_GameObjectList.end();
	for (iter = m_GameObjectList.begin(); iter != iterEnd;++iter)
	{
		delete *iter;
	}
	m_GameObjectList.clear();
}

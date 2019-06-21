#include "GameObject.h"
#include "Component.h"
#include "Scene.h"
#include "Layer.h"
#include "Core.h"
#include "Components\TextureRenderer.h"
#include "Texture.h"
#include "ResourceManager.h"
#include "Components\Transform.h"
#include "SceneManager.h"
#include "Components\EllipseRenderer.h"
#include "Components\Cursor.h"
#include "InfoPanelManager.h"
#include "ConsoleButtonManager.h"
#include "Components\UnitInfo.h"




void CGameObject::SetLayer(const string & strLayer)
{
	CLayer* pLayer = m_pScene->FindLayer(strLayer);
	if (pLayer)
	{		
		if (!pLayer->FindGameObject(this))
		{
			m_pLayer = pLayer;
			pLayer->AddGameObject(this);			
		}
		else
		{
			m_pLayer = pLayer;
		}			
	}	
}

void CGameObject::SetDestroy(bool bDestroy)
{	
	m_bDestory = bDestroy;
	CCursor* pCursor = m_pScene->GetLayer("System")->FindGameObject("Cursor")->GetComponent<CCursor>();

	if (pCursor->ContainedInSelectedUnit(this))
	{
		pCursor->RemoveSelectedUnit(this);
		int iRemainedSize = pCursor->GetSelectedUnitList().size();
		if (iRemainedSize == 0)
		{
			GET_SINGLE(CConsoleButtonManager)->UpdateControlPanel(NULL);
			GET_SINGLE(CInfoPanelManager)->ClearInfoPanel();
			//버튼도 업데이트 해줘야하나?
		}
		else if (iRemainedSize == 1)
		{
			GET_SINGLE(CConsoleButtonManager)->UpdateControlPanel(*pCursor->GetSelectedUnitList().begin());
			GET_SINGLE(CInfoPanelManager)->UpdateInfoPanel((*pCursor->GetSelectedUnitList().begin())->GetComponent<CUnitInfo>());
		}
		else
		{
			GET_SINGLE(CConsoleButtonManager)->UpdateControlPanel(*pCursor->GetSelectedUnitList().begin());
			GET_SINGLE(CInfoPanelManager)->UpdateInfoPanel(pCursor->GetSelectedUnitList());
		}
	}	
}

void CGameObject::Initialize()
{
	list<CComponent*>::iterator iter;
	list<CComponent*>::iterator iterEnd = m_ComponentList.end();
	for (iter = m_ComponentList.begin(); iter != iterEnd; ++iter)
	{
		if ((*iter)->GetEnable() && !(*iter)->GetDestroy() && !(*iter)->GetStart())
		{
			(*iter)->Start();
			(*iter)->SetStart(true);
		}
	}
}

void CGameObject::Start()
{
	list<CComponent*>::iterator iter;
	list<CComponent*>::iterator iterEnd = m_ComponentList.end();
	for (iter = m_ComponentList.begin(); iter != iterEnd; )
	{
		if ((*iter)->GetEnable() && !(*iter)->GetStart())
		{
			(*iter)->Start();
			(*iter)->SetStart(true);
			++iter;
		}
		else if ((*iter)->GetDestroy())
		{
			delete *iter;
			iter = m_ComponentList.erase(iter);
		}
		else
			++iter;
	}
}

void CGameObject::Update()
{
	list<CComponent*>::iterator iter;
	list<CComponent*>::iterator iterEnd = m_ComponentList.end();
	for (iter = m_ComponentList.begin(); iter != iterEnd;)
	{
		if ((*iter)->GetEnable() && !(*iter)->GetDestroy())
		{
			(*iter)->Update();
			++iter;
		}
		else if ((*iter)->GetDestroy())
		{
			delete *iter;
			iter = m_ComponentList.erase(iter);
		}
		else
			++iter;

	}
}

void CGameObject::Render()
{
	if (m_pRendererList.size() != 0)
	{
		list<CRenderer*>::iterator iter;
		list<CRenderer*>::iterator iterEnd = m_pRendererList.end();
		
		for (iter = m_pRendererList.begin(); iter != iterEnd; ++iter)
		{
			if ((*iter)->GetEnable())
			{
				(*iter)->Render();
			}
		}
	}
}

void CGameObject::LateUpdate()
{
	list<CComponent*>::iterator iter;
	list<CComponent*>::iterator iterEnd = m_ComponentList.end();
	for (iter = m_ComponentList.begin(); iter != iterEnd;)
	{
		if ((*iter)->GetEnable() && !(*iter)->GetDestroy())
		{
			(*iter)->LateUpdate();
			++iter;
		}
		else if ((*iter)->GetDestroy())
		{
			delete *iter;
			iter = m_ComponentList.erase(iter);
		}
		else
			++iter;

	}
}

void CGameObject::CollisionEnter()
{
	list<CComponent*>::iterator iter;
	list<CComponent*>::iterator iterEnd = m_ComponentList.end();
	for (iter = m_ComponentList.begin(); iter != iterEnd;)
	{
		if ((*iter)->GetEnable() && !(*iter)->GetDestroy() && !(*iter)->GameObject()->GetDestroy())
		{
			(*iter)->CollisionEnter();
			++iter;
		}
		else if ((*iter)->GetDestroy() && !(*iter)->GameObject()->GetDestroy())
		{
			delete *iter;
			iter = m_ComponentList.erase(iter);
		}
		else
			++iter;
	}
}

void CGameObject::CollisionStay()
{
	list<CComponent*>::iterator iter;
	list<CComponent*>::iterator iterEnd = m_ComponentList.end();
	for (iter = m_ComponentList.begin(); iter != iterEnd;)
	{
		if ((*iter)->GetEnable() && !(*iter)->GetDestroy() && !(*iter)->GameObject()->GetDestroy())
		{
			(*iter)->CollisionStay();
			++iter;
		}
		else if ((*iter)->GetDestroy() && !(*iter)->GameObject()->GetDestroy())
		{
			delete *iter;
			iter = m_ComponentList.erase(iter);
		}
		else
			++iter;
	}
}

void CGameObject::CollisionExit()
{
	list<CComponent*>::iterator iter;
	list<CComponent*>::iterator iterEnd = m_ComponentList.end();
	for (iter = m_ComponentList.begin(); iter != iterEnd;)
	{
		if ((*iter)->GetEnable() && !(*iter)->GetDestroy() && !(*iter)->GameObject()->GetDestroy())
		{
			(*iter)->CollisionExit();
			++iter;
		}
		else if ((*iter)->GetDestroy() && !(*iter)->GameObject()->GetDestroy())
		{
			delete *iter;
			iter = m_ComponentList.erase(iter);
		}
		else
			++iter;
	}
}

//레이어에 자동으로 추가됨
CGameObject * CGameObject::clone()
{ 
	return new CGameObject(*this);
}

CGameObject::CGameObject(const CGameObject & gameObject) :
	m_pParent(NULL),
	m_bDestory(false),
	m_pLayer(NULL),
	m_pScene(NULL)
{
	{ // 기본으로 생성 시 Transform이 들어가 있으므로;
		m_pRendererList.clear();
		list<CComponent*>::iterator iter;
		list<CComponent*>::iterator iterEnd = m_ComponentList.end();
		for (iter = m_ComponentList.begin(); iter != iterEnd; ++iter)
		{
			(*iter)->Destroy();
			delete (*iter);
		}
		m_ComponentList.clear();
	}
	
	m_strKey = gameObject.m_strKey;
	m_pParent = gameObject.m_pParent;
	{
		list<CGameObject*>::const_iterator iter;
		list<CGameObject*>::const_iterator iterEnd = gameObject.m_ChildrenList.end();
		for (iter = gameObject.m_ChildrenList.begin(); iter != iterEnd; ++iter)
		{
			m_ChildrenList.push_back((*iter)->clone());
		}
	}
	{
		list<CComponent*>::const_iterator iter;
		list<CComponent*>::const_iterator iterEnd = gameObject.m_ComponentList.end();
		for (iter = gameObject.m_ComponentList.begin(); iter != iterEnd; ++iter)
		{
			m_ComponentList.push_back((*iter)->clone());		
		}
	}

	m_pTransform = GetComponent<CTransform>();
	m_pRendererList = GetComponents<CRenderer>();
	m_pLayer = gameObject.m_pLayer;
	m_pScene = gameObject.m_pScene;
	m_strName = gameObject.m_strName;

	if(m_pLayer)
		m_pLayer->AddGameObject(this);
	
	list<CCollider*> collider = GetComponents<CCollider>();
	{
		list<CCollider*>::iterator iter;
		list<CCollider*>::iterator iterEnd = collider.end();
		for (iter = collider.begin(); iter != iterEnd; ++iter)
		{
			CScene* pScene = GET_SINGLE(CSceneManager)->GetCurrentScene();
			pScene->AddCollider(*iter);
		}
	}


	list<CComponent*>::iterator iter;
	list<CComponent*>::iterator iterEnd = m_ComponentList.end();
	for (iter = m_ComponentList.begin(); iter != iterEnd; ++iter)
	{
		(*iter)->SetGameObject(this);
		(*iter)->m_pTransform = m_pTransform;
	}
}

CGameObject::CGameObject(const string & strName) :
	m_pParent(NULL),
	m_bDestory(false),
	m_pLayer(NULL),
	m_pScene(NULL),
	m_bSelected(false),
	m_bAirUnit(false),
	m_pPilot(NULL)
{
	m_pRendererList.clear();
	m_strName = strName;	
	m_pTransform = AddComponent<CTransform>();
}

CGameObject::CGameObject():
	m_pParent(NULL),
	m_bDestory(false),
	m_pLayer(NULL),
	m_pScene(NULL),
	m_bSelected(false),
	m_bAirUnit(false),
	m_pPilot(NULL)
{
	m_pRendererList.clear();
	m_strName = "GameObject";
	m_pTransform = AddComponent<CTransform>();
}


CGameObject::~CGameObject()
{
	m_pRendererList.clear();

	list<CComponent*>::iterator iter;
	list<CComponent*>::iterator iterEnd = m_ComponentList.end();

	for (iter = m_ComponentList.begin(); iter != iterEnd; ++iter)
	{
		(*iter)->Destroy();
		delete (*iter);
	}
	m_ComponentList.clear();
}

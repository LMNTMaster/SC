#include "Scene.h"
#include "Layer.h"
#include "GameObject.h"
#include "Component.h"
#include "Components\Transform.h"
#include "Components\Camera.h"
#include "Components\CollisionTile.h"
#include "Collider.h"
#include "Core.h"
#include "Components\ButtonCollider.h"
#include "Tile.h"
#include "Components\TerrainRenderer.h"
#include "Components\Player.h"

CLayer * CScene::CreateLayer(const string& strLayerName, int zOrder)
{
	CLayer* pLayer = new CLayer;
	pLayer->SetName(strLayerName);
	pLayer->SetZOrder(zOrder);
	pLayer->SetScene(this);
	return pLayer;
}

CLayer * CScene::GetLayer(const string& strLayerName) const
{
	list<CLayer*>::const_iterator iter;
	list<CLayer*>::const_iterator iterEnd = m_LayerList.end();
	for (iter = m_LayerList.begin(); iter != iterEnd; ++iter)
	{
		if ((*iter)->GetName() == strLayerName)
		{
			return *iter;
		}
	}
	return NULL;
}

void CScene::AddLayer(CLayer * pLayer)
{
	list<CLayer*>::iterator iter;
	list<CLayer*>::iterator iterEnd = m_LayerList.end();

	for (iter = m_LayerList.begin(); iter != iterEnd; ++iter)
	{
		if ((*iter) == pLayer)
		{
			return;
		}
	}
	m_LayerList.push_back(pLayer);

	if(m_LayerList.size() >= 2)
		m_LayerList.sort(CScene::LayerSort);
}


void CScene::SetPlayerRandomColor()
{
	srand(time(0));
	TEAM_COLOR arr[8] = {};
	for (int i = 0; i < 8; ++i)
	{
		arr[i] = (TEAM_COLOR)i;
	}

	for (int i = 0; i < 50; ++i)
	{
		int idx1 = rand() % 8;
		int idx2 = rand() % 8;

		TEAM_COLOR temp = arr[idx1];
		arr[idx1] = arr[idx2];
		arr[idx2] = temp;
	}

	for (int i = 0; i < m_vecPlayer.size(); ++i)
	{
		m_vecPlayer[i]->SetTeamColor(arr[i]);
	}
}

bool CScene::LayerSort(CLayer * pL1, CLayer * pL2)
{
	return pL1->GetZOrder() < pL2->GetZOrder();
}

void CScene::ClearContainUnitList()
{
	int iSize = m_GridSize.x * m_GridSize.y;
	for (int i = 0; i < iSize; ++i)
	{
		m_pTerrainRenderer->GetTile(i)->ClearList();
	}
}

CTile * CScene::GetTileByIndex(int idx)
{	
	return m_pTerrainRenderer->GetTile(idx);
}

void CScene::SortLayer()
{
	m_LayerList.sort(CScene::LayerSort);
}

CLayer * CScene::FindLayer(const string & strLayerName) const
{	
	list<class CLayer*>::const_iterator iter;
	list<class CLayer*>::const_iterator iterEnd = m_LayerList.end();

	for (iter = m_LayerList.begin(); iter != iterEnd; ++iter)
	{			
		if ((*iter)->GetName() == strLayerName)
		{
			return *iter;
		}
	}
	return NULL;	
}

void CScene::Initialize()
{
	list<CLayer*>::iterator iter;
	list<CLayer*>::iterator iterEnd = m_LayerList.end();

	for (iter = m_LayerList.begin(); iter != iterEnd; ++iter)
	{
		(*iter)->Initialize();
	}
}

void CScene::Start()
{
	list<CLayer*>::iterator iter;
	list<CLayer*>::iterator iterEnd = m_LayerList.end();

	for (iter = m_LayerList.begin(); iter != iterEnd; ++iter)
	{
		(*iter)->Start();
	}
}

void CScene::Update()
{
	list<CLayer*>::iterator iter;
	list<CLayer*>::iterator iterEnd = m_LayerList.end();

	for (iter = m_LayerList.begin(); iter != iterEnd; ++iter)
	{
		(*iter)->Update();
	}
}

void CScene::Render()
{
	list<CLayer*>::iterator iter;
	list<CLayer*>::iterator iterEnd = m_LayerList.end();
	for (iter = m_LayerList.begin(); iter != iterEnd; ++iter)
	{

		(*iter)->Render();
	}
}

void CScene::LateUpdate()
{
	list<CLayer*>::iterator iter;
	list<CLayer*>::iterator iterEnd = m_LayerList.end();

	for (iter = m_LayerList.begin(); iter != iterEnd; ++iter)
	{
		(*iter)->LateUpdate();
	}
}

void CScene::Collision()
{
	//ButtonCollider 확인
	//이 경우 반드시 Cursor와의 충돌밖에 없으므로, 커서의 위치만 가지고 확인 하도록 한다.

	POINT tCursorPosition;
	GetCursorPos(&tCursorPosition);
	ScreenToClient(GET_SINGLE(CCore)->GetWindowHandle(), &tCursorPosition);

	list<CButtonCollider*>::iterator iter;
	list<CButtonCollider*>::iterator iterEnd = m_ButtonColliderList.end();

	for (iter = m_ButtonColliderList.begin(); iter != iterEnd; ++iter)
	{
			if ((*iter)->GetEnable())
			{
				CVector2 LT = (*iter)->GetLT();
				CVector2 RB = (*iter)->GetRB();
				bool isCollided = (*iter)->GetCollision();
				if (tCursorPosition.x < LT.x)
				{
					if (isCollided)
					{
						//이전에 충돌했었고, 현재 충돌중이지 않으면
						(*iter)->GameObject()->CollisionExit();
						(*iter)->SetCollision(false);
					}
					continue;
				}
				if (tCursorPosition.x > RB.x)
				{
					if (isCollided)
					{
						//이전에 충돌했었고, 현재 충돌중이지 않으면
						(*iter)->GameObject()->CollisionExit();
						(*iter)->SetCollision(false);
					}
					continue;
				}
				if (tCursorPosition.y < LT.y)
				{
					if (isCollided)
					{
						//이전에 충돌했었고, 현재 충돌중이지 않으면
						(*iter)->GameObject()->CollisionExit();
						(*iter)->SetCollision(false);
					}
					continue;
				}
				if (tCursorPosition.y > RB.y)
				{
					if (isCollided)
					{
						//이전에 충돌했었고, 현재 충돌중이지 않으면
						(*iter)->GameObject()->CollisionExit();
						if ((*iter)->GetEnable())
						{
							(*iter)->SetCollision(true);
						}
					}
					continue;
				}

				if (!isCollided)
				{
					//이전에 충돌하지 않았고, 현재 충돌중이면
					(*iter)->GameObject()->CollisionEnter();
					if ((*iter)->GetEnable())
					{
						(*iter)->SetCollision(true);
					}
				}
				else
				{
					//이전에도 충돌 했고, 현재도 충돌중이면
					(*iter)->GameObject()->CollisionStay();	
					if ((*iter)->GetEnable())
					{
						(*iter)->SetCollision(true);
					}			
				}
			}
		
	}


	for (iter = m_ButtonColliderList.begin(); iter != iterEnd; )
	{
		if (!(*iter)->GetEnable())
		{
			iter = m_ButtonColliderList.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}



CScene::CScene()
{
	CLayer* pDefaultLayer = CreateLayer("Default", 0);
	pDefaultLayer->SetScene(this);
	AddLayer(pDefaultLayer);

	CGameObject* pMainCamera = new CGameObject("MainCamera");
	pDefaultLayer->AddGameObject(pMainCamera);
	CCamera* pCamera = pMainCamera->AddComponent<CCamera>();
	pMainCamera->GetTransform()->SetPosition(CVector2(0, 0));

	m_pCamera = pCamera;
}


CScene::~CScene()
{
	list<CLayer*>::iterator iter;
	list<CLayer*>::iterator iterEnd = m_LayerList.end();

	for (iter = m_LayerList.begin(); iter != iterEnd; ++iter)
	{
		delete *iter;
	}
	m_LayerList.clear();
}

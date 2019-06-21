#include "SystemManager.h"
#include "../ResourceManager.h"
#include "../Texture.h"
#include "../Core.h"
#include "Transform.h"
#include "../GameObject.h"
#include "../Scene.h"
#include "Camera.h"
#include "SpriteRenderer.h"
#include "../Layer.h"
#include "RectangleRenderer.h"
#include "RectCollider.h"
#include "EllipseRenderer.h"
#include "../Timer.h"
#include "../Option.h"

//TestCamera
#include "../Scenes/DefaultScene.h"

//Test Generate Unit
#include "CircleCollider.h"
#include "../Sprite.h"
#include "../FileStream.h"

#include "TestMove.h"

void CSystemManager::Update()
{
	m_pTransform->SetPivot(0.5f, 0.5f);
	CVector2 padding(30, 30);

	POINT pos;
	GetCursorPos(&pos);
	ScreenToClient(GET_SINGLE(CCore)->GetWindowHandle(), &pos);// 이걸로 카메라 이동 할거임

	//=========================================================
	//															카메라 이동
	//=========================================================
	CVector2 mapSize = dynamic_cast<CDefaultScene*>(m_pGameObject->GetScene())->GetGridSize();
	CVector2 moveMax;
	moveMax.x = mapSize.x * TILESIZE.x - GET_SINGLE(CCore)->GetScreenSize().x;
	moveMax.y = mapSize.y * TILESIZE.y - GET_SINGLE(CCore)->GetScreenSize().y;
	CVector2 cameraPosition = m_pGameObject->GetScene()->GetCamera()->Transform()->GetPosition();

	int screenWidth = GET_SINGLE(CCore)->GetScreenSize().x;
	int screenHeight = GET_SINGLE(CCore)->GetScreenSize().y;
	
	//Cursor 의 AnimationClip 바꿔주려면 8방향을 따로 계산해야함
	//Left
	if (pos.x > 0 && pos.x < padding.x && pos.y > padding.y && pos.y < screenHeight - padding.y )
	{
		m_pGameObject->GetComponent<CSpriteRenderer>()->ChangeCurrentClip("LeftEdge");
		CVector2 direction = CVector2(-1, 0);
		cameraPosition += direction * GET_SINGLE(COption)->GetCameraSpeed() * GET_SINGLE(CTimer)->GetDeltaTime();		
		
		if (cameraPosition.x < 0)
			cameraPosition.x= 0;

		m_pGameObject->GetScene()->GetCamera()->Transform()->SetPosition(cameraPosition);
	}
	//Top
	else if (pos.x > padding.x && pos.x < screenWidth - padding.x && pos.y < padding.y && pos.y > 0)
	{
		m_pGameObject->GetComponent<CSpriteRenderer>()->ChangeCurrentClip("TopEdge");
		CVector2 direction = CVector2(0, -1);
		cameraPosition += direction * GET_SINGLE(COption)->GetCameraSpeed() * GET_SINGLE(CTimer)->GetDeltaTime();
		
		if (cameraPosition.y < 0)
			cameraPosition.y = 0;

		m_pGameObject->GetScene()->GetCamera()->Transform()->SetPosition(cameraPosition);
	}
	//Right
	else if (pos.x < screenWidth && pos.x > screenWidth - padding.x && pos.y > padding.y && pos.y < screenHeight - padding.y)
	{
		m_pGameObject->GetComponent<CSpriteRenderer>()->ChangeCurrentClip("RightEdge");
		CVector2 direction = CVector2(1, 0);
		cameraPosition += direction * GET_SINGLE(COption)->GetCameraSpeed() * GET_SINGLE(CTimer)->GetDeltaTime();
		
		if (cameraPosition.x > moveMax.x)
			cameraPosition.x = moveMax.x;

		m_pGameObject->GetScene()->GetCamera()->Transform()->SetPosition(cameraPosition);
	}
	//Bottom
	else if (pos.x > padding.x && pos.x < screenWidth - padding.x && pos.y > screenHeight - padding.y && pos.y < screenHeight)
	{
		m_pGameObject->GetComponent<CSpriteRenderer>()->ChangeCurrentClip("BottomEdge");
		CVector2 direction = CVector2(0, 1);
		cameraPosition += direction * GET_SINGLE(COption)->GetCameraSpeed() * GET_SINGLE(CTimer)->GetDeltaTime();

		if (cameraPosition.y > moveMax.y)
			cameraPosition.y = moveMax.y;

		m_pGameObject->GetScene()->GetCamera()->Transform()->SetPosition(cameraPosition);
	}
	//TopLeft
	else if (pos.x > 0 && pos.x < padding.x && pos.y > 0 && pos.y < padding.y)
	{
		m_pGameObject->GetComponent<CSpriteRenderer>()->ChangeCurrentClip("LeftTopEdge");
		CVector2 direction = CVector2(-1, -1).normalize();
		cameraPosition += direction * GET_SINGLE(COption)->GetCameraSpeed() * GET_SINGLE(CTimer)->GetDeltaTime();

		if (cameraPosition.x < 0)
			cameraPosition.x = 0;

		if (cameraPosition.y < 0)
			cameraPosition.y = 0;

		m_pGameObject->GetScene()->GetCamera()->Transform()->SetPosition(cameraPosition);
	}
	//TopRight
	else if (pos.x < screenWidth && pos.x > screenWidth - padding.x && pos.y > 0 && pos.y < padding.y)
	{
		m_pGameObject->GetComponent<CSpriteRenderer>()->ChangeCurrentClip("RightTopEdge");
		CVector2 direction = CVector2(1, -1).normalize();
		cameraPosition += direction * GET_SINGLE(COption)->GetCameraSpeed() * GET_SINGLE(CTimer)->GetDeltaTime();

		if (cameraPosition.y < 0)
			cameraPosition.y = 0;

		if (cameraPosition.x > moveMax.x)
			cameraPosition.x = moveMax.x;

		m_pGameObject->GetScene()->GetCamera()->Transform()->SetPosition(cameraPosition);
	}
	//LeftBottom
	else if (pos.x > 0 && pos.x < padding.x && pos.y < screenHeight && pos.y > screenHeight - padding.y)
	{
		m_pGameObject->GetComponent<CSpriteRenderer>()->ChangeCurrentClip("LeftBottomEdge");
		CVector2 direction = CVector2(-1, 1).normalize();
		cameraPosition += direction * GET_SINGLE(COption)->GetCameraSpeed() * GET_SINGLE(CTimer)->GetDeltaTime();

		if (cameraPosition.x < 0)
			cameraPosition.x = 0;

		if (cameraPosition.y > moveMax.y)
			cameraPosition.y = moveMax.y;

		m_pGameObject->GetScene()->GetCamera()->Transform()->SetPosition(cameraPosition);
	}
	else if (pos.x < screenWidth && pos.x > screenWidth - padding.x && pos.y < screenHeight && pos.y > screenHeight - padding.y)
	{
		m_pGameObject->GetComponent<CSpriteRenderer>()->ChangeCurrentClip("RightBottomEdge");
		CVector2 direction = CVector2(1, 1).normalize();
		cameraPosition += direction * GET_SINGLE(COption)->GetCameraSpeed() * GET_SINGLE(CTimer)->GetDeltaTime();
		m_pGameObject->GetScene()->GetCamera()->Transform()->SetPosition(cameraPosition);
	}
	else
	{
		if (!m_bLeftButtonClicked)
		{
			m_pGameObject->GetComponent<CSpriteRenderer>()->ChangeCurrentClip("CursorNormal");
		}	
	}

	//=========================================================
	//=========================================================



	m_CurrentMousePosition = CVector2(pos.x, pos.y);
	m_CurrentMouseWorldPosition = m_CurrentMousePosition + cameraPosition;
	m_pTransform->SetPosition(m_CurrentMouseWorldPosition);

	if (!m_bLeftButtonClicked)
	{
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		{
			m_bLeftButtonClicked = true;			
			m_ClickedMousePosition = m_CurrentMouseWorldPosition;
			GameObject()->GetComponent<CSpriteRenderer>()->ChangeCurrentClip("CursorRange");
			if (m_pRectRenderer)
			{
				CRectangleRenderer* pRenderer = m_pRectRenderer->GetComponent<CRectangleRenderer>();			
				
				if (pRenderer)
				{
					pRenderer->SetEnable(true);
				}
			}
		}
	}
	else
	{
		if (!(GetAsyncKeyState(VK_LBUTTON) & 0x8000))
		{
			
			list<CGameObject*>::iterator iter;
			list<CGameObject*>::iterator iterEnd = m_SelectUnitList.end();
			for (iter = m_SelectUnitList.begin(); iter != iterEnd; ++iter)
			{
				(*iter)->GetComponent<CTestMove>()->SetSelected(false);
			}

			m_SelectUnitList.clear();


			CVector2 LT;
			CVector2 RB;

			if (m_ClickedMousePosition.x <= m_CurrentMouseWorldPosition.x)
			{
				LT.x = m_ClickedMousePosition.x;
				RB.x = m_CurrentMouseWorldPosition.x;
			}
			else
			{
				LT.x = m_CurrentMouseWorldPosition.x;
				RB.x = m_ClickedMousePosition.x;
			}

			if (m_ClickedMousePosition.y <= m_CurrentMouseWorldPosition.y)
			{
				LT.y = m_ClickedMousePosition.y;
				RB.y = m_CurrentMousePosition.y;
			}
			else
			{
				LT.y = m_CurrentMousePosition.y;
				RB.y = m_ClickedMousePosition.y;
			}


			GameObject()->GetComponent<CSpriteRenderer>()->ChangeCurrentClip("CursorNormal");
			if (m_pRectRenderer)
			{
				CRectangleRenderer* pRenderer = m_pRectRenderer->GetComponent<CRectangleRenderer>();
				if (pRenderer)
				{
					pRenderer->SetEnable(false);

					list<CGameObject*> unitList;

					unitList.insert(unitList.begin(), m_pGameObject->GetScene()->GetLayer("Ground Unit")->GetAllUnit().begin(), m_pGameObject->GetScene()->GetLayer("Ground Unit")->GetAllUnit().end());
					unitList.insert(unitList.begin(), m_pGameObject->GetScene()->GetLayer("Air Unit")->GetAllUnit().begin(), m_pGameObject->GetScene()->GetLayer("Air Unit")->GetAllUnit().end());
					
					list<CGameObject*>::iterator iter;
					list<CGameObject*>::iterator iterEnd = unitList.end();

					for (iter = unitList.begin(); iter != iterEnd; ++iter)
					{
						CVector2 unitPosition = (*iter)->GetTransform()->GetPosition();

						//Rect충돌 -> list 추가
						if (unitPosition.x < LT.x)
							continue;
						else if (unitPosition.x > RB.x)
							continue;
						else if (unitPosition.y < LT.y)
							continue;
						else if (unitPosition.y > RB.y)
							continue;
						else
						{
							m_SelectUnitList.push_back(*iter);
							(*iter)->GetComponent<CTestMove>()->SetSelected(true);
						}							
					}
				}
			}

			m_bLeftButtonClicked = false;
			m_ClickedMousePosition = CVector2();
		}
	}

	if (m_bLeftButtonClicked)
	{
		if (!m_pRectRenderer)
		{
			m_pRectRenderer = new CGameObject;
			m_pGameObject->GetScene()->FindLayer("UI Background")->AddGameObject(m_pRectRenderer);
		}

		CRectangleRenderer* pRenderer = m_pRectRenderer->GetComponent<CRectangleRenderer>();
		if (!pRenderer)
		{
			pRenderer = m_pRectRenderer->AddComponent<CRectangleRenderer>();
		}
		else
		{
			pRenderer->SetEnable(true);
		}
		pRenderer->SetColor(RGB(30, 140, 30));
		pRenderer->SetStartPosition(m_ClickedMousePosition);
		pRenderer->SetEndPosition(m_CurrentMousePosition);
		pRenderer->SetThickness(2);
		m_pRectRenderer->GetTransform()->SetPosition((m_CurrentMousePosition + m_ClickedMousePosition) / 2);
	}
	
}

void CSystemManager::SaveComponent(FILE * pFile)
{
}

void CSystemManager::LoadComponent(FILE * pFile)
{
}

CComponent * CSystemManager::clone()
{
	return new CSystemManager(*this);
}

CSystemManager::CSystemManager(const CSystemManager & component):
	m_bLeftButtonClicked(false),
	m_pRectRenderer(NULL)
{
	m_eComponentType = CT_SYSTEM_MANAGER;
}

CSystemManager::CSystemManager():
	m_bLeftButtonClicked(false),
	m_pRectRenderer(NULL)
{
	m_eComponentType = CT_SYSTEM_MANAGER;
}


CSystemManager::~CSystemManager()
{
	
}

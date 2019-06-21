#include "Move.h"
#include "../VectorFieldManager.h"
#include "../VectorField.h"
#include "../GameObject.h"
#include "../Components/Transform.h"
#include "../Timer.h"
#include "../ResourceManager.h"
#include "../Texture.h"
#include "Camera.h"
#include "../Scene.h"
#include "../SceneManager.h"
#include "CircleCollider.h"
#include "TerrainRenderer.h"
#include "../Tile.h"
#include "SpriteRenderer.h"
#include "../ConsoleButton.h"
#include "../Components/Player.h"
#include "../ConsoleButtonManager.h"
#include "ControlButton.h"
#include "../SceneManager.h"
#include "Cursor.h"
#include "../Layer.h"
#include "Stop.h"
#include "Gather.h"


void CMove::AddUnitToTile()
{
	
		CScene* pScene = m_pGameObject->GetScene();
		CVector2 position = m_pTransform->GetPosition();
		CVector2 gridSize = pScene->GetGridSize();

		int iX = position.x / 32;
		int iY = position.y / 32;
		int idx = iY * gridSize.x + iX;
		int collisionRadius = (int)m_pGameObject->GetComponent<CCircleCollider>()->GetRadius();

		int maxLevel = collisionRadius / 32;


		for (int y = -maxLevel; y <= maxLevel; ++y)
		{
			for (int x = -maxLevel; x <= maxLevel; ++x)
			{
				//타일 범위 밖이면 연산하지 않음
				if (iX + x < 0 || iX + x > gridSize.x || iY + y < 0 || iY + y > gridSize.y)
				{
					continue;
				}

				//타일의 중심부터 유닛과의 거리가 충돌 범위 내에 있으면 추가함.
				int iTileIndex = idx + y * gridSize.x + x;

				CTile* pTile = pScene->GetTileByIndex(iTileIndex);
				CVector2 temp = pTile->GetWorldPosition() + CVector2(16, 16);
				temp -= position;
				float distance = temp.length();
				if (distance <= collisionRadius + 16)
				{
					pTile->AddUnit(m_pGameObject);
				}
			}
		}
	
}

void CMove::RequestMove(CVector2 worldPosition)
{
	//m_pGameObject->GetComponent<CStop>()->RequestStop();
	m_bStop = false;
	m_TargetPosition = worldPosition;
	m_bArrived = false;
	if(!m_pGameObject->IsAirUnit())
		m_pVectorField = GET_SINGLE(CVectorFieldManager)->RequestVectorField(worldPosition);	

}
void CMove::RequestMove(CVector2 worldPosition, bool bIsAir)
{
	//m_pGameObject->GetComponent<CStop>()->RequestStop();
	m_TargetPosition = worldPosition;
	m_bArrived = false;
	m_bStop = false;

	if(!m_pGameObject->IsAirUnit())
		m_pVectorField = GET_SINGLE(CVectorFieldManager)->RequestVectorField(worldPosition);
}

void CMove::Start()
{

	m_pButton = new CConsoleButton;
	m_pGameObject->AddButton(m_pButton);
	m_pButton->SetRequireCursor(true);
	m_pButton->SetButtonName("Move");
	m_pButton->SetPanelIndex(0);
	m_pButton->SetShortcutKey('M');
	m_pButton->SetUpIconTexture(GET_SINGLE(CResourceManager)->FindTexture("ControlButton_Icon_Move_Normal"));
	m_pButton->SetDownIconTexture(GET_SINGLE(CResourceManager)->FindTexture("ControlButton_Icon_Move_Pressed"));
	m_pButton->SetButtonComponent(this);

	auto func = [&]( CVector2 position, CGameObject* pTarget) 
	{
		if (pTarget == NULL)
		{
			RequestMove(position);
		}
		else
		{
			RequestMove(pTarget->GetTransform()->GetPosition());
		}

		GET_SINGLE(CConsoleButtonManager)->UpdateControlPanel(GET_SINGLE(CConsoleButtonManager)->GetTargetObject());
		//GET_SINGLE(CSceneManager)->GetCurrentScene()->FindLayer("System")->FindGameObject("Cursor")->GetComponent<CCursor>()->EndRequest();
	};

	m_pButton->SetFunction(func);

	vector<CConsoleButton*> vecNextPage;
	vecNextPage.resize(9);

	for (int i = 0; i < 9; ++i)
	{
		vecNextPage[i] = NULL;
	}

	//자동 해제
	CConsoleButton* pTempButton = new CConsoleButton;
	pTempButton->SetRequireCursor(false);
	pTempButton->SetButtonName("Cancel");
	pTempButton->SetPanelIndex(8);
	pTempButton->SetShortcutKey(VK_SPACE); 
	pTempButton->SetUpIconTexture(GET_SINGLE(CResourceManager)->FindTexture("ControlButton_Icon_Cancel_Normal"));
	pTempButton->SetDownIconTexture(GET_SINGLE(CResourceManager)->FindTexture("ControlButton_Icon_Cancel_Pressed"));
	pTempButton->SetButtonComponent(this);
	pTempButton->SetExistNextPage(false);

	auto nextPage = [&](CVector2 position, CGameObject* pTarget)
	{
		GET_SINGLE(CConsoleButtonManager)->UpdateControlPanel(m_pGameObject);
		GET_SINGLE(CSceneManager)->GetCurrentScene()->FindLayer("System")->FindGameObject("Cursor")->GetComponent<CCursor>()->EndRequest();
	};	

	vecNextPage[8] = pTempButton;


	pTempButton->SetFunction(nextPage);

	m_pButton->SetExistNextPage(true);
	m_pButton->SetNextPage(vecNextPage);
}

void CMove::Update()
{
	CTerrainRenderer* pTerrain = m_pGameObject->GetScene()->GetTerrainRenderer();

	AddUnitToTile();
	if (!m_bStop)
	{
		if (!m_bPause)
		{
			if (m_pGameObject->IsAirUnit())
			{
				if (m_TargetPosition != CVector2::zero())
				{
					CVector2 position = m_pTransform->GetPosition();
					CScene* scene = m_pGameObject->GetScene();
					float collisionRadius = m_pGameObject->GetComponent<CCircleCollider>()->GetRadius();
					CVector2 gridSize = scene->GetGridSize();
					float distance = (m_TargetPosition - position).length();

					if (distance > m_fStopThreshold)
					{
						m_bArrived = false;
						CVector2 direction = m_TargetPosition - position;
						direction = direction.normalize();
						position = position + direction * m_fMoveSpeed * GET_SINGLE(CTimer)->GetDeltaTime();
						m_pTransform->SetPosition(position);
						m_pTransform->SetRotation(-direction);
						m_pButton->SetButtonState(BS_DISABLE);
					}
					else
					{
						m_bArrived = true;
						m_TargetPosition = CVector2::zero();
						m_pButton->SetButtonState(BS_ENABLE);
					}


					int rtX = (position.x + collisionRadius) / 32;
					int rtY = (position.y - collisionRadius) / 32;
					int ltX = (position.x - collisionRadius) / 32;
					int ltY = (position.y - collisionRadius) / 32;
					int lbX = (position.x - collisionRadius) / 32;
					int lbY = (position.y + collisionRadius) / 32;
					int rbX = (position.x + collisionRadius) / 32;
					int rbY = (position.y + collisionRadius) / 32;

					int LT = ltY * (int)gridSize.x + ltX;
					int RT = rtY * (int)gridSize.x + rtX;
					int LB = lbY * (int)gridSize.x + lbX;
					int RB = rbY * (int)gridSize.x + rbX;

				}
		
			}
			else
			{
				CVector2 position = m_pTransform->GetPosition();
				CScene* scene = m_pGameObject->GetScene();
				float collisionRadius = m_pGameObject->GetComponent<CCircleCollider>()->GetRadius();
				CVector2 gridSize = scene->GetGridSize();


				int rtX = (position.x + collisionRadius) / 32;
				int rtY = (position.y - collisionRadius) / 32;
				int ltX = (position.x - collisionRadius) / 32;
				int ltY = (position.y - collisionRadius) / 32;
				int lbX = (position.x - collisionRadius) / 32;
				int lbY = (position.y + collisionRadius) / 32;
				int rbX = (position.x + collisionRadius) / 32;
				int rbY = (position.y + collisionRadius) / 32;
				int cX = position.x / 32;
				int cY = position.y / 32;


				int C = cY * (int)gridSize.x + cX;
				int LT = ltY * (int)gridSize.x + ltX;
				int RT = rtY * (int)gridSize.x + rtX;
				int LB = lbY * (int)gridSize.x + lbX;
				int RB = rbY * (int)gridSize.x + rbX;


				if (!m_bArrived)
				{
					CVector2 currentPosition = m_pGameObject->GetTransform()->GetPosition();

					float distance = (currentPosition - m_TargetPosition).length();

					if (distance >  m_fStopThreshold)
					{
						m_bArrived = false;
						m_pButton->SetButtonState(BS_DISABLE);
						CVector2 direction;

						if (m_pVectorField) 
						{
							direction = m_pVectorField->GetVector(C).normalize();
						}
						else
						{
							if (m_TargetPosition != CVector2())
							{
								m_pVectorField = GET_SINGLE(CVectorFieldManager)->RequestVectorField(m_TargetPosition);
								direction = m_pVectorField->GetVector(C).normalize();
							}
							else
							{
								assert(0);
							}
						}


						if (m_pVectorField->GetVector(LT) != CVector2::zero())
						{
							direction += m_pVectorField->GetVector(LT);
						}
						else
						{
							direction += CVector2(1, 1).normalize();
						}
						if (m_pVectorField->GetVector(RT) != CVector2::zero())
						{
							direction += m_pVectorField->GetVector(RT);
						}
						else
						{
							direction += CVector2(-1, 1).normalize();
						}
						if (m_pVectorField->GetVector(LB) != CVector2::zero())
						{
							direction += m_pVectorField->GetVector(LB);
						}
						else
						{
							direction += CVector2(1, -1).normalize();
						}
						if (m_pVectorField->GetVector(RB) != CVector2::zero())
						{
							direction += m_pVectorField->GetVector(RB);
						}
						else
						{
							direction += CVector2(-1, -1).normalize();
						}

						direction = direction.normalize();

						float unitCollisionRadius = m_pGameObject->GetComponent<CCircleCollider>()->GetRadius();
						int  forwardX = (int)(position.x + direction.x * unitCollisionRadius) / 32;
						int  forwardY = (int)(position.y + direction.y * unitCollisionRadius) / 32;
						int forwardIndex = forwardY * gridSize.x + forwardX;

						//유닛의 중심을 기준으로 이동 할 위치 방향에 유닛이 존재할 경우 잠시 정지
						//size > 1인 이유는 자기 자신은 항상 해당 타일에 존재하기 때문에.
						if (pTerrain->GetTile(forwardIndex)->GetContainUnitList().size() > 1)
						{
							//전방과 현재 타일의 유닛과 충돌 확인.
							list<CGameObject*> tempList = pTerrain->GetTile(forwardIndex)->GetContainUnitList();
						
							//현재 타일과 전방 타일이 다른 타일이면 충돌 확인할 리스트에 추가함
							if (C != forwardIndex)
							{
								tempList.insert(tempList.begin(), pTerrain->GetTile(C)->GetContainUnitList().begin(), pTerrain->GetTile(C)->GetContainUnitList().end());
							}

							list<CGameObject*>::const_iterator iter;
							list<CGameObject*>::const_iterator iterEnd = tempList.end();

							bool bMove = true;
							for (iter = tempList.begin(); iter != iterEnd; ++iter)
							{
								//자신이거나 공중 유닛일 경우 충돌하지 않음.
								if (*iter == m_pGameObject || (*iter)->IsAirUnit())
									continue;

								float targetRadius = (*iter)->GetComponent<CCircleCollider>()->GetRadius();
								CVector2 targetPosition = (*iter)->GetTransform()->GetPosition();
								CVector2 targetDirection = position - targetPosition ;
								float targetDistance = targetDirection.length();

								if ((targetPosition - position).length() > targetRadius + unitCollisionRadius)
								{
									//전방에 유닛이 있으나 충돌하지 않았다면, 이동함			
								}
								else
								{							
									if ((*iter)->GetComponent<CMove>())
									{
										if ((*iter)->GetComponent<CMove>()->m_bArrived && (*iter)->GetComponent<CMove>()->m_pVectorField == m_pVectorField)
										{
											//같은 위치를 이동 하는 중 먼저 도착한 유닛과 충돌했다면, 더이상 이동하지 않음.	
											bMove = false;
											m_bArrived = true;
											m_pButton->SetButtonState(BS_ENABLE);
										}
										else if (!(*iter)->GetComponent<CMove>()->m_bArrived && (*iter)->GetComponent<CMove>()->m_pVectorField != m_pVectorField)
										{
											//다른 곳으로 이동하는 유닛과 충돌했다면
											direction = CVector2();
										}
										else if (!(*iter)->GetComponent<CMove>()->m_bArrived && (*iter)->GetComponent<CMove>()->m_pVectorField == m_pVectorField)
										{
											//전방의 유닛이 현재 유닛과 같은 지점을 향해 이동 중일 때 아직 도착하지 않은 상태에서 충돌
											direction = CVector2();
										}
										else
										{
											//다른 정지해 있는 유닛과 충돌
											direction = direction + targetDirection.normalize();
											direction = direction.normalize();
										}
									}									
								}
							}

							if (bMove)
							{
								m_pTransform->SetRotation(direction * -1);
								currentPosition = currentPosition + direction * m_fMoveSpeed * GET_SINGLE(CTimer)->GetDeltaTime();
								m_pGameObject->GetTransform()->SetPosition(currentPosition);
							}
						}
						else
						{
							m_pTransform->SetRotation(direction * -1);
							currentPosition = currentPosition + direction * m_fMoveSpeed * GET_SINGLE(CTimer)->GetDeltaTime();
							m_pGameObject->GetTransform()->SetPosition(currentPosition);
						}
					}
					else
					{
						m_bArrived = true;
						m_pButton->SetButtonState(BS_ENABLE);
					}
				}
			}
		}
		else
		{
			CVector2 position = m_pTransform->GetPosition();
			CScene* scene = m_pGameObject->GetScene();
			float collisionRadius = m_pGameObject->GetComponent<CCircleCollider>()->GetTileCollisionRadius();
			CVector2 gridSize = scene->GetGridSize();

			int rtX = (position.x + collisionRadius) / 32;
			int rtY = (position.y - collisionRadius) / 32;
			int ltX = (position.x - collisionRadius) / 32;
			int ltY = (position.y - collisionRadius) / 32;
			int lbX = (position.x - collisionRadius) / 32;
			int lbY = (position.y + collisionRadius) / 32;
			int rbX = (position.x + collisionRadius) / 32;
			int rbY = (position.y + collisionRadius) / 32;
		
			int LT = ltY * (int)gridSize.x + ltX;
			int RT = rtY * (int)gridSize.x + rtX;
			int LB = lbY * (int)gridSize.x + lbX;
			int RB = rbY * (int)gridSize.x + rbX;

		}
	


		float fAngle = m_pTransform->GetRotation();

		if (fAngle >= 360)
		{
			fAngle -= 360;
		}
		if (fAngle <= 0)
		{
			fAngle += 360;
		}
		m_pTransform->SetRotation(fAngle);

		if (!m_bArrived)
		{
			//이동 모션 방향 따라 수정
			string unitName = m_pGameObject->GetName();

			CSpriteRenderer* pRenderer = m_pGameObject->GetComponent<CSpriteRenderer>();
			if (fAngle >= 0.0f && fAngle < 22.5f)
			{
				if (pRenderer->GetCurrentClipKey() != unitName + "Move12")
					pRenderer->ChangeCurrentClip(unitName + "Move12");
			}
			else if (fAngle >= 22.5f && fAngle < 45)
			{
				if (pRenderer->GetCurrentClipKey() != unitName + "Move13")
					pRenderer->ChangeCurrentClip(unitName + "Move13");
			}
			else if (fAngle >= 45.0f && fAngle < 67.5f)
			{
				if (pRenderer->GetCurrentClipKey() != unitName + "Move14")
					pRenderer->ChangeCurrentClip(unitName + "Move14");
			}
			else if (fAngle >= 67.5f && fAngle < 90.0f)
			{
				if (pRenderer->GetCurrentClipKey() != unitName + "Move15")
					pRenderer->ChangeCurrentClip(unitName + "Move15");
			}
			else if (fAngle >= 90.0f && fAngle < 112.5f)
			{
				if (pRenderer->GetCurrentClipKey() != unitName + "Move0")
					pRenderer->ChangeCurrentClip(unitName + "Move0");
			}
			else if (fAngle >= 112.5f && fAngle < 135.0f)
			{
				if (pRenderer->GetCurrentClipKey() != unitName + "Move1")
					pRenderer->ChangeCurrentClip(unitName + "Move1");
			}
			else if (fAngle >= 135.0f && fAngle < 157.5f)
			{
				if (pRenderer->GetCurrentClipKey() != unitName + "Move2")
					pRenderer->ChangeCurrentClip(unitName + "Move2");
			}
			else if (fAngle >= 157.5f && fAngle < 180.0f)
			{
				if (pRenderer->GetCurrentClipKey() != unitName + "Move3")
					pRenderer->ChangeCurrentClip(unitName + "Move3");
			}
			else if (fAngle >= 180.0f && fAngle < 202.5f)
			{
				if (pRenderer->GetCurrentClipKey() != unitName + "Move4")
					pRenderer->ChangeCurrentClip(unitName + "Move4");
			}
			else if (fAngle >= 202.5f && fAngle < 225.0f)
			{
				if (pRenderer->GetCurrentClipKey() != unitName + "Move5")
					pRenderer->ChangeCurrentClip(unitName + "Move5");
			}
			else if (fAngle >= 225.0f && fAngle < 247.5f)
			{
				if (pRenderer->GetCurrentClipKey() != unitName + "Move6")
					pRenderer->ChangeCurrentClip(unitName + "Move6");
			}
			else if (fAngle >= 247.5f && fAngle < 270.0f)
			{
				if (pRenderer->GetCurrentClipKey() != unitName + "Move7")
					pRenderer->ChangeCurrentClip(unitName + "Move7");
			}
			else if (fAngle >= 270.0f && fAngle < 292.5f)
			{
				if (pRenderer->GetCurrentClipKey() != unitName + "Move8")
					pRenderer->ChangeCurrentClip(unitName + "Move8");
			}
			else if (fAngle >= 292.5f && fAngle < 315.0f)
			{
				if (pRenderer->GetCurrentClipKey() != unitName + "Move9")
					pRenderer->ChangeCurrentClip(unitName + "Move9");
			}
			else if (fAngle >= 315.0f && fAngle < 337.5f)
			{
				if (pRenderer->GetCurrentClipKey() != unitName + "Move10")
					pRenderer->ChangeCurrentClip(unitName + "Move10");
			}
			else if (fAngle >= 337.5f && fAngle < 360)
			{
				if (pRenderer->GetCurrentClipKey() != unitName + "Move11")
					pRenderer->ChangeCurrentClip(unitName + "Move11");
			}
		}
		else
		{
			if (m_pGameObject->GetComponent<CGather>())
			{
				if(m_pGameObject->GetComponent<CGather>()->GetGatherState() == GS_GATHERING)
				{
					return;
				}
			}

			string unitName = m_pGameObject->GetName();
			CSpriteRenderer* pRenderer = m_pGameObject->GetComponent<CSpriteRenderer>();
			if (fAngle >= 0.0f && fAngle < 22.5f)
			{
				if (pRenderer->GetCurrentClipKey() != unitName + "Stand12")
					pRenderer->ChangeCurrentClip(unitName + "Stand12");
			}
			else if (fAngle >= 22.5f && fAngle < 45)
			{
				if (pRenderer->GetCurrentClipKey() != unitName + "Stand13")
					pRenderer->ChangeCurrentClip(unitName + "Stand13");
			}
			else if (fAngle >= 45.0f && fAngle < 67.5f)
			{
				if (pRenderer->GetCurrentClipKey() != unitName + "Stand14")
					pRenderer->ChangeCurrentClip(unitName + "Stand14");
			}
			else if (fAngle >= 67.5f && fAngle < 90.0f)
			{
				if (pRenderer->GetCurrentClipKey() != unitName + "Stand15")
					pRenderer->ChangeCurrentClip(unitName + "Stand15");
			}
			else if (fAngle >= 90.0f && fAngle < 112.5f)
			{
				if (pRenderer->GetCurrentClipKey() != unitName + "Stand0")
					pRenderer->ChangeCurrentClip(unitName + "Stand0");
			}
			else if (fAngle >= 112.5f && fAngle < 135.0f)
			{
				if (pRenderer->GetCurrentClipKey() != unitName + "Stand1")
					pRenderer->ChangeCurrentClip(unitName + "Stand1");
			}
			else if (fAngle >= 135.0f && fAngle < 157.5f)
			{
				if (pRenderer->GetCurrentClipKey() != unitName + "Stand2")
					pRenderer->ChangeCurrentClip(unitName + "Stand2");
			}
			else if (fAngle >= 157.5f && fAngle < 180.0f)
			{
				if (pRenderer->GetCurrentClipKey() != unitName + "Stand3")
					pRenderer->ChangeCurrentClip(unitName + "Stand3");
			}
			else if (fAngle >= 180.0f && fAngle < 202.5f)
			{
				if (pRenderer->GetCurrentClipKey() != unitName + "Stand4")
					pRenderer->ChangeCurrentClip(unitName + "Stand4");
			}
			else if (fAngle >= 202.5f && fAngle < 225.0f)
			{
				if (pRenderer->GetCurrentClipKey() != unitName + "Stand5")
					pRenderer->ChangeCurrentClip(unitName + "Stand5");
			}
			else if (fAngle >= 225.0f && fAngle < 247.5f)
			{
				if (pRenderer->GetCurrentClipKey() != unitName + "Stand6")
					pRenderer->ChangeCurrentClip(unitName + "Stand6");
			}
			else if (fAngle >= 247.5f && fAngle < 270.0f)
			{
				if (pRenderer->GetCurrentClipKey() != unitName + "Stand7")
					pRenderer->ChangeCurrentClip(unitName + "Stand7");
			}
			else if (fAngle >= 270.0f && fAngle < 292.5f)
			{
				if (pRenderer->GetCurrentClipKey() != unitName + "Stand8")
					pRenderer->ChangeCurrentClip(unitName + "Stand8");
			}
			else if (fAngle >= 292.5f && fAngle < 315.0f)
			{
				if (pRenderer->GetCurrentClipKey() != unitName + "Stand9")
					pRenderer->ChangeCurrentClip(unitName + "Stand9");
			}
			else if (fAngle >= 315.0f && fAngle < 337.5f)
			{
				if (pRenderer->GetCurrentClipKey() != unitName + "Stand10")
					pRenderer->ChangeCurrentClip(unitName + "Stand10");
			}
			else if (fAngle >= 337.5f && fAngle < 360)
			{
				if (pRenderer->GetCurrentClipKey() != unitName + "Stand11")
					pRenderer->ChangeCurrentClip(unitName + "Stand11");
			}
		}
	}	
}

void CMove::LateUpdate()
{

//#ifdef _DEBUG
	
	//if (m_pVectorField)
	//{
	//	HDC dc = GET_SINGLE(CResourceManager)->GetBackBuffer()->GetDC();
	//	CVector2 cameraPosition = GET_SINGLE(CSceneManager)->GetCurrentScene()->GetCamera()->Transform()->GetPosition();
	//
	//	for (int y = 0; y < m_pVectorField->m_iGridHeight; ++y)
	//	{
	//		for (int x = 0; x < m_pVectorField->m_iGridWidth; ++x)
	//		{
	//			int idx = y * m_pVectorField->m_iGridWidth + x;
	//			int screenX = (16 + x * 32) - cameraPosition.x;
	//			int screenY = (16 + y * 32) - cameraPosition.y;
	//
	//			CVector2 dir = m_pVectorField->GetVector(idx);
	//
	//			for (int i = 0; i < 10; ++i)
	//			{
	//				SetPixel(dc, screenX + (dir.x * i), screenY + (dir.y * i), RGB(255, 0, 0));
	//			}
	//
	//		}
	//	}
	//}

//#endif // _DEBUG
}

void CMove::LoadComponent(FILE * pFile)
{
	fread(&m_fStopThreshold, 4, 1, pFile);
	fread(&m_fMoveSpeed, 4, 1, pFile);
	fread(&m_fAngularSpeed, 4, 1, pFile);
}

void CMove::SaveComponent(FILE * pFile)
{

	fwrite(&m_fStopThreshold, 4, 1, pFile);
	fwrite(&m_fMoveSpeed, 4, 1, pFile);
	fwrite(&m_fAngularSpeed, 4, 1, pFile);
}

CComponent * CMove::clone()
{
	return new CMove(*this);
}

CMove::CMove(const CMove & component):
	m_pVectorField(NULL),
	m_TargetPosition(CVector2()),
	m_bPause(false),
	m_bArrived(true),
	m_bStop(true)
{

	m_fStopThreshold = component.m_fStopThreshold;
	m_fMoveSpeed = component.m_fMoveSpeed;
	m_fAngularSpeed = component.m_fAngularSpeed;

	m_eComponentParentType = PT_NONE;
	m_eComponentType = CT_MOVE;
}

CMove::CMove() :
	m_pVectorField(NULL),
	m_TargetPosition(CVector2()),
	m_fStopThreshold(30),
	m_fMoveSpeed(150),
	m_fAngularSpeed(30),
	m_bPause(false),
	m_bArrived(true),
	m_bStop(true)
{
	m_eComponentParentType = PT_NONE;
	m_eComponentType = CT_MOVE;
	
}


CMove::~CMove()
{
	if (m_pButton)
		delete m_pButton;
}

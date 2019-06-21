#include "Cursor.h"
#include "../Input.h"
#include "Camera.h"
#include "../Scene.h"
#include "../GameObject.h"
#include "Transform.h"
#include "../Layer.h"
#include "RectangleRenderer.h"
#include "SpriteRenderer.h"
#include "Move.h"
#include "../Tile.h"
#include "CircleCollider.h"
#include "../ConsoleButtonManager.h"
#include "../ConsoleButton.h"
#include "../Core.h"
#include "../ResourceManager.h"
#include "../Texture.h"
#include "AdvancedBuild.h"
#include "Build.h"
#include "GameResource.h"
#include "Gather.h"
#include "../InfoPanelManager.h"
#include "UnitInfo.h"
#include "../Timer.h"
#include "Stop.h"
#include "../SceneManager.h"

void CCursor::UnSelectAllUnit()
{
	list<CGameObject*>::iterator iter;
	list<CGameObject*>::iterator iterEnd = m_SelectedUnitList.end();
	for (iter = m_SelectedUnitList.begin(); iter != iterEnd; ++iter)
	{
		(*iter)->SetSelected(false);
	}
	m_SelectedUnitList.clear();
}

void CCursor::EndBuildMode()
{
	m_bBuildMode = false;
	m_pBuildTarget->SetDestroy(true);
	//m_pBuildTarget = NULL;
}

void CCursor::SetBuildTarget(bool isAdvanced, CGameObject * pTarget)
{	
	m_bAdvancedBuildRequest = isAdvanced;
	m_pBuildTarget = pTarget;
	m_pBuildTarget->SetPilot(m_pGameObject->GetPilot());
	m_pGameObject->GetScene()->FindLayer("UIGame")->AddGameObject(m_pBuildTarget);
	m_pBuildTarget->GetComponent<CStructure>()->SetStart(true);
	m_pBuildTarget->GetComponent<CSpriteRenderer>()->ChangeCurrentClip(m_pBuildTarget->GetName() + "Normal");
}

void CCursor::EndRequest()
{
	class CSpriteRenderer* pRenderer = m_pGameObject->GetComponent<CSpriteRenderer>();
	m_pRequestedButton = NULL;
	m_pRequestedButtonObject = NULL;
	m_RequestedFunction = NULL;
	m_bHasRequested = false;
	pRenderer->ChangeCurrentClip("CursorNormal");
}

void CCursor::RequestFunction(CGameObject* pButtonObject, CConsoleButton* pButton, function<void(CVector2, class CGameObject*)> func)
{
	m_pRequestedButtonObject = pButtonObject;
	m_pRequestedButton = pButton;
	m_bHasRequested = true;
	m_RequestedFunction = func;
}

void CCursor::LateUpdate()
{
	CVector2 cameraPosition = m_pGameObject->GetScene()->GetCamera()->Transform()->GetPosition();
	CVector2 cursorScreenPosition = CInput::GetCursorPosition();
	CVector2 cursorWorldPosition = cursorScreenPosition + cameraPosition;
	CVector2 gridSize = m_pGameObject->GetScene()->GetGridSize();
	CSpriteRenderer* pRenderer = m_pGameObject->GetComponent<CSpriteRenderer>();
	CScene* pScene = m_pGameObject->GetScene();

	if (cursorScreenPosition.x < 0 || cursorScreenPosition.x > GET_SINGLE(CCore)->GetScreenSize().x || cursorScreenPosition.y < 0 || cursorScreenPosition.y > GET_SINGLE(CCore)->GetScreenSize().y)
		return;

	CGameObject* pTargetGameObject = NULL;
	int iX = cursorWorldPosition.x / 32;
	int iY = cursorWorldPosition.y / 32;
	int iIndex = iY * (int)gridSize.x + iX;

	if (!m_bBuildMode)
	{
		if (cursorScreenPosition.y < 500)
		{
			if (!m_bHasRequested)
			{
				//공중 유닛도 포함되어 있음.
				list<CGameObject*> unitList = pScene->GetTileByIndex(iIndex)->GetContainUnitList();

				//해당 타일에 유닛이 존재하면
				if (unitList.size() > 0)
				{
					list<CGameObject*>::iterator iter;
					list<CGameObject*>::iterator iterEnd = unitList.end();
					for (iter = unitList.begin(); iter != iterEnd; ++iter)
					{
						float radius;
						if ((*iter)->GetComponent<CCircleCollider>())
						{
							radius = (*iter)->GetComponent<CCircleCollider>()->GetRadius();
						}
						
						CVector2 targetPosition = (*iter)->GetTransform()->GetPosition();
						if ((targetPosition - cursorWorldPosition).length() <= radius)
						{
							if ((*iter)->GetPilot() == m_pGameObject->GetPilot())
							{
								pRenderer->ChangeCurrentClip("Cursor_Normal_Local_Over");
								pTargetGameObject = (*iter);
								break;
							}
							else if ((*iter)->GetPilot() == NULL)
							{
								pRenderer->ChangeCurrentClip("Cursor_Normal_Neutral_Over");
								pTargetGameObject = (*iter);
								break;
							}
							else
							{
								pRenderer->ChangeCurrentClip("Cursor_Normal_Enemy_Over");
								pTargetGameObject = (*iter);
								break;
							}
						}
					}
				}
				else
				{
					//지형과 충돌 시
					pRenderer->ChangeCurrentClip("CursorNormal");
				}

				if (GETKEYDOWN(VK_LBUTTON))
				{
					m_ClickedWorldPosition = cursorWorldPosition;

					m_pRect = new CGameObject;
					m_pGameObject->GetScene()->FindLayer("UIGame")->AddGameObject(m_pRect);
					CRectangleRenderer* pRenderer = m_pRect->AddComponent<CRectangleRenderer>();
				}

				if (GETKEYUP(VK_LBUTTON))
				{
					if (m_pRect)
					{
						if (pTargetGameObject)
						{
							list<CGameObject*>::iterator iter;
							list<CGameObject*>::iterator iterEnd = m_SelectedUnitList.end();
							for (iter = m_SelectedUnitList.begin(); iter != iterEnd; ++iter)
							{
								(*iter)->SetSelected(false);
							}
							m_SelectedUnitList.clear();

							m_SelectedUnitList.push_back(pTargetGameObject);
							pTargetGameObject->SetSelected(true);

							GET_SINGLE(CConsoleButtonManager)->UpdateControlPanel(pTargetGameObject);


							int iRandom = rand() % 4;
							char cRandom[4] = {};
							itoa(iRandom, cRandom, 10);
							GET_SINGLE(CResourceManager)->PlaySFX((*m_SelectedUnitList.begin())->GetName() + string("Select") + string(cRandom));

							m_pRect->SetDestroy(true);
							m_pRect = NULL;
						}
						else
						{
							{
								list<CGameObject*>::iterator iter;
								list<CGameObject*>::iterator iterEnd = m_SelectedUnitList.end();
								for (iter = m_SelectedUnitList.begin(); iter != iterEnd; ++iter)
								{
									(*iter)->SetSelected(false);
								}

								m_SelectedUnitList.clear();
							}

							CVector2 LT;
							CVector2 RB;

							if (m_ClickedWorldPosition.x <= cursorWorldPosition.x)
							{
								LT.x = m_ClickedWorldPosition.x;
								RB.x = cursorWorldPosition.x;
							}
							else
							{
								LT.x = cursorWorldPosition.x;
								RB.x = m_ClickedWorldPosition.x;
							}

							if (m_ClickedWorldPosition.y <= cursorWorldPosition.y)
							{
								LT.y = m_ClickedWorldPosition.y;
								RB.y = cursorWorldPosition.y;
							}
							else
							{
								LT.y = cursorWorldPosition.y;
								RB.y = m_ClickedWorldPosition.y;
							}


							GameObject()->GetComponent<CSpriteRenderer>()->ChangeCurrentClip("CursorNormal");

							list<CGameObject*> unitList;
							unitList.insert(unitList.begin(), m_pGameObject->GetScene()->GetLayer("AirUnit")->GetAllUnit().begin(), m_pGameObject->GetScene()->GetLayer("AirUnit")->GetAllUnit().end());
							unitList.insert(unitList.begin(), m_pGameObject->GetScene()->GetLayer("GroundUnit")->GetAllUnit().begin(), m_pGameObject->GetScene()->GetLayer("GroundUnit")->GetAllUnit().end());

							list<CGameObject*>::iterator iter;
							list<CGameObject*>::iterator iterEnd = unitList.end();

							for (iter = unitList.begin(); iter != iterEnd; ++iter)
							{
								if ((*iter)->GetPilot() == NULL || (*iter)->GetPilot() != m_pGameObject->GetPilot() || (*iter)->GetComponent<CStructure>())
								{
									continue;
								}

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
									m_SelectedUnitList.push_back(*iter);
									(*iter)->SetSelected(true);

									if (m_SelectedUnitList.size() >= 12)
									{
										break;
									}
								}
							}
							m_pRect->SetDestroy(true);
							m_pRect = NULL;
							if (m_SelectedUnitList.size() > 0)
							{
								GET_SINGLE(CConsoleButtonManager)->UpdateControlPanel(*m_SelectedUnitList.begin());

								int iRandom = rand() % 4;
								char cRandom[4] = {};
								itoa(iRandom, cRandom, 10);
								GET_SINGLE(CResourceManager)->PlaySFX((*m_SelectedUnitList.begin())->GetName() + string("Select") + string(cRandom));
							}
								


						}


						if (m_SelectedUnitList.size() == 1)
						{
							GET_SINGLE(CInfoPanelManager)->UpdateInfoPanel((*m_SelectedUnitList.begin())->GetComponent<CUnitInfo>());

						}
						else if (m_SelectedUnitList.size() >= 2)
						{
							GET_SINGLE(CInfoPanelManager)->UpdateInfoPanel(m_SelectedUnitList);
						}
						else
						{
							GET_SINGLE(CInfoPanelManager)->ClearInfoPanel();
						}
					}
				}

				if (GETKEY(VK_LBUTTON))
				{
					if (m_pRect)
					{
						CVector2 clickedWorldToScreenPosition = m_ClickedWorldPosition - cameraPosition;
						CVector2 currentWorldToScreenPosition = cursorWorldPosition - cameraPosition;

						CRectangleRenderer* pRenderer = m_pRect->GetComponent<CRectangleRenderer>();
						pRenderer->SetColor(RGB(30, 140, 30));
						pRenderer->SetStartPosition(clickedWorldToScreenPosition);
						pRenderer->SetEndPosition(currentWorldToScreenPosition);
						pRenderer->SetThickness(2);
					}					
				}
				//범위 선택 사각형이 없을 때, 커서가 유닛 위에 있으면서 클릭하면


				if (GETKEYDOWN(VK_RBUTTON))
				{
					if (!m_SelectedUnitList.empty())
					{
						list<CGameObject*>::iterator	iter;
						list<CGameObject*>::iterator iterEnd = m_SelectedUnitList.end();

						int iRandom = rand() % 4;
						char cRandom[4] = {};
						itoa(iRandom, cRandom, 10);
						GET_SINGLE(CResourceManager)->PlaySFX((*m_SelectedUnitList.begin())->GetName() + string("Command") + string(cRandom));

						for (iter = m_SelectedUnitList.begin(); iter != iterEnd; ++iter)
						{
							bool isAir = (*iter)->IsAirUnit();
							if ((*iter)->GetComponent<CMove>())
							{
								(*iter)->GetComponent<CStop>()->RequestStop();
								(*iter)->GetComponent<CMove>()->RequestMove(cursorWorldPosition, isAir);
								CGameObject* pPointer = GET_SINGLE(CResourceManager)->FindUnit("CursorRequestPointer")->clone();
								pPointer->GetTransform()->SetPosition(cursorWorldPosition);
								pPointer->SetPilot(m_pGameObject->GetPilot());
								GET_SINGLE(CSceneManager)->GetCurrentScene()->FindLayer("UIGame")->AddGameObject(pPointer);
							}
						}
					}

					if (!m_SelectedUnitList.empty() && pTargetGameObject)
					{
						if (pTargetGameObject->GetComponent<CResource>())
						{
							list<CGameObject*>::iterator iter;
							list<CGameObject*>::iterator iterEnd = m_SelectedUnitList.end();


							int iRandom = rand() % 4;
							char cRandom[4] = {};
							itoa(iRandom, cRandom, 10);
							GET_SINGLE(CResourceManager)->PlaySFX((*m_SelectedUnitList.begin())->GetName() + string("Command") + string(cRandom));

							for (iter = m_SelectedUnitList.begin(); iter != iterEnd; ++iter)
							{
								if ((*iter)->GetComponent<CGather>())
								{
									(*iter)->GetComponent<CStop>()->RequestStop();
									(*iter)->GetComponent<CGather>()->RequestMoveToGathering(pTargetGameObject);
								}
							}
						}
					}
				}
			}

			else
			{

				//공중 유닛도 포함되어 있음.
				list<CGameObject*> unitList = pScene->GetTileByIndex(iIndex)->GetContainUnitList();

				//해당 타일에 유닛이 존재하면
				if (unitList.size() > 0)
				{
					list<CGameObject*>::iterator iter;
					list<CGameObject*>::iterator iterEnd = unitList.end();
					for (iter = unitList.begin(); iter != iterEnd; ++iter)
					{
						float radius = (*iter)->GetComponent<CCircleCollider>()->GetRadius();
						CVector2 targetPosition = (*iter)->GetTransform()->GetPosition();
						if ((targetPosition - cursorWorldPosition).length() <= radius)
						{
							//유닛 위에 커서가 있을 때.
							if ((*iter)->GetPilot() == m_pGameObject->GetPilot())
							{
								//커서의 파일럿과, 해당 유닛의 파일럿이 같으면 아군이므로..
								pRenderer->ChangeCurrentClip("Cursor_Request_Local_Over");
								pTargetGameObject = (*iter);
								break;
							}
							else if ((*iter)->GetPilot() == NULL)
							{
								//해당 유닛의 파일럿이 존재하지 않으면, 중립 유닛이므로
								pRenderer->ChangeCurrentClip("Cursor_Request_Neutral_Over");
								pTargetGameObject = (*iter);
								break;
							}
							else
							{
								//유닛의 파일럿이 위의 사항에 포함되지 않는 파일럿이라면 적군
								pRenderer->ChangeCurrentClip("Cursor_Request_Enemy_Over");
								pTargetGameObject = (*iter);
								break;
							}
						}
					}
				}
				else
				{
					//지형과 충돌 시
					pRenderer->ChangeCurrentClip("Cursor_Request_Neutral_Normal");
				}


				if (GETKEYDOWN(VK_LBUTTON))
				{
					if (pTargetGameObject)
					{
						//선택 된 모든 유닛에게 해당 함수 실행함
						list<CGameObject*>::iterator iter;
						list<CGameObject*>::iterator iterEnd = m_SelectedUnitList.end();

						int iRandom = rand() % 4;
						char cRandom[4] = {};
						itoa(iRandom, cRandom, 10);
						GET_SINGLE(CResourceManager)->PlaySFX((*m_SelectedUnitList.begin())->GetName() + string("Command") + string(cRandom));

						for (iter = m_SelectedUnitList.begin(); iter != iterEnd; ++iter)
						{
							list<CConsoleButton*> unitList = (*iter)->GetButtonList();
							list<CConsoleButton*>::iterator _iter;
							list<CConsoleButton*>::iterator _iterEnd = unitList.end();
							for (_iter = unitList.begin(); _iter != _iterEnd; ++_iter)
							{
								if ((*_iter)->GetButtonName() == m_pRequestedButton->GetButtonName())
								{
									(*_iter)->RequestFunction(CVector2(), pTargetGameObject);
								}
							}
						}

						EndRequest();
					}
					else
					{
						list<CGameObject*>::iterator iter;
						list<CGameObject*>::iterator iterEnd = m_SelectedUnitList.end();

						int iRandom = rand() % 4;
						char cRandom[4] = {};
						itoa(iRandom, cRandom, 10);
						GET_SINGLE(CResourceManager)->PlaySFX((*m_SelectedUnitList.begin())->GetName() + string("Command") + string(cRandom));

						for (iter = m_SelectedUnitList.begin(); iter != iterEnd; ++iter)
						{
							list<CConsoleButton*> unitList = (*iter)->GetButtonList();
							list<CConsoleButton*>::iterator _iter;
							list<CConsoleButton*>::iterator _iterEnd = unitList.end();
							for (_iter = unitList.begin(); _iter != _iterEnd; ++_iter)
							{
								if ((*_iter)->GetButtonName() == m_pRequestedButton->GetButtonName())
								{
									(*_iter)->RequestFunction(cursorWorldPosition, NULL);
									CGameObject* pPointer = GET_SINGLE(CResourceManager)->FindUnit("CursorRequestPointer")->clone();
									pPointer->GetTransform()->SetPosition(cursorWorldPosition);
									pPointer->SetPilot(m_pGameObject->GetPilot());
									GET_SINGLE(CSceneManager)->GetCurrentScene()->FindLayer("UIGame")->AddGameObject(pPointer);
								}
							}
						}
						EndRequest();
					}
				}


				if (GETKEYDOWN(VK_ESCAPE) || GETKEYDOWN(VK_RBUTTON))
				{
					GET_SINGLE(CConsoleButtonManager)->UpdateControlPanel(GET_SINGLE(CConsoleButtonManager)->GetTargetObject());
					EndRequest();
				}
			}
		}

		else
		{
			if (GETKEYUP(VK_LBUTTON))
			{
				if (m_pRect)
				{
					if (m_pRect)
					{
						if (pTargetGameObject)
						{
							list<CGameObject*>::iterator iter;
							list<CGameObject*>::iterator iterEnd = m_SelectedUnitList.end();
							for (iter = m_SelectedUnitList.begin(); iter != iterEnd; ++iter)
							{
								(*iter)->SetSelected(false);
							}
							m_SelectedUnitList.clear();

							m_SelectedUnitList.push_back(pTargetGameObject);
							pTargetGameObject->SetSelected(true);

							GET_SINGLE(CConsoleButtonManager)->UpdateControlPanel(pTargetGameObject);


							m_pRect->SetDestroy(true);
							m_pRect = NULL;
						}
						else
						{
							{
								list<CGameObject*>::iterator iter;
								list<CGameObject*>::iterator iterEnd = m_SelectedUnitList.end();
								for (iter = m_SelectedUnitList.begin(); iter != iterEnd; ++iter)
								{
									(*iter)->SetSelected(false);
								}

								m_SelectedUnitList.clear();
							}

							CVector2 LT;
							CVector2 RB;

							if (m_ClickedWorldPosition.x <= cursorWorldPosition.x)
							{
								LT.x = m_ClickedWorldPosition.x;
								RB.x = cursorWorldPosition.x;
							}
							else
							{
								LT.x = cursorWorldPosition.x;
								RB.x = m_ClickedWorldPosition.x;
							}

							if (m_ClickedWorldPosition.y <= cursorWorldPosition.y)
							{
								LT.y = m_ClickedWorldPosition.y;
								RB.y = cursorWorldPosition.y;
							}
							else
							{
								LT.y = cursorWorldPosition.y;
								RB.y = m_ClickedWorldPosition.y;
							}


							GameObject()->GetComponent<CSpriteRenderer>()->ChangeCurrentClip("CursorNormal");

							list<CGameObject*> unitList;
							unitList.insert(unitList.begin(), m_pGameObject->GetScene()->GetLayer("AirUnit")->GetAllUnit().begin(), m_pGameObject->GetScene()->GetLayer("AirUnit")->GetAllUnit().end());
							unitList.insert(unitList.begin(), m_pGameObject->GetScene()->GetLayer("GroundUnit")->GetAllUnit().begin(), m_pGameObject->GetScene()->GetLayer("GroundUnit")->GetAllUnit().end());

							list<CGameObject*>::iterator iter;
							list<CGameObject*>::iterator iterEnd = unitList.end();

							for (iter = unitList.begin(); iter != iterEnd; ++iter)
							{
								if ((*iter)->GetPilot() == NULL || (*iter)->GetPilot() != m_pGameObject->GetPilot() || (*iter)->GetComponent<CStructure>())
								{
									continue;
								}

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
									m_SelectedUnitList.push_back(*iter);
									(*iter)->SetSelected(true);

									if (m_SelectedUnitList.size() >= 12)
									{
										break;
									}
								}
							}
							m_pRect->SetDestroy(true);
							m_pRect = NULL;
							if (m_SelectedUnitList.size() > 0)
							{
								GET_SINGLE(CConsoleButtonManager)->UpdateControlPanel(*m_SelectedUnitList.begin());
							}
						}


						if (m_SelectedUnitList.size() == 1)
						{
							GET_SINGLE(CInfoPanelManager)->UpdateInfoPanel((*m_SelectedUnitList.begin())->GetComponent<CUnitInfo>());
						}
						else if (m_SelectedUnitList.size() >= 2)
						{
							GET_SINGLE(CInfoPanelManager)->UpdateInfoPanel(m_SelectedUnitList);
						}
						else
						{
							GET_SINGLE(CInfoPanelManager)->ClearInfoPanel();
						}
					}
				}
			}
		}
	}
	else
	{
		if (m_pBuildTarget)
		{
			m_pBuildTarget->GetTransform()->SetPosition(iX * 32, iY * 32);
			m_pBuildTarget->GetComponent<CSpriteRenderer>()->ChangeCurrentClip(m_pBuildTarget->GetName() + "Normal");
			
			if (GETKEYDOWN(VK_SPACE))
			{
				EndBuildMode();
			}
			
			BLENDFUNCTION tBF;
			tBF.AlphaFormat = NULL;
			tBF.BlendFlags = NULL;
			tBF.BlendOp = AC_SRC_OVER;
			tBF.SourceConstantAlpha = 128;
			CVector2 origin = m_pBuildTarget->GetComponent<CSpriteRenderer>()->GetSize();
			origin.x = origin.x * m_pBuildTarget->GetTransform()->GetPivot().x;
			origin.y = origin.y * m_pBuildTarget->GetTransform()->GetPivot().y;
			CVector2 LT = m_pBuildTarget->GetTransform()->GetPosition() - origin;
			LT -= cameraPosition;
			vector<CVector2> buildableTile = m_pBuildTarget->GetComponent<CStructure>()->GetBuildableTile();
			
			int iX = (LT.x + cameraPosition.x) / 32;
			int iY = (LT.y + cameraPosition.y) / 32;

			bool bBuildable = true;

			for (int i = 0; i < buildableTile.size(); ++i)
			{
				int x = iX + buildableTile[i].x;
				int y = iY + buildableTile[i].y;
				
				int index = y * gridSize.x + x;


				if (pScene->GetTileByIndex(index)->GetBuildable() && pScene->GetTileByIndex(index)->GetContainUnitList().size() == 0)
				{
					AlphaBlend(GET_SINGLE(CResourceManager)->GetBackBuffer()->GetDC(),
						LT.x + buildableTile[i].x * 32, LT.y + buildableTile[i].y * 32, 32, 32,
						GET_SINGLE(CResourceManager)->FindTexture("PositiveCell")->GetDC(),
						0, 0, 32, 32, tBF);
				}
				else if(pScene->GetTileByIndex(index)->GetContainUnitList().size() == 1)
				{
					list<CGameObject*> unitList = pScene->GetTileByIndex(index)->GetContainUnitList();

					if ((*unitList.begin())->GetName().find("SCV") != string::npos)
					{
						AlphaBlend(GET_SINGLE(CResourceManager)->GetBackBuffer()->GetDC(),
							LT.x + buildableTile[i].x * 32, LT.y + buildableTile[i].y * 32, 32, 32,
							GET_SINGLE(CResourceManager)->FindTexture("PositiveCell")->GetDC(),
							0, 0, 32, 32, tBF);
					}
					else
					{
						bBuildable = false;
						AlphaBlend(GET_SINGLE(CResourceManager)->GetBackBuffer()->GetDC(),
							LT.x + buildableTile[i].x * 32, LT.y + buildableTile[i].y * 32, 32, 32,
							GET_SINGLE(CResourceManager)->FindTexture("NegativeCell")->GetDC(),
							0, 0, 32, 32, tBF);
					}
				}
			}

			if (bBuildable)
			{
				if (GETKEYDOWN(VK_LBUTTON))
				{
					CGameObject* pCreateBuilding = GET_SINGLE(CResourceManager)->FindUnit(m_pBuildTarget->GetKey())->clone();				


					pCreateBuilding->GetTransform()->SetPosition(m_pBuildTarget->GetTransform()->GetPosition());
					pCreateBuilding->GetTransform()->SetPivot(m_pBuildTarget->GetTransform()->GetPivot());
					pCreateBuilding->GetTransform()->SetScale(m_pBuildTarget->GetTransform()->GetScale());
					pCreateBuilding->SetPilot(m_pGameObject->GetPilot());
					//Build Component로 넘겨줌  		
					if (m_bAdvancedBuildRequest)
					{
						GET_SINGLE(CConsoleButtonManager)->GetTargetObject()->GetComponent<CAdvancedBuild>()->SetRequestedBuilding(pCreateBuilding);
						GET_SINGLE(CResourceManager)->PlaySFX("BuildStructure");
						EndBuildMode();
						EndRequest();
					}
					else
					{
						GET_SINGLE(CConsoleButtonManager)->GetTargetObject()->GetComponent<CBuild>()->SetRequestedBuilding(pCreateBuilding);
						GET_SINGLE(CResourceManager)->PlaySFX("BuildStructure");
						EndBuildMode();
						EndRequest();
					}
				}
			}
		}
	}



	if (m_SelectedUnitList.size() == 1)
	{
		m_fInfoPanelUpdateTime += GET_SINGLE(CTimer)->GetDeltaTime();
		if (m_fInfoPanelUpdateTime >= 1 / m_fInfoPanelUpdateRate)
		{
			m_fInfoPanelUpdateTime -= 1 / m_fInfoPanelUpdateRate;
			GET_SINGLE(CInfoPanelManager)->UpdateInfoPanel((*m_SelectedUnitList.begin())->GetComponent<CUnitInfo>());
		}
	}
}

void CCursor::LoadComponent(FILE * pFile)
{
}

void CCursor::SaveComponent(FILE * pFile)
{
}

CComponent * CCursor::clone()
{
	return nullptr;
}

CCursor::CCursor(const CCursor & component)
{
}

CCursor::CCursor() :
	m_pRect(NULL),
	m_bHasRequested(false),
	m_RequestedFunction(NULL),
	m_pRequestedButton(NULL),
	m_pRequestedButtonObject(NULL),
	m_bBuildMode(false),
	m_fInfoPanelUpdateTime(0),
	m_fInfoPanelUpdateRate(3)
{
}


CCursor::~CCursor()
{
}

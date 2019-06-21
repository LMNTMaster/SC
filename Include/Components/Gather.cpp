#include "Gather.h"
#include "../GameObject.h"
#include "Transform.h"
#include "SpriteRenderer.h"
#include "ControlButton.h"
#include "../ConsoleButton.h"
#include "../Components/Player.h"
#include "../ConsoleButtonManager.h"
#include "../SceneManager.h"
#include "../ResourceManager.h"
#include "../Scene.h"
#include "../SceneManager.h"
#include "../Layer.h"
#include "Player.h"
#include "../Component.h"
#include "Move.h"
#include "GameResource.h"
#include "Stop.h"
#include "../Timer.h"

void CGather::Stop()
{
	if (m_pGameObject->IsAirUnit())
	{
		m_pGameObject->SetToAirUnit(false);
	}


	m_bStop = true;
}

CGameObject* CGather::GetNearestBase()
{
	list<CGameObject*> baseList;
	switch (m_pGameObject->GetScene()->GetLayer("System")->FindGameObject("Player")->GetComponent<CPlayer>()->GetRaceType())
	{
	case RT_TERRAN:
		baseList = m_pGameObject->GetScene()->GetLayer("GroundUnit")->FindGameObjects("CommandCenter");
		break;
	case RT_PROTOSS:
		baseList = m_pGameObject->GetScene()->GetLayer("GroundUnit")->FindGameObjects("Nexus");
		break;
	case RT_ZERG:
	{
		baseList = m_pGameObject->GetScene()->GetLayer("GroundUnit")->FindGameObjects("Hatchery");
		list<CGameObject*> lair = m_pGameObject->GetScene()->GetLayer("GroundUnit")->FindGameObjects("Lair");
		list<CGameObject*> hive = m_pGameObject->GetScene()->GetLayer("GroundUnit")->FindGameObjects("Hive");
		baseList.insert(baseList.begin(), lair.begin(), lair.end());
		baseList.insert(baseList.begin(), hive.begin(), hive.end());
	}break;
	default:
		break;
	}


	list<CGameObject*>::iterator iter;
	list<CGameObject*>::iterator iterEnd = baseList.end();
	

	float fNearlestDistance = INT_MAX;
	CGameObject* pNearlest = NULL;
	
	for (iter = baseList.begin() ; iter != iterEnd; ++iter)
	{
		float distance = ((*iter)->GetTransform()->GetPosition() - m_pTransform->GetPosition()).length();
		if (distance < fNearlestDistance)
		{
			fNearlestDistance = distance;
			pNearlest = *iter;
		}
	}
	return pNearlest;
}

void CGather::RequestMoveToGathering(CGameObject * pTarget)
{
	if (pTarget)
	{
		m_pGameObject->SetToAirUnit(true);
		CMove* pMoveComponent = m_pGameObject->GetComponent<CMove>();
		//m_pGameObject->GetComponent<CStop>()->RequestStop();
		if (!m_pOrb)
		{
			if (pMoveComponent)
			{
				m_bStop = false;
				m_pTargetResource = pTarget;
				pMoveComponent->RequestMove(pTarget->GetTransform()->GetPosition());
				m_eGatherState = GS_MOVETORESOURCE;
			}
		}
		else
		{
			RequestReturnToBasement();
		}
	}
}

void CGather::RequestReturnToBasement()
{
	CMove* pMoveComponent = m_pGameObject->GetComponent<CMove>();
	CGameObject* pBasement = GetNearestBase();

	//m_pGameObject->GetComponent<CStop>()->RequestStop();
	if (pMoveComponent)
	{
		m_bStop = false;
		pMoveComponent->RequestMove(pBasement->GetTransform()->GetPosition());
		m_eGatherState = GS_RETURNTOBASEMENT;
	}
}

CGameObject* CGather::GetNearestMineral()
{
	list<CGameObject*> resourceList = m_pGameObject->GetScene()->FindLayer("GroundUnit")->FindGameObjects("Mineral");
	
	list<CGameObject*>::iterator iter;
	list<CGameObject*>::iterator iterEnd = resourceList.end();
	
	for (iter = resourceList.begin(); iter != iterEnd; )
	{
		if ((*iter)->GetComponent<CResource>()->GetQueueSize() < 2)
		{
			iter = resourceList.erase(iter);
		}
		else
		{
			++iter;
		}
	}

	float distance = 500;  //최대 탐색 범위. 자원과의 거리가 이 값보다 멀면 검색하지 않는다.
	CGameObject* pNearest = NULL;

	for (iter = resourceList.begin(); iter != iterEnd; ++iter)
	{
		if ((m_pTransform->GetPosition() - (*iter)->GetTransform()->GetPosition()).length() < distance)
		{
			pNearest = (*iter);
			distance = (m_pTransform->GetPosition() - (*iter)->GetTransform()->GetPosition()).length();
		}
	}

	return pNearest;

}

void CGather::Start()
{
	CScene* pScene = GET_SINGLE(CSceneManager)->GetCurrentScene();
	CPlayer* pPlayer = pScene->GetLayer("System")->FindGameObject("Player")->GetComponent<CPlayer>();
	m_pButton = new CConsoleButton;
	m_pGameObject->AddButton(m_pButton);

	m_pButton->SetUpIconTexture(GET_SINGLE(CResourceManager)->FindTexture("ControlButton_Icon_Gather_Normal"));
	m_pButton->SetDownIconTexture(GET_SINGLE(CResourceManager)->FindTexture("ControlButton_Icon_Gather_Pressed"));

	m_pButton->SetRequireCursor(true);
	m_pButton->SetButtonName("Gather");
	m_pButton->SetPanelIndex(4);
	m_pButton->SetExistNextPage(true);
	m_pButton->SetShortcutKey('G');
	m_pButton->SetButtonComponent(this);

	auto func = [&](CVector2 position, CGameObject* pTarget)
	{
		RequestMoveToGathering(pTarget);
	};
	m_pButton->SetFunction(func);


	//Next Page
	vector<CConsoleButton*> vecNextPage;
	vecNextPage.resize(9);

	for (int i = 0; i < 9; ++i)
	{
		vecNextPage[i] = NULL;
	}

	//자동 해제
	CConsoleButton* pCancelButton = new CConsoleButton;
	pCancelButton->SetRequireCursor(false);
	pCancelButton->SetButtonName("Cancel");
	pCancelButton->SetPanelIndex(8);
	pCancelButton->SetShortcutKey(VK_SPACE);
	pCancelButton->SetUpIconTexture(GET_SINGLE(CResourceManager)->FindTexture("ControlButton_Icon_Cancel_Normal"));
	pCancelButton->SetDownIconTexture(GET_SINGLE(CResourceManager)->FindTexture("ControlButton_Icon_Cancel_Pressed"));
	pCancelButton->SetButtonComponent(this);
	pCancelButton->SetExistNextPage(false);

	auto cancel = [&](CVector2 position, CGameObject* pTarget)
	{
		GET_SINGLE(CConsoleButtonManager)->UpdateControlPanel(m_pGameObject);
	};

	vecNextPage[8] = pCancelButton;
	pCancelButton->SetFunction(cancel);
	m_pButton->SetNextPage(vecNextPage);
}

void CGather::Update()
{
	CMove* pMoveComponent = m_pGameObject->GetComponent<CMove>();
	CSpriteRenderer* pRenderer = m_pGameObject->GetComponent<CSpriteRenderer>();
	CTransform* pTransform = m_pTransform;
	CScene* pScene = GET_SINGLE(CSceneManager)->GetCurrentScene();
	CPlayer* pPlayer = pScene->GetLayer("System")->FindGameObject("Player")->GetComponent<CPlayer>();

	if (!m_bStop)
	{
		switch (m_eGatherState)
		{
		case GS_MOVETORESOURCE:
		{
			if (m_pTargetResource)
			{
				if ((m_pTargetResource->GetTransform()->GetPosition() - m_pTransform->GetPosition()).length() <= 64)
				{
					m_eGatherState = GS_GATHERING;
					CResource* pResource = m_pTargetResource->GetComponent<CResource>();
					pResource->AddUnit(m_pGameObject);
				}
				else
				{
					RequestMoveToGathering(m_pTargetResource);
				}
			}
		}
		break;
		case GS_RETURNTOBASEMENT:
		{
			if (pMoveComponent->GetArrived())
			{
				if (m_pOrb)
				{
					if (m_pOrb->GetComponent<CSpriteRenderer>()->GetCurrentClipKey().find("Mineral") != string::npos)
					{
						pPlayer->AddMineral(8);
					}
					else
					{
						pPlayer->AddVespeneGas(8);
					}					
					m_pOrb->SetDestroy(true);
					m_pOrb = NULL;
				}

				m_eGatherState = GS_MOVETORESOURCE;
				
				if (m_pTargetResource)
				{
					RequestMoveToGathering(m_pTargetResource);
				}
				else
				{
					CGameObject* pTargetResource = GetNearestMineral();
					if (pTargetResource)
					{
						m_pTargetResource = pTargetResource;
						RequestMoveToGathering(m_pTargetResource);
					}
				}
			}
		}
		break;
		case GS_GATHERING:
		{
			m_fAnimationTimer += GET_SINGLE(CTimer)->GetDeltaTime();

			if (m_fAnimationTimer >= m_fAnimationTime)
			{
				m_fAnimationTimer -= m_fAnimationTime;

				string unitName = m_pGameObject->GetName();
				float fAngle = pTransform->GetRotation();

				if (fAngle >= 360)
				{
					fAngle -= 360;
				}
				if (fAngle <= 0)
				{
					fAngle += 360;
				}
				m_pTransform->SetRotation(fAngle);

				if (fAngle >= 0.0f && fAngle < 22.5f)
				{
					if (pRenderer->GetCurrentClipKey() != unitName + "Attack12")
					{
						pRenderer->ChangeCurrentClip(unitName + "Attack12");
					}
				}
				else if (fAngle >= 22.5f && fAngle < 45)
				{
					if (pRenderer->GetCurrentClipKey() != unitName + "Attack13")
						pRenderer->ChangeCurrentClip(unitName + "Attack13");
				}
				else if (fAngle >= 45.0f && fAngle < 67.5f)
				{
					if (pRenderer->GetCurrentClipKey() != unitName + "Attack14")
						pRenderer->ChangeCurrentClip(unitName + "Attack14");
				}
				else if (fAngle >= 67.5f && fAngle < 90.0f)
				{
					if (pRenderer->GetCurrentClipKey() != unitName + "Attack15")
						pRenderer->ChangeCurrentClip(unitName + "Attack15");
				}
				else if (fAngle >= 90.0f && fAngle < 112.5f)
				{
					if (pRenderer->GetCurrentClipKey() != unitName + "Attack0")
						pRenderer->ChangeCurrentClip(unitName + "Attack0");
				}
				else if (fAngle >= 112.5f && fAngle < 135.0f)
				{
					if (pRenderer->GetCurrentClipKey() != unitName + "Attack1")
						pRenderer->ChangeCurrentClip(unitName + "Attack1");
				}
				else if (fAngle >= 135.0f && fAngle < 157.5f)
				{
					if (pRenderer->GetCurrentClipKey() != unitName + "Attack2")
						pRenderer->ChangeCurrentClip(unitName + "Attack2");
				}
				else if (fAngle >= 157.5f && fAngle < 180.0f)
				{
					if (pRenderer->GetCurrentClipKey() != unitName + "Attack3")
						pRenderer->ChangeCurrentClip(unitName + "Attack3");
				}
				else if (fAngle >= 180.0f && fAngle < 202.5f)
				{
					if (pRenderer->GetCurrentClipKey() != unitName + "Attack4")
						pRenderer->ChangeCurrentClip(unitName + "Attack4");
				}
				else if (fAngle >= 202.5f && fAngle < 225.0f)
				{
					if (pRenderer->GetCurrentClipKey() != unitName + "Attack5")
						pRenderer->ChangeCurrentClip(unitName + "Attack5");
				}
				else if (fAngle >= 225.0f && fAngle < 247.5f)
				{
					if (pRenderer->GetCurrentClipKey() != unitName + "Attack6")
						pRenderer->ChangeCurrentClip(unitName + "Attack6");
				}
				else if (fAngle >= 247.5f && fAngle < 270.0f)
				{
					if (pRenderer->GetCurrentClipKey() != unitName + "Attack7")
						pRenderer->ChangeCurrentClip(unitName + "Attack7");
				}
				else if (fAngle >= 270.0f && fAngle < 292.5f)
				{
					if (pRenderer->GetCurrentClipKey() != unitName + "Attack8")
						pRenderer->ChangeCurrentClip(unitName + "Attack8");
				}
				else if (fAngle >= 292.5f && fAngle < 315.0f)
				{
					if (pRenderer->GetCurrentClipKey() != unitName + "Attack9")
						pRenderer->ChangeCurrentClip(unitName + "Attack9");
				}
				else if (fAngle >= 315.0f && fAngle < 337.5f)
				{
					if (pRenderer->GetCurrentClipKey() != unitName + "Attack10")
						pRenderer->ChangeCurrentClip(unitName + "Attack10");
				}
				else if (fAngle >= 337.5f && fAngle < 360)
				{
					if (pRenderer->GetCurrentClipKey() != unitName + "Attack11")
						pRenderer->ChangeCurrentClip(unitName + "Attack11");
				}
			}
		}
		default:
			break;

		}
	}

	else
	{
		if (m_pGameObject->IsAirUnit())
		{
			m_pGameObject->SetToAirUnit(false);
		}
	}
}

void CGather::SaveComponent(FILE * pFile)
{
	fwrite(&m_iGatherAmount, 4, 1, pFile);
}

void CGather::LoadComponent(FILE * pFile)
{
	fread(&m_iGatherAmount, 4, 1, pFile);
}

CComponent * CGather::clone()
{
	return new CGather(*this);
}

CGather::CGather(const CGather & component):
	m_bStop(true),
	m_pOrb(NULL),
	m_fAnimationTimer(0),
	m_fAnimationTime(0.5f)
{
	m_iGatherAmount = component.m_iGatherAmount;

	m_eComponentParentType = PT_NONE;
	m_eComponentType = CT_GATHER;
}

CGather::CGather():
	m_bStop(true),
	m_pOrb(NULL),
	m_fAnimationTimer(0),
	m_fAnimationTime(0.5f)
{
	m_eComponentParentType = PT_NONE;
	m_eComponentType = CT_GATHER;
}


CGather::~CGather()
{
	if (m_pButton)
		delete m_pButton;
}

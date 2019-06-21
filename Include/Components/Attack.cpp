#include "Attack.h"
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
#include "../GameObject.h"
#include "../Tile.h"
#include "Transform.h"
#include "Move.h"
#include "SpriteRenderer.h"
#include "../Timer.h"
#include "Stop.h"
#include "UnitStatus.h"


list<class CGameObject*> CAttack::GetAttackRangeUnitList()
{
	list<CGameObject*> targetList;
	list<CTile*> tileList;

	CScene* pScene = m_pGameObject->GetScene();
	CVector2 position = m_pTransform->GetPosition();
	CVector2 gridSize = pScene->GetGridSize();
	int iX = position.x / 32;
	int iY = position.y / 32;
	int idx = iY * gridSize.x + iX;
	
	int maxLevel = m_fAttackRange / 32;

	
	for (int y = -maxLevel; y <= maxLevel; ++y)
	{
		for (int x = -maxLevel; x <= maxLevel; ++x)
		{
			//타일 범위 밖이면 연산하지 않음
			if (iX + x < 0 || iX + x > gridSize.x || iY + y < 0 || iY + y > gridSize.y)
			{
				continue;
			}

			//타일의 중심부터 유닛과의 거리가 공격 범위 내에 있으면, 타일 추가함.
			int iTileIndex = idx + y * gridSize.x + x;
			
			CTile* pTile = pScene->GetTileByIndex(iTileIndex);
			CVector2 temp = pTile->GetWorldPosition() + CVector2(16,16);
			temp -= position;
			float distance = temp.length();
			if (distance <= m_fAttackRange + 16)
			{
				tileList.push_back(pTile);
			}
		}
	}
	//범위 내의 타일 전부 추가했으니, 타일 내의 모든 유닛 리스트를 만들어서 리턴해줌.
	list<CTile*>::iterator iter;
	list<CTile*>::iterator iterEnd = tileList.end();

	for (iter = tileList.begin(); iter != iterEnd; ++iter)
	{
		targetList.insert(targetList.begin(), (*iter)->GetContainUnitList().begin(), (*iter)->GetContainUnitList().end());
	}

	return targetList;
}

void CAttack::RequestAttackMove(CVector2 position)
{
	m_pGameObject->GetComponent<CStop>()->RequestStop();
	m_bStop = false;
	m_eAttackMode = AM_ATTACK_MOVE;
	m_pTarget = NULL;
	m_pGameObject->GetComponent<CMove>()->RequestMove(position);
}

void CAttack::RequestAttackTarget(CGameObject * pTarget)
{
	m_pGameObject->GetComponent<CStop>()->RequestStop();
	m_bStop = false;
	m_eAttackMode = AM_ATTACK_TARGET;
	m_pTarget = pTarget;
}

void CAttack::Start()
{
	CScene* pScene = GET_SINGLE(CSceneManager)->GetCurrentScene();
	CPlayer* pPlayer = pScene->GetLayer("System")->FindGameObject("Player")->GetComponent<CPlayer>();
	m_pButton = new CConsoleButton;
	m_pGameObject->AddButton(m_pButton);

	m_pButton->SetUpIconTexture(GET_SINGLE(CResourceManager)->FindTexture("ControlButton_Icon_Attack_Normal"));
	m_pButton->SetDownIconTexture(GET_SINGLE(CResourceManager)->FindTexture("ControlButton_Icon_Attack_Pressed"));

	m_pButton->SetRequireCursor(true);
	m_pButton->SetButtonName("Attack");
	m_pButton->SetPanelIndex(2);
	m_pButton->SetExistNextPage(true);
	m_pButton->SetShortcutKey('A');
	m_pButton->SetButtonComponent(this);

	auto func = [&](CVector2 position, CGameObject* pTarget) 
	{		
		//타겟을 찍었을 때,
		if (position == CVector2() && pTarget)
		{
			RequestAttackTarget(pTarget);
		}
		//지형을 찍었을 때
		else if (position != CVector2() && !pTarget)
		{
			RequestAttackMove(position);
		}
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

void CAttack::LateUpdate()
{
	if (!m_bStop)
	{
		switch (m_eAttackMode)
		{
		case AM_NONE:
			break;
		case AM_ATTACK_MOVE:
		{
			CMove* pMove = m_pGameObject->GetComponent<CMove>();
			list<CGameObject*> unitList = GetAttackRangeUnitList();

			list<CGameObject*>::iterator iter;
			list<CGameObject*>::iterator iterEnd = unitList.end();
			for (iter = unitList.begin(); iter != iterEnd; ++iter)
			{
				if ((*iter)->GetPilot() != NULL)
				{
					if ((*iter)->GetPilot() != m_pGameObject->GetPilot())
					{
						m_pTarget = *iter;
						if (pMove)
						{
							pMove->Stop();							
								
							m_fIntervalTimer += GET_SINGLE(CTimer)->GetDeltaTime();
							if (m_fIntervalTimer >= m_fInterval)
							{
								m_fIntervalTimer -= m_fInterval;
							
								Attack();
							}
						}
					}
				}
			}
		}
		break;
		case AM_ATTACK_TARGET:
		{
			if (m_pTarget)
			{
				if (m_pTarget == m_pGameObject)
				{
					m_pTarget = NULL;
					m_eAttackMode = AM_NONE;
					break;
				}


				list<CGameObject*> unitList = GetAttackRangeUnitList();

				list<CGameObject*>::iterator iter;
				list<CGameObject*>::iterator iterEnd = unitList.end();
				bool bFindTarget = false;
				for (iter = unitList.begin(); iter != iterEnd; ++iter)
				{
					if (*iter == m_pTarget)
					{
						bFindTarget = true;
					}
				}

				if (bFindTarget)
				{
					CMove* pMove = m_pGameObject->GetComponent<CMove>();
					CSpriteRenderer* pRenderer = m_pGameObject->GetComponent<CSpriteRenderer>();

					if (pMove)
					{
						pMove->Stop();

						m_fIntervalTimer += GET_SINGLE(CTimer)->GetDeltaTime();
					
						if (m_fIntervalTimer >= m_fInterval)
						{
							m_fIntervalTimer -= m_fInterval;
							Attack();
						}
					}
				}
				else
				{
					//공격 범위 내에 대상이 없으면 이동함.
					CMove* pMove = m_pGameObject->GetComponent<CMove>();
					if (m_pTarget && !m_pTarget->GetDestroy())
					{						
						pMove->RequestMove(m_pTarget->GetTransform()->GetPosition());
					}
					else
					{
						m_pTarget = NULL;
					}
					m_fIntervalTimer = 0;
				}
			}
			else
			{
				//공격중 대상이 없어졌을 때, 여기로 옴				

				CSpriteRenderer* pRenderer = m_pGameObject->GetComponent<CSpriteRenderer>();
				string unitName = m_pGameObject->GetName();
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
		break;
		default:
			break;
		}
	}
	
}

void CAttack::Attack()
{
	CUnitStatus* pStatus = m_pTarget->GetComponent<CUnitStatus>();
	pStatus->AddHP( -m_fDamage);
	if (pStatus->GetCurrentHP() <= 0)
		m_pTarget = NULL;


	CSpriteRenderer* pRenderer = m_pGameObject->GetComponent<CSpriteRenderer>();
	string unitName = m_pGameObject->GetName();

	float fAngle = 0;

	if (m_pTarget)
	{
		CVector2 lookat = (m_pTransform->GetPosition() - m_pTarget->GetTransform()->GetPosition()).normalize();
		fAngle = CVector2::DirectionToAngle(lookat);
	}
	else
	{
		return;
	}


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
			pRenderer->ChangeCurrentClip(unitName + "Attack12");
	}
	else if (fAngle >= 22.5f && fAngle < 45)
	{
			pRenderer->ChangeCurrentClip(unitName + "Attack13");
	}
	else if (fAngle >= 45.0f && fAngle < 67.5f)
	{
			pRenderer->ChangeCurrentClip(unitName + "Attack14");
	}
	else if (fAngle >= 67.5f && fAngle < 90.0f)
	{
			pRenderer->ChangeCurrentClip(unitName + "Attack15");
	}
	else if (fAngle >= 90.0f && fAngle < 112.5f)
	{
			pRenderer->ChangeCurrentClip(unitName + "Attack0");
	}
	else if (fAngle >= 112.5f && fAngle < 135.0f)
	{
			pRenderer->ChangeCurrentClip(unitName + "Attack1");
	}
	else if (fAngle >= 135.0f && fAngle < 157.5f)
	{
			pRenderer->ChangeCurrentClip(unitName + "Attack2");
	}
	else if (fAngle >= 157.5f && fAngle < 180.0f)
	{
			pRenderer->ChangeCurrentClip(unitName + "Attack3");
	}
	else if (fAngle >= 180.0f && fAngle < 202.5f)
	{
			pRenderer->ChangeCurrentClip(unitName + "Attack4");
	}
	else if (fAngle >= 202.5f && fAngle < 225.0f)
	{
			pRenderer->ChangeCurrentClip(unitName + "Attack5");
	}
	else if (fAngle >= 225.0f && fAngle < 247.5f)
	{
			pRenderer->ChangeCurrentClip(unitName + "Attack6");
	}
	else if (fAngle >= 247.5f && fAngle < 270.0f)
	{
			pRenderer->ChangeCurrentClip(unitName + "Attack7");
	}
	else if (fAngle >= 270.0f && fAngle < 292.5f)
	{
			pRenderer->ChangeCurrentClip(unitName + "Attack8");
	}
	else if (fAngle >= 292.5f && fAngle < 315.0f)
	{
			pRenderer->ChangeCurrentClip(unitName + "Attack9");
	}
	else if (fAngle >= 315.0f && fAngle < 337.5f)
	{
			pRenderer->ChangeCurrentClip(unitName + "Attack10");
	}
	else if (fAngle >= 337.5f && fAngle < 360)
	{
			pRenderer->ChangeCurrentClip(unitName + "Attack11");
	}

}

void CAttack::SaveComponent(FILE * pFile)
{
	int iLength = strlen(m_strWeaponName.c_str());
	char cBuffer[128] = {};
	strcpy(cBuffer, m_strWeaponName.c_str());

	fwrite(&iLength, 4, 1, pFile);
	fwrite(cBuffer, 1, iLength, pFile);
	fwrite(&m_eUpgradeType, sizeof(UPGRADE_TYPE), 1, pFile);
	fwrite(&m_fAttackRange, 4, 1, pFile);
	fwrite(&m_fUpgradeIncrease, 4, 1, pFile);
	fwrite(&m_fDamage, 4, 1, pFile);
	fwrite(&m_fInterval, 4, 1, pFile);
}

void CAttack::LoadComponent(FILE * pFile)
{
	int iLength = 0;
	char cBuffer[128] = {};
	fread(&iLength, 4, 1, pFile);	
	fread(cBuffer, 1, iLength, pFile);
	m_strWeaponName = string(cBuffer);

	fread(&m_eUpgradeType, sizeof(UPGRADE_TYPE), 1, pFile);
	fread(&m_fAttackRange, 4, 1, pFile);
	fread(&m_fUpgradeIncrease, 4, 1, pFile);
	fread(&m_fDamage, 4, 1, pFile);
	fread(&m_fInterval, 4, 1, pFile);
}

CComponent * CAttack::clone()
{
	return new CAttack(*this);
}



CAttack::CAttack(const CAttack & component):
	m_fIntervalTimer(0),
	m_pTarget(NULL),
	m_eAttackMode(AM_NONE),
	m_bStop(true), m_bOnAttack(false)
{
	m_strWeaponName = component.m_strWeaponName;
	m_eUpgradeType = component.m_eUpgradeType;
	m_fAttackRange = component.m_fAttackRange;
	m_fUpgradeIncrease = component.m_fUpgradeIncrease;
	m_fDamage = component.m_fDamage;
	m_fInterval = component.m_fInterval;

	m_eComponentParentType = PT_NONE;
	m_eComponentType = CT_ATTACK;

}

CAttack::CAttack() :
	m_strWeaponName(""),
	m_eUpgradeType(UT_NONE),
	m_fAttackRange(5),
	m_fDamage(0),
	m_fInterval(1),
	m_fIntervalTimer(0),
	m_pTarget(NULL),
	m_eAttackMode(AM_NONE),
	m_bStop(true), m_bOnAttack(false)
{

	m_eComponentParentType = PT_NONE;
	m_eComponentType = CT_ATTACK;
}


CAttack::~CAttack()
{
	if (m_pButton)
		delete m_pButton;
}

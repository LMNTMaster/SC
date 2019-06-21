#include "AdvancedBuild.h"
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
#include "../Components/Cursor.h"
#include "UnitStatus.h"
#include "Transform.h"
#include "Move.h"
#include "../Timer.h"
#include "Gather.h"



void CAdvancedBuild::CancelBuild()
{
	CScene* pScene = GET_SINGLE(CSceneManager)->GetCurrentScene();
	pScene->FindLayer("System")->FindGameObject("Cursor")->GetComponent<CCursor>()->EndBuildMode();
}

void CAdvancedBuild::Start()
{

	CScene* pScene = GET_SINGLE(CSceneManager)->GetCurrentScene();
	CPlayer* pPlayer = pScene->GetLayer("System")->FindGameObject("Player")->GetComponent<CPlayer>();
	m_pButton = new CConsoleButton;
	m_pGameObject->AddButton(m_pButton);

	if (m_pGameObject->GetName() == "SCV")
	{
		m_pButton->SetUpIconTexture(GET_SINGLE(CResourceManager)->FindTexture("ControlButton_Icon_TerranBuild_Normal"));
		m_pButton->SetDownIconTexture(GET_SINGLE(CResourceManager)->FindTexture("ControlButton_Icon_TerranBuild_Press"));

		m_pButton->SetRequireCursor(false);
		m_pButton->SetButtonName("Advanced Build");
		m_pButton->SetPanelIndex(7);
		m_pButton->SetExistNextPage(true);
		m_pButton->SetShortcutKey('V');
		m_pButton->SetButtonComponent(this);

		auto func = [&](CVector2 position, CGameObject* pTarget) {};
		m_pButton->SetFunction(func);


		//Next Page
		vector<CConsoleButton*> vecNextPage;
		vecNextPage.resize(9);

		for (int i = 0; i < 9; ++i)
		{
			vecNextPage[i] = NULL;
		}

		{
			CConsoleButton* pFactory = new CConsoleButton;
			pFactory->SetButtonName("Factory");
			pFactory->SetRequireCursor(true);
			pFactory->SetRequireBuildMode(true);
			pFactory->SetPanelIndex(0);
			pFactory->SetShortcutKey('F');
			pFactory->SetUpIconTexture(GET_SINGLE(CResourceManager)->FindTexture("ControlButton_Icon_TerranFactory_Normal"));
			pFactory->SetDownIconTexture(GET_SINGLE(CResourceManager)->FindTexture("ControlButton_Icon_TerranFactory_Pressed"));
			pFactory->SetButtonComponent(this);
			pFactory->SetExistNextPage(true);

			//CControlButton 내에서 clone 해줌.
			pFactory->SetAdvanced(true);
			pFactory->SetBuildTarget(GET_SINGLE(CResourceManager)->FindUnit("Factory"));
			{
				//Next Page
				vector<CConsoleButton*> vecNextPage2;
				vecNextPage2.resize(9);

				for (int i = 0; i < 9; ++i)
				{
					vecNextPage2[i] = NULL;
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
					CancelBuild();
					GET_SINGLE(CConsoleButtonManager)->UpdateControlPanel(m_pGameObject);
				};

				vecNextPage2[8] = pCancelButton;
				pCancelButton->SetFunction(cancel);
				pFactory->SetNextPage(vecNextPage2);
			}

			auto func = [&](CVector2 position, CGameObject* pTarget)
			{
				GET_SINGLE(CConsoleButtonManager)->UpdateControlPanel(m_pGameObject);
			};

			vecNextPage[0] = pFactory;
			pFactory->SetFunction(func);

		}
		{
			CConsoleButton* pStructure = new CConsoleButton;
			pStructure->SetButtonName("Starport");
			pStructure->SetRequireCursor(true);
			pStructure->SetRequireBuildMode(true);
			pStructure->SetPanelIndex(1);
			pStructure->SetShortcutKey('S');
			pStructure->SetUpIconTexture(GET_SINGLE(CResourceManager)->FindTexture("ControlButton_Icon_TerranStarport_Normal"));
			pStructure->SetDownIconTexture(GET_SINGLE(CResourceManager)->FindTexture("ControlButton_Icon_TerranStarport_Pressed"));
			pStructure->SetButtonComponent(this);
			pStructure->SetExistNextPage(true);

			//CControlButton 내에서 clone 해줌.
			pStructure->SetAdvanced(true);
			pStructure->SetBuildTarget(GET_SINGLE(CResourceManager)->FindUnit("Starport"));
			{
				//Next Page
				vector<CConsoleButton*> vecNextPage2;
				vecNextPage2.resize(9);

				for (int i = 0; i < 9; ++i)
				{
					vecNextPage2[i] = NULL;
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
					CancelBuild();
					GET_SINGLE(CConsoleButtonManager)->UpdateControlPanel(m_pGameObject);
				};

				vecNextPage2[8] = pCancelButton;
				pCancelButton->SetFunction(cancel);
				pStructure->SetNextPage(vecNextPage2);
			}

			auto func = [&](CVector2 position, CGameObject* pTarget)
			{
				GET_SINGLE(CConsoleButtonManager)->UpdateControlPanel(m_pGameObject);
			};

			vecNextPage[1] = pStructure;
			pStructure->SetFunction(func);

		}

		{
			CConsoleButton* pStructure = new CConsoleButton;
			pStructure->SetButtonName("Science Facility");
			pStructure->SetRequireCursor(true);
			pStructure->SetRequireBuildMode(true);
			pStructure->SetPanelIndex(2);
			pStructure->SetShortcutKey('I');
			pStructure->SetUpIconTexture(GET_SINGLE(CResourceManager)->FindTexture("ControlButton_Icon_TerranScienceFacility_Normal"));
			pStructure->SetDownIconTexture(GET_SINGLE(CResourceManager)->FindTexture("ControlButton_Icon_TerranScienceFacility_Pressed"));
			pStructure->SetButtonComponent(this);
			pStructure->SetExistNextPage(true);

			//CControlButton 내에서 clone 해줌.
			pStructure->SetAdvanced(true);
			{
				//Next Page
				vector<CConsoleButton*> vecNextPage2;
				vecNextPage2.resize(9);

				for (int i = 0; i < 9; ++i)
				{
					vecNextPage2[i] = NULL;
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
					CancelBuild();
					GET_SINGLE(CConsoleButtonManager)->UpdateControlPanel(m_pGameObject);
				};

				vecNextPage2[8] = pCancelButton;
				pCancelButton->SetFunction(cancel);
				pStructure->SetNextPage(vecNextPage2);
			}

			pStructure->SetBuildTarget(GET_SINGLE(CResourceManager)->FindUnit("ScienceFacility"));
			auto func = [&](CVector2 position, CGameObject* pTarget)
			{
				GET_SINGLE(CConsoleButtonManager)->UpdateControlPanel(m_pGameObject);
			};

			vecNextPage[2] = pStructure;
			pStructure->SetFunction(func);
		}

		{
			CConsoleButton* pStructure = new CConsoleButton;
			pStructure->SetButtonName("Armory");
			pStructure->SetRequireCursor(true);
			pStructure->SetRequireBuildMode(true);
			pStructure->SetPanelIndex(3);
			pStructure->SetShortcutKey('A');
			pStructure->SetUpIconTexture(GET_SINGLE(CResourceManager)->FindTexture("ControlButton_Icon_TerranArmory_Normal"));
			pStructure->SetDownIconTexture(GET_SINGLE(CResourceManager)->FindTexture("ControlButton_Icon_TerranArmory_Pressed"));
			pStructure->SetButtonComponent(this);
			pStructure->SetExistNextPage(true);

			//CControlButton 내에서 clone 해줌.
			pStructure->SetAdvanced(true);
			pStructure->SetBuildTarget(GET_SINGLE(CResourceManager)->FindUnit("Armory"));
			{
				//Next Page
				vector<CConsoleButton*> vecNextPage2;
				vecNextPage2.resize(9);

				for (int i = 0; i < 9; ++i)
				{
					vecNextPage2[i] = NULL;
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
					CancelBuild();
					GET_SINGLE(CConsoleButtonManager)->UpdateControlPanel(m_pGameObject);
				};

				vecNextPage2[8] = pCancelButton;
				pCancelButton->SetFunction(cancel);
				pStructure->SetNextPage(vecNextPage2);
			}

			auto func = [&](CVector2 position, CGameObject* pTarget)
			{
				GET_SINGLE(CConsoleButtonManager)->UpdateControlPanel(m_pGameObject);
			};

			vecNextPage[3] = pStructure;
			pStructure->SetFunction(func);
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
}

void CAdvancedBuild::Update()
{
	if (!m_pButton)
	{
		if (!GetStart())
		{
			this->Start();
			SetStart(true);
		}
	}

	CScene* pScene = GET_SINGLE(CSceneManager)->GetCurrentScene();
	CPlayer* pPlayer = pScene->GetLayer("System")->FindGameObject("Player")->GetComponent<CPlayer>();
	//Factory
	if (pPlayer->GetMineral() < 200 || pPlayer->GetVespeneGas() < 100 || !pPlayer->FindOwnedStructure("Barracks"))
	{
		m_pButton->GetNextPage(0)->SetButtonState(BS_DISABLE);
	}
	else
	{
		m_pButton->GetNextPage(0)->SetButtonState(BS_ENABLE);
	}

	//Starport
	if (pPlayer->GetMineral() < 150 || pPlayer->GetVespeneGas() < 100 || !pPlayer->FindOwnedStructure("Factory"))
	{
		m_pButton->GetNextPage(1)->SetButtonState(BS_DISABLE);
	}
	else
	{
		m_pButton->GetNextPage(1)->SetButtonState(BS_ENABLE);
	}

	//Science Facility
	if (pPlayer->GetMineral() < 100 || pPlayer->GetVespeneGas() < 150 || !pPlayer->FindOwnedStructure("Starport"))
	{
		m_pButton->GetNextPage(2)->SetButtonState(BS_DISABLE);
	}
	else
	{
		m_pButton->GetNextPage(2)->SetButtonState(BS_ENABLE);
	}

	//Armory
	if (pPlayer->GetMineral() < 100 || pPlayer->GetVespeneGas() < 60 || !pPlayer->FindOwnedStructure("Factory"))
	{
		m_pButton->GetNextPage(3)->SetButtonState(BS_DISABLE);
	}
	else
	{
		m_pButton->GetNextPage(3)->SetButtonState(BS_ENABLE);
	}


	if (m_pRequestedBuilding)
	{

		CVector2 position = m_pTransform->GetPosition();
		CVector2 targetPosition = m_pRequestedBuilding->GetTransform()->GetPosition();

		if (m_eBuildState != BS_BUILD)
		{
			CMove* pMove = m_pGameObject->GetComponent<CMove>();
			if (pMove)
			{
				pMove->Stop();
			}
			CGather* pGather = m_pGameObject->GetComponent<CGather>();
			if (pGather)
			{
				pGather->Stop();
			}

			m_pRequestedBuilding->GetComponent<CUnitStatus>()->SetCurrentHP(0);
			m_pRequestedBuilding->GetComponent<CUnitStatus>()->SetEnable(false);

			CSpriteRenderer* pRenderer = m_pRequestedBuilding->GetComponent<CSpriteRenderer>();
			pRenderer->ChangeCurrentClip(m_pRequestedBuilding->GetName() + "Build");


			if ((position - targetPosition).length() > 96)
			{
				m_eBuildState = BS_MOVETOBUILD;
			}
			else
			{
				m_eBuildState = BS_BUILD;

				m_pGameObject->GetScene()->FindLayer("GroundUnit")->AddGameObject(m_pRequestedBuilding);
				m_pRequestedBuilding->GetComponent<CSpriteRenderer>()->ChangeCurrentClip(m_pRequestedBuilding->GetName() + "Build");
				m_pRequestedBuilding->SetPilot(m_pGameObject->GetPilot());
				m_pRequestedBuilding->SetToAirUnit(false);
				m_pRequestedBuilding->SetSelected(false);
			}
		}

		switch (m_eBuildState)
		{
		case BS_NONE:
			break;
		case BS_MOVETOBUILD:
		{
			m_pGameObject->GetComponent<CMove>()->RequestMove(targetPosition);
			m_fTimer = 0;
		}
		break;
		case BS_BUILD:
		{

			float deltaTime = GET_SINGLE(CTimer)->GetDeltaTime();
			float fBuildTime = m_pRequestedBuilding->GetComponent<CStructure>()->GetBuildTime();
			m_fTimer += deltaTime;
			float fProgress = m_fTimer / fBuildTime;
			float fHPMax = m_pRequestedBuilding->GetComponent<CUnitStatus>()->GetMaxHP();


			if (m_fTimer >= fBuildTime)
			{
				m_pRequestedBuilding->GetComponent<CUnitStatus>()->SetEnable(true);
				m_pRequestedBuilding->GetComponent<CSpriteRenderer>()->ChangeCurrentClip(m_pRequestedBuilding->GetName() + "Normal");
				m_eBuildState = BS_NONE;
				m_pRequestedBuilding = NULL;
				m_fTimer = 0;

				m_pGameObject->SetToAirUnit(false);

			}
			else
			{
				m_pRequestedBuilding->GetComponent<CUnitStatus>()->AddHP((fHPMax / fBuildTime) * deltaTime);
				m_fMoveTimer += deltaTime;

				if (m_fMoveTimer >= 5)
				{
					m_fMoveTimer -= 5;
					m_pGameObject->SetToAirUnit(true);
					CVector2 position = m_pTransform->GetPosition();
					CVector2 targetPosition = m_pRequestedBuilding->GetTransform()->GetPosition();

					CVector2 forwardPosition = (position - targetPosition).normalize() * 48;

					m_pGameObject->GetComponent<CMove>()->RequestMove(position + forwardPosition);
				}
				else
				{
					if (m_pGameObject->GetComponent<CMove>()->GetArrived())
					{
						string unitName = m_pGameObject->GetName();
						float fAngle = m_pTransform->GetRotation();
						CSpriteRenderer* pRenderer = m_pGameObject->GetComponent<CSpriteRenderer>();

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
								pRenderer->ChangeCurrentClip(unitName + "Attack12");
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
			}
		}
		break;
		default:
			break;
		}
	}
}

void CAdvancedBuild::SaveComponent(FILE * pFile)
{
}

void CAdvancedBuild::LoadComponent(FILE * pFile)
{
}

CComponent * CAdvancedBuild::clone()
{
	return new CAdvancedBuild(*this);
}

CAdvancedBuild::CAdvancedBuild(const CAdvancedBuild & component) :
	m_pRequestedBuilding(NULL)
{
	//m_pButton은 Start에서 생성해주기 때문에 따로 깊은복사 할 필요 없음.
	m_eComponentParentType = PT_NONE;
	m_eComponentType = CT_ADVANCED_BUILD;
}

CAdvancedBuild::CAdvancedBuild() :
	m_pRequestedBuilding(NULL)
{
	m_eComponentParentType = PT_NONE;
	m_eComponentType = CT_ADVANCED_BUILD;
}


CAdvancedBuild::~CAdvancedBuild()
{
	if (m_pButton)
		delete m_pButton;


}

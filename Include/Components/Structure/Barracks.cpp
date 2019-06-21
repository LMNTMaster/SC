#include "Barracks.h"
#include "../../GameObject.h"
#include "../Transform.h"
#include "../SpriteRenderer.h"
#include "../ControlButton.h"
#include "../../ConsoleButton.h"
#include "../../Components/Player.h"
#include "../../ConsoleButtonManager.h"
#include "../../SceneManager.h"
#include "../../ResourceManager.h"
#include "../../Scene.h"
#include "../../SceneManager.h"
#include "../../Layer.h"
#include "../Player.h"
#include "../../Component.h"
#include "../Move.h"
#include "../GameResource.h"
#include "../Stop.h"
#include "../UnitStatus.h"
#include "../../Timer.h"
#include "../UnitInfo.h"
#include "../../Texture.h"



void CBarracks::RequestUnit(CGameObject * pTarget, CTexture * pIconTexture)
{
	CScene* pScene = GET_SINGLE(CSceneManager)->GetCurrentScene();
	CPlayer* pPlayer = pScene->GetLayer("System")->FindGameObject("Player")->GetComponent<CPlayer>();	
	CUnitInfo* pInfo = m_pGameObject->GetComponent<CUnitInfo>();

	if (pPlayer->GetMineral() < pTarget->GetComponent<CUnitStatus>()->GetMineralRequirement())
	{
		GET_SINGLE(CResourceManager)->PlaySFX("ErrorMineral");
	}
	else if (pPlayer->GetVespeneGas() < pTarget->GetComponent<CUnitStatus>()->GetGasRequirement())
	{
		GET_SINGLE(CResourceManager)->PlaySFX("ErroeVespeneGas");
	}
	else if(pPlayer->GetMaxPopulation() - pPlayer->GetCurrentPopulation() < pTarget->GetComponent<CUnitStatus>()->GetSupplyRequirement())
	{
		GET_SINGLE(CResourceManager)->PlaySFX("ErrorSupply");
	}
	else
	{
		pInfo->AddQueue(pTarget, pIconTexture);
	}
}

void CBarracks::Start()
{
	CScene* pScene = GET_SINGLE(CSceneManager)->GetCurrentScene();
	CPlayer* pPlayer = pScene->GetLayer("System")->FindGameObject("Player")->GetComponent<CPlayer>();
	CUnitInfo* pInfo = m_pGameObject->GetComponent<CUnitInfo>();

#pragma region Marine
	{
		CConsoleButton* pButton = new CConsoleButton;
		m_ButtonList.push_back(pButton);

		m_pGameObject->AddButton(pButton);

		pButton->SetUpIconTexture(GET_SINGLE(CResourceManager)->FindTexture("ControlButton_Icon_TerranMarine_Normal"));
		pButton->SetDownIconTexture(GET_SINGLE(CResourceManager)->FindTexture("ControlButton_Icon_TerranMarine_Pressed"));

		pButton->SetRequireCursor(false);
		pButton->SetButtonName("Marine");
		pButton->SetPanelIndex(0);
		pButton->SetExistNextPage(false);
		pButton->SetShortcutKey('M');
		pButton->SetButtonComponent(this);

		auto func = [&](CVector2 position, CGameObject* pTarget)
		{
			CGameObject* pCreateTarget = GET_SINGLE(CResourceManager)->FindUnit("Marine");
			RequestUnit(pCreateTarget, pCreateTarget->GetComponent<CUnitInfo>()->GetUnitButtonTexture());
		};

		pButton->SetFunction(func);


		//Next Page
		vector<CConsoleButton*> vecNextPage;
		vecNextPage.resize(9);

		for (int i = 0; i < 9; ++i)
		{
			vecNextPage[i] = NULL;
		}
		
		pButton->SetNextPage(vecNextPage);

	}

#pragma endregion

#pragma region Firebat
	{
		CConsoleButton* pButton = new CConsoleButton;
		m_ButtonList.push_back(pButton);

		m_pGameObject->AddButton(pButton);

		pButton->SetUpIconTexture(GET_SINGLE(CResourceManager)->FindTexture("ControlButton_Icon_TerranFirebat_Normal"));
		pButton->SetDownIconTexture(GET_SINGLE(CResourceManager)->FindTexture("ControlButton_Icon_TerranFirebat_Pressed"));

		pButton->SetRequireCursor(false);
		pButton->SetButtonName("Firebat");
		pButton->SetPanelIndex(1);
		pButton->SetExistNextPage(false);
		pButton->SetShortcutKey('F');
		pButton->SetButtonComponent(this);

		auto func = [&](CVector2 position, CGameObject* pTarget)
		{
			CGameObject* pCreateTarget = GET_SINGLE(CResourceManager)->FindUnit("Firebat");
			RequestUnit(pCreateTarget, pCreateTarget->GetComponent<CUnitInfo>()->GetUnitButtonTexture());
		};

		pButton->SetFunction(func);


		//Next Page
		vector<CConsoleButton*> vecNextPage;
		vecNextPage.resize(9);

		for (int i = 0; i < 9; ++i)
		{
			vecNextPage[i] = NULL;
		}

		pButton->SetNextPage(vecNextPage);
	}

#pragma endregion

#pragma region Medic
	{
		CConsoleButton* pButton = new CConsoleButton;
		m_ButtonList.push_back(pButton);

		m_pGameObject->AddButton(pButton);

		pButton->SetUpIconTexture(GET_SINGLE(CResourceManager)->FindTexture("ControlButton_Icon_TerranMedic_Normal"));
		pButton->SetDownIconTexture(GET_SINGLE(CResourceManager)->FindTexture("ControlButton_Icon_TerranMedic_Pressed"));

		pButton->SetRequireCursor(false);
		pButton->SetButtonName("Medic");
		pButton->SetPanelIndex(3);
		pButton->SetExistNextPage(false);
		pButton->SetShortcutKey('C');
		pButton->SetButtonComponent(this);

		auto func = [&](CVector2 position, CGameObject* pTarget)
		{
			CGameObject* pCreateTarget = GET_SINGLE(CResourceManager)->FindUnit("Medic");
			RequestUnit(pCreateTarget, pCreateTarget->GetComponent<CUnitInfo>()->GetUnitButtonTexture());
		};

		pButton->SetFunction(func);


		//Next Page
		vector<CConsoleButton*> vecNextPage;
		vecNextPage.resize(9);

		for (int i = 0; i < 9; ++i)
		{
			vecNextPage[i] = NULL;
		}
		pButton->SetNextPage(vecNextPage);

	}
#pragma endregion

#pragma region Ghost
	{
		CConsoleButton* pButton = new CConsoleButton;
		m_ButtonList.push_back(pButton);

		m_pGameObject->AddButton(pButton);

		pButton->SetUpIconTexture(GET_SINGLE(CResourceManager)->FindTexture("ControlButton_Icon_TerranGhost_Normal"));
		pButton->SetDownIconTexture(GET_SINGLE(CResourceManager)->FindTexture("ControlButton_Icon_TerranGhost_Pressed"));

		pButton->SetRequireCursor(false);
		pButton->SetButtonName("Ghost");
		pButton->SetPanelIndex(2);
		pButton->SetExistNextPage(false);
		pButton->SetShortcutKey('G');
		pButton->SetButtonComponent(this);

		auto func = [&](CVector2 position, CGameObject* pTarget)
		{
			CGameObject* pCreateTarget = GET_SINGLE(CResourceManager)->FindUnit("Ghost");
			RequestUnit(pCreateTarget, pCreateTarget->GetComponent<CUnitInfo>()->GetUnitButtonTexture());
		};

		pButton->SetFunction(func);


		//Next Page
		vector<CConsoleButton*> vecNextPage;
		vecNextPage.resize(9);

		for (int i = 0; i < 9; ++i)
		{
			vecNextPage[i] = NULL;
		}

		pButton->SetNextPage(vecNextPage);

	}
#pragma endregion

}

void CBarracks::Update()
{
	CScene* pScene = GET_SINGLE(CSceneManager)->GetCurrentScene();
	CPlayer* pPlayer = pScene->GetLayer("System")->FindGameObject("Player")->GetComponent<CPlayer>();
	CUnitInfo* pInfo = m_pGameObject->GetComponent<CUnitInfo>();

	//모든 버튼들 enable / disable 설정	
	list<CConsoleButton*>::iterator iter;
	list<CConsoleButton*>::iterator iterEnd = m_ButtonList.end();
	for (iter = m_ButtonList.begin(); iter != iterEnd; ++iter)
	{
		if ((*iter)->GetShortcutKey() == 'M')
		{
			CUnitStatus* pStatus = GET_SINGLE(CResourceManager)->FindUnit("Marine")->GetComponent<CUnitStatus>();
			if (pPlayer->GetMineral() < pStatus->GetMineralRequirement() ||
				pPlayer->GetVespeneGas() < pStatus->GetGasRequirement() ||
				pPlayer->GetMaxPopulation() - pPlayer->GetCurrentPopulation() < pStatus->GetSupplyRequirement()||
				!pPlayer->FindOwnedStructure("Barracks"))
			{
				(*iter)->SetButtonState(BS_DISABLE);
			}
			else
			{
				(*iter)->SetButtonState(BS_ENABLE);
			}
		}
		else if ((*iter)->GetShortcutKey() == 'F')
		{
			CUnitStatus* pStatus = GET_SINGLE(CResourceManager)->FindUnit("Firebat")->GetComponent<CUnitStatus>();
			if (pPlayer->GetMineral() < pStatus->GetMineralRequirement() ||
				pPlayer->GetVespeneGas() < pStatus->GetGasRequirement() ||
				pPlayer->GetMaxPopulation() - pPlayer->GetCurrentPopulation() < pStatus->GetSupplyRequirement() ||
				!pPlayer->FindOwnedStructure("Academy"))
			{
				(*iter)->SetButtonState(BS_DISABLE);
			}
			else
			{
				(*iter)->SetButtonState(BS_ENABLE);
			}
		}
		else if ((*iter)->GetShortcutKey() == 'G')
		{
			CUnitStatus* pStatus = GET_SINGLE(CResourceManager)->FindUnit("Ghost")->GetComponent<CUnitStatus>();
			if (pPlayer->GetMineral() < pStatus->GetMineralRequirement() ||
				pPlayer->GetVespeneGas() < pStatus->GetGasRequirement() ||
				pPlayer->GetMaxPopulation() - pPlayer->GetCurrentPopulation() < pStatus->GetSupplyRequirement() ||
				!pPlayer->FindOwnedStructure("Science Facility"))
			{
				(*iter)->SetButtonState(BS_DISABLE);
			}
			else
			{
				(*iter)->SetButtonState(BS_ENABLE);
			}
		}
		else if ((*iter)->GetShortcutKey() == 'C')
		{
			CUnitStatus* pStatus = GET_SINGLE(CResourceManager)->FindUnit("Medic")->GetComponent<CUnitStatus>();
			if (pPlayer->GetMineral() < pStatus->GetMineralRequirement() ||
				pPlayer->GetVespeneGas() < pStatus->GetGasRequirement() ||
				pPlayer->GetMaxPopulation() - pPlayer->GetCurrentPopulation() < pStatus->GetSupplyRequirement() ||
				!pPlayer->FindOwnedStructure("Academy"))
			{
				(*iter)->SetButtonState(BS_DISABLE);
			}
			else
			{
				(*iter)->SetButtonState(BS_ENABLE);
			}
		}
	}


}

void CBarracks::SaveComponent(FILE * pFile)
{
}

void CBarracks::LoadComponent(FILE * pFile)
{
}

CComponent * CBarracks::clone()
{
	return new CBarracks(*this);
}

CBarracks::CBarracks(const CBarracks & component)
{
	m_eComponentType = CT_BARRACKS;
}

CBarracks::CBarracks()
{
	m_eComponentType = CT_BARRACKS;
}


CBarracks::~CBarracks()
{
	if (m_pButton)
		delete m_pButton;

	list<CConsoleButton*>::iterator iter;
	list<CConsoleButton*>::iterator iterEnd = m_ButtonList.end();
	for (iter = m_ButtonList.begin(); iter != iterEnd; ++iter)
	{
		delete *iter;			
	}
	m_ButtonList.clear();
}

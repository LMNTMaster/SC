#include "Factory.h"
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


void CFactory::RequestUnit(CGameObject * pTarget, CTexture * pIconTexture)
{
	CScene* pScene = GET_SINGLE(CSceneManager)->GetCurrentScene();
	CPlayer* pPlayer = pScene->GetLayer("System")->FindGameObject("Player")->GetComponent<CPlayer>();

	if (pPlayer->GetMineral() < pTarget->GetComponent<CUnitStatus>()->GetMineralRequirement())
	{
		GET_SINGLE(CResourceManager)->PlaySFX("ErrorMineral");
	}
	else if (pPlayer->GetVespeneGas() < pTarget->GetComponent<CUnitStatus>()->GetGasRequirement())
	{
		GET_SINGLE(CResourceManager)->PlaySFX("ErrorVespeneGas");
	}
	else if (pPlayer->GetMaxPopulation() - pPlayer->GetCurrentPopulation() < pTarget->GetComponent<CUnitStatus>()->GetSupplyRequirement())
	{
		GET_SINGLE(CResourceManager)->PlaySFX("ErrorSupply");
	}
	else
	{
		m_pGameObject->GetComponent<CUnitInfo>()->AddQueue(pTarget, pIconTexture);
	}
}

void CFactory::Start()
{
	CScene* pScene = GET_SINGLE(CSceneManager)->GetCurrentScene();
	CPlayer* pPlayer = pScene->GetLayer("System")->FindGameObject("Player")->GetComponent<CPlayer>();
	CUnitInfo* pInfo = m_pGameObject->GetComponent<CUnitInfo>();


#pragma region Vulture
	{
		m_pVulture = new CConsoleButton;

		m_pGameObject->AddButton(m_pVulture);

		m_pVulture->SetUpIconTexture(GET_SINGLE(CResourceManager)->FindTexture("ControlButton_Icon_TerranVulture_Normal"));
		m_pVulture->SetDownIconTexture(GET_SINGLE(CResourceManager)->FindTexture("ControlButton_Icon_TerranVulture_Pressed"));

		m_pVulture->SetRequireCursor(false);
		m_pVulture->SetButtonName("Vulture");
		m_pVulture->SetPanelIndex(0);
		m_pVulture->SetExistNextPage(false);
		m_pVulture->SetShortcutKey('V');
		m_pVulture->SetButtonComponent(this);

		auto func = [&](CVector2 position, CGameObject* pTarget)
		{
			CGameObject* pCreateTarget = GET_SINGLE(CResourceManager)->FindUnit("Vulture");
			RequestUnit(pCreateTarget, pCreateTarget->GetComponent<CUnitInfo>()->GetUnitButtonTexture());
		};

		m_pVulture->SetFunction(func);


		//Next Page
		vector<CConsoleButton*> vecNextPage;
		vecNextPage.resize(9);

		for (int i = 0; i < 9; ++i)
		{
			vecNextPage[i] = NULL;
		}

		m_pVulture->SetNextPage(vecNextPage);

	}

#pragma endregion


#pragma region Siege Tank
	{
		m_pSiegeTank = new CConsoleButton;

		m_pGameObject->AddButton(m_pSiegeTank);

		m_pSiegeTank->SetUpIconTexture(GET_SINGLE(CResourceManager)->FindTexture("ControlButton_Icon_TerranSiegeTank_Normal"));
		m_pSiegeTank->SetDownIconTexture(GET_SINGLE(CResourceManager)->FindTexture("ControlButton_Icon_TerranSiegeTank_Pressed"));

		m_pSiegeTank->SetRequireCursor(false);
		m_pSiegeTank->SetButtonName("Siege Tank");
		m_pSiegeTank->SetPanelIndex(1);
		m_pSiegeTank->SetExistNextPage(false);
		m_pSiegeTank->SetShortcutKey('T');
		m_pSiegeTank->SetButtonComponent(this);
		m_pSiegeTank->SetButtonState(BS_DISABLE);

		auto func = [&](CVector2 position, CGameObject* pTarget)
		{
			CGameObject* pCreateTarget = GET_SINGLE(CResourceManager)->FindUnit("SiegeTank");
			RequestUnit(pCreateTarget, pCreateTarget->GetComponent<CUnitInfo>()->GetUnitButtonTexture());
		};

		m_pSiegeTank->SetFunction(func);


		//Next Page
		vector<CConsoleButton*> vecNextPage;
		vecNextPage.resize(9);

		for (int i = 0; i < 9; ++i)
		{
			vecNextPage[i] = NULL;
		}

		m_pSiegeTank->SetNextPage(vecNextPage);

	}

#pragma endregion


#pragma region Goliath
	{
		m_pGoliath = new CConsoleButton;

		m_pGameObject->AddButton(m_pGoliath);

		m_pGoliath->SetUpIconTexture(GET_SINGLE(CResourceManager)->FindTexture("ControlButton_Icon_TerranGoliath_Normal"));
		m_pGoliath->SetDownIconTexture(GET_SINGLE(CResourceManager)->FindTexture("ControlButton_Icon_TerranGoliath_Pressed"));

		m_pGoliath->SetRequireCursor(false);
		m_pGoliath->SetButtonName("Goliath");
		m_pGoliath->SetPanelIndex(2);
		m_pGoliath->SetExistNextPage(false);
		m_pGoliath->SetShortcutKey('G');
		m_pGoliath->SetButtonComponent(this);
		m_pGoliath->SetButtonState(BS_DISABLE);

		auto func = [&](CVector2 position, CGameObject* pTarget)
		{
			CGameObject* pCreateTarget = GET_SINGLE(CResourceManager)->FindUnit("Goliath");
			RequestUnit(pCreateTarget, pCreateTarget->GetComponent<CUnitInfo>()->GetUnitButtonTexture());
		};

		m_pGoliath->SetFunction(func);


		//Next Page
		vector<CConsoleButton*> vecNextPage;
		vecNextPage.resize(9);

		for (int i = 0; i < 9; ++i)
		{
			vecNextPage[i] = NULL;
		}

		m_pGoliath->SetNextPage(vecNextPage);

	}

#pragma endregion



	
#pragma region Machine Shop
	{
		m_pAddon = new CConsoleButton;

		m_pGameObject->AddButton(m_pAddon);

		m_pAddon->SetUpIconTexture(GET_SINGLE(CResourceManager)->FindTexture("ControlButton_Icon_TerranMachineShop_Normal"));
		m_pAddon->SetDownIconTexture(GET_SINGLE(CResourceManager)->FindTexture("ControlButton_Icon_TerranMachineShop_Pressed"));

		m_pAddon->SetRequireCursor(false);
		m_pAddon->SetButtonName("Machine Shop");
		m_pAddon->SetPanelIndex(6);
		m_pAddon->SetExistNextPage(false);
		m_pAddon->SetShortcutKey('C');
		m_pAddon->SetButtonComponent(this);
		m_pAddon->SetButtonState(BS_DISABLE);

		auto func = [&](CVector2 position, CGameObject* pTarget)
		{
		};

		m_pAddon->SetFunction(func);


		//Next Page
		vector<CConsoleButton*> vecNextPage;
		vecNextPage.resize(9);

		for (int i = 0; i < 9; ++i)
		{
			vecNextPage[i] = NULL;
		}

		m_pAddon->SetNextPage(vecNextPage);

	}

#pragma endregion

}

void CFactory::Update()
{
	CScene* pScene = GET_SINGLE(CSceneManager)->GetCurrentScene();
	CPlayer* pPlayer = pScene->GetLayer("System")->FindGameObject("Player")->GetComponent<CPlayer>();
	
	if (!m_pVulture || !m_pAddon || !m_pGoliath || !m_pSiegeTank)
	{
		if (!GetStart())
		{
			Start();
			SetStart(true);
		}
	}

	if (pPlayer->GetMineral() < 75 ||
		pPlayer->GetVespeneGas() < 0 ||
		pPlayer->GetMaxPopulation() - pPlayer->GetCurrentPopulation() < 2 )
	{
		m_pVulture->SetButtonState(BS_DISABLE);
	}
	else
	{
		m_pVulture->SetButtonState(BS_ENABLE);
	}

	if (pPlayer->GetMineral() < 150 ||
		pPlayer->GetVespeneGas() < 100 ||
		pPlayer->GetMaxPopulation() - pPlayer->GetCurrentPopulation() <2 ||		
		!pPlayer->FindOwnedStructure("Machine Shop"))
	{
		m_pSiegeTank->SetButtonState(BS_DISABLE);
	}
	else
	{
		m_pSiegeTank->SetButtonState(BS_ENABLE);
	}


	if (pPlayer->GetMineral() < 100 ||
		pPlayer->GetVespeneGas() < 50 ||
		pPlayer->GetMaxPopulation() - pPlayer->GetCurrentPopulation() <2 ||
		!pPlayer->FindOwnedStructure("Machine Shop"))
	{
		m_pGoliath->SetButtonState(BS_DISABLE);
	}
	else
	{
		m_pGoliath->SetButtonState(BS_ENABLE);
	}


	if (pPlayer->GetMineral() < 9000000 ||
		pPlayer->GetVespeneGas() < 9000000 ||		
		!pPlayer->FindOwnedStructure("Factory") )
	{
		m_pAddon->SetButtonState(BS_DISABLE);
	}
	else
	{
		m_pAddon->SetButtonState(BS_ENABLE);
	}
}

void CFactory::SaveComponent(FILE * pFile)
{
}

void CFactory::LoadComponent(FILE * pFile)
{
}

CComponent * CFactory::clone()
{
	return new CFactory(*this);
}

CFactory::CFactory(const CFactory & component) :
	m_pVulture(NULL),
	m_pSiegeTank(NULL),
	m_pGoliath(NULL),
	m_pAddon(NULL)
{
	m_eComponentType = CT_FACTORY;
}

CFactory::CFactory():
	m_pVulture(NULL),
	m_pSiegeTank(NULL),
	m_pGoliath(NULL),
	m_pAddon(NULL)
{
	m_eComponentType = CT_FACTORY;
}


CFactory::~CFactory()
{
	if (m_pButton)
		delete m_pButton;

	if (m_pVulture)
		delete m_pVulture;
	if (m_pSiegeTank)
		delete m_pSiegeTank;
	if (m_pGoliath)
		delete m_pGoliath;

	if (m_pAddon)
	{
		delete m_pAddon;
		m_pAddon = NULL;
	}
}

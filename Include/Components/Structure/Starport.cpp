#include "Starport.h"
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



void CStarport::RequestUnit(CGameObject * pTarget, CTexture * pIconTexture)
{
	CScene* pScene = GET_SINGLE(CSceneManager)->GetCurrentScene();
	CPlayer* pPlayer = pScene->GetLayer("System")->FindGameObject("Player")->GetComponent<CPlayer>();
	CUnitStatus* pStatus = pTarget->GetComponent<CUnitStatus>();
	if (pPlayer->GetMineral() < pStatus->GetMineralRequirement())
	{
		GET_SINGLE(CResourceManager)->PlaySFX("ErrorMineral");
	}
	else if (pPlayer->GetVespeneGas() < pStatus->GetGasRequirement())
	{
		GET_SINGLE(CResourceManager)->PlaySFX("ErrorVespeneGas");
	}
	else if (pPlayer->GetMaxPopulation() - pPlayer->GetCurrentPopulation() < pStatus->GetSupplyRequirement())
	{
		GET_SINGLE(CResourceManager)->PlaySFX("ErrorSupply");
	}
	else
	{
		m_pGameObject->GetComponent<CUnitInfo>()->AddQueue(pTarget, pIconTexture);
	}
}

void CStarport::Start()
{
	CScene* pScene = GET_SINGLE(CSceneManager)->GetCurrentScene();
	CPlayer* pPlayer = pScene->GetLayer("System")->FindGameObject("Player")->GetComponent<CPlayer>();
	CUnitInfo* pInfo = m_pGameObject->GetComponent<CUnitInfo>();

#pragma region Wraith
	{
		m_pWraith = new CConsoleButton;

		m_pGameObject->AddButton(m_pWraith);

		m_pWraith->SetUpIconTexture(GET_SINGLE(CResourceManager)->FindTexture("ControlButton_Icon_TerranWraith_Normal"));
		m_pWraith->SetDownIconTexture(GET_SINGLE(CResourceManager)->FindTexture("ControlButton_Icon_TerranWraith_Pressed"));

		m_pWraith->SetRequireCursor(false);
		m_pWraith->SetButtonName("Wraith");
		m_pWraith->SetPanelIndex(0);
		m_pWraith->SetExistNextPage(false);
		m_pWraith->SetShortcutKey('W');
		m_pWraith->SetButtonComponent(this);

		auto func = [&](CVector2 position, CGameObject* pTarget)
		{
			CGameObject* pCreateTarget = GET_SINGLE(CResourceManager)->FindUnit("Wraith");
			RequestUnit(pCreateTarget, pCreateTarget->GetComponent<CUnitInfo>()->GetUnitButtonTexture());
		};
		m_pWraith->SetFunction(func);

		//Next Page
		vector<CConsoleButton*> vecNextPage;
		vecNextPage.resize(9);

		for (int i = 0; i < 9; ++i)
		{
			vecNextPage[i] = NULL;
		}

		m_pWraith->SetNextPage(vecNextPage);

	}

#pragma endregion

#pragma region Drop Ship
	{
		m_pDropship = new CConsoleButton;

		m_pGameObject->AddButton(m_pDropship);

		m_pDropship->SetUpIconTexture(GET_SINGLE(CResourceManager)->FindTexture("ControlButton_Icon_TerranDropship_Normal"));
		m_pDropship->SetDownIconTexture(GET_SINGLE(CResourceManager)->FindTexture("ControlButton_Icon_TerranDropship_Pressed"));

		m_pDropship->SetRequireCursor(false);
		m_pDropship->SetButtonName("Dropship");
		m_pDropship->SetPanelIndex(1);
		m_pDropship->SetExistNextPage(false);
		m_pDropship->SetShortcutKey('D');
		m_pDropship->SetButtonComponent(this);

		auto func = [&](CVector2 position, CGameObject* pTarget)
		{
			CGameObject* pCreateTarget = GET_SINGLE(CResourceManager)->FindUnit("Dropship");
			RequestUnit(pCreateTarget, pCreateTarget->GetComponent<CUnitInfo>()->GetUnitButtonTexture());
		};
		m_pDropship->SetFunction(func);

		//Next Page
		vector<CConsoleButton*> vecNextPage;
		vecNextPage.resize(9);

		for (int i = 0; i < 9; ++i)
		{
			vecNextPage[i] = NULL;
		}

		m_pDropship->SetNextPage(vecNextPage);

	}

#pragma endregion

#pragma region Science Vessel
	{
		m_pScienceVessel = new CConsoleButton;

		m_pGameObject->AddButton(m_pScienceVessel);

		m_pScienceVessel->SetUpIconTexture(GET_SINGLE(CResourceManager)->FindTexture("ControlButton_Icon_TerranScienceVessel_Normal"));
		m_pScienceVessel->SetDownIconTexture(GET_SINGLE(CResourceManager)->FindTexture("ControlButton_Icon_TerranScienceVessel_Pressed"));

		m_pScienceVessel->SetRequireCursor(false);
		m_pScienceVessel->SetButtonName("Science Vessel");
		m_pScienceVessel->SetPanelIndex(2);
		m_pScienceVessel->SetExistNextPage(false);
		m_pScienceVessel->SetShortcutKey('V');
		m_pScienceVessel->SetButtonComponent(this);

		auto func = [&](CVector2 position, CGameObject* pTarget)
		{
			CGameObject* pCreateTarget = GET_SINGLE(CResourceManager)->FindUnit("Science Vessel");
			RequestUnit(pCreateTarget, pCreateTarget->GetComponent<CUnitInfo>()->GetUnitButtonTexture());
		};
		m_pScienceVessel->SetFunction(func);

		//Next Page
		vector<CConsoleButton*> vecNextPage;
		vecNextPage.resize(9);

		for (int i = 0; i < 9; ++i)
		{
			vecNextPage[i] = NULL;
		}

		m_pScienceVessel->SetNextPage(vecNextPage);

	}

#pragma endregion

#pragma region Battlecruiser
	{
		m_pBattlecruiser = new CConsoleButton;

		m_pGameObject->AddButton(m_pBattlecruiser);

		m_pBattlecruiser->SetUpIconTexture(GET_SINGLE(CResourceManager)->FindTexture("ControlButton_Icon_TerranBattlecruiser_Normal"));
		m_pBattlecruiser->SetDownIconTexture(GET_SINGLE(CResourceManager)->FindTexture("ControlButton_Icon_TerranBattlecruiser_Pressed"));

		m_pBattlecruiser->SetRequireCursor(false);
		m_pBattlecruiser->SetButtonName("Battlecruiser");
		m_pBattlecruiser->SetPanelIndex(3);
		m_pBattlecruiser->SetExistNextPage(false);
		m_pBattlecruiser->SetShortcutKey('B');
		m_pBattlecruiser->SetButtonComponent(this);

		auto func = [&](CVector2 position, CGameObject* pTarget)
		{
			CGameObject* pCreateTarget = GET_SINGLE(CResourceManager)->FindUnit("Battlecruiser");
			RequestUnit(pCreateTarget, pCreateTarget->GetComponent<CUnitInfo>()->GetUnitButtonTexture());
		};
		m_pBattlecruiser->SetFunction(func);

		//Next Page
		vector<CConsoleButton*> vecNextPage;
		vecNextPage.resize(9);

		for (int i = 0; i < 9; ++i)
		{
			vecNextPage[i] = NULL;
		}

		m_pBattlecruiser->SetNextPage(vecNextPage);

	}

#pragma endregion
	
#pragma region Valkyrie
	{
		m_pValkyrie = new CConsoleButton;

		m_pGameObject->AddButton(m_pValkyrie);

		m_pValkyrie->SetUpIconTexture(GET_SINGLE(CResourceManager)->FindTexture("ControlButton_Icon_TerranValkyrie_Normal"));
		m_pValkyrie->SetDownIconTexture(GET_SINGLE(CResourceManager)->FindTexture("ControlButton_Icon_TerranValkyrie_Pressed"));

		m_pValkyrie->SetRequireCursor(false);
		m_pValkyrie->SetButtonName("Valkyrie");
		m_pValkyrie->SetPanelIndex(4);
		m_pValkyrie->SetExistNextPage(false);
		m_pValkyrie->SetShortcutKey('Y');
		m_pValkyrie->SetButtonComponent(this);

		auto func = [&](CVector2 position, CGameObject* pTarget)
		{
			CGameObject* pCreateTarget = GET_SINGLE(CResourceManager)->FindUnit("Valkyrie");
			RequestUnit(pCreateTarget, pCreateTarget->GetComponent<CUnitInfo>()->GetUnitButtonTexture());
		};
		m_pValkyrie->SetFunction(func);

		//Next Page
		vector<CConsoleButton*> vecNextPage;
		vecNextPage.resize(9);

		for (int i = 0; i < 9; ++i)
		{
			vecNextPage[i] = NULL;
		}

		m_pValkyrie->SetNextPage(vecNextPage);
	}

#pragma endregion

#pragma region Control Tower
	{
		m_pAddon = new CConsoleButton;

		m_pGameObject->AddButton(m_pAddon);

		m_pAddon->SetUpIconTexture(GET_SINGLE(CResourceManager)->FindTexture("ControlButton_Icon_TerranControlTower_Normal"));
		m_pAddon->SetDownIconTexture(GET_SINGLE(CResourceManager)->FindTexture("ControlButton_Icon_TerranControlTower_Pressed"));

		m_pAddon->SetRequireCursor(false);
		m_pAddon->SetButtonName("Control Tower");
		m_pAddon->SetPanelIndex(6);
		m_pAddon->SetExistNextPage(false);
		m_pAddon->SetShortcutKey('C');
		m_pAddon->SetButtonComponent(this);

		auto func = [&](CVector2 position, CGameObject* pTarget)
		{
			//CGameObject* pCreateTarget = GET_SINGLE(CResourceManager)->FindUnit("Valkyrie");
			//RequestUnit(pCreateTarget, pCreateTarget->GetComponent<CUnitInfo>()->GetUnitButtonTexture());
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

void CStarport::Update()
{

	if (!m_pWraith || !m_pDropship || !m_pScienceVessel || !m_pBattlecruiser || !m_pAddon)
	{
		if (!GetStart())
		{
			Start();
			SetStart(true);
		}
	}


	CScene* pScene = GET_SINGLE(CSceneManager)->GetCurrentScene();
	CPlayer* pPlayer = pScene->GetLayer("System")->FindGameObject("Player")->GetComponent<CPlayer>();
	CUnitInfo* pInfo = m_pGameObject->GetComponent<CUnitInfo>();

	if (pPlayer->GetMineral() < 150 || pPlayer->GetVespeneGas() < 100 || pPlayer->GetMaxPopulation() - pPlayer->GetCurrentPopulation() < 2)
	{
		m_pWraith->SetButtonState(BS_DISABLE);
	}
	else
	{
		m_pWraith->SetButtonState(BS_ENABLE);
	}

	if (pPlayer->GetMineral() < 100 || pPlayer->GetVespeneGas() < 100 ||
		pPlayer->GetMaxPopulation() - pPlayer->GetCurrentPopulation() < 2 ||
		!pPlayer->FindOwnedStructure("Control Tower"))
	{
		m_pDropship->SetButtonState(BS_DISABLE);
	}
	else
	{
		m_pDropship->SetButtonState(BS_ENABLE);
	}

	if (pPlayer->GetMineral() < 100 || pPlayer->GetVespeneGas() < 225 ||
		pPlayer->GetMaxPopulation() - pPlayer->GetCurrentPopulation() < 2 ||
		!pPlayer->FindOwnedStructure("Control Tower"))
	{
		m_pScienceVessel->SetButtonState(BS_DISABLE);
	}
	else
	{
		m_pScienceVessel->SetButtonState(BS_ENABLE);
	}

	if (pPlayer->GetMineral() < 400|| pPlayer->GetVespeneGas() < 300 ||
		pPlayer->GetMaxPopulation() - pPlayer->GetCurrentPopulation() < 6 ||
		!pPlayer->FindOwnedStructure("Science Facility"))
	{
		m_pBattlecruiser->SetButtonState(BS_DISABLE);
	}
	else
	{
		m_pBattlecruiser->SetButtonState(BS_ENABLE);
	}

	if (pPlayer->GetMineral() < 900000 || pPlayer->GetVespeneGas() < 900000 ||
		!pPlayer->FindOwnedStructure("Control Tower"))
	{
		m_pValkyrie->SetButtonState(BS_DISABLE);
	}
	else
	{
		m_pValkyrie->SetButtonState(BS_ENABLE);
	}


}

void CStarport::SaveComponent(FILE * pFile)
{
}

void CStarport::LoadComponent(FILE * pFile)
{
}

CComponent * CStarport::clone()
{
	return new CStarport(*this);
}

CStarport::CStarport(const CStarport & component) :
	m_pWraith(NULL),
	m_pDropship(NULL),
	m_pScienceVessel(NULL),
	m_pBattlecruiser(NULL),
	m_pValkyrie(NULL),
	m_pAddon(NULL)
{
	m_eComponentType = CT_STARPORT;
}

CStarport::CStarport():
	m_pWraith(NULL),
	m_pDropship(NULL),
	m_pScienceVessel(NULL),
	m_pBattlecruiser(NULL),
	m_pValkyrie(NULL),
	m_pAddon(NULL)
{
	m_eComponentType = CT_STARPORT;
}


CStarport::~CStarport()
{
	if (m_pButton)
		delete m_pButton;
	if (m_pWraith)
		delete m_pWraith;
	if (m_pDropship)
		delete m_pDropship;
	if (m_pScienceVessel)
		delete m_pScienceVessel;
	if (m_pBattlecruiser)
		delete m_pBattlecruiser;
	if (m_pValkyrie)
		delete m_pValkyrie;
	if (m_pAddon)
		delete m_pAddon;
}

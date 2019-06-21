#include "Academy.h"
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
#include "../Attack.h"



void CAcademy::UpgradeU238()
{
	CScene* pScene = GET_SINGLE(CSceneManager)->GetCurrentScene();
	CPlayer* pPlayer = pScene->GetLayer("System")->FindGameObject("Player")->GetComponent<CPlayer>();

	if (pPlayer->GetUpgrade(UT_TERRAN_U238) == 0)
	{
		if (pPlayer->GetMineral() < 150)
		{
			GET_SINGLE(CResourceManager)->PlaySFX("ErrorMineral");
		}
		else if (pPlayer->GetVespeneGas() < 150)
		{
			GET_SINGLE(CResourceManager)->PlaySFX("ErrorVespeneGas");
		}
		else
		{
			pPlayer->SetUpgrade(UT_TERRAN_U238, 1);
			pPlayer->AddMineral(-150);
			pPlayer->AddVespeneGas(-150);
			GET_SINGLE(CResourceManager)->PlaySFX("CompleteResearch");
		}
	}

}

void CAcademy::UpgradeOpticalFlare()
{
	CScene* pScene = GET_SINGLE(CSceneManager)->GetCurrentScene();
	CPlayer* pPlayer = pScene->GetLayer("System")->FindGameObject("Player")->GetComponent<CPlayer>();

	if (pPlayer->GetUpgrade(UT_TERRAN_OPTICAL_FLARE) == 0)
	{
		if (pPlayer->GetMineral() < 100)
		{
			GET_SINGLE(CResourceManager)->PlaySFX("ErrorMineral");
		}
		else if (pPlayer->GetVespeneGas() < 100)
		{
			GET_SINGLE(CResourceManager)->PlaySFX("ErrorVespeneGas");
		}
		else
		{
			pPlayer->SetUpgrade(UT_TERRAN_OPTICAL_FLARE, 1);
			pPlayer->AddMineral(-100);
			pPlayer->AddVespeneGas(-100);
			GET_SINGLE(CResourceManager)->PlaySFX("CompleteResearch");
		}
	}

}

void CAcademy::UpgradeStimpack()
{
	CScene* pScene = GET_SINGLE(CSceneManager)->GetCurrentScene();
	CPlayer* pPlayer = pScene->GetLayer("System")->FindGameObject("Player")->GetComponent<CPlayer>();

	if (pPlayer->GetUpgrade(UT_TERRAN_STIMPACK) == 0)
	{
		if (pPlayer->GetMineral() < 100)
		{
			GET_SINGLE(CResourceManager)->PlaySFX("ErrorMineral");
		}
		else if (pPlayer->GetVespeneGas() < 100)
		{
			GET_SINGLE(CResourceManager)->PlaySFX("ErrorVespeneGas");
		}
		else
		{
			pPlayer->SetUpgrade(UT_TERRAN_STIMPACK, 1);
			pPlayer->AddMineral(-100);
			pPlayer->AddVespeneGas(-100);
			GET_SINGLE(CResourceManager)->PlaySFX("CompleteResearch");
		}
	}

}

void CAcademy::UpgradeCaduceusReactor()
{
	CScene* pScene = GET_SINGLE(CSceneManager)->GetCurrentScene();
	CPlayer* pPlayer = pScene->GetLayer("System")->FindGameObject("Player")->GetComponent<CPlayer>();

	if (pPlayer->GetUpgrade(UT_TERRAN_CADUCEUS_REACTOR) == 0)
	{
		if (pPlayer->GetMineral() < 150)
		{
			GET_SINGLE(CResourceManager)->PlaySFX("ErrorMineral");
		}
		else if (pPlayer->GetVespeneGas() < 150)
		{
			GET_SINGLE(CResourceManager)->PlaySFX("ErrorVespeneGas");
		}
		else
		{
			pPlayer->SetUpgrade(UT_TERRAN_CADUCEUS_REACTOR, 1);
			pPlayer->AddMineral(-150);
			pPlayer->AddVespeneGas(-150);
			GET_SINGLE(CResourceManager)->PlaySFX("CompleteResearch");
		}
	}

}

void CAcademy::UpgradeRestoration()
{
	CScene* pScene = GET_SINGLE(CSceneManager)->GetCurrentScene();
	CPlayer* pPlayer = pScene->GetLayer("System")->FindGameObject("Player")->GetComponent<CPlayer>();

	if (pPlayer->GetUpgrade(UT_TERRAN_RESTORATION) == 0)
	{
		if (pPlayer->GetMineral() < 100)
		{
			GET_SINGLE(CResourceManager)->PlaySFX("ErrorMineral");
		}
		else if (pPlayer->GetVespeneGas() < 100)
		{
			GET_SINGLE(CResourceManager)->PlaySFX("ErrorVespeneGas");
		}
		else
		{
			pPlayer->SetUpgrade(UT_TERRAN_RESTORATION, 1);
			pPlayer->AddMineral(-100);
			pPlayer->AddVespeneGas(-100);
			GET_SINGLE(CResourceManager)->PlaySFX("CompleteResearch");
		}
	}
}

void CAcademy::RequestCancel()
{
}

void CAcademy::Start()
{
	CScene* pScene = GET_SINGLE(CSceneManager)->GetCurrentScene();
	CPlayer* pPlayer = pScene->GetLayer("System")->FindGameObject("Player")->GetComponent<CPlayer>();
	
	{
		m_pU238 = new CConsoleButton;

		m_pGameObject->AddButton(m_pU238);

		m_pU238->SetUpIconTexture(GET_SINGLE(CResourceManager)->FindTexture("ControlButton_Icon_TerranU238_Normal"));
		m_pU238->SetDownIconTexture(GET_SINGLE(CResourceManager)->FindTexture("ControlButton_Icon_TerranU238_Pressed"));

		m_pU238->SetRequireCursor(false);
		m_pU238->SetButtonName("U-238 Shells");
		m_pU238->SetPanelIndex(0);
		m_pU238->SetExistNextPage(false);
		m_pU238->SetShortcutKey('U');
		m_pU238->SetButtonComponent(this);

		auto func = [&](CVector2 position, CGameObject* pTarget)
		{
			UpgradeU238();
		};

		m_pU238->SetFunction(func);


		//Next Page
		vector<CConsoleButton*> vecNextPage;
		vecNextPage.resize(9);

		for (int i = 0; i < 9; ++i)
		{
			vecNextPage[i] = NULL;
		}
		m_pU238->SetNextPage(vecNextPage);

	}

	{
		m_pStimpack = new CConsoleButton;

		m_pGameObject->AddButton(m_pStimpack);

		m_pStimpack->SetUpIconTexture(GET_SINGLE(CResourceManager)->FindTexture("ControlButton_Icon_TerranStimpack_Normal"));
		m_pStimpack->SetDownIconTexture(GET_SINGLE(CResourceManager)->FindTexture("ControlButton_Icon_TerranStimpack_Pressed"));

		m_pStimpack->SetRequireCursor(false);
		m_pStimpack->SetButtonName("Stimpack");
		m_pStimpack->SetPanelIndex(1);
		m_pStimpack->SetExistNextPage(false);
		m_pStimpack->SetShortcutKey('T');
		m_pStimpack->SetButtonComponent(this);

		auto func = [&](CVector2 position, CGameObject* pTarget)
		{
			UpgradeStimpack();
		};

		m_pStimpack->SetFunction(func);


		//Next Page
		vector<CConsoleButton*> vecNextPage;
		vecNextPage.resize(9);

		for (int i = 0; i < 9; ++i)
		{
			vecNextPage[i] = NULL;
		}
		m_pStimpack->SetNextPage(vecNextPage);
	}

	{
		m_pRestoration = new CConsoleButton;

		m_pGameObject->AddButton(m_pRestoration);

		m_pRestoration->SetUpIconTexture(GET_SINGLE(CResourceManager)->FindTexture("ControlButton_Icon_TerranRestoration_Normal"));
		m_pRestoration->SetDownIconTexture(GET_SINGLE(CResourceManager)->FindTexture("ControlButton_Icon_TerranRestoration_Pressed"));

		m_pRestoration->SetRequireCursor(false);
		m_pRestoration->SetButtonName("Restoration");
		m_pRestoration->SetPanelIndex(3);
		m_pRestoration->SetExistNextPage(false);
		m_pRestoration->SetShortcutKey('R');
		m_pRestoration->SetButtonComponent(this);

		auto func = [&](CVector2 position, CGameObject* pTarget)
		{
			UpgradeRestoration();
		};

		m_pRestoration->SetFunction(func);


		//Next Page
		vector<CConsoleButton*> vecNextPage;
		vecNextPage.resize(9);

		for (int i = 0; i < 9; ++i)
		{
			vecNextPage[i] = NULL;
		}
		m_pRestoration->SetNextPage(vecNextPage);

	}

	{
		m_pOpticalFlare = new CConsoleButton;

		m_pGameObject->AddButton(m_pOpticalFlare);

		m_pOpticalFlare->SetUpIconTexture(GET_SINGLE(CResourceManager)->FindTexture("ControlButton_Icon_TerranOpticalFlare_Normal"));
		m_pOpticalFlare->SetDownIconTexture(GET_SINGLE(CResourceManager)->FindTexture("ControlButton_Icon_TerranOpticalFlare_Pressed"));

		m_pOpticalFlare->SetRequireCursor(false);
		m_pOpticalFlare->SetButtonName("Optical Flare");
		m_pOpticalFlare->SetPanelIndex(4);
		m_pOpticalFlare->SetExistNextPage(false);
		m_pOpticalFlare->SetShortcutKey('F');
		m_pOpticalFlare->SetButtonComponent(this);

		auto func = [&](CVector2 position, CGameObject* pTarget)
		{
			UpgradeOpticalFlare();
		};

		m_pOpticalFlare->SetFunction(func);


		//Next Page
		vector<CConsoleButton*> vecNextPage;
		vecNextPage.resize(9);

		for (int i = 0; i < 9; ++i)
		{
			vecNextPage[i] = NULL;
		}
		m_pOpticalFlare->SetNextPage(vecNextPage);

	}

	{
		m_pCaduceusReactor = new CConsoleButton;

		m_pGameObject->AddButton(m_pCaduceusReactor);

		m_pCaduceusReactor->SetUpIconTexture(GET_SINGLE(CResourceManager)->FindTexture("ControlButton_Icon_TerranCaduceusReactor_Normal"));
		m_pCaduceusReactor->SetDownIconTexture(GET_SINGLE(CResourceManager)->FindTexture("ControlButton_Icon_TerranCaduceusReactor_Pressed"));

		m_pCaduceusReactor->SetRequireCursor(false);
		m_pCaduceusReactor->SetButtonName("Caduceus Reactor");
		m_pCaduceusReactor->SetPanelIndex(5);
		m_pCaduceusReactor->SetExistNextPage(false);
		m_pCaduceusReactor->SetShortcutKey('D');
		m_pCaduceusReactor->SetButtonComponent(this);

		auto func = [&](CVector2 position, CGameObject* pTarget)
		{
			UpgradeCaduceusReactor();
		};

		m_pCaduceusReactor->SetFunction(func);


		//Next Page
		vector<CConsoleButton*> vecNextPage;
		vecNextPage.resize(9);

		for (int i = 0; i < 9; ++i)
		{
			vecNextPage[i] = NULL;
		}

		m_pCaduceusReactor->SetNextPage(vecNextPage);

	}

}

void CAcademy::Update()
{
	CScene* pScene = GET_SINGLE(CSceneManager)->GetCurrentScene();
	CPlayer* pPlayer = pScene->GetLayer("System")->FindGameObject("Player")->GetComponent<CPlayer>();
	
	if (m_pU238)
	{
		if (pPlayer->GetUpgrade(UT_TERRAN_U238) == 0)
		{
			if (pPlayer->GetMineral() < 150 || pPlayer->GetVespeneGas() < 150 || !pPlayer->FindOwnedStructure("Engineering Bay"))
			{
				m_pU238->SetButtonState(BS_DISABLE);
			}
			else
			{
				m_pU238->SetButtonState(BS_ENABLE);
			}
		}
		else
		{			
			m_pGameObject->RemoveButton(m_pU238);
			delete m_pU238;
			m_pU238 = NULL;
		}
	}	

	if (m_pStimpack)
	{
		if (pPlayer->GetUpgrade(UT_TERRAN_STIMPACK) == 0)
		{
			if (pPlayer->GetMineral() < 100 || pPlayer->GetVespeneGas() < 100 || !pPlayer->FindOwnedStructure("Engineering Bay"))
			{
				m_pStimpack->SetButtonState(BS_DISABLE);
			}
			else
			{
				m_pStimpack->SetButtonState(BS_ENABLE);
			}
		}
		else
		{
			m_pGameObject->RemoveButton(m_pStimpack);
			delete m_pStimpack;
			m_pStimpack = NULL;
			GET_SINGLE(CConsoleButtonManager)->UpdateControlPanel(m_pGameObject);
		}
	}

	if (m_pRestoration)
	{
		if (pPlayer->GetUpgrade(UT_TERRAN_RESTORATION) == 0)
		{
			if (pPlayer->GetMineral() < 100 || pPlayer->GetVespeneGas() < 100 || !pPlayer->FindOwnedStructure("Engineering Bay"))
			{
				m_pRestoration->SetButtonState(BS_DISABLE);
			}
			else
			{
				m_pRestoration->SetButtonState(BS_ENABLE);
			}
		}
		else
		{
			m_pGameObject->RemoveButton(m_pRestoration);
			delete m_pRestoration;
			m_pRestoration = NULL;
		}
	}

	if (m_pOpticalFlare)
	{
		if (pPlayer->GetUpgrade(UT_TERRAN_OPTICAL_FLARE) == 0)
		{
			if (pPlayer->GetMineral() < 100 || pPlayer->GetVespeneGas() < 100 || !pPlayer->FindOwnedStructure("Engineering Bay"))
			{
				m_pOpticalFlare->SetButtonState(BS_DISABLE);
			}
			else
			{
				m_pOpticalFlare->SetButtonState(BS_ENABLE);
			}
		}
		else
		{
			m_pGameObject->RemoveButton(m_pOpticalFlare);
			delete m_pOpticalFlare;
			m_pOpticalFlare = NULL;
		}
	}
	
	if (m_pCaduceusReactor)
	{
		if (pPlayer->GetUpgrade(UT_TERRAN_CADUCEUS_REACTOR) == 0)
		{
			if (pPlayer->GetMineral() < 150 || pPlayer->GetVespeneGas() < 150 || !pPlayer->FindOwnedStructure("Engineering Bay"))
			{
				m_pCaduceusReactor->SetButtonState(BS_DISABLE);
			}
			else
			{
				m_pCaduceusReactor->SetButtonState(BS_ENABLE);
			}
		}
		else
		{
			m_pGameObject->RemoveButton(m_pCaduceusReactor);
			delete m_pCaduceusReactor;
			m_pCaduceusReactor = NULL;
		}
	}
}

void CAcademy::LateUpdate()
{
}

void CAcademy::LoadComponent(FILE * pFile)
{
}

void CAcademy::SaveComponent(FILE * pFile)
{
}

CComponent * CAcademy::clone()
{
	return new CAcademy(*this);
}
CAcademy::CAcademy(const CAcademy & component) :
	m_pU238(NULL),
	m_pOpticalFlare(NULL),
	m_pStimpack(NULL),
	m_pCaduceusReactor(NULL),
	m_pRestoration(NULL)
{
	m_eComponentType = CT_ACADEMY;
}

CAcademy::CAcademy():
	m_pU238(NULL),
	m_pOpticalFlare(NULL),
	m_pStimpack(NULL),
	m_pCaduceusReactor(NULL),
	m_pRestoration(NULL)
{
	m_eComponentType = CT_ACADEMY;
}

CAcademy::~CAcademy()
{
	if (m_pButton)
		delete m_pButton;
	if(m_pU238) 
		delete m_pU238;
	if(m_pOpticalFlare) 
		delete m_pOpticalFlare;
	if(m_pStimpack) 
		delete m_pStimpack;
	if(m_pCaduceusReactor) 
		delete m_pCaduceusReactor;
	if(m_pRestoration) 
		delete m_pRestoration;
}

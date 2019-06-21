#include "Armory.h"

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
#include "../UnitInfo.h"


void CArmory::UpgradeVehicleWeapon()
{
	CScene* pScene = GET_SINGLE(CSceneManager)->GetCurrentScene();
	CPlayer* pPlayer = pScene->GetLayer("System")->FindGameObject("Player")->GetComponent<CPlayer>();

	int iUpgradeValue = pPlayer->GetUpgrade(UT_TERRAN_MECHANIC_GROUND_WAEPON);
	if (iUpgradeValue == 0)
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
			pPlayer->AddMineral(-100);
			pPlayer->AddVespeneGas(-100);
			pPlayer->SetUpgrade(UT_TERRAN_MECHANIC_GROUND_WAEPON, 1);
			GET_SINGLE(CResourceManager)->PlaySFX("CompleteUpgrade");
		}
	}
	else	if (iUpgradeValue == 1)
	{
		if (pPlayer->GetMineral() < 175)
		{
			GET_SINGLE(CResourceManager)->PlaySFX("ErrorMineral");
		}
		else if (pPlayer->GetVespeneGas() < 175)
		{
			GET_SINGLE(CResourceManager)->PlaySFX("ErrorVespeneGas");
		}
		else
		{
			pPlayer->AddMineral(-175);
			pPlayer->AddVespeneGas(-175);
			pPlayer->SetUpgrade(UT_TERRAN_MECHANIC_GROUND_WAEPON, 2);
			GET_SINGLE(CResourceManager)->PlaySFX("CompleteUpgrade");
		}
	}
	else	if (iUpgradeValue == 2)
	{
		if (pPlayer->GetMineral() < 250)
		{
			GET_SINGLE(CResourceManager)->PlaySFX("ErrorMineral");
		}
		else if (pPlayer->GetVespeneGas() < 250)
		{
			GET_SINGLE(CResourceManager)->PlaySFX("ErrorVespeneGas");
		}
		else
		{
			pPlayer->AddMineral(-250);
			pPlayer->AddVespeneGas(-250);
			pPlayer->SetUpgrade(UT_TERRAN_MECHANIC_GROUND_WAEPON, 3);
			GET_SINGLE(CResourceManager)->PlaySFX("CompleteUpgrade");
		}
	}
}

void CArmory::UpgradeVehicleArmor()
{
	CScene* pScene = GET_SINGLE(CSceneManager)->GetCurrentScene();
	CPlayer* pPlayer = pScene->GetLayer("System")->FindGameObject("Player")->GetComponent<CPlayer>();

	int iUpgradeValue = pPlayer->GetUpgrade(UT_TERRAN_MECHANIC_GROUND_DEFFENCE);
	if (iUpgradeValue == 0)
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
			pPlayer->AddMineral(-100);
			pPlayer->AddVespeneGas(-100);
			pPlayer->SetUpgrade(UT_TERRAN_MECHANIC_GROUND_DEFFENCE, 1);
			GET_SINGLE(CResourceManager)->PlaySFX("CompleteUpgrade");
		}
	}
	else	if (iUpgradeValue == 1)
	{
		if (pPlayer->GetMineral() < 175)
		{
			GET_SINGLE(CResourceManager)->PlaySFX("ErrorMineral");
		}
		else if (pPlayer->GetVespeneGas() < 175)
		{
			GET_SINGLE(CResourceManager)->PlaySFX("ErrorVespeneGas");
		}
		else
		{
			pPlayer->AddMineral(-175);
			pPlayer->AddVespeneGas(-175);
			pPlayer->SetUpgrade(UT_TERRAN_MECHANIC_GROUND_DEFFENCE, 2);
			GET_SINGLE(CResourceManager)->PlaySFX("CompleteUpgrade");
		}
	}
	else	if (iUpgradeValue == 2)
	{
		if (pPlayer->GetMineral() < 250)
		{
			GET_SINGLE(CResourceManager)->PlaySFX("ErrorMineral");
		}
		else if (pPlayer->GetVespeneGas() < 250)
		{
			GET_SINGLE(CResourceManager)->PlaySFX("ErrorVespeneGas");
		}
		else
		{
			pPlayer->AddMineral(-250);
			pPlayer->AddVespeneGas(-250);
			pPlayer->SetUpgrade(UT_TERRAN_MECHANIC_GROUND_DEFFENCE, 3);
			GET_SINGLE(CResourceManager)->PlaySFX("CompleteUpgrade");
		}
	}
}

void CArmory::UpgradeShipWeapon()
{
	CScene* pScene = GET_SINGLE(CSceneManager)->GetCurrentScene();
	CPlayer* pPlayer = pScene->GetLayer("System")->FindGameObject("Player")->GetComponent<CPlayer>();

	int iUpgradeValue = pPlayer->GetUpgrade(UT_TERRAN_MECHANIC_AIR_WAEPON);
	if (iUpgradeValue == 0)
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
			pPlayer->AddMineral(-100);
			pPlayer->AddVespeneGas(-100);
			pPlayer->SetUpgrade(UT_TERRAN_MECHANIC_AIR_WAEPON, 1);
			GET_SINGLE(CResourceManager)->PlaySFX("CompleteUpgrade");
		}
	}
	else	if (iUpgradeValue == 1)
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
			pPlayer->AddMineral(-150);
			pPlayer->AddVespeneGas(-150);
			pPlayer->SetUpgrade(UT_TERRAN_MECHANIC_AIR_WAEPON, 2);
			GET_SINGLE(CResourceManager)->PlaySFX("CompleteUpgrade");
		}
	}
	else	if (iUpgradeValue == 2)
	{
		if (pPlayer->GetMineral() < 200)
		{
			GET_SINGLE(CResourceManager)->PlaySFX("ErrorMineral");
		}
		else if (pPlayer->GetVespeneGas() < 200)
		{
			GET_SINGLE(CResourceManager)->PlaySFX("ErrorVespeneGas");
		}
		else
		{
			pPlayer->AddMineral(-200);
			pPlayer->AddVespeneGas(-200);
			pPlayer->SetUpgrade(UT_TERRAN_MECHANIC_AIR_WAEPON, 3);
			GET_SINGLE(CResourceManager)->PlaySFX("CompleteUpgrade");
		}
	}
}

void CArmory::UpgradeShipArmor()
{
	CScene* pScene = GET_SINGLE(CSceneManager)->GetCurrentScene();
	CPlayer* pPlayer = pScene->GetLayer("System")->FindGameObject("Player")->GetComponent<CPlayer>();

	int iUpgradeValue = pPlayer->GetUpgrade(UT_TERRAN_MECHANIC_AIR_DEFFENCE);
	if (iUpgradeValue == 0)
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
			pPlayer->AddMineral(-150);
			pPlayer->AddVespeneGas(-150);
			pPlayer->SetUpgrade(UT_TERRAN_MECHANIC_AIR_DEFFENCE, 1);
			GET_SINGLE(CResourceManager)->PlaySFX("CompleteUpgrade");
		}
	}
	else	if (iUpgradeValue == 1)
	{
		if (pPlayer->GetMineral() < 225)
		{
			GET_SINGLE(CResourceManager)->PlaySFX("ErrorMineral");
		}
		else if (pPlayer->GetVespeneGas() < 225)
		{
			GET_SINGLE(CResourceManager)->PlaySFX("ErrorVespeneGas");
		}
		else
		{
			pPlayer->AddMineral(-225);
			pPlayer->AddVespeneGas(-225);
			pPlayer->SetUpgrade(UT_TERRAN_MECHANIC_AIR_DEFFENCE, 2);
			GET_SINGLE(CResourceManager)->PlaySFX("CompleteUpgrade");
		}
	}
	else	if (iUpgradeValue == 2)
	{
		if (pPlayer->GetMineral() < 300)
		{
			GET_SINGLE(CResourceManager)->PlaySFX("ErrorMineral");
		}
		else if (pPlayer->GetVespeneGas() < 300)
		{
			GET_SINGLE(CResourceManager)->PlaySFX("ErrorVespeneGas");
		}
		else
		{
			pPlayer->AddMineral(-300);
			pPlayer->AddVespeneGas(-300);
			pPlayer->SetUpgrade(UT_TERRAN_MECHANIC_AIR_DEFFENCE, 3);
			GET_SINGLE(CResourceManager)->PlaySFX("CompleteUpgrade");
		}
	}
}

void CArmory::Start()
{
	CScene* pScene = GET_SINGLE(CSceneManager)->GetCurrentScene();
	CPlayer* pPlayer = pScene->GetLayer("System")->FindGameObject("Player")->GetComponent<CPlayer>();

	{
		m_pVehicleWeapon = new CConsoleButton;

		m_pGameObject->AddButton(m_pVehicleWeapon);

		m_pVehicleWeapon->SetUpIconTexture(GET_SINGLE(CResourceManager)->FindTexture("ControlButton_Icon_TerranVehicleWeapon_Normal"));
		m_pVehicleWeapon->SetDownIconTexture(GET_SINGLE(CResourceManager)->FindTexture("ControlButton_Icon_TerranVehicleWeapon_Pressed"));

		m_pVehicleWeapon->SetRequireCursor(false);
		m_pVehicleWeapon->SetButtonName("Upgrade Vehicle Weapons");
		m_pVehicleWeapon->SetPanelIndex(0);
		m_pVehicleWeapon->SetExistNextPage(false);
		m_pVehicleWeapon->SetShortcutKey('W');
		m_pVehicleWeapon->SetButtonComponent(this);

		auto func = [&](CVector2 position, CGameObject* pTarget)
		{
			UpgradeVehicleWeapon();
		};

		m_pVehicleWeapon->SetFunction(func);


		//Next Page
		vector<CConsoleButton*> vecNextPage;
		vecNextPage.resize(9);

		for (int i = 0; i < 9; ++i)
		{
			vecNextPage[i] = NULL;
		}

		m_pVehicleWeapon->SetNextPage(vecNextPage);

	}

	{
		m_pVehicleArmor = new CConsoleButton;

		m_pGameObject->AddButton(m_pVehicleArmor);

		m_pVehicleArmor->SetUpIconTexture(GET_SINGLE(CResourceManager)->FindTexture("ControlButton_Icon_TerranVehicleArmor_Normal"));
		m_pVehicleArmor->SetDownIconTexture(GET_SINGLE(CResourceManager)->FindTexture("ControlButton_Icon_TerranVehicleArmor_Pressed"));

		m_pVehicleArmor->SetRequireCursor(false);
		m_pVehicleArmor->SetButtonName("Upgrade Vehicle Plating");
		m_pVehicleArmor->SetPanelIndex(3);
		m_pVehicleArmor->SetExistNextPage(false);
		m_pVehicleArmor->SetShortcutKey('P');
		m_pVehicleArmor->SetButtonComponent(this);

		auto func = [&](CVector2 position, CGameObject* pTarget)
		{
			UpgradeVehicleArmor();
		};

		m_pVehicleArmor->SetFunction(func);

		//Next Page
		vector<CConsoleButton*> vecNextPage;
		vecNextPage.resize(9);

		for (int i = 0; i < 9; ++i)
		{
			vecNextPage[i] = NULL;
		}
		m_pVehicleArmor->SetNextPage(vecNextPage);
	}

	{
		m_pShipWeapon = new CConsoleButton;

		m_pGameObject->AddButton(m_pShipWeapon);

		m_pShipWeapon->SetUpIconTexture(GET_SINGLE(CResourceManager)->FindTexture("ControlButton_Icon_TerranShipWeapon_Normal"));
		m_pShipWeapon->SetDownIconTexture(GET_SINGLE(CResourceManager)->FindTexture("ControlButton_Icon_TerranShipWeapon_Pressed"));

		m_pShipWeapon->SetRequireCursor(false);
		m_pShipWeapon->SetButtonName("Upgrade Ship Weapons");
		m_pShipWeapon->SetPanelIndex(1);
		m_pShipWeapon->SetExistNextPage(false);
		m_pShipWeapon->SetShortcutKey('S');
		m_pShipWeapon->SetButtonComponent(this);

		auto func = [&](CVector2 position, CGameObject* pTarget)
		{
			UpgradeShipWeapon();
		};

		m_pShipWeapon->SetFunction(func);


		//Next Page
		vector<CConsoleButton*> vecNextPage;
		vecNextPage.resize(9);

		for (int i = 0; i < 9; ++i)
		{
			vecNextPage[i] = NULL;
		}

		m_pShipWeapon->SetNextPage(vecNextPage);

	}

	{
		m_pShipArmor = new CConsoleButton;

		m_pGameObject->AddButton(m_pShipArmor);

		m_pShipArmor->SetUpIconTexture(GET_SINGLE(CResourceManager)->FindTexture("ControlButton_Icon_TerranShipArmor_Normal"));
		m_pShipArmor->SetDownIconTexture(GET_SINGLE(CResourceManager)->FindTexture("ControlButton_Icon_TerranShipArmor_Pressed"));

		m_pShipArmor->SetRequireCursor(false);
		m_pShipArmor->SetButtonName("Upgrade Ship Plating");
		m_pShipArmor->SetPanelIndex(4);
		m_pShipArmor->SetExistNextPage(false);
		m_pShipArmor->SetShortcutKey('P');
		m_pShipArmor->SetButtonComponent(this);

		auto func = [&](CVector2 position, CGameObject* pTarget)
		{
			UpgradeShipArmor();
		};

		m_pShipArmor->SetFunction(func);

		//Next Page
		vector<CConsoleButton*> vecNextPage;
		vecNextPage.resize(9);

		for (int i = 0; i < 9; ++i)
		{
			vecNextPage[i] = NULL;
		}
		m_pShipArmor->SetNextPage(vecNextPage);
	}
}

void CArmory::Update()
{
	CScene* pScene = GET_SINGLE(CSceneManager)->GetCurrentScene();
	CPlayer* pPlayer = pScene->GetLayer("System")->FindGameObject("Player")->GetComponent<CPlayer>();

	if (m_pVehicleWeapon)
	{
		if (pPlayer->GetUpgrade(UT_TERRAN_MECHANIC_GROUND_WAEPON) == 0)
		{
			if (pPlayer->GetMineral() < 100 || pPlayer->GetVespeneGas() < 100 || !pPlayer->FindOwnedStructure("Armory"))
			{
				m_pVehicleWeapon->SetButtonState(BS_DISABLE);
			}
			else
			{
				m_pVehicleWeapon->SetButtonState(BS_ENABLE);
			}
		}
		else if (pPlayer->GetUpgrade(UT_TERRAN_MECHANIC_GROUND_WAEPON) == 1)
		{
			if (pPlayer->GetMineral() < 175 || pPlayer->GetVespeneGas() < 175 || !pPlayer->FindOwnedStructure("Science Facility"))
			{
				m_pVehicleWeapon->SetButtonState(BS_DISABLE);
			}
			else
			{
				m_pVehicleWeapon->SetButtonState(BS_ENABLE);
			}
		}
		else if (pPlayer->GetUpgrade(UT_TERRAN_MECHANIC_GROUND_WAEPON) == 2)
		{
			if (pPlayer->GetMineral() < 250 || pPlayer->GetVespeneGas() < 250 || !pPlayer->FindOwnedStructure("Science Facility"))
			{
				m_pVehicleWeapon->SetButtonState(BS_DISABLE);
			}
			else
			{
				m_pVehicleWeapon->SetButtonState(BS_ENABLE);
			}
		}
		else if (pPlayer->GetUpgrade(UT_TERRAN_MECHANIC_GROUND_WAEPON) == 3)
		{
			m_pGameObject->RemoveButton(m_pVehicleWeapon);
			delete m_pVehicleWeapon;
			m_pVehicleWeapon = NULL;
		}

	}

	if (m_pVehicleArmor)
	{
		if (pPlayer->GetUpgrade(UT_TERRAN_MECHANIC_GROUND_DEFFENCE) == 0)
		{
			if (pPlayer->GetMineral() < 100 || pPlayer->GetVespeneGas() < 100 || !pPlayer->FindOwnedStructure("Engineering Bay"))
			{
				m_pVehicleArmor->SetButtonState(BS_DISABLE);
			}
			else
			{
				m_pVehicleArmor->SetButtonState(BS_ENABLE);
			}
		}
		else if (pPlayer->GetUpgrade(UT_TERRAN_MECHANIC_GROUND_DEFFENCE) == 1)
		{
			if (pPlayer->GetMineral() < 175 || pPlayer->GetVespeneGas() < 175 || !pPlayer->FindOwnedStructure("Science Facility"))
			{
				m_pVehicleArmor->SetButtonState(BS_DISABLE);
			}
			else
			{
				m_pVehicleArmor->SetButtonState(BS_ENABLE);
			}
		}
		else if (pPlayer->GetUpgrade(UT_TERRAN_MECHANIC_GROUND_DEFFENCE) == 2)
		{
			if (pPlayer->GetMineral() < 250 || pPlayer->GetVespeneGas() < 250 || !pPlayer->FindOwnedStructure("Science Facility"))
			{
				m_pVehicleArmor->SetButtonState(BS_DISABLE);
			}
			else
			{
				m_pVehicleArmor->SetButtonState(BS_ENABLE);
			}
		}
		else if (pPlayer->GetUpgrade(UT_TERRAN_MECHANIC_GROUND_DEFFENCE) == 3)
		{
			m_pGameObject->RemoveButton(m_pVehicleArmor);
			delete m_pVehicleArmor;
			m_pVehicleArmor = NULL;
		}


	}


	if (m_pShipWeapon)
	{
		if (pPlayer->GetUpgrade(UT_TERRAN_MECHANIC_AIR_WAEPON) == 0)
		{
			if (pPlayer->GetMineral() < 100 || pPlayer->GetVespeneGas() < 100 || !pPlayer->FindOwnedStructure("Armory"))
			{
				m_pShipWeapon->SetButtonState(BS_DISABLE);
			}
			else
			{
				m_pShipWeapon->SetButtonState(BS_ENABLE);
			}
		}
		else if (pPlayer->GetUpgrade(UT_TERRAN_MECHANIC_AIR_WAEPON) == 1)
		{
			if (pPlayer->GetMineral() < 150 || pPlayer->GetVespeneGas() < 150 || !pPlayer->FindOwnedStructure("Science Facility"))
			{
				m_pShipWeapon->SetButtonState(BS_DISABLE);
			}
			else
			{
				m_pShipWeapon->SetButtonState(BS_ENABLE);
			}
		}
		else if (pPlayer->GetUpgrade(UT_TERRAN_MECHANIC_AIR_WAEPON) == 2)
		{
			if (pPlayer->GetMineral() < 200 || pPlayer->GetVespeneGas() < 200 || !pPlayer->FindOwnedStructure("Science Facility"))
			{
				m_pShipWeapon->SetButtonState(BS_DISABLE);
			}
			else
			{
				m_pShipWeapon->SetButtonState(BS_ENABLE);
			}
		}
		else if (pPlayer->GetUpgrade(UT_TERRAN_MECHANIC_AIR_WAEPON) == 3)
		{
			m_pGameObject->RemoveButton(m_pShipWeapon);
			delete m_pShipWeapon;
			m_pShipWeapon = NULL;
		}

	}

	if (m_pShipArmor)
	{
		if (pPlayer->GetUpgrade(UT_TERRAN_MECHANIC_AIR_DEFFENCE) == 0)
		{
			if (pPlayer->GetMineral() < 150 || pPlayer->GetVespeneGas() < 150 || !pPlayer->FindOwnedStructure("Engineering Bay"))
			{
				m_pShipArmor->SetButtonState(BS_DISABLE);
			}
			else
			{
				m_pShipArmor->SetButtonState(BS_ENABLE);
			}
		}
		else if (pPlayer->GetUpgrade(UT_TERRAN_MECHANIC_AIR_DEFFENCE) == 1)
		{
			if (pPlayer->GetMineral() < 225 || pPlayer->GetVespeneGas() < 225 || !pPlayer->FindOwnedStructure("Science Facility"))
			{
				m_pShipArmor->SetButtonState(BS_DISABLE);
			}
			else
			{
				m_pShipArmor->SetButtonState(BS_ENABLE);
			}
		}
		else if (pPlayer->GetUpgrade(UT_TERRAN_MECHANIC_AIR_DEFFENCE) == 2)
		{
			if (pPlayer->GetMineral() < 300 || pPlayer->GetVespeneGas() < 300 || !pPlayer->FindOwnedStructure("Science Facility"))
			{
				m_pShipArmor->SetButtonState(BS_DISABLE);
			}
			else
			{
				m_pShipArmor->SetButtonState(BS_ENABLE);
			}
		}
		else if (pPlayer->GetUpgrade(UT_TERRAN_MECHANIC_AIR_DEFFENCE) == 3)
		{
			m_pGameObject->RemoveButton(m_pShipArmor);
			delete m_pShipArmor;
			m_pShipArmor = NULL;
		}
	}
}



CArmory::CArmory(const CArmory & component) :
	m_pVehicleArmor(NULL),
	m_pVehicleWeapon(NULL),
	m_pShipArmor(NULL),
	m_pShipWeapon(NULL)
{
	m_eComponentType = CT_ARMORY;
}

CArmory::CArmory():
	m_pVehicleArmor(NULL),
	m_pVehicleWeapon(NULL),
	m_pShipArmor(NULL),
	m_pShipWeapon(NULL)
{
	m_eComponentType = CT_ARMORY;
}


CArmory::~CArmory()
{
	if (m_pButton)
		delete m_pButton;

	if (m_pVehicleArmor)
		delete m_pVehicleArmor;
	if (m_pVehicleWeapon)
		delete m_pVehicleWeapon;
	if (m_pShipArmor)
		delete m_pShipArmor;
	if (m_pShipWeapon)
		delete m_pShipWeapon;
}


void CArmory::LoadComponent(FILE * pFile)
{
}

void CArmory::SaveComponent(FILE * pFile)
{
}

CComponent * CArmory::clone()
{
	return new CArmory(*this);
}

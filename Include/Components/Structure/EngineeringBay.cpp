#include "EngineeringBay.h"

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


void CEngineeringBay::UpgradeWeapon()
{
	CScene* pScene = GET_SINGLE(CSceneManager)->GetCurrentScene();
	CPlayer* pPlayer = pScene->GetLayer("System")->FindGameObject("Player")->GetComponent<CPlayer>();

	int iUpgradeValue = pPlayer->GetUpgrade(UT_TERRAN_BIONIC_WEAPON);
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
			pPlayer->SetUpgrade(UT_TERRAN_BIONIC_WEAPON, 1);
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
			pPlayer->SetUpgrade(UT_TERRAN_BIONIC_WEAPON, 2);
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
			pPlayer->SetUpgrade(UT_TERRAN_BIONIC_WEAPON, 3);
			GET_SINGLE(CResourceManager)->PlaySFX("CompleteUpgrade");
		}
	}

}

void CEngineeringBay::UpgradeArmor()
{
	CScene* pScene = GET_SINGLE(CSceneManager)->GetCurrentScene();
	CPlayer* pPlayer = pScene->GetLayer("System")->FindGameObject("Player")->GetComponent<CPlayer>();

	int iUpgradeValue = pPlayer->GetUpgrade(UT_TERRAN_BIONIC_DEFFENCE);
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
			pPlayer->SetUpgrade(UT_TERRAN_BIONIC_DEFFENCE, 1);
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
			pPlayer->SetUpgrade(UT_TERRAN_BIONIC_DEFFENCE, 2);
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
			pPlayer->SetUpgrade(UT_TERRAN_BIONIC_DEFFENCE, 3);
			GET_SINGLE(CResourceManager)->PlaySFX("CompleteUpgrade");
		}
	}

}

void CEngineeringBay::Start()
{
	CScene* pScene = GET_SINGLE(CSceneManager)->GetCurrentScene();
	CPlayer* pPlayer = pScene->GetLayer("System")->FindGameObject("Player")->GetComponent<CPlayer>();

	{
		m_pWeaponButton = new CConsoleButton;

		m_pGameObject->AddButton(m_pWeaponButton);

		m_pWeaponButton->SetUpIconTexture(GET_SINGLE(CResourceManager)->FindTexture("ControlButton_Icon_TerranInfantryWeapon_Normal"));
		m_pWeaponButton->SetDownIconTexture(GET_SINGLE(CResourceManager)->FindTexture("ControlButton_Icon_TerranInfantryWeapon_Pressed"));

		m_pWeaponButton->SetRequireCursor(false);
		m_pWeaponButton->SetButtonName("Upgrade Infantry Weapons");
		m_pWeaponButton->SetPanelIndex(0);
		m_pWeaponButton->SetExistNextPage(false);
		m_pWeaponButton->SetShortcutKey('W');
		m_pWeaponButton->SetButtonComponent(this);

		auto func = [&](CVector2 position, CGameObject* pTarget)
		{
			UpgradeWeapon();
		};

		m_pWeaponButton->SetFunction(func);


		//Next Page
		vector<CConsoleButton*> vecNextPage;
		vecNextPage.resize(9);

		for (int i = 0; i < 9; ++i)
		{
			vecNextPage[i] = NULL;
		}

		m_pWeaponButton->SetNextPage(vecNextPage);

	}

	{
		m_pArmorButton = new CConsoleButton;

		m_pGameObject->AddButton(m_pArmorButton);

		m_pArmorButton->SetUpIconTexture(GET_SINGLE(CResourceManager)->FindTexture("ControlButton_Icon_TerranInfantryArmor_Normal"));
		m_pArmorButton->SetDownIconTexture(GET_SINGLE(CResourceManager)->FindTexture("ControlButton_Icon_TerranInfantryArmor_Pressed"));

		m_pArmorButton->SetRequireCursor(false);
		m_pArmorButton->SetButtonName("Upgrade Infantry Armor");
		m_pArmorButton->SetPanelIndex(1);
		m_pArmorButton->SetExistNextPage(false);
		m_pArmorButton->SetShortcutKey('A');
		m_pArmorButton->SetButtonComponent(this);

		auto func = [&](CVector2 position, CGameObject* pTarget)
		{
			UpgradeArmor();
		};

		m_pArmorButton->SetFunction(func);

		//Next Page
		vector<CConsoleButton*> vecNextPage;
		vecNextPage.resize(9);

		for (int i = 0; i < 9; ++i)
		{
			vecNextPage[i] = NULL;
		}
		m_pArmorButton->SetNextPage(vecNextPage);
	}
}

void CEngineeringBay::Update()
{
	CScene* pScene = GET_SINGLE(CSceneManager)->GetCurrentScene();
	CPlayer* pPlayer = pScene->GetLayer("System")->FindGameObject("Player")->GetComponent<CPlayer>();

	if (m_pWeaponButton)
	{
		if (pPlayer->GetUpgrade(UT_TERRAN_BIONIC_WEAPON) == 0)
		{
			if (pPlayer->GetMineral() < 100 || pPlayer->GetVespeneGas() < 100 || !pPlayer->FindOwnedStructure("Engineering Bay"))
			{
				m_pWeaponButton->SetButtonState(BS_DISABLE);
			}
			else
			{
				m_pWeaponButton->SetButtonState(BS_ENABLE);
			}
		}
		else if (pPlayer->GetUpgrade(UT_TERRAN_BIONIC_WEAPON) == 1)
		{
			if (pPlayer->GetMineral() < 175 || pPlayer->GetVespeneGas() < 175 || !pPlayer->FindOwnedStructure("Science Facility"))
			{
				m_pWeaponButton->SetButtonState(BS_DISABLE);
			}
			else
			{
				m_pWeaponButton->SetButtonState(BS_ENABLE);
			}
		}
		else if (pPlayer->GetUpgrade(UT_TERRAN_BIONIC_WEAPON) == 2)
		{
			if (pPlayer->GetMineral() < 250 || pPlayer->GetVespeneGas() < 250 || !pPlayer->FindOwnedStructure("Science Facility"))
			{
				m_pWeaponButton->SetButtonState(BS_DISABLE);
			}
			else
			{
				m_pWeaponButton->SetButtonState(BS_ENABLE);
			}
		}
		else if (pPlayer->GetUpgrade(UT_TERRAN_BIONIC_WEAPON) == 3)
		{
			m_pGameObject->RemoveButton(m_pWeaponButton);
			delete m_pWeaponButton;
			m_pWeaponButton = NULL;
		}

	}

	if (m_pArmorButton)
	{
		if (pPlayer->GetUpgrade(UT_TERRAN_BIONIC_DEFFENCE) == 0)
		{
			if (pPlayer->GetMineral() < 100 || pPlayer->GetVespeneGas() < 100 || !pPlayer->FindOwnedStructure("Engineering Bay"))
			{
				m_pArmorButton->SetButtonState(BS_DISABLE);
			}
			else
			{
				m_pArmorButton->SetButtonState(BS_ENABLE);
			}
		}
		else if (pPlayer->GetUpgrade(UT_TERRAN_BIONIC_DEFFENCE) == 1)
		{
			if (pPlayer->GetMineral() < 175 || pPlayer->GetVespeneGas() < 175 || !pPlayer->FindOwnedStructure("Science Facility"))
			{
				m_pArmorButton->SetButtonState(BS_DISABLE);
			}
			else
			{
				m_pArmorButton->SetButtonState(BS_ENABLE);
			}
		}
		else if (pPlayer->GetUpgrade(UT_TERRAN_BIONIC_DEFFENCE) == 2)
		{
			if (pPlayer->GetMineral() < 250 || pPlayer->GetVespeneGas() < 250 || !pPlayer->FindOwnedStructure("Science Facility"))
			{
				m_pArmorButton->SetButtonState(BS_DISABLE);
			}
			else
			{
				m_pWeaponButton->SetButtonState(BS_ENABLE);
			}
		}
		else if (pPlayer->GetUpgrade(UT_TERRAN_BIONIC_DEFFENCE) == 3)
		{
			m_pGameObject->RemoveButton(m_pArmorButton);
			delete m_pArmorButton;
			m_pArmorButton = NULL;
		}


	}
}

void CEngineeringBay::SaveComponent(FILE * pFile)
{
}

void CEngineeringBay::LoadComponent(FILE * pFile)
{
}

CComponent * CEngineeringBay::clone()
{
	return new CEngineeringBay(*this);
}

CEngineeringBay::CEngineeringBay(const CEngineeringBay & component) :
	m_pWeaponButton(NULL),
	m_pArmorButton(NULL)
{
	m_eComponentType = CT_ENGINEERINGBAY;
}

CEngineeringBay::CEngineeringBay():
	m_pWeaponButton(NULL),
	m_pArmorButton(NULL)
{
	m_eComponentType = CT_ENGINEERINGBAY;
}


CEngineeringBay::~CEngineeringBay()
{
	if(m_pWeaponButton)
	delete m_pWeaponButton;

	if(m_pArmorButton)
	delete m_pArmorButton;
}

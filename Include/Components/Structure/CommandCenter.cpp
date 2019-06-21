#include "CommandCenter.h"
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



void CCommandCenter::RequestUnit(CGameObject * pTarget, CTexture * pIconTexture)
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
	else if (pPlayer->GetMaxPopulation() - pPlayer->GetCurrentPopulation() < pTarget->GetComponent<CUnitStatus>()->GetSupplyRequirement())
	{
		GET_SINGLE(CResourceManager)->PlaySFX("ErrorSupply");
	}
	else
	{
		pInfo->AddQueue(pTarget, pIconTexture);
	}
}

void CCommandCenter::Start()
{
	CScene* pScene = GET_SINGLE(CSceneManager)->GetCurrentScene();
	CPlayer* pPlayer = pScene->GetLayer("System")->FindGameObject("Player")->GetComponent<CPlayer>();
	CUnitInfo* pInfo = m_pGameObject->GetComponent<CUnitInfo>();

#pragma region SCV
	{
		m_pSCV = new CConsoleButton;

		m_pGameObject->AddButton(m_pSCV);

		m_pSCV->SetUpIconTexture(GET_SINGLE(CResourceManager)->FindTexture("ControlButton_Icon_TerranSCV_Normal"));
		m_pSCV->SetDownIconTexture(GET_SINGLE(CResourceManager)->FindTexture("ControlButton_Icon_TerranSCV_Pressed"));

		m_pSCV->SetRequireCursor(false);
		m_pSCV->SetButtonName("SCV");
		m_pSCV->SetPanelIndex(0);
		m_pSCV->SetExistNextPage(false);
		m_pSCV->SetShortcutKey('S');
		m_pSCV->SetButtonComponent(this);

		auto func = [&](CVector2 position, CGameObject* pTarget)
		{
			CGameObject* pCreateTarget = GET_SINGLE(CResourceManager)->FindUnit("SCV");
			RequestUnit(pCreateTarget, pCreateTarget->GetComponent<CUnitInfo>()->GetUnitButtonTexture());
		};

		m_pSCV->SetFunction(func);


		//Next Page
		vector<CConsoleButton*> vecNextPage;
		vecNextPage.resize(9);

		for (int i = 0; i < 9; ++i)
		{
			vecNextPage[i] = NULL;
		}

		m_pSCV->SetNextPage(vecNextPage);
	}

#pragma endregion
}

void CCommandCenter::Update()
{
	if (!m_pSCV)
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

	CUnitStatus* pStatus = GET_SINGLE(CResourceManager)->FindUnit("SCV")->GetComponent<CUnitStatus>();
	if (pPlayer->GetMineral() < 50 ||
		pPlayer->GetMaxPopulation() - pPlayer->GetCurrentPopulation() < 1)
	{
		m_pSCV->SetButtonState(BS_DISABLE);
	}
	else
	{
		m_pSCV->SetButtonState(BS_ENABLE);
	}
}

void CCommandCenter::LoadComponent(FILE * pFile)
{
}

void CCommandCenter::SaveComponent(FILE * pFile)
{
}

CComponent * CCommandCenter::clone()
{
	return new CCommandCenter(*this);
}

CCommandCenter::CCommandCenter(const CCommandCenter & component) :
	m_pSCV(NULL)
{
	m_eComponentType = CT_COMMANDCENTER;
}

CCommandCenter::CCommandCenter():
	m_pSCV(NULL)
{
	m_eComponentType = CT_COMMANDCENTER;
}


CCommandCenter::~CCommandCenter()
{
	if (m_pButton)
		delete m_pButton;

	if (m_pSCV)
		delete m_pSCV;
}

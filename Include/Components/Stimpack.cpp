#include "Stimpack.h"

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
#include "UnitStatus.h"
#include "../Timer.h"
#include "Attack.h"

CStimpack::CStimpack(const CStimpack & component):
	m_fTimer(0),
	m_bEnableStimpack(false)
{
	m_eComponentType = CT_STIMPACK;
}

CStimpack::CStimpack() :
	m_fTimer(0),
	m_bEnableStimpack(false)
{
	m_eComponentType = CT_STIMPACK;
}

CStimpack::~CStimpack()
{
	if (m_pButton)
		delete m_pButton;
}

void CStimpack::RequestFunction()
{
	float HP = m_pGameObject->GetComponent<CUnitStatus>()->GetCurrentHP();

	if (HP - 10 >= 1)
	{
		int iRandom = rand() % 2;
		char cRandom[4] = {};
		itoa(iRandom, cRandom, 10);

		GET_SINGLE(CResourceManager)->PlaySFX("Stimpack" + string(cRandom));
		m_pGameObject->GetComponent<CUnitStatus>()->AddHP(-10);
		m_bEnableStimpack = true;
		m_fTimer = 10;
	}
	else
	{
		GET_SINGLE(CResourceManager)->PlaySFX("Buzz");
	}
}

void CStimpack::Start()
{
	if (m_pGameObject->GetComponent<CAttack>())
	{
		m_fOriginInterval = m_pGameObject->GetComponent<CAttack>()->GetInterval();
	}
	if (m_pGameObject->GetComponent<CMove>())
	{
		m_fOriginMoveSpeed = m_pGameObject->GetComponent<CMove>()->GetMoveSpeed();
	}

	CScene* pScene = GET_SINGLE(CSceneManager)->GetCurrentScene();
	CPlayer* pPlayer = pScene->GetLayer("System")->FindGameObject("Player")->GetComponent<CPlayer>();
	m_pButton = new CConsoleButton;
	m_pGameObject->AddButton(m_pButton);

	m_pButton->SetUpIconTexture(GET_SINGLE(CResourceManager)->FindTexture("ControlButton_Icon_TerranStimpack_Normal"));
	m_pButton->SetDownIconTexture(GET_SINGLE(CResourceManager)->FindTexture("ControlButton_Icon_TerranStimpack_Pressed"));

	m_pButton->SetRequireCursor(false);
	m_pButton->SetButtonName("Stimpack");
	m_pButton->SetPanelIndex(6);
	m_pButton->SetExistNextPage(false);
	m_pButton->SetShortcutKey('T');
	m_pButton->SetButtonComponent(this);

	auto func = [&](CVector2 position, CGameObject* pTarget)
	{
		RequestFunction();
	};
	m_pButton->SetFunction(func);


	//Next Page
	vector<CConsoleButton*> vecNextPage;
	vecNextPage.resize(9);

	for (int i = 0; i < 9; ++i)
	{
		vecNextPage[i] = NULL;
	}
}

void CStimpack::Update()
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
	if (pPlayer->GetUpgrade(UT_TERRAN_STIMPACK))
	{
		m_pButton->SetButtonState(BS_ENABLE);
	}
	else
	{
		m_pButton->SetButtonState(BS_DISABLE);
	}

	if (m_bEnableStimpack)
	{
		m_fTimer -= GET_SINGLE(CTimer)->GetDeltaTime();
		if (m_fTimer <= 0)
		{
			m_pGameObject->GetComponent<CAttack>()->SetInterval(m_fOriginInterval);
			m_pGameObject->GetComponent<CMove>()->SetMoveSpeed(m_fOriginMoveSpeed);
			m_bEnableStimpack = false;
			m_fTimer = 0;
		}
		else
		{
			m_pGameObject->GetComponent<CAttack>()->SetInterval(m_fOriginInterval * 0.75f);
			m_pGameObject->GetComponent<CMove>()->SetMoveSpeed(m_fOriginMoveSpeed * 1.25f);
		}
	}
}

void CStimpack::LateUpdate()
{
}

void CStimpack::LoadComponent(FILE * pFile)
{
}

void CStimpack::SaveComponent(FILE * pFile)
{
}

CComponent * CStimpack::clone()
{
	return new CStimpack(*this);
}

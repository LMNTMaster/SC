#include "Stop.h"
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
#include "Gather.h"
#include "Move.h"
#include "Attack.h"
#include "Build.h"
#include "Repair.h"

void CStop::RequestStop()
{
	if(m_pGameObject->GetComponent<CGather>())
		m_pGameObject->GetComponent<CGather>()->Stop();

	if (m_pGameObject->GetComponent<CMove>())
		m_pGameObject->GetComponent<CMove>()->Stop();

	if (m_pGameObject->GetComponent<CAttack>())
		m_pGameObject->GetComponent<CAttack>()->Stop();

	//if (m_pGameObject->GetComponent<CBuild>())
	//	m_pGameObject->GetComponent<CBuild>()->Stop();
	//
	//if (m_pGameObject->GetComponent<CRepair>())
	//	m_pGameObject->GetComponent<CRepair>()->Stop();
}

void CStop::Start()
{
	CScene* pScene = GET_SINGLE(CSceneManager)->GetCurrentScene();
	CPlayer* pPlayer = pScene->GetLayer("System")->FindGameObject("Player")->GetComponent<CPlayer>();
	m_pButton = new CConsoleButton;
	m_pGameObject->AddButton(m_pButton);

	m_pButton->SetUpIconTexture(GET_SINGLE(CResourceManager)->FindTexture("ControlButton_Icon_Stop_Normal"));
	m_pButton->SetDownIconTexture(GET_SINGLE(CResourceManager)->FindTexture("ControlButton_Icon_Stop_Pressed"));

	m_pButton->SetRequireCursor(false);
	m_pButton->SetButtonName("Stop");
	m_pButton->SetPanelIndex(1);
	m_pButton->SetExistNextPage(false);
	m_pButton->SetShortcutKey('S');
	m_pButton->SetButtonComponent(this);

	auto func = [&](CVector2 position, CGameObject* pTarget)
	{
		RequestStop();
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

void CStop::Update()
{
}

void CStop::SaveComponent(FILE * pFile)
{
	//DO NOTHING
}

void CStop::LoadComponent(FILE * pFile)
{
	//DO NOTHING
}

CComponent * CStop::clone()
{
	return new CStop(*this);
}

CStop::CStop(const CStop & component)
{
	m_eComponentParentType = PT_NONE;
	m_eComponentType = CT_STOP;
}

CStop::CStop()
{
	m_eComponentParentType = PT_NONE;
	m_eComponentType = CT_STOP;
}


CStop::~CStop()
{
	if (m_pButton)
		delete m_pButton;
}

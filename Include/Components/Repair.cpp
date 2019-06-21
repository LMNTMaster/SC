#include "Repair.h"
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


void CRepair::Start()
{
	CScene* pScene = GET_SINGLE(CSceneManager)->GetCurrentScene();
	CPlayer* pPlayer = pScene->GetLayer("System")->FindGameObject("Player")->GetComponent<CPlayer>();
	m_pButton = new CConsoleButton;
	m_pGameObject->AddButton(m_pButton);

	m_pButton->SetUpIconTexture(GET_SINGLE(CResourceManager)->FindTexture("ControlButton_Icon_Repair_Normal"));
	m_pButton->SetDownIconTexture(GET_SINGLE(CResourceManager)->FindTexture("ControlButton_Icon_Repair_Pressed"));

	m_pButton->SetRequireCursor(true);
	m_pButton->SetButtonName("Repair");
	m_pButton->SetPanelIndex(3);
	m_pButton->SetExistNextPage(true);
	m_pButton->SetShortcutKey('R');
	m_pButton->SetButtonComponent(this);

	auto func = [&](CVector2 position, CGameObject* pTarget)
	{

	};
	m_pButton->SetFunction(func);


	//Next Page
	vector<CConsoleButton*> vecNextPage;
	vecNextPage.resize(9);

	for (int i = 0; i < 9; ++i)
	{
		vecNextPage[i] = NULL;
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

void CRepair::Update()
{
}

void CRepair::SaveComponent(FILE * pFile)
{
	fwrite(&m_fRestoreAmount, 4, 1, pFile);
}

void CRepair::LoadComponent(FILE * pFile)
{
	fread(&m_fRestoreAmount, 4, 1, pFile);
}

CComponent * CRepair::clone()
{
	return new CRepair(*this);
}

CRepair::CRepair(const CRepair & component)
{
	m_fRestoreAmount = component.m_fRestoreAmount;
	m_eComponentParentType = PT_NONE;
	m_eComponentType = CT_REPAIR;
}

CRepair::CRepair()
{
	m_eComponentParentType = PT_NONE;
	m_eComponentType = CT_REPAIR;
}


CRepair::~CRepair()
{
	if (m_pButton)
		delete m_pButton;
}

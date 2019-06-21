#include "Hold.h"
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


void CHold::Start()
{
	CScene* pScene = GET_SINGLE(CSceneManager)->GetCurrentScene();
	CPlayer* pPlayer = pScene->GetLayer("System")->FindGameObject("Player")->GetComponent<CPlayer>();
	m_pButton = new CConsoleButton;
	m_pGameObject->AddButton(m_pButton);

	m_pButton->SetUpIconTexture(GET_SINGLE(CResourceManager)->FindTexture("ControlButton_Icon_Hold_Normal"));
	m_pButton->SetDownIconTexture(GET_SINGLE(CResourceManager)->FindTexture("ControlButton_Icon_Hold_Pressed"));

	m_pButton->SetRequireCursor(false);
	m_pButton->SetButtonName("Hold");
	m_pButton->SetPanelIndex(5);
	m_pButton->SetExistNextPage(false);
	m_pButton->SetShortcutKey('H');
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
}

void CHold::Update()
{
}

void CHold::SaveComponent(FILE * pFile)
{
	//DO NOTHING
}

void CHold::LoadComponent(FILE * pFile)
{
	//DO NOTHING
}

CComponent * CHold::clone()
{
	return new CHold(*this);
}

CHold::CHold(const CHold & component)
{
	m_eComponentParentType = PT_NONE;
	m_eComponentType = CT_HOLD;
}

CHold::CHold()
{
	m_eComponentParentType = PT_NONE;
	m_eComponentType = CT_HOLD;
}


CHold::~CHold()
{
	if (m_pButton)
		delete m_pButton;
}

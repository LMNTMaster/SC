#include "EditorButton.h"
#include "SpriteRenderer.h"
#include "../Scenes/MapEditorScene.h"
#include "../SceneManager.h"
#include "../ResourceManager.h"
#include "../Input.h"

void CEditorButton::Update()
{
	if (GETKEYDOWN('E'))
	{
		GET_SINGLE(CSceneManager)->SetNextScene(new CMapEditorScene);
	}
}

void CEditorButton::CollisionEnter()
{
	GET_SINGLE(CResourceManager)->PlaySFX("ButtonOver");
	m_pTargetRenderer->SetEnable(true);
}

void CEditorButton::CollisionStay()
{
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		GET_SINGLE(CResourceManager)->PlaySFX("ButtonClick");
		GET_SINGLE(CSceneManager)->SetNextScene(new CMapEditorScene);
	}
}

void CEditorButton::CollisionExit()
{
	m_pTargetRenderer->SetEnable(false);
}


void CEditorButton::SaveComponent(FILE * pFile)
{
}

void CEditorButton::LoadComponent(FILE * pFile)
{
}

CComponent * CEditorButton::clone()
{
	return nullptr;
}

CEditorButton::CEditorButton(const CEditorButton & component)
{
}

CEditorButton::CEditorButton():
	m_pTargetRenderer(NULL)
{
}


CEditorButton::~CEditorButton()
{
}

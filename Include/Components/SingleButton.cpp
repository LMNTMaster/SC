#include "SingleButton.h"
#include "SpriteRenderer.h"
#include "../Input.h"
#include "../SceneManager.h"
#include "../Scenes/GameScene.h"
#include "../ResourceManager.h"
#include "../Scenes/MainGameScene.h"


CSingleButton::CSingleButton(const CSingleButton & component)
{
}

CSingleButton::CSingleButton()
{
}


CSingleButton::~CSingleButton()
{
}

void CSingleButton::Update()
{
	if (GETKEYDOWN('S'))
	{
		GET_SINGLE(CResourceManager)->StopSFX(ST_BGM);
		GET_SINGLE(CSceneManager)->SetNextScene(new CGameScene);
	}
}

void CSingleButton::CollisionEnter()
{
	m_pTargetRenderer->SetEnable(true);
	GET_SINGLE(CResourceManager)->PlaySFX("ButtonOver");
}

void CSingleButton::CollisionStay()
{
	if(GETKEY(VK_LBUTTON))
	{
		GET_SINGLE(CResourceManager)->PlaySFX("ButtonClick");
		GET_SINGLE(CResourceManager)->StopSFX(ST_BGM);
		//GET_SINGLE(CSceneManager)->SetNextScene(new CGameScene); 
		GET_SINGLE(CSceneManager)->SetNextScene(new CGameScene);
	}
}

void CSingleButton::CollisionExit()
{
	m_pTargetRenderer->SetEnable(false);
}

void CSingleButton::SaveComponent(FILE * pFile)
{
}

void CSingleButton::LoadComponent(FILE * pFile)
{
}

CComponent * CSingleButton::clone()
{
	return nullptr;
}

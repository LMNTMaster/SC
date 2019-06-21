#include "ExitButton.h"
#include "SpriteRenderer.h"
#include "../Core.h"
#include "../ResourceManager.h"
#include "../Input.h"

CExitButton::CExitButton(const CExitButton & component)
{
}

CExitButton::CExitButton()
{
}


CExitButton::~CExitButton()
{
}

void CExitButton::Update()
{
	if (GETKEYDOWN('X'))
	{
		GET_SINGLE(CCore)->ExitGame();
	}
}

void CExitButton::CollisionEnter()
{
	m_pTargetRenderer->SetEnable(true);
	GET_SINGLE(CResourceManager)->PlaySFX("ButtonOver");
}

void CExitButton::CollisionStay()
{
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		GET_SINGLE(CResourceManager)->PlaySFX("ButtonClick");
		GET_SINGLE(CCore)->ExitGame();
	}
}

void CExitButton::CollisionExit()
{

	m_pTargetRenderer->SetEnable(false);
}

void CExitButton::SaveComponent(FILE * pFile)
{
}

void CExitButton::LoadComponent(FILE * pFile)
{
}

CComponent * CExitButton::clone()
{
	return nullptr;
}

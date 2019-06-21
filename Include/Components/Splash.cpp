#include "Splash.h"
#include "../GameObject.h"
#include "../Component.h"
#include "../Core.h"
#include "TextRenderer.h"
#include "../SceneManager.h"
#include "../Scenes/MainMenuScene.h"
#include "../Scene.h"


void CSplash::Update()
{
	float progress = GET_SINGLE(CCore)->GetLoadingProgress();

	CTextRenderer* pRenderer = m_pGameObject->GetComponent<CTextRenderer>();
		
	int iProgress = progress * 100.0f;
	
	wstring text(L"Loading..  ");
	text +=  to_wstring(iProgress);
	text += L" % ";

	pRenderer->SetText(text);


	if (progress == 1.0f)
	{	
		GET_SINGLE(CCore)->GetLoadingThread()->join();
		GET_SINGLE(CSceneManager)->SetNextScene(new CMainMenuScene);		
	}
}

void CSplash::SaveComponent(FILE * pFile)
{
}

void CSplash::LoadComponent(FILE * pFile)
{
}

CComponent * CSplash::clone()
{
	return new CSplash(*this);
}

CSplash::CSplash(const CSplash & component)
{

}

CSplash::CSplash()
{
}


CSplash::~CSplash()
{
}

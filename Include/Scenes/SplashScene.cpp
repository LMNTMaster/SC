#include "SplashScene.h"
#include "../ResourceManager.h"
#include "../GameObject.h"
#include "../Component.h"
#include "../Layer.h"
#include "../Core.h"
#include "../Components/Transform.h"
#include "../Components/TextRenderer.h"
#include "../Components/Splash.h"


CSplashScene::CSplashScene()
{
	CLayer* pLayer = FindLayer("Default");
	
	CGameObject* pSplashTitle = new CGameObject("Title");
	pSplashTitle->GetComponent<CTransform>()->SetPosition(0, 0);
	pSplashTitle->GetComponent<CTransform>()->SetPivot(0, 0);
	CTextureRenderer* pRenderer = pSplashTitle->AddComponent<CTextureRenderer>();
	pRenderer->SetTexture("SplashTexture", L"title.bmp", UI_TEXTURE_PATH);
	pRenderer->SetSize(GET_SINGLE(CCore)->GetScreenSize());
	pRenderer->SetColorKey(255,0,255);
	
	CTextRenderer* pTextRenderer = pSplashTitle->AddComponent<CTextRenderer>();
	pTextRenderer->SetColor(255, 255, 255);
	pTextRenderer->SetPosition(GET_SINGLE(CCore)->GetScreenSize().x / 2, GET_SINGLE(CCore)->GetScreenSize().y * 0.9f);

	CSplash* pSplash = pSplashTitle->AddComponent<CSplash>();

	pLayer->AddGameObject(pSplashTitle);
	//GET_SINGLE(CResourceManager)->LoadTexture("SplashTexture", L"title.bmp", UI_TEXTURE_PATH);

	GET_SINGLE(CResourceManager)->LoadSound("Title", true, "title.wav", BGM_PATH);
	GET_SINGLE(CResourceManager)->PlaySFX("Title");
	GET_SINGLE(CResourceManager)->SetVolume(ST_BGM, 0.25f);
	GET_SINGLE(CResourceManager)->SetVolume(ST_SFX, 1);

}


CSplashScene::~CSplashScene()
{
}

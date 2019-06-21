#include "MainMenuScene.h"
#include "../Sprite.h"
#include "../ResourceManager.h"
#include "../Texture.h"
#include "../Components/SpriteRenderer.h"
#include "../Layer.h"
#include "../GameObject.h"
#include "../Component.h"
#include "../FileStream.h"
#include "../Components/CursorMove.h"
#include "../Components/TextureRenderer.h"
#include "../Core.h"
#include "../Components/Transform.h"
#include "../Components/EditorButton.h"
#include "../Components/ExitButton.h"
#include "../Components/ButtonCollider.h"
#include "../Components/TextRenderer.h"
#include "../Components/SingleButton.h"

CMainMenuScene::CMainMenuScene()
{

	SetName("DefaultScene");

	CLayer* pLayer = GetLayer("Default");

	CLayer* pBottomLayer = CreateLayer("Bottom", INT_MAX - 10);
	pBottomLayer->SetScene(this);
	this->AddLayer(pBottomLayer);
	CLayer* pTopLayer = CreateLayer("Top", INT_MAX);
	pTopLayer->SetScene(this);
	this->AddLayer(pTopLayer);

	
	CGameObject* pBackground = new CGameObject("Background");
	CTextureRenderer* pBackgroundRenderer = pBackground->AddComponent<CTextureRenderer>();
	pBackgroundRenderer->SetTexture("MainMenuBackground");
	pBackgroundRenderer->SetSize(GET_SINGLE(CCore)->GetScreenSize());
	pBackground->GetTransform()->SetPivot(0, 0);
	pLayer->AddGameObject(pBackground);

#pragma region EditorButton

	CGameObject* pEditorButton = new CGameObject("EditorButton");
	pBottomLayer->AddGameObject(pEditorButton);

	CButtonCollider* pCollider = pEditorButton->AddComponent<CButtonCollider>();
	pCollider->SetSize(300, 250);
	pCollider->SetLocalPosition(0, 0);

	CSpriteRenderer* pEditorSprite = pEditorButton->AddComponent<CSpriteRenderer>();
	pEditorButton->GetTransform()->SetPivot(0, 0);
	pEditorSprite->SetSize(160, 140);

	CSprite* pSprite = new CSprite;

	pSprite->AddFrame(CVector2(0, 0));
	pSprite->AddFrame(CVector2(1, 0));
	pSprite->AddFrame(CVector2(2, 0));
	pSprite->AddFrame(CVector2(3, 0));
	pSprite->AddFrame(CVector2(4, 0));
	pSprite->AddFrame(CVector2(5, 0));
	pSprite->AddFrame(CVector2(6, 0));
	pSprite->AddFrame(CVector2(7, 0));
	pSprite->AddFrame(CVector2(8, 0));
	pSprite->AddFrame(CVector2(9, 0));

	pSprite->AddFrame(CVector2(0, 1));
	pSprite->AddFrame(CVector2(1, 1));
	pSprite->AddFrame(CVector2(2, 1));
	pSprite->AddFrame(CVector2(3, 1));
	pSprite->AddFrame(CVector2(4, 1));
	pSprite->AddFrame(CVector2(5, 1));
	pSprite->AddFrame(CVector2(6, 1));
	pSprite->AddFrame(CVector2(7, 1));
	pSprite->AddFrame(CVector2(8, 1));
	pSprite->AddFrame(CVector2(9, 1));

	pSprite->AddFrame(CVector2(0, 2));
	pSprite->AddFrame(CVector2(1, 2));
	pSprite->AddFrame(CVector2(2, 2));
	pSprite->AddFrame(CVector2(3, 2));
	pSprite->AddFrame(CVector2(4, 2));
	pSprite->AddFrame(CVector2(5, 2));
	pSprite->AddFrame(CVector2(6, 2));
	pSprite->AddFrame(CVector2(7, 2));
	pSprite->AddFrame(CVector2(8, 2));
	pSprite->AddFrame(CVector2(9, 2));

	pSprite->AddFrame(CVector2(0, 3));
	pSprite->AddFrame(CVector2(1, 3));
	pSprite->AddFrame(CVector2(2, 3));
	pSprite->AddFrame(CVector2(3, 3));
	pSprite->AddFrame(CVector2(4, 3));
	pSprite->AddFrame(CVector2(5, 3));
	pSprite->AddFrame(CVector2(6, 3));
	pSprite->AddFrame(CVector2(7, 3));
	pSprite->AddFrame(CVector2(8, 3));
	pSprite->AddFrame(CVector2(9, 3));

	pSprite->AddFrame(CVector2(0, 4));
	pSprite->AddFrame(CVector2(1, 4));
	pSprite->AddFrame(CVector2(2, 4));
	pSprite->AddFrame(CVector2(3, 4));
	pSprite->AddFrame(CVector2(4, 4));
	pSprite->AddFrame(CVector2(5, 4));
	pSprite->AddFrame(CVector2(6, 4));
	pSprite->AddFrame(CVector2(7, 4));
	pSprite->AddFrame(CVector2(8, 4));
	pSprite->AddFrame(CVector2(9, 4));


	pSprite->AddFrame(CVector2(0, 5));
	pSprite->AddFrame(CVector2(1, 5));
	pSprite->AddFrame(CVector2(2, 5));
	pSprite->AddFrame(CVector2(3, 5));
	pSprite->AddFrame(CVector2(4, 5));
	pSprite->AddFrame(CVector2(5, 5));
	pSprite->AddFrame(CVector2(6, 5));
	pSprite->AddFrame(CVector2(7, 5));


	pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("Main_EditorBase_Atlas"));
	pSprite->SetCellSize(160, 140);
	pSprite->SetAtlasGridSize(10, 10);
	pSprite->SetSampleRate(8);
	pSprite->SetLoop(true);

	pSprite->SaveSprite("Main_EditorButtonBase.aclp");
	pEditorSprite->AddSprite("Main_EditorBase", pSprite);
	pEditorSprite->ChangeCurrentClip("Main_EditorBase");
	delete pSprite;

	pEditorButton->GetTransform()->SetPosition(900, 100);
	pEditorButton->GetTransform()->SetScale(CVector2(1.5f, 1.5f));
	pEditorButton->GetTransform()->SetPivot(0, 0);
	pEditorSprite->SetSize(160, 140);


	CGameObject* pEditOver = new CGameObject("EditOver");
	CSpriteRenderer* pOverRenderer = pEditOver->AddComponent<CSpriteRenderer>();
	pEditOver->GetTransform()->SetPosition(930, 125);
	pEditOver->GetTransform()->SetPivot(0, 0);

	pOverRenderer->SetSize(204, 132);
	pSprite = new CSprite;
	pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("Main_EditorOver_Atlas"));
	pSprite->AddFrame(CVector2(0, 0));
	pSprite->AddFrame(CVector2(1, 0));
	pSprite->AddFrame(CVector2(2, 0));
	pSprite->AddFrame(CVector2(3, 0));
	pSprite->AddFrame(CVector2(4, 0));
	pSprite->AddFrame(CVector2(5, 0));
	pSprite->AddFrame(CVector2(6, 0));
	pSprite->AddFrame(CVector2(7, 0));
	pSprite->AddFrame(CVector2(8, 0));
	pSprite->AddFrame(CVector2(9, 0));
	pSprite->AddFrame(CVector2(0, 1));
	pSprite->AddFrame(CVector2(1, 1));
	pSprite->AddFrame(CVector2(2, 1));
	pSprite->AddFrame(CVector2(3, 1));

	pSprite->SetCellSize(204, 132);
	pSprite->SetAtlasGridSize(10, 2);
	pSprite->SetSampleRate(8);
	pSprite->SetLoop(true);

	pSprite->SaveSprite("Main_EditorButtonOver.aclp");
	pOverRenderer->AddSprite("Main_EditorOver", pSprite);
	pOverRenderer->ChangeCurrentClip("Main_EditorOver");
	delete pSprite;

	pBottomLayer->AddGameObject(pEditOver);
	pEditOver->GetTransform()->SetScale(CVector2(1.5f, 1.5f));

	pOverRenderer->SetEnable(false);


	CEditorButton* pEdit = pEditorButton->AddComponent<CEditorButton>();
	pEdit->SetTarget(pOverRenderer);

	CTextRenderer* pTextRenderer = pEditorButton->AddComponent<CTextRenderer>();
	pTextRenderer->SetText(L"에디터 (E)");
	pTextRenderer->SetColor(31, 225, 31);
	pTextRenderer->SetPosition(1000, 330);

#pragma endregion

#pragma region ExitButton

	CGameObject* pExitButton = new CGameObject("ExitButton");
	pBottomLayer->AddGameObject(pExitButton);


	pCollider = pExitButton->AddComponent<CButtonCollider>();
	pCollider->SetSize(400, 300);
	pCollider->SetLocalPosition(0, 0);

	CSpriteRenderer* pExitSprite = pExitButton->AddComponent<CSpriteRenderer>();
	pExitButton->GetTransform()->SetPivot(0, 0);
	pExitSprite->SetSize(160, 140);

	pSprite = new CSprite;

	pSprite->AddFrame(CVector2(0, 0));
	pSprite->AddFrame(CVector2(1, 0));
	pSprite->AddFrame(CVector2(2, 0));
	pSprite->AddFrame(CVector2(3, 0));
	pSprite->AddFrame(CVector2(4, 0));
	pSprite->AddFrame(CVector2(5, 0));
	pSprite->AddFrame(CVector2(6, 0));
	pSprite->AddFrame(CVector2(7, 0));
	pSprite->AddFrame(CVector2(8, 0));
	pSprite->AddFrame(CVector2(9, 0));

	pSprite->AddFrame(CVector2(0, 1));
	pSprite->AddFrame(CVector2(1, 1));
	pSprite->AddFrame(CVector2(2, 1));
	pSprite->AddFrame(CVector2(3, 1));
	pSprite->AddFrame(CVector2(4, 1));
	pSprite->AddFrame(CVector2(5, 1));
	pSprite->AddFrame(CVector2(6, 1));
	pSprite->AddFrame(CVector2(7, 1));
	pSprite->AddFrame(CVector2(8, 1));
	pSprite->AddFrame(CVector2(9, 1));

	pSprite->AddFrame(CVector2(0, 2));
	pSprite->AddFrame(CVector2(1, 2));
	pSprite->AddFrame(CVector2(2, 2));
	pSprite->AddFrame(CVector2(3, 2));
	pSprite->AddFrame(CVector2(4, 2));
	pSprite->AddFrame(CVector2(5, 2));
	pSprite->AddFrame(CVector2(6, 2));
	pSprite->AddFrame(CVector2(7, 2));
	pSprite->AddFrame(CVector2(8, 2));
	pSprite->AddFrame(CVector2(9, 2));

	pSprite->AddFrame(CVector2(0, 3));
	pSprite->AddFrame(CVector2(1, 3));
	pSprite->AddFrame(CVector2(2, 3));
	pSprite->AddFrame(CVector2(3, 3));
	pSprite->AddFrame(CVector2(4, 3));


	pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("Main_ExitBase_Atlas"));
	pSprite->SetCellSize(184, 128);
	pSprite->SetAtlasGridSize(10, 4);
	pSprite->SetSampleRate(15);
	pSprite->SetLoop(true);

	pSprite->SaveSprite("Main_ExitButtonBase.aclp");
	pExitSprite->AddSprite("Main_ExitBase", pSprite);
	pExitSprite->ChangeCurrentClip("Main_ExitBase");
	delete pSprite;

	pExitButton->GetTransform()->SetPosition(800, 450);
	pExitButton->GetTransform()->SetScale(CVector2(2.0f, 2.0f));
	pExitButton->GetTransform()->SetPivot(0, 0);
	pExitSprite->SetSize(184, 128);


	CGameObject* pExitOver = new CGameObject("ExitOver");
	pOverRenderer = pExitOver->AddComponent<CSpriteRenderer>();
	pExitOver->GetTransform()->SetPosition(830, 450);
	pExitOver->GetTransform()->SetPivot(0, 0);

	pOverRenderer->SetSize(216, 136);
	pSprite = new CSprite;
	pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("Main_ExitOver_Atlas"));
	
	pSprite->AddFrame(CVector2(0, 0));
	pSprite->AddFrame(CVector2(1, 0));
	pSprite->AddFrame(CVector2(2, 0));
	pSprite->AddFrame(CVector2(3, 0));
	pSprite->AddFrame(CVector2(4, 0));
	pSprite->AddFrame(CVector2(5, 0));
	pSprite->AddFrame(CVector2(6, 0));
	pSprite->AddFrame(CVector2(7, 0));
	pSprite->AddFrame(CVector2(8, 0));
	pSprite->AddFrame(CVector2(9, 0));

	pSprite->AddFrame(CVector2(0, 1));
	pSprite->AddFrame(CVector2(1, 1));
	pSprite->AddFrame(CVector2(2, 1));
	pSprite->AddFrame(CVector2(3, 1));
	pSprite->AddFrame(CVector2(4, 1));
	pSprite->AddFrame(CVector2(5, 1));
	pSprite->AddFrame(CVector2(6, 1));
	pSprite->AddFrame(CVector2(7, 1));
	pSprite->AddFrame(CVector2(8, 1));
	pSprite->AddFrame(CVector2(9, 1));

	pSprite->AddFrame(CVector2(0, 2));
	pSprite->AddFrame(CVector2(1, 2));
	

	pSprite->SetCellSize(216, 136);
	pSprite->SetAtlasGridSize(10, 3);
	pSprite->SetSampleRate(15);
	pSprite->SetLoop(true);

	pSprite->SaveSprite("Main_ExitButtonOver.aclp");
	pOverRenderer->AddSprite("Main_ExitOver", pSprite);
	pOverRenderer->ChangeCurrentClip("Main_ExitOver");
	delete pSprite;

	pBottomLayer->AddGameObject(pExitOver);
	pExitOver->GetTransform()->SetScale(CVector2(2.0f, 2.0f));

	pOverRenderer->SetEnable(false);


	CExitButton* pExit = pExitButton->AddComponent<CExitButton>();
	pExit->SetTarget(pOverRenderer);



	pTextRenderer = pExitButton->AddComponent<CTextRenderer>();
	pTextRenderer->SetPosition(1020, 460);
	pTextRenderer->SetColor(31, 225, 31);
	pTextRenderer->SetText(L"나가기 (X)");

#pragma endregion

#pragma region SingleButton

	CGameObject* pButtonOver = new CGameObject("SingleOver");
	pOverRenderer = pButtonOver->AddComponent<CSpriteRenderer>();
	pButtonOver->GetTransform()->SetPosition(100, 125);
	pButtonOver->GetTransform()->SetPivot(0, 0);

	pOverRenderer->SetSize(252, 124);
	pSprite = new CSprite;
	pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("Main_SingleOver_Atlas"));
	pSprite->AddFrame(CVector2(0, 0));
	pSprite->AddFrame(CVector2(1, 0));
	pSprite->AddFrame(CVector2(2, 0));
	pSprite->AddFrame(CVector2(3, 0));
	pSprite->AddFrame(CVector2(4, 0));
	pSprite->AddFrame(CVector2(5, 0));
	pSprite->AddFrame(CVector2(6, 0));
	pSprite->AddFrame(CVector2(7, 0));
	pSprite->AddFrame(CVector2(8, 0));
	pSprite->AddFrame(CVector2(9, 0));

	pSprite->AddFrame(CVector2(0, 1));
	pSprite->AddFrame(CVector2(1, 1));
	pSprite->AddFrame(CVector2(2, 1));
	pSprite->AddFrame(CVector2(3, 1));
	pSprite->AddFrame(CVector2(4, 1));
	pSprite->AddFrame(CVector2(5, 1));
	pSprite->AddFrame(CVector2(6, 1));
	pSprite->AddFrame(CVector2(7, 1));
	pSprite->AddFrame(CVector2(8, 1));
	pSprite->AddFrame(CVector2(9, 1));

	pSprite->AddFrame(CVector2(0, 2));
	pSprite->AddFrame(CVector2(1, 2));
	pSprite->AddFrame(CVector2(2, 2));
	pSprite->AddFrame(CVector2(3, 2));
	pSprite->AddFrame(CVector2(4, 2));
	pSprite->AddFrame(CVector2(5, 2));
	pSprite->AddFrame(CVector2(6, 2));
	pSprite->AddFrame(CVector2(7, 2));
	pSprite->AddFrame(CVector2(8, 2));
	pSprite->AddFrame(CVector2(9, 2));

	pSprite->AddFrame(CVector2(0, 3));
	pSprite->AddFrame(CVector2(1, 3));
	pSprite->AddFrame(CVector2(2, 3));
	pSprite->AddFrame(CVector2(3, 3));
	pSprite->AddFrame(CVector2(4, 3));
	pSprite->AddFrame(CVector2(5, 3));
	pSprite->AddFrame(CVector2(6, 3));
	pSprite->AddFrame(CVector2(7, 3));
	pSprite->AddFrame(CVector2(8, 3));
	pSprite->AddFrame(CVector2(9, 3));

	pSprite->AddFrame(CVector2(0, 4));
	pSprite->AddFrame(CVector2(1, 4));

	pSprite->SetCellSize(252, 124);
	pSprite->SetAtlasGridSize(10, 5);
	pSprite->SetSampleRate(15);
	pSprite->SetLoop(true);

	pSprite->SaveSprite("Main_SingleButtonOver.aclp");
	pOverRenderer->AddSprite("Main_SingleOver", pSprite);
	pOverRenderer->ChangeCurrentClip("Main_SingleOver");
	delete pSprite;

	pBottomLayer->AddGameObject(pButtonOver);
	pButtonOver->GetTransform()->SetScale(CVector2(1.5f, 1.5f));

	pOverRenderer->SetEnable(false);



	CGameObject* pButton = new CGameObject("SingleButton");
	pBottomLayer->AddGameObject(pButton);

	pCollider = pButton->AddComponent<CButtonCollider>();
	pCollider->SetSize(400, 200);
	pCollider->SetLocalPosition(0, 0);

	CSpriteRenderer* pSpriteRenderer = pButton->AddComponent<CSpriteRenderer>();
	pButton->GetTransform()->SetPivot(0, 0);
	pSpriteRenderer->SetSize(320, 116);

	pSprite = new CSprite;
	pSprite->AddFrame(CVector2(0, 0));
	pSprite->AddFrame(CVector2(1, 0));
	pSprite->AddFrame(CVector2(2, 0));
	pSprite->AddFrame(CVector2(3, 0));
	pSprite->AddFrame(CVector2(4, 0));
	pSprite->AddFrame(CVector2(5, 0));
	pSprite->AddFrame(CVector2(6, 0));
	pSprite->AddFrame(CVector2(7, 0));
	pSprite->AddFrame(CVector2(8, 0));
	pSprite->AddFrame(CVector2(9, 0));

	pSprite->AddFrame(CVector2(0, 1));
	pSprite->AddFrame(CVector2(1, 1));
	pSprite->AddFrame(CVector2(2, 1));
	pSprite->AddFrame(CVector2(3, 1));
	pSprite->AddFrame(CVector2(4, 1));
	pSprite->AddFrame(CVector2(5, 1));
	pSprite->AddFrame(CVector2(6, 1));
	pSprite->AddFrame(CVector2(7, 1));
	pSprite->AddFrame(CVector2(8, 1));
	pSprite->AddFrame(CVector2(9, 1));

	pSprite->AddFrame(CVector2(0, 2));
	pSprite->AddFrame(CVector2(1, 2));
	pSprite->AddFrame(CVector2(2, 2));
	pSprite->AddFrame(CVector2(3, 2));
	pSprite->AddFrame(CVector2(4, 2));


	pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("Main_SingleBase_Atlas"));
	pSprite->SetCellSize(320, 116);
	pSprite->SetAtlasGridSize(10, 3);
	pSprite->SetSampleRate(10);
	pSprite->SetLoop(true);

	pSprite->SaveSprite("Main_SingleButtonBase.aclp");
	pSpriteRenderer->AddSprite("Main_SingleBase", pSprite);
	pSpriteRenderer->ChangeCurrentClip("Main_SingleBase");
	delete pSprite;

	pButton->GetTransform()->SetPosition(100, 50);
	pButton->GetTransform()->SetScale(CVector2(1.25f, 1.25f));
	pButton->GetTransform()->SetPivot(0, 0);
	pSpriteRenderer->SetSize(320, 116);



	CSingleButton* pSingleButton = pButton->AddComponent<CSingleButton>();
	pSingleButton->SetTarget(pOverRenderer);
	pTextRenderer = pButton->AddComponent<CTextRenderer>();
	pTextRenderer->SetPosition(300, 200);
	pTextRenderer->SetText(L"싱글 플레이 (S)");
	pTextRenderer->SetColor(31, 225, 31);
#pragma endregion
		

	//CGameObject* pCursor = GET_SINGLE(CResourceManager)->FindUnit("Cursor")->clone();
	//pTopLayer->AddGameObject(pCursor);
	//pCursor->GetComponent<CSpriteRenderer>()->ChangeCurrentClip("CursorNormal");
	//pCursor->AddComponent<CCursorMove>();

}


CMainMenuScene::~CMainMenuScene()
{
}

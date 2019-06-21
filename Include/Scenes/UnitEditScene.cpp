#include "UnitEditScene.h"
#include "../Sprite.h"
#include "../ResourceManager.h"
#include "../Texture.h"
#include "../Components/SpriteRenderer.h"
#include "../Layer.h"
#include "../GameObject.h"
#include "../Component.h"
#include "../FileStream.h"

//test
#include "../Components/CursorMove.h"

CUnitEditScene::CUnitEditScene()
{
	SetName("DefaultScene");

	CLayer* pLayer = GetLayer("Default");
	CLayer* pTopLayer = CreateLayer("Top", INT_MAX);
	pTopLayer->SetScene(this);
	this->AddLayer(pTopLayer);

	
	
	CGameObject* pCursor = GET_SINGLE(CResourceManager)->FindUnit("Cursor")->clone();
	pLayer->AddGameObject(pCursor);
	pCursor->GetComponent<CSpriteRenderer>()->ChangeCurrentClip("CursorNormal");
	pCursor->AddComponent<CCursorMove>();

	
	//CGameObject* pCursor = new CGameObject("Cursor");
	//CSpriteRenderer* pRenderer = pCursor->AddComponent<CSpriteRenderer>();	
	//pRenderer->SetSize(80, 80);
	//pCursorSprite->SetRenderer(pRenderer);
	//pRenderer->AddSprite("CursorNormal", pCursorSprite);
	//pRenderer->ChangeCurrentClip("CursorNormal");
	//pTopLayer->AddGameObject(pCursor);
	//CTest* pTest = pCursor->AddComponent<CTest>();
	//
	//GET_SINGLE(CFileStream)->SaveUnit(pCursor, "Cursor.unit");
	

}


CUnitEditScene::~CUnitEditScene()
{
}

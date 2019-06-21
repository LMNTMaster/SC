#include "DefaultScene.h"
#include "../Layer.h"
#include "../GameObject.h"
#include "../Components/TextureRenderer.h"
#include "../Components/TestMove.h"
#include "../Components/GridRenderer.h"
#include "../Core.h"
#include "../Components/Transform.h"
#include "../Component.h"
#include "../Components/Camera.h"
#include "../Components/CameraMove.h"
#include "../Components/SpriteRenderer.h"
#include "../Sprite.h"
#include "../ResourceManager.h"
#include "../Texture.h"
#include "../Components/SystemManager.h"
#include "../FileStream.h"
#include "../Collider.h"
#include "../Components/RectCollider.h"
#include "../Components/CircleCollider.h"
#include "../Components/EllipseRenderer.h"
#include "../Components/UIRenderer.h"
#include "../Components/CollisionTile.h"

CDefaultScene::CDefaultScene()
{
	SetName("DefaultScene");

	CLayer* pGroundUnitLayer = CreateLayer("Ground Unit" , 5);	
	pGroundUnitLayer->SetZOrder(1);
	this->AddLayer(pGroundUnitLayer);

	CLayer* pAirUnitLayer = CreateLayer("Air Unit", 10);
	pAirUnitLayer->SetScene(this);
	this->AddLayer(pAirUnitLayer);
	
	CLayer* pTerrainLayer = CreateLayer("Terrain", -1);
	pTerrainLayer->SetScene(this);
	this->AddLayer(pTerrainLayer);
	
	CLayer* pUIBackgroundLayer = CreateLayer("UI Background", 53);
	pUIBackgroundLayer->SetScene(this);
	this->AddLayer(pUIBackgroundLayer);

	CLayer* pUILayer = CreateLayer("UI", 54);
	pUILayer->SetScene(this);
	this->AddLayer(pUILayer);

	CLayer* pUIForegroundLayer = CreateLayer("UI Foreground", 55);
	pUIForegroundLayer->SetScene(this);
	this->AddLayer(pUIForegroundLayer);

	CLayer* pTopLayer = CreateLayer("Top", 56);
	pTopLayer->SetScene(this);
	this->AddLayer(pTopLayer);


	CCameraMove* pCameraMove = GetCamera()->GameObject()->AddComponent<CCameraMove>();
	m_TileSize = CVector2(64,64);
	m_GridSize = CVector2(32, 32);

	GetCamera()->Transform()->SetPivot(0,0);

	ShowCursor(false);

	CGameObject* pBottomUIPanel = new CGameObject("Bottom Panel");
	pUILayer->AddGameObject(pBottomUIPanel);
	CUIRenderer* pBottomPanelRenderer = pBottomUIPanel->AddComponent<CUIRenderer>();
	pBottomPanelRenderer->SetTexture("TerranBottomPanel", L"BottomPanel\\ConsolePanel\\ConsolePanel_Terran.bmp", UI_TEXTURE_PATH);
	pBottomPanelRenderer->SetSize(1280, 960);

	pBottomUIPanel->GetTransform()->SetPivot(0, 0);
	CVector2 pos = GET_SINGLE(CCore)->GetScreenSize();
	pos.x = pos.x / 2;
	pBottomUIPanel->GetTransform()->SetPosition(CVector2(0,-240));

	//pBottomUIPanel->GetTransform()->SetPosition();

	CGameObject* pMouse = new CGameObject("Mouse");
	CSpriteRenderer* pMouseRenderer = pMouse->AddComponent<CSpriteRenderer>();
	pMouseRenderer->SetSize(80, 80);
	pMouse->AddComponent<CSystemManager>();
	pTopLayer->AddGameObject(pMouse);
	pMouse->GetTransform()->SetPivot(0, 0);

	CSprite* pCursorSprite = new CSprite;
	CTexture* pAtlasTexture = GET_SINGLE(CResourceManager)->LoadTexture("Cursor", L"Cursor.bmp", UI_TEXTURE_PATH);
	pCursorSprite->SetAtlas(pAtlasTexture);
	pCursorSprite->SetCellSize(80,80);
	pCursorSprite->SetAtlasGridSize(16,16);
	pCursorSprite->SetSampleRate(5);
	pCursorSprite->SetLoop(true);

	pCursorSprite->AddFrame(CVector2(0, 0));
	pCursorSprite->AddFrame(CVector2(1, 0));
	pCursorSprite->AddFrame(CVector2(2, 0));
	pCursorSprite->AddFrame(CVector2(3, 0));
	pCursorSprite->AddFrame(CVector2(4, 0));
	pMouseRenderer->AddSprite("CursorNormal", pCursorSprite);
	pMouseRenderer->ChangeCurrentClip("CursorNormal");
	delete pCursorSprite;

	pCursorSprite = new CSprite;
	pCursorSprite->SetAtlas(pAtlasTexture);
	pCursorSprite->SetCellSize(80, 80);
	pCursorSprite->SetAtlasGridSize(16, 16);
	pCursorSprite->SetSampleRate(5);
	pCursorSprite->SetLoop(true);
	pCursorSprite->AddFrame(CVector2(0, 2));
	pCursorSprite->AddFrame(CVector2(1, 2));
	pMouseRenderer->AddSprite("BottomEdge", pCursorSprite);
	delete pCursorSprite;

	pCursorSprite = new CSprite;
	pCursorSprite->SetAtlas(pAtlasTexture);
	pCursorSprite->SetCellSize(80, 80);
	pCursorSprite->SetAtlasGridSize(16, 16);
	pCursorSprite->SetSampleRate(5);
	pCursorSprite->SetLoop(true);
	pCursorSprite->AddFrame(CVector2(2, 2));
	pCursorSprite->AddFrame(CVector2(3, 2));
	pMouseRenderer->AddSprite("LeftBottomEdge", pCursorSprite);
	delete pCursorSprite;

	pCursorSprite = new CSprite;
	pCursorSprite->SetAtlas(pAtlasTexture);
	pCursorSprite->SetCellSize(80, 80);
	pCursorSprite->SetAtlasGridSize(16, 16);
	pCursorSprite->SetSampleRate(5);
	pCursorSprite->SetLoop(true);
	pCursorSprite->AddFrame(CVector2(4, 2));
	pCursorSprite->AddFrame(CVector2(5, 2));
	pMouseRenderer->AddSprite("RightBottomEdge", pCursorSprite);
	delete pCursorSprite;

	pCursorSprite = new CSprite;
	pCursorSprite->SetAtlas(pAtlasTexture);
	pCursorSprite->SetCellSize(80, 80);
	pCursorSprite->SetAtlasGridSize(16, 16);
	pCursorSprite->SetSampleRate(5);
	pCursorSprite->SetLoop(true);
	pCursorSprite->AddFrame(CVector2(6, 2));
	pCursorSprite->AddFrame(CVector2(7, 2));
	pMouseRenderer->AddSprite("LeftEdge", pCursorSprite);
	delete pCursorSprite;

	pCursorSprite = new CSprite;
	pCursorSprite->SetAtlas(pAtlasTexture);
	pCursorSprite->SetCellSize(80, 80);
	pCursorSprite->SetAtlasGridSize(16, 16);
	pCursorSprite->SetSampleRate(5);
	pCursorSprite->SetLoop(true);
	pCursorSprite->AddFrame(CVector2(8, 2));
	pCursorSprite->AddFrame(CVector2(9, 2));
	pMouseRenderer->AddSprite("RightEdge", pCursorSprite);
	delete pCursorSprite;

	pCursorSprite = new CSprite;
	pCursorSprite->SetAtlas(pAtlasTexture);
	pCursorSprite->SetCellSize(80, 80);
	pCursorSprite->SetAtlasGridSize(16, 16);
	pCursorSprite->SetSampleRate(5);
	pCursorSprite->SetLoop(true);
	pCursorSprite->AddFrame(CVector2(10, 2));
	pCursorSprite->AddFrame(CVector2(11, 2));
	pMouseRenderer->AddSprite("TopEdge", pCursorSprite);
	delete pCursorSprite;

	pCursorSprite = new CSprite;
	pCursorSprite->SetAtlas(pAtlasTexture);
	pCursorSprite->SetCellSize(80, 80);
	pCursorSprite->SetAtlasGridSize(16, 16);
	pCursorSprite->SetSampleRate(5);
	pCursorSprite->SetLoop(true);
	pCursorSprite->AddFrame(CVector2(12, 2));
	pCursorSprite->AddFrame(CVector2(13, 2));
	pMouseRenderer->AddSprite("LeftTopEdge", pCursorSprite);
	delete pCursorSprite;

	pCursorSprite = new CSprite;
	pCursorSprite->SetAtlas(pAtlasTexture);
	pCursorSprite->SetCellSize(80, 80);
	pCursorSprite->SetAtlasGridSize(16, 16);
	pCursorSprite->SetSampleRate(5);
	pCursorSprite->SetLoop(true);
	pCursorSprite->AddFrame(CVector2(14, 2));
	pCursorSprite->AddFrame(CVector2(15, 2));
	pMouseRenderer->AddSprite("RightTopEdge", pCursorSprite);
	delete pCursorSprite;

	pCursorSprite = new CSprite;
	pCursorSprite->SetAtlas(pAtlasTexture);
	pCursorSprite->SetCellSize(80, 80);
	pCursorSprite->SetAtlasGridSize(16, 16);
	pCursorSprite->SetSampleRate(5);
	pCursorSprite->SetLoop(true); 

	pCursorSprite->AddFrame(CVector2(0, 1));
	pMouseRenderer->AddSprite("CursorRange", pCursorSprite);
	
	delete pCursorSprite;
	
	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			CGameObject* pPlayer = new CGameObject("Player");
			pGroundUnitLayer->AddGameObject(pPlayer);

			pPlayer->GetTransform()->SetPosition(CVector2(i * 30, j * 30));
			pPlayer->GetTransform()->SetPivot(0.5f, 0.6f);

			//CRectCollider* pRectCollider = pPlayer->AddComponent<CRectCollider>();
			//pRectCollider->SetSize(20, 30);

			CCircleCollider* pCircleCollider = pPlayer->AddComponent<CCircleCollider>();
			pCircleCollider->SetRadius(12);
			pCircleCollider->SetTileCollisionRadius(12);
			pCircleCollider->SetLocalPosition(CVector2(0,0));
			

			CEllipseRenderer* pSelectEllipseRenderer = pPlayer->AddComponent<CEllipseRenderer>();
			pSelectEllipseRenderer->SetMinorAxisLength(8);
			pSelectEllipseRenderer->SetThickness(2);
			pSelectEllipseRenderer->SetLocalPosition(0, 10);

			CSpriteRenderer* pRenderer = pPlayer->AddComponent<CSpriteRenderer>();
			pRenderer->SetSize(64, 64);

			{
				CSprite* pSprite = new CSprite;
				wchar_t atlasDirectory[LONG_MAX_PATH] = L"Terran\\Marine\\marine_right.bmp";
				char strTextureKey[128] = "MarineRight";
				CVector2 cellSize = CVector2(64, 64);
				CVector2 atlasGridSize = CVector2(17, 14);
				unsigned int samplerate = 30;
				size_t frameSize = 0;
				bool loop = true;

				CTexture* pAtlasTexture = GET_SINGLE(CResourceManager)->LoadTexture(string(strTextureKey), atlasDirectory, UNIT_TEXTURE_PATH);
				CTexture* pColoredAtlasTexture = pAtlasTexture;
				//CTexture* pColoredAtlasTexture = GET_SINGLE(CFileStream)->SetTeamColor("BlueRight", "marine_right_temp.bmp", pAtlasTexture, 0, 0, -1);
				//CTexture* pColoredAtlasTexture = GET_SINGLE(CFileStream)->SetTeamColor("GreenRight", "marine_left_temp.bmp", pAtlasTexture, 50, -1, 0);
				//CTexture* pColoredAtlasTexture = GET_SINGLE(CFileStream)->SetTeamColor("PurpleRight", "marine_left_temp.bmp", pAtlasTexture, 125, 0, -1);

				pSprite->SetAtlas(pColoredAtlasTexture);
				pSprite->SetCellSize(cellSize);
				pSprite->SetAtlasGridSize(atlasGridSize);
				pSprite->SetSampleRate(samplerate);
				pSprite->SetLoop(loop);

				pSprite->AddFrame(CVector2(0, 0));
				pSprite->AddFrame(CVector2(0, 1));
				pSprite->AddFrame(CVector2(0, 2));
				pSprite->AddFrame(CVector2(0, 3));
				pSprite->AddFrame(CVector2(0, 2));
				pSprite->AddFrame(CVector2(0, 3));
				pSprite->AddFrame(CVector2(0, 2));
				pSprite->AddFrame(CVector2(0, 3));
				pSprite->AddFrame(CVector2(0, 2));
				pSprite->AddFrame(CVector2(0, 1));

				frameSize = pSprite->GetClipLength();

				pRenderer->AddSprite("MarineAttack0", pSprite);
				pRenderer->ChangeCurrentClip("MarineAttack0");


				FILE* pFile = NULL;

				fopen_s(&pFile, "MarineAttack0.animclip", "wb");
				fwrite(&strTextureKey, sizeof(char) * 128, 1, pFile);
				fwrite(&atlasDirectory, sizeof(atlasDirectory), 1, pFile);
				fwrite(&cellSize, sizeof(CVector2), 1, pFile);
				fwrite(&atlasGridSize, sizeof(CVector2), 1, pFile);
				fwrite(&samplerate, sizeof(unsigned int), 1, pFile);
				fwrite(&loop, sizeof(bool), 1, pFile);
				fwrite(&frameSize, sizeof(size_t), 1, pFile);

				for (size_t i = 0; i < frameSize; ++i)
				{
					CVector2 temp = pSprite->GetFrameOffset(i);
					fwrite(&temp, sizeof(CVector2), 1, pFile);
				}

				fclose(pFile);
				delete pSprite;


				pSprite = new CSprite;
				pSprite->SetAtlas(pColoredAtlasTexture);
				pSprite->SetCellSize(64, 64);
				pSprite->SetAtlasGridSize(17, 14);
				pSprite->AddFrame(CVector2(2, 0));
				pSprite->AddFrame(CVector2(2, 1));
				pSprite->AddFrame(CVector2(2, 2));
				pSprite->AddFrame(CVector2(2, 3));
				pSprite->AddFrame(CVector2(2, 2));
				pSprite->AddFrame(CVector2(2, 3));
				pSprite->AddFrame(CVector2(2, 2));
				pSprite->AddFrame(CVector2(2, 3));
				pSprite->AddFrame(CVector2(2, 2));
				pSprite->AddFrame(CVector2(2, 1));
				pSprite->SetSampleRate(30);
				pRenderer->AddSprite("MarineAttack1", pSprite);
				delete pSprite;

				pSprite = new CSprite;
				pSprite->SetAtlas(pColoredAtlasTexture);
				pSprite->SetCellSize(64, 64);
				pSprite->SetAtlasGridSize(17, 14);
				pSprite->AddFrame(CVector2(4, 0));
				pSprite->AddFrame(CVector2(4, 1));
				pSprite->AddFrame(CVector2(4, 2));
				pSprite->AddFrame(CVector2(4, 3));
				pSprite->AddFrame(CVector2(4, 2));
				pSprite->AddFrame(CVector2(4, 3));
				pSprite->AddFrame(CVector2(4, 2));
				pSprite->AddFrame(CVector2(4, 3));
				pSprite->AddFrame(CVector2(4, 2));
				pSprite->AddFrame(CVector2(4, 1));
				pSprite->SetSampleRate(30);
				pRenderer->AddSprite("MarineAttack2", pSprite);
				delete pSprite;


				pSprite = new CSprite;
				pSprite->SetAtlas(pColoredAtlasTexture);
				pSprite->SetCellSize(64, 64);
				pSprite->SetAtlasGridSize(17, 14);
				pSprite->AddFrame(CVector2(6, 0));
				pSprite->AddFrame(CVector2(6, 1));
				pSprite->AddFrame(CVector2(6, 2));
				pSprite->AddFrame(CVector2(6, 3));
				pSprite->AddFrame(CVector2(6, 2));
				pSprite->AddFrame(CVector2(6, 3));
				pSprite->AddFrame(CVector2(6, 2));
				pSprite->AddFrame(CVector2(6, 3));
				pSprite->AddFrame(CVector2(6, 2));
				pSprite->AddFrame(CVector2(6, 1));
				pSprite->SetSampleRate(30);
				pRenderer->AddSprite("MarineAttack3", pSprite);
				delete pSprite;

				pSprite = new CSprite;
				pSprite->SetAtlas(pColoredAtlasTexture);
				pSprite->SetCellSize(64, 64);
				pSprite->SetAtlasGridSize(17, 14);
				pSprite->AddFrame(CVector2(8, 0));
				pSprite->AddFrame(CVector2(8, 1));
				pSprite->AddFrame(CVector2(8, 2));
				pSprite->AddFrame(CVector2(8, 3));
				pSprite->AddFrame(CVector2(8, 2));
				pSprite->AddFrame(CVector2(8, 3));
				pSprite->AddFrame(CVector2(8, 2));
				pSprite->AddFrame(CVector2(8, 3));
				pSprite->AddFrame(CVector2(8, 2));
				pSprite->AddFrame(CVector2(8, 1));
				pSprite->SetSampleRate(30);
				pRenderer->AddSprite("MarineAttack4", pSprite);
				delete pSprite;

				pSprite = new CSprite;
				pSprite->SetAtlas(pColoredAtlasTexture);
				pSprite->SetCellSize(64, 64);
				pSprite->SetAtlasGridSize(17, 14);
				pSprite->AddFrame(CVector2(10, 0));
				pSprite->AddFrame(CVector2(10, 1));
				pSprite->AddFrame(CVector2(10, 2));
				pSprite->AddFrame(CVector2(10, 3));
				pSprite->AddFrame(CVector2(10, 2));
				pSprite->AddFrame(CVector2(10, 3));
				pSprite->AddFrame(CVector2(10, 2));
				pSprite->AddFrame(CVector2(10, 3));
				pSprite->AddFrame(CVector2(10, 2));
				pSprite->AddFrame(CVector2(10, 1));
				pSprite->SetSampleRate(30);
				pRenderer->AddSprite("MarineAttack5", pSprite);
				delete pSprite;

				pSprite = new CSprite;
				pSprite->SetAtlas(pColoredAtlasTexture);
				pSprite->SetCellSize(64, 64);
				pSprite->SetAtlasGridSize(17, 14);
				pSprite->AddFrame(CVector2(12, 0));
				pSprite->AddFrame(CVector2(12, 1));
				pSprite->AddFrame(CVector2(12, 2));
				pSprite->AddFrame(CVector2(12, 3));
				pSprite->AddFrame(CVector2(12, 2));
				pSprite->AddFrame(CVector2(12, 3));
				pSprite->AddFrame(CVector2(12, 2));
				pSprite->AddFrame(CVector2(12, 3));
				pSprite->AddFrame(CVector2(12, 2));
				pSprite->AddFrame(CVector2(12, 1));
				pSprite->SetSampleRate(30);
				pRenderer->AddSprite("MarineAttack6", pSprite);
				delete pSprite;

				pSprite = new CSprite;
				pSprite->SetAtlas(pColoredAtlasTexture);
				pSprite->SetCellSize(64, 64);
				pSprite->SetAtlasGridSize(17, 14);
				pSprite->AddFrame(CVector2(14, 0));
				pSprite->AddFrame(CVector2(14, 1));
				pSprite->AddFrame(CVector2(14, 2));
				pSprite->AddFrame(CVector2(14, 3));
				pSprite->AddFrame(CVector2(14, 2));
				pSprite->AddFrame(CVector2(14, 3));
				pSprite->AddFrame(CVector2(14, 2));
				pSprite->AddFrame(CVector2(14, 3));
				pSprite->AddFrame(CVector2(14, 2));
				pSprite->AddFrame(CVector2(14, 1));
				pSprite->SetSampleRate(30);
				pRenderer->AddSprite("MarineAttack7", pSprite);
				delete pSprite;

				pSprite = new CSprite;
				pSprite->SetAtlas(pColoredAtlasTexture);
				pSprite->SetCellSize(64, 64);
				pSprite->SetAtlasGridSize(17, 14);
				pSprite->AddFrame(CVector2(16, 0));
				pSprite->AddFrame(CVector2(16, 1));
				pSprite->AddFrame(CVector2(16, 2));
				pSprite->AddFrame(CVector2(16, 3));
				pSprite->AddFrame(CVector2(16, 2));
				pSprite->AddFrame(CVector2(16, 3));
				pSprite->AddFrame(CVector2(16, 2));
				pSprite->AddFrame(CVector2(16, 3));
				pSprite->AddFrame(CVector2(16, 2));
				pSprite->AddFrame(CVector2(16, 1));
				pSprite->SetSampleRate(30);
				pRenderer->AddSprite("MarineAttack8", pSprite);
				delete pSprite;
			}

			{

				CSprite* pSprite = new CSprite;
				wchar_t atlasDirectory[LONG_MAX_PATH] = L"Terran\\Marine\\marine_left.bmp";
				char strTextureKey[128] = "MarineLeft";

				CTexture* pAtlasTexture = GET_SINGLE(CResourceManager)->LoadTexture(string(strTextureKey), atlasDirectory, UNIT_TEXTURE_PATH);
				CTexture* pColoredAtlasTexture = pAtlasTexture;
				//CTexture* pColoredAtlasTexture = GET_SINGLE(CFileStream)->SetTeamColor("BlueLeft", "marine_left_temp.bmp", pAtlasTexture, 0, 0, -1);
				//CTexture* pColoredAtlasTexture = GET_SINGLE(CFileStream)->SetTeamColor("GreenLeft", "marine_left_temp.bmp", pAtlasTexture,50, -1, 0);
				//CTexture* pColoredAtlasTexture = GET_SINGLE(CFileStream)->SetTeamColor("PurpleLeft", "marine_left_temp.bmp", pAtlasTexture, 125, 0, -1);

				pSprite->SetAtlas(pColoredAtlasTexture);
				pSprite->SetCellSize(64, 64);
				pSprite->SetAtlasGridSize(17, 14);
				pSprite->AddFrame(CVector2(2, 0));
				pSprite->AddFrame(CVector2(2, 1));
				pSprite->AddFrame(CVector2(2, 2));
				pSprite->AddFrame(CVector2(2, 3));
				pSprite->AddFrame(CVector2(2, 2));
				pSprite->AddFrame(CVector2(2, 3));
				pSprite->AddFrame(CVector2(2, 2));
				pSprite->AddFrame(CVector2(2, 3));
				pSprite->AddFrame(CVector2(2, 2));
				pSprite->AddFrame(CVector2(2, 1));
				pSprite->SetSampleRate(30);
				pRenderer->AddSprite("MarineAttack9", pSprite);
				delete pSprite;

				pSprite = new CSprite;
				pSprite->SetAtlas(pColoredAtlasTexture);
				pSprite->SetCellSize(64, 64);
				pSprite->SetAtlasGridSize(17, 14);
				pSprite->AddFrame(CVector2(4, 0));
				pSprite->AddFrame(CVector2(4, 1));
				pSprite->AddFrame(CVector2(4, 2));
				pSprite->AddFrame(CVector2(4, 3));
				pSprite->AddFrame(CVector2(4, 2));
				pSprite->AddFrame(CVector2(4, 3));
				pSprite->AddFrame(CVector2(4, 2));
				pSprite->AddFrame(CVector2(4, 3));
				pSprite->AddFrame(CVector2(4, 2));
				pSprite->AddFrame(CVector2(4, 1));
				pSprite->SetSampleRate(30);
				pRenderer->AddSprite("MarineAttack10", pSprite);
				delete pSprite;


				pSprite = new CSprite;
				pSprite->SetAtlas(pColoredAtlasTexture);
				pSprite->SetCellSize(64, 64);
				pSprite->SetAtlasGridSize(17, 14);
				pSprite->AddFrame(CVector2(6, 0));
				pSprite->AddFrame(CVector2(6, 1));
				pSprite->AddFrame(CVector2(6, 2));
				pSprite->AddFrame(CVector2(6, 3));
				pSprite->AddFrame(CVector2(6, 2));
				pSprite->AddFrame(CVector2(6, 3));
				pSprite->AddFrame(CVector2(6, 2));
				pSprite->AddFrame(CVector2(6, 3));
				pSprite->AddFrame(CVector2(6, 2));
				pSprite->AddFrame(CVector2(6, 1));
				pSprite->SetSampleRate(30);
				pRenderer->AddSprite("MarineAttack11", pSprite);
				delete pSprite;

				pSprite = new CSprite;
				pSprite->SetAtlas(pColoredAtlasTexture);
				pSprite->SetCellSize(64, 64);
				pSprite->SetAtlasGridSize(17, 14);
				pSprite->AddFrame(CVector2(8, 0));
				pSprite->AddFrame(CVector2(8, 1));
				pSprite->AddFrame(CVector2(8, 2));
				pSprite->AddFrame(CVector2(8, 3));
				pSprite->AddFrame(CVector2(8, 2));
				pSprite->AddFrame(CVector2(8, 3));
				pSprite->AddFrame(CVector2(8, 2));
				pSprite->AddFrame(CVector2(8, 3));
				pSprite->AddFrame(CVector2(8, 2));
				pSprite->AddFrame(CVector2(8, 1));
				pSprite->SetSampleRate(30);
				pRenderer->AddSprite("MarineAttack12", pSprite);
				delete pSprite;

				pSprite = new CSprite;
				pSprite->SetAtlas(pColoredAtlasTexture);
				pSprite->SetCellSize(64, 64);
				pSprite->SetAtlasGridSize(17, 14);
				pSprite->AddFrame(CVector2(10, 0));
				pSprite->AddFrame(CVector2(10, 1));
				pSprite->AddFrame(CVector2(10, 2));
				pSprite->AddFrame(CVector2(10, 3));
				pSprite->AddFrame(CVector2(10, 2));
				pSprite->AddFrame(CVector2(10, 3));
				pSprite->AddFrame(CVector2(10, 2));
				pSprite->AddFrame(CVector2(10, 3));
				pSprite->AddFrame(CVector2(10, 2));
				pSprite->AddFrame(CVector2(10, 1));
				pSprite->SetSampleRate(30);
				pRenderer->AddSprite("MarineAttack13", pSprite);
				delete pSprite;

				pSprite = new CSprite;
				pSprite->SetAtlas(pColoredAtlasTexture);
				pSprite->SetCellSize(64, 64);
				pSprite->SetAtlasGridSize(17, 14);
				pSprite->AddFrame(CVector2(12, 0));
				pSprite->AddFrame(CVector2(12, 1));
				pSprite->AddFrame(CVector2(12, 2));
				pSprite->AddFrame(CVector2(12, 3));
				pSprite->AddFrame(CVector2(12, 2));
				pSprite->AddFrame(CVector2(12, 3));
				pSprite->AddFrame(CVector2(12, 2));
				pSprite->AddFrame(CVector2(12, 3));
				pSprite->AddFrame(CVector2(12, 2));
				pSprite->AddFrame(CVector2(12, 1));
				pSprite->SetSampleRate(30);
				pRenderer->AddSprite("MarineAttack14", pSprite);
				delete pSprite;

				pSprite = new CSprite;
				pSprite->SetAtlas(pColoredAtlasTexture);
				pSprite->SetCellSize(64, 64);
				pSprite->SetAtlasGridSize(17, 14);
				pSprite->AddFrame(CVector2(15, 0));
				pSprite->AddFrame(CVector2(15, 1));
				pSprite->AddFrame(CVector2(15, 2));
				pSprite->AddFrame(CVector2(15, 3));
				pSprite->AddFrame(CVector2(15, 2));
				pSprite->AddFrame(CVector2(15, 3));
				pSprite->AddFrame(CVector2(15, 2));
				pSprite->AddFrame(CVector2(15, 3));
				pSprite->AddFrame(CVector2(15, 2));
				pSprite->AddFrame(CVector2(15, 1));
				pSprite->SetSampleRate(30);
				pRenderer->AddSprite("MarineAttack15", pSprite);
				delete pSprite;

			}


			CTestMove* pMove = pPlayer->AddComponent<CTestMove>();
		}		
	}
   
	//m_vecTile.clear();
	//m_vecTile.resize(m_GridSize.x * m_GridSize.y);
	//
	//for (int i = 0; i < m_GridSize.y; ++i)
	//{
	//	for (int j = 0; j < m_GridSize.x; ++j)
	//	{
	//		CGameObject* pTerrain = new CGameObject("Terrain");
	//		pTerrainLayer->AddGameObject(pTerrain);
	//		pTerrain->GetTransform()->SetPivot(0, 0);
	//		pTerrain->GetTransform()->SetPosition(CVector2(j * 64, i * 64));
	//
	//		CCollisionTile* pCollisionTile = pTerrain->AddComponent<CCollisionTile>();
	//		CTextureRenderer*  pRenderer = pTerrain->AddComponent<CTextureRenderer>();
	//		int randNum = rand() % 40 + 60;
	//		wstring directory(L"Badland\\");
	//		wstring fileName(L"badlands0");
	//		wstring ex(L".bmp");
	//		string keyName;
	//		keyName.assign(fileName.begin(), fileName.end());
	//		keyName += to_string(randNum);
	//		fileName = directory + fileName + to_wstring(randNum) + ex;
	//
	//		pRenderer->SetTexture(keyName, fileName.c_str(), TILESET_TEXTURE_PATH);
	//		pRenderer->SetSize(64, 64);
	//
	//		pCollisionTile->SetCellIndex(i * m_GridSize.x + j);
	//		m_vecTile[i * m_GridSize.x + j] = pCollisionTile;
	//		//m_vecTile.push_back(pCollisionTile);
	//	}
	//}	

#ifdef _DEBUG

	CGameObject* pGrid = new CGameObject("Grid");
	pTerrainLayer->AddGameObject(pGrid);
	CGridRenderer* pGridRenderer = pGrid->AddComponent<CGridRenderer>();
	pGridRenderer->SetCellSize(64, 64);
	pGridRenderer->SetWidthCount(m_GridSize.x);
	pGridRenderer->SetHeightCount(m_GridSize.y);

#endif // DEBUG


}


CDefaultScene::~CDefaultScene()
{
}

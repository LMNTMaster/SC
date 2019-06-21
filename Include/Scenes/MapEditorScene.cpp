#include "MapEditorScene.h"
#include "../Layer.h"
#include "../GameObject.h"
#include "../Components/Transform.h"
#include "../Components/GridRenderer.h"
#include "../Components/Camera.h"
#include "../Components/CameraMove.h"
#include "../Components/TerrainRenderer.h"
#include "../ResourceManager.h"
#include "../Tile.h"
#include "../Components/EditorManager.h"
#include "../Components/Structure.h"
#include "../Components/SpriteRenderer.h"
#include "../Sprite.h"
#include "../Texture.h"
#include "../FileStream.h"
#include "../Components/GameResource.h"
#include "../Components/Player.h"

CMapEditorScene::CMapEditorScene()
{
	SetName("EditorScene");

	CLayer* pLayer = GetLayer("Default");


	CLayer* pUnitLayer = CreateLayer("UnitLayer", 10);
	pUnitLayer->SetScene(this);
	this->AddLayer(pUnitLayer);


	CLayer* pSystemLayer = CreateLayer("System", INT_MAX);
	pSystemLayer->SetScene(this);
	this->AddLayer(pSystemLayer);


	m_GridSize = CVector2(128, 128);
	m_TileSize = CVector2(32, 32);

	m_pCamera->GameObject()->AddComponent<CCameraMove>();

	//타일 사이즈 32 * 32로 변경,
	//타일 Atlas로 변경, TerrainRenderer에서 Atlas를 잘라서 사용하도록 설정
	

	CGameObject* pTerrain = new CGameObject("Terrain");

	pLayer->AddGameObject(pTerrain);
	CTerrainRenderer* pRenderer = pTerrain->AddComponent<CTerrainRenderer>();	
	CEditorManager* pManager = pTerrain->AddComponent<CEditorManager>();
	pManager->Initialize();

	m_pTerrainRenderer = pRenderer;

	for (int y = 0; y < m_GridSize.y; ++y)
	{
		for (int x = 0; x < m_GridSize.x; ++x)
		{
			pRenderer->AddTile(GET_SINGLE(CResourceManager)->GetTileSet(y)[x]);
		}
	}


	
	CGameObject* pPlayer = new CGameObject("Player");
	pSystemLayer->AddGameObject(pPlayer);
	CPlayer* pPlayerComponent = pPlayer->AddComponent<CPlayer>();
	pPlayerComponent->SetTeamColor(TC_RED);
	pPlayerComponent->SetRaceType(RT_TERRAN);
	pPlayerComponent->SetPlayerName("Eunsoo");
	AddPlayer(pPlayerComponent);
	

	//CGameObject* pMineral01 = GET_SINGLE(CResourceManager)->FindUnit("Mineral01")->clone();
	//pUnitLayer->AddGameObject(pMineral01);
	//pMineral01->GetTransform()->SetPosition(512, 512);
	//pMineral01->GetComponent<CSpriteRenderer>()->ChangeCurrentClip("Mineral01_100");
	//
	//CGameObject* pMineral02 = GET_SINGLE(CResourceManager)->FindUnit("Mineral02")->clone();
	//pUnitLayer->AddGameObject(pMineral02);
	//pMineral02->GetTransform()->SetPosition(576, 512);
	//pMineral02->GetComponent<CSpriteRenderer>()->ChangeCurrentClip("Mineral02_100");
	//
	//CGameObject* pMineral03 = GET_SINGLE(CResourceManager)->FindUnit("Mineral03")->clone();
	//pUnitLayer->AddGameObject(pMineral03);
	//pMineral03->GetTransform()->SetPosition(640, 512);
	//pMineral03->GetComponent<CSpriteRenderer>()->ChangeCurrentClip("Mineral03_100");



	/*{
		CGameObject* pMineral = new CGameObject("Mineral01");
		pUnitLayer->AddGameObject(pMineral);
		pMineral->GetTransform()->SetPivot(0.5f, 1.0f);
		pMineral->GetTransform()->SetPosition(512, 512);

		CResource* pResource = pMineral->AddComponent<CResource>();
		CStructure* pStructure = pMineral->AddComponent<CStructure>();		
		pStructure->SetSize(2, 1);
		pStructure->AddBuildableTile(0, 1);
		pStructure->AddBuildableTile(1, 1);
		
		CSpriteRenderer* pSpriteRenderer = pMineral->AddComponent<CSpriteRenderer>();
		pSpriteRenderer->SetSize(64, 96);


		CSprite* pSprite = new CSprite;

		pSprite->AddFrame(CVector2(0, 0));
		pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("Mineral01"));
		pSprite->SetAtlasGridSize(4, 1);
		pSprite->SetCellSize(64, 96);
		pSpriteRenderer->AddSprite("Mineral01_100", pSprite);
		pSprite->SaveSprite("Mineral01_100.aclp");
		delete pSprite;

		pSprite = new CSprite;
		pSprite->AddFrame(CVector2(1, 0));
		pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("Mineral01"));
		pSprite->SetAtlasGridSize(4, 1);
		pSprite->SetCellSize(64, 96);
		pSpriteRenderer->AddSprite("Mineral01_075", pSprite);
		pSprite->SaveSprite("Mineral01_075.aclp");
		delete pSprite;

		pSprite = new CSprite;
		pSprite->AddFrame(CVector2(2, 0));
		pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("Mineral01"));
		pSprite->SetAtlasGridSize(4, 1);
		pSprite->SetCellSize(64, 96);
		pSpriteRenderer->AddSprite("Mineral01_050", pSprite);
		pSprite->SaveSprite("Mineral01_050.aclp");
		delete pSprite;

		pSprite = new CSprite;
		pSprite->AddFrame(CVector2(3, 0));
		pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("Mineral01"));
		pSprite->SetAtlasGridSize(4, 1);
		pSprite->SetCellSize(64, 96);
		pSpriteRenderer->AddSprite("Mineral01_025", pSprite);
		pSprite->SaveSprite("Mineral01_025.aclp");
		delete pSprite;


		pSpriteRenderer->ChangeCurrentClip("Mineral01_100");

		GET_SINGLE(CFileStream)->SaveUnit(pMineral, "Mineral01.unit");
	}

	{
		CGameObject* pMineral = new CGameObject("Mineral02");
		pUnitLayer->AddGameObject(pMineral);
		pMineral->GetTransform()->SetPivot(0.5f, 1.0f);
		pMineral->GetTransform()->SetPosition(640, 512);

		CResource* pResource = pMineral->AddComponent<CResource>();


		CStructure* pStructure = pMineral->AddComponent<CStructure>();
		pStructure->SetSize(2, 1);
		pStructure->AddBuildableTile(0, 1);
		pStructure->AddBuildableTile(1, 1);

		CSpriteRenderer* pSpriteRenderer = pMineral->AddComponent<CSpriteRenderer>();
		pSpriteRenderer->SetSize(64, 96);

		CSprite* pSprite = new CSprite;

		pSprite->AddFrame(CVector2(0, 0));
		pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("Mineral02"));
		pSprite->SetAtlasGridSize(4, 1);
		pSprite->SetCellSize(64, 96);
		pSpriteRenderer->AddSprite("Mineral02_100", pSprite);
		pSprite->SaveSprite("Mineral02_100.aclp");
		delete pSprite;

		pSprite = new CSprite;
		pSprite->AddFrame(CVector2(1, 0));
		pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("Mineral02"));
		pSprite->SetAtlasGridSize(4, 1);
		pSprite->SetCellSize(64, 96);
		pSpriteRenderer->AddSprite("Mineral02_075", pSprite);
		pSprite->SaveSprite("Mineral02_075.aclp");
		delete pSprite;

		pSprite = new CSprite;
		pSprite->AddFrame(CVector2(2, 0));
		pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("Mineral02"));
		pSprite->SetAtlasGridSize(4, 1);
		pSprite->SetCellSize(64, 96);
		pSpriteRenderer->AddSprite("Mineral02_050", pSprite);
		pSprite->SaveSprite("Mineral02_050.aclp");
		delete pSprite;

		pSprite = new CSprite;
		pSprite->AddFrame(CVector2(3, 0));
		pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("Mineral02"));
		pSprite->SetAtlasGridSize(4, 1);
		pSprite->SetCellSize(64, 96);
		pSpriteRenderer->AddSprite("Mineral02_025", pSprite);
		pSprite->SaveSprite("Mineral02_025.aclp");
		delete pSprite;


		pSpriteRenderer->ChangeCurrentClip("Mineral02_100");

		GET_SINGLE(CFileStream)->SaveUnit(pMineral, "Mineral02.unit");
	}

	{
		CGameObject* pMineral = new CGameObject("Mineral03");
		pUnitLayer->AddGameObject(pMineral);
		pMineral->GetTransform()->SetPivot(0.5f, 1.0f);
		pMineral->GetTransform()->SetPosition(768, 512);

		CResource* pResource = pMineral->AddComponent<CResource>();


		CStructure* pStructure = pMineral->AddComponent<CStructure>();
		pStructure->SetSize(2, 1);
		pStructure->AddBuildableTile(0, 1);
		pStructure->AddBuildableTile(1, 1);

		CSpriteRenderer* pSpriteRenderer = pMineral->AddComponent<CSpriteRenderer>();
		pSpriteRenderer->SetSize(64, 96);

		CSprite* pSprite = new CSprite;

		pSprite->AddFrame(CVector2(0, 0));
		pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("Mineral03"));
		pSprite->SetAtlasGridSize(4, 1);
		pSprite->SetCellSize(64, 96);
		pSpriteRenderer->AddSprite("Mineral03_100", pSprite);
		pSprite->SaveSprite("Mineral03_100.aclp");
		delete pSprite;

		pSprite = new CSprite;
		pSprite->AddFrame(CVector2(1, 0));
		pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("Mineral03"));
		pSprite->SetAtlasGridSize(4, 1);
		pSprite->SetCellSize(64, 96);
		pSpriteRenderer->AddSprite("Mineral03_075", pSprite);
		pSprite->SaveSprite("Mineral03_075.aclp");
		delete pSprite;

		pSprite = new CSprite;
		pSprite->AddFrame(CVector2(2, 0));
		pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("Mineral03"));
		pSprite->SetAtlasGridSize(4, 1);
		pSprite->SetCellSize(64, 96);
		pSpriteRenderer->AddSprite("Mineral03_050", pSprite);
		pSprite->SaveSprite("Mineral03_050.aclp");
		delete pSprite;

		pSprite = new CSprite;
		pSprite->AddFrame(CVector2(3, 0));
		pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("Mineral03"));
		pSprite->SetAtlasGridSize(4, 1);
		pSprite->SetCellSize(64, 96);
		pSpriteRenderer->AddSprite("Mineral03_025", pSprite);
		pSprite->SaveSprite("Mineral03_025.aclp");
		delete pSprite;


		pSpriteRenderer->ChangeCurrentClip("Mineral03_100");

		GET_SINGLE(CFileStream)->SaveUnit(pMineral, "Mineral03.unit");
	}*/

	
	//CGameObject* pCommandCenter = GET_SINGLE(CResourceManager)->FindUnit("CommandCenter")->clone();
	//pCommandCenter->GetTransform()->SetPosition(500, 500);
	//pCommandCenter->GetComponent<CSpriteRenderer>()->ChangeCurrentClip("CommandCenter_Normal");
	//pUnitLayer->AddGameObject(pCommandCenter);

	//CGameObject* pCommandCenter = new CGameObject("CommandCenter");
	//pUnitLayer->AddGameObject(pCommandCenter);
	//CStructure* pStrucrtureComponent = pCommandCenter->AddComponent<CStructure>();
	//CSpriteRenderer* pCCRenderer = pCommandCenter->AddComponent<CSpriteRenderer>();
	//pCCRenderer->SetSize(128, 160);
	//pCCRenderer->AddSprite("CommandCenter_Normal", GET_SINGLE(CResourceManager)->FindSprite("CommandCenter_Normal"));
	//pCCRenderer->ChangeCurrentClip("CommandCenter_Normal");
	//
	//pCommandCenter->GetTransform()->SetPosition(300, 300);
	//pCommandCenter->GetTransform()->SetPivot(0.5f, 1.0f);
	//
	//GET_SINGLE(CFileStream)->SaveUnit(pCommandCenter, "CommandCenter.unit");
	//
	//
	//CSprite* pSprite = new CSprite;
	//pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("CommandCenter"));
	//pSprite->SetCellSize(128, 160);
	//pSprite->SetAtlasGridSize(6, 1);
	//pSprite->SetSampleRate(1);
	//pSprite->AddFrame(CVector2(0, 0));
	//
	//pSprite->SaveSprite("CommandCenter_Normal.aclp");
	//
	//pCCRenderer->AddSprite("CommandCenter_Normal", pSprite);
	//delete pSprite;


//#ifdef _DEBUG

	CGameObject* pGrid = new CGameObject("Grid");
	pLayer->AddGameObject(pGrid);
	CGridRenderer* pGridRenderer = pGrid->AddComponent<CGridRenderer>();
	pGridRenderer->SetCellSize(32, 32);
	pGridRenderer->SetWidthCount(m_GridSize.x);
	pGridRenderer->SetHeightCount(m_GridSize.y);

//#endif // DEBUG
}


CMapEditorScene::~CMapEditorScene()
{
}

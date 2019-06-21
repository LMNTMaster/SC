#include "GameScene.h"
#include "../Layer.h"
#include "../ResourceManager.h"
#include "../Components/SpriteRenderer.h"
#include "../GameObject.h"
#include "../Component.h"
#include "../FileStream.h"
#include "../Components/Camera.h"
#include "../Components/CameraMove.h"
#include "../Option.h"
#include "../Components/Transform.h"
#include "../Sprite.h"
#include "../Texture.h"
#include "../Core.h"
#include "../Components/Player.h"
#include "../ConsoleButtonManager.h"
#include "../Components/UnitStatus.h"
#include "../InfoPanelManager.h"
#include "../Components/TextRenderer.h"
#include "../Components/TextureRenderer.h"
#include "../Components/Patrol.h"
#include "../FogOfWarManager.h"
#include "../Components/FOW.h"
#include "../MinimapManager.h"
#include "../Components/MinimapRenderer.h"

//Animator
#include "../Components\Animator\SCVAnimator.h"
#include "../Components\Animator\MineralOrb.h"
#include "../Components\Animator\GasBox.h"
#include "../Components\Animator\GasSac.h"
#include "../Components\Animator\GasTank.h"
#include "../Components/Animator/MarineAnimator.h"
#include "../Components\Animator/FirebatAnimator.h"

//UI

#include "../Components/UIRenderer.h"
#include "../Components/ControlButton.h"
#include "../Components/CreateUnit.h"

//커서
#include "../Components/CursorMove.h"
#include "../Components/Cursor.h"

//터레인
#include "../Components/TerrainRenderer.h"

//유닛
#include "../Components/CircleCollider.h"
#include "../Components/EllipseRenderer.h"

#include "../Components/Move.h"
#include "../Components/Build.h"
#include "../Components/AdvancedBuild.h"
#include "../Components/Attack.h"
#include "../Components/Gather.h"
#include "../Components/Stop.h"
#include "../Components/Hold.h"
#include "../Components/Repair.h"
#include "../Components/UnitInfo.h"
#include "../Components/Deffence.h"
#include "../Components/Shield.h"
#include "../Components/Stimpack.h"
#include "../Components/Structure/Academy.h"
#include "../Components/Structure/Barracks.h"
#include "../Components/Structure/EngineeringBay.h"
#include "../Components/Structure/Factory.h"
#include "../Components/Structure/Starport.h"
#include "../Components/Structure/Armory.h"
#include "../Components/Structure/CommandCenter.h"


//디버그
#include "../Components/TestMove.h"
#include "../Components/GridRenderer.h"
#include "../Components/GameResource.h"

CGameScene::CGameScene()
{
	SetName("GameScene");

#pragma region CreateLayer

	//Render Target : Terrain, Creep
	CLayer* pLayer = GetLayer("Default");
	pLayer->SetName("Terrain");

	//Render Target : Ground Unit, Resources
	CLayer* pGroundUnitLayer = CreateLayer("GroundUnit", 10);
	pGroundUnitLayer->SetScene(this);
	this->AddLayer(pGroundUnitLayer);

	//Render Target : Ground Unit VFX 
	CLayer* pGroundEffectLayer = CreateLayer("GroundVFX", 15);
	pGroundEffectLayer->SetScene(this);
	this->AddLayer(pGroundEffectLayer);

	//Render Target : Air Unit
	CLayer* pAirUnitLayer = CreateLayer("AirUnit", 20);
	pAirUnitLayer->SetScene(this);
	this->AddLayer(pAirUnitLayer);

	//Render Target : Air Unit VFX
	CLayer* pAirEffectLayer = CreateLayer("AirVFX", 25);
	pAirEffectLayer->SetScene(this);
	this->AddLayer(pAirEffectLayer);

	//Render Target : FOW
	CLayer* pFogOfWarLayer = CreateLayer("FOW", 30);
	pFogOfWarLayer->SetScene(this);
	this->AddLayer(pFogOfWarLayer);

	//Render Target : Unit Status Bar, Select Rectangle
	CLayer* pUIGameLayer = CreateLayer("UIGame", 100);
	pUIGameLayer->SetScene(this);
	this->AddLayer(pUIGameLayer);

	//Render Target : BottomPanel Background
	CLayer* pUIBottomLayer = CreateLayer("UIBottom", 150);
	pUIBottomLayer->SetScene(this);
	this->AddLayer(pUIBottomLayer);

	//Render Target : Button , Minimap, Portrait, Wireframe, Unit Info Panel Data
	CLayer* pUIMiddleLayer = CreateLayer("UIMiddle", 200);
	pUIMiddleLayer->SetScene(this);
	this->AddLayer(pUIMiddleLayer);
	GET_SINGLE(CInfoPanelManager)->SetInfoPanelLayer(pUIMiddleLayer);

	//Render Target : Tooltip, Menu
	CLayer* pUITopLayer = CreateLayer("UITop", 250);
	pUITopLayer->SetScene(this);
	this->AddLayer(pUITopLayer);

	//Render Target : Cursor, (Camera)
	CLayer* pSystemLayer = CreateLayer("System", INT_MAX);
	pSystemLayer->SetScene(this);
	this->AddLayer(pSystemLayer);

#pragma endregion
//
//#pragma region SetEffect
//	
//	{
//		CGameObject* pCursorObject = new CGameObject("CursorRequestPointer");
//		CSpriteRenderer* pRenderer = pCursorObject->AddComponent<CSpriteRenderer>();
//		
//		pRenderer->SetSize(44, 28);
//
//		CSprite* pSprite = new CSprite;
//		pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("CursorRequestPointer"));
//		pSprite->SetAtlasGridSize(5, 1);
//		pSprite->SetCellSize(44, 28);
//		pSprite->SetLoop(false);
//		pSprite->SetDestroyOnEnd(true);
//		pSprite->SetSampleRate(20);
//
//		pSprite->AddFrame(0, 0);
//		pSprite->AddFrame(1, 0);
//		pSprite->AddFrame(2, 0);
//		pSprite->AddFrame(3, 0);
//		pSprite->AddFrame(4, 0);
//		pSprite->SaveSprite("CursorRequestPointer.aclp");
//		pRenderer->AddSprite("CursorRequestPointer",pSprite);	
//		delete pSprite;
//
//		GET_SINGLE(CFileStream)->SaveUnit(pCursorObject, "CursorRequestPointer.unit");	
//	}
//
//
//	{
//		CGameObject* pGeyser = new CGameObject("VespeneGeyser");
//		pGeyser->GetTransform()->SetPivot(0, 0);
//		pGeyser->SetPilot(NULL);
//		CEllipseRenderer* pEllipse = pGeyser->AddComponent<CEllipseRenderer>();
//		CSpriteRenderer* pMainRenderer = pGeyser->AddComponent<CSpriteRenderer>();
//		CSpriteRenderer* pVFXRenderer = pGeyser->AddComponent<CSpriteRenderer>();
//		CSpriteRenderer* pVFXRenderer2 = pGeyser->AddComponent<CSpriteRenderer>();
//		CSpriteRenderer* pVFXRenderer3 = pGeyser->AddComponent<CSpriteRenderer>();
//		CResource* pResource = pGeyser->AddComponent<CResource>();
//		CStructure* pStructure = pGeyser->AddComponent<CStructure>();
//		CCircleCollider* pCollider = pGeyser->AddComponent<CCircleCollider>();
//
//		pMainRenderer->SetSize(128, 64);
//		pVFXRenderer->SetSize(32,64);
//		pVFXRenderer2->SetSize(32,64);
//		pVFXRenderer3->SetSize(32,64);
//
//		pCollider->SetRadius(50);
//		pCollider->SetTileCollisionRadius(50);
//		pCollider->SetLocalPosition(CVector2(64, 32));
//
//		pGeyser->SetSelected(false);
//		pGeyser->SetToAirUnit(false);
//		pGeyser->SetPilot(NULL);
//
//		pEllipse->SetMinorAxisLength(40);
//		pEllipse->SetLocalPosition(64, 32);
//		pEllipse->SetMajorAxisScale(1.6f);
//		pEllipse->SetColor(255, 255, 0);
//		pEllipse->SetThickness(2);
//
//		pResource->SetResourceType(RT_VESPENE_GAS);
//		pResource->SetValue(5000);
//		pResource->SetR2BTime(2);
//		pResource->SetR2BTime(5);
//
//		pStructure->SetRequireGas(0);
//		pStructure->SetRequireMineral(0);
//		pStructure->SetSupply(0);
//		pStructure->SetSize(4, 2);
//		pStructure->AddBuildableTile(0, 0); 
//		pStructure->AddBuildableTile(1, 0);
//		pStructure->AddBuildableTile(2, 0);
//		pStructure->AddBuildableTile(3, 0);
//		pStructure->AddBuildableTile(0, 1);
//		pStructure->AddBuildableTile(1, 1);
//		pStructure->AddBuildableTile(2, 1);
//		pStructure->AddBuildableTile(3, 1);
//
//		CSprite* pSprite = new CSprite;
//		pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("VespeneGeyser"));
//		pSprite->SetAtlasGridSize(1, 1);
//		pSprite->SetCellSize(128, 64);
//		pSprite->SetLoop(true);
//		pSprite->SetSampleRate(0.001f);
//		
//		pSprite->AddFrame(0, 0);
//		pMainRenderer->AddSprite("VespeneGeyser", pSprite);
//		pMainRenderer->ChangeCurrentClip("VespeneGeyser");
//		pSprite->SaveSprite("VespeneGeyser.aclp");
//		delete pSprite;
//
//
//
//		pSprite = new CSprite;
//		pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("GeyserSmoke2"));
//		pSprite->SetAtlasGridSize(9, 1);
//		pSprite->SetCellSize(32, 64);
//		pSprite->SetLoop(true);
//		pSprite->SetSampleRate(10);
//
//		//Post Delay
//		for (int i = 0; i < 20; ++i)
//		{
//			pSprite->AddFrame(8, 0);
//		}
//		for (int i = 0; i < 9; ++i)
//		{
//			pSprite->AddFrame(i, 0);
//		}
//
//		pVFXRenderer->AddSprite("GeyserSmoke1", pSprite);
//		pVFXRenderer->ChangeCurrentClip("GeyserSmoke1");
//		pVFXRenderer2->AddSprite("GeyserSmoke1", pSprite);
//		pVFXRenderer2->ChangeCurrentClip("GeyserSmoke1");
//		pSprite->SaveSprite("GeyserSmoke1.aclp");
//		delete pSprite;
//
//
//		pSprite = new CSprite;
//		pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("GeyserSmoke1"));
//		pSprite->SetAtlasGridSize(9, 1);
//		pSprite->SetCellSize(32, 64);
//		pSprite->SetLoop(true);
//		pSprite->SetSampleRate(10);
//
//		//Post Delay
//		for (int i = 0; i < 30; ++i)
//		{
//			pSprite->AddFrame(8, 0);
//		}
//		for (int i = 0; i < 9; ++i)
//		{
//			pSprite->AddFrame(i, 0);
//		}
//		pVFXRenderer3->AddSprite("GeyserSmoke2", pSprite);
//		pVFXRenderer3->ChangeCurrentClip("GeyserSmoke2");
//		pSprite->SaveSprite("GeyserSmoke2.aclp");
//
//		delete pSprite;
//
//		GET_SINGLE(CFileStream)->SaveUnit(pGeyser, "VespeneGeyser.unit");
//
//		delete pGeyser;
//	}
//
//
//	{
//		CSprite* pSprite = new CSprite;
//		pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("SCVAttack"));
//		pSprite->SetAtlasGridSize(10, 1);
//		pSprite->SetCellSize(48, 48);
//		pSprite->SetSampleRate(10);
//		pSprite->SetLoop(false);
//		pSprite->SetDestroyOnEnd(true);
//		pSprite->AddFrame(0, 0);
//		pSprite->AddFrame(1, 0);
//		pSprite->AddFrame(2, 0);
//		pSprite->AddFrame(3, 0);
//		pSprite->AddFrame(4, 0);
//		pSprite->AddFrame(5, 0);
//		pSprite->AddFrame(6, 0);
//		pSprite->AddFrame(7, 0);
//		pSprite->AddFrame(8, 0);
//		pSprite->AddFrame(9, 0);
//		pSprite->SetSpriteKey("SCVAttack");
//		pSprite->SaveSprite("SCVAttack.aclp");
//		delete pSprite;
//	} 
//	{
//		CSprite* pSprite = new CSprite;
//		pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("TerranBulletAttack"));
//		pSprite->SetAtlasGridSize(9, 1);
//		pSprite->SetCellSize(40, 40);
//		pSprite->SetSampleRate(20);
//		pSprite->SetLoop(false);
//		pSprite->SetDestroyOnEnd(true);
//		pSprite->AddFrame(0, 0);
//		pSprite->AddFrame(1, 0);
//		pSprite->AddFrame(2, 0);
//		pSprite->AddFrame(3, 0);
//		pSprite->AddFrame(4, 0);
//		pSprite->AddFrame(5, 0);
//		pSprite->AddFrame(6, 0);
//		pSprite->AddFrame(7, 0);
//		pSprite->AddFrame(8, 0);
//		pSprite->AddFrame(9, 0);
//		pSprite->SetSpriteKey("TerranBulletAttack");
//		pSprite->SaveSprite("TerranBulletAttack.aclp");
//		delete pSprite;
//	}
//
//	{
//		CGameObject* pOrb = new CGameObject("MineralOrb");
//		pOrb->SetPilot(NULL);
//		CSpriteRenderer* pRenderer = pOrb->AddComponent<CSpriteRenderer>();
//		pRenderer->SetSize(32, 32);
//		pOrb->AddComponent<CMineralOrb>();
//				
//		CSprite* pSprite = new CSprite;
//		pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("MineralOrb"));
//		pSprite->SetAtlasGridSize(17, 1);
//		pSprite->SetLoop(true);
//		pSprite->SetCellSize(32, 32);
//		pSprite->SetSampleRate(1);
//		pSprite->AddFrame(0, 0);
//		pSprite->SetSpriteKey("MineralOrb0");
//		pRenderer->AddSprite("MineralOrb0",pSprite);
//		pSprite->SaveSprite("MineralOrb0.aclp");
//		delete pSprite;
//		pSprite = new CSprite;
//		pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("MineralOrb"));
//		pSprite->SetAtlasGridSize(17, 1);
//		pSprite->SetLoop(true);
//		pSprite->SetCellSize(32, 32);
//		pSprite->SetSampleRate(1);
//		pSprite->AddFrame(2, 0);
//		pSprite->SetSpriteKey("MineralOrb1");
//		pRenderer->AddSprite("MineralOrb1", pSprite);
//		pSprite->SaveSprite("MineralOrb1.aclp");
//		delete pSprite;
//		pSprite = new CSprite;
//		pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("MineralOrb"));
//		pSprite->SetAtlasGridSize(17, 1);
//		pSprite->SetLoop(true);
//		pSprite->SetCellSize(32, 32);
//		pSprite->SetSampleRate(1);
//		pSprite->AddFrame(4, 0);
//		pSprite->SetSpriteKey("MineralOrb2");
//		pRenderer->AddSprite("MineralOrb2", pSprite);
//		pSprite->SaveSprite("MineralOrb2.aclp");
//		delete pSprite;
//
//		pSprite = new CSprite;
//		pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("MineralOrb"));
//		pSprite->SetAtlasGridSize(17, 1);
//		pSprite->SetLoop(true);
//		pSprite->SetCellSize(32, 32);
//		pSprite->SetSampleRate(1);
//		pSprite->AddFrame(6, 0);
//		pSprite->SetSpriteKey("MineralOrb3");
//		pRenderer->AddSprite("MineralOrb3", pSprite);
//		pSprite->SaveSprite("MineralOrb3.aclp");
//		delete pSprite;
//		pSprite = new CSprite;
//		pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("MineralOrb"));
//		pSprite->SetAtlasGridSize(17, 1);
//		pSprite->SetLoop(true);
//		pSprite->SetCellSize(32, 32);
//		pSprite->SetSampleRate(1);
//		pSprite->AddFrame(8, 0);
//		pSprite->SetSpriteKey("MineralOrb4");
//		pRenderer->AddSprite("MineralOrb4", pSprite);
//		pSprite->SaveSprite("MineralOrb4.aclp");
//		delete pSprite;
//		pSprite = new CSprite;
//		pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("MineralOrb"));
//		pSprite->SetAtlasGridSize(17, 1);
//		pSprite->SetLoop(true);
//		pSprite->SetCellSize(32, 32);
//		pSprite->SetSampleRate(1);
//		pSprite->AddFrame(10, 0);
//		pSprite->SetSpriteKey("MineralOrb5");
//		pRenderer->AddSprite("MineralOrb5", pSprite);
//		pSprite->SaveSprite("MineralOrb5.aclp");
//		delete pSprite;
//		pSprite = new CSprite;
//		pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("MineralOrb"));
//		pSprite->SetAtlasGridSize(17, 1);
//		pSprite->SetLoop(true);
//		pSprite->SetCellSize(32, 32);
//		pSprite->SetSampleRate(1);
//		pSprite->AddFrame(12, 0);
//		pSprite->SetSpriteKey("MineralOrb6");
//		pRenderer->AddSprite("MineralOrb6", pSprite);
//		pSprite->SaveSprite("MineralOrb6.aclp");
//		delete pSprite;
//		pSprite = new CSprite;
//		pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("MineralOrb"));
//		pSprite->SetAtlasGridSize(17, 1);
//		pSprite->SetLoop(true);
//		pSprite->SetCellSize(32, 32);
//		pSprite->SetSampleRate(1);
//		pSprite->AddFrame(14, 0);
//		pSprite->SetSpriteKey("MineralOrb7");
//		pRenderer->AddSprite("MineralOrb7", pSprite);
//		pSprite->SaveSprite("MineralOrb7.aclp");
//		delete pSprite;
//		pSprite = new CSprite;
//		pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("MineralOrb"));
//		pSprite->SetAtlasGridSize(17, 1);
//		pSprite->SetLoop(true);
//		pSprite->SetCellSize(32, 32);
//		pSprite->SetSampleRate(1);
//		pSprite->AddFrame(16, 0);
//		pSprite->SetSpriteKey("MineralOrb8");
//		pRenderer->AddSprite("MineralOrb8", pSprite);
//		pSprite->SaveSprite("MineralOrb8.aclp");
//		delete pSprite;
//
//		pRenderer->ChangeCurrentClip("MineralOrb0");
//		GET_SINGLE(CFileStream)->SaveUnit(pOrb, "MineralOrb.unit");
//
//		delete pOrb;
//	}
//
//	{
//		CGameObject* pOrb = new CGameObject("GasTank");
//		pOrb->SetPilot(NULL);
//		CSpriteRenderer* pRenderer = pOrb->AddComponent<CSpriteRenderer>();
//		pRenderer->SetSize(32, 32); 
//		pOrb->AddComponent<CGasTank>();
//
//		CSprite* pSprite = new CSprite;
//		pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("GasTank"));
//		pSprite->SetAtlasGridSize(2, 1);
//		pSprite->SetLoop(true);
//		pSprite->SetCellSize(28, 28);
//		pSprite->SetSampleRate(1);
//		pSprite->AddFrame(1, 0);
//		pSprite->SetSpriteKey("GasTank");
//		pRenderer->AddSprite("GasTank", pSprite);
//		pSprite->SaveSprite("GasTank.aclp");
//		delete pSprite;
//		pRenderer->ChangeCurrentClip("GasTank");
//		GET_SINGLE(CFileStream)->SaveUnit(pOrb, "GasTank.unit");
//
//		delete pOrb;
//	}
//		{
//		CGameObject* pOrb = new CGameObject("GasSac");
//		pOrb->SetPilot(NULL);
//		CSpriteRenderer* pRenderer = pOrb->AddComponent<CSpriteRenderer>();
//		pRenderer->SetSize(32, 32);
//
//		CSprite* pSprite = new CSprite;
//		pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("GasSac"));
//		pSprite->SetAtlasGridSize(17, 2);
//		pSprite->SetLoop(true);
//		pSprite->SetCellSize(32, 32);
//		pSprite->SetSampleRate(1);
//		pSprite->AddFrame(0, 1);
//		pSprite->SetSpriteKey("GasSac0");
//		pRenderer->AddSprite("GasSac0", pSprite);
//		pSprite->SaveSprite("GasSac.aclp");
//		delete pSprite;
//		pSprite = new CSprite;
//		pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("GasSac"));
//		pSprite->SetAtlasGridSize(17, 2);
//		pSprite->SetLoop(true);
//		pSprite->SetCellSize(32, 32);
//		pSprite->SetSampleRate(1);
//		pSprite->AddFrame(2, 1);
//		pSprite->SetSpriteKey("GasSac1");
//		pRenderer->AddSprite("GasSac1", pSprite);
//		pSprite->SaveSprite("GasSac1.aclp");
//		delete pSprite;
//		pSprite = new CSprite;
//		pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("GasSac"));
//		pSprite->SetAtlasGridSize(17, 2);
//		pSprite->SetLoop(true);
//		pSprite->SetCellSize(32, 32);
//		pSprite->SetSampleRate(1);
//		pSprite->AddFrame(4, 1);
//		pSprite->SetSpriteKey("GasSac2");
//		pRenderer->AddSprite("GasSac2", pSprite);
//		pSprite->SaveSprite("GasSac2.aclp");
//		delete pSprite;
//
//		pSprite = new CSprite;
//		pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("GasSac"));
//		pSprite->SetAtlasGridSize(17, 2);
//		pSprite->SetLoop(true);
//		pSprite->SetCellSize(32, 32);
//		pSprite->SetSampleRate(1);
//		pSprite->AddFrame(6, 1);
//		pSprite->SetSpriteKey("GasSac3");
//		pRenderer->AddSprite("GasSac3", pSprite);
//		pSprite->SaveSprite("GasSac3.aclp");
//		delete pSprite;
//		pSprite = new CSprite;
//		pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("GasSac"));
//		pSprite->SetAtlasGridSize(17, 2);
//		pSprite->SetLoop(true);
//		pSprite->SetCellSize(32, 32);
//		pSprite->SetSampleRate(1);
//		pSprite->AddFrame(8, 1);
//		pSprite->SetSpriteKey("GasSac4");
//		pRenderer->AddSprite("GasSac4", pSprite);
//		pSprite->SaveSprite("GasSac4.aclp");
//		delete pSprite;
//		pSprite = new CSprite;
//		pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("GasSac"));
//		pSprite->SetAtlasGridSize(17, 2);
//		pSprite->SetLoop(true);
//		pSprite->SetCellSize(32, 32);
//		pSprite->SetSampleRate(1);
//		pSprite->AddFrame(10, 1);
//		pSprite->SetSpriteKey("GasSac5");
//		pRenderer->AddSprite("GasSac5", pSprite);
//		pSprite->SaveSprite("GasSac5.aclp");
//		delete pSprite;
//		pSprite = new CSprite;
//		pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("GasSac"));
//		pSprite->SetAtlasGridSize(17, 2);
//		pSprite->SetLoop(true);
//		pSprite->SetCellSize(32, 32);
//		pSprite->SetSampleRate(1);
//		pSprite->AddFrame(12, 1);
//		pSprite->SetSpriteKey("GasSac6");
//		pRenderer->AddSprite("GasSac6", pSprite);
//		pSprite->SaveSprite("GasSac6.aclp");
//		delete pSprite;
//		pSprite = new CSprite;
//		pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("GasSac"));
//		pSprite->SetAtlasGridSize(17, 2);
//		pSprite->SetLoop(true);
//		pSprite->SetCellSize(32, 32);
//		pSprite->SetSampleRate(1);
//		pSprite->AddFrame(14, 1);
//		pSprite->SetSpriteKey("GasSac7");
//		pRenderer->AddSprite("GasSac7", pSprite);
//		pSprite->SaveSprite("GasSac7.aclp");
//		delete pSprite;
//		pSprite = new CSprite;
//		pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("GasSac"));
//		pSprite->SetAtlasGridSize(17, 2);
//		pSprite->SetLoop(true);
//		pSprite->SetCellSize(32, 32);
//		pSprite->SetSampleRate(1);
//		pSprite->AddFrame(16, 1);
//		pSprite->SetSpriteKey("GasSac8");
//		pRenderer->AddSprite("GasSac8", pSprite);
//		pSprite->SaveSprite("GasSac8.aclp");
//		delete pSprite;
//
//		pRenderer->ChangeCurrentClip("GasSac0");
//		GET_SINGLE(CFileStream)->SaveUnit(pOrb, "GasSac.unit");
//
//		delete pOrb;
//	}
//	{
//	CGameObject* pOrb = new CGameObject("GasBox");
//	CSpriteRenderer* pRenderer = pOrb->AddComponent<CSpriteRenderer>();
//	pRenderer->SetSize(32, 32);
//	pOrb->AddComponent<CGasBox>();
//
//	CSprite* pSprite = new CSprite;
//	pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("GasBox"));
//	pSprite->SetAtlasGridSize(17, 2);
//	pSprite->SetLoop(true);
//	pSprite->SetCellSize(32, 32);
//	pSprite->SetSampleRate(1);
//	pSprite->AddFrame(0, 1);
//	pSprite->SetSpriteKey("GasBox0");
//	pRenderer->AddSprite("GasBox0", pSprite);
//	pSprite->SaveSprite("GasBox0.aclp");
//	delete pSprite;
//	pSprite = new CSprite;
//	pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("GasBox"));
//	pSprite->SetAtlasGridSize(17, 2);
//	pSprite->SetLoop(true);
//	pSprite->SetCellSize(32, 32);
//	pSprite->SetSampleRate(1);
//	pSprite->AddFrame(2, 1);
//	pSprite->SetSpriteKey("GasBox1");
//	pRenderer->AddSprite("GasBox1", pSprite);
//	pSprite->SaveSprite("GasBox1.aclp");
//	delete pSprite;
//	pSprite = new CSprite;
//	pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("GasBox"));
//	pSprite->SetAtlasGridSize(17, 2);
//	pSprite->SetLoop(true);
//	pSprite->SetCellSize(32, 32);
//	pSprite->SetSampleRate(1);
//	pSprite->AddFrame(4, 1);
//	pSprite->SetSpriteKey("GasBox2");
//	pRenderer->AddSprite("GasBox2", pSprite);
//	pSprite->SaveSprite("GasBox2.aclp");
//	delete pSprite;
//
//	pSprite = new CSprite;
//	pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("GasBox"));
//	pSprite->SetAtlasGridSize(17, 2);
//	pSprite->SetLoop(true);
//	pSprite->SetCellSize(32, 32);
//	pSprite->SetSampleRate(1);
//	pSprite->AddFrame(6, 1);
//	pSprite->SetSpriteKey("GasBox3");
//	pRenderer->AddSprite("GasBox3", pSprite);
//	pSprite->SaveSprite("GasBox3.aclp");
//	delete pSprite;
//	pSprite = new CSprite;
//	pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("GasBox"));
//	pSprite->SetAtlasGridSize(17, 2);
//	pSprite->SetLoop(true);
//	pSprite->SetCellSize(32, 32);
//	pSprite->SetSampleRate(1);
//	pSprite->AddFrame(8, 1);
//	pSprite->SetSpriteKey("GasBox4");
//	pRenderer->AddSprite("GasBox4", pSprite);
//	pSprite->SaveSprite("GasBox4.aclp");
//	delete pSprite;
//	pSprite = new CSprite;
//	pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("GasBox"));
//	pSprite->SetAtlasGridSize(17, 2);
//	pSprite->SetLoop(true);
//	pSprite->SetCellSize(32, 32);
//	pSprite->SetSampleRate(1);
//	pSprite->AddFrame(10, 1);
//	pSprite->SetSpriteKey("GasBox5");
//	pRenderer->AddSprite("GasBox5", pSprite);
//	pSprite->SaveSprite("GasBox5.aclp");
//	delete pSprite;
//	pSprite = new CSprite;
//	pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("GasBox"));
//	pSprite->SetAtlasGridSize(17, 2);
//	pSprite->SetLoop(true);
//	pSprite->SetCellSize(32, 32);
//	pSprite->SetSampleRate(1);
//	pSprite->AddFrame(12, 1);
//	pSprite->SetSpriteKey("GasBox6");
//	pRenderer->AddSprite("GasBox6", pSprite);
//	pSprite->SaveSprite("GasBox6.aclp");
//	delete pSprite;
//	pSprite = new CSprite;
//	pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("GasBox"));
//	pSprite->SetAtlasGridSize(17, 2);
//	pSprite->SetLoop(true);
//	pSprite->SetCellSize(32, 32);
//	pSprite->SetSampleRate(1);
//	pSprite->AddFrame(14, 1);
//	pSprite->SetSpriteKey("GasBox7");
//	pRenderer->AddSprite("GasBox7", pSprite);
//	pSprite->SaveSprite("GasBox7.aclp");
//	delete pSprite;
//	pSprite = new CSprite;
//	pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("GasBox"));
//	pSprite->SetAtlasGridSize(17, 2);
//	pSprite->SetLoop(true);
//	pSprite->SetCellSize(32, 32);
//	pSprite->SetSampleRate(1);
//	pSprite->AddFrame(16, 1);
//	pSprite->SetSpriteKey("GasBox8");
//	pRenderer->AddSprite("GasBox8", pSprite);
//	pSprite->SaveSprite("GasBox8.aclp");
//	delete pSprite;
//
//	pRenderer->ChangeCurrentClip("GasBox0");
//	GET_SINGLE(CFileStream)->SaveUnit(pOrb, "GasBox.unit");
//
//	delete pOrb;
//	}
//#pragma endregion


#pragma region SetGameOption

	GET_SINGLE(COption)->SetCameraSpeed(1024);
	GET_SINGLE(COption)->SetCursorClipped(true);

	CGameObject* pPlayer = new CGameObject("Player");
	pSystemLayer->AddGameObject(pPlayer);
	CPlayer* pPlayerComponent = pPlayer->AddComponent<CPlayer>();


	CGameObject* pPlayer2 = new CGameObject("Player2");
	pSystemLayer->AddGameObject(pPlayer2);
	CPlayer* pPlayer2Component = pPlayer2->AddComponent<CPlayer>();

	pPlayerComponent->SetTeamColor(TC_YELLOW);
	pPlayerComponent->SetRaceType(RT_TERRAN);
	pPlayerComponent->SetPlayerName("Eunsoo");
	AddPlayer(pPlayerComponent);

	pPlayer2Component->SetTeamColor(TC_YELLOW);
	pPlayer2Component->SetRaceType(RT_TERRAN);
	pPlayer2Component->SetPlayerName("Computer");
	AddPlayer(pPlayer2Component);

	CGameObject* pFogOfWar = new CGameObject("FOW");
	pFogOfWar->AddComponent<CFOW>();
	pFogOfWarLayer->AddGameObject(pFogOfWar);

	GET_SINGLE(CResourceManager)->PlaySFX("Terran1");
	
/*
	{
		CGameObject* pMineral = new CGameObject("Mineral");
		pGroundUnitLayer->AddGameObject(pMineral);
		pMineral->GetTransform()->SetPivot(0.5f, 1.0f);
		pMineral->GetTransform()->SetPosition(512, 512);

		CResource* pResource = pMineral->AddComponent<CResource>();
		CStructure* pStructure = pMineral->AddComponent<CStructure>();
		pStructure->SetRequireGas(0);
		pStructure->SetRequireMineral(0);
		pStructure->SetSupply(0);
		pStructure->SetSize(2, 1);
		pStructure->AddBuildableTile(0, 1);
		pStructure->AddBuildableTile(1, 1);

		CEllipseRenderer* pEllipseRenderer = pMineral->AddComponent<CEllipseRenderer>();
		CCircleCollider* pCollider = pMineral->AddComponent<CCircleCollider>();

		pEllipseRenderer->SetLocalPosition(0, -15);
		pEllipseRenderer->SetColor(255, 255, 0);
		pEllipseRenderer->SetMinorAxisLength(20);
		pEllipseRenderer->SetThickness(2);
		pCollider->SetRadius(30);

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
		CGameObject* pMineral = new CGameObject("Mineral");
		pGroundUnitLayer->AddGameObject(pMineral);
		pMineral->GetTransform()->SetPivot(0.5f, 1.0f);
		pMineral->GetTransform()->SetPosition(512, 512);

		CResource* pResource = pMineral->AddComponent<CResource>();
		CStructure* pStructure = pMineral->AddComponent<CStructure>();
		pStructure->SetRequireGas(0);
		pStructure->SetRequireMineral(0);
		pStructure->SetSupply(0);
		pStructure->SetSize(2, 1);
		pStructure->AddBuildableTile(0, 1);
		pStructure->AddBuildableTile(1, 1);

		CEllipseRenderer* pEllipseRenderer = pMineral->AddComponent<CEllipseRenderer>();
		CCircleCollider* pCollider = pMineral->AddComponent<CCircleCollider>();

		pEllipseRenderer->SetLocalPosition(0, -15);
		pEllipseRenderer->SetColor(255, 255, 0);
		pEllipseRenderer->SetMinorAxisLength(20);
		pEllipseRenderer->SetThickness(2);
		pCollider->SetRadius(30);

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
		CGameObject* pMineral = new CGameObject("Mineral");
		pGroundUnitLayer->AddGameObject(pMineral);
		pMineral->GetTransform()->SetPivot(0.5f, 1.0f);
		pMineral->GetTransform()->SetPosition(512, 512);

		CResource* pResource = pMineral->AddComponent<CResource>();
		CStructure* pStructure = pMineral->AddComponent<CStructure>();
		pStructure->SetRequireGas(0);
		pStructure->SetRequireMineral(0);
		pStructure->SetSupply(0);
		pStructure->SetSize(2, 1);
		pStructure->AddBuildableTile(0, 1);
		pStructure->AddBuildableTile(1, 1);

		CEllipseRenderer* pEllipseRenderer = pMineral->AddComponent<CEllipseRenderer>();
		CCircleCollider* pCollider = pMineral->AddComponent<CCircleCollider>();

		pEllipseRenderer->SetLocalPosition(0, -15);
		pEllipseRenderer->SetColor(255, 255, 0);
		pEllipseRenderer->SetMinorAxisLength(20);
		pEllipseRenderer->SetThickness(2);
		pCollider->SetRadius(30);

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
	}
#pragma endregion*/
//
//#pragma region Create Terran Proto Type
//
//#pragma region Supply Depot
//
////SupplyDepot
//{
//int iTestPositionX = 20;
//int iTestPositionY = 13;
//	//Supply Depot
//	CGameObject* pSupplyDepot = new CGameObject("Supply Depot");
//	pSupplyDepot->SetPilot(pPlayer->GetComponent<CPlayer>());
//	pGroundUnitLayer->AddGameObject(pSupplyDepot);
//	pSupplyDepot->GetTransform()->SetPivot(0.5f, 0.5f);
//	pSupplyDepot->GetTransform()->SetPosition(iTestPositionX * 32, iTestPositionY * 32);
//
//	CEllipseRenderer* pEllipse = pSupplyDepot->AddComponent<CEllipseRenderer>();
//	CSpriteRenderer* pRenderer = pSupplyDepot->AddComponent<CSpriteRenderer>();
//	CUnitStatus* pStatus = pSupplyDepot->AddComponent<CUnitStatus>();
//	CCircleCollider* pCollider = pSupplyDepot->AddComponent<CCircleCollider>();
//	CUnitInfo* pInfo = pSupplyDepot->AddComponent<CUnitInfo>();
//	CStructure* pStructure = pSupplyDepot->AddComponent<CStructure>();
//
//
//	pInfo->SetUnitButtonTexture(GET_SINGLE(CResourceManager)->FindTexture("ControlButton_Icon_TerranSupplyDepot_Normal"));
//
//	pStatus->SetCreateTime(10);
//	pStatus->SetMaxHP(500);
//	pStatus->SetMaxMP(0);
//	pStatus->SetMaxShield(0);
//	pStatus->SetRequirement(10, 100, 0, 0);
//	pStatus->SetSightRadius(8);
//
//	pStatus->SetHPMaxCondition();
//	pStatus->SetMPMaxCondition();
//	pStatus->SetShieldMaxCondition();
//	
//	pStructure->SetSupply(8);
//	pStructure->SetBuildTime(10);
//	pStructure->SetRequireGas(0);
//	pStructure->SetRequireMineral(100);
//	pStructure->SetSize(3, 2);
//	pStructure->AddBuildableTile(0, 1);
//	pStructure->AddBuildableTile(1, 1);
//	pStructure->AddBuildableTile(2, 1);
//	pStructure->AddBuildableTile(0, 2);
//	pStructure->AddBuildableTile(1, 2);
//	pStructure->AddBuildableTile(2, 2);
//
//	pEllipse->SetMinorAxisLength(32);
//	pEllipse->SetMajorAxisScale(1.6f);
//	pEllipse->SetThickness(2);
//	pEllipse->SetLocalPosition(0, 8);
//
//	pCollider->SetRadius(32);
//	pRenderer->SetSize(96, 128);
//
//
//	CSprite* pSprite = new CSprite;
//	pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("SupplyDepot"));
//	pSprite->SetAtlasGridSize(9, 1);
//	pSprite->SetCellSize(96, 128);
//	pSprite->SetLoop(true);
//	pSprite->SetSampleRate(5);
//
//	pSprite->AddFrame(CVector2(4, 0));
//	pSprite->AddFrame(CVector2(5, 0));
//	pSprite->AddFrame(CVector2(6, 0));
//	pSprite->AddFrame(CVector2(7, 0));
//	pSprite->AddFrame(CVector2(8, 0));
//
//	pRenderer->AddSprite("Supply DepotNormal", pSprite);
//	pSprite->SaveSprite("Supply DepotNormal.aclp");
//	delete pSprite;
//
//	pSprite = new CSprite;
//	pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("SupplyDepot"));
//	pSprite->SetAtlasGridSize(9, 1);
//	pSprite->SetCellSize(96, 128);
//	pSprite->SetLoop(false);
//	pSprite->SetSampleRate(4 / pStructure->GetBuildTime());
//
//	pSprite->AddFrame(CVector2(0, 0));
//	pSprite->AddFrame(CVector2(1, 0));
//	pSprite->AddFrame(CVector2(2, 0));
//	pSprite->AddFrame(CVector2(3, 0));
//	pRenderer->AddSprite("Supply DepotBuild", pSprite);
//	pSprite->SaveSprite("Supply DepotBuild.aclp");
//	delete pSprite;
//
//	CSprite* pDeathSprite = new CSprite;
//	pDeathSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("Terran_Explosion_Large"));
//	pDeathSprite->SetAtlasGridSize(1, 10);
//	pDeathSprite->SetSampleRate(10);
//	pDeathSprite->SetLoop(false);
//	pDeathSprite->SetCellSize(200, 200);
//	pDeathSprite->AddFrame(CVector2(0, 0));
//	pDeathSprite->AddFrame(CVector2(1, 0));
//	pDeathSprite->AddFrame(CVector2(2, 0));
//	pDeathSprite->AddFrame(CVector2(3, 0));
//	pDeathSprite->AddFrame(CVector2(4, 0));
//	pDeathSprite->AddFrame(CVector2(5, 0));
//	pDeathSprite->AddFrame(CVector2(6, 0));
//	pDeathSprite->AddFrame(CVector2(7, 0));
//	pDeathSprite->AddFrame(CVector2(8, 0));
//	pDeathSprite->AddFrame(CVector2(9, 0));
//
//	pRenderer->AddSprite("Supply DepotDeath", pDeathSprite);
//	pDeathSprite->SaveSprite("Supply DepotDeath.aclp");
//	delete pDeathSprite;
//
//	GET_SINGLE(CFileStream)->SaveUnit(pSupplyDepot, "SupplyDepot.unit");
//
//}
//#pragma endregion
//
//#pragma region Refinery
//{
//	int iTestPositionX = 13;
//	int iTestPositionY = 3;
//	//Supply Depot
//	CGameObject* pBuilding = new CGameObject("Refinery");
//	pBuilding->SetPilot(pPlayer->GetComponent<CPlayer>());
//	pGroundUnitLayer->AddGameObject(pBuilding);
//	pBuilding->GetTransform()->SetPivot(0.5f, 0.5f);
//	pBuilding->GetTransform()->SetPosition(iTestPositionX * 32, iTestPositionY * 32);
//
//	CEllipseRenderer* pEllipse = pBuilding->AddComponent<CEllipseRenderer>();
//	CSpriteRenderer* pRenderer = pBuilding->AddComponent<CSpriteRenderer>();
//	CUnitStatus* pStatus = pBuilding->AddComponent<CUnitStatus>();
//	CCircleCollider* pCollider = pBuilding->AddComponent<CCircleCollider>();
//	CUnitInfo* pInfo = pBuilding->AddComponent<CUnitInfo>();
//	CStructure* pStructure = pBuilding->AddComponent<CStructure>();
//
//
//	pInfo->SetUnitButtonTexture(GET_SINGLE(CResourceManager)->FindTexture("ControlButton_Icon_TerranRefinery_Normal"));
//
//	pStatus->SetCreateTime(10);
//	pStatus->SetMaxHP(750);
//	pStatus->SetMaxMP(0);
//	pStatus->SetMaxShield(0);
//	pStatus->SetRequirement(10, 75, 0, 0);
//	pStatus->SetSightRadius(8);
//
//	pStatus->SetHPMaxCondition();
//	pStatus->SetMPMaxCondition();
//	pStatus->SetShieldMaxCondition();
//
//	pStructure->SetVespeneGeyser(true);
//	pStructure->SetSupply(0);
//	pStructure->SetBuildTime(10);
//	pStructure->SetRequireGas(0);
//	pStructure->SetRequireMineral(75);
//	pStructure->SetSize(4, 3);
//	pStructure->AddBuildableTile(1, 1);
//	pStructure->AddBuildableTile(2, 1);
//	pStructure->AddBuildableTile(3, 1);
//	pStructure->AddBuildableTile(4, 1);
//	pStructure->AddBuildableTile(1, 2);
//	pStructure->AddBuildableTile(2, 2);
//	pStructure->AddBuildableTile(3, 2);
//	pStructure->AddBuildableTile(4, 2);
//	pStructure->AddBuildableTile(1, 3);
//	pStructure->AddBuildableTile(2, 3);
//	pStructure->AddBuildableTile(3, 3);
//	pStructure->AddBuildableTile(4, 3);
//
//	pEllipse->SetMinorAxisLength(48);
//	pEllipse->SetMajorAxisScale(1.6f);
//	pEllipse->SetThickness(2);
//	pEllipse->SetLocalPosition(0, 8);
//
//
//	pCollider->SetRadius(48);
//	pRenderer->SetSize(192, 192);
//
//
//	CSprite* pSprite = new CSprite;
//	pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("Refinery"));
//	pSprite->SetAtlasGridSize(5, 1);
//	pSprite->SetCellSize(192, 192);
//	pSprite->SetLoop(true);
//	pSprite->SetSampleRate(1);
//	pSprite->AddFrame(CVector2(0, 0));
//	pRenderer->AddSprite("RefineryNormal", pSprite);
//	pSprite->SaveSprite("RefineryNormal.aclp");
//	delete pSprite;
//
//
//	pSprite = new CSprite;
//	pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("Refinery"));
//	pSprite->SetAtlasGridSize(5, 1);
//	pSprite->SetCellSize(192, 192);
//	pSprite->SetLoop(true);
//	pSprite->SetSampleRate(4 / pStructure->GetBuildTime());
//
//	pSprite->AddFrame(CVector2(1, 0));
//	pSprite->AddFrame(CVector2(2, 0));
//	pSprite->AddFrame(CVector2(3, 0));
//	pSprite->AddFrame(CVector2(4, 0));
//	pRenderer->AddSprite("RefineryBuild", pSprite);
//	pSprite->SaveSprite("RefineryBuild.aclp");
//	delete pSprite;
//
//	CSprite* pDeathSprite = new CSprite;
//	pDeathSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("Terran_Explosion_Large"));
//	pDeathSprite->SetAtlasGridSize(1, 10);
//	pDeathSprite->SetSampleRate(10);
//	pDeathSprite->SetLoop(false);
//	pDeathSprite->SetCellSize(200, 200);
//	pDeathSprite->AddFrame(CVector2(0, 0));
//	pDeathSprite->AddFrame(CVector2(1, 0));
//	pDeathSprite->AddFrame(CVector2(2, 0));
//	pDeathSprite->AddFrame(CVector2(3, 0));
//	pDeathSprite->AddFrame(CVector2(4, 0));
//	pDeathSprite->AddFrame(CVector2(5, 0));
//	pDeathSprite->AddFrame(CVector2(6, 0));
//	pDeathSprite->AddFrame(CVector2(7, 0));
//	pDeathSprite->AddFrame(CVector2(8, 0));
//	pDeathSprite->AddFrame(CVector2(9, 0));
//
//	pRenderer->AddSprite("RefineryDeath", pDeathSprite);
//	pDeathSprite->SaveSprite("RefineryDeath.aclp");
//	delete pDeathSprite;
//
//	GET_SINGLE(CFileStream)->SaveUnit(pBuilding, "Refinery.unit");
//
//}
//
//#pragma endregion
//
//#pragma region Barracks
//{
//	int iTestPositionX = 20;
//	int iTestPositionY = 20;
//	//Supply Depot
//	CGameObject* pUnit = new CGameObject("Barracks");
//	pUnit->SetPilot(pPlayer->GetComponent<CPlayer>());
//	pGroundUnitLayer->AddGameObject(pUnit);
//	pUnit->GetTransform()->SetPivot(0.5f, 0.5f);
//	pUnit->GetTransform()->SetPosition(iTestPositionX * 32, iTestPositionY * 32);
//
//	CEllipseRenderer* pEllipse = pUnit->AddComponent<CEllipseRenderer>();
//	CSpriteRenderer* pRenderer = pUnit->AddComponent<CSpriteRenderer>();
//	CUnitStatus* pStatus = pUnit->AddComponent<CUnitStatus>();
//	CCircleCollider* pCollider = pUnit->AddComponent<CCircleCollider>();
//	CUnitInfo* pInfo = pUnit->AddComponent<CUnitInfo>();
//	CStructure* pStructure = pUnit->AddComponent<CStructure>();
//	CBarracks* pBarracks = pUnit->AddComponent<CBarracks>();
//
//
//	pInfo->SetUnitButtonTexture(GET_SINGLE(CResourceManager)->FindTexture("ControlButton_Icon_TerranBarrcks_Normal"));
//
//	pStatus->SetCreateTime(10);
//	pStatus->SetMaxHP(1000);
//	pStatus->SetMaxMP(0);
//	pStatus->SetMaxShield(0);
//	pStatus->SetRequirement(10, 150, 0, 0);
//	pStatus->SetSightRadius(8);
//
//	pStatus->SetHPMaxCondition();
//	pStatus->SetMPMaxCondition();
//	pStatus->SetShieldMaxCondition();
//
//	pStructure->SetSupply(0);
//	pStructure->SetBuildTime(10);
//	pStructure->SetRequireGas(0);
//	pStructure->SetRequireMineral(150);
//	pStructure->SetSize(4, 3);
//	pStructure->AddBuildableTile(1, 1);
//	pStructure->AddBuildableTile(2, 1);
//	pStructure->AddBuildableTile(3, 1);
//	pStructure->AddBuildableTile(4, 1);
//	pStructure->AddBuildableTile(1, 2);
//	pStructure->AddBuildableTile(2, 2);
//	pStructure->AddBuildableTile(3, 2);
//	pStructure->AddBuildableTile(4, 2);
//	pStructure->AddBuildableTile(1, 3);
//	pStructure->AddBuildableTile(2, 3);
//	pStructure->AddBuildableTile(3, 3);
//	pStructure->AddBuildableTile(4, 3);
//
//	pEllipse->SetMinorAxisLength(48);
//	pEllipse->SetMajorAxisScale(1.6f);
//	pEllipse->SetThickness(2);
//	pEllipse->SetLocalPosition(0, 8);
//
//
//	pCollider->SetRadius(48);
//	pRenderer->SetSize(192, 160);
//
//
//	CSprite* pSprite = new CSprite;
//	pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("Barracks"));
//	pSprite->SetAtlasGridSize(12, 1);
//	pSprite->SetCellSize(192, 160);
//	pSprite->SetLoop(true);
//	pSprite->SetSampleRate(1);
//	pSprite->AddFrame(CVector2(4, 0));
//	pRenderer->AddSprite("BarracksNormal", pSprite);
//	pSprite->SaveSprite("BarracksNormal.aclp");
//	delete pSprite;
//
//
//	pSprite = new CSprite;
//	pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("Barracks"));
//	pSprite->SetAtlasGridSize(12, 1);
//	pSprite->SetCellSize(192, 160);
//	pSprite->SetLoop(true);
//	pSprite->SetSampleRate(5);
//
//	pSprite->AddFrame(CVector2(4, 0));
//	pSprite->AddFrame(CVector2(10, 0));
//	pSprite->AddFrame(CVector2(11, 0));
//	pSprite->AddFrame(CVector2(4, 0));
//	pSprite->AddFrame(CVector2(4, 0));
//	pSprite->AddFrame(CVector2(4, 0));
//	pSprite->AddFrame(CVector2(4, 0));
//	pSprite->AddFrame(CVector2(10, 0));
//	pSprite->AddFrame(CVector2(11, 0));
//	pSprite->AddFrame(CVector2(4, 0));
//	pSprite->AddFrame(CVector2(4, 0));
//	pSprite->AddFrame(CVector2(10, 0));
//	pSprite->AddFrame(CVector2(11, 0));
//	pSprite->AddFrame(CVector2(4, 0));
//	pRenderer->AddSprite("BarracksWork", pSprite);
//	pSprite->SaveSprite("BarracksWork.aclp");
//	delete pSprite;
//
//	pSprite = new CSprite;
//	pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("Barracks"));
//	pSprite->SetAtlasGridSize(12, 1);
//	pSprite->SetCellSize(192, 160);
//	pSprite->SetLoop(true);
//	pSprite->SetSampleRate(4 / pStructure->GetBuildTime());
//
//	pSprite->AddFrame(CVector2(0, 0));
//	pSprite->AddFrame(CVector2(1, 0));
//	pSprite->AddFrame(CVector2(2, 0));
//	pSprite->AddFrame(CVector2(3, 0));
//	pRenderer->AddSprite("BarracksBuild", pSprite);
//	pSprite->SaveSprite("BarracksBuild.aclp");
//	delete pSprite;
//
//	CSprite* pDeathSprite = new CSprite;
//	pDeathSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("Terran_Explosion_Large"));
//	pDeathSprite->SetAtlasGridSize(1, 10);
//	pDeathSprite->SetSampleRate(10);
//	pDeathSprite->SetLoop(false);
//	pDeathSprite->SetCellSize(200, 200);
//	pDeathSprite->AddFrame(CVector2(0, 0));
//	pDeathSprite->AddFrame(CVector2(1, 0));
//	pDeathSprite->AddFrame(CVector2(2, 0));
//	pDeathSprite->AddFrame(CVector2(3, 0));
//	pDeathSprite->AddFrame(CVector2(4, 0));
//	pDeathSprite->AddFrame(CVector2(5, 0));
//	pDeathSprite->AddFrame(CVector2(6, 0));
//	pDeathSprite->AddFrame(CVector2(7, 0));
//	pDeathSprite->AddFrame(CVector2(8, 0));
//	pDeathSprite->AddFrame(CVector2(9, 0));
//
//	pRenderer->AddSprite("BarracksDeath", pDeathSprite);
//	pDeathSprite->SaveSprite("BarracksDeath.aclp");
//	delete pDeathSprite;
//
//	GET_SINGLE(CFileStream)->SaveUnit(pUnit, "Barracks.unit");
//
//}
//
//#pragma endregion
//
//#pragma region Engineering Bay
//{
//	int iTestPositionX = 25;
//	int iTestPositionY = 10;
//	//Supply Depot
//	CGameObject* pUnit = new CGameObject("Engineering Bay");
//	pUnit->SetPilot(pPlayer->GetComponent<CPlayer>());
//	pGroundUnitLayer->AddGameObject(pUnit);
//	pUnit->GetTransform()->SetPivot(0.5f, 0.5f);
//	pUnit->GetTransform()->SetPosition(iTestPositionX * 32, iTestPositionY * 32);
//
//	CEllipseRenderer* pEllipse = pUnit->AddComponent<CEllipseRenderer>();
//	CSpriteRenderer* pRenderer = pUnit->AddComponent<CSpriteRenderer>();
//	CUnitStatus* pStatus = pUnit->AddComponent<CUnitStatus>();
//	CCircleCollider* pCollider = pUnit->AddComponent<CCircleCollider>();
//	CUnitInfo* pInfo = pUnit->AddComponent<CUnitInfo>();
//	CStructure* pStructure = pUnit->AddComponent<CStructure>();
//	CEngineeringBay* pEngineeringBay = pUnit->AddComponent<CEngineeringBay>();
//
//
//	pInfo->SetUnitButtonTexture(GET_SINGLE(CResourceManager)->FindTexture("ControlButton_Icon_TerranEngineeringBay_Normal"));
//
//	pStatus->SetCreateTime(10);
//	pStatus->SetMaxHP(850);
//	pStatus->SetMaxMP(0);
//	pStatus->SetMaxShield(0);
//	pStatus->SetRequirement(10, 125, 0, 0);
//	pStatus->SetSightRadius(8);
//
//	pStatus->SetHPMaxCondition();
//	pStatus->SetMPMaxCondition();
//	pStatus->SetShieldMaxCondition();
//
//	pStructure->SetSupply(0);
//	pStructure->SetBuildTime(10);
//	pStructure->SetRequireGas(0);
//	pStructure->SetRequireMineral(125);
//	pStructure->SetSize(4, 3);
//	pStructure->AddBuildableTile(1, 1);
//	pStructure->AddBuildableTile(2, 1);
//	pStructure->AddBuildableTile(3, 1);
//	pStructure->AddBuildableTile(4, 1);
//	pStructure->AddBuildableTile(1, 2);
//	pStructure->AddBuildableTile(2, 2);
//	pStructure->AddBuildableTile(3, 2);
//	pStructure->AddBuildableTile(4, 2);
//	pStructure->AddBuildableTile(1, 3);
//	pStructure->AddBuildableTile(2, 3);
//	pStructure->AddBuildableTile(3, 3);
//	pStructure->AddBuildableTile(4, 3);
//
//	pEllipse->SetMinorAxisLength(48);
//	pEllipse->SetMajorAxisScale(1.6f);
//	pEllipse->SetThickness(2);
//	pEllipse->SetLocalPosition(0, 8);
//
//
//	pCollider->SetRadius(48);
//	pRenderer->SetSize(192, 160);
//
//
//	CSprite* pSprite = new CSprite;
//	pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("EngineeringBay"));
//	pSprite->SetAtlasGridSize(15, 1);
//	pSprite->SetCellSize(192, 160);
//	pSprite->SetLoop(true);
//	pSprite->SetSampleRate(1);
//	pSprite->AddFrame(CVector2(4, 0));
//	pRenderer->AddSprite("Engineering BayNormal", pSprite);
//	pSprite->SaveSprite("Engineering BayNormal.aclp");
//	delete pSprite;
//
//	
//	pSprite = new CSprite;
//	pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("EngineeringBay"));
//	pSprite->SetAtlasGridSize(15, 1);
//	pSprite->SetCellSize(192, 160);
//	pSprite->SetLoop(true);
//	pSprite->SetSampleRate(5);
//
//	pSprite->AddFrame(5, 1);
//	pSprite->AddFrame(6, 1);
//	pSprite->AddFrame(7, 1);
//	pSprite->AddFrame(8, 1);
//	pSprite->AddFrame(9, 1);
//	pSprite->AddFrame(10, 1);
//	pRenderer->AddSprite("Engineering BayWork", pSprite);
//	pSprite->SaveSprite("Engineering BayWork.aclp");
//	delete pSprite;
//
//
//	pSprite = new CSprite;
//	pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("EngineeringBay"));
//	pSprite->SetAtlasGridSize(15, 1);
//	pSprite->SetCellSize(192, 160);
//	pSprite->SetLoop(true);
//	pSprite->SetSampleRate(5);
//
//	pSprite->AddFrame(11, 1);
//	pSprite->AddFrame(12, 1);
//	pSprite->AddFrame(13, 1);
//	pSprite->AddFrame(14, 1);
//	pRenderer->AddSprite("Engineering BayLiftUp", pSprite);
//	pSprite->SaveSprite("Engineering BayLiftUp.aclp");
//	delete pSprite;
//
//	
//	pSprite = new CSprite;
//	pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("EngineeringBay"));
//	pSprite->SetAtlasGridSize(15, 1);
//	pSprite->SetCellSize(192, 160);
//	pSprite->SetLoop(true);
//	pSprite->SetSampleRate(5);
//
//	pSprite->AddFrame(14, 1);
//	pRenderer->AddSprite("Engineering BayAir", pSprite);
//	pSprite->SaveSprite("Engineering BayAir.aclp");
//	delete pSprite;
//
//
//	pSprite = new CSprite;
//	pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("EngineeringBay"));
//	pSprite->SetAtlasGridSize(15, 1);
//	pSprite->SetCellSize(192, 160);
//	pSprite->SetLoop(true);
//	pSprite->SetSampleRate(5);
//
//	pSprite->AddFrame(14, 1);
//	pSprite->AddFrame(13, 1);
//	pSprite->AddFrame(12, 1);
//	pSprite->AddFrame(11, 1);
//	pRenderer->AddSprite("Engineering BayLiftDown", pSprite);
//	pSprite->SaveSprite("Engineering BayLiftDown.aclp");
//	delete pSprite;
//
//	pSprite = new CSprite;
//	pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("EngineeringBay"));
//	pSprite->SetAtlasGridSize(15, 1);
//	pSprite->SetCellSize(192, 160);
//	pSprite->SetLoop(true);
//	pSprite->SetSampleRate(4 / pStructure->GetBuildTime());
//
//	pSprite->AddFrame(CVector2(0, 0));
//	pSprite->AddFrame(CVector2(1, 0));
//	pSprite->AddFrame(CVector2(2, 0));
//	pSprite->AddFrame(CVector2(3, 0));
//	pRenderer->AddSprite("Engineering BayBuild", pSprite);
//	pSprite->SaveSprite("Engineering BayBuild.aclp");
//	delete pSprite;
//
//	CSprite* pDeathSprite = new CSprite;
//	pDeathSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("Terran_Explosion_Large"));
//	pDeathSprite->SetAtlasGridSize(1, 10);
//	pDeathSprite->SetSampleRate(10);
//	pDeathSprite->SetLoop(false);
//	pDeathSprite->SetCellSize(200, 200);
//	pDeathSprite->AddFrame(CVector2(0, 0));
//	pDeathSprite->AddFrame(CVector2(1, 0));
//	pDeathSprite->AddFrame(CVector2(2, 0));
//	pDeathSprite->AddFrame(CVector2(3, 0));
//	pDeathSprite->AddFrame(CVector2(4, 0));
//	pDeathSprite->AddFrame(CVector2(5, 0));
//	pDeathSprite->AddFrame(CVector2(6, 0));
//	pDeathSprite->AddFrame(CVector2(7, 0));
//	pDeathSprite->AddFrame(CVector2(8, 0));
//	pDeathSprite->AddFrame(CVector2(9, 0));
//
//	pRenderer->AddSprite("Engineering BayDeath", pDeathSprite);
//	pDeathSprite->SaveSprite("Engineering BayDeath.aclp");
//	delete pDeathSprite;
//
//	GET_SINGLE(CFileStream)->SaveUnit(pUnit, "EngineeringBay.unit");
//}
//
//#pragma endregion
//
//#pragma region Missile Turret
//{
//	int iTestPositionX = 25;
//	int iTestPositionY = 25;
//	//Supply Depot
//	CGameObject* pUnit = new CGameObject("Missile Turret");
//	pUnit->SetPilot(pPlayer->GetComponent<CPlayer>());
//	pGroundUnitLayer->AddGameObject(pUnit);
//	pUnit->GetTransform()->SetPivot(0.5f, 0.5f);
//	pUnit->GetTransform()->SetPosition(iTestPositionX * 32, iTestPositionY * 32);
//
//	CEllipseRenderer* pEllipse = pUnit->AddComponent<CEllipseRenderer>();
//	CSpriteRenderer* pRenderer = pUnit->AddComponent<CSpriteRenderer>();
//
//	CUnitStatus* pStatus = pUnit->AddComponent<CUnitStatus>();
//	CCircleCollider* pCollider = pUnit->AddComponent<CCircleCollider>();
//	CUnitInfo* pInfo = pUnit->AddComponent<CUnitInfo>();
//	CStructure* pStructure = pUnit->AddComponent<CStructure>();
//
//	pInfo->SetUnitButtonTexture(GET_SINGLE(CResourceManager)->FindTexture("ControlButton_Icon_TerranMissileTurret_Normal"));
//
//	pStatus->SetCreateTime(10);
//	pStatus->SetMaxHP(850);
//	pStatus->SetMaxMP(0);
//	pStatus->SetMaxShield(0);
//	pStatus->SetRequirement(10, 75, 0, 0);
//	pStatus->SetSightRadius(8);
//
//	pStatus->SetHPMaxCondition();
//	pStatus->SetMPMaxCondition();
//	pStatus->SetShieldMaxCondition();
//
//	pStructure->SetSupply(0);
//	pStructure->SetBuildTime(10);
//	pStructure->SetRequireGas(0);
//	pStructure->SetRequireMineral(75);
//	pStructure->SetSize(2, 2);
//	pStructure->AddBuildableTile(1, 1);
//	pStructure->AddBuildableTile(2, 1);
//	pStructure->AddBuildableTile(1, 2);
//	pStructure->AddBuildableTile(2, 2);
//
//	pEllipse->SetMinorAxisLength(20);
//	pEllipse->SetMajorAxisScale(1.6f);
//	pEllipse->SetThickness(2);
//	pEllipse->SetLocalPosition(0, 8);
//
//
//	pCollider->SetRadius(20);
//
//	pRenderer->SetSize(128, 128);
//
//
//	CSprite* pSprite = new CSprite;
//	pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("MissileTurret"));
//	pSprite->SetAtlasGridSize(17, 2);
//	pSprite->SetCellSize(128, 128);
//	pSprite->SetLoop(true);
//	pSprite->SetSampleRate(22.5f);
//	pSprite->AddFrame(CVector2(0, 0));
//	pSprite->AddFrame(CVector2(1, 0));
//	pSprite->AddFrame(CVector2(2, 0));
//	pSprite->AddFrame(CVector2(3, 0));
//	pSprite->AddFrame(CVector2(4, 0));
//	pSprite->AddFrame(CVector2(5, 0));
//	pSprite->AddFrame(CVector2(6, 0));
//	pSprite->AddFrame(CVector2(7, 0));
//	pSprite->AddFrame(CVector2(8, 0));
//	pSprite->AddFrame(CVector2(9, 0));
//	pSprite->AddFrame(CVector2(10, 0));
//	pSprite->AddFrame(CVector2(11, 0));
//	pSprite->AddFrame(CVector2(12, 0));
//	pSprite->AddFrame(CVector2(13, 0));
//	pSprite->AddFrame(CVector2(14, 0));
//	pSprite->AddFrame(CVector2(15, 0));
//	pSprite->AddFrame(CVector2(16, 0));
//	pSprite->AddFrame(CVector2(1, 1));
//	pSprite->AddFrame(CVector2(2, 1));
//	pSprite->AddFrame(CVector2(3, 1));
//	pSprite->AddFrame(CVector2(4, 1));
//	pSprite->AddFrame(CVector2(5, 1));
//	pSprite->AddFrame(CVector2(6, 1));
//	pSprite->AddFrame(CVector2(7, 1));
//	pSprite->AddFrame(CVector2(8, 1));
//	pSprite->AddFrame(CVector2(9, 1));
//	pSprite->AddFrame(CVector2(11, 1));
//	pSprite->AddFrame(CVector2(12, 1));
//	pSprite->AddFrame(CVector2(13, 1));
//	pSprite->AddFrame(CVector2(14, 1));
//	pRenderer->AddSprite("Missile TurretNormal", pSprite);
//	pSprite->SaveSprite("Missile TurretNormal.aclp");
//	delete pSprite;
//
//	pSprite = new CSprite;
//	pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("MissileTurretBuild"));
//	pSprite->SetAtlasGridSize(4, 1);
//	pSprite->SetCellSize(128, 128);
//	pSprite->SetLoop(true);
//	pSprite->SetSampleRate(4 / pStructure->GetBuildTime());
//
//	pSprite->AddFrame(CVector2(0, 0));
//	pSprite->AddFrame(CVector2(1, 0));
//	pSprite->AddFrame(CVector2(2, 0));
//	pSprite->AddFrame(CVector2(3, 0));
//
//	pRenderer->AddSprite("Missile TurretBuild", pSprite);
//	pSprite->SaveSprite("Missile TurretBuild.aclp");
//	delete pSprite;
//
//	CSprite* pDeathSprite = new CSprite;
//	pDeathSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("Terran_Explosion_Small"));
//	pDeathSprite->SetAtlasGridSize(1, 10);
//	pDeathSprite->SetSampleRate(10);
//	pDeathSprite->SetLoop(false);
//	pDeathSprite->SetCellSize(128, 128);
//	pDeathSprite->AddFrame(CVector2(0, 0));
//	pDeathSprite->AddFrame(CVector2(1, 0));
//	pDeathSprite->AddFrame(CVector2(2, 0));
//	pDeathSprite->AddFrame(CVector2(3, 0));
//	pDeathSprite->AddFrame(CVector2(4, 0));
//	pDeathSprite->AddFrame(CVector2(5, 0));
//	pDeathSprite->AddFrame(CVector2(6, 0));
//	pDeathSprite->AddFrame(CVector2(7, 0));
//	pDeathSprite->AddFrame(CVector2(8, 0));
//	pDeathSprite->AddFrame(CVector2(9, 0));
//
//	pRenderer->AddSprite("Missile TurretDeath", pDeathSprite);
//	pDeathSprite->SaveSprite("Missile TurretDeath.aclp");
//	delete pDeathSprite;
//
//	GET_SINGLE(CFileStream)->SaveUnit(pUnit, "MissileTurret.unit");
//}
//
//#pragma endregion
//
//#pragma region Academy
//
//{
//	int iTestPositionX = 28;
//	int iTestPositionY = 22;
//	//Supply Depot
//	CGameObject* pUnit = new CGameObject("Academy");
//	pUnit->SetPilot(pPlayer->GetComponent<CPlayer>());
//	pGroundUnitLayer->AddGameObject(pUnit);
//	pUnit->GetTransform()->SetPivot(0.5f, 0.5f);
//	pUnit->GetTransform()->SetPosition(iTestPositionX * 32, iTestPositionY * 32);
//
//	CEllipseRenderer* pEllipse = pUnit->AddComponent<CEllipseRenderer>();
//	CSpriteRenderer* pRenderer = pUnit->AddComponent<CSpriteRenderer>();
//
//	CUnitStatus* pStatus = pUnit->AddComponent<CUnitStatus>();
//	CCircleCollider* pCollider = pUnit->AddComponent<CCircleCollider>();
//	CUnitInfo* pInfo = pUnit->AddComponent<CUnitInfo>();
//	CStructure* pStructure = pUnit->AddComponent<CStructure>();
//	CAcademy* pAcademy = pUnit->AddComponent<CAcademy>();
//
//	pInfo->SetUnitButtonTexture(GET_SINGLE(CResourceManager)->FindTexture("ControlButton_Icon_TerranAcademy_Normal"));
//
//	pStatus->SetCreateTime(10);
//	pStatus->SetMaxHP(600);
//	pStatus->SetMaxMP(0);
//	pStatus->SetMaxShield(0);
//	pStatus->SetRequirement(10, 150, 0, 0);
//	pStatus->SetSightRadius(8);
//
//	pStatus->SetHPMaxCondition();
//	pStatus->SetMPMaxCondition();
//	pStatus->SetShieldMaxCondition();
//
//	pStructure->SetSupply(0);
//	pStructure->SetBuildTime(10);
//	pStructure->SetRequireGas(0);
//	pStructure->SetRequireMineral(150);
//	pStructure->SetSize(3, 2);
//	pStructure->AddBuildableTile(1, 1);
//	pStructure->AddBuildableTile(2, 1);
//	pStructure->AddBuildableTile(3, 1);
//	pStructure->AddBuildableTile(1, 2);
//	pStructure->AddBuildableTile(2, 2);
//	pStructure->AddBuildableTile(3, 2);
//
//	pEllipse->SetMinorAxisLength(32);
//	pEllipse->SetMajorAxisScale(1.6f);
//	pEllipse->SetThickness(2);
//	pEllipse->SetLocalPosition(0, 8);
//
//
//	pCollider->SetRadius(32);
//
//	pRenderer->SetSize(96, 128);
//
//
//	CSprite* pSprite = new CSprite;
//	pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("Academy"));
//	pSprite->SetAtlasGridSize(6, 1);
//	pSprite->SetCellSize(96, 128);
//	pSprite->SetLoop(true);
//	pSprite->SetSampleRate(1);
//	pSprite->AddFrame(CVector2(4, 0));
//	pRenderer->AddSprite("AcademyNormal", pSprite);
//	pSprite->SaveSprite("AcademyNormal.aclp");
//	delete pSprite;
//
//	pSprite = new CSprite;
//	pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("Academy"));
//	pSprite->SetAtlasGridSize(6, 1);
//	pSprite->SetCellSize(96, 128);
//	pSprite->SetLoop(true);
//	pSprite->SetSampleRate(4 / pStructure->GetBuildTime());
//
//	pSprite->AddFrame(CVector2(0, 0));
//	pSprite->AddFrame(CVector2(1, 0));
//	pSprite->AddFrame(CVector2(2, 0));
//	pSprite->AddFrame(CVector2(3, 0));
//
//	pRenderer->AddSprite("AcademyBuild", pSprite);
//	pSprite->SaveSprite("AcademyBuild.aclp");
//	delete pSprite;
//
//
//	pSprite = new CSprite;
//	pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("Academy"));
//	pSprite->SetAtlasGridSize(6, 1);
//	pSprite->SetCellSize(96, 128);
//	pSprite->SetLoop(true);
//	pSprite->SetSampleRate(5);
//
//	pSprite->AddFrame(CVector2(4, 0));
//	pSprite->AddFrame(CVector2(5, 0));
//	pSprite->AddFrame(CVector2(4, 0));
//	pSprite->AddFrame(CVector2(4, 0));
//	pSprite->AddFrame(CVector2(4, 0));
//	pSprite->AddFrame(CVector2(5, 0));
//	pSprite->AddFrame(CVector2(5, 0));
//	pSprite->AddFrame(CVector2(4, 0));
//
//	pRenderer->AddSprite("AcademyWork", pSprite);
//	pSprite->SaveSprite("AcademyWork.aclp");
//	delete pSprite;
//
//	CSprite* pDeathSprite = new CSprite;
//	pDeathSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("Terran_Explosion_Small"));
//	pDeathSprite->SetAtlasGridSize(1, 10);
//	pDeathSprite->SetSampleRate(10);
//	pDeathSprite->SetLoop(false);
//	pDeathSprite->SetCellSize(128, 128);
//	pDeathSprite->AddFrame(CVector2(0, 0));
//	pDeathSprite->AddFrame(CVector2(1, 0));
//	pDeathSprite->AddFrame(CVector2(2, 0));
//	pDeathSprite->AddFrame(CVector2(3, 0));
//	pDeathSprite->AddFrame(CVector2(4, 0));
//	pDeathSprite->AddFrame(CVector2(5, 0));
//	pDeathSprite->AddFrame(CVector2(6, 0));
//	pDeathSprite->AddFrame(CVector2(7, 0));
//	pDeathSprite->AddFrame(CVector2(8, 0));
//	pDeathSprite->AddFrame(CVector2(9, 0));
//
//	pRenderer->AddSprite("AcademyDeath", pDeathSprite);
//	pDeathSprite->SaveSprite("AcademyDeath.aclp");
//	delete pDeathSprite;
//
//	GET_SINGLE(CFileStream)->SaveUnit(pUnit, "Academy.unit");
//}
//
//#pragma endregion
//
//#pragma region Bunker
//{
//	int iTestPositionX = 28;
//	int iTestPositionY = 15;
//	//Supply Depot
//	CGameObject* pUnit = new CGameObject("Bunker");
//	pUnit->SetPilot(pPlayer->GetComponent<CPlayer>());
//	pGroundUnitLayer->AddGameObject(pUnit);
//	pUnit->GetTransform()->SetPivot(0.5f, 0.5f);
//	pUnit->GetTransform()->SetPosition(iTestPositionX * 32, iTestPositionY * 32);
//
//	CEllipseRenderer* pEllipse = pUnit->AddComponent<CEllipseRenderer>();
//	CSpriteRenderer* pRenderer = pUnit->AddComponent<CSpriteRenderer>();
//
//	CUnitStatus* pStatus = pUnit->AddComponent<CUnitStatus>();
//	CCircleCollider* pCollider = pUnit->AddComponent<CCircleCollider>();
//	CUnitInfo* pInfo = pUnit->AddComponent<CUnitInfo>();
//	CStructure* pStructure = pUnit->AddComponent<CStructure>();
//
//	pInfo->SetUnitButtonTexture(GET_SINGLE(CResourceManager)->FindTexture("ControlButton_Icon_TerranBunker_Normal"));
//
//	pStatus->SetCreateTime(10);
//	pStatus->SetMaxHP(350);
//	pStatus->SetMaxMP(0);
//	pStatus->SetMaxShield(0);
//	pStatus->SetRequirement(10, 100, 0, 0);
//	pStatus->SetSightRadius(8);
//
//	pStatus->SetHPMaxCondition();
//	pStatus->SetMPMaxCondition();
//	pStatus->SetShieldMaxCondition();
//
//	pStructure->SetSupply(0);
//	pStructure->SetBuildTime(10);
//	pStructure->SetRequireGas(0);
//	pStructure->SetRequireMineral(100);
//	pStructure->SetSize(3, 2);
//	pStructure->AddBuildableTile(1, 1);
//	pStructure->AddBuildableTile(2, 1);
//	pStructure->AddBuildableTile(3, 1);
//	pStructure->AddBuildableTile(1, 2);
//	pStructure->AddBuildableTile(2, 2);
//	pStructure->AddBuildableTile(3, 2);
//
//	pEllipse->SetMinorAxisLength(32);
//	pEllipse->SetMajorAxisScale(1.6f);
//	pEllipse->SetThickness(2);
//	pEllipse->SetLocalPosition(0, 8);
//
//
//	pCollider->SetRadius(32);
//
//	pRenderer->SetSize(96, 128);
//
//
//	CSprite* pSprite = new CSprite;
//	pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("Bunker"));
//	pSprite->SetAtlasGridSize(5, 1);
//	pSprite->SetCellSize(96, 128);
//	pSprite->SetLoop(true);
//	pSprite->SetSampleRate(1);
//	pSprite->AddFrame(CVector2(4, 0));
//	pRenderer->AddSprite("BunkerNormal", pSprite);
//	pSprite->SaveSprite("BunkerNormal.aclp");
//	delete pSprite;
//
//	pSprite = new CSprite;
//	pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("Bunker"));
//	pSprite->SetAtlasGridSize(5, 1);
//	pSprite->SetCellSize(96, 128);
//	pSprite->SetLoop(true);
//	pSprite->SetSampleRate(4 / pStructure->GetBuildTime());
//
//	pSprite->AddFrame(CVector2(0, 0));
//	pSprite->AddFrame(CVector2(1, 0));
//	pSprite->AddFrame(CVector2(2, 0));
//	pSprite->AddFrame(CVector2(3, 0));
//
//	pRenderer->AddSprite("BunkerBuild", pSprite);
//	pSprite->SaveSprite("BunkerBuild.aclp");
//	delete pSprite;
//
//	CSprite* pDeathSprite = new CSprite;
//	pDeathSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("Terran_Explosion_Small"));
//	pDeathSprite->SetAtlasGridSize(1, 10);
//	pDeathSprite->SetSampleRate(10);
//	pDeathSprite->SetLoop(false);
//	pDeathSprite->SetCellSize(128, 128);
//	pDeathSprite->AddFrame(CVector2(0, 0));
//	pDeathSprite->AddFrame(CVector2(1, 0));
//	pDeathSprite->AddFrame(CVector2(2, 0));
//	pDeathSprite->AddFrame(CVector2(3, 0));
//	pDeathSprite->AddFrame(CVector2(4, 0));
//	pDeathSprite->AddFrame(CVector2(5, 0));
//	pDeathSprite->AddFrame(CVector2(6, 0));
//	pDeathSprite->AddFrame(CVector2(7, 0));
//	pDeathSprite->AddFrame(CVector2(8, 0));
//	pDeathSprite->AddFrame(CVector2(9, 0));
//
//	pRenderer->AddSprite("BunkerDeath", pDeathSprite);
//	pDeathSprite->SaveSprite("BunkerDeath.aclp");
//	delete pDeathSprite;
//
//	GET_SINGLE(CFileStream)->SaveUnit(pUnit, "Bunker.unit");
//}
//
//#pragma endregion
//
//#pragma region Factory
//{
//	int iTestPositionX = 29;
//	int iTestPositionY = 10;
//	//Supply Depot
//	CGameObject* pUnit = new CGameObject("Factory");
//	pUnit->SetPilot(pPlayer->GetComponent<CPlayer>());
//	pGroundUnitLayer->AddGameObject(pUnit);
//	pUnit->GetTransform()->SetPivot(0.5f, 0.5f);
//	pUnit->GetTransform()->SetPosition(iTestPositionX * 32, iTestPositionY * 32);
//
//	CEllipseRenderer* pEllipse = pUnit->AddComponent<CEllipseRenderer>();
//	CSpriteRenderer* pRenderer = pUnit->AddComponent<CSpriteRenderer>();
//	CUnitStatus* pStatus = pUnit->AddComponent<CUnitStatus>();
//	CCircleCollider* pCollider = pUnit->AddComponent<CCircleCollider>();
//	CUnitInfo* pInfo = pUnit->AddComponent<CUnitInfo>();
//	CStructure* pStructure = pUnit->AddComponent<CStructure>();
//	CFactory* pFactory = pUnit->AddComponent<CFactory>();
//
//
//	pInfo->SetUnitButtonTexture(GET_SINGLE(CResourceManager)->FindTexture("ControlButton_Icon_TerranFactory_Normal"));
//
//	pStatus->SetCreateTime(10);
//	pStatus->SetMaxHP(1250);
//	pStatus->SetMaxMP(0);
//	pStatus->SetMaxShield(0);
//	pStatus->SetRequirement(10, 200, 100, 0);
//	pStatus->SetSightRadius(8);
//
//	pStatus->SetHPMaxCondition();
//	pStatus->SetMPMaxCondition();
//	pStatus->SetShieldMaxCondition();
//
//	pStructure->SetSupply(0);
//	pStructure->SetBuildTime(10);
//	pStructure->SetRequireGas(100);
//	pStructure->SetRequireMineral(200);
//	pStructure->SetSize(4, 3);
//	pStructure->AddBuildableTile(1, 1);
//	pStructure->AddBuildableTile(2, 1);
//	pStructure->AddBuildableTile(3, 1);
//	pStructure->AddBuildableTile(4, 1);
//	pStructure->AddBuildableTile(1, 2);
//	pStructure->AddBuildableTile(2, 2);
//	pStructure->AddBuildableTile(3, 2);
//	pStructure->AddBuildableTile(4, 2);
//	pStructure->AddBuildableTile(1, 3);
//	pStructure->AddBuildableTile(2, 3);
//	pStructure->AddBuildableTile(3, 3);
//	pStructure->AddBuildableTile(4, 3);
//
//	pEllipse->SetMinorAxisLength(48);
//	pEllipse->SetMajorAxisScale(1.6f);
//	pEllipse->SetThickness(2);
//	pEllipse->SetLocalPosition(0, 8);
//
//
//	pCollider->SetRadius(48);
//	pRenderer->SetSize(128, 160);
//
//
//	CSprite* pSprite = new CSprite;
//	pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("Factory"));
//	pSprite->SetAtlasGridSize(12, 1);
//	pSprite->SetCellSize(128, 160);
//	pSprite->SetLoop(true);
//	pSprite->SetSampleRate(1);
//	pSprite->AddFrame(CVector2(4, 0));
//	pRenderer->AddSprite("FactoryNormal", pSprite);
//	pSprite->SaveSprite("FactoryNormal.aclp");
//	delete pSprite;
//
//
//	pSprite = new CSprite;
//	pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("Factory"));
//	pSprite->SetAtlasGridSize(12, 1);
//	pSprite->SetCellSize(128, 160);
//	pSprite->SetLoop(true);
//	pSprite->SetSampleRate(4);
//
//	pSprite->AddFrame(4, 1);
//	pSprite->AddFrame(5, 1);
//	pSprite->AddFrame(6, 1);
//	pSprite->AddFrame(7, 1);
//	pRenderer->AddSprite("FactoryWork", pSprite);
//	pSprite->SaveSprite("FactoryWork.aclp");
//	delete pSprite;
//
//
//	pSprite = new CSprite;
//	pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("Factory"));
//	pSprite->SetAtlasGridSize(12, 1);
//	pSprite->SetCellSize(128, 160);
//	pSprite->SetLoop(true);
//	pSprite->SetSampleRate(4);
//
//	pSprite->AddFrame(8, 1);
//	pSprite->AddFrame(9, 1);
//	pSprite->AddFrame(10, 1);
//	pSprite->AddFrame(11, 1);
//	pRenderer->AddSprite("FactoryLiftUp", pSprite);
//	pSprite->SaveSprite("FactoryLiftUp.aclp");
//	delete pSprite;
//
//
//	pSprite = new CSprite;
//	pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("Factory"));
//	pSprite->SetAtlasGridSize(12, 1);
//	pSprite->SetCellSize(128, 160);
//	pSprite->SetLoop(true);
//	pSprite->SetSampleRate(1);
//
//	pSprite->AddFrame(11, 1);
//	pRenderer->AddSprite("FactoryAir", pSprite);
//	pSprite->SaveSprite("FactoryAir.aclp");
//	delete pSprite;
//
//
//	pSprite = new CSprite;
//	pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("Factory"));
//	pSprite->SetAtlasGridSize(12, 1);
//	pSprite->SetCellSize(128, 160);
//	pSprite->SetLoop(true);
//	pSprite->SetSampleRate(4);
//
//	pSprite->AddFrame(11, 1);
//	pSprite->AddFrame(10, 1);
//	pSprite->AddFrame(9, 1);
//	pSprite->AddFrame(8, 1);
//	pRenderer->AddSprite("FactoryLiftDown", pSprite);
//	pSprite->SaveSprite("FactoryLiftDown.aclp");
//	delete pSprite;
//
//	pSprite = new CSprite;
//	pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("Factory"));
//	pSprite->SetAtlasGridSize(12, 1);
//	pSprite->SetCellSize(128, 160);
//	pSprite->SetLoop(true);
//	pSprite->SetSampleRate(4 / pStructure->GetBuildTime());
//
//	pSprite->AddFrame(CVector2(0, 0));
//	pSprite->AddFrame(CVector2(1, 0));
//	pSprite->AddFrame(CVector2(2, 0));
//	pSprite->AddFrame(CVector2(3, 0));
//	pRenderer->AddSprite("FactoryBuild", pSprite);
//	pSprite->SaveSprite("FactoryBuild.aclp");
//	delete pSprite;
//
//	CSprite* pDeathSprite = new CSprite;
//	pDeathSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("Terran_Explosion_Large"));
//	pDeathSprite->SetAtlasGridSize(1, 10);
//	pDeathSprite->SetSampleRate(10);
//	pDeathSprite->SetLoop(false);
//	pDeathSprite->SetCellSize(200, 200);
//	pDeathSprite->AddFrame(CVector2(0, 0));
//	pDeathSprite->AddFrame(CVector2(1, 0));
//	pDeathSprite->AddFrame(CVector2(2, 0));
//	pDeathSprite->AddFrame(CVector2(3, 0));
//	pDeathSprite->AddFrame(CVector2(4, 0));
//	pDeathSprite->AddFrame(CVector2(5, 0));
//	pDeathSprite->AddFrame(CVector2(6, 0));
//	pDeathSprite->AddFrame(CVector2(7, 0));
//	pDeathSprite->AddFrame(CVector2(8, 0));
//	pDeathSprite->AddFrame(CVector2(9, 0));
//
//	pRenderer->AddSprite("FactoryDeath", pDeathSprite);
//	pDeathSprite->SaveSprite("FactoryDeath.aclp");
//	delete pDeathSprite;
//
//	GET_SINGLE(CFileStream)->SaveUnit(pUnit, "Factory.unit");
//}
//
//#pragma endregion
//
//
//#pragma region Starport
//{
//	int iTestPositionX = 27;
//	int iTestPositionY = 13;
//	//Supply Depot
//	CGameObject* pUnit = new CGameObject("Starport");
//	pUnit->SetPilot(pPlayer->GetComponent<CPlayer>());
//	pGroundUnitLayer->AddGameObject(pUnit);
//	pUnit->GetTransform()->SetPivot(0.5f, 0.5f);
//	pUnit->GetTransform()->SetPosition(iTestPositionX * 32, iTestPositionY * 32);
//
//	CEllipseRenderer* pEllipse = pUnit->AddComponent<CEllipseRenderer>();
//	CSpriteRenderer* pRenderer = pUnit->AddComponent<CSpriteRenderer>();
//	CUnitStatus* pStatus = pUnit->AddComponent<CUnitStatus>();
//	CCircleCollider* pCollider = pUnit->AddComponent<CCircleCollider>();
//	CUnitInfo* pInfo = pUnit->AddComponent<CUnitInfo>();
//	CStructure* pStructure = pUnit->AddComponent<CStructure>();
//	CStarport* pStarport = pUnit->AddComponent<CStarport>();
//
//	pInfo->SetUnitButtonTexture(GET_SINGLE(CResourceManager)->FindTexture("ControlButton_Icon_TerranStarport_Normal"));
//
//	pStatus->SetCreateTime(10);
//	pStatus->SetMaxHP(1250);
//	pStatus->SetMaxMP(0);
//	pStatus->SetMaxShield(0);
//	pStatus->SetRequirement(10, 150, 100, 0);
//	pStatus->SetSightRadius(8);
//
//	pStatus->SetHPMaxCondition();
//	pStatus->SetMPMaxCondition();
//	pStatus->SetShieldMaxCondition();
//
//	pStructure->SetSupply(0);
//	pStructure->SetBuildTime(10);
//	pStructure->SetRequireGas(100);
//	pStructure->SetRequireMineral(150);
//	pStructure->SetSize(4, 3);
//
//	pStructure->AddBuildableTile(0, 1);
//	pStructure->AddBuildableTile(1, 1);
//	pStructure->AddBuildableTile(2, 1);
//	pStructure->AddBuildableTile(3, 1);
//	pStructure->AddBuildableTile(0, 2);
//	pStructure->AddBuildableTile(1, 2);
//	pStructure->AddBuildableTile(2, 2);
//	pStructure->AddBuildableTile(3, 2);
//	pStructure->AddBuildableTile(0, 3);
//	pStructure->AddBuildableTile(1, 3);
//	pStructure->AddBuildableTile(2, 3);
//	pStructure->AddBuildableTile(3, 3);
//
//	pEllipse->SetMinorAxisLength(48);
//	pEllipse->SetMajorAxisScale(1.6f);
//	pEllipse->SetThickness(2);
//	pEllipse->SetLocalPosition(0, 8);
//
//
//	pCollider->SetRadius(48);
//	pRenderer->SetSize(128, 160);
//
//
//	CSprite* pSprite = new CSprite;
//	pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("Starport"));
//	pSprite->SetAtlasGridSize(11, 1);
//	pSprite->SetCellSize(128, 160);
//	pSprite->SetLoop(true);
//	pSprite->SetSampleRate(1);
//	pSprite->AddFrame(CVector2(4, 0));
//	pRenderer->AddSprite("StarportNormal", pSprite);
//	pSprite->SaveSprite("StarportNormal.aclp");
//	delete pSprite;
//
//
//	pSprite = new CSprite;
//	pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("Starport"));
//	pSprite->SetAtlasGridSize(11, 1);
//	pSprite->SetCellSize(128, 160);
//	pSprite->SetLoop(true);
//	pSprite->SetSampleRate(4);
//
//	pSprite->AddFrame(4, 1);
//	pSprite->AddFrame(5, 1);
//	pSprite->AddFrame(6, 1);
//	pSprite->AddFrame(7, 1);
//	pRenderer->AddSprite("StarportWork", pSprite);
//	pSprite->SaveSprite("StarportWork.aclp");
//	delete pSprite;
//
//
//	pSprite = new CSprite;
//	pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("Starport"));
//	pSprite->SetAtlasGridSize(11, 1);
//	pSprite->SetCellSize(128, 160);
//	pSprite->SetLoop(true);
//	pSprite->SetSampleRate(3);
//
//	pSprite->AddFrame(8, 1);
//	pSprite->AddFrame(9, 1);
//	pSprite->AddFrame(10, 1);
//	pRenderer->AddSprite("StarportLiftUp", pSprite);
//	pSprite->SaveSprite("StarportLiftUp.aclp");
//	delete pSprite;
//
//
//	pSprite = new CSprite;
//	pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("Starport"));
//	pSprite->SetAtlasGridSize(11, 1);
//	pSprite->SetCellSize(128, 160);
//	pSprite->SetLoop(true);
//	pSprite->SetSampleRate(1);
//
//	pSprite->AddFrame(10, 1);
//	pRenderer->AddSprite("StarportAir", pSprite);
//	pSprite->SaveSprite("StarportAir.aclp");
//	delete pSprite;
//
//
//	pSprite = new CSprite;
//	pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("Starport"));
//	pSprite->SetAtlasGridSize(11, 1);
//	pSprite->SetCellSize(128, 160);
//	pSprite->SetLoop(true);
//	pSprite->SetSampleRate(3);
//
//	pSprite->AddFrame(10, 1);
//	pSprite->AddFrame(9, 1);
//	pSprite->AddFrame(8, 1);
//	pRenderer->AddSprite("StarportLiftDown", pSprite);
//	pSprite->SaveSprite("StarportLiftDown.aclp");
//	delete pSprite;
//
//	pSprite = new CSprite;
//	pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("Starport"));
//	pSprite->SetAtlasGridSize(11, 1);
//	pSprite->SetCellSize(128, 160);
//	pSprite->SetLoop(true);
//	pSprite->SetSampleRate(4 / pStructure->GetBuildTime());
//
//	pSprite->AddFrame(CVector2(0, 0));
//	pSprite->AddFrame(CVector2(1, 0));
//	pSprite->AddFrame(CVector2(2, 0));
//	pSprite->AddFrame(CVector2(3, 0));
//	pRenderer->AddSprite("StarportBuild", pSprite);
//	pSprite->SaveSprite("StarportBuild.aclp");
//	delete pSprite;
//
//	CSprite* pDeathSprite = new CSprite;
//	pDeathSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("Terran_Explosion_Large"));
//	pDeathSprite->SetAtlasGridSize(1, 10);
//	pDeathSprite->SetSampleRate(10);
//	pDeathSprite->SetLoop(false);
//	pDeathSprite->SetCellSize(200, 200);
//	pDeathSprite->AddFrame(CVector2(0, 0));
//	pDeathSprite->AddFrame(CVector2(1, 0));
//	pDeathSprite->AddFrame(CVector2(2, 0));
//	pDeathSprite->AddFrame(CVector2(3, 0));
//	pDeathSprite->AddFrame(CVector2(4, 0));
//	pDeathSprite->AddFrame(CVector2(5, 0));
//	pDeathSprite->AddFrame(CVector2(6, 0));
//	pDeathSprite->AddFrame(CVector2(7, 0));
//	pDeathSprite->AddFrame(CVector2(8, 0));
//	pDeathSprite->AddFrame(CVector2(9, 0));
//
//	pRenderer->AddSprite("StarportDeath", pDeathSprite);
//	pDeathSprite->SaveSprite("StarportDeath.aclp");
//	delete pDeathSprite;
//
//	GET_SINGLE(CFileStream)->SaveUnit(pUnit, "Starport.unit");
//}
//
//#pragma endregion
//
//
//#pragma region Science Facility
//
//{
//	int iTestPositionX = 27;
//	int iTestPositionY = 3;
//	//Supply Depot
//	CGameObject* pUnit = new CGameObject("Science Facility");
//	pUnit->SetPilot(pPlayer->GetComponent<CPlayer>());
//	pGroundUnitLayer->AddGameObject(pUnit);
//	pUnit->GetTransform()->SetPivot(0.5f, 0.5f);
//	pUnit->GetTransform()->SetPosition(iTestPositionX * 32, iTestPositionY * 32);
//
//	CEllipseRenderer* pEllipse = pUnit->AddComponent<CEllipseRenderer>();
//	CSpriteRenderer* pRenderer = pUnit->AddComponent<CSpriteRenderer>();
//	CUnitStatus* pStatus = pUnit->AddComponent<CUnitStatus>();
//	CCircleCollider* pCollider = pUnit->AddComponent<CCircleCollider>();
//	CUnitInfo* pInfo = pUnit->AddComponent<CUnitInfo>();
//	CStructure* pStructure = pUnit->AddComponent<CStructure>();
//
//
//	pInfo->SetUnitButtonTexture(GET_SINGLE(CResourceManager)->FindTexture("ControlButton_Icon_TerranScienceFacility_Normal"));
//
//	pStatus->SetCreateTime(10);
//	pStatus->SetMaxHP(850);
//	pStatus->SetMaxMP(0);
//	pStatus->SetMaxShield(0);
//	pStatus->SetRequirement(10, 100, 150, 0);
//	pStatus->SetSightRadius(8);
//
//	pStatus->SetHPMaxCondition();
//	pStatus->SetMPMaxCondition();
//	pStatus->SetShieldMaxCondition();
//
//	pStructure->SetSupply(0);
//	pStructure->SetBuildTime(10);
//	pStructure->SetRequireMineral(100);
//	pStructure->SetRequireGas(150);
//	pStructure->SetSize(4, 3);
//
//	pStructure->AddBuildableTile(0, 0);
//	pStructure->AddBuildableTile(1, 0);
//	pStructure->AddBuildableTile(2, 0);
//	pStructure->AddBuildableTile(3, 0);
//	pStructure->AddBuildableTile(0, 1);
//	pStructure->AddBuildableTile(1, 1);
//	pStructure->AddBuildableTile(2, 1);
//	pStructure->AddBuildableTile(3, 1);
//	pStructure->AddBuildableTile(0, 2);
//	pStructure->AddBuildableTile(1, 2);
//	pStructure->AddBuildableTile(2, 2);
//	pStructure->AddBuildableTile(3, 2);
//
//	pEllipse->SetMinorAxisLength(48);
//	pEllipse->SetMajorAxisScale(1.6f);
//	pEllipse->SetThickness(2);
//	pEllipse->SetLocalPosition(0, 8);
//
//
//	pCollider->SetRadius(48);
//	pRenderer->SetSize(128, 96);
//
//
//	CSprite* pSprite = new CSprite;
//	pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("ScienceFacility"));
//	pSprite->SetAtlasGridSize(10, 1);
//	pSprite->SetCellSize(128, 96);
//	pSprite->SetLoop(true);
//	pSprite->SetSampleRate(1);
//	pSprite->AddFrame(CVector2(4, 0));
//	pRenderer->AddSprite("Science FacilityNormal", pSprite);
//	pSprite->SaveSprite("Science FacilityNormal.aclp");
//	delete pSprite;
//
//
//	pSprite = new CSprite;
//	pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("ScienceFacility"));
//	pSprite->SetAtlasGridSize(10, 1);
//	pSprite->SetCellSize(128, 96);
//	pSprite->SetLoop(true);
//	pSprite->SetSampleRate(2);
//
//	pSprite->AddFrame(4, 1);
//	pSprite->AddFrame(5, 1);
//	pRenderer->AddSprite("Science FacilityWork", pSprite);
//	pSprite->SaveSprite("Science FacilityWork.aclp");
//	delete pSprite;
//
//
//	pSprite = new CSprite;
//	pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("ScienceFacility"));
//	pSprite->SetAtlasGridSize(10, 1);
//	pSprite->SetCellSize(128, 96);
//	pSprite->SetLoop(true);
//	pSprite->SetSampleRate(4);
//	
//	pSprite->AddFrame(6, 1);
//	pSprite->AddFrame(7, 1);
//	pSprite->AddFrame(8, 1);
//	pSprite->AddFrame(9, 1);
//	pRenderer->AddSprite("Science FacilityLiftUp", pSprite);
//	pSprite->SaveSprite("Science FacilityLiftUp.aclp");
//	delete pSprite;
//
//
//	pSprite = new CSprite;
//	pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("ScienceFacility"));
//	pSprite->SetAtlasGridSize(10, 1);
//	pSprite->SetCellSize(128, 96);
//	pSprite->SetLoop(true);
//	pSprite->SetSampleRate(1);
//
//	pSprite->AddFrame(9, 1);
//	pRenderer->AddSprite("Science FacilityAir", pSprite);
//	pSprite->SaveSprite("Science FacilityAir.aclp");
//	delete pSprite;
//
//
//	pSprite = new CSprite;
//	pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("ScienceFacility"));
//	pSprite->SetAtlasGridSize(10, 1);
//	pSprite->SetCellSize(128, 96);
//	pSprite->SetLoop(true);
//	pSprite->SetSampleRate(4);
//
//	pSprite->AddFrame(9, 1);
//	pSprite->AddFrame(8, 1);
//	pSprite->AddFrame(7, 1);
//	pSprite->AddFrame(6, 1);
//	pRenderer->AddSprite("Science FacilityLiftDown", pSprite);
//	pSprite->SaveSprite("Science FacilityLiftDown.aclp");
//	delete pSprite;
//
//	pSprite = new CSprite;
//	pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("ScienceFacility"));
//	pSprite->SetAtlasGridSize(10, 1);
//	pSprite->SetCellSize(128, 96);
//	pSprite->SetLoop(true);
//	pSprite->SetSampleRate(4 / pStructure->GetBuildTime());
//
//	pSprite->AddFrame(CVector2(0, 0));
//	pSprite->AddFrame(CVector2(1, 0));
//	pSprite->AddFrame(CVector2(2, 0));
//	pSprite->AddFrame(CVector2(3, 0));
//	pRenderer->AddSprite("Science FacilityBuild", pSprite);
//	pSprite->SaveSprite("Science FacilityBuild.aclp");
//	delete pSprite;
//
//	CSprite* pDeathSprite = new CSprite;
//	pDeathSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("Terran_Explosion_Large"));
//	pDeathSprite->SetAtlasGridSize(1, 10);
//	pDeathSprite->SetSampleRate(10);
//	pDeathSprite->SetLoop(false);
//	pDeathSprite->SetCellSize(200, 200);
//	pDeathSprite->AddFrame(CVector2(0, 0));
//	pDeathSprite->AddFrame(CVector2(1, 0));
//	pDeathSprite->AddFrame(CVector2(2, 0));
//	pDeathSprite->AddFrame(CVector2(3, 0));
//	pDeathSprite->AddFrame(CVector2(4, 0));
//	pDeathSprite->AddFrame(CVector2(5, 0));
//	pDeathSprite->AddFrame(CVector2(6, 0));
//	pDeathSprite->AddFrame(CVector2(7, 0));
//	pDeathSprite->AddFrame(CVector2(8, 0));
//	pDeathSprite->AddFrame(CVector2(9, 0));
//
//	pRenderer->AddSprite("Science FacilityDeath", pDeathSprite);
//	pDeathSprite->SaveSprite("Science FacilityDeath.aclp");
//	delete pDeathSprite;
//
//	GET_SINGLE(CFileStream)->SaveUnit(pUnit, "ScienceFacility.unit");
//}
//
//#pragma endregion
//
//
//#pragma region Armory
//
//	{
//	int iTestPositionX = 15;
//	int iTestPositionY = 15;
//	//Supply Depot
//	CGameObject* pUnit = new CGameObject("Armory");
//	pUnit->SetPilot(pPlayer->GetComponent<CPlayer>());
//	pGroundUnitLayer->AddGameObject(pUnit);
//	pUnit->GetTransform()->SetPivot(0.5f, 0.5f);
//	pUnit->GetTransform()->SetPosition(iTestPositionX * 32, iTestPositionY * 32);
//
//	CEllipseRenderer* pEllipse = pUnit->AddComponent<CEllipseRenderer>();
//	CSpriteRenderer* pRenderer = pUnit->AddComponent<CSpriteRenderer>();
//
//	CUnitStatus* pStatus = pUnit->AddComponent<CUnitStatus>();
//	CCircleCollider* pCollider = pUnit->AddComponent<CCircleCollider>();
//	CUnitInfo* pInfo = pUnit->AddComponent<CUnitInfo>();
//	CStructure* pStructure = pUnit->AddComponent<CStructure>();
//	CArmory* pArmory = pUnit->AddComponent<CArmory>();
//
//	pInfo->SetUnitButtonTexture(GET_SINGLE(CResourceManager)->FindTexture("ControlButton_Icon_TerranArmory_Normal"));
//
//	pStatus->SetCreateTime(10);
//	pStatus->SetMaxHP(750);
//	pStatus->SetMaxMP(0);
//	pStatus->SetMaxShield(0);
//	pStatus->SetRequirement(10, 100, 50, 0);
//	pStatus->SetSightRadius(8);
//
//	pStatus->SetHPMaxCondition();
//	pStatus->SetMPMaxCondition();
//	pStatus->SetShieldMaxCondition();
//
//	pStructure->SetSupply(0);
//	pStructure->SetBuildTime(10);
//	pStructure->SetRequireGas(50);
//	pStructure->SetRequireMineral(100);
//	pStructure->SetSize(4, 3);
//
//	pStructure->AddBuildableTile(1, 1);
//	pStructure->AddBuildableTile(2, 1);
//	pStructure->AddBuildableTile(3, 1);
//	pStructure->AddBuildableTile(1, 2);
//	pStructure->AddBuildableTile(2, 2);
//	pStructure->AddBuildableTile(3, 2);
//
//	pEllipse->SetMinorAxisLength(32);
//	pEllipse->SetMajorAxisScale(1.6f);
//	pEllipse->SetThickness(2);
//	pEllipse->SetLocalPosition(0, 8);
//
//
//	pCollider->SetRadius(32);
//
//	pRenderer->SetSize(160, 128);
//
//
//	CSprite* pSprite = new CSprite;
//	pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("Armory"));
//	pSprite->SetAtlasGridSize(8, 1);
//	pSprite->SetCellSize(160, 128);
//	pSprite->SetLoop(true);
//	pSprite->SetSampleRate(1);
//	pSprite->AddFrame(CVector2(4, 0));
//	pRenderer->AddSprite("ArmoryNormal", pSprite);
//	pSprite->SaveSprite("ArmoryNormal.aclp");
//	delete pSprite;
//
//	pSprite = new CSprite;
//	pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("Armory"));
//	pSprite->SetAtlasGridSize(8, 1);
//	pSprite->SetCellSize(160, 128);
//	pSprite->SetLoop(true);
//	pSprite->SetSampleRate(4 / pStructure->GetBuildTime());
//
//	pSprite->AddFrame(CVector2(0, 0));
//	pSprite->AddFrame(CVector2(1, 0));
//	pSprite->AddFrame(CVector2(2, 0));
//	pSprite->AddFrame(CVector2(3, 0));
//
//	pRenderer->AddSprite("ArmoryBuild", pSprite);
//	pSprite->SaveSprite("ArmoryBuild.aclp");
//	delete pSprite;
//
//
//	pSprite = new CSprite;
//	pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("Armory"));
//	pSprite->SetAtlasGridSize(8, 1);
//	pSprite->SetCellSize(160, 128);
//	pSprite->SetLoop(true);
//	pSprite->SetSampleRate(5);
//
//	pSprite->AddFrame(CVector2(4, 0));
//	pSprite->AddFrame(CVector2(5, 0));
//	pSprite->AddFrame(CVector2(6, 0));
//	pSprite->AddFrame(CVector2(7, 0));
//
//	pRenderer->AddSprite("ArmoryWork", pSprite);
//	pSprite->SaveSprite("ArmoryWork.aclp");
//	delete pSprite;
//
//	CSprite* pDeathSprite = new CSprite;
//	pDeathSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("Terran_Explosion_Small"));
//	pDeathSprite->SetAtlasGridSize(1, 10);
//	pDeathSprite->SetSampleRate(10);
//	pDeathSprite->SetLoop(false);
//	pDeathSprite->SetCellSize(128, 128);
//	pDeathSprite->AddFrame(CVector2(0, 0));
//	pDeathSprite->AddFrame(CVector2(1, 0));
//	pDeathSprite->AddFrame(CVector2(2, 0));
//	pDeathSprite->AddFrame(CVector2(3, 0));
//	pDeathSprite->AddFrame(CVector2(4, 0));
//	pDeathSprite->AddFrame(CVector2(5, 0));
//	pDeathSprite->AddFrame(CVector2(6, 0));
//	pDeathSprite->AddFrame(CVector2(7, 0));
//	pDeathSprite->AddFrame(CVector2(8, 0));
//	pDeathSprite->AddFrame(CVector2(9, 0));
//
//	pRenderer->AddSprite("ArmoryDeath", pDeathSprite);
//	pDeathSprite->SaveSprite("ArmoryDeath.aclp");
//	delete pDeathSprite;
//
//	GET_SINGLE(CFileStream)->SaveUnit(pUnit, "Armory.unit");
//}
//
//#pragma endregion
//
//#pragma endregion
//
//#pragma region Unit Prototype
//
//#pragma region Marine
//{
//	int iTempPositionX = 10;
//	int iTempPositionY = 10;
//
//	CGameObject* pUnit = new CGameObject("Marine");
//	pUnit->SetPilot(pPlayer->GetComponent<CPlayer>());
//	pUnit->SetSelected(false);
//	pUnit->SetToAirUnit(false);
//	pGroundUnitLayer->AddGameObject(pUnit);
//	pUnit->GetTransform()->SetPivot(CVector2(0.5f, 0.6f));
//	pUnit->GetTransform()->SetPosition(iTempPositionX * 32, iTempPositionY * 32);
//
//	CCircleCollider* pCollider = pUnit->AddComponent<CCircleCollider>();
//	CEllipseRenderer* pEllipse = pUnit->AddComponent<CEllipseRenderer>();
//	CSpriteRenderer* pRenderer = pUnit->AddComponent<CSpriteRenderer>();
//	CMarineAnimator* pAnimator = pUnit->AddComponent<CMarineAnimator>();
//	CMove* pMove = pUnit->AddComponent<CMove>();
//	CAttack* pAttack = pUnit->AddComponent<CAttack>();
//	CStop* pStop = pUnit->AddComponent<CStop>();
//	CHold* pHold = pUnit->AddComponent<CHold>();
//	CPatrol* pPatrol = pUnit->AddComponent<CPatrol>();
//	CStimpack* pStimpack = pUnit->AddComponent<CStimpack>();
//	CDeffence* pDeffence = pUnit->AddComponent<CDeffence>();
//	CUnitStatus* pStatus = pUnit->AddComponent<CUnitStatus>();
//	CUnitInfo* pInfo = pUnit->AddComponent<CUnitInfo>();
//
//
//	pDeffence->SetDamageDecrement(1);
//	pDeffence->SetName("Terran Infantry Armor");
//	pDeffence->SetUpgradeType(UT_TERRAN_BIONIC_DEFFENCE);
//	pDeffence->SetValue(0);
//
//	pStatus->SetMaxHP(40);
//	pStatus->SetMaxMP(0);
//	pStatus->SetMaxShield(0);
//	pStatus->SetCreateTime(5);
//	pStatus->SetRequirement(5, 50, 0, 1);
//	pStatus->SetSightRadius(6);
//	pStatus->SetHPMaxCondition();
//	pStatus->SetMPMaxCondition();
//	pStatus->SetShieldMaxCondition();
//
//	pInfo->SetAttackComponent(pAttack);
//	pInfo->SetDeffenceComponent(pDeffence);
//	pInfo->SetShieldComponent(NULL);
//	pInfo->SetUnitButtonTexture(GET_SINGLE(CResourceManager)->FindTexture("ControlButton_Icon_TerranMarine_Normal"));
//	pInfo->SetInfoState(IS_NONE);
//
//	pCollider->SetRadius(10);
//
//	pEllipse->SetMinorAxisLength(10);
//	pEllipse->SetMajorAxisScale(1.6f);
//	pEllipse->SetColor(0, 255, 0);
//	pEllipse->SetThickness(2);
//
//	pRenderer->SetSize(64, 64);
//
//	pMove->SetMoveSpeed(100);
//	pMove->SetStopThresholdRadius(50);
//
//	pAttack->SetAttackRange(256);
//	pAttack->SetDamage(6);
//	pAttack->SetInterval(0.5f);
//	pAttack->SetUpgradeIncrease(1);
//	pAttack->SetUpgradeType(UT_TERRAN_BIONIC_WEAPON);
//	pAttack->SetWeaponName("Gauss Rifle");
//
//
//	{
//		string name = pUnit->GetName();
//
//		for (int i = 0; i < 16; ++i)
//		{
//			char idx[4] = {};
//			itoa(i, idx, 10);
//
//
//			CSprite* pSprite = new CSprite;
//			pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("Marine"));
//			pSprite->SetAtlasGridSize(16, 14);
//			pSprite->SetCellSize(64, 64);
//			pSprite->SetLoop(true);
//			pSprite->SetSampleRate(1);
//			pSprite->AddFrame(i, 0);
//			pRenderer->AddSprite(name + string("Stand") + string(idx), pSprite);
//			pSprite->SaveSprite(name + string("Stand") + string(idx) + string(".aclp"));
//			delete pSprite;
//
//			pSprite = new CSprite;
//			pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("Marine"));
//			pSprite->SetAtlasGridSize(16, 14);
//			pSprite->SetCellSize(64, 64);
//			pSprite->SetLoop(false);
//			pSprite->SetDestroyOnEnd(false);
//			pSprite->SetSampleRate(15 * 1 / pAttack->GetInterval());
//			pSprite->AddFrame(i, 2);
//			pSprite->AddFrame(i, 3);
//			pSprite->AddFrame(i, 2);
//			pSprite->AddFrame(i, 3);
//			pSprite->AddFrame(i, 2);
//			pSprite->AddFrame(i, 3); 
//			pSprite->AddFrame(i, 2);
//			pRenderer->AddSprite(name + string("Attack") + string(idx), pSprite);
//			pSprite->SaveSprite(name + string("Attack") + string(idx) + string(".aclp"));
//			delete pSprite;
//
//		
//			pSprite = new CSprite;
//			pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("Marine"));
//			pSprite->SetAtlasGridSize(16, 14);
//			pSprite->SetCellSize(64, 64);
//			pSprite->SetLoop(true);
//			pSprite->SetSampleRate(15);
//			pSprite->AddFrame(i, 4);
//			pSprite->AddFrame(i, 5);
//			pSprite->AddFrame(i, 6);
//			pSprite->AddFrame(i, 7);
//			pSprite->AddFrame(i, 8);
//			pSprite->AddFrame(i, 9);
//			pSprite->AddFrame(i, 10);
//			pSprite->AddFrame(i, 11);
//			pRenderer->AddSprite(name + string("Move") + string(idx), pSprite);
//			pSprite->SaveSprite(name + string("Move") + string(idx) + string(".aclp"));
//			delete pSprite;
//		}
//
//		CSprite* pSprite = new CSprite;
//		pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("Marine"));
//		pSprite->SetAtlasGridSize(16, 14);
//		pSprite->SetCellSize(64, 64);
//		pSprite->SetLoop(false);
//		pSprite->SetSampleRate(15);
//		pSprite->AddFrame(0, 13);
//		pSprite->AddFrame(1, 13);
//		pSprite->AddFrame(2, 13);
//		pSprite->AddFrame(3, 13);
//		pSprite->AddFrame(4, 13);
//		pSprite->AddFrame(5, 13);
//		pSprite->AddFrame(6, 13);
//		pSprite->AddFrame(7, 13);
//		pRenderer->AddSprite(name + string("Death"), pSprite);
//		pSprite->SaveSprite(name + string("Death") + string(".aclp"));
//		delete pSprite;
//	}
//
//	GET_SINGLE(CFileStream)->SaveUnit(pUnit,"Marine.unit");
//}
//#pragma endregion
//
//#pragma region Firebat
//	{
//	int iTempPositionX = 9;
//	int iTempPositionY = 10;
//
//	CGameObject* pUnit = new CGameObject("Firebat");
//	pUnit->SetPilot(pPlayer->GetComponent<CPlayer>());
//	pUnit->SetSelected(false);
//	pUnit->SetToAirUnit(false);
//	pGroundUnitLayer->AddGameObject(pUnit);
//	pUnit->GetTransform()->SetPivot(CVector2(0.5f, 0.6f));
//	pUnit->GetTransform()->SetPosition(iTempPositionX * 32, iTempPositionY * 32);
//
//	CCircleCollider* pCollider = pUnit->AddComponent<CCircleCollider>();
//	CEllipseRenderer* pEllipse = pUnit->AddComponent<CEllipseRenderer>();
//	CSpriteRenderer* pRenderer = pUnit->AddComponent<CSpriteRenderer>();
//	CFirebatAnimator* pAnimator = pUnit->AddComponent<CFirebatAnimator>();
//	CMove* pMove = pUnit->AddComponent<CMove>();
//	CAttack* pAttack = pUnit->AddComponent<CAttack>();
//	CStop* pStop = pUnit->AddComponent<CStop>();
//	CHold* pHold = pUnit->AddComponent<CHold>();
//	CPatrol* pPatrol = pUnit->AddComponent<CPatrol>();
//	CStimpack* pStimpack = pUnit->AddComponent<CStimpack>();
//	CDeffence* pDeffence = pUnit->AddComponent<CDeffence>();
//	CUnitStatus* pStatus = pUnit->AddComponent<CUnitStatus>();
//	CUnitInfo* pInfo = pUnit->AddComponent<CUnitInfo>();
//
//
//	pDeffence->SetDamageDecrement(1);
//	pDeffence->SetName("Terran Infantry Armor");
//	pDeffence->SetUpgradeType(UT_TERRAN_BIONIC_DEFFENCE);
//	pDeffence->SetValue(0);
//
//	pStatus->SetMaxHP(40);
//	pStatus->SetMaxMP(0);
//	pStatus->SetMaxShield(0);
//	pStatus->SetCreateTime(5);
//	pStatus->SetRequirement(5, 50, 25, 1);
//	pStatus->SetSightRadius(6);
//	pStatus->SetHPMaxCondition();
//	pStatus->SetMPMaxCondition();
//	pStatus->SetShieldMaxCondition();
//
//	pInfo->SetAttackComponent(pAttack);
//	pInfo->SetDeffenceComponent(pDeffence);
//	pInfo->SetShieldComponent(NULL);
//	pInfo->SetUnitButtonTexture(GET_SINGLE(CResourceManager)->FindTexture("ControlButton_Icon_TerranFirebat_Normal"));
//	pInfo->SetInfoState(IS_NONE);
//
//	pCollider->SetRadius(15);
//
//	pEllipse->SetMinorAxisLength(15);
//	pEllipse->SetMajorAxisScale(1.6f);
//	pEllipse->SetColor(0, 255, 0);
//	pEllipse->SetThickness(2);
//
//	pRenderer->SetSize(32, 32);
//
//	pMove->SetMoveSpeed(100);
//	pMove->SetStopThresholdRadius(50);
//
//	pAttack->SetAttackRange(64);
//	pAttack->SetDamage(16);
//	pAttack->SetInterval(0.75f);
//	pAttack->SetUpgradeIncrease(1);
//	pAttack->SetUpgradeType(UT_TERRAN_BIONIC_WEAPON);
//	pAttack->SetWeaponName("Flame Thrower");
//
//
//	{
//		string name = pUnit->GetName();
//		//VFX
//		for (int i = 0; i < 16; ++i)
//		{
//			char idx[4] = {};
//			itoa(i, idx, 10);
//
//			CSprite* pSprite = new CSprite;
//			pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("FirebatAttack"));
//			pSprite->SetAtlasGridSize(16, 13);
//			pSprite->SetCellSize(224, 224);
//			pSprite->SetLoop(false);
//			pSprite->SetDestroyOnEnd(true);
//			pSprite->SetSampleRate(20);
//			pSprite->AddFrame(i, 0);
//			pSprite->AddFrame(i, 1);
//			pSprite->AddFrame(i, 2);
//			pSprite->AddFrame(i, 3);
//			pSprite->AddFrame(i, 4);
//			pSprite->AddFrame(i, 5);
//			pSprite->AddFrame(i, 6);
//			pSprite->AddFrame(i, 7);
//			pSprite->AddFrame(i, 8);
//			pSprite->AddFrame(i, 9);
//			pSprite->AddFrame(i, 10);
//			pSprite->AddFrame(i, 11);
//			pSprite->AddFrame(i, 12);
//			pSprite->SetSpriteKey(name + string("AttackEffect") + string(idx));
//			pSprite->SaveSprite(name + string("AttackEffect") + string(idx) + string(".aclp"));
//			delete pSprite;
//
//		}
//
//		for (int i = 0; i < 16; ++i)
//		{
//			char idx[4] = {};
//			itoa(i, idx, 10);
//
//
//			CSprite* pSprite = new CSprite;
//			pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("Firebat"));
//			pSprite->SetAtlasGridSize(16, 10);
//			pSprite->SetCellSize(32, 32);
//			pSprite->SetLoop(true);
//			pSprite->SetSampleRate(1);
//			pSprite->AddFrame(i, 3);
//			pRenderer->AddSprite(name + string("Stand") + string(idx), pSprite);
//			pSprite->SaveSprite(name + string("Stand") + string(idx) + string(".aclp"));
//			delete pSprite;
//
//			pSprite = new CSprite;
//			pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("Firebat"));
//			pSprite->SetAtlasGridSize(16, 10);
//			pSprite->SetCellSize(32, 32);
//			pSprite->SetLoop(false);
//			pSprite->SetDestroyOnEnd(false);
//			pSprite->SetSampleRate(15 * 1 / pAttack->GetInterval());
//			pSprite->AddFrame(i, 0);
//			pSprite->AddFrame(i, 1);
//			pRenderer->AddSprite(name + string("Attack") + string(idx), pSprite);
//			pSprite->SaveSprite(name + string("Attack") + string(idx) + string(".aclp"));
//			delete pSprite;
//
//
//			pSprite = new CSprite;
//			pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("Firebat"));
//			pSprite->SetAtlasGridSize(16, 10);
//			pSprite->SetCellSize(32, 32);
//			pSprite->SetLoop(true);
//			pSprite->SetDestroyOnEnd(false);
//			pSprite->SetSampleRate(15);
//			pSprite->AddFrame(i, 2);
//			pSprite->AddFrame(i, 3);
//			pSprite->AddFrame(i, 4);
//			pSprite->AddFrame(i, 5);
//			pSprite->AddFrame(i, 6);
//			pSprite->AddFrame(i, 7);
//			pSprite->AddFrame(i, 8);
//			pSprite->AddFrame(i, 9);
//			pRenderer->AddSprite(name + string("Move") + string(idx), pSprite);
//			pSprite->SaveSprite(name + string("Move") + string(idx) + string(".aclp"));
//			delete pSprite;
//		}
//
//		CSprite* pSprite = new CSprite;
//		pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("Terran_Explosion_XSmall"));
//		pSprite->SetAtlasGridSize(9, 1);
//		pSprite->SetCellSize(64, 64);
//		pSprite->SetLoop(false);
//		pSprite->SetDestroyOnEnd(true);
//		pSprite->SetSampleRate(15);
//		pSprite->AddFrame(0, 0);
//		pSprite->AddFrame(1, 0);
//		pSprite->AddFrame(2, 0);
//		pSprite->AddFrame(3, 0);
//		pSprite->AddFrame(4, 0);
//		pSprite->AddFrame(5, 0);
//		pSprite->AddFrame(6, 0);
//		pSprite->AddFrame(7, 0);
//		pSprite->AddFrame(8, 0);
//		pRenderer->AddSprite(name + string("Death"), pSprite);
//		pSprite->SaveSprite(name + string("Death") + string(".aclp"));
//		delete pSprite;
//
//
//		GET_SINGLE(CFileStream)->SaveUnit(pUnit, "Firebat.unit");
//	}
//}
//#pragma endregion
//
//
//#pragma region Medic
//{
//int iTempPositionX = 10;
//int iTempPositionY = 9;
//
//CGameObject* pUnit = new CGameObject("Medic");
//pUnit->SetPilot(pPlayer->GetComponent<CPlayer>());
//pUnit->SetSelected(false);
//pUnit->SetToAirUnit(false);
//pGroundUnitLayer->AddGameObject(pUnit);
//pUnit->GetTransform()->SetPivot(CVector2(0.5f, 0.6f));
//pUnit->GetTransform()->SetPosition(iTempPositionX * 32, iTempPositionY * 32);
//
//CCircleCollider* pCollider = pUnit->AddComponent<CCircleCollider>();
//CEllipseRenderer* pEllipse = pUnit->AddComponent<CEllipseRenderer>();
//CSpriteRenderer* pRenderer = pUnit->AddComponent<CSpriteRenderer>();
//CFirebatAnimator* pAnimator = pUnit->AddComponent<CFirebatAnimator>();
//CMove* pMove = pUnit->AddComponent<CMove>();
//CStop* pStop = pUnit->AddComponent<CStop>();
//CHold* pHold = pUnit->AddComponent<CHold>();
//CPatrol* pPatrol = pUnit->AddComponent<CPatrol>();
//CDeffence* pDeffence = pUnit->AddComponent<CDeffence>();
//CUnitStatus* pStatus = pUnit->AddComponent<CUnitStatus>();
//CUnitInfo* pInfo = pUnit->AddComponent<CUnitInfo>();
//
//
//pDeffence->SetDamageDecrement(1);
//pDeffence->SetName("Terran Infantry Armor");
//pDeffence->SetUpgradeType(UT_TERRAN_BIONIC_DEFFENCE);
//pDeffence->SetValue(0);
//
//pStatus->SetMaxHP(60);
//pStatus->SetMaxMP(200);
//pStatus->SetMaxShield(0);
//pStatus->SetCreateTime(5);
//pStatus->SetRequirement(5, 50, 25, 1);
//pStatus->SetSightRadius(6);
//pStatus->SetHPMaxCondition();
//pStatus->SetMPMaxCondition();
//pStatus->SetShieldMaxCondition();
//
//pInfo->SetAttackComponent(NULL);
//pInfo->SetDeffenceComponent(pDeffence);
//pInfo->SetShieldComponent(NULL);
//pInfo->SetUnitButtonTexture(GET_SINGLE(CResourceManager)->FindTexture("ControlButton_Icon_TerranMedic_Normal"));
//pInfo->SetInfoState(IS_NONE);
//
//pCollider->SetRadius(12);
//
//pEllipse->SetMinorAxisLength(12);
//pEllipse->SetMajorAxisScale(1.6f);
//pEllipse->SetColor(0, 255, 0);
//pEllipse->SetThickness(2);
//
//pRenderer->SetSize(64, 64);
//
//pMove->SetMoveSpeed(100);
//pMove->SetStopThresholdRadius(50);
//
//
//	string name = pUnit->GetName();
//
//	for (int i = 0; i < 16; ++i)
//	{
//		char idx[4] = {};
//		itoa(i, idx, 10);
//
//		CSprite* pSprite = new CSprite;
//		pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("Medic"));
//		pSprite->SetAtlasGridSize(16, 14);
//		pSprite->SetCellSize(64, 64);
//		pSprite->SetLoop(true);
//		pSprite->SetSampleRate(1);
//		pSprite->AddFrame(i, 0);
//		pRenderer->AddSprite(name + string("Stand") + string(idx), pSprite);
//		pSprite->SaveSprite(name + string("Stand") + string(idx) + string(".aclp"));
//		delete pSprite;
//
//		pSprite = new CSprite;
//		pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("Medic"));
//		pSprite->SetAtlasGridSize(16, 14);
//		pSprite->SetCellSize(64, 64);
//		pSprite->SetLoop(true);
//		pSprite->SetDestroyOnEnd(false);
//		pSprite->SetSampleRate(30);
//		pSprite->AddFrame(i, 1);
//		pSprite->AddFrame(i, 2);
//		pSprite->AddFrame(i, 3);
//		pSprite->AddFrame(i, 4);
//		pSprite->AddFrame(i, 5);
//		pSprite->AddFrame(i, 4);
//		pSprite->AddFrame(i, 5);
//		pSprite->AddFrame(i, 4);
//		pSprite->AddFrame(i, 5);
//		pRenderer->AddSprite(name + string("Heal") + string(idx), pSprite);
//		pSprite->SaveSprite(name + string("Heal") + string(idx) + string(".aclp"));
//		delete pSprite;
//
//
//		pSprite = new CSprite;
//		pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("Medic"));
//		pSprite->SetAtlasGridSize(16, 14);
//		pSprite->SetCellSize(64, 64);
//		pSprite->SetLoop(true);
//		pSprite->SetDestroyOnEnd(false);
//		pSprite->SetSampleRate(15);
//		pSprite->AddFrame(i, 6);
//		pSprite->AddFrame(i, 7);
//		pSprite->AddFrame(i, 8);
//		pSprite->AddFrame(i, 9);
//		pSprite->AddFrame(i, 10);
//		pSprite->AddFrame(i, 11);
//		pSprite->AddFrame(i, 12);
//		pRenderer->AddSprite(name + string("Move") + string(idx), pSprite);
//		pSprite->SaveSprite(name + string("Move") + string(idx) + string(".aclp"));
//		delete pSprite;
//	}
//
//	CSprite* pSprite = new CSprite;
//	pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("Medic"));
//	pSprite->SetAtlasGridSize(16, 14);
//	pSprite->SetCellSize(64, 64);
//	pSprite->SetLoop(false);
//	pSprite->SetDestroyOnEnd(true);
//	pSprite->SetSampleRate(15);
//	pSprite->AddFrame(0, 13);
//	pSprite->AddFrame(1, 13);
//	pSprite->AddFrame(2, 13);
//	pSprite->AddFrame(3, 13);
//	pSprite->AddFrame(4, 13);
//	pSprite->AddFrame(5, 13);
//	pSprite->AddFrame(6, 13);
//	pSprite->AddFrame(7, 13);
//	pSprite->AddFrame(8, 13);
//	pRenderer->AddSprite(name + string("Death"), pSprite);
//	pSprite->SaveSprite(name + string("Death") + string(".aclp"));
//	delete pSprite;
//
//
//
//	GET_SINGLE(CFileStream)->SaveUnit(pUnit, "Medic.unit");
//}
//#pragma endregion
//
//
//#pragma region Ghost
//{
//int iTempPositionX = 12;
//int iTempPositionY = 11;
//
//CGameObject* pUnit = new CGameObject("Ghost");
//pUnit->SetPilot(pPlayer->GetComponent<CPlayer>());
//pUnit->SetSelected(false);
//pUnit->SetToAirUnit(false);
//pGroundUnitLayer->AddGameObject(pUnit);
//pUnit->GetTransform()->SetPivot(CVector2(0.5f, 0.6f));
//pUnit->GetTransform()->SetPosition(iTempPositionX * 32, iTempPositionY * 32);
//
//CCircleCollider* pCollider = pUnit->AddComponent<CCircleCollider>();
//CEllipseRenderer* pEllipse = pUnit->AddComponent<CEllipseRenderer>();
//CSpriteRenderer* pRenderer = pUnit->AddComponent<CSpriteRenderer>();
//CMarineAnimator* pAnimator = pUnit->AddComponent<CMarineAnimator>();
//CMove* pMove = pUnit->AddComponent<CMove>();
//CAttack* pAttack = pUnit->AddComponent<CAttack>();
//CStop* pStop = pUnit->AddComponent<CStop>();
//CHold* pHold = pUnit->AddComponent<CHold>();
//CPatrol* pPatrol = pUnit->AddComponent<CPatrol>();
//CStimpack* pStimpack = pUnit->AddComponent<CStimpack>();
//CDeffence* pDeffence = pUnit->AddComponent<CDeffence>();
//CUnitStatus* pStatus = pUnit->AddComponent<CUnitStatus>();
//CUnitInfo* pInfo = pUnit->AddComponent<CUnitInfo>();
//
//
//pDeffence->SetDamageDecrement(1);
//pDeffence->SetName("Terran Infantry Armor");
//pDeffence->SetUpgradeType(UT_TERRAN_BIONIC_DEFFENCE);
//pDeffence->SetValue(0);
//
//pStatus->SetMaxHP(45);
//pStatus->SetMaxMP(200);
//pStatus->SetMaxShield(0);
//pStatus->SetCreateTime(5);
//pStatus->SetRequirement(5, 25, 75, 1);
//pStatus->SetSightRadius(6);
//pStatus->SetHPMaxCondition();
//pStatus->SetMPMaxCondition();
//pStatus->SetShieldMaxCondition();
//
//pInfo->SetAttackComponent(pAttack);
//pInfo->SetDeffenceComponent(pDeffence);
//pInfo->SetShieldComponent(NULL);
//pInfo->SetUnitButtonTexture(GET_SINGLE(CResourceManager)->FindTexture("ControlButton_Icon_TerranGhost_Normal"));
//pInfo->SetInfoState(IS_NONE);
//
//pCollider->SetRadius(10);
//
//pEllipse->SetMinorAxisLength(10);
//pEllipse->SetMajorAxisScale(1.6f);
//pEllipse->SetColor(0, 255, 0);
//pEllipse->SetThickness(2);
//
//pRenderer->SetSize(64, 64);
//
//pMove->SetMoveSpeed(100);
//pMove->SetStopThresholdRadius(50);
//
//pAttack->SetAttackRange(320);
//pAttack->SetDamage(10);
//pAttack->SetInterval(1.25f);
//pAttack->SetUpgradeIncrease(1);
//pAttack->SetUpgradeType(UT_TERRAN_BIONIC_WEAPON);
//pAttack->SetWeaponName("C-10 Canister Rifle");
//
//
//{
//	string name = pUnit->GetName();
//
//	for (int i = 0; i < 16; ++i)
//	{
//		char idx[4] = {};
//		itoa(i, idx, 10);
//
//		CSprite* pSprite = new CSprite;
//		pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("Ghost"));
//		pSprite->SetAtlasGridSize(16, 14);
//		pSprite->SetCellSize(64, 64);
//		pSprite->SetLoop(true);
//		pSprite->SetSampleRate(1);
//		pSprite->AddFrame(i, 4);
//		pRenderer->AddSprite(name + string("Stand") + string(idx), pSprite);
//		pSprite->SaveSprite(name + string("Stand") + string(idx) + string(".aclp"));
//		delete pSprite;
//
//		pSprite = new CSprite;
//		pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("Ghost"));
//		pSprite->SetAtlasGridSize(16, 14);
//		pSprite->SetCellSize(64, 64);
//		pSprite->SetLoop(false);
//		pSprite->SetDestroyOnEnd(false);
//		pSprite->SetSampleRate(15 * 1 / pAttack->GetInterval());
//		pSprite->AddFrame(i, 3);
//		pSprite->AddFrame(i, 2);
//		pRenderer->AddSprite(name + string("Attack") + string(idx), pSprite);
//		pSprite->SaveSprite(name + string("Attack") + string(idx) + string(".aclp"));
//		delete pSprite;
//
//
//		pSprite = new CSprite;
//		pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("Ghost"));
//		pSprite->SetAtlasGridSize(16, 14);
//		pSprite->SetCellSize(64, 64);
//		pSprite->SetLoop(true);
//		pSprite->SetSampleRate(15);
//		pSprite->AddFrame(i, 4);
//		pSprite->AddFrame(i, 5);
//		pSprite->AddFrame(i, 6);
//		pSprite->AddFrame(i, 7);
//		pSprite->AddFrame(i, 8);
//		pSprite->AddFrame(i, 9);
//		pSprite->AddFrame(i, 10);
//		pSprite->AddFrame(i, 11);
//		pSprite->AddFrame(i, 12);
//		pRenderer->AddSprite(name + string("Move") + string(idx), pSprite);
//		pSprite->SaveSprite(name + string("Move") + string(idx) + string(".aclp"));
//		delete pSprite;
//	}
//
//	CSprite* pSprite = new CSprite;
//	pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("Ghost"));
//	pSprite->SetAtlasGridSize(16, 14);
//	pSprite->SetCellSize(64, 64);
//	pSprite->SetLoop(false);
//	pSprite->SetSampleRate(15);
//	pSprite->AddFrame(0, 13);
//	pSprite->AddFrame(1, 13);
//	pSprite->AddFrame(2, 13);
//	pSprite->AddFrame(3, 13);
//	pSprite->AddFrame(4, 13);
//	pSprite->AddFrame(5, 13);
//	pSprite->AddFrame(6, 13);
//	pSprite->AddFrame(7, 13);
//	pRenderer->AddSprite(name + string("Death"), pSprite);
//	pSprite->SaveSprite(name + string("Death") + string(".aclp"));
//	delete pSprite;
//}
//
//
//GET_SINGLE(CFileStream)->SaveUnit(pUnit, "Ghost.unit");
//}
//#pragma endregion
// 
//
//#pragma region Vulture
//{
//int iTempPositionX = 12;
//int iTempPositionY = 11;
//
//CGameObject* pUnit = new CGameObject("Vulture");
//pUnit->SetPilot(pPlayer->GetComponent<CPlayer>());
//pUnit->SetSelected(false);
//pUnit->SetToAirUnit(false);
//pGroundUnitLayer->AddGameObject(pUnit);
//pUnit->GetTransform()->SetPivot(CVector2(0.5f, 0.6f));
//pUnit->GetTransform()->SetPosition(iTempPositionX * 32, iTempPositionY * 32);
//
//CCircleCollider* pCollider = pUnit->AddComponent<CCircleCollider>();
//CEllipseRenderer* pEllipse = pUnit->AddComponent<CEllipseRenderer>();
//CSpriteRenderer* pRenderer = pUnit->AddComponent<CSpriteRenderer>();
//CMarineAnimator* pAnimator = pUnit->AddComponent<CMarineAnimator>();
//CMove* pMove = pUnit->AddComponent<CMove>();
//CAttack* pAttack = pUnit->AddComponent<CAttack>();
//CStop* pStop = pUnit->AddComponent<CStop>();
//CHold* pHold = pUnit->AddComponent<CHold>();
//CPatrol* pPatrol = pUnit->AddComponent<CPatrol>();
//CDeffence* pDeffence = pUnit->AddComponent<CDeffence>();
//CUnitStatus* pStatus = pUnit->AddComponent<CUnitStatus>();
//CUnitInfo* pInfo = pUnit->AddComponent<CUnitInfo>();
//
//
//pDeffence->SetDamageDecrement(1);
//pDeffence->SetName("Terran Vehicle Plating");
//pDeffence->SetUpgradeType(UT_TERRAN_MECHANIC_GROUND_DEFFENCE);
//pDeffence->SetValue(0);
//
//pStatus->SetMaxHP(80);
//pStatus->SetMaxMP(0);
//pStatus->SetMaxShield(0);
//pStatus->SetCreateTime(5);
//pStatus->SetRequirement(5, 75, 0, 2);
//pStatus->SetSightRadius(6);
//pStatus->SetHPMaxCondition();
//pStatus->SetMPMaxCondition();
//pStatus->SetShieldMaxCondition();
//
//pInfo->SetAttackComponent(pAttack);
//pInfo->SetDeffenceComponent(pDeffence);
//pInfo->SetShieldComponent(NULL);
//pInfo->SetUnitButtonTexture(GET_SINGLE(CResourceManager)->FindTexture("ControlButton_Icon_TerranVulture_Normal"));
//pInfo->SetInfoState(IS_NONE);
//
//pCollider->SetRadius(18);
//
//pEllipse->SetMinorAxisLength(18);
//pEllipse->SetMajorAxisScale(1.6f);
//pEllipse->SetColor(0, 255, 0);
//pEllipse->SetThickness(2);
//
//pRenderer->SetSize(100, 100);
//
//pMove->SetMoveSpeed(100);
//pMove->SetStopThresholdRadius(50);
//
//pAttack->SetAttackRange(160);
//pAttack->SetDamage(20);
//pAttack->SetInterval(1.25f);
//pAttack->SetUpgradeIncrease(1);
//pAttack->SetUpgradeType(UT_TERRAN_MECHANIC_GROUND_WAEPON);
//pAttack->SetWeaponName("Fragmentation Grenade");
//
//
//{
//	string name = pUnit->GetName();
//
//	for (int i = 0; i < 16; ++i)
//	{
//		char idx[4] = {};
//		itoa(i, idx, 10);
//
//		CSprite* pSprite = new CSprite;
//		pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("Vulture"));
//		pSprite->SetAtlasGridSize(16, 1);
//		pSprite->SetCellSize(100, 100);
//		pSprite->SetLoop(true);
//		pSprite->SetSampleRate(1);
//		pSprite->AddFrame(i, 0);
//		pRenderer->AddSprite(name + string("Stand") + string(idx), pSprite);
//		pSprite->SaveSprite(name + string("Stand") + string(idx) + string(".aclp"));
//		pRenderer->AddSprite(name + string("Move") + string(idx), pSprite);
//		pSprite->SaveSprite(name + string("Move") + string(idx) + string(".aclp"));
//		delete pSprite;
//
//		pSprite = new CSprite;
//		pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("Vulture"));
//		pSprite->SetAtlasGridSize(16, 1);
//		pSprite->SetCellSize(100, 100);
//		pSprite->SetLoop(false);
//		pSprite->SetDestroyOnEnd(false);
//		pSprite->SetSampleRate(1);
//		pSprite->AddFrame(i, 0);
//		pRenderer->AddSprite(name + string("Attack") + string(idx), pSprite);
//		pSprite->SaveSprite(name + string("Attack") + string(idx) + string(".aclp"));
//		delete pSprite;
//	}
//
//	CSprite* pSprite = new CSprite;
//	pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("Terran_Explosion_Small"));
//	pSprite->SetAtlasGridSize(10, 0);
//	pSprite->SetCellSize(128, 128);
//	pSprite->SetLoop(false);
//	pSprite->SetDestroyOnEnd(true);
//	pSprite->SetSampleRate(15);
//	pSprite->AddFrame(0, 0);
//	pSprite->AddFrame(1, 0);
//	pSprite->AddFrame(2, 0);
//	pSprite->AddFrame(3, 0);
//	pSprite->AddFrame(4, 0);
//	pSprite->AddFrame(5, 0);
//	pSprite->AddFrame(6, 0);
//	pSprite->AddFrame(7, 0);
//	pSprite->AddFrame(8, 0);
//	pSprite->AddFrame(9, 0);
//	pRenderer->AddSprite(name + string("Death"), pSprite);
//	pSprite->SaveSprite(name + string("Death") + string(".aclp"));
//	delete pSprite;
//}
//
//GET_SINGLE(CFileStream)->SaveUnit(pUnit,"Vulture.unit");
//}
//#pragma endregion
///*
//#pragma region Siege Tank
//{
//int iTempPositionX = 12;
//int iTempPositionY = 11;
//
//CGameObject* pUnit = new CGameObject("Siege Tank");
//pUnit->SetPilot(pPlayer->GetComponent<CPlayer>());
//pUnit->SetSelected(false);
//pUnit->SetToAirUnit(false);
//pGroundUnitLayer->AddGameObject(pUnit);
//pUnit->GetTransform()->SetPivot(CVector2(0.5f, 0.6f));
//pUnit->GetTransform()->SetPosition(iTempPositionX * 32, iTempPositionY * 32);
//
//CCircleCollider* pCollider = pUnit->AddComponent<CCircleCollider>();
//CEllipseRenderer* pEllipse = pUnit->AddComponent<CEllipseRenderer>();
//CSpriteRenderer* pBodyRenderer = pUnit->AddComponent<CSpriteRenderer>();
//CSpriteRenderer* pHeadRenderer = pUnit->AddComponent<CSpriteRenderer>();
//CMarineAnimator* pAnimator = pUnit->AddComponent<CMarineAnimator>();
//CMove* pMove = pUnit->AddComponent<CMove>();
//CAttack* pAttack = pUnit->AddComponent<CAttack>();
//CStop* pStop = pUnit->AddComponent<CStop>();
//CHold* pHold = pUnit->AddComponent<CHold>();
//CPatrol* pPatrol = pUnit->AddComponent<CPatrol>();
//CDeffence* pDeffence = pUnit->AddComponent<CDeffence>();
//CUnitStatus* pStatus = pUnit->AddComponent<CUnitStatus>();
//CUnitInfo* pInfo = pUnit->AddComponent<CUnitInfo>();
//
//
//pDeffence->SetDamageDecrement(1);
//pDeffence->SetName("Terran Vehicle Plating");
//pDeffence->SetUpgradeType(UT_TERRAN_MECHANIC_GROUND_DEFFENCE);
//pDeffence->SetValue(0);
//
//pStatus->SetMaxHP(150);
//pStatus->SetMaxMP(0);
//pStatus->SetMaxShield(0);
//pStatus->SetCreateTime(5);
//pStatus->SetRequirement(5, 150, 100, 2);
//pStatus->SetSightRadius(6);
//pStatus->SetHPMaxCondition();
//pStatus->SetMPMaxCondition();
//pStatus->SetShieldMaxCondition();
//
//pInfo->SetAttackComponent(pAttack);
//pInfo->SetDeffenceComponent(pDeffence);
//pInfo->SetShieldComponent(NULL);
//pInfo->SetUnitButtonTexture(GET_SINGLE(CResourceManager)->FindTexture("ControlButton_Icon_TerranSiegeTank_Normal"));
//pInfo->SetInfoState(IS_NONE);
//
//pCollider->SetRadius(18);
//
//pEllipse->SetMinorAxisLength(18);
//pEllipse->SetMajorAxisScale(1.6f);
//pEllipse->SetColor(0, 255, 0);
//pEllipse->SetThickness(2);
//
//pBodyRenderer->SetSize(128, 128);
//pHeadRenderer->SetSize(128, 128);
//
//pMove->SetMoveSpeed(100);
//pMove->SetStopThresholdRadius(50);
//
//pAttack->SetAttackRange(160);
//pAttack->SetDamage(20);
//pAttack->SetInterval(1.25f);
//pAttack->SetUpgradeIncrease(1);
//pAttack->SetUpgradeType(UT_TERRAN_MECHANIC_GROUND_WAEPON);
//pAttack->SetWeaponName("Fragmentation Grenade");
//
//
//{
//	string name = pUnit->GetName();
//
//	for (int i = 0; i < 16; ++i)
//	{
//		char idx[4] = {};
//		itoa(i, idx, 10);
//
//		CSprite* pSprite = new CSprite;
//		pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("TankHead"));
//		pSprite->SetAtlasGridSize(16, 2);
//		pSprite->SetCellSize(128, 128);
//		pSprite->SetLoop(true);
//		pSprite->SetSampleRate(1);
//		pSprite->AddFrame(i, 0);
//		pHeadRenderer->AddSprite(name + string("HeadNormalStand") + string(idx), pSprite);
//		pSprite->SaveSprite(name + string("HeadNormalStand") + string(idx) + string(".aclp"));
//		delete pSprite;
//
//		pSprite = new CSprite;
//		pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("TankHead"));
//		pSprite->SetAtlasGridSize(16, 2);
//		pSprite->SetCellSize(128, 128);
//		pSprite->SetLoop(true);
//		pSprite->SetSampleRate(1);
//		pSprite->AddFrame(i, 1);
//		pHeadRenderer->AddSprite(name + string("HeadTransformedStand") + string(idx), pSprite);
//		pSprite->SaveSprite(name + string("HeadTransformedStand") + string(idx) + string(".aclp"));
//		delete pSprite;
//
//		pSprite = new CSprite;
//		pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("TankBody"));
//		pSprite->SetAtlasGridSize(16, 3);
//		pSprite->SetCellSize(128, 128);
//		pSprite->SetLoop(true);
//		pSprite->SetSampleRate(5);
//		pSprite->AddFrame(i, 0);
//		pSprite->AddFrame(i, 1);
//		pSprite->AddFrame(i, 2);
//		pBodyRenderer->AddSprite(name + string("Body") + string(idx), pSprite);
//		pSprite->SaveSprite(name + string("Body") + string(idx) + string(".aclp"));
//		delete pSprite;
//
//	}
//
//
//
//	CSprite* pSprite = new CSprite;
//	pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("Terran_Explosion_Small"));
//	pSprite->SetAtlasGridSize(10, 0);
//	pSprite->SetCellSize(128, 128);
//	pSprite->SetLoop(false);
//	pSprite->SetDestroyOnEnd(true);
//	pSprite->SetSampleRate(15);
//	pSprite->AddFrame(0, 0);
//	pSprite->AddFrame(1, 0);
//	pSprite->AddFrame(2, 0);
//	pSprite->AddFrame(3, 0);
//	pSprite->AddFrame(4, 0);
//	pSprite->AddFrame(5, 0);
//	pSprite->AddFrame(6, 0);
//	pSprite->AddFrame(7, 0);
//	pSprite->AddFrame(8, 0);
//	pSprite->AddFrame(9, 0);
//	pRenderer->AddSprite(name + string("Death"), pSprite);
//	pSprite->SaveSprite(name + string("Death") + string(".aclp"));
//	delete pSprite;
//
//
//	pSprite = new CSprite;
//	pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("TankBodyTransform"));
//	pSprite->SetAtlasGridSize(6, 1);
//	pSprite->SetCellSize(128, 128);
//	pSprite->SetLoop(false);
//	pSprite->SetDestroyOnEnd(false);
//	pSprite->SetSampleRate(2);
//	pSprite->AddFrame(0, 0);
//	pSprite->AddFrame(1, 0);
//	pSprite->AddFrame(2, 0);
//	pSprite->AddFrame(3, 0);
//	pSprite->AddFrame(4, 0);
//	pBodyRenderer->AddSprite(name + string("TransformBody") , pSprite);
//	pSprite->SaveSprite(name + string("TransformBody") + string(".aclp"));
//	delete pSprite;
//
//	pSprite = new CSprite;
//	pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("TankHeadTransform"));
//	pSprite->SetAtlasGridSize(6, 1);
//	pSprite->SetCellSize(128, 128);
//	pSprite->SetLoop(false);
//	pSprite->SetDestroyOnEnd(false);
//	pSprite->SetSampleRate(2);
//	pSprite->AddFrame(0, 0);
//	pSprite->AddFrame(1, 0);
//	pSprite->AddFrame(2, 0);
//	pSprite->AddFrame(3, 0);
//	pSprite->AddFrame(4, 0);
//	pHeadRenderer->AddSprite(name + string("TransformHead"), pSprite);
//	pSprite->SaveSprite(name + string("TransformHead") + string(".aclp"));
//	delete pSprite;
//
//	pSprite = new CSprite;
//	pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("TankBodyTransform"));
//	pSprite->SetAtlasGridSize(6, 1);
//	pSprite->SetCellSize(128, 128);
//	pSprite->SetLoop(false);
//	pSprite->SetDestroyOnEnd(false);
//	pSprite->SetSampleRate(1);
//	pSprite->AddFrame(5, 0);
//	pBodyRenderer->AddSprite(name + string("TransformedBody"), pSprite);
//	pSprite->SaveSprite(name + string("TransformedBody") + string(".aclp"));
//	delete pSprite;
//
//
//
//}
//GET_SINGLE(CFileStream)->SaveUnit(pUnit, "SiegeTank.unit");
//
//}
//#pragma endregion
//
//
//#pragma region Goliath
//{
//int iTempPositionX = 12;
//int iTempPositionY = 11;
//
//CGameObject* pUnit = new CGameObject("Goliath");
//pUnit->SetPilot(pPlayer->GetComponent<CPlayer>());
//pUnit->SetSelected(false);
//pUnit->SetToAirUnit(false);
//pGroundUnitLayer->AddGameObject(pUnit);
//pUnit->GetTransform()->SetPivot(CVector2(0.5f, 0.6f));
//pUnit->GetTransform()->SetPosition(iTempPositionX * 32, iTempPositionY * 32);
//
//CCircleCollider* pCollider = pUnit->AddComponent<CCircleCollider>();
//CEllipseRenderer* pEllipse = pUnit->AddComponent<CEllipseRenderer>();
//CSpriteRenderer* pBodyRenderer = pUnit->AddComponent<CSpriteRenderer>();
//CSpriteRenderer* pHeadRenderer = pUnit->AddComponent<CSpriteRenderer>();
//CMarineAnimator* pAnimator = pUnit->AddComponent<CMarineAnimator>();
//CMove* pMove = pUnit->AddComponent<CMove>();
//CAttack* pAttack = pUnit->AddComponent<CAttack>();
//CStop* pStop = pUnit->AddComponent<CStop>();
//CHold* pHold = pUnit->AddComponent<CHold>();
//CPatrol* pPatrol = pUnit->AddComponent<CPatrol>();
//CDeffence* pDeffence = pUnit->AddComponent<CDeffence>();
//CUnitStatus* pStatus = pUnit->AddComponent<CUnitStatus>();
//CUnitInfo* pInfo = pUnit->AddComponent<CUnitInfo>();
//
//
//pDeffence->SetDamageDecrement(1);
//pDeffence->SetName("Terran Vehicle Plating");
//pDeffence->SetUpgradeType(UT_TERRAN_MECHANIC_GROUND_DEFFENCE);
//pDeffence->SetValue(0);
//
//pStatus->SetMaxHP(150);
//pStatus->SetMaxMP(0);
//pStatus->SetMaxShield(0);
//pStatus->SetCreateTime(5);
//pStatus->SetRequirement(5, 150, 100, 2);
//pStatus->SetSightRadius(6);
//pStatus->SetHPMaxCondition();
//pStatus->SetMPMaxCondition();
//pStatus->SetShieldMaxCondition();
//
//pInfo->SetAttackComponent(pAttack);
//pInfo->SetDeffenceComponent(pDeffence);
//pInfo->SetShieldComponent(NULL);
//pInfo->SetUnitButtonTexture(GET_SINGLE(CResourceManager)->FindTexture("ControlButton_Icon_TerranGoliath_Normal"));
//pInfo->SetInfoState(IS_NONE);
//
//pCollider->SetRadius(18);
//
//pEllipse->SetMinorAxisLength(18);
//pEllipse->SetMajorAxisScale(1.6f);
//pEllipse->SetColor(0, 255, 0);
//pEllipse->SetThickness(2);
//
//pBodyRenderer->SetSize(128, 128);
//pHeadRenderer->SetSize(128, 128);
//
//pMove->SetMoveSpeed(80);
//pMove->SetStopThresholdRadius(50);
//
//pAttack->SetAttackRange(160);
//pAttack->SetDamage(20);
//pAttack->SetInterval(1.25f);
//pAttack->SetUpgradeIncrease(1);
//pAttack->SetUpgradeType(UT_TERRAN_MECHANIC_GROUND_WAEPON);
//pAttack->SetWeaponName("Fragmentation Grenade");
//{
//	string name = pUnit->GetName();
//
//	for (int i = 0; i < 16; ++i)
//	{
//		char idx[4] = {};
//		itoa(i, idx, 10);
//
//		CSprite* pSprite = new CSprite;
//		pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("GoliathHead"));
//		pSprite->SetAtlasGridSize(16, 11);
//		pSprite->SetCellSize(128, 128);
//		pSprite->SetLoop(true);
//		pSprite->SetSampleRate(15);
//		pSprite->AddFrame(i, 0);
//		pSprite->AddFrame(i, 1);
//		pSprite->AddFrame(i, 2);
//		pSprite->AddFrame(i, 3);
//		pSprite->AddFrame(i, 4);
//		pSprite->AddFrame(i, 5);
//		pSprite->AddFrame(i, 6);
//		pSprite->AddFrame(i, 7);
//		pSprite->AddFrame(i, 8);
//		pSprite->AddFrame(i, 9);
//
//		pHeadRenderer->AddSprite(name + string("Head") + string(idx), pSprite);
//		pSprite->SaveSprite(name + string("Head") + string(idx) + string(".aclp"));
//		delete pSprite;
//
//
//		pSprite = new CSprite;
//		pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("GoliathHead"));
//		pSprite->SetAtlasGridSize(16, 11);
//		pSprite->SetCellSize(128, 128);
//		pSprite->SetLoop(false); 
//		pSprite->SetDestroyOnEnd(false);
//		pSprite->SetSampleRate(15);
//		pSprite->AddFrame(i, 10);
//		pSprite->AddFrame(i, 9);
//		pSprite->AddFrame(i, 10);
//		pSprite->AddFrame(i, 9);
//		pSprite->AddFrame(i, 10);
//		pSprite->AddFrame(i, 9);
//		pHeadRenderer->AddSprite(name + string("HeadAttack") + string(idx), pSprite);
//		pSprite->SaveSprite(name + string("HeadAttack") + string(idx) + string(".aclp"));
//		delete pSprite;
//
//		pSprite = new CSprite;
//		pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("GoliathBody"));
//		pSprite->SetAtlasGridSize(16, 10);
//		pSprite->SetCellSize(128, 128);
//		pSprite->SetLoop(true);
//		pSprite->SetSampleRate(15);
//		pSprite->AddFrame(i, 0);
//		pSprite->AddFrame(i, 1);
//		pSprite->AddFrame(i, 2);
//		pSprite->AddFrame(i, 3);
//		pSprite->AddFrame(i, 4);
//		pSprite->AddFrame(i, 5);
//		pSprite->AddFrame(i, 6);
//		pSprite->AddFrame(i, 7);
//		pSprite->AddFrame(i, 8);
//		pSprite->AddFrame(i, 9);
//
//		pBodyRenderer->AddSprite(name + string("MoveBody") + string(idx), pSprite);
//		pSprite->SaveSprite(name + string("MoveBody") + string(idx) + string(".aclp"));
//		delete pSprite;
//		
//	}
//
//
//
//	CSprite* pSprite = new CSprite;
//	pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("Terran_Explosion_Small"));
//	pSprite->SetAtlasGridSize(10, 0);
//	pSprite->SetCellSize(128, 128);
//	pSprite->SetLoop(false);
//	pSprite->SetDestroyOnEnd(true);
//	pSprite->SetSampleRate(15);
//	pSprite->AddFrame(0, 0);
//	pSprite->AddFrame(1, 0);
//	pSprite->AddFrame(2, 0);
//	pSprite->AddFrame(3, 0);
//	pSprite->AddFrame(4, 0);
//	pSprite->AddFrame(5, 0);
//	pSprite->AddFrame(6, 0);
//	pSprite->AddFrame(7, 0);
//	pSprite->AddFrame(8, 0);
//	pSprite->AddFrame(9, 0);
//	pRenderer->AddSprite(name + string("Death"), pSprite);
//	pSprite->SaveSprite(name + string("Death") + string(".aclp"));
//	delete pSprite;
//}
//
//GET_SINGLE(CFileStream)->SaveUnit(pUnit, "Goliath.unit");
//
//}
//#pragma endregion*/
//
//
//#pragma region Wraith
//{
//	int iTempPositionX = 12;
//	int iTempPositionY = 11;
//
//	CGameObject* pUnit = new CGameObject("Wraith");
//	pUnit->SetPilot(pPlayer->GetComponent<CPlayer>());
//	pUnit->SetSelected(false);
//	pUnit->SetToAirUnit(true); 
//	pAirUnitLayer->AddGameObject(pUnit);
//	pUnit->GetTransform()->SetPivot(CVector2(0.5f, 0.6f));
//	pUnit->GetTransform()->SetPosition(iTempPositionX * 32, iTempPositionY * 32);
//
//	CCircleCollider* pCollider = pUnit->AddComponent<CCircleCollider>();
//	CEllipseRenderer* pEllipse = pUnit->AddComponent<CEllipseRenderer>();
//	CSpriteRenderer* pRenderer = pUnit->AddComponent<CSpriteRenderer>();
//	CMove* pMove = pUnit->AddComponent<CMove>();
//	CAttack* pAttack = pUnit->AddComponent<CAttack>();
//	CStop* pStop = pUnit->AddComponent<CStop>();
//	CHold* pHold = pUnit->AddComponent<CHold>();
//	CPatrol* pPatrol = pUnit->AddComponent<CPatrol>();
//	CDeffence* pDeffence = pUnit->AddComponent<CDeffence>();
//	CUnitStatus* pStatus = pUnit->AddComponent<CUnitStatus>();
//	CUnitInfo* pInfo = pUnit->AddComponent<CUnitInfo>();
//
//
//	pDeffence->SetDamageDecrement(1);
//	pDeffence->SetName("Terran Ship Plating");
//	pDeffence->SetUpgradeType(UT_TERRAN_MECHANIC_AIR_DEFFENCE);
//	pDeffence->SetValue(0);
//
//	pStatus->SetMaxHP(120);
//	pStatus->SetMaxMP(200);
//	pStatus->SetMaxShield(0);
//	pStatus->SetCreateTime(5);
//	pStatus->SetRequirement(5, 150, 100, 2);
//	pStatus->SetSightRadius(6);
//	pStatus->SetHPMaxCondition();
//	pStatus->SetMPMaxCondition();
//	pStatus->SetShieldMaxCondition();
//
//	pInfo->SetAttackComponent(pAttack);
//	pInfo->SetDeffenceComponent(pDeffence);
//	pInfo->SetShieldComponent(NULL);
//	pInfo->SetUnitButtonTexture(GET_SINGLE(CResourceManager)->FindTexture("ControlButton_Icon_TerranWraith_Normal"));
//	pInfo->SetInfoState(IS_NONE);
//
//	pCollider->SetRadius(20);
//
//	pEllipse->SetMinorAxisLength(20);
//	pEllipse->SetMajorAxisScale(1.6f);
//	pEllipse->SetColor(0, 255, 0);
//	pEllipse->SetThickness(2);
//
//	pRenderer->SetSize(64, 64);
//
//	pMove->SetMoveSpeed(100);
//	pMove->SetStopThresholdRadius(50);
//
//	pAttack->SetAttackRange(160);
//	pAttack->SetDamage(8);
//	pAttack->SetInterval(1.25f);
//	pAttack->SetUpgradeIncrease(1);
//	pAttack->SetUpgradeType(UT_TERRAN_MECHANIC_AIR_WAEPON);
//	pAttack->SetWeaponName("Burst Laser");
//
//
//	{
//		string name = pUnit->GetName();
//
//		for (int i = 0; i < 16; ++i)
//		{
//			char idx[4] = {};
//			itoa(i, idx, 10);
//
//			CSprite* pSprite = new CSprite;
//			pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("Wraith"));
//			pSprite->SetAtlasGridSize(16, 1);
//			pSprite->SetCellSize(64, 64);
//			pSprite->SetLoop(true);
//			pSprite->SetSampleRate(1);
//			pSprite->AddFrame(i, 0);
//			pRenderer->AddSprite(name + string("Move") + string(idx), pSprite);
//			pSprite->SaveSprite(name + string("Move") + string(idx) + string(".aclp"));
//			pRenderer->AddSprite(name + string("Stand") + string(idx), pSprite);
//			pSprite->SaveSprite(name + string("Stand") + string(idx) + string(".aclp"));
//			pRenderer->AddSprite(name + string("Attack") + string(idx), pSprite);
//			pSprite->SaveSprite(name + string("Attack") + string(idx) + string(".aclp"));
//			delete pSprite;
//		}
//
//		CSprite* pSprite = new CSprite;
//		pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("Terran_Explosion_Small"));
//		pSprite->SetAtlasGridSize(10, 0);
//		pSprite->SetCellSize(128, 128);
//		pSprite->SetLoop(false);
//		pSprite->SetDestroyOnEnd(true);
//		pSprite->SetSampleRate(15);
//		pSprite->AddFrame(0, 0);
//		pSprite->AddFrame(1, 0);
//		pSprite->AddFrame(2, 0);
//		pSprite->AddFrame(3, 0);
//		pSprite->AddFrame(4, 0);
//		pSprite->AddFrame(5, 0);
//		pSprite->AddFrame(6, 0);
//		pSprite->AddFrame(7, 0);
//		pSprite->AddFrame(8, 0);
//		pSprite->AddFrame(9, 0);
//		pRenderer->AddSprite(name + string("Death"), pSprite);
//		pSprite->SaveSprite(name + string("Death") + string(".aclp"));
//		delete pSprite;
//	}
//}
//#pragma endregion
//
//#pragma region Dropship
//{
//
//int iTempPositionX = 12;
//int iTempPositionY = 12;
//
//CGameObject* pUnit = new CGameObject("Dropship");
//pUnit->SetPilot(pPlayer->GetComponent<CPlayer>());
//pUnit->SetSelected(false);
//pUnit->SetToAirUnit(true);
//pAirUnitLayer->AddGameObject(pUnit);
//pUnit->GetTransform()->SetPivot(CVector2(0.5f, 0.6f));
//pUnit->GetTransform()->SetPosition(iTempPositionX * 32, iTempPositionY * 32);
//
//CCircleCollider* pCollider = pUnit->AddComponent<CCircleCollider>();
//CEllipseRenderer* pEllipse = pUnit->AddComponent<CEllipseRenderer>();
//CSpriteRenderer* pRenderer = pUnit->AddComponent<CSpriteRenderer>();
//CMove* pMove = pUnit->AddComponent<CMove>();
//CStop* pStop = pUnit->AddComponent<CStop>();
//CHold* pHold = pUnit->AddComponent<CHold>();
//CPatrol* pPatrol = pUnit->AddComponent<CPatrol>();
//CDeffence* pDeffence = pUnit->AddComponent<CDeffence>();
//CUnitStatus* pStatus = pUnit->AddComponent<CUnitStatus>();
//CUnitInfo* pInfo = pUnit->AddComponent<CUnitInfo>();
//
//
//pDeffence->SetDamageDecrement(1);
//pDeffence->SetName("Terran Ship Plating");
//pDeffence->SetUpgradeType(UT_TERRAN_MECHANIC_AIR_DEFFENCE);
//pDeffence->SetValue(0);
//
//pStatus->SetMaxHP(150);
//pStatus->SetMaxMP(0);
//pStatus->SetMaxShield(0);
//pStatus->SetCreateTime(5);
//pStatus->SetRequirement(5, 100, 100, 2);
//pStatus->SetSightRadius(6);
//pStatus->SetHPMaxCondition();
//pStatus->SetMPMaxCondition();
//pStatus->SetShieldMaxCondition();
//
//pInfo->SetAttackComponent(NULL);
//pInfo->SetDeffenceComponent(pDeffence);
//pInfo->SetShieldComponent(NULL);
//pInfo->SetUnitButtonTexture(GET_SINGLE(CResourceManager)->FindTexture("ControlButton_Icon_TerranDropship_Normal"));
//pInfo->SetInfoState(IS_NONE);
//
//pCollider->SetRadius(20);
//
//pEllipse->SetMinorAxisLength(20);
//pEllipse->SetMajorAxisScale(1.6f);
//pEllipse->SetColor(0, 255, 0);
//pEllipse->SetThickness(2);
//
//pRenderer->SetSize(60, 60);
//
//pMove->SetMoveSpeed(50);
//pMove->SetStopThresholdRadius(32);
//{
//	string name = pUnit->GetName();
//
//	for (int i = 0; i < 16; ++i)
//	{
//		char idx[4] = {};
//		itoa(i, idx, 10);
//
//		CSprite* pSprite = new CSprite;
//		pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("Dropship"));
//		pSprite->SetAtlasGridSize(16, 1);
//		pSprite->SetCellSize(60, 60);
//		pSprite->SetLoop(true);
//		pSprite->SetSampleRate(1);
//		pSprite->AddFrame(i, 0);
//		pRenderer->AddSprite(name + string("Move") + string(idx), pSprite);
//		pSprite->SaveSprite(name + string("Move") + string(idx) + string(".aclp"));
//		pRenderer->AddSprite(name + string("Stand") + string(idx), pSprite);
//		pSprite->SaveSprite(name + string("Stand") + string(idx) + string(".aclp"));
//		delete pSprite;
//	}
//
//	CSprite* pSprite = new CSprite;
//	pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("Terran_Explosion_Small"));
//	pSprite->SetAtlasGridSize(10, 0);
//	pSprite->SetCellSize(128, 128);
//	pSprite->SetLoop(false);
//	pSprite->SetDestroyOnEnd(true);
//	pSprite->SetSampleRate(15);
//	pSprite->AddFrame(0, 0);
//	pSprite->AddFrame(1, 0);
//	pSprite->AddFrame(2, 0);
//	pSprite->AddFrame(3, 0);
//	pSprite->AddFrame(4, 0);
//	pSprite->AddFrame(5, 0);
//	pSprite->AddFrame(6, 0);
//	pSprite->AddFrame(7, 0);
//	pSprite->AddFrame(8, 0);
//	pSprite->AddFrame(9, 0);
//	pRenderer->AddSprite(name + string("Death"), pSprite);
//	pSprite->SaveSprite(name + string("Death") + string(".aclp"));
//	delete pSprite;
//}
//
//GET_SINGLE(CFileStream)->SaveUnit(pUnit, "Dropship.unit");
//
//}
//#pragma endregion
//
//
//#pragma region Science Vessel
//{
//
//int iTempPositionX = 12;
//int iTempPositionY = 12;
//
//CGameObject* pUnit = new CGameObject("Science Vessel");
//pUnit->SetPilot(pPlayer->GetComponent<CPlayer>());
//pUnit->SetSelected(false);
//pUnit->SetToAirUnit(true);
//pAirUnitLayer->AddGameObject(pUnit);
//pUnit->GetTransform()->SetPivot(CVector2(0.5f, 0.6f));
//pUnit->GetTransform()->SetPosition(iTempPositionX * 32, iTempPositionY * 32);
//
//CCircleCollider* pCollider = pUnit->AddComponent<CCircleCollider>();
//CEllipseRenderer* pEllipse = pUnit->AddComponent<CEllipseRenderer>();
//CSpriteRenderer* pRenderer = pUnit->AddComponent<CSpriteRenderer>();
//CMove* pMove = pUnit->AddComponent<CMove>();
//CStop* pStop = pUnit->AddComponent<CStop>();
//CHold* pHold = pUnit->AddComponent<CHold>();
//CPatrol* pPatrol = pUnit->AddComponent<CPatrol>();
//CDeffence* pDeffence = pUnit->AddComponent<CDeffence>();
//CUnitStatus* pStatus = pUnit->AddComponent<CUnitStatus>();
//CUnitInfo* pInfo = pUnit->AddComponent<CUnitInfo>();
//
//
//pDeffence->SetDamageDecrement(1);
//pDeffence->SetName("Terran Ship Plating");
//pDeffence->SetUpgradeType(UT_TERRAN_MECHANIC_AIR_DEFFENCE);
//pDeffence->SetValue(0);
//
//pStatus->SetMaxHP(200);
//pStatus->SetMaxMP(200);
//pStatus->SetMaxShield(0);
//pStatus->SetCreateTime(5);
//pStatus->SetRequirement(5, 100, 100, 2);
//pStatus->SetSightRadius(6);
//pStatus->SetHPMaxCondition();
//pStatus->SetMPMaxCondition();
//pStatus->SetShieldMaxCondition();
//
//pInfo->SetAttackComponent(NULL);
//pInfo->SetDeffenceComponent(pDeffence);
//pInfo->SetShieldComponent(NULL);
//pInfo->SetUnitButtonTexture(GET_SINGLE(CResourceManager)->FindTexture("ControlButton_Icon_TerranScienceVessel_Normal"));
//pInfo->SetInfoState(IS_NONE);
//
//pCollider->SetRadius(20);
//
//pEllipse->SetMinorAxisLength(20);
//pEllipse->SetMajorAxisScale(1.6f);
//pEllipse->SetColor(0, 255, 0);
//pEllipse->SetThickness(2);
//
//pRenderer->SetSize(96, 128);
//
//pMove->SetMoveSpeed(100);
//pMove->SetStopThresholdRadius(32);
//{
//	string name = pUnit->GetName();
//
//	for (int i = 0; i < 16; ++i)
//	{
//		char idx[4] = {};
//		itoa(i, idx, 10);
//
//		CSprite* pSprite = new CSprite;
//		pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("ScienceVessel"));
//		pSprite->SetAtlasGridSize(1, 1);
//		pSprite->SetCellSize(96, 128);
//		pSprite->SetLoop(true);
//		pSprite->SetSampleRate(1);
//		pSprite->AddFrame(0, 0);
//		pRenderer->AddSprite(name + string("Move") + string(idx), pSprite);
//		pSprite->SaveSprite(name + string("Move") + string(idx) + string(".aclp"));
//		pRenderer->AddSprite(name + string("Stand") + string(idx), pSprite);
//		pSprite->SaveSprite(name + string("Stand") + string(idx) + string(".aclp"));
//		delete pSprite;
//	}
//
//	CSprite* pSprite = new CSprite;
//	pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("Terran_Explosion_Small"));
//	pSprite->SetAtlasGridSize(10, 0);
//	pSprite->SetCellSize(128, 128);
//	pSprite->SetLoop(false);
//	pSprite->SetDestroyOnEnd(true);
//	pSprite->SetSampleRate(15);
//	pSprite->AddFrame(0, 0);
//	pSprite->AddFrame(1, 0);
//	pSprite->AddFrame(2, 0);
//	pSprite->AddFrame(3, 0);
//	pSprite->AddFrame(4, 0);
//	pSprite->AddFrame(5, 0);
//	pSprite->AddFrame(6, 0);
//	pSprite->AddFrame(7, 0);
//	pSprite->AddFrame(8, 0);
//	pSprite->AddFrame(9, 0);
//	pRenderer->AddSprite(name + string("Death"), pSprite);
//	pSprite->SaveSprite(name + string("Death") + string(".aclp"));
//	delete pSprite;
//}
//
//GET_SINGLE(CFileStream)->SaveUnit(pUnit, "ScienceVessel.unit");
//
//}
//#pragma endregion
//
//#pragma region Battlecruiser
//{
//
//int iTempPositionX = 12;
//int iTempPositionY = 11;
//
//CGameObject* pUnit = new CGameObject("Battlecruiser");
//pUnit->SetPilot(pPlayer->GetComponent<CPlayer>());
//pUnit->SetSelected(false);
//pUnit->SetToAirUnit(true);
//pAirUnitLayer->AddGameObject(pUnit);
//pUnit->GetTransform()->SetPivot(CVector2(0.5f, 0.6f));
//pUnit->GetTransform()->SetPosition(iTempPositionX * 32, iTempPositionY * 32);
//
//CCircleCollider* pCollider = pUnit->AddComponent<CCircleCollider>();
//CEllipseRenderer* pEllipse = pUnit->AddComponent<CEllipseRenderer>();
//CSpriteRenderer* pRenderer = pUnit->AddComponent<CSpriteRenderer>();
//CMove* pMove = pUnit->AddComponent<CMove>();
//CAttack* pAttack = pUnit->AddComponent<CAttack>();
//CStop* pStop = pUnit->AddComponent<CStop>();
//CHold* pHold = pUnit->AddComponent<CHold>();
//CPatrol* pPatrol = pUnit->AddComponent<CPatrol>();
//CDeffence* pDeffence = pUnit->AddComponent<CDeffence>();
//CUnitStatus* pStatus = pUnit->AddComponent<CUnitStatus>();
//CUnitInfo* pInfo = pUnit->AddComponent<CUnitInfo>();
//
//
//pDeffence->SetDamageDecrement(1);
//pDeffence->SetName("Terran Ship Plating");
//pDeffence->SetUpgradeType(UT_TERRAN_MECHANIC_AIR_DEFFENCE);
//pDeffence->SetValue(0);
//
//pStatus->SetMaxHP(500);
//pStatus->SetMaxMP(200);
//pStatus->SetMaxShield(0);
//pStatus->SetCreateTime(5);
//pStatus->SetRequirement(5, 400, 300, 6);
//pStatus->SetSightRadius(6);
//pStatus->SetHPMaxCondition();
//pStatus->SetMPMaxCondition();
//pStatus->SetShieldMaxCondition();
//
//pInfo->SetAttackComponent(pAttack);
//pInfo->SetDeffenceComponent(pDeffence);
//pInfo->SetShieldComponent(NULL);
//pInfo->SetUnitButtonTexture(GET_SINGLE(CResourceManager)->FindTexture("ControlButton_Icon_TerranBattlecruiser_Normal"));
//pInfo->SetInfoState(IS_NONE);
//
//pCollider->SetRadius(32);
//
//pEllipse->SetMinorAxisLength(32);
//pEllipse->SetMajorAxisScale(1.6f);
//pEllipse->SetColor(0, 255, 0);
//pEllipse->SetThickness(2);
//
//pRenderer->SetSize(120, 120);
//
//pMove->SetMoveSpeed(50);
//pMove->SetStopThresholdRadius(50);
//
//pAttack->SetAttackRange(256);
//pAttack->SetDamage(8);
//pAttack->SetInterval(1.25f);
//pAttack->SetUpgradeIncrease(1);
//pAttack->SetUpgradeType(UT_TERRAN_MECHANIC_AIR_WAEPON);
//pAttack->SetWeaponName("Burst Laser");
//
//
//{
//	string name = pUnit->GetName();
//
//	for (int i = 0; i < 16; ++i)
//	{
//		char idx[4] = {};
//		itoa(i, idx, 10);
//
//		CSprite* pSprite = new CSprite;
//		pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("Battlecruiser"));
//		pSprite->SetAtlasGridSize(16, 1);
//		pSprite->SetCellSize(120, 120);
//		pSprite->SetLoop(true);
//		pSprite->SetSampleRate(1);
//		pSprite->AddFrame(i, 0);
//		pRenderer->AddSprite(name + string("Move") + string(idx), pSprite);
//		pSprite->SaveSprite(name + string("Move") + string(idx) + string(".aclp"));
//		pRenderer->AddSprite(name + string("Stand") + string(idx), pSprite);
//		pSprite->SaveSprite(name + string("Stand") + string(idx) + string(".aclp"));
//		pRenderer->AddSprite(name + string("Attack") + string(idx), pSprite);
//		pSprite->SaveSprite(name + string("Attack") + string(idx) + string(".aclp"));
//		delete pSprite;
//	}
//
//	CSprite* pSprite = new CSprite;
//	pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("Terran_Explosion_Small"));
//	pSprite->SetAtlasGridSize(10, 0);
//	pSprite->SetCellSize(128, 128);
//	pSprite->SetLoop(false);
//	pSprite->SetDestroyOnEnd(true);
//	pSprite->SetSampleRate(15);
//	pSprite->AddFrame(0, 0);
//	pSprite->AddFrame(1, 0);
//	pSprite->AddFrame(2, 0);
//	pSprite->AddFrame(3, 0);
//	pSprite->AddFrame(4, 0);
//	pSprite->AddFrame(5, 0);
//	pSprite->AddFrame(6, 0);
//	pSprite->AddFrame(7, 0);
//	pSprite->AddFrame(8, 0);
//	pSprite->AddFrame(9, 0);
//	pRenderer->AddSprite(name + string("Death"), pSprite);
//	pSprite->SaveSprite(name + string("Death") + string(".aclp"));
//	delete pSprite;
//}
//
//GET_SINGLE(CFileStream)->SaveUnit(pUnit, "Battlecruiser.unit");
//
//}
//#pragma endregion
//
//
//#pragma endregion
//


#pragma region CreateCamera
	{
		GetCamera()->GameObject()->AddComponent<CCameraMove>();
	}
#pragma endregion

#pragma region CreateCursor
	{
		CGameObject* pCursor = new CGameObject("Cursor");// GET_SINGLE(CResourceManager)->FindUnit("Cursor")->clone();
		pSystemLayer->AddGameObject(pCursor);
		pCursor->SetPilot(pPlayer->GetComponent<CPlayer>());
		CSpriteRenderer* pRenderer = pCursor->AddComponent<CSpriteRenderer>();		
		pCursor->AddComponent<CCursorMove>();
		pCursor->AddComponent<CCursor>();
		ShowCursor(false);

		pRenderer->SetSize(80, 80);

		CSprite* pSprite = new CSprite;
		pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("Cursor"));
		pSprite->SetCellSize(80, 80);
		pSprite->SetAtlasGridSize(16, 16);
		pSprite->SetSampleRate(10);
		pSprite->SetLoop(true);
		pSprite->AddFrame(CVector2(0, 0));
		pSprite->AddFrame(CVector2(1, 0));
		pSprite->AddFrame(CVector2(2, 0));
		pSprite->AddFrame(CVector2(3, 0));
		pSprite->AddFrame(CVector2(4, 0));
		pRenderer->AddSprite("CursorNormal", pSprite);
		pSprite->SaveSprite("CursorNormal.aclp");
		delete pSprite;


		pSprite = new CSprite;
		pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("Cursor"));
		pSprite->SetCellSize(80, 80);
		pSprite->SetAtlasGridSize(16, 16);
		pSprite->SetSampleRate(10);
		pSprite->SetLoop(true);
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
		pSprite->AddFrame(CVector2(10, 3));
		pSprite->AddFrame(CVector2(11, 3));
		pSprite->AddFrame(CVector2(12, 3));
		pSprite->AddFrame(CVector2(13, 3));
		pRenderer->AddSprite("Cursor_Normal_Local_Over", pSprite);
		pSprite->SaveSprite("Cursor_Normal_Local_Over.aclp");
		delete pSprite;


		pSprite = new CSprite;
		pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("Cursor"));
		pSprite->SetCellSize(80, 80);
		pSprite->SetAtlasGridSize(16, 16);
		pSprite->SetSampleRate(10);
		pSprite->SetLoop(true);
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
		pSprite->AddFrame(CVector2(10, 4));
		pSprite->AddFrame(CVector2(11, 4));
		pSprite->AddFrame(CVector2(12, 4));
		pSprite->AddFrame(CVector2(13, 4));
		pRenderer->AddSprite("Cursor_Normal_Enemy_Over", pSprite);
		pSprite->SaveSprite("Cursor_Normal_Enemy_Over.aclp");
		delete pSprite;

		pSprite = new CSprite;
		pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("Cursor"));
		pSprite->SetCellSize(80, 80);
		pSprite->SetAtlasGridSize(16, 16);
		pSprite->SetSampleRate(10);
		pSprite->SetLoop(true);
		pSprite->AddFrame(CVector2(0, 5));
		pSprite->AddFrame(CVector2(1, 5));
		pSprite->AddFrame(CVector2(2, 5));
		pSprite->AddFrame(CVector2(3, 5));
		pSprite->AddFrame(CVector2(4, 5));
		pSprite->AddFrame(CVector2(5, 5));
		pSprite->AddFrame(CVector2(6, 5));
		pSprite->AddFrame(CVector2(7, 5));
		pSprite->AddFrame(CVector2(8, 5));
		pSprite->AddFrame(CVector2(9, 5));
		pSprite->AddFrame(CVector2(10, 5));
		pSprite->AddFrame(CVector2(11, 5));
		pSprite->AddFrame(CVector2(12, 5));
		pSprite->AddFrame(CVector2(13, 5));
		pRenderer->AddSprite("Cursor_Normal_Neutral_Over", pSprite);
		pSprite->SaveSprite("Cursor_Normal_Neutral_Over.aclp");
		delete pSprite;

		pSprite = new CSprite;
		pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("Cursor"));
		pSprite->SetCellSize(80, 80);
		pSprite->SetAtlasGridSize(16, 16);
		pSprite->SetSampleRate(1);
		pSprite->SetLoop(true);
		pSprite->AddFrame(CVector2(0, 6));
		pRenderer->AddSprite("Cursor_Request_Local_Normal", pSprite);
		pSprite->SaveSprite("Cursor_Request_Local_Normal.aclp");
		delete pSprite;

		pSprite = new CSprite;
		pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("Cursor"));
		pSprite->SetCellSize(80, 80);
		pSprite->SetAtlasGridSize(16, 16);
		pSprite->SetSampleRate(10);
		pSprite->SetLoop(true);
		pSprite->AddFrame(CVector2(0, 6));
		pSprite->AddFrame(CVector2(1, 6));
		pRenderer->AddSprite("Cursor_Request_Local_Over", pSprite);
		pSprite->SaveSprite("Cursor_Request_Local_Over.aclp");
		delete pSprite;

		pSprite = new CSprite;
		pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("Cursor"));
		pSprite->SetCellSize(80, 80);
		pSprite->SetAtlasGridSize(16, 16);
		pSprite->SetSampleRate(1);
		pSprite->SetLoop(true);
		pSprite->AddFrame(CVector2(2, 6));
		pRenderer->AddSprite("Cursor_Request_Neutral_Normal", pSprite);
		pSprite->SaveSprite("Cursor_Request_Neutral_Normal.aclp");
		delete pSprite;

		pSprite = new CSprite;
		pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("Cursor"));
		pSprite->SetCellSize(80, 80);
		pSprite->SetAtlasGridSize(16, 16);
		pSprite->SetSampleRate(10);
		pSprite->SetLoop(true);
		pSprite->AddFrame(CVector2(2, 6));
		pSprite->AddFrame(CVector2(3, 6));
		pRenderer->AddSprite("Cursor_Request_Neutral_Over", pSprite);
		pSprite->SaveSprite("Cursor_Request_Neutral_Over.aclp");
		delete pSprite;

		pSprite = new CSprite;
		pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("Cursor"));
		pSprite->SetCellSize(80, 80);
		pSprite->SetAtlasGridSize(16, 16);
		pSprite->SetSampleRate(1);
		pSprite->SetLoop(true);
		pSprite->AddFrame(CVector2(4, 6));
		pRenderer->AddSprite("Cursor_Request_Enemy_Normal", pSprite);
		pSprite->SaveSprite("Cursor_Request_Enemy_Normal.aclp");
		delete pSprite;

		pSprite = new CSprite;
		pSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("Cursor"));
		pSprite->SetCellSize(80, 80);
		pSprite->SetAtlasGridSize(16, 16);
		pSprite->SetSampleRate(10);
		pSprite->SetLoop(true);
		pSprite->AddFrame(CVector2(4, 6));
		pSprite->AddFrame(CVector2(5, 6));
		pRenderer->AddSprite("Cursor_Request_Enemy_Over", pSprite);
		pSprite->SaveSprite("Cursor_Request_Enemy_Over.aclp");
		delete pSprite;

		pRenderer->ChangeCurrentClip("CursorNormal");
	}
#pragma endregion
	
	//{
	//	CGameObject* pGeyser = GET_SINGLE(CResourceManager)->FindUnit("VespeneGeyser")->clone();
	//	pGroundUnitLayer->AddGameObject(pGeyser);
	//	pGeyser->SetPilot(NULL);
	//	pGeyser->SetSelected(false);
	//	list<CSpriteRenderer*> componentList =	pGeyser->GetComponents<CSpriteRenderer>();
	//	list<CSpriteRenderer*>::iterator iter;
	//	list<CSpriteRenderer*>::iterator iterEnd = componentList.end();
	//	for (iter = componentList.begin(); iter != iterEnd; ++iter)
	//	{
	//		(*iter)->SetDefaultClip();
	//	}
	//	
	//}
#pragma endregion


#pragma region CreateUI
	{
		{	
			CGameObject* pIcon = new CGameObject("MineralIcon");
			pIcon->SetPilot(pPlayer->GetComponent<CPlayer>());
			pUIBottomLayer->AddGameObject(pIcon);
			pIcon->GetTransform()->SetPivot(0.5f, 0.5f);
			pIcon->GetTransform()->SetPosition(GET_SINGLE(CCore)->GetScreenSize().x * 0.76f, 16);

			CUIRenderer* pRenderer = pIcon->AddComponent<CUIRenderer>();
			pRenderer->SetTexture(GET_SINGLE(CResourceManager)->FindTexture("TopPanel_Icon_Mineral"));
			pRenderer->SetSize(20, 20);

			CTextRenderer* pText = pIcon->AddComponent<CTextRenderer>();
			pText->SetColor(32, 200, 32);
			pText->SetTextSize(18);
			pText->SetPosition(pIcon->GetTransform()->GetPosition() + CVector2(15, -8));
			pText->SetAlign(TA_LEFT);


			pPlayer->GetComponent<CPlayer>()->SetMineralTextObject(pIcon);
		}

		{
			CGameObject* pIcon = new CGameObject("GasIcon");
			pIcon->SetPilot(pPlayer->GetComponent<CPlayer>());
			pUIBottomLayer->AddGameObject(pIcon);
			pIcon->GetTransform()->SetPivot(0.5f, 0.5f);
			pIcon->GetTransform()->SetPosition(GET_SINGLE(CCore)->GetScreenSize().x * 0.84f, 16);

			CTextRenderer* pText = pIcon->AddComponent<CTextRenderer>();
			pText->SetColor(32, 200, 32);
			pText->SetTextSize(18);
			pText->SetPosition(pIcon->GetTransform()->GetPosition() + CVector2(15, -8));
			pText->SetAlign(TA_LEFT);

			CUIRenderer* pRenderer = pIcon->AddComponent<CUIRenderer>();
			switch (pPlayer->GetComponent<CPlayer>()->GetRaceType())
			{
			case RT_TERRAN:
				pRenderer->SetTexture(GET_SINGLE(CResourceManager)->FindTexture("TopPanel_Icon_Terran_VespeneGas"));
				break;
			case RT_PROTOSS:
				pRenderer->SetTexture(GET_SINGLE(CResourceManager)->FindTexture("TopPanel_Icon_Protoss_VespeneGas"));
				break;
			case RT_ZERG:
				pRenderer->SetTexture(GET_SINGLE(CResourceManager)->FindTexture("TopPanel_Icon_Zerg_VespeneGas"));
				break;
			default:
				break;
			}
			pRenderer->SetSize(20, 20);


			pPlayer->GetComponent<CPlayer>()->SetGasTextObject(pIcon);
		}

		{
			CGameObject* pIcon = new CGameObject("SupplyIcon");
			pIcon->SetPilot(pPlayer->GetComponent<CPlayer>());
			pUIBottomLayer->AddGameObject(pIcon);
			pIcon->GetTransform()->SetPivot(0.5f, 0.5f);
			pIcon->GetTransform()->SetPosition(GET_SINGLE(CCore)->GetScreenSize().x * 0.92f, 16);

			CTextRenderer* pText = pIcon->AddComponent<CTextRenderer>();
			pText->SetColor(32, 200, 32);
			pText->SetTextSize(18);
			pText->SetPosition(pIcon->GetTransform()->GetPosition() + CVector2(15, -8));
			pText->SetAlign(TA_LEFT);

			CUIRenderer* pRenderer = pIcon->AddComponent<CUIRenderer>();
			switch (pPlayer->GetComponent<CPlayer>()->GetRaceType())
			{
			case RT_TERRAN:
				pRenderer->SetTexture(GET_SINGLE(CResourceManager)->FindTexture("TopPanel_Icon_Terran_Supply"));
				break;
			case RT_PROTOSS:
				pRenderer->SetTexture(GET_SINGLE(CResourceManager)->FindTexture("TopPanel_Icon_Protoss_Supply"));
				break;
			case RT_ZERG:
				pRenderer->SetTexture(GET_SINGLE(CResourceManager)->FindTexture("TopPanel_Icon_Zerg_Supply"));
				break;
			default:
				break;
			}
			pRenderer->SetSize(20, 20);

			pPlayer->GetComponent<CPlayer>()->SetSupplyTextObject(pIcon);
		}	
	}
	
	//Bottom
	{
		//종족 별로 다르게 해야함.
		CGameObject* pGameObject = new CGameObject("ConsolePanel");
		pGameObject->SetPilot(pPlayer->GetComponent<CPlayer>());
		pUIBottomLayer->AddGameObject(pGameObject);
		pGameObject->GetTransform()->SetPivot(0.5f, 1.0f);
		pGameObject->GetTransform()->SetPosition(GET_SINGLE(CCore)->GetScreenSize().x / 2, GET_SINGLE(CCore)->GetScreenSize().y);

		CUIRenderer* pRenderer = pGameObject->AddComponent<CUIRenderer>();

		switch (pPlayer->GetComponent<CPlayer>()->GetRaceType())
		{
		case RT_RANDOM:
		{
			srand(time(0));
			int i = rand() % 3;
			switch (i)
			{
			case RT_TERRAN:
			{
				CTexture* pTexture = GET_SINGLE(CResourceManager)->FindTexture("ConsolePanel_Terran");
				pRenderer->SetTexture(pTexture);
				pRenderer->SetSize(pTexture->GetTextureInfo().bmWidth, pTexture->GetTextureInfo().bmHeight);
				pPlayer->GetComponent<CPlayer>()->SetRaceType(RT_TERRAN);

			}break;
			case RT_PROTOSS:
			{
				CTexture* pTexture = GET_SINGLE(CResourceManager)->FindTexture("ConsolePanel_Protoss");
				pRenderer->SetTexture(pTexture);
				pRenderer->SetSize(pTexture->GetTextureInfo().bmWidth, pTexture->GetTextureInfo().bmHeight);
				pPlayer->GetComponent<CPlayer>()->SetRaceType(RT_PROTOSS);
			}break;
			case RT_ZERG:
			{
				CTexture* pTexture = GET_SINGLE(CResourceManager)->FindTexture("ConsolePanel_Zerg");
				pRenderer->SetTexture(pTexture);
				pRenderer->SetSize(pTexture->GetTextureInfo().bmWidth, pTexture->GetTextureInfo().bmHeight);
				pPlayer->GetComponent<CPlayer>()->SetRaceType(RT_ZERG);
			}break;
			default:
				break;
			}
		}
		break;
		case RT_TERRAN:
		{
			CTexture* pTexture = GET_SINGLE(CResourceManager)->FindTexture("ConsolePanel_Terran");
			pRenderer->SetTexture(pTexture);
			pRenderer->SetSize(pTexture->GetTextureInfo().bmWidth, pTexture->GetTextureInfo().bmHeight);
		}break;
		case RT_PROTOSS:
		{
			CTexture* pTexture = GET_SINGLE(CResourceManager)->FindTexture("ConsolePanel_Protoss");
			pRenderer->SetTexture(pTexture);
			pRenderer->SetSize(pTexture->GetTextureInfo().bmWidth, pTexture->GetTextureInfo().bmHeight);
		}break;
		case RT_ZERG:
		{
			CTexture* pTexture = GET_SINGLE(CResourceManager)->FindTexture("ConsolePanel_Zerg");
			pRenderer->SetTexture(pTexture);
			pRenderer->SetSize(pTexture->GetTextureInfo().bmWidth, pTexture->GetTextureInfo().bmHeight);
		}break;
		default:
			break;
		}


	}
	//Buttons
	{
		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				char cIndex[4];
				itoa((i * 3 + j), cIndex, 10);
				CGameObject* pGameObject = new CGameObject(string("ControlPanelButton") + string(cIndex));
				pGameObject->SetPilot(pPlayer->GetComponent<CPlayer>());
				pUIMiddleLayer->AddGameObject(pGameObject);
				pGameObject->GetTransform()->SetPosition(945 + j * 69.5f, 562.5f + i * 60);
				CButtonCollider* pCollider = pGameObject->AddComponent<CButtonCollider>();
				CControlButton* pButton = pGameObject->AddComponent<CControlButton>();
				pButton->SetSize(50, 50);
				pCollider->SetSize(50, 50);
	
				GET_SINGLE(CConsoleButtonManager)->AddControlPanelButton(pGameObject, i * 3 + j);
			}
		}
	}
#pragma endregion

	//for (int i = 0; i < 32; ++i)
	//{
	//	for (int j = 0; j < 32; ++j)
	//	{
	//		CGameObject* pMarine = GET_SINGLE(CResourceManager)->FindUnit("Marine")->clone();
	//		pGroundUnitLayer->AddGameObject(pMarine);
	//		pMarine->SetSelected(false);
	//		CSpriteRenderer* pRenderer = pMarine->GetComponent<CSpriteRenderer>();
	//		CTexture* pOriginTexture = pRenderer->FindSprite("MarineMove0")->GetAtlasTexture();
	//		CTexture* pTeamColorTexture = GET_SINGLE(CFileStream)->SetTeamColor("WhiteRight", "White\\Terran\\marine_right.bmp", pOriginTexture, 0.796875f, 0.875f, 0.8125f);
	//		pRenderer->ChangeSpriteTexture("MarineMove0", pTeamColorTexture);
	//		pRenderer->ChangeCurrentClip("MarineMove0");
	//		pMarine->SetToAirUnit(false);
	//		pMarine->GetComponent<CCircleCollider>()->SetRadius(15);
	//		pMarine->GetComponent<CCircleCollider>()->SetTileCollisionRadius(15);
	//
	//		CMove* pMove = pMarine->AddComponent<CMove>();
	//		pMove->SetMoveSpeed(100);
	//
	//		CCollider* pCollider = pMarine->GetComponent<CCollider>();
	//		AddCollider(pCollider);
	//
	//		
	//
	//		pMarine->GetTransform()->SetPosition(1000 + j * 28,1000+ i * 28);
	//	}	
	//}


	/*for (int i = 0; i < 5; ++i)
		for (int j = 0; j < 5; ++j)
		{
			CGameObject* pMarine = new CGameObject("Marine");
			pMarine->SetPilot(pPlayer->GetComponent<CPlayer>());
			pMarine->SetSelected(false);
			pMarine->SetToAirUnit(false);
			pGroundUnitLayer->AddGameObject(pMarine);
			pMarine->GetTransform()->SetPivot(CVector2(0.5f, 0.6f));
			pMarine->GetTransform()->SetPosition(300 + j * 32, 300 + i * 32);

			CEllipseRenderer* pEllipse = pMarine->AddComponent<CEllipseRenderer>();
			CSpriteRenderer* pRenderer = pMarine->AddComponent<CSpriteRenderer>();
			CCircleCollider* pCollider = pMarine->AddComponent<CCircleCollider>();
			CMove*			pMove = pMarine->AddComponent<CMove>();

			pRenderer->SetSize(CVector2(64, 64));

			pCollider->SetRadius(15);
			pCollider->SetTileCollisionRadius(15);

			pEllipse->SetLocalPosition(0, 2);
			pEllipse->SetThickness(2);
			pEllipse->SetMinorAxisLength(8);
			pEllipse->SetMajorAxisScale(1.6);
			pMove->SetMoveSpeed(100);


			//인게임 런타임중에 clone으로 생성하는 경우에는 추가해 줄 필요 없음
			//AddCollider(pCollider);
			//pAtlasTexture = GET_SINGLE(CFileStream)->SetTeamColor("RedRight", "Red\\Terran\\marine_right.bmp", pAtlasTexture, 0.953125f, 0.015625f, 0.015625f);
			//pAtlasTexture = GET_SINGLE(CFileStream)->SetTeamColor("BlueRight", "Blue\\Terran\\marine_right.bmp", pAtlasTexture, 0.046875f, 0.28125f, 0.796875f);
			//pAtlasTexture = GET_SINGLE(CFileStream)->SetTeamColor("TealRight", "Teal\\Terran\\marine_right.bmp", pAtlasTexture, 0.171875f, 0.703125f, 0.578125f);
			//pAtlasTexture = GET_SINGLE(CFileStream)->SetTeamColor("PurpleRight", "Purple\\Terran\\marine_right.bmp", pAtlasTexture, 0.53125f, 0.25f, 0.609375f);
			//pAtlasTexture = GET_SINGLE(CFileStream)->SetTeamColor("OrangeRight", "Orange\\Terran\\marine_right.bmp", pAtlasTexture, 0.96875f, 0.546875f, 0.078125f);
			//pAtlasTexture = GET_SINGLE(CFileStream)->SetTeamColor("BrownRight", "Brown\\Terran\\marine_right.bmp", pAtlasTexture, 0.4375f, 0.1875f, 0.078125f);
			//pAtlasTexture = GET_SINGLE(CFileStream)->SetTeamColor("WhiteRight", "White\\Terran\\marine_right.bmp", pAtlasTexture, 0.796875f, 0.875f, 0.8125f);
			//pAtlasTexture = GET_SINGLE(CFileStream)->SetTeamColor("YellowRight", "Yellow\\Terran\\marine_right.bmp", pAtlasTexture, 0.984375f, 0.984375f, 0.21875f);
			//CTexture* pOriginTexture = pRenderer->FindSprite("MarineAttack0")->GetAtlasTexture();
			//CTexture* pTeamColorTexture = GET_SINGLE(CFileStream)->SetTeamColor("WhiteRight", "White\\Terran\\marine_right.bmp", pOriginTexture, 0.796875f, 0.875f, 0.8125f);
			//pRenderer->ChangeSpriteTexture("MarineAttack0", pTeamColorTexture);
			//pRenderer->ChangeCurrentClip("MarineAttack0");

			CSprite* pSprite = new CSprite;
			CTexture* pAtlasTexture = GET_SINGLE(CResourceManager)->FindTexture("MarineRight");
			pSprite->SetAtlas(pAtlasTexture);
			pSprite->SetCellSize(CVector2(64, 64));
			pSprite->SetAtlasGridSize(CVector2(17, 14));
			pSprite->SetSampleRate(15);
			pSprite->SetLoop(true);
			pSprite->AddFrame(CVector2(0, 4));
			pSprite->AddFrame(CVector2(0, 5));
			pSprite->AddFrame(CVector2(0, 6));
			pSprite->AddFrame(CVector2(0, 7));
			pSprite->AddFrame(CVector2(0, 8));
			pSprite->AddFrame(CVector2(0, 9));
			pSprite->AddFrame(CVector2(0, 10));
			pSprite->AddFrame(CVector2(0, 11));
			pSprite->AddFrame(CVector2(0, 12));
			pRenderer->AddSprite("MarineMove0", pSprite);
			pSprite->SaveSprite("MarineMove0.aclp");

			delete pSprite;

			pSprite = new CSprite;
			pSprite->SetAtlas(pAtlasTexture);
			pSprite->SetCellSize(CVector2(64, 64));
			pSprite->SetAtlasGridSize(CVector2(17, 14));
			pSprite->SetSampleRate(15);
			pSprite->SetLoop(true);
			pSprite->AddFrame(CVector2(2, 4));
			pSprite->AddFrame(CVector2(2, 5));
			pSprite->AddFrame(CVector2(2, 6));
			pSprite->AddFrame(CVector2(2, 7));
			pSprite->AddFrame(CVector2(2, 8));
			pSprite->AddFrame(CVector2(2, 9));
			pSprite->AddFrame(CVector2(2, 10));
			pSprite->AddFrame(CVector2(2, 11));
			pSprite->AddFrame(CVector2(2, 12));
			pRenderer->AddSprite("MarineMove1", pSprite);
			pSprite->SaveSprite("MarineMove1.aclp");
			delete pSprite;


			pSprite = new CSprite;
			pSprite->SetAtlas(pAtlasTexture);
			pSprite->SetCellSize(CVector2(64, 64));
			pSprite->SetAtlasGridSize(CVector2(17, 14));
			pSprite->SetSampleRate(15);
			pSprite->SetLoop(true);
			pSprite->AddFrame(CVector2(4, 4));
			pSprite->AddFrame(CVector2(4, 5));
			pSprite->AddFrame(CVector2(4, 6));
			pSprite->AddFrame(CVector2(4, 7));
			pSprite->AddFrame(CVector2(4, 8));
			pSprite->AddFrame(CVector2(4, 9));
			pSprite->AddFrame(CVector2(4, 10));
			pSprite->AddFrame(CVector2(4, 11));
			pSprite->AddFrame(CVector2(4, 12));
			pRenderer->AddSprite("MarineMove2", pSprite);
			pSprite->SaveSprite("MarineMove2.aclp");
			delete pSprite;


			pSprite = new CSprite;
			pSprite->SetAtlas(pAtlasTexture);
			pSprite->SetCellSize(CVector2(64, 64));
			pSprite->SetAtlasGridSize(CVector2(17, 14));
			pSprite->SetSampleRate(15);
			pSprite->SetLoop(true);
			pSprite->AddFrame(CVector2(6, 4));
			pSprite->AddFrame(CVector2(6, 5));
			pSprite->AddFrame(CVector2(6, 6));
			pSprite->AddFrame(CVector2(6, 7));
			pSprite->AddFrame(CVector2(6, 8));
			pSprite->AddFrame(CVector2(6, 9));
			pSprite->AddFrame(CVector2(6, 10));
			pSprite->AddFrame(CVector2(6, 11));
			pSprite->AddFrame(CVector2(6, 12));
			pRenderer->AddSprite("MarineMove3", pSprite);
			pSprite->SaveSprite("MarineMove3.aclp");
			delete pSprite;


			pSprite = new CSprite;
			pSprite->SetAtlas(pAtlasTexture);
			pSprite->SetCellSize(CVector2(64, 64));
			pSprite->SetAtlasGridSize(CVector2(17, 14));
			pSprite->SetSampleRate(15);
			pSprite->SetLoop(true);
			pSprite->AddFrame(CVector2(8, 4));
			pSprite->AddFrame(CVector2(8, 5));
			pSprite->AddFrame(CVector2(8, 6));
			pSprite->AddFrame(CVector2(8, 7));
			pSprite->AddFrame(CVector2(8, 8));
			pSprite->AddFrame(CVector2(8, 9));
			pSprite->AddFrame(CVector2(8, 10));
			pSprite->AddFrame(CVector2(8, 11));
			pSprite->AddFrame(CVector2(8, 12));
			pRenderer->AddSprite("MarineMove4", pSprite);
			pSprite->SaveSprite("MarineMove4.aclp");
			delete pSprite;


			pSprite = new CSprite;
			pSprite->SetAtlas(pAtlasTexture);
			pSprite->SetCellSize(CVector2(64, 64));
			pSprite->SetAtlasGridSize(CVector2(17, 14));
			pSprite->SetSampleRate(15);
			pSprite->SetLoop(true);
			pSprite->AddFrame(CVector2(10, 4));
			pSprite->AddFrame(CVector2(10, 5));
			pSprite->AddFrame(CVector2(10, 6));
			pSprite->AddFrame(CVector2(10, 7));
			pSprite->AddFrame(CVector2(10, 8));
			pSprite->AddFrame(CVector2(10, 9));
			pSprite->AddFrame(CVector2(10, 10));
			pSprite->AddFrame(CVector2(10, 11));
			pSprite->AddFrame(CVector2(10, 12));
			pRenderer->AddSprite("MarineMove5", pSprite);
			pSprite->SaveSprite("MarineMove5.aclp");
			delete pSprite;


			pSprite = new CSprite;
			pSprite->SetAtlas(pAtlasTexture);
			pSprite->SetCellSize(CVector2(64, 64));
			pSprite->SetAtlasGridSize(CVector2(17, 14));
			pSprite->SetSampleRate(15);
			pSprite->SetLoop(true);
			pSprite->AddFrame(CVector2(12, 4));
			pSprite->AddFrame(CVector2(12, 5));
			pSprite->AddFrame(CVector2(12, 6));
			pSprite->AddFrame(CVector2(12, 7));
			pSprite->AddFrame(CVector2(12, 8));
			pSprite->AddFrame(CVector2(12, 9));
			pSprite->AddFrame(CVector2(12, 10));
			pSprite->AddFrame(CVector2(12, 11));
			pSprite->AddFrame(CVector2(12, 12));
			pRenderer->AddSprite("MarineMove6", pSprite);
			pSprite->SaveSprite("MarineMove6.aclp");
			delete pSprite;


			pSprite = new CSprite;
			pSprite->SetAtlas(pAtlasTexture);
			pSprite->SetCellSize(CVector2(64, 64));
			pSprite->SetAtlasGridSize(CVector2(17, 14));
			pSprite->SetSampleRate(15);
			pSprite->SetLoop(true);
			pSprite->AddFrame(CVector2(14, 4));
			pSprite->AddFrame(CVector2(14, 5));
			pSprite->AddFrame(CVector2(14, 6));
			pSprite->AddFrame(CVector2(14, 7));
			pSprite->AddFrame(CVector2(14, 8));
			pSprite->AddFrame(CVector2(14, 9));
			pSprite->AddFrame(CVector2(14, 10));
			pSprite->AddFrame(CVector2(14, 11));
			pSprite->AddFrame(CVector2(14, 12));
			pRenderer->AddSprite("MarineMove7", pSprite);
			pSprite->SaveSprite("MarineMove7.aclp");
			delete pSprite;


			pSprite = new CSprite;
			pSprite->SetAtlas(pAtlasTexture);
			pSprite->SetCellSize(CVector2(64, 64));
			pSprite->SetAtlasGridSize(CVector2(17, 14));
			pSprite->SetSampleRate(15);
			pSprite->SetLoop(true);
			pSprite->AddFrame(CVector2(16, 4));
			pSprite->AddFrame(CVector2(16, 5));
			pSprite->AddFrame(CVector2(16, 6));
			pSprite->AddFrame(CVector2(16, 7));
			pSprite->AddFrame(CVector2(16, 8));
			pSprite->AddFrame(CVector2(16, 9));
			pSprite->AddFrame(CVector2(16, 10));
			pSprite->AddFrame(CVector2(16, 11));
			pSprite->AddFrame(CVector2(16, 12));
			pRenderer->AddSprite("MarineMove8", pSprite);
			pSprite->SaveSprite("MarineMove8.aclp");
			delete pSprite;

			string strIndex = "0";
			string strClipName = "MarineStand";
			pSprite = new CSprite;
			pSprite->SetAtlas(pAtlasTexture);
			pSprite->SetCellSize(CVector2(64, 64));
			pSprite->SetAtlasGridSize(CVector2(17, 14));
			pSprite->SetSampleRate(5);
			pSprite->SetLoop(true);
			pSprite->AddFrame(CVector2(0, 4));
			pRenderer->AddSprite(strClipName + strIndex, pSprite);
			pSprite->SaveSprite(strClipName + strIndex + ".aclp");
			delete pSprite;

			strIndex = "1";
			strClipName = "MarineStand";
			pSprite = new CSprite;
			pSprite->SetAtlas(pAtlasTexture);
			pSprite->SetCellSize(CVector2(64, 64));
			pSprite->SetAtlasGridSize(CVector2(17, 14));
			pSprite->SetSampleRate(5);
			pSprite->SetLoop(true);
			pSprite->AddFrame(CVector2(2, 4));
			pRenderer->AddSprite(strClipName + strIndex, pSprite);
			pSprite->SaveSprite(strClipName + strIndex + ".aclp");
			delete pSprite;

			strIndex = "2";
			strClipName = "MarineStand";
			pSprite = new CSprite;
			pSprite->SetAtlas(pAtlasTexture);
			pSprite->SetCellSize(CVector2(64, 64));
			pSprite->SetAtlasGridSize(CVector2(17, 14));
			pSprite->SetSampleRate(5);
			pSprite->SetLoop(true);
			pSprite->AddFrame(CVector2(4, 4));
			pRenderer->AddSprite(strClipName + strIndex, pSprite);
			pSprite->SaveSprite(strClipName + strIndex + ".aclp");
			delete pSprite;

			strIndex = "3";
			strClipName = "MarineStand";
			pSprite = new CSprite;
			pSprite->SetAtlas(pAtlasTexture);
			pSprite->SetCellSize(CVector2(64, 64));
			pSprite->SetAtlasGridSize(CVector2(17, 14));
			pSprite->SetSampleRate(5);
			pSprite->SetLoop(true);
			pSprite->AddFrame(CVector2(6, 4));
			pRenderer->AddSprite(strClipName + strIndex, pSprite);
			pSprite->SaveSprite(strClipName + strIndex + ".aclp");
			delete pSprite;

			strIndex = "4";
			strClipName = "MarineStand";
			pSprite = new CSprite;
			pSprite->SetAtlas(pAtlasTexture);
			pSprite->SetCellSize(CVector2(64, 64));
			pSprite->SetAtlasGridSize(CVector2(17, 14));
			pSprite->SetSampleRate(5);
			pSprite->SetLoop(true);
			pSprite->AddFrame(CVector2(8, 4));
			pRenderer->AddSprite(strClipName + strIndex, pSprite);
			pSprite->SaveSprite(strClipName + strIndex + ".aclp");
			delete pSprite;

			strIndex = "5";
			strClipName = "MarineStand";
			pSprite = new CSprite;
			pSprite->SetAtlas(pAtlasTexture);
			pSprite->SetCellSize(CVector2(64, 64));
			pSprite->SetAtlasGridSize(CVector2(17, 14));
			pSprite->SetSampleRate(5);
			pSprite->SetLoop(true);
			pSprite->AddFrame(CVector2(10, 4));
			pRenderer->AddSprite(strClipName + strIndex, pSprite);
			pSprite->SaveSprite(strClipName + strIndex + ".aclp");
			delete pSprite;

			strIndex = "6";
			strClipName = "MarineStand";
			pSprite = new CSprite;
			pSprite->SetAtlas(pAtlasTexture);
			pSprite->SetCellSize(CVector2(64, 64));
			pSprite->SetAtlasGridSize(CVector2(17, 14));
			pSprite->SetSampleRate(5);
			pSprite->SetLoop(true);
			pSprite->AddFrame(CVector2(12, 4));
			pRenderer->AddSprite(strClipName + strIndex, pSprite);
			pSprite->SaveSprite(strClipName + strIndex + ".aclp");
			delete pSprite;

			strIndex = "7";
			strClipName = "MarineStand";
			pSprite = new CSprite;
			pSprite->SetAtlas(pAtlasTexture);
			pSprite->SetCellSize(CVector2(64, 64));
			pSprite->SetAtlasGridSize(CVector2(17, 14));
			pSprite->SetSampleRate(5);
			pSprite->SetLoop(true);
			pSprite->AddFrame(CVector2(14, 4));
			pRenderer->AddSprite(strClipName + strIndex, pSprite);
			pSprite->SaveSprite(strClipName + strIndex + ".aclp");
			delete pSprite;

			strIndex = "8";
			strClipName = "MarineStand";
			pSprite = new CSprite;
			pSprite->SetAtlas(pAtlasTexture);
			pSprite->SetCellSize(CVector2(64, 64));
			pSprite->SetAtlasGridSize(CVector2(17, 14));
			pSprite->SetSampleRate(5);
			pSprite->SetLoop(true);
			pSprite->AddFrame(CVector2(16, 4));
			pRenderer->AddSprite(strClipName + strIndex, pSprite);
			pSprite->SaveSprite(strClipName + strIndex + ".aclp");
			delete pSprite;



			pSprite = new CSprite;

			pAtlasTexture = GET_SINGLE(CResourceManager)->FindTexture("MarineLeft");
			pSprite->SetAtlas(pAtlasTexture);
			pSprite->SetCellSize(CVector2(64, 64));
			pSprite->SetAtlasGridSize(CVector2(17, 14));
			pSprite->SetSampleRate(15);
			pSprite->SetLoop(true);
			pSprite->AddFrame(CVector2(2, 4));
			pSprite->AddFrame(CVector2(2, 5));
			pSprite->AddFrame(CVector2(2, 6));
			pSprite->AddFrame(CVector2(2, 7));
			pSprite->AddFrame(CVector2(2, 8));
			pSprite->AddFrame(CVector2(2, 9));
			pSprite->AddFrame(CVector2(2, 10));
			pSprite->AddFrame(CVector2(2, 11));
			pSprite->AddFrame(CVector2(2, 12));
			pRenderer->AddSprite("MarineMove9", pSprite);
			pSprite->SaveSprite("MarineMove9.aclp");
			delete pSprite;

			pSprite = new CSprite;
			pSprite->SetAtlas(pAtlasTexture);
			pSprite->SetCellSize(CVector2(64, 64));
			pSprite->SetAtlasGridSize(CVector2(17, 14));
			pSprite->SetSampleRate(15);
			pSprite->SetLoop(true);
			pSprite->AddFrame(CVector2(4, 4));
			pSprite->AddFrame(CVector2(4, 5));
			pSprite->AddFrame(CVector2(4, 6));
			pSprite->AddFrame(CVector2(4, 7));
			pSprite->AddFrame(CVector2(4, 8));
			pSprite->AddFrame(CVector2(4, 9));
			pSprite->AddFrame(CVector2(4, 10));
			pSprite->AddFrame(CVector2(4, 11));
			pSprite->AddFrame(CVector2(4, 12));
			pRenderer->AddSprite("MarineMove10", pSprite);
			pSprite->SaveSprite("MarineMove10.aclp");
			delete pSprite;


			pSprite = new CSprite;
			pSprite->SetAtlas(pAtlasTexture);
			pSprite->SetCellSize(CVector2(64, 64));
			pSprite->SetAtlasGridSize(CVector2(17, 14));
			pSprite->SetSampleRate(15);
			pSprite->SetLoop(true);
			pSprite->AddFrame(CVector2(6, 4));
			pSprite->AddFrame(CVector2(6, 5));
			pSprite->AddFrame(CVector2(6, 6));
			pSprite->AddFrame(CVector2(6, 7));
			pSprite->AddFrame(CVector2(6, 8));
			pSprite->AddFrame(CVector2(6, 9));
			pSprite->AddFrame(CVector2(6, 10));
			pSprite->AddFrame(CVector2(6, 11));
			pSprite->AddFrame(CVector2(6, 12));
			pRenderer->AddSprite("MarineMove11", pSprite);
			pSprite->SaveSprite("MarineMove11.aclp");
			delete pSprite;


			pSprite = new CSprite;
			pSprite->SetAtlas(pAtlasTexture);
			pSprite->SetCellSize(CVector2(64, 64));
			pSprite->SetAtlasGridSize(CVector2(17, 14));
			pSprite->SetSampleRate(15);
			pSprite->SetLoop(true);
			pSprite->AddFrame(CVector2(8, 4));
			pSprite->AddFrame(CVector2(8, 5));
			pSprite->AddFrame(CVector2(8, 6));
			pSprite->AddFrame(CVector2(8, 7));
			pSprite->AddFrame(CVector2(8, 8));
			pSprite->AddFrame(CVector2(8, 9));
			pSprite->AddFrame(CVector2(8, 10));
			pSprite->AddFrame(CVector2(8, 11));
			pSprite->AddFrame(CVector2(8, 12));
			pRenderer->AddSprite("MarineMove12", pSprite);
			pSprite->SaveSprite("MarineMove12.aclp");
			delete pSprite;


			pSprite = new CSprite;
			pSprite->SetAtlas(pAtlasTexture);
			pSprite->SetCellSize(CVector2(64, 64));
			pSprite->SetAtlasGridSize(CVector2(17, 14));
			pSprite->SetSampleRate(15);
			pSprite->SetLoop(true);
			pSprite->AddFrame(CVector2(10, 4));
			pSprite->AddFrame(CVector2(10, 5));
			pSprite->AddFrame(CVector2(10, 6));
			pSprite->AddFrame(CVector2(10, 7));
			pSprite->AddFrame(CVector2(10, 8));
			pSprite->AddFrame(CVector2(10, 9));
			pSprite->AddFrame(CVector2(10, 10));
			pSprite->AddFrame(CVector2(10, 11));
			pSprite->AddFrame(CVector2(10, 12));
			pRenderer->AddSprite("MarineMove13", pSprite);
			pSprite->SaveSprite("MarineMove13.aclp");
			delete pSprite;

			pSprite = new CSprite;
			pSprite->SetAtlas(pAtlasTexture);
			pSprite->SetCellSize(CVector2(64, 64));
			pSprite->SetAtlasGridSize(CVector2(17, 14));
			pSprite->SetSampleRate(15);
			pSprite->SetLoop(true);
			pSprite->AddFrame(CVector2(12, 4));
			pSprite->AddFrame(CVector2(12, 5));
			pSprite->AddFrame(CVector2(12, 6));
			pSprite->AddFrame(CVector2(12, 7));
			pSprite->AddFrame(CVector2(12, 8));
			pSprite->AddFrame(CVector2(12, 9));
			pSprite->AddFrame(CVector2(12, 10));
			pSprite->AddFrame(CVector2(12, 11));
			pSprite->AddFrame(CVector2(12, 12));
			pRenderer->AddSprite("MarineMove14", pSprite);
			pSprite->SaveSprite("MarineMove14.aclp");
			delete pSprite;


			pSprite = new CSprite;
			pSprite->SetAtlas(pAtlasTexture);
			pSprite->SetCellSize(CVector2(64, 64));
			pSprite->SetAtlasGridSize(CVector2(17, 14));
			pSprite->SetSampleRate(15);
			pSprite->SetLoop(true);
			pSprite->AddFrame(CVector2(14, 4));
			pSprite->AddFrame(CVector2(14, 5));
			pSprite->AddFrame(CVector2(14, 6));
			pSprite->AddFrame(CVector2(14, 7));
			pSprite->AddFrame(CVector2(14, 8));
			pSprite->AddFrame(CVector2(14, 9));
			pSprite->AddFrame(CVector2(14, 10));
			pSprite->AddFrame(CVector2(14, 11));
			pSprite->AddFrame(CVector2(14, 12));
			pRenderer->AddSprite("MarineMove15", pSprite);
			pSprite->SaveSprite("MarineMove15.aclp");
			delete pSprite;

			strIndex = "9";
			strClipName = "MarineStand";
			pSprite = new CSprite;
			pSprite->SetAtlas(pAtlasTexture);
			pSprite->SetCellSize(CVector2(64, 64));
			pSprite->SetAtlasGridSize(CVector2(17, 14));
			pSprite->SetSampleRate(5);
			pSprite->SetLoop(true);
			pSprite->AddFrame(CVector2(2, 4));
			pRenderer->AddSprite(strClipName + strIndex, pSprite);
			pSprite->SaveSprite(strClipName + strIndex + ".aclp");
			delete pSprite;


			strIndex = "10";
			strClipName = "MarineStand";
			pSprite = new CSprite;
			pSprite->SetAtlas(pAtlasTexture);
			pSprite->SetCellSize(CVector2(64, 64));
			pSprite->SetAtlasGridSize(CVector2(17, 14));
			pSprite->SetSampleRate(5);
			pSprite->SetLoop(true);
			pSprite->AddFrame(CVector2(4, 4));
			pRenderer->AddSprite(strClipName + strIndex, pSprite);
			pSprite->SaveSprite(strClipName + strIndex + ".aclp");
			delete pSprite;

			strIndex = "11";
			strClipName = "MarineStand";
			pSprite = new CSprite;
			pSprite->SetAtlas(pAtlasTexture);
			pSprite->SetCellSize(CVector2(64, 64));
			pSprite->SetAtlasGridSize(CVector2(17, 14));
			pSprite->SetSampleRate(5);
			pSprite->SetLoop(true);
			pSprite->AddFrame(CVector2(6, 4));
			pRenderer->AddSprite(strClipName + strIndex, pSprite);
			pSprite->SaveSprite(strClipName + strIndex + ".aclp");
			delete pSprite;

			strIndex = "12";
			strClipName = "MarineStand";
			pSprite = new CSprite;
			pSprite->SetAtlas(pAtlasTexture);
			pSprite->SetCellSize(CVector2(64, 64));
			pSprite->SetAtlasGridSize(CVector2(17, 14));
			pSprite->SetSampleRate(5);
			pSprite->SetLoop(true);
			pSprite->AddFrame(CVector2(8, 4));
			pRenderer->AddSprite(strClipName + strIndex, pSprite);
			pSprite->SaveSprite(strClipName + strIndex + ".aclp");
			delete pSprite;

			strIndex = "13";
			strClipName = "MarineStand";
			pSprite = new CSprite;
			pSprite->SetAtlas(pAtlasTexture);
			pSprite->SetCellSize(CVector2(64, 64));
			pSprite->SetAtlasGridSize(CVector2(17, 14));
			pSprite->SetSampleRate(5);
			pSprite->SetLoop(true);
			pSprite->AddFrame(CVector2(10, 4));
			pRenderer->AddSprite(strClipName + strIndex, pSprite);
			pSprite->SaveSprite(strClipName + strIndex + ".aclp");
			delete pSprite;

			strIndex = "14";
			strClipName = "MarineStand";
			pSprite = new CSprite;
			pSprite->SetAtlas(pAtlasTexture);
			pSprite->SetCellSize(CVector2(64, 64));
			pSprite->SetAtlasGridSize(CVector2(17, 14));
			pSprite->SetSampleRate(5);
			pSprite->SetLoop(true);
			pSprite->AddFrame(CVector2(12, 4));
			pRenderer->AddSprite(strClipName + strIndex, pSprite);
			pSprite->SaveSprite(strClipName + strIndex + ".aclp");
			delete pSprite;

			strIndex = "15";
			strClipName = "MarineStand";
			pSprite = new CSprite;
			pSprite->SetAtlas(pAtlasTexture);
			pSprite->SetCellSize(CVector2(64, 64));
			pSprite->SetAtlasGridSize(CVector2(17, 14));
			pSprite->SetSampleRate(5);
			pSprite->SetLoop(true);
			pSprite->AddFrame(CVector2(14, 4));
			pRenderer->AddSprite(strClipName + strIndex, pSprite);
			pSprite->SaveSprite(strClipName + strIndex + ".aclp");
			delete pSprite;


			pRenderer->ChangeCurrentClip("MarineStand0");

			GET_SINGLE(CFileStream)->SaveUnit(pMarine, "Marine.unit");

		}
		}
		*/



#pragma region CommandCenter

int iCommandCenterX = 15;
int iCommandCenterY = 10;
{
	CGameObject* pCommandCenter = new CGameObject("CommandCenter");
	pCommandCenter->SetPilot(pPlayer->GetComponent<CPlayer>());
	pGroundUnitLayer->AddGameObject(pCommandCenter);
	pCommandCenter->GetTransform()->SetPivot(0.5f, 0.5f);
	pCommandCenter->GetTransform()->SetPosition(iCommandCenterX * 32, iCommandCenterY * 32);
	CEllipseRenderer* pEllipseRenderer = pCommandCenter->AddComponent<CEllipseRenderer>();
	pEllipseRenderer->SetMinorAxisLength(45);
	pEllipseRenderer->SetThickness(2);
	pEllipseRenderer->SetLocalPosition(0, 5);

	CSpriteRenderer* pRenderer = pCommandCenter->AddComponent<CSpriteRenderer>();
	pRenderer->SetSize(128, 160);

	CCommandCenter* pCreateUnit = pCommandCenter->AddComponent<CCommandCenter>();

	CSprite* pDeathSprite = new CSprite;
	pDeathSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("Terran_Explosion_XLarge"));
	pDeathSprite->SetAtlasGridSize(1, 15);
	pDeathSprite->SetSampleRate(10);
	pDeathSprite->SetLoop(false);
	pDeathSprite->SetCellSize(252, 200);
	pDeathSprite->AddFrame(CVector2(0, 0));
	pDeathSprite->AddFrame(CVector2(1, 0));
	pDeathSprite->AddFrame(CVector2(2, 0));
	pDeathSprite->AddFrame(CVector2(3, 0));
	pDeathSprite->AddFrame(CVector2(4, 0));
	pDeathSprite->AddFrame(CVector2(5, 0));
	pDeathSprite->AddFrame(CVector2(6, 0));
	pDeathSprite->AddFrame(CVector2(7, 0));
	pDeathSprite->AddFrame(CVector2(8, 0));
	pDeathSprite->AddFrame(CVector2(9, 0));
	pDeathSprite->AddFrame(CVector2(10, 0));
	pDeathSprite->AddFrame(CVector2(11, 0));
	pDeathSprite->AddFrame(CVector2(12, 0));
	pDeathSprite->AddFrame(CVector2(13, 0));
	pDeathSprite->AddFrame(CVector2(14, 0));

	pDeathSprite->SaveSprite("CommandCenterDeath.aclp");
	pRenderer->AddSprite("CommandCenterDeath", pDeathSprite);
	delete pDeathSprite;

	CStructure* pStructure = pCommandCenter->AddComponent<CStructure>();
	pStructure->SetRequireGas(0);
	pStructure->SetRequireMineral(400);
	pStructure->SetSupply(10);
	pStructure->SetBuildTime(10);
	pStructure->AddBuildableTile(0, 1);
	pStructure->AddBuildableTile(1, 1);
	pStructure->AddBuildableTile(2, 1);
	pStructure->AddBuildableTile(3, 1);
	pStructure->AddBuildableTile(0, 2);
	pStructure->AddBuildableTile(1, 2);
	pStructure->AddBuildableTile(2, 2);
	pStructure->AddBuildableTile(3, 2);
	pStructure->AddBuildableTile(0, 3);
	pStructure->AddBuildableTile(1, 3);
	pStructure->AddBuildableTile(2, 3);
	pStructure->AddBuildableTile(3, 3);


	CUnitStatus* pStatus = pCommandCenter->AddComponent<CUnitStatus>();
	pStatus->SetMaxHP(1500);
	pStatus->SetHPMaxCondition();
	pStatus->SetMaxMP(0);
	pStatus->SetHPMaxCondition();
	pStatus->SetMaxShield(0);
	pStatus->SetHPMaxCondition();
	pStatus->SetRequirement(pStructure->GetBuildTime(), 400, 0, 0);
	pStatus->SetSightRadius(8);

	CCircleCollider* pCollider = pCommandCenter->AddComponent<CCircleCollider>();
	pCollider->SetRadius(40);

	CUnitInfo* pInfo = pCommandCenter->AddComponent<CUnitInfo>();

	CSprite* pSprite = new CSprite;
	CTexture* pAtlas = GET_SINGLE(CResourceManager)->FindTexture("CommandCenter");
	pSprite->SetAtlas(pAtlas);
	pSprite->SetAtlasGridSize(10, 1);
	pSprite->SetCellSize(128, 160);
	pSprite->SetSampleRate(4 / pStructure->GetBuildTime());
	pSprite->SetLoop(false);

	pSprite->AddFrame(CVector2(0, 0));
	pSprite->AddFrame(CVector2(1, 0));
	pSprite->AddFrame(CVector2(2, 0));
	pSprite->AddFrame(CVector2(3, 0));
	pRenderer->AddSprite("CommandCenterBuild",pSprite);
	pSprite->SaveSprite("CommandCenterBuild.aclp");
	delete pSprite;

	pSprite = new CSprite;
	pSprite->SetAtlas(pAtlas);
	pSprite->SetAtlasGridSize(10, 1);
	pSprite->SetCellSize(128, 160);
	pSprite->SetSampleRate(1);
	pSprite->SetLoop(true);

	pSprite->AddFrame(CVector2(4, 0));
	pRenderer->AddSprite("CommandCenterNormal", pSprite);
	pSprite->SaveSprite("CommandCenterNormal.aclp");
	delete pSprite;

	pSprite = new CSprite;
	pSprite->SetAtlas(pAtlas);
	pSprite->SetAtlasGridSize(10, 1);
	pSprite->SetCellSize(128, 160);
	pSprite->SetSampleRate(5);
	pSprite->SetLoop(true);

	pSprite->AddFrame(CVector2(4, 0));
	pSprite->AddFrame(CVector2(5, 0));
	pSprite->AddFrame(CVector2(4, 0));
	pSprite->AddFrame(CVector2(4, 0));
	pSprite->AddFrame(CVector2(4, 0));
	pSprite->AddFrame(CVector2(5, 0));
	pSprite->AddFrame(CVector2(4, 0));
	pSprite->AddFrame(CVector2(5, 0));
	pSprite->AddFrame(CVector2(5, 0));
	pSprite->AddFrame(CVector2(5, 0));
	pSprite->AddFrame(CVector2(4, 0));
	pSprite->AddFrame(CVector2(5, 0));	

	pRenderer->AddSprite("CommandCenterWork", pSprite);
	pSprite->SaveSprite("CommandCenterWork.aclp");
	delete pSprite;


	pSprite = new CSprite;
	pSprite->SetAtlas(pAtlas);
	pSprite->SetAtlasGridSize(10, 1);
	pSprite->SetCellSize(128, 160);
	pSprite->SetSampleRate(2);
	pSprite->SetLoop(false);

	pSprite->AddFrame(CVector2(9, 0));
	pSprite->AddFrame(CVector2(6, 0));
	pSprite->AddFrame(CVector2(7, 0));
	pSprite->AddFrame(CVector2(8, 0));

	pRenderer->AddSprite("CommandCenterLiftUp", pSprite);
	pSprite->SaveSprite("CommandCenterLiftUp.aclp");
	delete pSprite;


	pSprite = new CSprite;
	pSprite->SetAtlas(pAtlas);
	pSprite->SetAtlasGridSize(10, 1);
	pSprite->SetCellSize(128, 160);
	pSprite->SetSampleRate(1);
	pSprite->SetLoop(true);

	pSprite->AddFrame(CVector2(8, 0));

	pRenderer->AddSprite("CommandCenterAir", pSprite);
	pSprite->SaveSprite("CommandCenterAir.aclp");
	delete pSprite;

	pSprite = new CSprite;
	pSprite->SetAtlas(pAtlas);
	pSprite->SetAtlasGridSize(10, 1);
	pSprite->SetCellSize(128, 160);
	pSprite->SetSampleRate(2);
	pSprite->SetLoop(false);

	pSprite->AddFrame(CVector2(8, 0));
	pSprite->AddFrame(CVector2(7, 0));
	pSprite->AddFrame(CVector2(6, 0));
	pSprite->AddFrame(CVector2(9, 0));

	pRenderer->AddSprite("CommandCenterLiftDown", pSprite);
	pSprite->SaveSprite("CommandCenterLiftDown.aclp");
	delete pSprite;

	pRenderer->ChangeCurrentClip("CommandCenterNormal");


	GET_SINGLE(CFileStream)->SaveUnit(pCommandCenter, "CommandCenter.unit");
}

#pragma endregion


#pragma region SCV
for (int i = 0; i < 4; ++i)
{
	CGameObject* pSCV = new CGameObject("SCV");
	pSCV->SetPilot(pPlayer->GetComponent<CPlayer>());
	pSCV->SetSelected(false);
	pSCV->SetToAirUnit(false);
	pGroundUnitLayer->AddGameObject(pSCV);
	pSCV->GetTransform()->SetPivot(CVector2(0.5f, 0.6f));
	pSCV->GetTransform()->SetPosition(iCommandCenterX*32 + i * 32, iCommandCenterY*32 + 64);

	CEllipseRenderer* pEllipse = pSCV->AddComponent<CEllipseRenderer>();
	CSpriteRenderer* pRenderer = pSCV->AddComponent<CSpriteRenderer>();
	CSCVAnimator* pAnimator = pSCV->AddComponent<CSCVAnimator>();
	CSprite* pDeathSprite = new CSprite;
	pDeathSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("Terran_Explosion_XSmall"));
	pDeathSprite->SetAtlasGridSize(1, 9);
	pDeathSprite->SetCellSize(64, 64);
	pDeathSprite->SetSampleRate(10);
	pDeathSprite->SetLoop(false);
	pDeathSprite->AddFrame(CVector2(0, 0));
	pDeathSprite->AddFrame(CVector2(1, 0));
	pDeathSprite->AddFrame(CVector2(2, 0));
	pDeathSprite->AddFrame(CVector2(3, 0));
	pDeathSprite->AddFrame(CVector2(4, 0));
	pDeathSprite->AddFrame(CVector2(5, 0));
	pDeathSprite->AddFrame(CVector2(6, 0));
	pDeathSprite->AddFrame(CVector2(7, 0));
	pDeathSprite->AddFrame(CVector2(8, 0));
	pDeathSprite->AddFrame(CVector2(9, 0));
	pDeathSprite->SaveSprite("SCVDeath.aclp");
	pRenderer->AddSprite("SCVDeath", pDeathSprite);
	delete pDeathSprite;

	CUnitInfo* pInfo = pSCV->AddComponent<CUnitInfo>();
	CCircleCollider* pCollider = pSCV->AddComponent<CCircleCollider>();
	CUnitStatus* pStatus = pSCV->AddComponent<CUnitStatus>();
	CMove*	pMove = pSCV->AddComponent<CMove>();
	CBuild* pBuild = pSCV->AddComponent<CBuild>();
	CAdvancedBuild* pAdvancedBuild = pSCV->AddComponent<CAdvancedBuild>();
	CStop* pStop = pSCV->AddComponent<CStop>();
	CHold* pHold = pSCV->AddComponent<CHold>();
	CAttack* pAttack = pSCV->AddComponent<CAttack>();
	CRepair* pRepair = pSCV->AddComponent<CRepair>();
	CGather* pGather = pSCV->AddComponent<CGather>();
	CDeffence* pDeffence = pSCV->AddComponent<CDeffence>();


	pInfo->SetUnitButtonTexture(GET_SINGLE(CResourceManager)->FindTexture("InfoPanel_Button_Terran_SCV"));


	pDeffence->SetName("Terran Infantry Armor");
	pDeffence->SetValue(60);
	pDeffence->SetMaxValue(60);
	pDeffence->SetUpgradeType(UT_TERRAN_BIONIC_DEFFENCE);

	pInfo->SetAttackComponent(pAttack);
	pInfo->SetDeffenceComponent(pDeffence);

	pAttack->SetAttackRange(32);
	pAttack->SetInterval(1.25f);
	pAttack->SetDamage(50);
	pAttack->SetWeaponName("Fusion Cutter");
	pAttack->SetUpgradeIncrease(1);
	pAttack->SetUpgradeType(UT_TERRAN_BIONIC_WEAPON);


	pStatus->SetRequirement(15, 50, 0, 1);
	pStatus->SetMaxHP(60);
	pStatus->SetHPMaxCondition();
	pStatus->SetMaxMP(0);
	pStatus->SetMPMaxCondition();
	pStatus->SetMaxShield(0);
	pStatus->SetShieldMaxCondition();
	pStatus->SetSightRadius(5);

	pMove->SetStopThresholdRadius(48);
	pRenderer->SetSize(CVector2(72, 72));

	pCollider->SetRadius(20);
	pCollider->SetTileCollisionRadius(20);
	pEllipse->SetLocalPosition(0, 2);
	pEllipse->SetThickness(2);
	pEllipse->SetMinorAxisLength(12);
	pEllipse->SetMajorAxisScale(1.6);
	pMove->SetMoveSpeed(100);


	CSprite* pSprite = new CSprite;
	CTexture* pAtlasTexture = GET_SINGLE(CResourceManager)->FindTexture("SCVRight");

	pSprite->SetAtlas(pAtlasTexture);
	pSprite->SetCellSize(CVector2(72, 72));
	pSprite->SetAtlasGridSize(CVector2(17, 3));
	pSprite->SetSampleRate(15);
	pSprite->SetLoop(true);
	pSprite->AddFrame(CVector2(0, 0));
	pSprite->SetSpriteKey("SCVMove0");
	pRenderer->AddSprite("SCVMove0", pSprite);
	pSprite->SaveSprite("SCVMove0.aclp");
	pSprite->SetSpriteKey("SCVStand0");
	pRenderer->AddSprite("SCVStand0", pSprite);
	pSprite->SaveSprite("SCVStand0.aclp");
	delete pSprite;

	pSprite = new CSprite;
	pSprite->SetAtlas(pAtlasTexture);
	pSprite->SetCellSize(CVector2(72, 72));
	pSprite->SetAtlasGridSize(CVector2(17, 3));
	pSprite->SetSampleRate(15);
	pSprite->SetLoop(true);
	pSprite->AddFrame(CVector2(2, 0));
	pSprite->SetSpriteKey("SCVMove1");
	pRenderer->AddSprite("SCVMove1", pSprite);
	pSprite->SaveSprite("SCVMove1.aclp");
	pSprite->SetSpriteKey("SCVStand1");
	pRenderer->AddSprite("SCVStand1", pSprite);
	pSprite->SaveSprite("SCVStand1.aclp");
	delete pSprite;

	pSprite = new CSprite;
	pSprite->SetAtlas(pAtlasTexture);
	pSprite->SetCellSize(CVector2(72, 72));
	pSprite->SetAtlasGridSize(CVector2(17, 3));
	pSprite->SetSampleRate(15);
	pSprite->SetLoop(true);
	pSprite->AddFrame(CVector2(4, 0));
	pSprite->SetSpriteKey("SCVMove2");
	pRenderer->AddSprite("SCVMove2", pSprite);
	pSprite->SaveSprite("SCVMove2.aclp");
	pSprite->SetSpriteKey("SCVStand2");
	pRenderer->AddSprite("SCVStand2", pSprite);
	pSprite->SaveSprite("SCVStand2.aclp");
	delete pSprite;


	pSprite = new CSprite;
	pSprite->SetAtlas(pAtlasTexture);
	pSprite->SetCellSize(CVector2(72, 72));
	pSprite->SetAtlasGridSize(CVector2(17, 3));
	pSprite->SetSampleRate(15);
	pSprite->SetLoop(true);
	pSprite->AddFrame(CVector2(6, 0));
	pSprite->SetSpriteKey("SCVMove3");
	pRenderer->AddSprite("SCVMove3", pSprite);
	pSprite->SaveSprite("SCVMove3.aclp");
	pSprite->SetSpriteKey("SCVStand3");
	pRenderer->AddSprite("SCVStand3", pSprite);
	pSprite->SaveSprite("SCVStand3.aclp");
	delete pSprite;


	pSprite = new CSprite;
	pSprite->SetAtlas(pAtlasTexture);
	pSprite->SetCellSize(CVector2(72, 72));
	pSprite->SetAtlasGridSize(CVector2(17, 3));
	pSprite->SetSampleRate(15);
	pSprite->SetLoop(true);
	pSprite->AddFrame(CVector2(8, 0));
	pSprite->SetSpriteKey("SCVMove4");
	pRenderer->AddSprite("SCVMove4", pSprite);
	pSprite->SaveSprite("SCVMove4.aclp");
	pSprite->SetSpriteKey("SCVStand4");
	pRenderer->AddSprite("SCVStand4", pSprite);
	pSprite->SaveSprite("SCVStand4.aclp");
	delete pSprite;

	pSprite = new CSprite;
	pSprite->SetAtlas(pAtlasTexture);
	pSprite->SetCellSize(CVector2(72, 72));
	pSprite->SetAtlasGridSize(CVector2(17, 3));
	pSprite->SetSampleRate(15);
	pSprite->SetLoop(true);
	pSprite->AddFrame(CVector2(10, 0));
	pSprite->SetSpriteKey("SCVMove5");
	pRenderer->AddSprite("SCVMove5", pSprite);
	pSprite->SaveSprite("SCVMove5.aclp");
	pSprite->SetSpriteKey("SCVStand5");
	pRenderer->AddSprite("SCVStand5", pSprite);
	pSprite->SaveSprite("SCVStand5.aclp");
	delete pSprite;

	pSprite = new CSprite;
	pSprite->SetAtlas(pAtlasTexture);
	pSprite->SetCellSize(CVector2(72, 72));
	pSprite->SetAtlasGridSize(CVector2(17, 3));
	pSprite->SetSampleRate(15);
	pSprite->SetLoop(true);
	pSprite->AddFrame(CVector2(12, 0));
	pSprite->SetSpriteKey("SCVMove6");
	pRenderer->AddSprite("SCVMove6", pSprite);
	pSprite->SaveSprite("SCVMove6.aclp");
	pSprite->SetSpriteKey("SCVStand6");
	pRenderer->AddSprite("SCVStand6", pSprite);
	pSprite->SaveSprite("SCVStand6.aclp");
	delete pSprite;

	pSprite = new CSprite;
	pSprite->SetAtlas(pAtlasTexture);
	pSprite->SetCellSize(CVector2(72, 72));
	pSprite->SetAtlasGridSize(CVector2(17, 3));
	pSprite->SetSampleRate(15);
	pSprite->SetLoop(true);
	pSprite->AddFrame(CVector2(14, 0));
	pSprite->SetSpriteKey("SCVMove7");
	pRenderer->AddSprite("SCVMove7", pSprite);
	pSprite->SaveSprite("SCVMove7.aclp");
	pSprite->SetSpriteKey("SCVStand7");
	pRenderer->AddSprite("SCVStand7", pSprite);
	pSprite->SaveSprite("SCVStand7.aclp");
	delete pSprite;

	pSprite = new CSprite;
	pSprite->SetAtlas(pAtlasTexture);
	pSprite->SetCellSize(CVector2(72, 72));
	pSprite->SetAtlasGridSize(CVector2(17, 3));
	pSprite->SetSampleRate(15);
	pSprite->SetLoop(true);
	pSprite->AddFrame(CVector2(16, 0));
	pSprite->SetSpriteKey("SCVMove8");
	pRenderer->AddSprite("SCVMove8", pSprite);
	pSprite->SaveSprite("SCVMove8.aclp");
	pSprite->SetSpriteKey("SCVStand8");
	pRenderer->AddSprite("SCVStand8", pSprite);
	pSprite->SaveSprite("SCVStand8.aclp");
	delete pSprite;


	pAtlasTexture = GET_SINGLE(CResourceManager)->FindTexture("SCVLeft");
	pSprite = new CSprite;
	pSprite->SetAtlas(pAtlasTexture);
	pSprite->SetCellSize(CVector2(72, 72));
	pSprite->SetAtlasGridSize(CVector2(17, 3));
	pSprite->SetSampleRate(15);
	pSprite->SetLoop(true);
	pSprite->AddFrame(CVector2(2, 0));
	pSprite->SetSpriteKey("SCVMove9");
	pRenderer->AddSprite("SCVMove9", pSprite);
	pSprite->SaveSprite("SCVMove9.aclp");
	pSprite->SetSpriteKey("SCVStand9");
	pRenderer->AddSprite("SCVStand9", pSprite);
	pSprite->SaveSprite("SCVStand9.aclp");
	delete pSprite;

	pSprite = new CSprite;
	pSprite->SetAtlas(pAtlasTexture);
	pSprite->SetCellSize(CVector2(72, 72));
	pSprite->SetAtlasGridSize(CVector2(17, 3));
	pSprite->SetSampleRate(15);
	pSprite->SetLoop(true);
	pSprite->AddFrame(CVector2(4, 0));
	pSprite->SetSpriteKey("SCVMove10");
	pRenderer->AddSprite("SCVMove10", pSprite);
	pSprite->SaveSprite("SCVMove10.aclp");
	pSprite->SetSpriteKey("SCVStand10");
	pRenderer->AddSprite("SCVStand10", pSprite);
	pSprite->SaveSprite("SCVStand10.aclp");
	delete pSprite;

	pSprite = new CSprite;
	pSprite->SetAtlas(pAtlasTexture);
	pSprite->SetCellSize(CVector2(72, 72));
	pSprite->SetAtlasGridSize(CVector2(17, 3));
	pSprite->SetSampleRate(15);
	pSprite->SetLoop(true);
	pSprite->AddFrame(CVector2(6, 0));
	pSprite->SetSpriteKey("SCVMove11");
	pRenderer->AddSprite("SCVMove11", pSprite);
	pSprite->SaveSprite("SCVMove11.aclp");
	pSprite->SetSpriteKey("SCVStand11");
	pRenderer->AddSprite("SCVStand11", pSprite);
	pSprite->SaveSprite("SCVStand11.aclp");
	delete pSprite;

	pSprite = new CSprite;
	pSprite->SetAtlas(pAtlasTexture);
	pSprite->SetCellSize(CVector2(72, 72));
	pSprite->SetAtlasGridSize(CVector2(17, 3));
	pSprite->SetSampleRate(15);
	pSprite->SetLoop(true);
	pSprite->AddFrame(CVector2(8, 0));
	pSprite->SetSpriteKey("SCVMove12");
	pRenderer->AddSprite("SCVMove12", pSprite);
	pSprite->SaveSprite("SCVMove12.aclp");
	pSprite->SetSpriteKey("SCVStand12");
	pRenderer->AddSprite("SCVStand12", pSprite);
	pSprite->SaveSprite("SCVStand12.aclp");
	delete pSprite;

	pSprite = new CSprite;
	pSprite->SetAtlas(pAtlasTexture);
	pSprite->SetCellSize(CVector2(72, 72));
	pSprite->SetAtlasGridSize(CVector2(17, 3));
	pSprite->SetSampleRate(15);
	pSprite->SetLoop(true);
	pSprite->AddFrame(CVector2(10, 0));
	pSprite->SetSpriteKey("SCVMove13");
	pRenderer->AddSprite("SCVMove13", pSprite);
	pSprite->SaveSprite("SCVMove13.aclp");
	pSprite->SetSpriteKey("SCVStand13");
	pRenderer->AddSprite("SCVStand13", pSprite);
	pSprite->SaveSprite("SCVStand13.aclp");
	delete pSprite;

	pSprite = new CSprite;
	pSprite->SetAtlas(pAtlasTexture);
	pSprite->SetCellSize(CVector2(72, 72));
	pSprite->SetAtlasGridSize(CVector2(17, 3));
	pSprite->SetSampleRate(15);
	pSprite->SetLoop(true);
	pSprite->AddFrame(CVector2(12, 0));
	pSprite->SetSpriteKey("SCVMove14");
	pRenderer->AddSprite("SCVMove14", pSprite);
	pSprite->SaveSprite("SCVMove14.aclp");
	pSprite->SetSpriteKey("SCVStand14");
	pRenderer->AddSprite("SCVStand14", pSprite);
	pSprite->SaveSprite("SCVStand14.aclp");
	delete pSprite;

	pSprite = new CSprite;
	pSprite->SetAtlas(pAtlasTexture);
	pSprite->SetCellSize(CVector2(72, 72));
	pSprite->SetAtlasGridSize(CVector2(17, 3));
	pSprite->SetSampleRate(15);
	pSprite->SetLoop(true);
	pSprite->AddFrame(CVector2(14, 0));
	pSprite->SetSpriteKey("SCVMove15");
	pRenderer->AddSprite("SCVMove15", pSprite);
	pSprite->SaveSprite("SCVMove15.aclp");
	pSprite->SetSpriteKey("SCVStand15");
	pRenderer->AddSprite("SCVStand15", pSprite);
	pSprite->SaveSprite("SCVStand15.aclp");
	delete pSprite;


	pAtlasTexture = GET_SINGLE(CResourceManager)->FindTexture("SCVRight");
	pSprite = new CSprite;
	pSprite->SetAtlas(pAtlasTexture);
	pSprite->SetCellSize(CVector2(72, 72));
	pSprite->SetAtlasGridSize(CVector2(17, 3));
	pSprite->SetSampleRate(12);
	pSprite->SetLoop(true);
	pSprite->AddFrame(CVector2(0, 1));
	pSprite->AddFrame(CVector2(0, 2));
	pSprite->AddFrame(CVector2(0, 1));
	pSprite->AddFrame(CVector2(0, 2));
	pSprite->AddFrame(CVector2(0, 1));
	pSprite->AddFrame(CVector2(0, 2));
	pSprite->AddFrame(CVector2(0, 1));
	pSprite->AddFrame(CVector2(0, 2));
	pSprite->AddFrame(CVector2(0, 1));
	pSprite->AddFrame(CVector2(0, 2));
	pSprite->AddFrame(CVector2(0, 1));
	pSprite->AddFrame(CVector2(0, 2));
	pSprite->SetSpriteKey("SCVAttack0");
	pRenderer->AddSprite("SCVAttack0", pSprite);
	pSprite->SaveSprite("SCVAttack0.aclp");
	delete pSprite;

	pSprite = new CSprite;
	pSprite->SetAtlas(pAtlasTexture);
	pSprite->SetCellSize(CVector2(72, 72));
	pSprite->SetAtlasGridSize(CVector2(17, 3));
	pSprite->SetSampleRate(15);
	pSprite->SetLoop(true);
	pSprite->AddFrame(CVector2(2, 1));
	pSprite->AddFrame(CVector2(2, 2));
	pSprite->AddFrame(CVector2(2, 1));
	pSprite->AddFrame(CVector2(2, 2));
	pSprite->AddFrame(CVector2(2, 1));
	pSprite->AddFrame(CVector2(2, 2));
	pSprite->AddFrame(CVector2(2, 1));
	pSprite->AddFrame(CVector2(2, 2));
	pSprite->AddFrame(CVector2(2, 1));
	pSprite->AddFrame(CVector2(2, 2));
	pSprite->AddFrame(CVector2(2, 1));
	pSprite->AddFrame(CVector2(2, 2));
	pSprite->SetSpriteKey("SCVAttack1");
	pRenderer->AddSprite("SCVAttack1", pSprite);
	pSprite->SaveSprite("SCVAttack1.aclp");
	delete pSprite;

	pSprite = new CSprite;
	pSprite->SetAtlas(pAtlasTexture);
	pSprite->SetCellSize(CVector2(72, 72));
	pSprite->SetAtlasGridSize(CVector2(17, 3));
	pSprite->SetSampleRate(15);
	pSprite->SetLoop(true);
	pSprite->AddFrame(CVector2(4, 1));
	pSprite->AddFrame(CVector2(4, 2));
	pSprite->AddFrame(CVector2(4, 1));
	pSprite->AddFrame(CVector2(4, 2));
	pSprite->AddFrame(CVector2(4, 1));
	pSprite->AddFrame(CVector2(4, 2));
	pSprite->AddFrame(CVector2(4, 1));
	pSprite->AddFrame(CVector2(4, 2));
	pSprite->AddFrame(CVector2(4, 1));
	pSprite->AddFrame(CVector2(4, 2));
	pSprite->AddFrame(CVector2(4, 1));
	pSprite->AddFrame(CVector2(4, 2));
	pSprite->SetSpriteKey("SCVAttack2");
	pRenderer->AddSprite("SCVAttack2", pSprite);
	pSprite->SaveSprite("SCVAttack2.aclp");
	delete pSprite;

	pSprite = new CSprite;
	pSprite->SetAtlas(pAtlasTexture);
	pSprite->SetCellSize(CVector2(72, 72));
	pSprite->SetAtlasGridSize(CVector2(17, 3));
	pSprite->SetSampleRate(15);
	pSprite->SetLoop(true);
	pSprite->AddFrame(CVector2(6, 1));
	pSprite->AddFrame(CVector2(6, 2));
	pSprite->AddFrame(CVector2(6, 1));
	pSprite->AddFrame(CVector2(6, 2));
	pSprite->AddFrame(CVector2(6, 1));
	pSprite->AddFrame(CVector2(6, 2));
	pSprite->AddFrame(CVector2(6, 1));
	pSprite->AddFrame(CVector2(6, 2));
	pSprite->AddFrame(CVector2(6, 1));
	pSprite->AddFrame(CVector2(6, 2));
	pSprite->AddFrame(CVector2(6, 1));
	pSprite->AddFrame(CVector2(6, 2));
	pSprite->SetSpriteKey("SCVAttack3");
	pRenderer->AddSprite("SCVAttack3", pSprite);
	pSprite->SaveSprite("SCVAttack3.aclp");
	delete pSprite;

	pSprite = new CSprite;
	pSprite->SetAtlas(pAtlasTexture);
	pSprite->SetCellSize(CVector2(72, 72));
	pSprite->SetAtlasGridSize(CVector2(17, 3));
	pSprite->SetSampleRate(15);
	pSprite->SetLoop(true);
	pSprite->AddFrame(CVector2(8, 1));
	pSprite->AddFrame(CVector2(8, 2));
	pSprite->AddFrame(CVector2(8, 1));
	pSprite->AddFrame(CVector2(8, 2));
	pSprite->AddFrame(CVector2(8, 1));
	pSprite->AddFrame(CVector2(8, 2));
	pSprite->AddFrame(CVector2(8, 1));
	pSprite->AddFrame(CVector2(8, 2));
	pSprite->AddFrame(CVector2(8, 1));
	pSprite->AddFrame(CVector2(8, 2));
	pSprite->AddFrame(CVector2(8, 1));
	pSprite->AddFrame(CVector2(8, 2));
	pSprite->SetSpriteKey("SCVAttack4");
	pRenderer->AddSprite("SCVAttack4", pSprite);
	pSprite->SaveSprite("SCVAttack4.aclp");
	delete pSprite;

	pSprite = new CSprite;
	pSprite->SetAtlas(pAtlasTexture);
	pSprite->SetCellSize(CVector2(72, 72));
	pSprite->SetAtlasGridSize(CVector2(17, 3));
	pSprite->SetSampleRate(15);
	pSprite->SetLoop(true);
	pSprite->AddFrame(CVector2(10, 1));
	pSprite->AddFrame(CVector2(10, 2));
	pSprite->AddFrame(CVector2(10, 1));
	pSprite->AddFrame(CVector2(10, 2));
	pSprite->AddFrame(CVector2(10, 1));
	pSprite->AddFrame(CVector2(10, 2));
	pSprite->AddFrame(CVector2(10, 1));
	pSprite->AddFrame(CVector2(10, 2));
	pSprite->AddFrame(CVector2(10, 1));
	pSprite->AddFrame(CVector2(10, 2));
	pSprite->AddFrame(CVector2(10, 1));
	pSprite->AddFrame(CVector2(10, 2));
	pSprite->SetSpriteKey("SCVAttack5");
	pRenderer->AddSprite("SCVAttack5", pSprite);
	pSprite->SaveSprite("SCVAttack5.aclp");
	delete pSprite;

	pSprite = new CSprite;
	pSprite->SetAtlas(pAtlasTexture);
	pSprite->SetCellSize(CVector2(72, 72));
	pSprite->SetAtlasGridSize(CVector2(17, 3));
	pSprite->SetSampleRate(15);
	pSprite->SetLoop(true);
	pSprite->AddFrame(CVector2(12, 1));
	pSprite->AddFrame(CVector2(12, 2));
	pSprite->AddFrame(CVector2(12, 1));
	pSprite->AddFrame(CVector2(12, 2));
	pSprite->AddFrame(CVector2(12, 1));
	pSprite->AddFrame(CVector2(12, 2));
	pSprite->AddFrame(CVector2(12, 1));
	pSprite->AddFrame(CVector2(12, 2));
	pSprite->AddFrame(CVector2(12, 1));
	pSprite->AddFrame(CVector2(12, 2));
	pSprite->AddFrame(CVector2(12, 1));
	pSprite->AddFrame(CVector2(12, 2));
	pSprite->SetSpriteKey("SCVAttack6");
	pRenderer->AddSprite("SCVAttack6", pSprite);
	pSprite->SaveSprite("SCVAttack6.aclp");
	delete pSprite;

	pSprite = new CSprite;
	pSprite->SetAtlas(pAtlasTexture);
	pSprite->SetCellSize(CVector2(72, 72));
	pSprite->SetAtlasGridSize(CVector2(17, 3));
	pSprite->SetSampleRate(15);
	pSprite->SetLoop(true);
	pSprite->AddFrame(CVector2(14, 1));
	pSprite->AddFrame(CVector2(14, 2));
	pSprite->AddFrame(CVector2(14, 1));
	pSprite->AddFrame(CVector2(14, 2));
	pSprite->AddFrame(CVector2(14, 1));
	pSprite->AddFrame(CVector2(14, 2));
	pSprite->AddFrame(CVector2(14, 1));
	pSprite->AddFrame(CVector2(14, 2));
	pSprite->AddFrame(CVector2(14, 1));
	pSprite->AddFrame(CVector2(14, 2));
	pSprite->AddFrame(CVector2(14, 1));
	pSprite->AddFrame(CVector2(14, 2));
	pSprite->SetSpriteKey("SCVAttack7");
	pRenderer->AddSprite("SCVAttack7", pSprite);
	pSprite->SaveSprite("SCVAttack7.aclp");
	delete pSprite;

	pSprite = new CSprite;
	pSprite->SetAtlas(pAtlasTexture);
	pSprite->SetCellSize(CVector2(72, 72));
	pSprite->SetAtlasGridSize(CVector2(17, 3));
	pSprite->SetSampleRate(15);
	pSprite->SetLoop(true);
	pSprite->AddFrame(CVector2(16, 1));
	pSprite->AddFrame(CVector2(16, 2));
	pSprite->AddFrame(CVector2(16, 1));
	pSprite->AddFrame(CVector2(16, 2));
	pSprite->AddFrame(CVector2(16, 1));
	pSprite->AddFrame(CVector2(16, 2));
	pSprite->AddFrame(CVector2(16, 1));
	pSprite->AddFrame(CVector2(16, 2));
	pSprite->AddFrame(CVector2(16, 1));
	pSprite->AddFrame(CVector2(16, 2));
	pSprite->AddFrame(CVector2(16, 1));
	pSprite->AddFrame(CVector2(16, 2));
	pSprite->SetSpriteKey("SCVAttack8");
	pRenderer->AddSprite("SCVAttack8", pSprite);
	pSprite->SaveSprite("SCVAttack8.aclp");
	delete pSprite;


	pAtlasTexture = GET_SINGLE(CResourceManager)->FindTexture("SCVLeft");
	pSprite = new CSprite;
	pSprite->SetAtlas(pAtlasTexture);
	pSprite->SetCellSize(CVector2(72, 72));
	pSprite->SetAtlasGridSize(CVector2(17, 3));
	pSprite->SetSampleRate(15);
	pSprite->SetLoop(true);
	pSprite->AddFrame(CVector2(2, 1));
	pSprite->AddFrame(CVector2(2, 2));
	pSprite->AddFrame(CVector2(2, 1));
	pSprite->AddFrame(CVector2(2, 2));
	pSprite->AddFrame(CVector2(2, 1));
	pSprite->AddFrame(CVector2(2, 2));
	pSprite->AddFrame(CVector2(2, 1));
	pSprite->AddFrame(CVector2(2, 2));
	pSprite->AddFrame(CVector2(2, 1));
	pSprite->AddFrame(CVector2(2, 2));
	pSprite->AddFrame(CVector2(2, 1));
	pSprite->AddFrame(CVector2(2, 2));
	pSprite->SetSpriteKey("SCVAttack9");
	pRenderer->AddSprite("SCVAttack9", pSprite);
	pSprite->SaveSprite("SCVAttack9.aclp");
	delete pSprite;

	pSprite = new CSprite;
	pSprite->SetAtlas(pAtlasTexture);
	pSprite->SetCellSize(CVector2(72, 72));
	pSprite->SetAtlasGridSize(CVector2(17, 3));
	pSprite->SetSampleRate(15);
	pSprite->SetLoop(true);
	pSprite->AddFrame(CVector2(4, 1));
	pSprite->AddFrame(CVector2(4, 2));
	pSprite->AddFrame(CVector2(4, 1));
	pSprite->AddFrame(CVector2(4, 2));
	pSprite->AddFrame(CVector2(4, 1));
	pSprite->AddFrame(CVector2(4, 2));
	pSprite->AddFrame(CVector2(4, 1));
	pSprite->AddFrame(CVector2(4, 2));
	pSprite->AddFrame(CVector2(4, 1));
	pSprite->AddFrame(CVector2(4, 2));
	pSprite->AddFrame(CVector2(4, 1));
	pSprite->AddFrame(CVector2(4, 2));
	pSprite->SetSpriteKey("SCVAttack10");
	pRenderer->AddSprite("SCVAttack10", pSprite);
	pSprite->SaveSprite("SCVAttack10.aclp");
	delete pSprite;

	pSprite = new CSprite;
	pSprite->SetAtlas(pAtlasTexture);
	pSprite->SetCellSize(CVector2(72, 72));
	pSprite->SetAtlasGridSize(CVector2(17, 3));
	pSprite->SetSampleRate(15);
	pSprite->SetLoop(true);
	pSprite->AddFrame(CVector2(6, 1));
	pSprite->AddFrame(CVector2(6, 2));
	pSprite->AddFrame(CVector2(6, 1));
	pSprite->AddFrame(CVector2(6, 2));
	pSprite->AddFrame(CVector2(6, 1));
	pSprite->AddFrame(CVector2(6, 2));
	pSprite->AddFrame(CVector2(6, 1));
	pSprite->AddFrame(CVector2(6, 2));
	pSprite->AddFrame(CVector2(6, 1));
	pSprite->AddFrame(CVector2(6, 2));
	pSprite->AddFrame(CVector2(6, 1));
	pSprite->AddFrame(CVector2(6, 2));
	pSprite->SetSpriteKey("SCVAttack11");
	pRenderer->AddSprite("SCVAttack11", pSprite);
	pSprite->SaveSprite("SCVAttack11.aclp");
	delete pSprite;

	pSprite = new CSprite;
	pSprite->SetAtlas(pAtlasTexture);
	pSprite->SetCellSize(CVector2(72, 72));
	pSprite->SetAtlasGridSize(CVector2(17, 3));
	pSprite->SetSampleRate(15);
	pSprite->SetLoop(true);
	pSprite->AddFrame(CVector2(8, 1));
	pSprite->AddFrame(CVector2(8, 2));
	pSprite->AddFrame(CVector2(8, 1));
	pSprite->AddFrame(CVector2(8, 2));
	pSprite->AddFrame(CVector2(8, 1));
	pSprite->AddFrame(CVector2(8, 2));
	pSprite->AddFrame(CVector2(8, 1));
	pSprite->AddFrame(CVector2(8, 2));
	pSprite->AddFrame(CVector2(8, 1));
	pSprite->AddFrame(CVector2(8, 2));
	pSprite->AddFrame(CVector2(8, 1));
	pSprite->AddFrame(CVector2(8, 2));
	pSprite->SetSpriteKey("SCVAttack12");
	pRenderer->AddSprite("SCVAttack12", pSprite);
	pSprite->SaveSprite("SCVAttack12.aclp");
	delete pSprite;

	pSprite = new CSprite;
	pSprite->SetAtlas(pAtlasTexture);
	pSprite->SetCellSize(CVector2(72, 72));
	pSprite->SetAtlasGridSize(CVector2(17, 3));
	pSprite->SetSampleRate(15);
	pSprite->SetLoop(true);
	pSprite->AddFrame(CVector2(10, 1));
	pSprite->AddFrame(CVector2(10, 2));
	pSprite->AddFrame(CVector2(10, 1));
	pSprite->AddFrame(CVector2(10, 2));
	pSprite->AddFrame(CVector2(10, 1));
	pSprite->AddFrame(CVector2(10, 2));
	pSprite->AddFrame(CVector2(10, 1));
	pSprite->AddFrame(CVector2(10, 2));
	pSprite->AddFrame(CVector2(10, 1));
	pSprite->AddFrame(CVector2(10, 2));
	pSprite->AddFrame(CVector2(10, 1));
	pSprite->AddFrame(CVector2(10, 2));
	pSprite->SetSpriteKey("SCVAttack13");
	pRenderer->AddSprite("SCVAttack13", pSprite);
	pSprite->SaveSprite("SCVAttack13.aclp");
	delete pSprite;

	pSprite = new CSprite;
	pSprite->SetAtlas(pAtlasTexture);
	pSprite->SetCellSize(CVector2(72, 72));
	pSprite->SetAtlasGridSize(CVector2(17, 3));
	pSprite->SetSampleRate(15);
	pSprite->SetLoop(true);
	pSprite->AddFrame(CVector2(12, 1));
	pSprite->AddFrame(CVector2(12, 2));
	pSprite->AddFrame(CVector2(12, 1));
	pSprite->AddFrame(CVector2(12, 2));
	pSprite->AddFrame(CVector2(12, 1));
	pSprite->AddFrame(CVector2(12, 2));
	pSprite->AddFrame(CVector2(12, 1));
	pSprite->AddFrame(CVector2(12, 2));
	pSprite->AddFrame(CVector2(12, 1));
	pSprite->AddFrame(CVector2(12, 2));
	pSprite->AddFrame(CVector2(12, 1));
	pSprite->AddFrame(CVector2(12, 2));
	pSprite->SetSpriteKey("SCVAttack14");
	pRenderer->AddSprite("SCVAttack14", pSprite);
	pSprite->SaveSprite("SCVAttack14.aclp");
	delete pSprite;

	pSprite = new CSprite;
	pSprite->SetAtlas(pAtlasTexture);
	pSprite->SetCellSize(CVector2(72, 72));
	pSprite->SetAtlasGridSize(CVector2(17, 3));
	pSprite->SetSampleRate(15);
	pSprite->SetLoop(true);
	pSprite->AddFrame(CVector2(14, 1));
	pSprite->AddFrame(CVector2(14, 2));
	pSprite->AddFrame(CVector2(14, 1));
	pSprite->AddFrame(CVector2(14, 2));
	pSprite->AddFrame(CVector2(14, 1));
	pSprite->AddFrame(CVector2(14, 2));
	pSprite->AddFrame(CVector2(14, 1));
	pSprite->AddFrame(CVector2(14, 2));
	pSprite->AddFrame(CVector2(14, 1));
	pSprite->AddFrame(CVector2(14, 2));
	pSprite->AddFrame(CVector2(14, 1));
	pSprite->AddFrame(CVector2(14, 2));
	pSprite->SetSpriteKey("SCVAttack15");
	pRenderer->AddSprite("SCVAttack15", pSprite);
	pSprite->SaveSprite("SCVAttack15.aclp");
	delete pSprite;


	pRenderer->ChangeCurrentClip("SCVStand0");

	GET_SINGLE(CFileStream)->SaveUnit(pSCV, "SCV.unit");
}
#pragma endregion



#pragma region Enemy Command


#pragma region CommandCenter

{
	int iCommandCenterX = 110;
	int iCommandCenterY = 110;
	{
		CGameObject* pCommandCenter = new CGameObject("CommandCenter");
		pCommandCenter->SetPilot(pPlayer2->GetComponent<CPlayer>());
		pGroundUnitLayer->AddGameObject(pCommandCenter);
		pCommandCenter->GetTransform()->SetPivot(0.5f, 0.5f);
		pCommandCenter->GetTransform()->SetPosition(iCommandCenterX * 32, iCommandCenterY * 32);
		CEllipseRenderer* pEllipseRenderer = pCommandCenter->AddComponent<CEllipseRenderer>();
		pEllipseRenderer->SetMinorAxisLength(45);
		pEllipseRenderer->SetThickness(2);
		pEllipseRenderer->SetLocalPosition(0, 5);

		CSpriteRenderer* pRenderer = pCommandCenter->AddComponent<CSpriteRenderer>();
		pRenderer->SetSize(128, 160);

		CCommandCenter* pCreateUnit = pCommandCenter->AddComponent<CCommandCenter>();

		CSprite* pDeathSprite = new CSprite;
		pDeathSprite->SetAtlas(GET_SINGLE(CResourceManager)->FindTexture("Terran_Explosion_XLarge"));
		pDeathSprite->SetAtlasGridSize(1, 15);
		pDeathSprite->SetSampleRate(10);
		pDeathSprite->SetLoop(false);
		pDeathSprite->SetCellSize(252, 200);
		pDeathSprite->AddFrame(CVector2(0, 0));
		pDeathSprite->AddFrame(CVector2(1, 0));
		pDeathSprite->AddFrame(CVector2(2, 0));
		pDeathSprite->AddFrame(CVector2(3, 0));
		pDeathSprite->AddFrame(CVector2(4, 0));
		pDeathSprite->AddFrame(CVector2(5, 0));
		pDeathSprite->AddFrame(CVector2(6, 0));
		pDeathSprite->AddFrame(CVector2(7, 0));
		pDeathSprite->AddFrame(CVector2(8, 0));
		pDeathSprite->AddFrame(CVector2(9, 0));
		pDeathSprite->AddFrame(CVector2(10, 0));
		pDeathSprite->AddFrame(CVector2(11, 0));
		pDeathSprite->AddFrame(CVector2(12, 0));
		pDeathSprite->AddFrame(CVector2(13, 0));
		pDeathSprite->AddFrame(CVector2(14, 0));

		pDeathSprite->SaveSprite("CommandCenterDeath.aclp");
		pRenderer->AddSprite("CommandCenterDeath", pDeathSprite);
		delete pDeathSprite;

		CStructure* pStructure = pCommandCenter->AddComponent<CStructure>();
		pStructure->SetRequireGas(0);
		pStructure->SetRequireMineral(400);
		pStructure->SetSupply(10);
		pStructure->SetBuildTime(10);
		pStructure->AddBuildableTile(0, 1);
		pStructure->AddBuildableTile(1, 1);
		pStructure->AddBuildableTile(2, 1);
		pStructure->AddBuildableTile(3, 1);
		pStructure->AddBuildableTile(0, 2);
		pStructure->AddBuildableTile(1, 2);
		pStructure->AddBuildableTile(2, 2);
		pStructure->AddBuildableTile(3, 2);
		pStructure->AddBuildableTile(0, 3);
		pStructure->AddBuildableTile(1, 3);
		pStructure->AddBuildableTile(2, 3);
		pStructure->AddBuildableTile(3, 3);


		CUnitStatus* pStatus = pCommandCenter->AddComponent<CUnitStatus>();
		pStatus->SetMaxHP(1500);
		pStatus->SetHPMaxCondition();
		pStatus->SetMaxMP(0);
		pStatus->SetHPMaxCondition();
		pStatus->SetMaxShield(0);
		pStatus->SetHPMaxCondition();
		pStatus->SetRequirement(pStructure->GetBuildTime(), 400, 0, 0);
		pStatus->SetSightRadius(8);

		CCircleCollider* pCollider = pCommandCenter->AddComponent<CCircleCollider>();
		pCollider->SetRadius(40);

		CUnitInfo* pInfo = pCommandCenter->AddComponent<CUnitInfo>();

		CSprite* pSprite = new CSprite;
		CTexture* pAtlas = GET_SINGLE(CResourceManager)->FindTexture("CommandCenter");
		pSprite->SetAtlas(pAtlas);
		pSprite->SetAtlasGridSize(10, 1);
		pSprite->SetCellSize(128, 160);
		pSprite->SetSampleRate(4 / pStructure->GetBuildTime());
		pSprite->SetLoop(false);

		pSprite->AddFrame(CVector2(0, 0));
		pSprite->AddFrame(CVector2(1, 0));
		pSprite->AddFrame(CVector2(2, 0));
		pSprite->AddFrame(CVector2(3, 0));
		pRenderer->AddSprite("CommandCenterBuild", pSprite);
		pSprite->SaveSprite("CommandCenterBuild.aclp");
		delete pSprite;

		pSprite = new CSprite;
		pSprite->SetAtlas(pAtlas);
		pSprite->SetAtlasGridSize(10, 1);
		pSprite->SetCellSize(128, 160);
		pSprite->SetSampleRate(1);
		pSprite->SetLoop(true);

		pSprite->AddFrame(CVector2(4, 0));
		pRenderer->AddSprite("CommandCenterNormal", pSprite);
		pSprite->SaveSprite("CommandCenterNormal.aclp");
		delete pSprite;

		pSprite = new CSprite;
		pSprite->SetAtlas(pAtlas);
		pSprite->SetAtlasGridSize(10, 1);
		pSprite->SetCellSize(128, 160);
		pSprite->SetSampleRate(5);
		pSprite->SetLoop(true);

		pSprite->AddFrame(CVector2(4, 0));
		pSprite->AddFrame(CVector2(5, 0));
		pSprite->AddFrame(CVector2(4, 0));
		pSprite->AddFrame(CVector2(4, 0));
		pSprite->AddFrame(CVector2(4, 0));
		pSprite->AddFrame(CVector2(5, 0));
		pSprite->AddFrame(CVector2(4, 0));
		pSprite->AddFrame(CVector2(5, 0));
		pSprite->AddFrame(CVector2(5, 0));
		pSprite->AddFrame(CVector2(5, 0));
		pSprite->AddFrame(CVector2(4, 0));
		pSprite->AddFrame(CVector2(5, 0));

		pRenderer->AddSprite("CommandCenterWork", pSprite);
		pSprite->SaveSprite("CommandCenterWork.aclp");
		delete pSprite;


		pSprite = new CSprite;
		pSprite->SetAtlas(pAtlas);
		pSprite->SetAtlasGridSize(10, 1);
		pSprite->SetCellSize(128, 160);
		pSprite->SetSampleRate(2);
		pSprite->SetLoop(false);

		pSprite->AddFrame(CVector2(9, 0));
		pSprite->AddFrame(CVector2(6, 0));
		pSprite->AddFrame(CVector2(7, 0));
		pSprite->AddFrame(CVector2(8, 0));

		pRenderer->AddSprite("CommandCenterLiftUp", pSprite);
		pSprite->SaveSprite("CommandCenterLiftUp.aclp");
		delete pSprite;


		pSprite = new CSprite;
		pSprite->SetAtlas(pAtlas);
		pSprite->SetAtlasGridSize(10, 1);
		pSprite->SetCellSize(128, 160);
		pSprite->SetSampleRate(1);
		pSprite->SetLoop(true);

		pSprite->AddFrame(CVector2(8, 0));

		pRenderer->AddSprite("CommandCenterAir", pSprite);
		pSprite->SaveSprite("CommandCenterAir.aclp");
		delete pSprite;

		pSprite = new CSprite;
		pSprite->SetAtlas(pAtlas);
		pSprite->SetAtlasGridSize(10, 1);
		pSprite->SetCellSize(128, 160);
		pSprite->SetSampleRate(2);
		pSprite->SetLoop(false);

		pSprite->AddFrame(CVector2(8, 0));
		pSprite->AddFrame(CVector2(7, 0));
		pSprite->AddFrame(CVector2(6, 0));
		pSprite->AddFrame(CVector2(9, 0));

		pRenderer->AddSprite("CommandCenterLiftDown", pSprite);
		pSprite->SaveSprite("CommandCenterLiftDown.aclp");
		delete pSprite;

		pRenderer->ChangeCurrentClip("CommandCenterNormal");


		GET_SINGLE(CFileStream)->SaveUnit(pCommandCenter, "CommandCenter.unit");
	}
}


for (int i = 0; i < 3; ++i)
{
	for(int j = 0 ; j < 4 ; ++j )
	{
		CGameObject* pMarine = GET_SINGLE(CResourceManager)->FindUnit("Marine")->clone();
		pMarine->SetPilot(pPlayer2Component);
		pGroundUnitLayer->AddGameObject(pMarine);
		pMarine->SetSelected(false);
		pMarine->SetToAirUnit(false);

		pMarine->GetComponent<CSpriteRenderer>()->ChangeCurrentClip("MarineStand0");
		pMarine->GetTransform()->SetPosition(103 * 32 + i * 32, 103 * 32 + j * 32);
	}
}


#pragma endregion

#pragma endregion



	/*
#pragma region CreateTestUnit
	{
		CVector2 spawnPosition = CVector2(100, 100);

		CGameObject* pMarine = new CGameObject("Marine");
		pGroundUnitLayer->AddGameObject(pMarine);

		pMarine->GetTransform()->SetPosition(spawnPosition);
		pMarine->GetTransform()->SetPivot(0.5f, 0.6f);

		//CRectCollider* pRectCollider = pPlayer->AddComponent<CRectCollider>();
		//pRectCollider->SetSize(20, 30);

		CCircleCollider* pCircleCollider = pMarine->AddComponent<CCircleCollider>();
		pCircleCollider->SetRadius(12);
		pCircleCollider->SetTileCollisionRadius(12);
		pCircleCollider->SetLocalPosition(CVector2(0, 0));


		CEllipseRenderer* pSelectEllipseRenderer = pMarine->AddComponent<CEllipseRenderer>();
		pSelectEllipseRenderer->SetMinorAxisLength(8);
		pSelectEllipseRenderer->SetThickness(2);
		pSelectEllipseRenderer->SetLocalPosition(0, 3);

		CSpriteRenderer* pRenderer = pMarine->AddComponent<CSpriteRenderer>();
		pRenderer->SetSize(64, 64);
		

		{
			CSprite* pSprite = new CSprite;
			CTexture* pAtlasTexture = GET_SINGLE(CResourceManager)->FindTexture("MarineRight");
			
			//pAtlasTexture = GET_SINGLE(CFileStream)->SetTeamColor("RedRight", "Red\\Terran\\marine_right.bmp", pAtlasTexture, 0.953125f, 0.015625f, 0.015625f);
			//pAtlasTexture = GET_SINGLE(CFileStream)->SetTeamColor("BlueRight", "Blue\\Terran\\marine_right.bmp", pAtlasTexture, 0.046875f, 0.28125f, 0.796875f);
			//pAtlasTexture = GET_SINGLE(CFileStream)->SetTeamColor("TealRight", "Teal\\Terran\\marine_right.bmp", pAtlasTexture, 0.171875f, 0.703125f, 0.578125f);
			//pAtlasTexture = GET_SINGLE(CFileStream)->SetTeamColor("PurpleRight", "Purple\\Terran\\marine_right.bmp", pAtlasTexture, 0.53125f, 0.25f, 0.609375f);
			//pAtlasTexture = GET_SINGLE(CFileStream)->SetTeamColor("OrangeRight", "Orange\\Terran\\marine_right.bmp", pAtlasTexture, 0.96875f, 0.546875f, 0.078125f);
			//pAtlasTexture = GET_SINGLE(CFileStream)->SetTeamColor("BrownRight", "Brown\\Terran\\marine_right.bmp", pAtlasTexture, 0.4375f, 0.1875f, 0.078125f);
			//pAtlasTexture = GET_SINGLE(CFileStream)->SetTeamColor("WhiteRight", "White\\Terran\\marine_right.bmp", pAtlasTexture, 0.796875f, 0.875f, 0.8125f);
			//pAtlasTexture = GET_SINGLE(CFileStream)->SetTeamColor("YellowRight", "Yellow\\Terran\\marine_right.bmp", pAtlasTexture, 0.984375f, 0.984375f, 0.21875f);

			pSprite->SetAtlas(pAtlasTexture);
			pSprite->SetCellSize(CVector2(64,64));
			pSprite->SetAtlasGridSize(CVector2(17,14));
			pSprite->SetSampleRate(30);
			pSprite->SetLoop(true);

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
			pRenderer->AddSprite("MarineAttack0", pSprite);
			pRenderer->ChangeCurrentClip("MarineAttack0");

			pSprite->SaveSprite("MarineAttack0.aclp");
			delete pSprite;


			pSprite = new CSprite;
			pSprite->SetAtlas(pAtlasTexture);
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
			pSprite->SaveSprite("MarineAttack1.aclp");
			delete pSprite;

			pSprite = new CSprite;
			pSprite->SetAtlas(pAtlasTexture);
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
			pSprite->SaveSprite("MarineAttack2.aclp");
			delete pSprite;


			pSprite = new CSprite;
			pSprite->SetAtlas(pAtlasTexture);
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
			pSprite->SaveSprite("MarineAttack3.aclp");
			delete pSprite;

			pSprite = new CSprite;
			pSprite->SetAtlas(pAtlasTexture);
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
			pSprite->SaveSprite("MarineAttack4.aclp");
			delete pSprite;

			pSprite = new CSprite;
			pSprite->SetAtlas(pAtlasTexture);
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
			pSprite->SaveSprite("MarineAttack5.aclp");
			delete pSprite;

			pSprite = new CSprite;
			pSprite->SetAtlas(pAtlasTexture);
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
			pSprite->SaveSprite("MarineAttack6.aclp");
			delete pSprite;

			pSprite = new CSprite;
			pSprite->SetAtlas(pAtlasTexture);
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
			pSprite->SaveSprite("MarineAttack7.aclp");
			delete pSprite;

			pSprite = new CSprite;
			pSprite->SetAtlas(pAtlasTexture);
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
			pSprite->SaveSprite("MarineAttack8.aclp");
			delete pSprite;
		}

		{
			CSprite* pSprite = new CSprite;
			CTexture* pAtlasTexture = GET_SINGLE(CResourceManager)->FindTexture("MarineLeft");
			//CTexture* pColoredAtlasTexture = GET_SINGLE(CFileStream)->SetTeamColor("MarineRedLeft", "marine_left_temp.bmp", pAtlasTexture, -1, 0, 0);
			//CTexture* pColoredAtlasTexture = GET_SINGLE(CFileStream)->SetTeamColor("BlueLeft", "marine_left_temp.bmp", pAtlasTexture, 0, 0, -1);
			//CTexture* pColoredAtlasTexture = GET_SINGLE(CFileStream)->SetTeamColor("GreenLeft", "marine_left_temp.bmp", pAtlasTexture,50, -1, 0);
			//CTexture* pColoredAtlasTexture = GET_SINGLE(CFileStream)->SetTeamColor("PurpleLeft", "marine_left_temp.bmp", pAtlasTexture, 125, 0, -1);

			pSprite->SetAtlas(pAtlasTexture);
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
			pSprite->SaveSprite("MarineAttack9.aclp");
			delete pSprite;

			pSprite = new CSprite;
			pSprite->SetAtlas(pAtlasTexture);
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
			pSprite->SaveSprite("MarineAttack10.aclp");
			delete pSprite;


			pSprite = new CSprite;
			pSprite->SetAtlas(pAtlasTexture);
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
			pSprite->SaveSprite("MarineAttack11.aclp");
			delete pSprite;

			pSprite = new CSprite;
			pSprite->SetAtlas(pAtlasTexture);
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
			pSprite->SaveSprite("MarineAttack12.aclp");
			delete pSprite;

			pSprite = new CSprite;
			pSprite->SetAtlas(pAtlasTexture);
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
			pSprite->SaveSprite("MarineAttack13.aclp");
			delete pSprite;

			pSprite = new CSprite;
			pSprite->SetAtlas(pAtlasTexture);
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
			pSprite->SaveSprite("MarineAttack14.aclp");
			delete pSprite;

			pSprite = new CSprite;
			pSprite->SetAtlas(pAtlasTexture);
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
			pSprite->SaveSprite("MarineAttack15.aclp");
			delete pSprite;
		}


		GET_SINGLE(CFileStream)->SaveUnit(pMarine, "Marine.unit");

		CTestMove* pMove = pMarine->AddComponent<CTestMove>();
	}
#pragma endregion
*/


#pragma region CreateTerrain
	{
		CGameObject* pTerrain = new CGameObject("Terrain");
		pLayer->AddGameObject(pTerrain);
		CTerrainRenderer* pRenderer = pTerrain->AddComponent<CTerrainRenderer>();
		//오브젝트 불러오는 부분에서 단순하게 맵에서 복사해서 쓸 수 있도록 하고 있으므로, 수정 시, 새로 저장 하기만 하면 된다.
		GET_SINGLE(CFileStream)->LoadMap(this, pGroundUnitLayer, pRenderer, "Hunter.map");
		{
			list<CGameObject*> resources = pGroundUnitLayer->FindGameObjects("Mineral");
			list<CGameObject*>::iterator iter;
			list<CGameObject*>::iterator iterEnd = resources.end();
			for (iter = resources.begin(); iter != iterEnd; ++iter)
			{
				(*iter)->SetPilot(NULL);
				(*iter)->SetSelected(false);
			}
		}

		{
			list<CGameObject*> resources = pGroundUnitLayer->FindGameObjects("VespeneGeyser");
			list<CGameObject*>::iterator iter;
			list<CGameObject*>::iterator iterEnd = resources.end();
			for (iter = resources.begin(); iter != iterEnd; ++iter)
			{
				(*iter)->SetPilot(NULL);
				(*iter)->SetSelected(false);
			}
		}

		m_pTerrainRenderer = pRenderer;

		GET_SINGLE(CMinimapManager)->CreateTerrainImage(this, pRenderer);
	}
#pragma endregion

#pragma region Minimap
	{
		CGameObject* pMinimap = new CGameObject("Minimap");
		pMinimap->AddComponent<CMinimapRenderer>();
		pUIMiddleLayer->AddGameObject(pMinimap);

		pMinimap->GetTransform()->SetPivot(0.5f, 0.5f);
		pMinimap->GetTransform()->SetPosition(168, 523);
	}
#pragma endregion



switch (pPlayerComponent->GetRaceType())
{
case RT_TERRAN:
	pPlayerComponent->SetMineral(1000);
	pPlayerComponent->SetVespeneGas(1000);
	pPlayerComponent->SetCurrentPopulation(4);
	break;
case RT_PROTOSS:
	pPlayerComponent->SetMineral(650);
	break;
case RT_ZERG:
	pPlayerComponent->SetMineral(550);
	break;
default:
	break;
}

SetPlayerRandomColor();
GET_SINGLE(CFogOfWarManager)->SetTileSize(m_GridSize.x, m_GridSize.y);
}


CGameScene::~CGameScene()
{
}

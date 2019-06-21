#include "MainGameScene.h"
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



CMainGameScene::CMainGameScene()
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

#pragma region CreatePlayer & Option Setting

	GET_SINGLE(COption)->SetCameraSpeed(1024);
	GET_SINGLE(COption)->SetCursorClipped(false);

	CGameObject* pPlayer = new CGameObject("Player");
	pSystemLayer->AddGameObject(pPlayer);
	CPlayer* pPlayerComponent = pPlayer->AddComponent<CPlayer>();

	pPlayerComponent->SetTeamColor(TC_YELLOW);
	pPlayerComponent->SetRaceType(RT_TERRAN);
	pPlayerComponent->SetPlayerName("Eunsoo");
	AddPlayer(pPlayerComponent);

	//CGameObject* pFogOfWar = new CGameObject("FOW");
	//pFogOfWar->AddComponent<CFOW>();
	//pFogOfWarLayer->AddGameObject(pFogOfWar);


	GET_SINGLE(CResourceManager)->PlaySFX("Terran1");


#pragma endregion
	
#pragma region Create Camera

	GetCamera()->GameObject()->AddComponent<CCameraMove>();
	
#pragma endregion
	
#pragma region CreateUI

	/*{
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
	}*/

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

//
//#pragma region CreateTerrain
//	{
//		CGameObject* pTerrain = new CGameObject("Terrain");
//		pLayer->AddGameObject(pTerrain);
//		CTerrainRenderer* pRenderer = pTerrain->AddComponent<CTerrainRenderer>();
//		//오브젝트 불러오는 부분에서 단순하게 맵에서 복사해서 쓸 수 있도록 하고 있으므로, 수정 시, 새로 저장 하기만 하면 된다.
//		GET_SINGLE(CFileStream)->LoadMap(this, pGroundUnitLayer, pRenderer, "Hunter.map");
//		{
//			list<CGameObject*> resources = pGroundUnitLayer->FindGameObjects("Mineral");
//			list<CGameObject*>::iterator iter;
//			list<CGameObject*>::iterator iterEnd = resources.end();
//			for (iter = resources.begin(); iter != iterEnd; ++iter)
//			{
//				(*iter)->SetPilot(NULL);
//				(*iter)->SetSelected(false);
//				(*iter)->SetToAirUnit(false);
//			}
//		}
//
//		{
//			list<CGameObject*> resources = pGroundUnitLayer->FindGameObjects("VespeneGeyser");
//			list<CGameObject*>::iterator iter;
//			list<CGameObject*>::iterator iterEnd = resources.end();
//			for (iter = resources.begin(); iter != iterEnd; ++iter)
//			{
//				(*iter)->SetPilot(NULL);
//				(*iter)->SetSelected(false); 
//				(*iter)->SetToAirUnit(false);
//			}
//		}
//
//		m_pTerrainRenderer = pRenderer;
//
//		GET_SINGLE(CMinimapManager)->CreateTerrainImage(this, pRenderer);
//	}
//#pragma endregion



#pragma region Minimap
	{
		CGameObject* pMinimap = new CGameObject("Minimap");
		pMinimap->AddComponent<CMinimapRenderer>();
		pUIMiddleLayer->AddGameObject(pMinimap);

		pMinimap->GetTransform()->SetPivot(0.5f, 0.5f);
		pMinimap->GetTransform()->SetPosition(168, 523);
	}
#pragma endregion


	SetPlayerRandomColor();
	GET_SINGLE(CFogOfWarManager)->SetTileSize(m_GridSize.x, m_GridSize.y);
}


CMainGameScene::~CMainGameScene()
{
}

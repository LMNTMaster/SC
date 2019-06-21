#include "FileStream.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "GameObject.h"
#include "Component.h"
#include "Layer.h"
#include "Tile.h"
#include "Components\EllipseRenderer.h"
#include "Components\GridRenderer.h"
#include "Components\TextureRenderer.h"
#include "Components\SpriteRenderer.h"
#include "Components\RectangleRenderer.h"
#include "Components\TerrainRenderer.h"
#include "Components\UIRenderer.h"
#include "Components\Camera.h"
#include "Components\CameraMove.h"
#include "Components\CollisionTile.h"
#include "Components\DefaultUnitAnimator.h"
#include "Components\SystemManager.h"
#include "Components\TestMove.h"
#include "Components\Transform.h"
#include "Components\CircleCollider.h"
#include "Components\PixelCollider.h"
#include "Components\PointCollider.h"
#include "Components\RectCollider.h"
#include "Components\GameResource.h"
#include "Components\Move.h"
#include "Components\Attack.h"
#include "Components\AdvancedBuild.h"
#include "Components\Build.h"
#include "Components\Gather.h"
#include "Components\Hold.h"
#include "Components\Stop.h"
#include "Components\Repair.h"
#include "Components\UnitStatus.h"
#include "Components\Deffence.h"
#include "Components\Shield.h"
#include "Components\UnitInfo.h"
#include "Components\Patrol.h"
#include "Components\Stimpack.h"

#include "Components\Structure\Barracks.h"
#include "Components\Structure\Academy.h"
#include "Components\Structure\EngineeringBay.h"
#include "Components\Structure\Bunker.h"
#include "Components\Structure\Factory.h"
#include "Components\Structure\Starport.h"
#include "Components\Structure\Armory.h"
#include "Components\Structure\CommandCenter.h"

//Animator
#include "Components\Animator\SCVAnimator.h"
#include "Components\Animator\MineralOrb.h"
#include "Components\Animator\GasBox.h"
#include "Components\Animator\GasSac.h"
#include "Components\Animator\GasTank.h"
#include "Components\Animator\MarineAnimator.h"
#include "Components\Animator\FirebatAnimator.h"

#include "Components\Animator\BattlecruiserAnimator.h"
#include "Components\Animator\DropshipAnimator.h"
#include "Components\Animator\GhostAnimator.h"
#include "Components\Animator\ScienceVesselAnimator.h"
#include "Components\Animator\VultureAnimator.h"
#include "Components\Animator\WraithAnimator.h"


CFileStream* CFileStream::m_pInstance = NULL;

CFileStream::CFileStream()
{

}


CFileStream::~CFileStream()
{
}

void CFileStream::Initialize()
{	
	/*Default Color Setting*/
	m_pPaletteColor[0] = Color(0.953125f, 0.015625f, 0.015625f);		//RED;		 244, 4, 4
	m_pPaletteColor[1] = Color(0.046875f, 0.28125f, 0.796875f);		//BLUE;		12, 72 , 204
	m_pPaletteColor[2] = Color(0.171875f, 0.703125f, 0.578125f);		//TEAL;		44, 180, 148
	m_pPaletteColor[3] = Color(0.53125f, 0.25f, 0.609375f);				//PURPLE;	 136, 64, 156
	m_pPaletteColor[4] = Color(0.96875f, 0.546875f, 0.078125f);		//ORANGE;	248, 140, 20
	m_pPaletteColor[5] = Color(0.4375f, 0.1875f, 0.078125f);			//BROWN;		112, 48, 20
	m_pPaletteColor[6] = Color(0.796875f, 0.875f, 0.8125f);				//WHITE;		204, 224, 208
	m_pPaletteColor[7] = Color(0.984375f, 0.984375f, 0.21875f);		//YELLOW;		252, 252, 56

}

void CFileStream::LoadMap(CScene* pScene, CLayer* pTerrainLayer, CTerrainRenderer * pTerrainRenderer, const string & strFileName)
{

	FILE* pFile = NULL;

	char strFullPath[LONG_MAX_PATH] = {};
	strcpy(strFullPath, GET_SINGLE(CResourceManager)->FindPathMultiByte(MAP_PATH));
	strcat(strFullPath, strFileName.c_str());
	fopen_s(&pFile, strFullPath, "rb");

	if (pFile)
	{
		//타일 갯수 읽어옴
		int iGridWidth = 0;
		fread(&iGridWidth, 4, 1, pFile);
		int iGridHeight = 0;
		fread(&iGridHeight, 4, 1, pFile);

		pScene->m_GridSize = CVector2(iGridWidth, iGridHeight);
		pScene->m_TileSize = CVector2(32, 32);

		int iLength = iGridWidth * iGridHeight;

		//후에 값 변경을 위해 일단 더미를 채워 넣음.
		for (int i = 0; i < iLength; ++i)
		{
			CTile* pDummyTile = GET_SINGLE(CResourceManager)->GetTile(32);
			pTerrainRenderer->AddTile(pDummyTile);
		}

		for (int i = 0; i < iLength; ++i)
		{
			CVector2 TilePosition;
			bool bMovable = false;
			int iTileHeight = 0;
			int iTileKey = 0;
			//타일 정보 불러오기
			fread(&iTileKey, 4, 1, pFile);
			fread(&TilePosition, sizeof(CVector2), 1, pFile);
			fread(&bMovable, 1, 1, pFile);
			fread(&iTileHeight, 4, 1, pFile);

			CTile * pTile = GET_SINGLE(CResourceManager)->GetTileSet((int)(i / 128))[i % 128]->clone();
			//pTile->SetCamera(m_pGameObject->GetScene()->GetCamera()); // 아래에 ChangeTile에서 해주니 딱히 안해줘도 됨
			pTile->SetMovable(bMovable);
			pTile->SetWorldPosition(TilePosition);
			pTile->SetTerrainHeight(iTileHeight);
			//불러온 타일은 현재 TerrainRenderer에 옮겨준다.

			pTerrainRenderer->ChangeTile(i, pTile);
		}

		iLength = 0;

		//오브젝트 갯수 저장
		fread(&iLength, 4, 1, pFile);

		for (int i = 0; i < iLength; ++i)
		{
			int iKeyLength = 0;
			char strKey[256] = {};

			fread(&iKeyLength, 4, 1, pFile);
			fread(&strKey, 1, iKeyLength, pFile);

			CGameObject* pGameObject = GET_SINGLE(CResourceManager)->FindUnit(string(strKey))->clone();
			
			CVector2 position;
			CVector2 pivot;
			vector<CVector2> buildTile;
			vector<unsigned int> builtTileIndex;
			int buildTileSize = 0;
			int builtTileIndexSize = 0;

			fread(&position, sizeof(CVector2), 1, pFile);
			fread(&pivot, sizeof(CVector2), 1, pFile);
			fread(&buildTileSize, 4, 1, pFile);
			fread(&builtTileIndexSize, 4, 1, pFile);

			pGameObject->GetTransform()->SetPosition(position);
			pGameObject->GetTransform()->SetPivot(pivot);
			pGameObject->GetComponent<CStructure>()->ClearBuildableTile();
			pGameObject->GetComponent<CStructure>()->ClearBuiltTileIndex();

			for (int j = 0; j < buildTileSize; ++j)
			{
				CVector2 temp;
				fread(&temp, sizeof(CVector2), 1, pFile);
				pGameObject->GetComponent<CStructure>()->AddBuildableTile(temp.x, temp.y);
			}
			for (int j = 0; j < builtTileIndexSize; ++j)
			{
				unsigned int temp = 0;
				fread(&temp, 4, 1, pFile);
				pGameObject->GetComponent<CStructure>()->AddBuiltTileIndex(temp);
			}

			int iAnimationClipKeyLength = 0;
			char strAnimationClipKey[256] = {};

			fread(&iAnimationClipKeyLength, 4, 1, pFile);
			fread(&strAnimationClipKey, 1, iAnimationClipKeyLength, pFile);

			pTerrainLayer->AddGameObject(pGameObject);

			pGameObject->GetComponent<CSpriteRenderer>()->ChangeCurrentClip(string(strAnimationClipKey));
		}
		fclose(pFile);
	}

}

vector<PIXEL>* CFileStream::LoadBMP( class CTexture * pTexture)
{	
	return pTexture->GetPixel();	
}

void CFileStream::SaveBMP(const CTexture * pTexture)
{

}

void CFileStream::SaveBMP(const char* fileName, BITMAPFILEHEADER fh, BITMAPINFOHEADER ih, vector<PIXEL>* pPixels)
{
	
	
}

//기준이 될 색상은 1로 처리
CTexture * CFileStream::SetTeamColor(size_t iPlayerIndex, const string& strColor, const wstring& strCacheBaseDirectory, CTexture * pTexture)
{
	float r = m_pPaletteColor[iPlayerIndex].r;
	float g = m_pPaletteColor[iPlayerIndex].g;
	float b = m_pPaletteColor[iPlayerIndex].b;

	const char* tempDir = NULL;
	wstring strCacheDirectory = strCacheBaseDirectory;

	//파일 명
	char tempPath[LONG_MAX_PATH] = {};
	strcpy(tempPath, pTexture->GetTextureFileName());
	wchar_t wTemp[LONG_MAX_PATH] = {};
	MultiByteToWideChar(CP_ACP, 0, tempPath, sizeof(tempPath), wTemp, sizeof(wTemp));
	wstring wt = strCacheDirectory + wstring(wTemp);
	
	//WideCharToMultiByte(CP_ACP, 0, pPath, -1, tempPath, lstrlen(pPath), 0, 0);


	CTexture* pColoredTexture = GET_SINGLE(CResourceManager)->LoadTexture(string("Cache") + strColor + pTexture->GetTextureKey(), wt.c_str(), CACHE_PATH);
	if (pColoredTexture)
	{
		return pColoredTexture;
	}
	else
	{
		vector<PIXEL>* pixelData = pTexture->GetPixel();
		vector<PIXEL> colored = *pixelData;

		int iTextureWidth = pTexture->GetTextureInfo().bmWidth;
		int iTextureHeight = pTexture->GetTextureInfo().bmHeight;

		for (int i = 0; i < iTextureHeight; ++i)
		{
			for (int j = 0; j < iTextureWidth; ++j)
			{
				PPIXEL pPixel = &(*pixelData)[i * iTextureWidth + j];
				if (!(pPixel->r == 0 && pPixel->g == 0 && pPixel->b == 0))
				{
					if (pPixel->r == pPixel->b && pPixel->g == 0)
					{
						unsigned char value = pPixel->r;

						colored[i * iTextureWidth + j].r = (int)(value * r);
						colored[i * iTextureWidth + j].g = (int)(value * g);
						colored[i * iTextureWidth + j].b = (int)(value * b);
					}
				}
			}
		}

		FILE* pFile = NULL;
		char tempDir[LONG_MAX_PATH] = {};
		char fileName[LONG_MAX_PATH] = {};
		//strcpy(fileName, tempFileName);
		WideCharToMultiByte(CP_ACP, 0, wt.c_str(), -1, fileName, lstrlen(wt.c_str()), 0, 0);
		strcpy(tempDir, GET_SINGLE(CResourceManager)->FindPathMultiByte(CACHE_PATH));
		strcat(tempDir, fileName);

		fopen_s(&pFile, tempDir, "wb");


		BITMAPINFOHEADER infoHeader = pTexture->GetInfoHeader();
		PPIXEL pPixelArr = new PIXEL[infoHeader.biWidth];

		for (int i = 0; i < infoHeader.biHeight / 2; ++i)
		{
			PIXEL pPixel = colored[i * infoHeader.biWidth];
			memcpy(pPixelArr, &colored[i * infoHeader.biWidth], sizeof(PIXEL) * infoHeader.biWidth);
			memcpy(&colored[i * infoHeader.biWidth], &colored[(infoHeader.biHeight - i - 1) * infoHeader.biWidth], sizeof(PIXEL) * infoHeader.biWidth);
			memcpy(&colored[(infoHeader.biHeight - i - 1) * infoHeader.biWidth], pPixelArr, sizeof(PIXEL) * infoHeader.biWidth);
		}
		delete[] pPixelArr;


		if (pFile)
		{
			fwrite(&pTexture->GetFileHeader(), sizeof(BITMAPFILEHEADER), 1, pFile);
			fwrite(&pTexture->GetInfoHeader(), sizeof(BITMAPINFOHEADER), 1, pFile);
			fwrite(&colored[0], sizeof(PIXEL), colored.size(), pFile);

			fclose(pFile);
		}

		//return GET_SINGLE(CResourceManager)->LoadTexture(strTeamName, wcBuffer, CACHE_PATH);
	}
}

CSprite * CFileStream::LoadAnimationClip(const string & strKey, const wchar_t * pFileName, const string & strPath)
{
	return nullptr;
}

void CFileStream::SaveAnimationClip(const CSprite * pSprite)
{
}

CTexture * CFileStream::MergeTexture(const CTexture * pBase, const CTexture * pAlpha, const CTexture* pCover)
{
	return nullptr;
}

CTexture * CFileStream::SaveTexture(const CTexture * pTexture)
{
	return nullptr;
}

CTexture * CFileStream::LoadPalette(const char * fileName)
{
	FILE* pFile = NULL;
	fopen_s(&pFile, fileName, "rb");
	if (pFile)
	{
		BITMAPFILEHEADER tFH;
		BITMAPINFOHEADER tIH;

		fread(&tFH, sizeof(BITMAPFILEHEADER), 1, pFile);
		fread(&tIH, sizeof(BITMAPINFOHEADER), 1, pFile);

		for (size_t i = 0; i < 8; ++i)
		{
			PIXEL tTempColor;
			fread(&tTempColor, sizeof(PIXEL), 1, pFile);
			m_pPaletteColor[i].r = tTempColor.r / 255.0f;
			m_pPaletteColor[i].g = tTempColor.g / 255.0f;
			m_pPaletteColor[i].b = tTempColor.b / 255.0f;
		}

		fclose(pFile);
	}
	return nullptr;
}



void CFileStream::SaveUnit(CGameObject * pGameObject, const string& strFileName)
{
	FILE* pFile = NULL;

	char strFullPath[LONG_MAX_PATH] = {};
	
	strcpy(strFullPath, GET_SINGLE(CResourceManager)->FindPathMultiByte(UNIT_PATH));
		
	strcat(strFullPath, strFileName.c_str());

	fopen_s(&pFile, strFullPath, "wb");
	if (pFile)
	{
		int iLength = strlen(pGameObject->GetName().c_str());

		fwrite(&iLength, 4, 1, pFile);
		fwrite(pGameObject->GetName().c_str(), sizeof(char), iLength, pFile);

		iLength = pGameObject->GetComponentCount();
		fwrite(&iLength, 4, 1, pFile);

		bool bState = pGameObject->IsAirUnit();
		fwrite(&bState, 1, 1, pFile);


		list<CComponent*> components = pGameObject->GetComponents();

		list<CComponent*>::iterator iter;
		list<CComponent*>::iterator iterEnd = components.end();

		COMPONENT_PARENT_TYPE eParentType = PT_NONE;
		COMPONENT_TYPE eType = CT_NONE;

		for (iter = components.begin(); iter != iterEnd; ++iter)
		{
			eParentType = (*iter)->GetComponentParentType();			
			eType = (*iter)->GetComponentType();

			fwrite(&eParentType, 4, 1, pFile);
			fwrite(&eType, 4, 1, pFile);

			(*iter)->SaveComponent(pFile);
		}

		fclose(pFile);
	}
}

//SpriteRenderer의 경우 내부에서 Sprite를 map에서 복사해서 생성하게 됨.
void CFileStream::LoadUnit(const string& strKey, const string& strFileName)
{
	CGameObject* pGameObject = new CGameObject;
	pGameObject->RemoveComponent<CTransform>();
	pGameObject->SetKey(strKey);
	pGameObject->SetPilot(NULL);

	FILE* pFile = NULL;
	char strFullPath[LONG_MAX_PATH] = {};	
	strcpy(strFullPath, GET_SINGLE(CResourceManager)->FindPathMultiByte(UNIT_PATH));
	strcat(strFullPath, strFileName.c_str());

	fopen_s(&pFile, string(strFullPath).c_str(), "rb");
	if (pFile)
	{
		int iLength = 0;
		char cName[256] = {};

		//오브젝트의 이름 받아옴
		fread(&iLength, 4, 1, pFile);
		fread(cName, sizeof(char), iLength, pFile);
		pGameObject->SetName(string(cName));




		//컴포넌트 갯수 받아옴
		fread(&iLength, 4, 1, pFile);

		bool bState = false;
		fread(&bState, 1, 1, pFile);

		pGameObject->SetToAirUnit(bState);
		pGameObject->SetSelected(false);

		COMPONENT_PARENT_TYPE eParentType = PT_NONE;
		COMPONENT_TYPE eType = CT_NONE;
		
		for (int i = 0; i < iLength; ++i)
		{
			fread(&eParentType, 4, 1, pFile);
			fread(&eType, 4, 1, pFile);

			switch (eParentType)
			{
			case PT_NONE:
			{
				switch (eType)
				{
				case CT_NONE:
					break;
				case CT_TRANSFORM:
				{
					CTransform* pComponent = pGameObject->AddComponent<CTransform>();
					pComponent->LoadComponent(pFile);
				}
				break;
				case CT_CAMERA:
				{
					CCamera* pComponent = pGameObject->AddComponent<CCamera>();
					pComponent->LoadComponent(pFile);
				}
				break;
				case CT_CAMERA_MOVE:
				{
					CCameraMove* pComponent = pGameObject->AddComponent<CCameraMove>();
					pComponent->LoadComponent(pFile);
				}
				break;
				case CT_COLLISION_TILE:
				{
					CCollisionTile* pComponent = pGameObject->AddComponent<CCollisionTile>();
					pComponent->LoadComponent(pFile);
				}
				break;
				case CT_DEFAULT_UNIT_ANIMATOR:
				{
					CDefaultUnitAnimator* pComponent = pGameObject->AddComponent<CDefaultUnitAnimator>();
					pComponent->LoadComponent(pFile);
				}
				break;
				case CT_SYSTEM_MANAGER:
				{
					CSystemManager* pComponent = pGameObject->AddComponent<CSystemManager>();
					pComponent->LoadComponent(pFile);
				}
				break;
				case CT_TEST_MOVE:
				{
					CTestMove* pComponent = pGameObject->AddComponent<CTestMove>();
					pComponent->LoadComponent(pFile);
				}
				break;
				case CT_STRUCTURE:
				{
					CStructure* pComponent = pGameObject->AddComponent<CStructure>();
					pComponent->LoadComponent(pFile);
				}
				break;
				case CT_RESOURCE:
				{
					CResource* pComponent = pGameObject->AddComponent<CResource>();
					pComponent -> LoadComponent(pFile);
				}
				break;
				case CT_MOVE:
				{
					CMove* pComponent = pGameObject->AddComponent<CMove>();
					pComponent->LoadComponent(pFile);
				}	break;
				case CT_ATTACK: 
				{
					CAttack* pComponent = pGameObject->AddComponent<CAttack>();
					pComponent->LoadComponent(pFile);
				}
					break;

				case CT_ADVANCED_BUILD:
				{
					CAdvancedBuild* pComponent = pGameObject->AddComponent<CAdvancedBuild>();
					pComponent->LoadComponent(pFile);
				}
					break;

				case CT_BUILD:
				{
					CBuild* pComponent = pGameObject->AddComponent<CBuild>();
					pComponent->LoadComponent(pFile);
				}
					break;

				case CT_GATHER:
				{
					CGather* pComponent = pGameObject->AddComponent<CGather>();
					pComponent->LoadComponent(pFile);
				}
					break;

				case CT_HOLD:
				{
					CHold* pComponent = pGameObject->AddComponent<CHold>();
					pComponent->LoadComponent(pFile);
				}
					break;

				case CT_STOP:
				{
					CStop* pComponent = pGameObject->AddComponent<CStop>();
					pComponent->LoadComponent(pFile);
				}
					break;

				case CT_REPAIR:
				{
					CRepair* pComponent = pGameObject->AddComponent<CRepair>();
					pComponent->LoadComponent(pFile);
				}
					break;

				case CT_UNIT_STATUS:
				{
					CUnitStatus* pComponent = pGameObject->AddComponent<CUnitStatus>();
					pComponent->LoadComponent(pFile);
				}
					break;
				case CT_DEFFENCE:
				{
					CDeffence* pComponent = pGameObject->AddComponent<CDeffence>();
					pComponent->LoadComponent(pFile); 
				}
					break;
				case CT_SHIELD:
				{
					CShield* pComponent = pGameObject->AddComponent<CShield>();
					pComponent->LoadComponent(pFile); 
				}break;
				case CT_UNITINFO:
				{
					CUnitInfo* pComponent = pGameObject->AddComponent<CUnitInfo>();
					pComponent->LoadComponent(pFile);
				}break;
				case CT_SCV_ANIMATOR:
				{
					CSCVAnimator* pComponent = pGameObject->AddComponent<CSCVAnimator>();
					pComponent->LoadComponent(pFile);
				}break;
				case CT_MINERALORB_ANIMATOR:
				{
					CMineralOrb* pComponent = pGameObject->AddComponent<CMineralOrb>();
					pComponent->LoadComponent(pFile);
				}break;
				case CT_GASTANK_ANIMATOR:
				{
					CGasTank* pComponent = pGameObject->AddComponent<CGasTank>();
					pComponent->LoadComponent(pFile);
				}break;
				case CT_GASBOX_ANIMATOR:
				{
					CGasBox* pComponent = pGameObject->AddComponent<CGasBox>();
					pComponent->LoadComponent(pFile);
				}break;
				case CT_GASSAC_ANIMATOR:
				{
					CGasSac* pComponent = pGameObject->AddComponent<CGasSac>();
					pComponent->LoadComponent(pFile);
				}break;
				case CT_PATROL:
				{
					CPatrol* pComponent = pGameObject->AddComponent<CPatrol>();
					pComponent->LoadComponent(pFile);
				}break;
				case CT_STIMPACK:
				{
					CStimpack* pComponent = pGameObject->AddComponent<CStimpack>();
					pComponent->LoadComponent(pFile);
				}break;
				case CT_MARINE_ANIMATOR:
				{
					CMarineAnimator* pComponent = pGameObject->AddComponent<CMarineAnimator>();
					pComponent->LoadComponent(pFile);
				}break;
				case CT_MEDIC_ANIMATOR:
				{
					//CMarineAnimator* pComponent = pGameObject->AddComponent<CMarineAnimator>();
					//pComponent->LoadComponent(pFile);
				}break;
				case CT_GHOST_ANIMATOR:
				{
					CGhostAnimator* pComponent = pGameObject->AddComponent<CGhostAnimator>();
					pComponent->LoadComponent(pFile);
				}break;
				case CT_FIREBAT_ANIMATOR:
				{
					CFirebatAnimator* pComponent = pGameObject->AddComponent<CFirebatAnimator>();
					pComponent->LoadComponent(pFile);
				}break;
				case CT_VULTURE_ANIMATOR:
				{
					CVultureAnimator* pComponent = pGameObject->AddComponent<CVultureAnimator>();
					pComponent->LoadComponent(pFile);
				}break;
				case CT_SEIGETANK_ANIMATOR:
				{
					//CMarineAnimator* pComponent = pGameObject->AddComponent<CMarineAnimator>();
					//pComponent->LoadComponent(pFile);
				}break;
				case CT_GOLIAHT_ANIMATOR:
				{
					//CMarineAnimator* pComponent = pGameObject->AddComponent<CMarineAnimator>();
					//pComponent->LoadComponent(pFile);
				}break;
				case CT_WRAITH_ANIMATOR:
				{
					CWraithAnimator* pComponent = pGameObject->AddComponent<CWraithAnimator>();
					pComponent->LoadComponent(pFile);
				}break;
				case CT_BATTLECRUISER_ANIMATOR:
				{
					CBattlecruiserAnimator* pComponent = pGameObject->AddComponent<CBattlecruiserAnimator>();
					pComponent->LoadComponent(pFile);
				}break;
				case CT_DROPSHIP_ANIMATOR:
				{
					CDropshipAnimator* pComponent = pGameObject->AddComponent<CDropshipAnimator>();
					pComponent->LoadComponent(pFile);
				}break;
				case CT_VALKYRIE_ANIMATOR:
				{
					//CMarineAnimator* pComponent = pGameObject->AddComponent<CMarineAnimator>();
					//pComponent->LoadComponent(pFile);
				}break;
				case CT_SPIDERMINE_ANIMATOR:
				{
					//CMarineAnimator* pComponent = pGameObject->AddComponent<CMarineAnimator>();
					//pComponent->LoadComponent(pFile);
				}break;
				case CT_ACADEMY:
				{
					CAcademy* pComponent = pGameObject->AddComponent<CAcademy>();
					pComponent->LoadComponent(pFile);
				}break;
				case CT_BARRACKS:
				{
					CBarracks* pComponent = pGameObject->AddComponent<CBarracks>();
					pComponent->LoadComponent(pFile);
				}break;
				case CT_ENGINEERINGBAY:
				{
					CEngineeringBay* pComponent = pGameObject->AddComponent<CEngineeringBay>();
					pComponent->LoadComponent(pFile);
				}break;
				case CT_BUNKER:
				{
					CBunker* pComponent = pGameObject->AddComponent<CBunker>();
					pComponent->LoadComponent(pFile);
				}break; 
				case CT_FACTORY:
				{
					CFactory* pComponent = pGameObject->AddComponent<CFactory>();
					pComponent->LoadComponent(pFile);
				}break;
				case CT_STARPORT:
				{
					CStarport* pComponent = pGameObject->AddComponent<CStarport>();
					pComponent->LoadComponent(pFile);
				}break;
				case CT_ARMORY:
				{
					CArmory* pComponent = pGameObject->AddComponent<CArmory>();
					pComponent->LoadComponent(pFile);
				}break;
				case CT_COMMANDCENTER:
				{
					CCommandCenter* pComponent = pGameObject->AddComponent<CCommandCenter>();
					pComponent->LoadComponent(pFile);
				}break;
				default:
					break;
				}
			}
			break;
			case PT_RENDERER:
			{
				switch (eType)
				{
				case CT_NONE:
					break;
				case CT_ELLIPSE_RENDERER:
				{
					CEllipseRenderer* pComponent = pGameObject->AddComponent<CEllipseRenderer>();
					pComponent->LoadComponent(pFile);
				}
				break;
				case CT_GRID_RENDERER:
				{
					CGridRenderer* pComponent = pGameObject->AddComponent<CGridRenderer>();
					pComponent->LoadComponent(pFile);
				}
				break;
				case CT_RECTANGLE_RENDERER:
				{
					CRectangleRenderer* pComponent = pGameObject->AddComponent<CRectangleRenderer>();
					pComponent->LoadComponent(pFile);
				}
				break;
				case CT_SPRITE_RENDERER:
				{
					CSpriteRenderer* pComponent = pGameObject->AddComponent<CSpriteRenderer>();
					pComponent->LoadComponent(pFile);
				}
				break;
				case CT_TERRAIN_RENDERER:
				{
					CTerrainRenderer* pComponent = pGameObject->AddComponent<CTerrainRenderer>();
					pComponent->LoadComponent(pFile);
				}
				break;
				case CT_TEXTURE_RENDERER:
				{
					CTextureRenderer* pComponent = pGameObject->AddComponent<CTextureRenderer>();
					pComponent->LoadComponent(pFile);
				}
				break;
				case CT_UI_RENDERER:
				{	
					CUIRenderer* pComponent = pGameObject->AddComponent<CUIRenderer>();
					pComponent->LoadComponent(pFile);
				}
				break;
				default:
					break;
				}
			}
			break;
			case PT_COLLIDER:
			{
				switch (eType)
				{
				case CT_NONE:
					break;
				case CT_CIRCLE_COLLIDER:
				{
					CCircleCollider* pComponent = pGameObject->AddComponent<CCircleCollider>();
					pComponent->LoadComponent(pFile);
				}
				break;
				case CT_PIXEL_COLLIDER:
				{
					CPixelCollider* pComponent = pGameObject->AddComponent<CPixelCollider>();
					pComponent->LoadComponent(pFile);
				}
				break;
				case CT_POINT_COLLIDER:
				{
					CPointCollider* pComponent = pGameObject->AddComponent<CPointCollider>();
					pComponent->LoadComponent(pFile);
				}
				break;
				case CT_RECT_COLLIDER:
				{
					CRectCollider* pComponent = pGameObject->AddComponent<CRectCollider>();
					pComponent->LoadComponent(pFile);
				}
				break;
				default:
					break;
				}
			}
			break;
			default:
				break;
			}

		}

		GET_SINGLE(CResourceManager)->AddUnit(strKey, pGameObject);

		fclose(pFile);
	}




}

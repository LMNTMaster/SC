#include "MinimapManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Tile.h"
#include "Texture.h"
#include "Components\Camera.h"
#include "Components\Transform.h"
#include "Core.h"


CMinimapManager* CMinimapManager::m_pInstance = NULL;

void CMinimapManager::CreateTerrainImage(CScene* pScene, CTerrainRenderer * pTerrainRenderer)
{
	CVector2 gridSize = pScene->GetGridSize();

	vector<COLORREF> LTPixel ;
	vector<COLORREF> RTPixel;
	vector<COLORREF> LBPixel ;
	vector<COLORREF> RBPixel;

	LTPixel.resize(gridSize.x * gridSize.y);
	RTPixel.resize(gridSize.x * gridSize.y);
	LBPixel.resize(gridSize.x * gridSize.y);
	RBPixel.resize(gridSize.x * gridSize.y);

	for (int y = 0; y < gridSize.y; ++y)
	{
		for (int x = 0; x < gridSize.x; ++x)
		{
			int index = y * gridSize.x + x;
			int iTileSetID = pScene->GetTileByIndex(index)->GetTileSetID();
			int iTileIndex = pScene->GetTileByIndex(index)->GetTileIndex();

			COLORREF LT = pScene->GetTileByIndex(index)->GetBaseTexture()->GetPixel(iTileIndex * 32 + 7, iTileSetID * 32 + 7);

			LTPixel[index] = LT;
		}
	}


	//생각할 시간이 읎다
	for (int y = 0; y < gridSize.y; ++y)
	{
		for (int x = 0; x < gridSize.x; ++x)
		{
			int index = y * gridSize.x + x;
			m_vecTerrainPixel.push_back(LTPixel[index]);
		}
	}
}


CVector2 CMinimapManager::GetRelativeCameraPosition()
{
	CCamera* pCamera = GET_SINGLE(CSceneManager)->GetCurrentScene()->GetCamera();
	CVector2 cameraPosition = pCamera->Transform()->GetPosition();
	CVector2 mapPixelSize = GET_SINGLE(CSceneManager)->GetCurrentScene()->GetGridSize() * 32;

	return CVector2(cameraPosition.x / mapPixelSize.x, cameraPosition.y / mapPixelSize.y);
}

CVector2 CMinimapManager::GetRelaticeCameraSize()
{
	CVector2 cameraSize = GET_SINGLE(CCore)->GetScreenSize();
	CVector2 mapPixelSize = GET_SINGLE(CSceneManager)->GetCurrentScene()->GetGridSize() * 32;
	CVector2 minimapSize = CVector2(190, 190);
	return CVector2(cameraSize.x / mapPixelSize.x * minimapSize.x, cameraSize.y / mapPixelSize.y * minimapSize.y);
}

void CMinimapManager::Initialize()
{
}

CMinimapManager::CMinimapManager()
{
}


CMinimapManager::~CMinimapManager()
{
}

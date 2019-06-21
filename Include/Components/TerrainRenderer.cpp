#include "TerrainRenderer.h"
#include "../Tile.h"
#include "../GameObject.h"
#include "../Component.h"
#include "../Components/Camera.h"
#include "Transform.h"
#include "../Scene.h"
#include "../Core.h"
#include "../ResourceManager.h"
#include "../FogOfWarManager.h"
#include "../Layer.h"
#include "MinimapRenderer.h"
#include "../MinimapManager.h"

void CTerrainRenderer::AddTile(CTile * pTile)
{
	int currentIndex = m_vecTile.size();
	CScene* pScene = m_pGameObject->GetScene();
	CVector2 mapSize = pScene->GetGridSize();
	int worldPositionX = (currentIndex % (int)mapSize.x) * (int)pScene->GetTileSize().x;
	int worldPositionY = (currentIndex / (int)mapSize.y) * (int)pScene->GetTileSize().y;

	CTile* pTempTile = pTile->clone();
	pTempTile->SetCamera(pScene->GetCamera());
	pTempTile->SetWorldPosition(CVector2(worldPositionX,worldPositionY));
	m_vecTile.push_back(pTempTile);
}


///<summary>기존의 타일은 메모리에서 해제하고, pTile로 교체한다. 힙에 재할당 하지 않는다.< / summary>
void CTerrainRenderer::ChangeTile(unsigned int index, CTile * pTile)
{
	CCamera* pCamera = m_vecTile[index]->GetCamera();
	CVector2 worldPosition = m_vecTile[index]->GetWorldPosition();

	delete m_vecTile[index];	
	m_vecTile[index] = pTile;
	pTile->SetCamera(pCamera);
	pTile->SetWorldPosition(worldPosition);
}

//내부에서 힙에 Clone으로 재할당 후 변경함.
void CTerrainRenderer::ChangeTile(unsigned int index, int iTileKey)
{
	CCamera* pCamera = m_vecTile[index]->GetCamera();
	CVector2 worldPosition = m_vecTile[index]->GetWorldPosition();
	CTile* pTile = GET_SINGLE(CResourceManager)->GetTile(iTileKey)->clone();

	delete m_vecTile[index];
	m_vecTile[index] = pTile;
	pTile->SetCamera(pCamera);
	pTile->SetWorldPosition(worldPosition);
}

//내부에서 힙에 Clone으로 재할당 후 변경함.
void CTerrainRenderer::ChangeRandomTileFromTileSet(unsigned int index, int iTileSetKey)
{
	CTile* pTile = GET_SINGLE(CResourceManager)->GetRandomTileFromTileSet(iTileSetKey)->clone();
	CCamera* pCamera = m_vecTile[index]->GetCamera();
	CVector2 worldPosition = m_vecTile[index]->GetWorldPosition();

	delete m_vecTile[index];
	m_vecTile[index] = pTile;
	pTile->SetCamera(pCamera);
	pTile->SetWorldPosition(worldPosition);
}


//내부에서 힙에 Clone으로 재할당 후 변경함.
void CTerrainRenderer::ChangeRandomTileFromTileSet(unsigned int index, int iTileSetKey , int iTileSetKey2)
{
	CTile* pTile = GET_SINGLE(CResourceManager)->GetRandomTileFromTileSet(iTileSetKey,iTileSetKey2)->clone();
	CCamera* pCamera = m_vecTile[index]->GetCamera();
	CVector2 worldPosition = m_vecTile[index]->GetWorldPosition();

	delete m_vecTile[index];
	m_vecTile[index] = pTile;
	pTile->SetCamera(pCamera);
	pTile->SetWorldPosition(worldPosition);
}

void CTerrainRenderer::LoadMap()
{
}

void CTerrainRenderer::Render()
{
	CVector2 cameraPosition = m_pGameObject->GetScene()->GetCamera()->GameObject()->GetTransform()->GetPosition();
	CVector2 screenSize = GET_SINGLE(CCore)->GetScreenSize();
	CVector2 gridSize = m_pGameObject->GetScene()->GetGridSize();

	int minWidthIndex = (int)cameraPosition.x / 32;
	int maxWidthIndex = (int)screenSize.x / 32 + minWidthIndex + 1;
	int minHeightIndex = (int)cameraPosition.y / 32;
	int maxHeightIndex =((int)screenSize.y / 32 + minHeightIndex) + 1;
	int horizontalRenderCount = m_pGameObject->GetScene()->GetGridSize().x;
	int verticalRenderCount = m_pGameObject->GetScene()->GetGridSize().y;
	if (m_pGameObject->GetScene()->GetGridSize().x > 40)
	{
		horizontalRenderCount = maxWidthIndex - minWidthIndex;
	}
	if (m_pGameObject->GetScene()->GetGridSize().y >= 23)
	{
		verticalRenderCount = maxHeightIndex - minHeightIndex;
	}
		
	for (int y = minHeightIndex; y < maxHeightIndex; ++y)
	{
		for (int x = minWidthIndex; x < maxWidthIndex; ++x)
		{
			if (y * gridSize.x + x >= gridSize.x * gridSize.y)
			{
				break;
			}
			else
			{
				
					if (m_pGameObject->GetScene()->GetName() == "EditorScene")
					{
						m_vecTile[y * gridSize.x + x]->RenderTileTexture();
					}
					else
					{
						m_vecTile[y * gridSize.x + x]->RenderTileTexture(GET_SINGLE(CFogOfWarManager)->GetTileState(y * gridSize.x + x));
					}
					if (m_vecTile[y * gridSize.y + x]->GetContainUnitList().size() >= 1)
					{
						list<CGameObject*> unitlist = m_vecTile[y * gridSize.x + x]->GetContainUnitList();

						list<CGameObject*>::iterator iter;
						list<CGameObject*>::iterator iterEnd = unitlist.end();
						for (iter = unitlist.begin(); iter != iterEnd; ++iter)
						{
							if (m_pGameObject->GetScene()->GetName() != "EditorScene")
							{
								if ((*iter)->GetPilot() == NULL)
								{
									m_pGameObject->GetScene()->GetLayer("UIMiddle")->FindGameObject("Minimap")->GetComponent<CMinimapRenderer>()->SetMinimapPixel(y * gridSize.x + x, RGB(255, 255, 0));
								}
								else if ((*iter)->GetPilot() == m_pGameObject->GetScene()->GetLayer("System")->FindGameObject("Cursor")->GetPilot())
								{
									m_pGameObject->GetScene()->GetLayer("UIMiddle")->FindGameObject("Minimap")->GetComponent<CMinimapRenderer>()->SetMinimapPixel(y * gridSize.x + x, RGB(0, 255, 0));
								}
								else
								{
									m_pGameObject->GetScene()->GetLayer("UIMiddle")->FindGameObject("Minimap")->GetComponent<CMinimapRenderer>()->SetMinimapPixel(y * gridSize.x + x, RGB(255, 0, 0));
								}
							}
						}
					}
					else
					{
						FOW tState = GET_SINGLE(CFogOfWarManager)->GetTileState(y * gridSize.x + x);
						if (tState.m_bVisit && tState.m_eState == FS_INVISIBLE)
						{
							m_pGameObject->GetScene()->GetLayer("UIMiddle")->FindGameObject("Minimap")->GetComponent<CMinimapRenderer>()->SetBasePixel(y * gridSize.x + x, true);
						}
						else if (!tState.m_bVisit && tState.m_eState == FS_INVISIBLE)
						{
							m_pGameObject->GetScene()->GetLayer("UIMiddle")->FindGameObject("Minimap")->GetComponent<CMinimapRenderer>()->SetBlackPixel(y * gridSize.x + x);
						}
						else if (tState.m_bVisit && tState.m_eState == FS_VISIBLE)
						{
							m_pGameObject->GetScene()->GetLayer("UIMiddle")->FindGameObject("Minimap")->GetComponent<CMinimapRenderer>()->SetBasePixel(y * gridSize.x + x, false);
						}
						else if (!tState.m_bVisit && tState.m_eState == FS_VISIBLE)
						{
							m_pGameObject->GetScene()->GetLayer("UIMiddle")->FindGameObject("Minimap")->GetComponent<CMinimapRenderer>()->SetBasePixel(y * gridSize.x + x, false);
						}
					}

				}
			
		}
	}
}

void CTerrainRenderer::SaveComponent(FILE * pFile)
{
}

void CTerrainRenderer::LoadComponent(FILE * pFile)
{
}

CComponent * CTerrainRenderer::clone()
{
	return new CTerrainRenderer(*this);
}

CTerrainRenderer::CTerrainRenderer(const CTerrainRenderer & component)
{
	vector<CTile*>::const_iterator iter;
	vector<CTile*>::const_iterator iterEnd = component.m_vecTile.end();
	

	//Terrain은 Texture를 쓰기 때문에, 다시 할당 할 필요가 없다.
	for (iter = component.m_vecTile.begin(); iter != iterEnd; ++iter)
	{
		m_vecTile.push_back((*iter));
	}
	m_eComponentParentType = PT_RENDERER;
	m_eComponentType = CT_TERRAIN_RENDERER;
}

CTerrainRenderer::CTerrainRenderer()
{
	m_eComponentParentType = PT_RENDERER;
	m_eComponentType = CT_TERRAIN_RENDERER;
}


CTerrainRenderer::~CTerrainRenderer()
{
	//벡터 비워준다.
	vector<CTile*>::iterator iter;
	vector<CTile*>::iterator	iterEnd = m_vecTile.end();

	for (iter = m_vecTile.begin(); iter != iterEnd; ++iter )
	{
		delete *iter;
	}
	m_vecTile.clear();
}

#include "FOW.h"
#include "../ResourceManager.h"
#include "../FogOfWarManager.h"
#include "Camera.h"
#include "../GameObject.h"
#include "../Core.h"
#include "../Scene.h"
#include "../Layer.h"
#include "Transform.h"
#include "../Texture.h"
#include "../Tile.h"
#include "MinimapRenderer.h"


void CFOW::Render()
{

	CVector2 cameraPosition = m_pGameObject->GetScene()->GetCamera()->GameObject()->GetTransform()->GetPosition();
	CVector2 screenSize = GET_SINGLE(CCore)->GetScreenSize();
	CVector2 gridSize = m_pGameObject->GetScene()->GetGridSize();

	int minWidthIndex = (int)cameraPosition.x / 32;
	int maxWidthIndex = (int)screenSize.x / 32 + minWidthIndex + 1;
	int minHeightIndex = (int)cameraPosition.y / 32;
	int maxHeightIndex = ((int)screenSize.y / 32 + minHeightIndex) + 1;
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
				FOW tState = GET_SINGLE(CFogOfWarManager)->GetTileState(y * gridSize.x + x);
				CVector2 renderPosition = m_pGameObject->GetScene()->GetTileByIndex(y * gridSize.x + x)->GetWorldPosition() - cameraPosition;

				if (tState.m_bVisit && tState.m_eState == FS_INVISIBLE)
				{
					BLENDFUNCTION tBF;
					tBF.AlphaFormat = NULL;
					tBF.BlendFlags = NULL;
					tBF.BlendOp = AC_SRC_OVER;
					tBF.SourceConstantAlpha = 96;

					AlphaBlend(GET_SINGLE(CResourceManager)->GetBackBuffer()->GetDC(),
						renderPosition.x, renderPosition.y,
						32, 32,
						GET_SINGLE(CResourceManager)->FindTexture("BlackCell")->GetDC(),
						0, 0,
						32, 32, tBF);
				}
				else if (!tState.m_bVisit && tState.m_eState == FS_INVISIBLE)
				{
					BitBlt(GET_SINGLE(CResourceManager)->GetBackBuffer()->GetDC(),
						renderPosition.x, renderPosition.y,
						32, 32,
						GET_SINGLE(CResourceManager)->FindTexture("BlackCell")->GetDC(),
						0,0,
						SRCCOPY);
				}
				else if (!tState.m_bVisit && tState.m_eState == FS_VISIBLE)
				{
					//DO NOTHING
				}
				else if (tState.m_bVisit && tState.m_eState == FS_VISIBLE)
				{
					//DO NOTHING
				}

				
				if (tState != GET_SINGLE(CFogOfWarManager)->GetPrevTileState(y * gridSize.x + x))
				{
					m_pGameObject->GetScene()->GetLayer("UIMiddle")->FindGameObject("Minimap")->GetComponent<CMinimapRenderer>()->SetMinimapPixel(y * gridSize.x + x, tState);
				}
			}
		}
	}
}

void CFOW::LoadComponent(FILE * pFile)
{
}

void CFOW::SaveComponent(FILE * pFile)
{
}

CComponent * CFOW::clone()
{
	return new CFOW(*this);
}

CFOW::CFOW(const CFOW & component)
{
}

CFOW::CFOW()
{
}


CFOW::~CFOW()
{
}

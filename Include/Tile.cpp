#include "Tile.h"
#include "Texture.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Components\Camera.h"
#include "GameObject.h"
#include "Components\Transform.h"
#include "Layer.h"
#include "Component.h"
#include "Components\EditorManager.h"

void CTile::RenderTileTexture()
{
	if (!m_pBaseTexture)
		return;

	CVector2 cameraPosition = m_pCamera->GameObject()->GetTransform()->GetPosition();

	CVector2 renderPosition = m_WorldPosition - cameraPosition;

	int iHorizontalIndex = m_iWidth * m_iX; //% m_pBaseTexture->GetTextureInfo().bmWidth;
	int iVerticalIndex = m_iHeight * m_iY;

	TransparentBlt(GET_SINGLE(CResourceManager)->GetBackBuffer()->GetDC(),
		renderPosition.x, renderPosition.y,
		m_iWidth, m_iHeight,
		m_pBaseTexture->GetDC(),
		iHorizontalIndex , iVerticalIndex,
		m_iWidth, m_iHeight,
		RGB(0, 0, 0));
	//1개 타일은 항상 32픽셀이다.

	if (m_pCamera->GameObject()->GetScene()->GetName() == "EditorScene")
	{
		if (m_pCamera->GameObject()->GetLayer()->FindGameObject("Terrain")->GetComponent<CEditorManager>()->GetEditState() == 2)
		{
			if (!m_bMovable)
			{
				BLENDFUNCTION tBF;
				tBF.AlphaFormat = NULL;
				tBF.BlendFlags = NULL;
				tBF.BlendOp = AC_SRC_OVER;
				tBF.SourceConstantAlpha = 64;

				AlphaBlend(GET_SINGLE(CResourceManager)->GetBackBuffer()->GetDC(),
					renderPosition.x, renderPosition.y,
					m_iWidth, m_iHeight,
					GET_SINGLE(CResourceManager)->FindTexture("NegativeCell")->GetDC(),
					0, 0,
					m_iWidth, m_iHeight, tBF);
			}			
		}
	}
}

void CTile::RenderTileTexture(FOW tState)
{
	if (!m_pBaseTexture)
		return;

	CVector2 cameraPosition = m_pCamera->GameObject()->GetTransform()->GetPosition();

	CVector2 renderPosition = m_WorldPosition - cameraPosition;

	int iHorizontalIndex = m_iWidth * m_iX; //% m_pBaseTexture->GetTextureInfo().bmWidth;
	int iVerticalIndex = m_iHeight * m_iY;

	if (tState.m_bVisit && tState.m_eState == FS_INVISIBLE)
	{
		TransparentBlt(GET_SINGLE(CResourceManager)->GetBackBuffer()->GetDC(),
			renderPosition.x, renderPosition.y,
			m_iWidth, m_iHeight,
			m_pBaseTexture->GetDC(),
			iHorizontalIndex, iVerticalIndex,
			m_iWidth, m_iHeight,
			RGB(0, 0, 0));
	}
	else if (tState.m_bVisit && tState.m_eState == FS_VISIBLE)
	{
		TransparentBlt(GET_SINGLE(CResourceManager)->GetBackBuffer()->GetDC(),
			renderPosition.x, renderPosition.y,
			m_iWidth, m_iHeight,
			m_pBaseTexture->GetDC(),
			iHorizontalIndex, iVerticalIndex,
			m_iWidth, m_iHeight,
			RGB(0, 0, 0));
	}
	else if (!tState.m_bVisit && tState.m_eState == FS_INVISIBLE)
	{
	}
	else
	{
		TransparentBlt(GET_SINGLE(CResourceManager)->GetBackBuffer()->GetDC(),
			renderPosition.x, renderPosition.y,
			m_iWidth, m_iHeight,
			m_pBaseTexture->GetDC(),
			iHorizontalIndex, iVerticalIndex,
			m_iWidth, m_iHeight,
			RGB(0, 0, 0));
	}

	//1개 타일은 항상 32픽셀이다.

	if (m_pCamera->GameObject()->GetScene()->GetName() == "EditorScene")
	{
		if (m_pCamera->GameObject()->GetLayer()->FindGameObject("Terrain")->GetComponent<CEditorManager>()->GetEditState() == 2)
		{
			if (!m_bMovable)
			{
				BLENDFUNCTION tBF;
				tBF.AlphaFormat = NULL;
				tBF.BlendFlags = NULL;
				tBF.BlendOp = AC_SRC_OVER;
				tBF.SourceConstantAlpha = 64;

				AlphaBlend(GET_SINGLE(CResourceManager)->GetBackBuffer()->GetDC(),
					renderPosition.x, renderPosition.y,
					m_iWidth, m_iHeight,
					GET_SINGLE(CResourceManager)->FindTexture("NegativeCell")->GetDC(),
					0, 0,
					m_iWidth, m_iHeight, tBF);
			}
		}
	}
}

CTile * CTile::clone()
{
	return new CTile(*this);
}

CTile::CTile(const CTile & pTile)
{
	m_iTileSetID = pTile.m_iTileSetID;
	m_iTileID = pTile.m_iTileID;
	m_iTileIndex = pTile.m_iTileIndex;
	m_pBaseTexture = pTile.m_pBaseTexture;
	m_pGreyScaleTexture = pTile.m_pGreyScaleTexture;
	m_pCreepTexture = pTile.m_pCreepTexture;
	m_WorldPosition = pTile.m_WorldPosition;
	m_iWidth = pTile.m_iWidth;
	m_iHeight = pTile.m_iHeight;
	m_iX = pTile.m_iX;
	m_iY = pTile.m_iY;
	m_pCamera = pTile.m_pCamera;

	m_iTerrainHeight = pTile.m_iTerrainHeight;
	m_bMovable	= pTile.m_bMovable;
	m_bCreep = pTile.m_bCreep;
	m_bBuildable = pTile.m_bBuildable;	
}  

CTile::CTile():
	m_pBaseTexture(NULL),
	m_pCamera(NULL),
	m_iTerrainHeight(0),
	m_bMovable(true),
	m_bCreep(false),
	m_bBuildable(true),
	m_iWidth(32),
	m_iHeight(32),
	m_iY(0),
	m_iX(0),
	m_iTileIndex(INT_MAX)
{
}


CTile::~CTile()
{
}

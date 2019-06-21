#include "MinimapRenderer.h"
#include "../MinimapManager.h"
#include "../ResourceManager.h"
#include "../Texture.h"
#include "../GameObject.h"
#include "Transform.h"


void CMinimapRenderer::SetMinimapPixel(int iTileIndex, COLORREF color)
{

	CVector2 gridSize = m_pGameObject->GetScene()->GetGridSize();

	int iTileXPosition = iTileIndex % (int)gridSize.x;
	int iTileYPosition = iTileIndex / (int)gridSize.x;

	CVector2 relativePositionLT = CVector2((iTileXPosition) / gridSize.x, (iTileYPosition) / gridSize.y) * 190;
	CVector2 relativePositionRT = CVector2((iTileXPosition + 1) / gridSize.x, (iTileYPosition) / gridSize.y) * 190;
	CVector2 relativePositionLB = CVector2((iTileXPosition) / gridSize.x, (iTileYPosition + 1) / gridSize.y) * 190;
	CVector2 relativePositionRB = CVector2((iTileXPosition + 1) / gridSize.x, (iTileYPosition + 1) / gridSize.y) * 190;

	SetPixel(m_pFogTexture->GetDC(), relativePositionLT.x, relativePositionLT.y, color);
	SetPixel(m_pFogTexture->GetDC(), relativePositionRT.x, relativePositionRT.y, color);
	SetPixel(m_pFogTexture->GetDC(), relativePositionLB.x, relativePositionLB.y, color);
	SetPixel(m_pFogTexture->GetDC(), relativePositionRB.x, relativePositionRB.y, color);
}

void CMinimapRenderer::SetMinimapPixel(int iTileIndex, FOW tFogState)
{
	CVector2 gridSize = m_pGameObject->GetScene()->GetGridSize();

	int iTileXPosition = iTileIndex % (int)gridSize.x;
	int iTileYPosition = iTileIndex / (int)gridSize.x;

	CVector2 relativePositionLT = CVector2((iTileXPosition) / gridSize.x,(iTileYPosition) / gridSize.y) * 190;
	//CVector2 relativePositionRT = CVector2((iTileXPosition + 1) / gridSize.x,(iTileYPosition) / gridSize.y) * 190;
	//CVector2 relativePositionLB = CVector2((iTileXPosition) / gridSize.x,(iTileYPosition + 1) / gridSize.y) * 190;
	//CVector2 relativePositionRB = CVector2((iTileXPosition + 1) / gridSize.x,(iTileYPosition + 1) / gridSize.y) * 190;

	if (tFogState.m_bVisit && tFogState.m_eState == FS_VISIBLE)
	{
		SetPixel(m_pFogTexture->GetDC(), relativePositionLT.x, relativePositionLT.y, m_pBaseTexture->GetPixel(relativePositionLT.x, relativePositionLT.y));
		//SetPixel(m_pFogTexture->GetDC(), relativePositionRT.x, relativePositionRT.y, m_pBaseTexture->GetPixel(relativePositionRT.x, relativePositionRT.y));
		//SetPixel(m_pFogTexture->GetDC(), relativePositionLB.x, relativePositionLB.y, m_pBaseTexture->GetPixel(relativePositionLB.x, relativePositionLB.y));
		//SetPixel(m_pFogTexture->GetDC(), relativePositionRB.x, relativePositionRB.y, m_pBaseTexture->GetPixel(relativePositionRB.x, relativePositionRB.y));	
	}
	else if (tFogState.m_bVisit && tFogState.m_eState == FS_INVISIBLE)
	{		
		COLORREF baseColorLT = m_pBaseTexture->GetPixel(relativePositionLT.x, relativePositionLT.y);
		//COLORREF baseColorRT = m_pBaseTexture->GetPixel(relativePositionRT.x, relativePositionRT.y);
		//COLORREF baseColorLB = m_pBaseTexture->GetPixel(relativePositionLB.x, relativePositionLB.y);
		//COLORREF baseColorRB = m_pBaseTexture->GetPixel(relativePositionRB.x, relativePositionRB.y);

		COLORREF colorLT		= RGB(GetRValue(baseColorLT) * 0.25f, GetGValue(baseColorLT) * 0.25f, GetBValue(baseColorLT) * 0.25f);
		//COLORREF colorRT		= RGB(GetRValue(baseColorRT) * 0.25f, GetGValue(baseColorRT) * 0.25f, GetBValue(baseColorRT) * 0.25f);
		//COLORREF colorLB		= RGB(GetRValue(baseColorLB) * 0.25f, GetGValue(baseColorLB) * 0.25f, GetBValue(baseColorLB) * 0.25f);
		//COLORREF colorRB		= RGB(GetRValue(baseColorRB) * 0.25f, GetGValue(baseColorRB) * 0.25f, GetBValue(baseColorRB) * 0.25f);

		SetPixel(m_pFogTexture->GetDC(), relativePositionLT.x, relativePositionLT.y, colorLT);
		//SetPixel(m_pFogTexture->GetDC(), relativePositionRT.x, relativePositionRT.y, colorRT);
		//SetPixel(m_pFogTexture->GetDC(), relativePositionLB.x, relativePositionLB.y, colorLB);
		//SetPixel(m_pFogTexture->GetDC(), relativePositionRB.x, relativePositionRB.y, colorRB);
	}
	else if (!tFogState.m_bVisit && tFogState.m_eState == FS_VISIBLE)
	{
		SetPixel(m_pFogTexture->GetDC(), relativePositionLT.x, relativePositionLT.y, m_pBaseTexture->GetPixel(relativePositionLT.x, relativePositionLT.y));
		//SetPixel(m_pFogTexture->GetDC(), relativePositionRT.x, relativePositionRT.y, m_pBaseTexture->GetPixel(relativePositionRT.x, relativePositionRT.y));
		//SetPixel(m_pFogTexture->GetDC(), relativePositionLB.x, relativePositionLB.y, m_pBaseTexture->GetPixel(relativePositionLB.x, relativePositionLB.y));
		//SetPixel(m_pFogTexture->GetDC(), relativePositionRB.x, relativePositionRB.y, m_pBaseTexture->GetPixel(relativePositionRB.x, relativePositionRB.y));
	}
	else if (!tFogState.m_bVisit && tFogState.m_eState == FS_INVISIBLE)
	{
		SetPixel(m_pFogTexture->GetDC(), relativePositionLT.x, relativePositionLT.y,	RGB(0,0,0));
		//SetPixel(m_pFogTexture->GetDC(), relativePositionRT.x, relativePositionRT.y,	RGB(0,0,0));
		//SetPixel(m_pFogTexture->GetDC(), relativePositionLB.x, relativePositionLB.y,	RGB(0,0,0));
		//SetPixel(m_pFogTexture->GetDC(), relativePositionRB.x, relativePositionRB.y,RGB(0,0,0));
	}
}

void CMinimapRenderer::SetBasePixel(int iTileIndex, bool bBlended)
{
	CVector2 gridSize = m_pGameObject->GetScene()->GetGridSize();

	int iTileXPosition = iTileIndex % (int)gridSize.x;
	int iTileYPosition = iTileIndex / (int)gridSize.x;

	CVector2 relativePositionLT = CVector2((iTileXPosition) / gridSize.x, (iTileYPosition) / gridSize.y) * 190;

	if (bBlended)
	{
		COLORREF baseColorLT = m_pBaseTexture->GetPixel(relativePositionLT.x, relativePositionLT.y);
		COLORREF colorLT = RGB(GetRValue(baseColorLT) * 0.25f, GetGValue(baseColorLT) * 0.25f, GetBValue(baseColorLT) * 0.25f);
		SetPixel(m_pFogTexture->GetDC(), relativePositionLT.x, relativePositionLT.y, colorLT);
	}
	else
	{
		SetPixel(m_pFogTexture->GetDC(), relativePositionLT.x, relativePositionLT.y, m_pBaseTexture->GetPixel(relativePositionLT.x, relativePositionLT.y));
	}
}

void CMinimapRenderer::SetBlackPixel(int iTileIndex)
{
	CVector2 gridSize = m_pGameObject->GetScene()->GetGridSize();
	int iTileXPosition = iTileIndex % (int)gridSize.x;
	int iTileYPosition = iTileIndex / (int)gridSize.x;
	CVector2 relativePositionLT = CVector2((iTileXPosition) / gridSize.x, (iTileYPosition) / gridSize.y) * 190;
	SetPixel(m_pFogTexture->GetDC(), relativePositionLT.x, relativePositionLT.y, RGB(0,0,0));
}


void CMinimapRenderer::Start()
{
	m_pBaseTexture = GET_SINGLE(CResourceManager)->FindTexture("Terrain_Hunter_Minimap");
	m_pFogTexture = new CTexture();
	*m_pFogTexture = *GET_SINGLE(CResourceManager)->FindTexture("Fog_Minimap");

}

void CMinimapRenderer::Render()
{
	
	CVector2 position = m_pTransform->GetPosition();
	CVector2 originPosition = CVector2(position.x - m_Size.x * m_pTransform->GetPivot().x, position.y - m_Size.y * m_pTransform->GetPivot().y);
	CTexture* pMinimapTexture = GET_SINGLE(CResourceManager)->FindTexture("Terrain_Hunter_Minimap");


	BitBlt(GET_SINGLE(CResourceManager)->GetBackBuffer()->GetDC(),
		originPosition.x, originPosition.y,
		m_pFogTexture->GetTextureInfo().bmWidth,
		m_pFogTexture->GetTextureInfo().bmHeight,
		m_pFogTexture->GetDC(),
		0, 0, SRCCOPY);
		
	HPEN pen = CreatePen(PS_SOLID, 1, RGB(255,255,255));
	SelectObject(GET_SINGLE(CResourceManager)->GetBackBuffer()->GetDC(), pen);
	SelectObject(GET_SINGLE(CResourceManager)->GetBackBuffer()->GetDC(), GetStockObject(NULL_BRUSH));

	CVector2 cameraLT= m_pTransform->GetPosition() + GET_SINGLE(CMinimapManager)->GetRelativeCameraPosition() * 190;
	CVector2 cameraRB = cameraLT + GET_SINGLE(CMinimapManager)->GetRelaticeCameraSize();
	Rectangle(GET_SINGLE(CResourceManager)->GetBackBuffer()->GetDC(), cameraLT.x, cameraLT.y, cameraRB.x, cameraRB.y);

}

void CMinimapRenderer::SaveComponent(FILE * pFile)
{
}

void CMinimapRenderer::LoadComponent(FILE * pFile)
{
}

CComponent * CMinimapRenderer::clone()
{
	return new CMinimapRenderer(*this);
}

CMinimapRenderer::CMinimapRenderer(const CMinimapRenderer & component)
{
}

CMinimapRenderer::CMinimapRenderer()
{
}


CMinimapRenderer::~CMinimapRenderer()
{
	delete m_pFogTexture;
}

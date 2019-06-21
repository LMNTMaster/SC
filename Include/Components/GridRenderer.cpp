#include "GridRenderer.h"
#include "Transform.h"
#include "../Component.h"
#include "../GameObject.h"
#include "../ResourceManager.h"
#include "../Texture.h"
#include "../Core.h"
#include "../Scene.h"
#include "Camera.h"

void CGridRenderer::Render()
{

	CTransform* transform = m_pGameObject->GetComponent<CTransform>();

	HDC dc = GET_SINGLE(CResourceManager)->GetBackBuffer()->GetDC();
	CVector2 cameraPosition = m_pGameObject->GetScene()->GetCamera()->Transform()->GetPosition();

	int iScreenWidth = GET_SINGLE(CCore)->GetScreenSize().x;
	int iScreenHeight = GET_SINGLE(CCore)->GetScreenSize().y;


	HPEN pen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	SelectObject(dc, pen);

	//가로줄
	for (int i = 0; i < m_iHeightCount; ++i)
	{
		MoveToEx(dc, 0, i * m_iCellHeight - (int) cameraPosition.y, NULL);
		LineTo(dc, m_iWidthCount * m_iCellWidth, i * m_iCellHeight - (int) cameraPosition.y);
	}

	//세로줄
	for (int i = 0; i < m_iWidthCount; ++i)
	{
		MoveToEx(dc, i * m_iCellWidth - (int)cameraPosition.x, 0, NULL);
		LineTo(dc, i * m_iCellWidth - (int) cameraPosition.x, m_iHeightCount * m_iCellHeight);
	}

	DeleteObject(pen);
	//for (int i = 0; i < m_iHeightCount; ++i)
	//{
	//	for (int j = 0; j < m_iWidthCount; ++j)
	//	{
	//		string a = to_string(i * m_iWidthCount + j);
	//
	//		TextOutA(dc, (m_iCellWidth/2 + j * m_iCellWidth) - cameraPosition.x, (i * m_iCellHeight) -cameraPosition.y, a.c_str(), 3);
	//	}
	//}

}

void CGridRenderer::SaveComponent(FILE * pFile)
{
	fwrite(&m_iWidthCount, 4, 1, pFile);
	fwrite(&m_iHeightCount, 4, 1, pFile);
	fwrite(&m_iCellWidth, 4, 1, pFile);
	fwrite(&m_iCellHeight, 4, 1, pFile);
}

void CGridRenderer::LoadComponent(FILE * pFile)
{
	fread(&m_iWidthCount, 4, 1, pFile);
	fread(&m_iHeightCount, 4, 1, pFile);
	fread(&m_iCellWidth, 4, 1, pFile);
	fread(&m_iCellHeight, 4, 1, pFile);
}

CComponent * CGridRenderer::clone()
{
	return new CGridRenderer(*this);
}

CGridRenderer::CGridRenderer(const CGridRenderer & component)
{
	m_iWidthCount = component.m_iWidthCount;
	m_iHeightCount = component.m_iHeightCount;
	m_iCellWidth = component.m_iCellWidth;
	m_iCellHeight = component.m_iCellHeight;	

	m_eComponentParentType = PT_RENDERER;
	m_eComponentType = CT_GRID_RENDERER;
}

CGridRenderer::CGridRenderer()
{
	m_eComponentParentType = PT_RENDERER;
	m_eComponentType = CT_GRID_RENDERER;
}


CGridRenderer::~CGridRenderer()
{
}

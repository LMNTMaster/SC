#include "RectangleRenderer.h"
#include "../ResourceManager.h"
#include "../Core.h"
#include "../Texture.h"
#include "../GameObject.h"
#include "../Scene.h"
#include "Transform.h"
#include "Camera.h"


void CRectangleRenderer::Render()
{
	HPEN pen = CreatePen(PS_SOLID, m_iThickness, m_tColor);

	HDC dc = GET_SINGLE(CResourceManager)->GetBackBuffer()->GetDC();
	SelectObject(dc, pen);
	MoveToEx(dc, m_StartPosition.x , m_StartPosition.y , NULL);
	LineTo(dc, m_EndPosition.x, m_StartPosition.y );
	LineTo(dc, m_EndPosition.x, m_EndPosition.y);
	LineTo(dc, m_StartPosition.x , m_EndPosition.y);
	LineTo(dc, m_StartPosition.x, m_StartPosition.y);
	DeleteObject(pen);
}

void CRectangleRenderer::SaveComponent(FILE * pFile)
{
	fwrite(&m_StartPosition, sizeof(CVector2), 1, pFile);
	fwrite(&m_EndPosition, sizeof(CVector2), 1, pFile);
	fwrite(&m_tColor, sizeof(COLORREF), 1, pFile);
	fwrite(&m_StartPosition, 4, 1, pFile);
}

void CRectangleRenderer::LoadComponent(FILE * pFile)
{
	fread(&m_StartPosition, sizeof(CVector2), 1, pFile);
	fread(&m_EndPosition, sizeof(CVector2), 1, pFile);
	fread(&m_tColor, sizeof(COLORREF), 1, pFile);
	fread(&m_StartPosition, 4, 1, pFile);
}

CComponent * CRectangleRenderer::clone()
{
	return new CRectangleRenderer(*this);
}

CRectangleRenderer::CRectangleRenderer(const CRectangleRenderer & component)
{
	m_StartPosition = component.m_StartPosition;
	m_EndPosition = component.m_EndPosition;
	m_tColor = component.m_tColor;
	m_iThickness = component.m_iThickness;
	m_eComponentParentType = PT_RENDERER;
	m_eComponentType = CT_RECTANGLE_RENDERER;
}

CRectangleRenderer::CRectangleRenderer()
{
	m_eComponentParentType = PT_RENDERER;
	m_eComponentType = CT_RECTANGLE_RENDERER;
}


CRectangleRenderer::~CRectangleRenderer()
{
}

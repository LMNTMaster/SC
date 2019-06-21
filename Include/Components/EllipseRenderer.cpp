#include "EllipseRenderer.h"
#include "../ResourceManager.h"
#include "../Texture.h"
#include "Transform.h"
#include "Camera.h"
#include "../GameObject.h"
#include "../Scene.h"


void CEllipseRenderer::Render()
{
	if (m_pGameObject->GetSelected())
	{
		HDC dc = GET_SINGLE(CResourceManager)->GetBackBuffer()->GetDC();
		HPEN pen = CreatePen(PS_SOLID, m_iThickness, m_tColor);
		CVector2 cameraPosition = m_pGameObject->GetScene()->GetCamera()->Transform()->GetPosition();


		SelectObject(dc, pen);
		SelectObject(dc, GetStockObject(NULL_BRUSH));
		CVector2 position = Transform()->GetPosition() + m_LocalPosition - cameraPosition;

		CVector2 lt = CVector2(position.x - m_fMinorAxis * m_fMajorAxisScale, position.y - m_fMinorAxis);
		CVector2 rb = CVector2(position.x + m_fMinorAxis * m_fMajorAxisScale, position.y + m_fMinorAxis);

		Ellipse(dc, lt.x, lt.y, rb.x, rb.y);
		DeleteObject(pen);
	}
}

void CEllipseRenderer::SaveComponent(FILE* pFile)
{
	fwrite(&m_fMinorAxis, sizeof(float), 1, pFile);
	fwrite(&m_fMajorAxisScale, sizeof(float), 1, pFile);
	fwrite(&m_tColor, sizeof(COLORREF), 1, pFile);
	fwrite(&m_iThickness, sizeof(int), 1, pFile);
	fwrite(&m_LocalPosition, sizeof(CVector2), 1, pFile);
}

void CEllipseRenderer::LoadComponent(FILE * pFile)
{
	fread(&m_fMinorAxis, sizeof(float), 1, pFile);
	fread(&m_fMajorAxisScale, sizeof(float), 1, pFile);
	fread(&m_tColor, sizeof(COLORREF), 1, pFile);
	fread(&m_iThickness, sizeof(int), 1, pFile);
	fread(&m_LocalPosition, sizeof(CVector2), 1, pFile);
}

CComponent * CEllipseRenderer::clone()
{
	return new CEllipseRenderer(*this);
}

CEllipseRenderer::CEllipseRenderer(const CEllipseRenderer & component)
{
	m_fMajorAxisScale = component.m_fMajorAxisScale;
	m_fMinorAxis = component.m_fMinorAxis;
	m_tColor = component.m_tColor;
	m_iThickness = component.m_iThickness;
	m_LocalPosition = component.m_LocalPosition;
	m_eComponentParentType = PT_RENDERER;
	m_eComponentType = CT_ELLIPSE_RENDERER;
}

CEllipseRenderer::CEllipseRenderer():
	m_fMajorAxisScale(1.6f),
	m_fMinorAxis(10),
	m_tColor(RGB(60,150,30)),
	m_iThickness(2),
	m_LocalPosition(CVector2())
{
	m_eComponentParentType = PT_RENDERER;
	m_eComponentType = CT_ELLIPSE_RENDERER;
}


CEllipseRenderer::~CEllipseRenderer()
{
}

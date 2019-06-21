#include "CircleCollider.h"
#include "../Texture.h"
#include "../ResourceManager.h"
#include "../GameObject.h"
#include "../Scene.h"
#include "Transform.h"
#include "Camera.h"


void CCircleCollider::LateUpdate()
{
	/*
#ifdef _DEBUG

	CVector2 cameraPosition = m_pGameObject->GetScene()->GetCamera()->Transform()->GetPosition();

	HDC dc = GET_SINGLE(CResourceManager)->GetBackBuffer()->GetDC();
	HPEN pen = CreatePen(PS_SOLID, 1, RGB(255, 255, 0));	
	
	SelectObject(dc, pen);
	SelectObject(dc, GetStockObject(NULL_BRUSH));

	CVector2 lt = CVector2(GetWorldPosition().x - m_fRadius, GetWorldPosition().y - m_fRadius);
	CVector2 rb = CVector2(GetWorldPosition().x + m_fRadius, GetWorldPosition().y + m_fRadius);
	

	lt -= cameraPosition;
	rb -= cameraPosition;

	Ellipse(dc, lt.x, lt.y, rb.x, rb.y);
	DeleteObject(pen);

#endif // _DEBUG
*/
}

void CCircleCollider::SaveComponent(FILE * pFile)
{
	fwrite(&m_fRadius, sizeof(float), 1, pFile);
}

void CCircleCollider::LoadComponent(FILE * pFile)
{
	fread(&m_fRadius, sizeof(float), 1, pFile);
}

CComponent * CCircleCollider::clone()
{
	return new CCircleCollider(*this);
}

CCircleCollider::CCircleCollider(const CCircleCollider & component)
{
	m_fRadius = component.m_fRadius;
	m_eType = COLLIDER_TYPE::CIRCLE;
	m_eComponentType = CT_CIRCLE_COLLIDER;
	m_eComponentParentType = PT_COLLIDER;
}

CCircleCollider::CCircleCollider():
	m_fRadius(1)
{
	m_eType = COLLIDER_TYPE::CIRCLE;
	m_eComponentType = CT_CIRCLE_COLLIDER;
	m_eComponentParentType = PT_COLLIDER;
}


CCircleCollider::~CCircleCollider()
{
}

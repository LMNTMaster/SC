#include "RectCollider.h"
#include "../ResourceManager.h"
#include "../Texture.h"
#include "../GameObject.h"
#include "../Scene.h"
#include "Transform.h"
#include "Camera.h"



CVector2 CRectCollider::GetLeftTopPosition() const
{
	CVector2 cameraPosition = m_pGameObject->GetScene()->GetCamera()->Transform()->GetPosition();
	CVector2 lt = CVector2(GetWorldPosition().x - m_Size.x / 2, GetWorldPosition().y - m_Size.y / 2);
	return lt - cameraPosition;
}

CVector2 CRectCollider::GetRightBottomPosition() const
{
	CVector2 cameraPosition = m_pGameObject->GetScene()->GetCamera()->Transform()->GetPosition();
	CVector2 rb = CVector2(GetWorldPosition().x + m_Size.x / 2, GetWorldPosition().y + m_Size.y / 2);
	return rb - cameraPosition;
}

void CRectCollider::LateUpdate()
{
#ifdef _DEBUG
	CVector2 cameraPosition = m_pGameObject->GetScene()->GetCamera()->Transform()->GetPosition();

	HPEN pen = CreatePen(PS_SOLID, 1, RGB(0,255,0));
	HDC dc = GET_SINGLE(CResourceManager)->GetBackBuffer()->GetDC();
	SelectObject(dc, pen);

	CVector2 lt = CVector2(GetWorldPosition().x - m_Size.x/2, GetWorldPosition().y - m_Size.y / 2);
	CVector2 rb = CVector2(lt.x + m_Size.x, lt.y + m_Size.y);

	lt -= cameraPosition;
	rb -= cameraPosition;

	MoveToEx(dc, lt.x, lt.y, NULL);
	LineTo(dc, rb.x, lt.y);
	LineTo(dc, rb.x, rb.y);
	LineTo(dc, lt.x, rb.y);
	LineTo(dc, lt.x, lt.y);

	DeleteObject(pen);
#endif // _DEBUG
}

void CRectCollider::SaveComponent(FILE * pFile)
{
	fwrite(&m_Size, sizeof(CVector2), 1, pFile);
}

void CRectCollider::LoadComponent(FILE * pFile)
{
	fread(&m_Size, sizeof(CVector2), 1, pFile);
}

CComponent * CRectCollider::clone()
{
	return new CRectCollider(*this);
}

CRectCollider::CRectCollider(const CRectCollider & component)
{
	m_Size = component.m_Size;
	m_eType = COLLIDER_TYPE::RECT;
	m_eComponentType = CT_RECT_COLLIDER;
	m_eComponentParentType = PT_COLLIDER;
}

CRectCollider::CRectCollider():
	m_Size(CVector2(10,10))
{
	m_eType = COLLIDER_TYPE::RECT;
	m_eComponentType = CT_RECT_COLLIDER;
	m_eComponentParentType = PT_COLLIDER;
}


CRectCollider::~CRectCollider()
{
}

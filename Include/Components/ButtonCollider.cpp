#include "ButtonCollider.h"
#include "Transform.h"
#include "../ResourceManager.h"
#include "../Texture.h"
#include "../Scene.h"
#include "../GameObject.h"

CVector2 CButtonCollider::GetLT() const
{
	CVector2 position = m_pTransform->GetPosition() + m_LocalPosition;
	return position - CVector2(m_Size.x * m_pTransform->GetPivot().x, m_Size.y * m_pTransform->GetPivot().y);
}

CVector2 CButtonCollider::GetRB() const
{
	CVector2 position = m_pTransform->GetPosition() + m_LocalPosition;
	return position + CVector2(m_Size.x * (1- m_pTransform->GetPivot().x), m_Size.y * (1 - m_pTransform->GetPivot().y));
}

void CButtonCollider::SaveComponent(FILE * pFile)
{
}

void CButtonCollider::LoadComponent(FILE * pFile)
{
}

CComponent * CButtonCollider::clone()
{
	return nullptr;
}

void CButtonCollider::LateUpdate()
{
#ifdef _DEBUG

	HPEN pen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	HDC dc = GET_SINGLE(CResourceManager)->GetBackBuffer()->GetDC();
	SelectObject(dc, pen);

	CVector2 lt = GetLT();
	CVector2 rb = GetRB();

	MoveToEx(dc, lt.x, lt.y, NULL);
	LineTo(dc, rb.x, lt.y);
	LineTo(dc, rb.x, rb.y);
	LineTo(dc, lt.x, rb.y);
	LineTo(dc, lt.x, lt.y);

	DeleteObject(pen);
#endif // _DEBUG

}

CButtonCollider::CButtonCollider(const CButtonCollider & component)
{
}

CButtonCollider::CButtonCollider()
{
}


CButtonCollider::~CButtonCollider()
{
	m_pGameObject->GetScene()->RemoveButtonCollider(this);
}

#pragma once
#include "../Collider.h"
class CRectCollider :
	public CCollider
{
private:
	CVector2 m_Size;

public :
	CVector2 GetLeftTopPosition() const ;
	CVector2 GetRightBottomPosition() const ;
	CVector2 GetSize() const
	{
		return m_Size;
	}
	void SetSize(CVector2 size)
	{
		m_Size = size;
	}
	void SetSize(float fWidth, float fHeight)
	{
		m_Size.x = fWidth;
		m_Size.y = fHeight;
	}
public:
	void LateUpdate() override;

public:
	void SaveComponent(FILE* pFile) override;
	void LoadComponent(FILE* pFile) override;
	CComponent* clone() override;

public:
	CRectCollider(const CRectCollider& component);
	CRectCollider();
	~CRectCollider();
};


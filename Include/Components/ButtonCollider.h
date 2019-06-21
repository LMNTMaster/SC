#pragma once
#include "../Collider.h"
class CButtonCollider :
	public CCollider
{
private:
	CVector2 m_LocalPosition;
	CVector2 m_Size;

public:

	void SetLocalPosition(CVector2 pos)
	{
		m_LocalPosition = pos;
	}
	void SetLocalPosition(float x, float y)
	{
		m_LocalPosition = CVector2(x, y);
	}

	CVector2 GetLocalPosition() const
	{
		return m_LocalPosition;
	}

	void SetSize(CVector2 size)
	{
		m_Size = size;
	}
	void SetSize(float width, float height)
	{
		m_Size = CVector2(width, height);
	}
	CVector2 GetSize() const
	{
		return m_Size;
	}

	CVector2 GetLT() const;
	
	CVector2 GetRB() const;

public:
	void SaveComponent(FILE* pFile) override;
	void LoadComponent(FILE* pFile) override;
	CComponent* clone() override;


public:
	void LateUpdate() override;

public:
	CButtonCollider(const CButtonCollider& component);
	CButtonCollider();
	~CButtonCollider();
};


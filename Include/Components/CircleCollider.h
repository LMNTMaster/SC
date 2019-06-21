#pragma once
#include "..\Collider.h"
class CCircleCollider :
	public CCollider
{
private:
	float m_fRadius;

public:
	float GetRadius() const
	{
		return m_fRadius;
	}
	void SetRadius(float fRadius)
	{
		m_fRadius = fRadius;
	}
public:
	void LateUpdate() override;

public:
	void SaveComponent(FILE* pFile) override;
	void LoadComponent(FILE* pFile) override;
	CComponent* clone() override;

public:
	CCircleCollider(const CCircleCollider&);
	CCircleCollider();
	~CCircleCollider();
};


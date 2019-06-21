#pragma once
#include "../Collider.h"
class CPointCollider :
	public CCollider
{

private:
	CVector2 m_Position;

public:
	void SetPosition(float x, float y)
	{
		m_Position = CVector2(x, y);
	}
	void SetPosition(CVector2 pos	)
	{
		m_Position = pos;
	}
	CVector2 GetPosition() const
	{
		return m_Position;
	}


public:
	void SaveComponent(FILE* pFile) override;
	void LoadComponent(FILE* pFile) override;

	CComponent* clone() override;

public:
	CPointCollider(const CPointCollider& component);
	CPointCollider();
	~CPointCollider();
};


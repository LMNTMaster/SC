#pragma once
#include "../Component.h"
#include "../Game.h"
class CTransform :
	public CComponent
{
private:
	CVector2 m_Pivot;
	CVector2 m_WorldPosition;
	CVector2 m_LocalPosition;
	CVector2 m_Scale;
	CVector2 m_LocalScale;
	float  m_Rotation;

public:
	void SetPivot(CVector2 pivot)
	{
		m_Pivot = pivot;
	}
	void SetPivot(float x, float y)
	{
		m_Pivot = CVector2(x, y);
	}
	void SetLocalScale(CVector2 scale)
	{
		m_LocalScale = scale;
	}
	void SetScale(CVector2 scale);
	void SetPosition(CVector2 pos);
	void SetPosition(float x, float y);
	void SetLocalPosition(CVector2 pos)
	{
		m_LocalPosition = pos;
	}
	void SetRotation(float fAngle)
	{
		m_Rotation = fAngle;
	}
	void SetRotation(CVector2 dir)
	{
		m_Rotation = CVector2::DirectionToAngle(dir);
	}
	
	float GetRotation() const
	{
		return m_Rotation;
	}
	CVector2 forword() const
	{
		return CVector2(cosf(D2R * m_Rotation), sinf(D2R * m_Rotation));
	}
	CVector2 right() const
	{
		return CVector2(cosf((m_Rotation + PI) * PI), sinf((m_Rotation + PI) * PI));
	}
	CVector2 left() const
	{
		return CVector2(cosf((m_Rotation - PI) * PI), sinf((m_Rotation - PI) * PI));
	}
	CVector2 backword() const
	{
		return CVector2(cosf(-PI * m_Rotation), sinf(-PI * m_Rotation));
	}

	CVector2 GetPivot() const
	{
		return m_Pivot;
	}
	CVector2 GetScale() const
	{
		return m_Scale;
	}
	CVector2 GetLocalScale() const
	{
		return m_LocalScale;
	}
	CVector2 GetPosition() const
	{
		return m_WorldPosition;
	}
	CVector2 GetLocalPosition() const
	{		
		return m_LocalPosition;
	}
public:

	void SaveComponent(FILE* pFile) override;
	void LoadComponent(FILE* pFile) override;
	CComponent* clone() override;


public:
	CTransform(const CTransform& component);
	CTransform();
	~CTransform();
};


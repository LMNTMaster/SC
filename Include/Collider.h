#pragma once
#include "Game.h"
#include "Component.h"

enum class COLLIDER_TYPE
{
	NONE,
	RECT,
	CIRCLE,
	POINT,
	PIXEL
};

class CCollider : public CComponent
{

protected:
	CVector2 m_LocalPosition;
	float m_fTileCollisionRadius;
	COLLIDER_TYPE m_eType;
	CCollider* m_pTarget;
	CVector2	m_CollidePosition;
	bool			m_bCollision;
	list<CCollider*> m_CollisionList;

public:
	float GetTileCollisionRadius() const
	{
		return m_fTileCollisionRadius;
	}
	void SetTileCollisionRadius(float fRadius)
	{
		m_fTileCollisionRadius = fRadius;
	}
	CVector2 GetWorldPosition() const;
	CVector2 GetLocalPosition() const
	{
		return m_LocalPosition;
	}
	COLLIDER_TYPE GetColliderType() const
	{
		return m_eType;
	}
	bool GetCollision() const
	{
		return m_bCollision;
	}
	CVector2 GetCollidePosition() const
	{
		return m_CollidePosition;
	}
	CCollider* GetTarget() const
	{
		return m_pTarget;
	}

	void SetLocalPosition(CVector2 pos)
	{
		m_LocalPosition = pos;
	}
	void SetColliderType(COLLIDER_TYPE eType)
	{
		m_eType = eType;
	}
	void SetCollision(bool bCollision)
	{
		m_bCollision = bCollision;
	}
	void SetCollidePosition(CVector2 position)
	{
		m_CollidePosition = position;
	}
	void SetTarget(CCollider* pTarget)
	{
		m_pTarget = pTarget;
	}

	
	bool CheckCollision(CCollider* pTarget);


	void AddColliderToCollisionList(CCollider* pCollider)
	{
		m_CollisionList.push_back(pCollider);
	}
	void RemoveColliderFromCollisionList(CCollider* pCollider)
	{
		list<CCollider*>::iterator iter;
		list<CCollider*>::iterator iterEnd = m_CollisionList.end();
		for (iter = m_CollisionList.begin(); iter != iterEnd; ++iter)
		{
			if ((*iter) == pCollider)
			{
				m_CollisionList.erase(iter); 
				break;
			}
		}
	}

	void ClearCollisionList()
	{
		m_CollisionList.clear();
	}
	const list<CCollider*>& GetCollisionList() const
	{
		return m_CollisionList;
	}
public:
	CCollider();
	virtual ~CCollider();
};


#pragma once
#include "Game.h"
class CComponent
{
private:
	friend class CGameObject;

private:
	bool m_bEnable;
	bool m_bDestroy;
	bool m_bStart;

protected:
	class CGameObject* m_pGameObject;
	class CTransform* m_pTransform;
	COMPONENT_PARENT_TYPE m_eComponentParentType;
	COMPONENT_TYPE m_eComponentType;

public:
	COMPONENT_PARENT_TYPE GetComponentParentType() 
	{
		return m_eComponentParentType;
	}
	COMPONENT_TYPE GetComponentType() 
	{
		return m_eComponentType;
	}

	bool GetEnable() const
	{
		return m_bEnable;
	}
	bool GetStart() const
	{
		return m_bStart;
	}
	bool GetDestroy() const
	{
		return m_bDestroy;
	}
	void SetEnable(bool bEnable)
	{
		m_bEnable = bEnable;
		if (!m_bEnable)
		{
			m_bStart = false;
		}
	}
	void SetStart(bool bStart)
	{
		m_bStart = bStart;
	}
	void SetDestroy(bool bDestroy)
	{
		m_bDestroy = bDestroy;
	}
	class CTransform* Transform() const
	{
		return m_pTransform;
	}
	CGameObject* GameObject() const
	{
		return m_pGameObject;
	}
	void SetGameObject(class CGameObject* gameObject);
	


private:

	virtual void Initialize();
	virtual void Start();
	virtual void Update();
	virtual void LateUpdate();
	virtual void CollisionEnter();
	virtual void CollisionStay();
	virtual void CollisionExit();
	virtual void Destroy();

public:
	virtual void SaveComponent(FILE* pFile) = 0;
	virtual void LoadComponent(FILE* pFile) = 0;
	virtual CComponent* clone() = 0;

public:
	CComponent();
	virtual ~CComponent();
};


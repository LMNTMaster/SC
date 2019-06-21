#pragma once
#include "../Component.h"
class CUnitInfo :
	public CComponent
{
private:
	friend class CInfoPanelManager;
	friend class CUnitStatus;

private:
	UNIT_INFO_STATE m_eInfoState;
	class CGameObject* m_pWorkTarget;
	class CTexture* m_pWorkTargetButtonTexture;
	float m_fProgress;
	list<class CGameObject*> m_WorkList;
	list<class CTexture*> m_WorkButtonTextureList;

	class CTexture* m_pWireframeTexture;
	class CAttack* m_pAttack;
	class CDeffence* m_pDeffence;
	class CShield* m_pShield;
	class CTexture* m_pUnitButtonTexture;

	float m_fProgressTimer;

public:
	CVector2 GetAvailablePosition();
	const list<class CGameObject*>& GetWorkList() const
	{
		return m_WorkList;
	}
	void AddQueue(class CGameObject* pTarget, class CTexture* pButtonTexture);
	
	void SetUnitButtonTexture(class CTexture* pTexture)
	{
		m_pUnitButtonTexture = pTexture;
	}
	class CTexture* GetUnitButtonTexture() const
	{
		return m_pUnitButtonTexture;
	}
	void SetInfoState(UNIT_INFO_STATE eState)
	{
		m_eInfoState = eState;
	}
	void SetAttackComponent(class CAttack* pAttack)
	{
		m_pAttack = pAttack;
	}
	void SetDeffenceComponent(class CDeffence* pDeffence)
	{
		m_pDeffence = pDeffence;
	}
	void SetShieldComponent(class CShield* pShield)
	{
		m_pShield = pShield;
	}

public:
	void Start() override;
	void Update() override;
public:
	void SaveComponent(FILE* pFile) override;
	void LoadComponent(FILE* pFile) override;

	CComponent* clone() override;


public:
	CUnitInfo(const CUnitInfo& component);
	CUnitInfo();
	~CUnitInfo();
};


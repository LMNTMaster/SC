#pragma once
#include "../ButtonComponent.h"
class CAttack :
	public CButtonComponent
{	
private:
	string m_strWeaponName;
	UPGRADE_TYPE m_eUpgradeType;
	float m_fAttackRange;
	float m_fUpgradeIncrease;
	float m_fDamage;
	float m_fInterval;
	float m_fIntervalTimer;
	ATTACK_MODE m_eAttackMode;
	class CGameObject* m_pTarget;
	bool m_bOnAttack;
	bool m_bStop;
	
public:
	class CGameObject* GetAttackTarget() const
	{
		return m_pTarget;
	}
	void SetTarget(class CGameObject* pTarget)
	{
		m_pTarget = pTarget;
	}
	void Stop()
	{
		m_bStop = true;
	}
	void SetUpgradeIncrease(float fValue)
	{
		m_fUpgradeIncrease = fValue;
	}
	float GetUpgradeIncrease() const
	{
		return m_fUpgradeIncrease;
	}
	void SetWeaponName(const string& strName)
	{
		m_strWeaponName = strName;
	}
	string GetWeaponName() const
	{
		return m_strWeaponName;
	}
	void SetUpgradeType(UPGRADE_TYPE eType)
	{
		m_eUpgradeType = eType;
	}
	UPGRADE_TYPE GetUpgradeType() const
	{
		return m_eUpgradeType;
	}
	void SetAttackRange(float fRange)
	{
		m_fAttackRange = fRange;
	}
	float GetAttackRange()
	{
		return m_fAttackRange;
	}
	void SetDamage(float fDamage)
	{
		m_fDamage = fDamage;
	}
	float GetDamage() const
	{
		return m_fDamage;
	}
	void SetInterval(float fInterval)
	{
		m_fInterval = fInterval;
	}
	float GetInterval() const
	{
		return m_fInterval;
	}

public:
	list<class CGameObject*> GetAttackRangeUnitList();

public:
	void RequestAttackMove(CVector2 position);
	void RequestAttackTarget(class CGameObject* pTarget);

public:
	void Start() override;
	void LateUpdate() override;

	void SaveComponent(FILE* pFile) override;
	void LoadComponent(FILE* pFile) override;
	CComponent* clone() override;

	void Attack();

public:
	CAttack(const CAttack& component);
	CAttack();
	~CAttack();
};


#pragma once
#include "../Component.h"
class CUnitStatus :
	public CComponent
{
private:
	friend class CUnitInfo;

private:
	float m_fCreateTime;
	float m_fMineralRequirement;
	float m_fGasRequirement;
	float m_fPopulationRequirement;

	float m_fHPMax;
	float m_fHP;
	float m_fHPGeneration;
	float m_fHPGenerationAmount;
	float m_fHPGenTime;

	float m_fMPMax;
	float m_fMP;
	float m_fMPGeneration;
	float m_fMPGenerationAmount;
	float m_fMPGenTime;

	float m_fShieldMax;
	float m_fShield;
	float m_fShieldGeneration;
	float m_fShieldGenerationAmount;
	float m_fShieldGenTime;

	float m_fSightRadius;

	list<class CGameObject*> m_AttackingUnitList;

public:
	float GetMineralRequirement() const
	{
		return m_fMineralRequirement;
	}
	float GetGasRequirement() const
	{
		return m_fGasRequirement;
	}
	float GetSupplyRequirement() const
	{
		return m_fPopulationRequirement;
	}
	void SetRequirement(float fTime, float fMineral, float fGas, float fSupply)
	{
		m_fCreateTime = fTime;
		m_fMineralRequirement = fMineral;
		m_fGasRequirement = fGas;
		m_fPopulationRequirement = fSupply;
	}
	float GetCreateTime() const
	{
		return m_fCreateTime;
	}
	void SetCreateTime(float fTime)
	{
		m_fCreateTime = fTime;
	}

	list<class CGameObject*> GetAttackingUnitList()
	{
		return m_AttackingUnitList;
	}
	void AddAttackUnit(class CGameObject* pUnit)
	{
		m_AttackingUnitList.push_back(pUnit);
	}
	void RemoveAttackUnit(class CGameObject* pUnit)
	{
		list<class CGameObject*>::iterator iter;
		list<class CGameObject*>::iterator iterEnd = m_AttackingUnitList.end();

		for (iter = m_AttackingUnitList.begin(); iter != iterEnd; ++iter)
		{
			if (*iter == pUnit)
			{
				m_AttackingUnitList.erase(iter);
				break;
			}			
		}
	}

	void SetHPMaxCondition()
	{
		m_fHP = m_fHPMax;
	}
	void SetMPMaxCondition()
	{
		m_fHP = m_fHPMax;
	}
	void SetShieldMaxCondition()
	{
		m_fShield = m_fShieldMax;
	}

	void SetMaxHP(float fMaxHP)
	{
		m_fHPMax = fMaxHP;
	}
	float GetMaxHP() const
	{
		return m_fHPMax;
	}
	void SetCurrentHP(float fHP)
	{
		m_fHP = fHP;
	}
	float GetCurrentHP() const
	{
		return m_fHP;
	}
	void AddHP(float fHP) 
	{
		m_fHP += fHP;
	}
	void SetMaxMP(float fMaxMP)
	{
		m_fMPMax = fMaxMP;
	}
	float GetMaxMP() const
	{
		return m_fMPMax;
	}
	void SetCurrentMP(float fMP)
	{
		m_fMP = fMP;
	}
	float GetCurrentMP() const
	{
		return m_fMP;
	}
	void AddMP(float fMP)
	{
		m_fMP += fMP;
	}
	

	void SetMaxShield(float fMaxShield)
	{
		m_fShieldMax = fMaxShield;
	}
	float GetMaxShield() const
	{
		return m_fShieldMax;
	}
	void SetCurrentShield(float fShield)
	{
		m_fShield = fShield;
	}
	float GetCurrentShield() const
	{
		return m_fShield;
	}
	void AddShield(float fShield)
	{
		m_fShield += fShield;
	}

	float GetSightRadius() const
	{
		return m_fSightRadius;
	}
	void SetSightRadius(float fRadius)
	{
		m_fSightRadius = fRadius;
	}

	void SetSightTile();

public:
	void Start() override;
		void Update() override;
public:

	void LoadComponent(FILE* pFile);
	void SaveComponent(FILE* pFile);
	CComponent* clone();
public:
	CUnitStatus(const CUnitStatus& component);
	CUnitStatus();
	~CUnitStatus();
};


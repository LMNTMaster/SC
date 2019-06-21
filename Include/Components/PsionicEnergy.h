#pragma once
#include "../Component.h"

class CPsionicEnergy :
	public CComponent
{

private:
	UPGRADE_TYPE m_eUpgradeType;
	float m_fValue;
	float m_fMaxValue;

public:
	UPGRADE_TYPE GetUpgradeType() const
	{
		return m_eUpgradeType;
	}
	float GetValue() const
	{
		return m_fValue;
	}
	float GetMaxValue() const
	{
		return m_fMaxValue;
	}
	void SetUpgradeType(UPGRADE_TYPE eType)
	{
		m_eUpgradeType = eType;
	}
	void SetValue(float fValue)
	{
		m_fValue = fValue;
	}
	void SetMaxValue(float fMaxValue)
	{
		m_fMaxValue = fMaxValue;
	}


	void Update() override;

public:
	void SaveComponent(FILE* pFile) override;
	void LoadComponent(FILE* pFile) override;
	CComponent* clone() override;

public:
	CPsionicEnergy(const CPsionicEnergy& component);
	CPsionicEnergy();
	~CPsionicEnergy();
};


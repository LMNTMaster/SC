#pragma once
#include "../Component.h"
#include "../Game.h"

class CDeffence :
	public CComponent
{
private:
	string m_strName;
	UPGRADE_TYPE m_eUpgradeType;
	float m_fValue;
	float m_fMaxValue;
	float m_fDamageDecrement;

public:
	void SetDamageDecrement(float fValue)
	{
		m_fDamageDecrement = fValue;
	}
	float GetDamageDecrement() const
	{
		return m_fDamageDecrement;
	}
	string GetName() const
	{
		return m_strName;
	}
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

	void SetName(const string& strName)
	{
		m_strName = strName;
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

public:
	void Update() override;
public:
	void SaveComponent(FILE* pFile) override;
	void LoadComponent(FILE* pFile) override;
	CComponent* clone() override;

public:
	CDeffence(const CDeffence& component);
	CDeffence();
	~CDeffence();
};


#pragma once
#include "../ButtonComponent.h"
class CRepair :
	public CButtonComponent
{
private:
	float m_fRestoreAmount;

public:
	void SetRepairAmount(float fValue)
	{
		m_fRestoreAmount = fValue;
	}
	float GetRepairAmount() const
	{
		return m_fRestoreAmount;
	}

public:

	void Start() override;
	void Update() override;

	void SaveComponent(FILE* pFile) override;
	void LoadComponent(FILE* pFile) override;
	CComponent* clone() override;

public:
	CRepair(const CRepair& component);
	CRepair();
	~CRepair();
};


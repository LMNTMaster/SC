#pragma once
#include "../../ButtonComponent.h"
class CEngineeringBay :
	public CButtonComponent
{
private:
	class CConsoleButton* m_pWeaponButton;
	class CConsoleButton* m_pArmorButton;

public:
	void UpgradeWeapon();
	void UpgradeArmor();

public:
	void Start() override;
	void Update() override;

public:
	void SaveComponent(FILE* pFile) override;
	void LoadComponent(FILE* pFile) override;
	CComponent* clone() override;

public:
	CEngineeringBay(const CEngineeringBay& component);
	CEngineeringBay();
	~CEngineeringBay();
};


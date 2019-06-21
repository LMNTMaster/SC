#pragma once
#include "../../ButtonComponent.h"
class CArmory :
	public CButtonComponent
{
private:
	class CConsoleButton* m_pVehicleWeapon;
	class CConsoleButton* m_pVehicleArmor;
	class CConsoleButton* m_pShipArmor;
	class CConsoleButton* m_pShipWeapon;

public:
	void UpgradeVehicleWeapon();
	void UpgradeVehicleArmor();
	void UpgradeShipWeapon();
	void UpgradeShipArmor();

public:
	void Start() override;
	void Update() override;

	void LoadComponent(FILE* pFile) override;
	void SaveComponent(FILE* pFile) override;
	CComponent* clone() override;

public:
	CArmory(const CArmory& component);
	CArmory();
	~CArmory();
};


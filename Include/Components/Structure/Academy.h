#pragma once
#include "../../ButtonComponent.h"
class CAcademy :
	public CButtonComponent
{
public:

	void UpgradeU238();
	void UpgradeOpticalFlare();
	void UpgradeStimpack();
	void UpgradeCaduceusReactor();
	void UpgradeRestoration();
	void RequestCancel();




private:
	class CConsoleButton* m_pU238;
	class CConsoleButton* m_pOpticalFlare;
	class CConsoleButton* m_pStimpack;
	class CConsoleButton* m_pCaduceusReactor;
	class CConsoleButton* m_pRestoration;


public:
	void Start() override;
	void Update() override;
	void LateUpdate() override;

	void LoadComponent(FILE* pFile) override;
	void SaveComponent(FILE* pFile) override;
	CComponent* clone() override;

public:
	CAcademy(const CAcademy& component);
	CAcademy();
	~CAcademy();
};


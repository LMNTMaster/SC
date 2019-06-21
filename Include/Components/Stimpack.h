#pragma once
#include "../ButtonComponent.h"
class CStimpack :
	public CButtonComponent
{
private:
	float m_fTimer;
	bool m_bEnableStimpack;
	float m_fOriginInterval;
	float m_fOriginMoveSpeed;

public:
	void RequestFunction();

public:
	void Start() override;
	void Update() override;
	void LateUpdate() override;

	void LoadComponent(FILE* pFile) override;
	void SaveComponent(FILE* pFile) override;
	CComponent* clone() override;

public:
	CStimpack(const CStimpack& component);
	CStimpack();
	~CStimpack();
};


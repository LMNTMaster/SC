#pragma once
#include "../ButtonComponent.h"

class CPatrol :
	public CButtonComponent
{
public:
	void Start() override;
	void Update() override;
	void LateUpdate() override;

	void LoadComponent(FILE* pFile) override;
	void SaveComponent(FILE* pFile) override;
	CComponent* clone() override;

public:
	CPatrol(const CPatrol& component);
	CPatrol();
	~CPatrol();
};


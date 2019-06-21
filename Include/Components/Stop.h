#pragma once
#include "../ButtonComponent.h"
class CStop :
	public CButtonComponent
{
public:
	void RequestStop();
public:
	void Start() override;
	void Update() override;

	void SaveComponent(FILE* pFile) override;
	void LoadComponent(FILE* pFile) override;
	CComponent* clone() override;

public:
	CStop(const CStop& component);
	CStop();
	~CStop();
};


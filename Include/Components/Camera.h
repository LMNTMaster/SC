#pragma once
#include "..\Component.h"
class CCamera :
	public CComponent
{

public:
	void SaveComponent(FILE* pFile) override;
	void LoadComponent(FILE* pFile) override;
	CComponent* clone() override;

public:
	CCamera(const CCamera& component);
	CCamera();
	~CCamera();
};


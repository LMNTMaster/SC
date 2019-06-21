#pragma once
#include "../ButtonComponent.h"
class CHold :
	public CButtonComponent
{
public:
	void Start() override;
	void Update() override;

	void SaveComponent(FILE* pFile) override;
	void LoadComponent(FILE* pFile) override;
	CComponent* clone() override;

public:
	CHold(const CHold& component);
	CHold();
	~CHold();
};


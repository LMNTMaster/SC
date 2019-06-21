#pragma once
#include "..\Component.h"
class CCameraMove :
	public CComponent
{
public:
	void Update() override;

public:
	void SaveComponent(FILE* pFile) override;
	void LoadComponent(FILE* pFile) override;
	CComponent* clone() override;

public:

	CCameraMove(const CCameraMove& component);
	CCameraMove();
	~CCameraMove();
};


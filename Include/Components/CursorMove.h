#pragma once
#include "../Component.h"
class CCursorMove :
	public CComponent
{

public:
	void Update() override;

	void LoadComponent(FILE* pFile) override;
	void SaveComponent(FILE* pFile) override;
	CComponent* clone() override;
public:
	CCursorMove();
	~CCursorMove();
};


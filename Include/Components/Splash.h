#pragma once
#include "../Component.h"
class CSplash :
	public CComponent
{
	
public :

	void Update() override;

public:
	void SaveComponent(FILE* pFile) override;
	void LoadComponent(FILE* pFile) override;
	CComponent* clone() override;

public:
	CSplash(const CSplash& component);
	CSplash();
	~CSplash();
};


#pragma once
#include "../Renderer.h"
class CFOW :
	public CRenderer
{
public:
	void Render() override;

public:
	void LoadComponent(FILE* pFile) override;
	void SaveComponent(FILE* pFile) override;
	CComponent* clone() override;

public:
	CFOW(const CFOW& component);
	CFOW();
	~CFOW();
};


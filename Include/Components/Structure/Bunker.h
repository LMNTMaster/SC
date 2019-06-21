#pragma once
#include "../../ButtonComponent.h"
class CBunker :
	public CButtonComponent
{
public:
	void Start() override;
	void Update() override;

public:
	void LoadComponent(FILE* pFile) override;
	void SaveComponent(FILE* pFile) override;
	CComponent* clone() override;

public:
	CBunker(const CBunker& component);
	CBunker();
	~CBunker();
};


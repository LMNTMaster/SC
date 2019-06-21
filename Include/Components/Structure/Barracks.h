#pragma once
#include "../../ButtonComponent.h"
class CBarracks :
	public CButtonComponent
{
private:
	list<class CConsoleButton*> m_ButtonList;

public:
	void RequestUnit(class CGameObject* pTarget, class CTexture* pIconTexture);

public:
	void Start() override;
	void Update() override;

public:
	void SaveComponent(FILE* pFile) override;
	void LoadComponent(FILE* pFile) override;
	CComponent* clone() override;

public:
	CBarracks(const CBarracks& component);
	CBarracks();
	~CBarracks();
};


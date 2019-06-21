#pragma once
#include "../../ButtonComponent.h"
class CCommandCenter :
	public CButtonComponent
{

	class CConsoleButton* m_pSCV;

public:
	void RequestUnit(class CGameObject * pTarget, class CTexture * pIconTexture);

public:
	void Start() override;
	void Update() override;

public:
	void LoadComponent(FILE* pFile) override;
	void SaveComponent(FILE* pFile) override;
	CComponent* clone() override;

public:
	CCommandCenter(const CCommandCenter& component);
	CCommandCenter();
	~CCommandCenter();
};


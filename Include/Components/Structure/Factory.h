#pragma once
#include "../../ButtonComponent.h"
class CFactory :
	public CButtonComponent
{
private:
	class CConsoleButton* m_pVulture;
	class CConsoleButton* m_pSiegeTank;
	class CConsoleButton* m_pGoliath;
	class CConsoleButton* m_pAddon;

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
	CFactory(const CFactory& component);
	CFactory();
	~CFactory();
};


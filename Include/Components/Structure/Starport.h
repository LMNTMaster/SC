#pragma once
#include "../../ButtonComponent.h"
class CStarport :
	public CButtonComponent
{
private:
	class CConsoleButton* m_pWraith;
	class CConsoleButton* m_pDropship;
	class CConsoleButton* m_pScienceVessel;
	class CConsoleButton* m_pBattlecruiser;
	class CConsoleButton* m_pValkyrie;
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
	CStarport(const CStarport& component);
	CStarport();
	~CStarport();
};


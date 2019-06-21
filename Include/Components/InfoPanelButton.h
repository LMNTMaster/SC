#pragma once
#include "../Component.h"
class CInfoPanelButton :
	public CComponent
{
private:
	class CGameObject* m_pUnit;

public:
	void SetUnit(class CGameObject* pUnit)
	{
		m_pUnit = pUnit;
	}
	class CGameObject* GetUnit() const
	{
		return m_pUnit;
	}

public:
	void CollisionStay() override;

public:
	void SaveComponent(FILE* pFile) override;
	void LoadComponent(FILE* pFile) override;
	CComponent* clone() override;
public:
	CInfoPanelButton(const CInfoPanelButton& component);
	CInfoPanelButton();
	~CInfoPanelButton();
};


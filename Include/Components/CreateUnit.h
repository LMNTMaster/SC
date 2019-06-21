#pragma once
#include "../ButtonComponent.h"
class CCreateUnit :
	public CButtonComponent
{
private:
	class CGameObject* m_pCreateTarget;

public:
	void SetCreateTarget( class CGameObject* pTarget)
	{
		m_pCreateTarget = pTarget;
	}
	class CGameObject* GetCreateTarget() const
	{
		m_pCreateTarget;
	}

public:
	void RequestCreateUnit(class CTexture* pIconTexture);

public:
	void Start() override;

public:
	void SaveComponent(FILE* pFile) override;
	void LoadComponent(FILE* pFile) override;
	CComponent* clone() override;

public:
	CCreateUnit(const CCreateUnit& component);
	CCreateUnit();
	~CCreateUnit();
};


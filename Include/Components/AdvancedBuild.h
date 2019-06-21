#pragma once
#include "../ButtonComponent.h"
class CAdvancedBuild :
	public CButtonComponent
{
private:
	class CGameObject* m_pRequestedBuilding;
	BUILD_STATE m_eBuildState;
	float m_fTimer;
	float m_fMoveTimer;

public:
	void SetRequestedBuilding(class CGameObject* pBuilding)
	{
		m_pRequestedBuilding = pBuilding;
	}
	class CGameObject* GetRequestedBuilding() const
	{
		return m_pRequestedBuilding;
	}
	void CancelBuild();

public:
	void Start() override;
	void Update() override;

	void SaveComponent(FILE* pFile) override;
	void LoadComponent(FILE* pFile) override;
	CComponent* clone() override;

public:
	CAdvancedBuild(const CAdvancedBuild& component);
	CAdvancedBuild();
	~CAdvancedBuild();
};


#pragma once
#include "../Component.h"
class CSingleButton :
	public CComponent
{
private:
	class CSpriteRenderer* m_pTargetRenderer;

public:
	void SetTarget(class CSpriteRenderer* pTarget)
	{
		m_pTargetRenderer = pTarget;
	}

public:
	void Update() override;
	void CollisionEnter() override;
	void CollisionStay() override;
	void CollisionExit() override;
public:
	void SaveComponent(FILE* pFile) override;
	void LoadComponent(FILE* pFile) override;
	CComponent* clone() override;

public:
	CSingleButton(const CSingleButton& component);
	CSingleButton();
	~CSingleButton();
};


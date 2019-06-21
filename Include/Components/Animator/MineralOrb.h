#pragma once
#include "../Animator.h"
class CMineralOrb :
	public CAnimator
{
private:
	class CGameObject* m_pTarget;
public:
	void SetTarget(class CGameObject* pTarget)
	{
		m_pTarget = pTarget;
	}
	class CGameObject* GetTarget()
	{
		return m_pTarget;
	}
public:
	void OnAnimationUpdate() override;
	void OnAnimationStart() override;
	void OnAnimationEnd() override;

public:

	void SaveComponent(FILE * pFile) override;
	void LoadComponent(FILE * pFile) override;
	CComponent* clone();

public:
	CMineralOrb(const CMineralOrb& component);
	CMineralOrb();
	~CMineralOrb();
};


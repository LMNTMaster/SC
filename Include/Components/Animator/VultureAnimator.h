#pragma once
#include "../Animator.h"
class CVultureAnimator :
	public CAnimator
{
public:
	void OnAnimationStart() override;
	void OnAnimationUpdate() override;
	void OnAnimationEnd() override;
public:
	void SaveComponent(FILE* pFile) override;
	void LoadComponent(FILE* pFile) override;
	CComponent* clone() override;
public:
	CVultureAnimator(const CVultureAnimator& component);
	CVultureAnimator();
	~CVultureAnimator();
};


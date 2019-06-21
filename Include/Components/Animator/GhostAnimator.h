#pragma once
#include "../Animator.h"
class CGhostAnimator :
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
	CGhostAnimator(const CGhostAnimator& component);
	CGhostAnimator();
	~CGhostAnimator();
};


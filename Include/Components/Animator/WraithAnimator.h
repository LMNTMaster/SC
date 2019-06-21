#pragma once
#include "../Animator.h"
class CWraithAnimator :
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
	CWraithAnimator(const CWraithAnimator& component);
	CWraithAnimator();
	~CWraithAnimator();
};


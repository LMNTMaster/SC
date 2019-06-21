#pragma once
#include "../Animator.h"
class CBattlecruiserAnimator :
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
	CBattlecruiserAnimator(const CBattlecruiserAnimator& component);
	CBattlecruiserAnimator();
	~CBattlecruiserAnimator();
};


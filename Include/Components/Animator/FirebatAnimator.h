#pragma once
#include "../Animator.h"
class CFirebatAnimator :
	public CAnimator
{
public:
	void OnAnimationUpdate() override;
	void OnAnimationStart() override;
	void OnAnimationEnd() override;

public:

	void SaveComponent(FILE * pFile) override;
	void LoadComponent(FILE * pFile) override;
	CComponent* clone();

public:
	CFirebatAnimator(const CFirebatAnimator& component);
	CFirebatAnimator();
	~CFirebatAnimator();
};


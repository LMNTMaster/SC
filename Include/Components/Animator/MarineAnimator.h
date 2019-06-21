#pragma once
#include "../Animator.h"
class CMarineAnimator :
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
	CMarineAnimator(const CMarineAnimator& component);
	CMarineAnimator();
	~CMarineAnimator();
};


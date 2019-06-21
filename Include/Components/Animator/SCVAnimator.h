#pragma once
#include "../Animator.h"
class CSCVAnimator :
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
	CSCVAnimator(const CSCVAnimator& component);
	CSCVAnimator();
	~CSCVAnimator();
};


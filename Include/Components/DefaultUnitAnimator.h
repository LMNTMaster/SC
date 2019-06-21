#pragma once
#include "Animator.h"
class CDefaultUnitAnimator :
	public CAnimator
{
public:
	void OnAnimationUpdate() override;
	void OnAnimationStart() override;
	void OnAnimationEnd() override;

public:
	void SaveComponent(FILE* pFile) override;
	void LoadComponent(FILE* pFile) override;
	CComponent* clone() override;


public:
	CDefaultUnitAnimator(const CDefaultUnitAnimator& component);
	CDefaultUnitAnimator();
	~CDefaultUnitAnimator();
};


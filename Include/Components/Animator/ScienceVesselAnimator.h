#pragma once
#include "../Animator.h"
class CScienceVesselAnimator :
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
	CScienceVesselAnimator(const CScienceVesselAnimator& component);
	CScienceVesselAnimator();
	~CScienceVesselAnimator();
};


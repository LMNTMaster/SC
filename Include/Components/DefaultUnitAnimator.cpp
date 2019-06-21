#include "DefaultUnitAnimator.h"



void CDefaultUnitAnimator::OnAnimationUpdate()
{
}

void CDefaultUnitAnimator::OnAnimationStart()
{
}

void CDefaultUnitAnimator::OnAnimationEnd()
{
}

void CDefaultUnitAnimator::SaveComponent(FILE * pFile)
{
}

void CDefaultUnitAnimator::LoadComponent(FILE * pFile)
{
}

CComponent * CDefaultUnitAnimator::clone()
{
	return new CDefaultUnitAnimator(*this);
}

CDefaultUnitAnimator::CDefaultUnitAnimator(const CDefaultUnitAnimator & component)
{

	m_eComponentType = CT_DEFAULT_UNIT_ANIMATOR;
}

CDefaultUnitAnimator::CDefaultUnitAnimator()
{
	m_eComponentType = CT_DEFAULT_UNIT_ANIMATOR;
}


CDefaultUnitAnimator::~CDefaultUnitAnimator()
{
}

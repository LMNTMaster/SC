#include "PsionicEnergy.h"
#include "UnitStatus.h"
#include "../GameObject.h"

void CPsionicEnergy::Update()
{
	CUnitStatus* pStatus = m_pGameObject->GetComponent<CUnitStatus>();

	m_fValue = pStatus->GetCurrentMP();
	m_fMaxValue = pStatus->GetMaxMP();
}

void CPsionicEnergy::SaveComponent(FILE * pFile)
{
	fwrite(&m_eUpgradeType, 4, 1, pFile);
	fwrite(&m_fValue, 4, 1, pFile);
	fwrite(&m_fMaxValue, 4, 1, pFile);
}

void CPsionicEnergy::LoadComponent(FILE * pFile)
{
	fread(&m_eUpgradeType, 4, 1, pFile);
	fread(&m_fValue, 4, 1, pFile);
	fread(&m_fMaxValue, 4, 1, pFile);
}

CComponent * CPsionicEnergy::clone()
{
	return new CPsionicEnergy(*this);
}

CPsionicEnergy::CPsionicEnergy(const CPsionicEnergy & component) :
	m_eUpgradeType(UT_NONE),
	m_fValue(0),
	m_fMaxValue(0)
{
	m_eUpgradeType = component.m_eUpgradeType;
	m_fValue = component.m_fValue;;
	m_fMaxValue = component.m_fMaxValue;

	m_eComponentParentType = PT_NONE;
	m_eComponentType = CT_ENERGY;

}

CPsionicEnergy::CPsionicEnergy():
	m_eUpgradeType(UT_NONE),
	m_fValue(0),
	m_fMaxValue(0)
{
	m_eComponentParentType = PT_NONE;
	m_eComponentType = CT_ENERGY;
}


CPsionicEnergy::~CPsionicEnergy()
{
}

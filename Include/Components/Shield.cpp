#include "Shield.h"
#include "UnitStatus.h"
#include "../GameObject.h"



void CShield::Update()
{
	CUnitStatus* pStatus = m_pGameObject->GetComponent<CUnitStatus>();

	m_fValue = pStatus->GetCurrentShield();
	m_fMaxValue = pStatus->GetMaxShield();
}


void CShield::SaveComponent(FILE * pFile)
{
	int iLength = 0;
	iLength = strlen(m_strName.c_str());
	fwrite(&iLength, 4, 1, pFile);
	fwrite(&m_strName, 1, iLength, pFile);
	fwrite(&m_eUpgradeType, 4, 1, pFile);
	fwrite(&m_fValue, 4, 1, pFile);
	fwrite(&m_fMaxValue, 4, 1, pFile);
}

void CShield::LoadComponent(FILE * pFile)
{
	int iLength = 0;
	fread(&iLength, 4, 1, pFile);
	fread(&m_strName, 1, iLength, pFile);
	fread(&m_eUpgradeType, 4, 1, pFile);
	fread(&m_fValue, 4, 1, pFile);
	fread(&m_fMaxValue, 4, 1, pFile);
}

CComponent * CShield::clone()
{
	return new CShield(*this);
}

CShield::CShield(const CShield & component):
	m_strName("Protoss Plasma Shields"),
	m_eUpgradeType(UT_PROTOSS_SHIELD),
	m_fValue(50),
	m_fMaxValue(50)
{
	m_strName = component.m_strName;
	m_eUpgradeType = component.m_eUpgradeType;
	m_fValue = component.m_fValue;
	m_fMaxValue = component.m_fMaxValue;
	m_eComponentParentType = PT_NONE;
	m_eComponentType = CT_SHIELD;
}

CShield::CShield():
	m_strName("Protoss Plasma Shields"),
	m_eUpgradeType(UT_PROTOSS_SHIELD),
	m_fValue(50),
	m_fMaxValue(50)
{
	m_eComponentParentType = PT_NONE;
	m_eComponentType = CT_SHIELD;
}


CShield::~CShield()
{
}

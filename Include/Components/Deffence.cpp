#include "Deffence.h"
#include "UnitStatus.h"
#include "../GameObject.h"



void CDeffence::Update()
{
	CUnitStatus* pStatus = m_pGameObject->GetComponent<CUnitStatus>();

	m_fValue = pStatus->GetCurrentShield();
	m_fMaxValue = pStatus->GetMaxShield();
}



void CDeffence::SaveComponent(FILE * pFile)
{
	int iLength = 0;
	char strBuffer[128] = {};
	strcpy(strBuffer, m_strName.c_str());
	iLength = strlen(strBuffer);
	fwrite(&iLength, 4, 1, pFile);
	fwrite(&strBuffer, 1, iLength, pFile);
	fwrite(&m_eUpgradeType, 4, 1, pFile);
	fwrite(&m_fValue, 4, 1, pFile);
	fwrite(&m_fMaxValue, 4, 1, pFile);
	fwrite(&m_fDamageDecrement, 4, 1, pFile);
}

void CDeffence::LoadComponent(FILE * pFile)
{
	int iLength = 0;
	char strBuffer[128] = {};

	fread(&iLength, 4, 1, pFile);
	fread(&strBuffer, 1, iLength, pFile);
	fread(&m_eUpgradeType, 4, 1, pFile);
	fread(&m_fValue, 4, 1, pFile);
	fread(&m_fMaxValue, 4, 1, pFile);
	fread(&m_fDamageDecrement, 4, 1, pFile);

	m_strName = string(strBuffer);
}

CComponent * CDeffence::clone()
{
	return new CDeffence(*this);
}

CDeffence::CDeffence(const CDeffence & component):
	m_strName(""),
	m_eUpgradeType(UT_NONE),
	m_fValue(50),
	m_fMaxValue(50),
	m_fDamageDecrement(0)
{
	m_strName = component.m_strName;
	m_eUpgradeType = component.m_eUpgradeType;
	m_fValue = component.m_fValue;
	m_fMaxValue = component.m_fMaxValue;
	m_eComponentParentType = PT_NONE;
	m_eComponentType = CT_DEFFENCE;
}

CDeffence::CDeffence():
	m_strName(""),
	m_eUpgradeType(UT_NONE),
	m_fValue(50),
	m_fMaxValue(50),
	m_fDamageDecrement(0)
{
	m_eComponentParentType = PT_NONE;
	m_eComponentType = CT_DEFFENCE;
}


CDeffence::~CDeffence()
{
}

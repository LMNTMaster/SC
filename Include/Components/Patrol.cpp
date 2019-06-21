#include "Patrol.h"



CPatrol::CPatrol(const CPatrol & component)
{
	m_eComponentType = CT_PATROL;
}

CPatrol::CPatrol()
{
	m_eComponentType = CT_PATROL;
}


CPatrol::~CPatrol()
{
	if (m_pButton)
		delete m_pButton;
}

void CPatrol::Start()
{
}

void CPatrol::Update()
{
}

void CPatrol::LateUpdate()
{
}

void CPatrol::LoadComponent(FILE * pFile)
{
}

void CPatrol::SaveComponent(FILE * pFile)
{
}

CComponent * CPatrol::clone()
{
	return new CPatrol(*this);
}
